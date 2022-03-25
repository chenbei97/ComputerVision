#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : getFeatures.py
@Author : chenbei
@Date : 2022-03-24 8:20
@Email ：chenbei_electric@163.com
@Address : Beijing Jiaotong University
'''
from matplotlib.pylab import mpl
mpl.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
# mpl.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
mpl.rcParams['savefig.dpi'] = 600  # 图片像素
mpl.rcParams['figure.dpi'] = 600  # 分辨率
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns
import scipy.stats as sst
# 1.读取数据
Train_data = pd.read_csv("PredictionSecondHandCarPrice/data/used_car_train_20200313.csv",sep=' ')
Test_data = pd.read_csv("PredictionSecondHandCarPrice/data/used_car_testB_20200421.csv",sep=' ')

# 2.查看数据情况
# 2.1 查看头
print(Train_data.head()) # 使用print可以防止后边的打印信息覆盖前边的
print(Test_data.head())
# 2.2 查看nan的情况
print(Train_data.info())
print(Test_data.info())
print(Train_data.isnull().sum()) # 统计nan的个数就是info的差值
print(Test_data.isnull().sum())
# 2.3 查看缺省值obeject的情况
print(Train_data["notRepairedDamage"].value_counts())
print(Test_data["notRepairedDamage"].value_counts())
# 将缺省值替换为np.nan
Train_data['notRepairedDamage'].replace('-', np.nan, inplace=True)
Test_data['notRepairedDamage'].replace('-', np.nan, inplace=True)
# 2.4 删除严重不平衡的属性列
del Train_data["seller"]
del Train_data["offerType"]
del Test_data["seller"]
del Test_data["offerType"]
# 2.5 查看训练数据的预测分布
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
# 2.6 查看频数直方图,将其转换为对数满足正态分布效果更好
fig,axes =plt.subplots(2,1)
axes.flatten()
ys = [Train_data['price'],np.log(Train_data['price'])]
for axe ,y in zip(axes,ys):
    axe.hist(y, orientation = 'vertical',histtype = 'bar', color ='red')
fig.show()
# 2.7 观察数字特征和类型特征
numeric_features = ['power', 'kilometer', 'v_0', 'v_1', 'v_2', 'v_3',
                    'v_4', 'v_5', 'v_6', 'v_7', 'v_8', 'v_9', 'v_10',
                    'v_11', 'v_12', 'v_13','v_14','price']

categorical_features = ['name', 'model', 'brand', 'bodyType', 'fuelType',
                        'gearbox', 'notRepairedDamage', 'regionCode',]
#%%
# 3 特征工程建立
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
#%%
# 4 可以再构造一份特征给 LR NN 之类的模型用
# 4.1 标准化和归一化
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