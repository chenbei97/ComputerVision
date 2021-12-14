#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : December_03_SVM.py
@Author : chenbei
@Date : 2021-12-14 8:01
@Email ：chenbei_electric@163.com
'''
from matplotlib.pylab import mpl
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns
from sklearn.datasets import load_digits, make_moons
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import confusion_matrix, accuracy_score
from sklearn import svm
mpl.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
mpl.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
mpl.rcParams['savefig.dpi'] = 600  # 图片像素
mpl.rcParams['figure.dpi'] = 600  # 分辨率

#%% (1)SVM的简单应用 ：数据集依然使用逻辑回归中的月亮数据集以比较逻辑回归与支持向量机的性能
n_samples = 1000
train_size = 0.7
random_state = 15
data = make_moons(n_samples=n_samples,shuffle=True,noise=0.5,random_state=10)
X ,y = data[0],data[1]
X_train,X_test,y_train,y_test = train_test_split(X,y,shuffle=True,random_state=random_state,train_size=train_size)
model = svm.SVC(kernel="linear",C=0.1,random_state=random_state)
model.fit(X_train,y_train)
y_pred = model.predict(X_test)
score = accuracy_score(y_test,y_pred) # 得分 0.786666
# (1.1)混淆矩阵展示
cm = pd.DataFrame(confusion_matrix(y_test,y_pred))
sns.set(font_scale=1.2) # 字体
sns.heatmap(cm,annot=True,annot_kws={"size":16},fmt="d",cbar=False)
plt.show()
# (1.2)散点图展示
x_min, x_max = X[:, 0].min() - 0.2, X[:, 0].max() + 0.2
y_min, y_max = X[:, 1].min() - 0.2, X[:, 1].max() + 0.2
xx, yy = np.meshgrid(np.arange(x_min, x_max, 0.02),
                     np.arange(y_min, y_max, 0.02))
points = np.c_[xx.ravel(), yy.ravel()] # 首先展平然后按列拼接成坐标点

Z = model.predict(points) # 所有坐标点都预测一遍
Z = Z.reshape(xx.shape) # 把列向量Z按照网格形状重塑
plt.contourf(xx, yy, Z, cmap = plt.cm.rainbow, alpha=0.6)
plt.scatter(X[:, 0], X[:, 1], marker='o', c=y.ravel(), s=10, lw=3)
plt.title('Linear SVM')
plt.show()
#(1.3)简单调参 首先比较不同核
for kernel in ["rbf","poly","sigmoid"]:
    if kernel == "poly":
        model = svm.SVC(kernel=kernel,C=0.1,degree=5,random_state=random_state)
    else:
        model =  svm.SVC(kernel=kernel,C=0.1,random_state=random_state)
    model.fit(X_train, y_train)
    print(f"kernel={kernel} score={model.score(X_test,y_test)}")
# 从结果来看 rbf核最好，那就固定为rbf核再改变C
# kernel=rbf score=0.8033333333333333
# kernel=poly score=0.73
# kernel=sigmoid score=0.59
# (1.4)比较不同正则化系数C
for C in [0.5,0.1,0.05,0.01,0.001]:
    model = svm.SVC(kernel="rbf", C=C,random_state=random_state)
    model.fit(X_train, y_train)
    print(f"C={C} score={model.score(X_test, y_test)}")
# 从结果来看C=0.1最好
# C=0.5 score=0.8
# C=0.1 score=0.8033333333333333
# C=0.05 score=0.7966666666666666
# C=0.01 score=0.77
# C=0.001 score=0.47
#(1.5)对于poly核可以单独比较degree
for degree in [3,5,7,10,15]:
    model = svm.SVC(kernel="poly", degree=degree, random_state=random_state)
    model.fit(X_train, y_train)
    print(f"degree={degree} score={model.score(X_test, y_test)}")
# 从结果来看degree=3最好，幂数过高反而过拟合
# degree=3 score=0.76
# degree=5 score=0.73
# degree=7 score=0.72
# degree=10 score=0.6166666666666667
# degree=15 score=0.6666666666666666
#(1.6)对于rbf核可以单独比较高斯核系数gamma
for gamma in [0.1,1,5,10,20,50]:
    model = svm.SVC(kernel="rbf", gamma=gamma, random_state=random_state)
    model.fit(X_train, y_train)
    print(f"gamma={gamma} score={model.score(X_test, y_test)}")
# 从结果来看gamma=1最好
# gamma=0.1 score=0.7966666666666666
# gamma=1 score=0.8
# gamma=5 score=0.7966666666666666
# gamma=10 score=0.7933333333333333
# gamma=20 score=0.7866666666666666
# gamma=50 score=0.7833333333333333
# 从以上结果来看，支持向量机最高也就0.8，逻辑回归最高0.84，所以看起来逻辑回归好一些
#%% (2)月亮数据集改变为图片识别的实际问题
# (2.1) 将0视为0,1-7视为1(不平衡数据集)
data = load_digits()
X = data["data"] # 已经展平的数据
# 归一化
# X_norm = np.zeros_like(X)
# for i in range(X.shape[0]):
#     minval,maxval = np.min(X[i,:]),np.max(X[i,:]) # 不同特征之间归一化也就是对每一行向量计算
#     X_norm[i,:] = np.array([(x-minval)/(maxval-minval) for x in X[i,:]])
# 标准化也是可以的，得分没有区别
scalar = StandardScaler()
X_norm = scalar.fit_transform(X)
y = data["target"] #0-7共8类
# 由于二分类问题可以用于可视化，所以将y除了0类以外的都看作1，但是要注意样本不平稳问题
y_new = np.array([1 if i !=0  else 0  for i in y]) # 改变标签只有0与1
train_size = 0.7
random_state = 10
X_train,X_test,y_train,y_test = train_test_split(X_norm,y_new,shuffle=True,random_state=random_state,train_size=train_size)
count = list(y_train).count(0) # 127 不平衡率 127 :: 1257
n_multiple = len(y_train)/ count # 不平衡倍数
# class_weight是字典,样本多的类别惩罚越大 0:1,1:n_multiple 0:count,1:len(y_train)-count
model = svm.SVC(kernel="rbf",class_weight={0:1,1:n_multiple},random_state=random_state)
model.fit(X_train,y_train)
y_pred = model.fit(X_test, y_test)
print(f"score={model.score(X_test, y_test)}")
# (2.2)将类别0和1的数据集单独抽取出来(平衡数据集)
XT = np.c_[X_norm,y.reshape(-1,1)]
X0,X1,y0,y1 = [],[],[],[]
for idx , value in enumerate(XT):
    if value[-1] == 0 : # 标签列为0、1的单取出来
        X0.append(value[:-1])
        y0.append(value[-1])
    if value[-1] == 1 :
        X1.append(value[:-1])
        y1.append(value[-1])
X0,X1 = np.array(X0),np.array(X1) # 178和182基本1：1平衡
y0,y1 = np.array(y0),np.array(y1)
X01 = np.r_[X0,X1] # 按行叠放 0类在前1类在后
y01 = np.c_[y0.reshape(1,-1),y1.reshape(1,-1)].reshape(-1)# 0类在前1类在后
model = svm.SVC(kernel="rbf",random_state=random_state)
X_train,X_test,y_train,y_test = train_test_split(X01,y01,shuffle=True,random_state=random_state,train_size=train_size)
model.fit(X_train,y_train)
print(f"score={model.score(X_test, y_test)}") # 1.0
#%% (2.3)不进行二分类进行八分类
model = svm.SVC(kernel="linear",random_state=random_state) # rbf
X_train,X_test,y_train,y_test = train_test_split(X_norm,y,shuffle=True,random_state=random_state,train_size=train_size)
model.fit(X_train,y_train)
print(f"score={model.score(X_test, y_test)}") # rbf：score=0.9685185185185186 linear：score=0.9703703703703703
#%(2.4)综合搜索最佳参数
#%%
from sklearn.model_selection import GridSearchCV
params = [
        {'kernel': ['linear'], 'C': [x for x in np.linspace(0.01,1,15)]},
        {'kernel': ['poly'], 'C': [1.], 'degree': [x for x in np.arange(2,15)]},
        {'kernel': ['rbf'], 'C': [x for x in np.linspace(0.01,1,15)], 'gamma':[x for x in np.linspace(0.001,1,20)]}
        ]
# estimator：指定选用的估计器
# param_grid：配套的估计器网格参数，使用字典，关键字是参数名，值是列表
# cv：交叉验证次数，默认5
# iid ：为真时返回交叉验证的平均测试集得分,默认False
# scoring ：评价测试集的指标，默认是准确率'accuracy'
# https://blog.csdn.net/qq_41076797/article/details/102755893查看相关可选指标
# return_train_score：计算训练的得分，默认False，此时属性cv_results_不会返回训练得分
# refit：默认为True，会在整个数据集上使用最佳参数重新调整估计器
model = GridSearchCV(svm.SVC(probability=True),
                        params,
                        scoring="accuracy",
                        iid=True,
                        refit=True,
                        return_train_score=True,
                        cv=5)
#%%
import time
t = time.time()
model.fit(X_train, y_train) # 8分类问题
print("cost time = ",time.time()-t)
# GridSearchCV的属性
print('Attrabutes:vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv')
print('cv_results_:',model.cv_results_.keys())
print('Desc:',model.cv_results_['params'][2], model.cv_results_['mean_train_score'][2],
      model.cv_results_['mean_test_score'][2],model.cv_results_['rank_test_score'][2])
print('best_estimator_:',model.best_estimator_)
print('best_params_:',model.best_params_)
print('best_params_:', model.cv_results_['params'][model.best_index_])
print('best_score_:',model.best_score_)
print('scorer_:',model.scorer_)
print('n_splits_:',model.n_splits_)
#%%
