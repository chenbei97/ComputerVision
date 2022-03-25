### 0.说明

只给出了[零基础入门数据挖掘 - 二手车交易价格预测-天池大赛-阿里云天池 (aliyun.com)](https://tianchi.aliyun.com/competition/entrance/231784/information)的解法，了解一下流程，我决定放弃。

**怎么说呢，突然觉得有心无力，很无聊，不想做这方面的事情，我还是专注于C++开发把，顺带一些机器学习之类的业务就可以**。

### 1. 读题

首先了解题目的背景和要求。

二手车交易记录有训练数据15万条，测试集A、B各5万条。

特征一共有31条，其中15条匿名特征，赛题的评价指标是平均绝对误差MAE。

本题是回归类型的题目，回归的常见评价指标是MAE、MAPE(平均绝对百分误差)、MSE(均方误差)、R2(均方根误差)等

### 2. 读取和查看数据

```python
# 1.读取数据
Train_data = pd.read_csv("PredictionSecondHandCarPrice/data/used_car_train_20200313.csv",sep=' ')
Test_data = pd.read_csv("PredictionSecondHandCarPrice/data/used_car_testB_20200421.csv",sep=' ')

# 2.查看数据情况
print(Train_data.head()) # 使用print可以防止后边的打印信息覆盖前边的
print(Test_data.head())
```

从结果可以看出，训练数据是150000×31，测试数据是50000×30，少的那一列是价格prices。

数据可能存在缺失值，可以通过info来查看，它可以统计出每列不是Nan的个数，或者使用isnull配合sum也可以这个统计的是Nan的个数。

```python
print(Train_data.info())
print(Test_data.info())

print(Train_data.isnull().sum()) # 统计nan的个数就是info的差值
print(Test_data.isnull().sum()) 
```

除了得到Nan的信息，还要注意是否存在缺省值，通过info的数据类型可以看出在"notRepairedDamage"这列的数据类型是object。

现在可以看看这列的值统计。

```python
print(Train_data["notRepairedDamage"].value_counts())
print(Test_data["notRepairedDamage"].value_counts())
```

其输出结果：

```python
0.0    111361
-       24324
1.0     14315
Name: notRepairedDamage, dtype: int64
0.0    37224
-       8069
1.0     4707
Name: notRepairedDamage, dtype: int64
```

可以看出，这列主要有3种数据类型，0、1和'-'，'-'就表示缺省。

### 3. 处理数据

处理数据主要是用Nan替换掉缺省值，而Nan因为很多模型有针对Nan的处理，所以如果Nan的数量很大无需自己处理。当然如果Nan的数量很少，可以自己填充值。填充的方法主要有中位数、众数、平均值填充等，这些可以单独了解。

首先处理"notRepairedDamage"列的缺省值。

```python
# 将缺省值替换为np.nan
Train_data['notRepairedDamage'].replace('-', np.nan, inplace=True)
Test_data['notRepairedDamage'].replace('-', np.nan, inplace=True)
```

其次观察，某些数据是否存在严重的不平衡。例如一些属性只有0和1的取值，但是其中1个的取值远远大于另1个取值，那这种其实没有意义，所以可以删除这样的属性列。本题的"seller"和"offerType"就属于这种情况，可以使用value_counts同样去查看它们，它们的取值存在严重的不平衡，所以可以del可以删除它们。

```python
del Train_data["seller"]
del Train_data["offerType"]
del Test_data["seller"]
del Test_data["offerType"]
```

然后查看训练数据prices的分布情况，可以用scipy.stat提供的分布，如无界约翰逊分布等，绘图可以使用seaborn的distplot绘图，这个图专门用于灵活地绘制观察值的单变量分布。

```python
import seaborn as sns
import scipy.stats as sst
y = Train_data['price']
plt.subplot(131)
sns.distplot(y,kde=False,fit=sst.johnsonsu)
plt.title("johnsonsu distribution")
plt.subplot(132)
sns.distplot(y,kde=False,fit=sst.norm)
plt.title("norm distribution")
plt.subplot(133)
sns.distplot(y,kde=False,fit=sst.lognorm)
plt.title("lognorm distribution")
plt.show()
```

图的结果如下。![price_dirtribution](user_data/price_distribution.jpg)

可以看出预测数据并不满足正态分布，所以需要转换，下图给出prices不引入分布的纯频数直方图，及其对数变换后的直方图。可以看出对数转换后prices比较符合正态分布，所以我们真正用来训练的目标值是log('prices')。

```python
fig,axes =plt.subplots(2,1)
axes.flatten()
ys = [Train_data['price'],np.log(Train_data['price'])]
for axe ,y in zip(axes,ys):
    axe.hist(y, orientation = 'vertical',histtype = 'bar', color ='red')
fig.show()
```

结果图示意如下。![prices_hist_linear_log](user_data/prices_hist_linear_log.jpg)

提取特征首先要看数据有什么特征，要区分开数字特征和类型特征，如果数据源已经通过np.number和np.object区分的话，就可以使用以下方式，直接获取。

```python
numeric_features = Train_data.select_dtypes(include=[np.number])
categorical_features = Train_data.select_dtypes(include=[np.object])
```

但是现在很多特征并不简单的通过number和object区分，所以需要手动区分。

```c++
numeric_features = ['power', 'kilometer', 'v_0', 'v_1', 'v_2', 'v_3', 'v_4', 'v_5', 'v_6', 'v_7', 'v_8', 'v_9', 'v_10', 'v_11', 'v_12', 'v_13','v_14','price']

categorical_features = ['name', 'model', 'brand', 'bodyType', 'fuelType', 'gearbox', 'notRepairedDamage', 'regionCode',]
```

### 4.提取特征

常见的特征工程：异常值/缺失值处理、标准化/归一化、构造特征(均值、方差、特征组合和变换)、特征筛选(过滤式、包裹式和嵌入式)和特征降维(PCA等)

下方的代码具体的实现，我不对其进行深究，因为先验知识取决于对业务的了解，只熟悉如何处理数据这个过程。

```python
# 3.1 过滤异常值
def outliers_proc(data, col_name, scale=3):
    """
    用于清洗异常值，默认用 box_plot（scale=3）进行清洗
    :param data: 接收 pandas 数据格式
    :param col_name: pandas 列名
    :param scale: 尺度
    :return:
    """

    def box_plot_outliers(data_ser, box_scale):
        """
        利用箱线图去除异常值
        :param data_ser: 接收 pandas.Series 数据格式
        :param box_scale: 箱线图尺度，
        :return:
        """
        iqr = box_scale * (data_ser.quantile(0.75) - data_ser.quantile(0.25))
        val_low = data_ser.quantile(0.25) - iqr
        val_up = data_ser.quantile(0.75) + iqr
        rule_low = (data_ser < val_low)
        rule_up = (data_ser > val_up)
        return (rule_low, rule_up), (val_low, val_up)

    data_n = data.copy()
    data_series = data_n[col_name]
    rule, value = box_plot_outliers(data_series, box_scale=scale)
    index = np.arange(data_series.shape[0])[rule[0] | rule[1]]
    print("Delete number is: {}".format(len(index)))
    data_n = data_n.drop(index)
    data_n.reset_index(drop=True, inplace=True)
    print("Now column number is: {}".format(data_n.shape[0]))
    index_low = np.arange(data_series.shape[0])[rule[0]]
    outliers = data_series.iloc[index_low]
    print("Description of data less than the lower bound is:")
    print(pd.Series(outliers).describe())
    index_up = np.arange(data_series.shape[0])[rule[1]]
    outliers = data_series.iloc[index_up]
    print("Description of data larger than the upper bound is:")
    print(pd.Series(outliers).describe())

    fig, ax = plt.subplots(1, 2, figsize=(10, 7))
    sns.boxplot(y=data[col_name], data=data, palette="Set1", ax=ax[0])
    sns.boxplot(y=data_n[col_name], data=data_n, palette="Set1", ax=ax[1])
    return data_n
Train_data = outliers_proc(Train_data, 'power', scale=3)
# 3.2 拼接训练和测试集
Train_data['train']=1
Test_data['train']=0
data = pd.concat([Train_data, Test_data], ignore_index=True)
# 3.3 构造特征used_time 汽车使用时间，一般来说价格与使用时间成反比
data['used_time'] = (pd.to_datetime(data['creatDate'], format='%Y%m%d', errors='coerce') -
                         pd.to_datetime(data['regDate'], format='%Y%m%d', errors='coerce')).dt.days
# 3.4 邮编对应城市
data['city'] = data['regionCode'].apply(lambda x : str(x)[:-3])
data = data
# 3.5 计算某品牌的销售统计量
Train_gb = Train_data.groupby("brand")
all_info = {}
for kind, kind_data in Train_gb:
    info = {}
    kind_data = kind_data[kind_data['price'] > 0]
    info['brand_amount'] = len(kind_data)
    info['brand_price_max'] = kind_data.price.max()
    info['brand_price_median'] = kind_data.price.median()
    info['brand_price_min'] = kind_data.price.min()
    info['brand_price_sum'] = kind_data.price.sum()
    info['brand_price_std'] = kind_data.price.std()
    info['brand_price_average'] = round(kind_data.price.sum() / (len(kind_data) + 1), 2)
    all_info[kind] = info
brand_fe = pd.DataFrame(all_info).T.reset_index().rename(columns={"index": "brand"})
data = data.merge(brand_fe, how='left', on='brand')
# 3.6 数据分桶 以 power 为例
bin = [i*10 for i in range(31)]
data['power_bin'] = pd.cut(data['power'], bin, labels=False)
data[['power_bin', 'power']].head()
data = data.drop(['creatDate', 'regDate', 'regionCode'], axis=1)
# 3.7 导出数据给模型使用
data.to_csv('PredictionSecondHandCarPrice/user_data/data_for_tree.csv', index=0)
```

如果不是给树模型使用，而是LR等回归模型使用，可以这样做。

```python
from sklearn import preprocessing
min_max_scaler = preprocessing.MinMaxScaler()
data['power'] = np.log(data['power'] + 1)
data['power'] = ((data['power'] - np.min(data['power'])) / (np.max(data['power']) - np.min(data['power'])))
data['kilometer'] = ((data['kilometer'] - np.min(data['kilometer'])) /
                        (np.max(data['kilometer']) - np.min(data['kilometer'])))
def max_min(x):
    return (x - np.min(x)) / (np.max(x) - np.min(x))
data['brand_amount'] = ((data['brand_amount'] - np.min(data['brand_amount'])) /
                        (np.max(data['brand_amount']) - np.min(data['brand_amount'])))
data['brand_price_average'] = ((data['brand_price_average'] - np.min(data['brand_price_average'])) /
                               (np.max(data['brand_price_average']) - np.min(data['brand_price_average'])))
data['brand_price_max'] = ((data['brand_price_max'] - np.min(data['brand_price_max'])) /
                           (np.max(data['brand_price_max']) - np.min(data['brand_price_max'])))
data['brand_price_median'] = ((data['brand_price_median'] - np.min(data['brand_price_median'])) /
                              (np.max(data['brand_price_median']) - np.min(data['brand_price_median'])))
data['brand_price_min'] = ((data['brand_price_min'] - np.min(data['brand_price_min'])) /
                           (np.max(data['brand_price_min']) - np.min(data['brand_price_min'])))
data['brand_price_std'] = ((data['brand_price_std'] - np.min(data['brand_price_std'])) /
                           (np.max(data['brand_price_std']) - np.min(data['brand_price_std'])))
data['brand_price_sum'] = ((data['brand_price_sum'] - np.min(data['brand_price_sum'])) /
                           (np.max(data['brand_price_sum']) - np.min(data['brand_price_sum'])))
# 4.2 对类别进行独热编码
data = pd.get_dummies(data, columns=['model', 'brand', 'bodyType', 'fuelType',
                                     'gearbox', 'notRepairedDamage', 'power_bin'])
# 4.3 导出给lr模型使用
data.to_csv('PredictionSecondHandCarPrice/user_data/data_for_lr.csv',index=0)
```

### 5.建立模型

以LR模型为例。

```c++
# 1 调整数据类型
def reduce_mem_usage(df):
    """ iterate through all the columns of a dataframe and modify the data type
        to reduce memory usage.
    """
    start_mem = df.memory_usage().sum()
    print('Memory usage of dataframe is {:.2f} MB'.format(start_mem))

    for col in df.columns:
        col_type = df[col].dtype

        if col_type != object:
            c_min = df[col].min()
            c_max = df[col].max()
            if str(col_type)[:3] == 'int':
                if c_min > np.iinfo(np.int8).min and c_max < np.iinfo(np.int8).max:
                    df[col] = df[col].astype(np.int8)
                elif c_min > np.iinfo(np.int16).min and c_max < np.iinfo(np.int16).max:
                    df[col] = df[col].astype(np.int16)
                elif c_min > np.iinfo(np.int32).min and c_max < np.iinfo(np.int32).max:
                    df[col] = df[col].astype(np.int32)
                elif c_min > np.iinfo(np.int64).min and c_max < np.iinfo(np.int64).max:
                    df[col] = df[col].astype(np.int64)
            else:
                if c_min > np.finfo(np.float16).min and c_max < np.finfo(np.float16).max:
                    df[col] = df[col].astype(np.float16)
                elif c_min > np.finfo(np.float32).min and c_max < np.finfo(np.float32).max:
                    df[col] = df[col].astype(np.float32)
                else:
                    df[col] = df[col].astype(np.float64)
        else:
            df[col] = df[col].astype('category')

    end_mem = df.memory_usage().sum()
    print('Memory usage after optimization is: {:.2f} MB'.format(end_mem))
    print('Decreased by {:.1f}%'.format(100 * (start_mem - end_mem) / start_mem))
    return df
sample_feature = reduce_mem_usage(
    pd.read_csv('PredictionSecondHandCarPrice/user_data/data_for_lr.csv'))
# 2. 获取训练集数据和标签
continuous_feature_names = [x for x in sample_feature.columns if x not in ['price','brand','model','brand']]
sample_feature = sample_feature.dropna().replace('-', 0).reset_index(drop=True)
train = sample_feature[continuous_feature_names + ['price']]
train_X = train[continuous_feature_names]
train_y = train['price']
# 3.训练模型
from sklearn.linear_model import LinearRegression
model = LinearRegression(normalize=True)
train_y_ln = np.log(train_y + 1)
model = model.fit(train_X, train_y_ln)
# 4.随机值输入预测验证模型
subsample_index = np.random.randint(low=0, high=len(train_y), size=50)
plt.scatter(train_X['v_9'][subsample_index], train_y[subsample_index], color='black')
plt.scatter(train_X['v_9'][subsample_index], np.exp(model.predict(train_X.loc[subsample_index])), color='blue')
plt.xlabel('v_9')
plt.ylabel('price')
plt.legend(['True Price','Predicted Price'],loc='upper right')
print('The predicted price seems normal after np.log transforming')
plt.show()
# 5.五折交叉验证
from sklearn.model_selection import cross_val_score
from sklearn.metrics import mean_absolute_error,  make_scorer
def log_transfer(func):
    def wrapper(y, yhat):
        result = func(np.log(y), np.nan_to_num(np.log(yhat)))
        return result
    return wrapper
scores = cross_val_score(model, X=train_X, y=train_y_ln,
                         verbose=1, cv = 5,
                         scoring=make_scorer(log_transfer(mean_absolute_error)))
print(np.mean(scores))
# 6 模拟业务真实情况
import datetime
sample_feature = sample_feature.reset_index(drop=True)
split_point = len(sample_feature) // 5 * 4
train = sample_feature.loc[:split_point].dropna()
val = sample_feature.loc[split_point:].dropna()

train_X = train[continuous_feature_names]
train_y_ln = np.log(train['price'] + 1)
val_X = val[continuous_feature_names]
val_y_ln = np.log(val['price'] + 1)
model = model.fit(train_X, train_y_ln)
print("mae => ",mean_absolute_error(val_y_ln, model.predict(val_X)))
# 7 绘制学习率曲线和验证曲线
from sklearn.model_selection import learning_curve, validation_curve
def plot_learning_curve(estimator, title, X, y, ylim=None, cv=None,n_jobs=1, train_size=np.linspace(.1, 1.0, 5 )):
    plt.figure()
    plt.title(title)
    if ylim is not None:
        plt.ylim(*ylim)
    plt.xlabel('Training example')
    plt.ylabel('score')
    train_sizes, train_scores, test_scores = learning_curve(estimator, X, y, cv=cv, n_jobs=n_jobs, train_sizes=train_size, scoring = make_scorer(mean_absolute_error))
    train_scores_mean = np.mean(train_scores, axis=1)
    train_scores_std = np.std(train_scores, axis=1)
    test_scores_mean = np.mean(test_scores, axis=1)
    test_scores_std = np.std(test_scores, axis=1)
    plt.grid()#区域
    plt.fill_between(train_sizes, train_scores_mean - train_scores_std,
                     train_scores_mean + train_scores_std, alpha=0.1,
                     color="r")
    plt.fill_between(train_sizes, test_scores_mean - test_scores_std,
                     test_scores_mean + test_scores_std, alpha=0.1,
                     color="g")
    plt.plot(train_sizes, train_scores_mean, 'o-', color='r',
             label="Training score")
    plt.plot(train_sizes, test_scores_mean,'o-',color="g",
             label="Cross-validation score")
    plt.legend(loc="best")
    plt.show()
plot_learning_curve(LinearRegression(), 'Liner_model',
                    train_X[:1000], train_y_ln[:1000],
                    ylim=(0.0, 0.5), cv=5, n_jobs=1)
# 8 导出模型
import pickle
with open('PredictionSecondHandCarPrice/model/myLrModel.pickle', 'wb') as f:
    pickle.dump(model, f)
```

后面就是使用模型预测的问题了，不再说明。









