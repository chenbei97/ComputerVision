# -*- coding: utf-8 -*-
# @Time    : 2021/12/11 14:59
# @File    : December_01_LinearR.py
# @Softfare : PyCharm
# @Author  : chenbei
# @Email   : chenbei_electric@163.com
# @Address : Beijing Jiaotong University
import numpy as np
import matplotlib.pyplot as plt
import os
from matplotlib.pylab import mpl
from matplotlib.font_manager import FontProperties
mpl.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
mpl.rcParams['figure.figsize'] = (10.8, 6.8)  # 设置figure_size尺寸
mpl.rcParams['savefig.dpi'] = 400  # 图片像素
mpl.rcParams['figure.dpi'] = 400  # 分辨率
myfont = FontProperties(fname=r"C:\Windows\Fonts\simsun.ttc", size=10.5)
#%%
# (1)一元线性回归
# 对线性数据回归问题很好用
from sklearn.linear_model import LinearRegression
def bubble_sort(X):
    """
    测试程序
    x_sort= np.random.rand(10)
    bubble_sort(x_sort) # 测试bubble_sort
    y_sort = (3 * x_sort + 4+ np.random.randn(10)*0.05).reshape(-1,1)
    print(y_sort)
    """
    assert X.ndim == 1
    for i in reversed(range(X.shape[0]+1)[2:]):# 在区间[0,n-1],[0,n-2],..,[0,1]两两比较
        # print(i) # 冒泡排序 i = 100,99,98,...,2
        for j in range(i-1): # j = 0,1,2,..i-2 = 0,1,2,...,n-2
             if (X[j] > X[j+1]): # 例如当前区间是[0,n-1],则从X[0]和X[1]两两比较直到X[n-2]和X[n-1]
                 X[j],X[j+1] = X[j+1],X[j] # 如果前者大于后者就交换,比较到最后最大值放在i-1的位置也就是j+1,最大值在X[i-1]上
             # 否则进入下一轮小区间比较 依次得到[0,n-2]的最大值在X[n-2],[0,n-3]的最大值在X[n-3]..
        # 循环结束 得到升序结果
    # 验证是否升序排列
    for i in range(X.shape[0])[1:]:
        assert X[i-1] <= X[i]
    return X
def generate_train_test_data(k,b,n,noise_coeff=(0.05,0.1)):
    def generate_data(seed,noise_coeff):
        np.random.seed(seed)
        X = np.random.rand(n)
        X = bubble_sort(X) # 排序前不要reshape,否则assert X.ndims == 1报错
        # 噪声的影响 y =kx+b+noise
        y = (k * X + b + np.random.randn(n)*noise_coeff) # 排序后也不要reshape否则y的结果是n*n对的矩阵
        # print(y.shape),最后进行reshape,只是为了符合model.fit的数据格式
        return X.reshape(-1,1) , y.reshape(-1,1)
    X_train , y_train = generate_data(0,noise_coeff[0])
    X_test, y_test = generate_data(25,noise_coeff[1])
    return  X_train,y_train,X_test,y_test

num_points = 100
k = 3
b =4
X_train , y_train , X_test , y_test = generate_train_test_data(k,b,num_points,(0.05,1))
model = LinearRegression()
model.fit(X_train,y_train)
print(f"Fitting equation => {model.coef_[0]} * x + {model.intercept_}")
score = model.score(X_test,y_test)
print(f"score = {score}")

# 绘制拟合线
plt.figure(dpi=600,figsize=(7.9,3.8))
x_linespace = np.linspace(0,np.max(X_train),num_points)
y_linespace = k * x_linespace + b
plt.plot(x_linespace,y_linespace,"g-",label="fit",linewidth=2)

plt.scatter(X_train,y_train,c="red",label="train")
plt.scatter(X_test,y_test,c="blue",label="test")
plt.scatter(X_test,model.predict(X_test),c="c",label="pred")
font = {'family': 'simsun',
         'style': 'normal',
         'weight': 'normal',
        'color':  'darkred',
        'size': 16,}
plt.text(x_linespace[num_points//10],y_linespace[num_points-10],"test score = "+str(score),fontdict=font)
plt.legend(loc="best")
plt.show()
#%%
# (2) 对于波士顿房价数据单一的线性拟合效果就差了很多
from sklearn.datasets import load_boston
data = load_boston()
X ,y = load_boston(return_X_y=True)
fig = plt.figure()
def create_and_fit_model(X,y,idx,show=True):
    # idx为 data的特征名字的序号 例如idx=0对应CRIM
    model = LinearRegression()
    model.fit(X.reshape(-1,1),y)
    print(f"Fitting equation => {model.coef_[0]} * x + {model.intercept_}")
    x_linespace = np.linspace(0,np.max(X),len(X))
    y_linespace = model.coef_[0] * x_linespace + model.intercept_
    if show:
        ax = fig.add_subplot(3,3,idx+1)
        ax.scatter(X.reshape(-1,1),y,c="blue",label="scatter")
        ax.plot(x_linespace,y_linespace,"r-",label="fit")
        ax.set_ylabel("house prices")
        ax.set_xlabel(data["feature_names"][idx])
        ax.legend("best")
        ax.set_title(data["feature_names"][idx]+" with house_prices chart")

for i in range(9) :
      create_and_fit_model(X[:,i],y,i)
fig.show()
#%% (3)引入多项式回归来更好对特征和房价进行拟合
# 首先计算单变量x的拟合多项式方程y=c0+c1x+c2x^2+...cmx^m的系数，这个方程的最高幂数为m
# 然后将其转化为幂数最高为1的多变量拟合方程 y=c0+c1x1+c2x2+...cmxm，也就是将x^m作为整体看成新的变量即可
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import PolynomialFeatures
from sklearn.model_selection import cross_val_score
data = load_boston() # 函数内部使用了这个全局变量data,所以放在前边
X ,y = load_boston(return_X_y=True)
def create_model(degree):
    poly_features = PolynomialFeatures(degree,include_bias=False)#include_bias指的是多项式会自动包含1，设为False就没这个1
    linear_regression = LinearRegression()
    # 管道串联模型，要求输入是列表且列表元素是元组，分别是自定义的步骤名称和串联的模型实例
    pipline = Pipeline([("PolyFea",poly_features),("LinearR",linear_regression)])
    return pipline
def maxminium(X):
    assert X.ndim == 1
    maxval, minval = np.max(X), np.min(X)
    X = [(x-minval)/(maxval-minval) for x in X]
    return np.array(X)
def spilit_train_test(X,y,train_size=0.7):
    np.random.seed(25)
    state = np.random.get_state()
    np.random.shuffle(X)
    np.random.set_state(state) # 相同规律打乱数据
    np.random.shuffle(y)
    # 归一化处理
    X_train , X_test = X[:(int)(len(X)*train_size)],X[(int)(len(X)*train_size):]
    y_train, y_test = y[:(int)(len(y)*train_size)],y[(int)(len(y)*train_size):]
    X_train ,X_test,y_train,y_test= maxminium(X_train),maxminium(X_test),maxminium(y_train),maxminium(y_test)
    return X_train.reshape(-1,1),y_train.reshape(-1,1),X_test.reshape(-1,1),y_test.reshape(-1,1)
def fit_model(X,y,featue_idx,degree=int or list,plot=True,train_size=0.7,cv=10):
    X_train, y_train, X_test, y_test = spilit_train_test(X, y, train_size)

    # 打印拟合的方程形式
    def print_fitting_line_score_mse(model,degree_idx=0):
        fitting_coefs = model.named_steps["LinearR"].coef_[0]
        if degree_idx == 0: # 默认传入的参数degree只有1个值
            message = "Fitting equation"
        else:
            message = "Fitting equation" + str(degree_idx+1)
        message += " => y = " + str(np.round(fitting_coefs[0]))+" + "
        for i in range(len(fitting_coefs))[1:]:
            message += str(np.round(fitting_coefs[i],5))+" * "+ "x"+str(i) + " + "
        print(message[0:-2])
        # 测试集的拟合得分，训练集的交叉验证得分和交叉验证均方根误差
        test_score = model.score(X_test,y_test)
        # scoring的选项可以 from sklearn.metrics import SCORERS查找
        cv_mse = cross_val_score(model, X_train, y_train, cv=cv, scoring="neg_mean_squared_error")
        print(f"test_score = {test_score} train_cv_mse = {np.mean(cv_mse)}")

    def plot_result(model,degree,onefig=True,oneaxe=True,fig=None,axes=None):
        if oneaxe and onefig: # 说明fig×1,axe×1只对一组固定的X,y,degree参数进行测试
            # 绘制预测的测试点和实际的测试点
            plt.figure(figsize=(7.9,3.8),dpi=600)
            plt.scatter(X_test, model.predict(X_test), c="r",marker="x",s=60,label="test_predict")
            plt.scatter(X_test, y_test,edgecolors="b",c="b",marker="o",s=60, label="test_true")
            # 绘制拟合线,已经归一化过,直接0-1选取坐标即可
            x_linespace = np.linspace(0,1,500).reshape(-1,1)
            y_linespace = model.predict(x_linespace)
            plt.plot(x_linespace,y_linespace,"g-*",label="fitting line",linewidth=0.2,alpha=0.3)
            plt.xlabel(data["feature_names"][featue_idx])
            plt.ylabel("prices")
            plt.legend(loc="best")
            plt.title(f"degree = {degree[0]} feature = {data['feature_names'][featue_idx]}")
            plt.show()
        elif onefig and (not oneaxe) : # 一组X,y,多个degree参数进行测试 画布只有1个,轴数支持小于4个
            if fig is None or axes is None:
                raise ValueError("when len(degree) >=2 , fig、axes should not be None!")
            assert (fig is not None) and (axes is not None)
            axes = axes.flatten() # 不要使用axes.flatten() 要用axes=axes.flatten()接收
            for i in range(len(degree)):
                # 绘制拟合线,已经归一化过,直接0-1选取坐标即可
                x_linespace = np.linspace(0, 1, 500).reshape(-1, 1)
                y_linespace = model[i].predict(x_linespace)
                axes[i].plot(x_linespace, y_linespace, "g-*", label="fitting line", linewidth=0.2, alpha=0.3)

                # 绘制预测的测试点和实际的测试点
                axes[i].scatter(X_test, model[i].predict(X_test), c="r",marker="x",s=60,label="test_predict")
                axes[i].scatter(X_test, y_test,edgecolors="b",c="b",marker="o",s=60, label="test_true")

                axes[i].set_ylabel("house prices")
                axes[i].set_xlabel(data["feature_names"][featue_idx])
                axes[i].legend("best")
                axes[i].set_title(data["feature_names"][featue_idx] + f" with house_prices chart  degree=[{degree[i]}]")
            fig.show()
    if isinstance(degree,int): #传入的只是1个数转换为1个元素的列表
        degree = [degree]
    if len(degree) == 1 :
        model = create_model(degree[0])
        model.fit(X_train, y_train)
        print_fitting_line_score_mse(model,0)
        if plot:
            # 一组固定的X, y, degree参数 无需传入画布和轴参数
            plot_result(model,degree,True,True) # 1个画布1个轴
        return model # 1组X,y，1个固定参数degree返回1个模型
    else: #  一组固定的X,y参数,但是degree比较多个,degree最多取4个=>坐标轴4个，画布1个
        assert len(degree) <= 4  # 1个画布多个轴但是要<=4
        if (len(degree) == 2):
            fig, axes = plt.subplots(1,2)
        elif (len(degree) == 3):
            fig, axes = plt.subplots(1, 3)
        elif (len(degree) == 4):
            fig, axes = plt.subplots(2, 2)
        else:
            raise ValueError("param degree has up to 4 parameters!")
        models = []
        for i in range(len(degree)):
            model = create_model(degree[i])
            model.fit(X_train, y_train)
            print_fitting_line_score_mse(model, i)
            models.append(model) # 1组X,y，多个固定参数degree返回模型列表
        if plot:
            plot_result(models, degree, True, False, fig, axes)
        return models
# (3.1) 一组固定的X,y,degree参数 无需传入画布和轴参数
feature_idx = 0 # 想要和房价作多项式回归的特征列索引号,506×13,idx取 0-12均可
degree = 5 # [5]也可以
model = fit_model(X[:,feature_idx],y,feature_idx,degree,True,0.7,10)
# (3.2) 一组固定的X,y参数,但是degree比较多个,degree最多取4个=>坐标轴4个，画布1个
feature_idx = 10 # 想要和房价作多项式回归的特征列索引号,506×13,idx取 0-12均可
degrees = [3,5,7,11]
models = fit_model(X[:,feature_idx],y,feature_idx,degrees)
# (3.3)多组X,y参数
for feature_idx in [0,2,4,6,8]:
    _ = fit_model(X[:,feature_idx],y,feature_idx,degrees,True,0.92)
# 从以上单变量线性回归和多变量的多项式回归可以看出，拟合效果其实不好，所以应当考虑更好的方法如逻辑回归、支持向量机等等


