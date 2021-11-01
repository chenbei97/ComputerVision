#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 4.线性回归和逻辑回归.py
@Author : chenbei
@Date : 2021/10/12 7:48
'''
from matplotlib.pylab import mpl
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.datasets import load_digits,load_boston,load_iris,make_moons
from sklearn.model_selection import train_test_split,KFold,cross_val_score,cross_validate
from sklearn.neighbors import  KNeighborsClassifier
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import  confusion_matrix ,accuracy_score,classification_report
from sklearn.svm import SVC
from sklearn.naive_bayes import GaussianNB
import seaborn as sns
from collections import defaultdict
import os
import operator
from tensorflow.keras.datasets import  mnist
import torch
import torchvision
import hiddenlayer
import tensorflow as tf
plt.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
plt.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
plt.rcParams['savefig.dpi'] = 600  # 图片像素
# plt.rcParams['figure.dpi'] = 600  # 分辨率
root = os.path.join(os.getcwd(), "ImageProcessing")
img_dir = os.path.join(root, "images")
#%% （0）自构造线性回归
# 【1】 采样数据
data = []
for i in range(1000):
    #  numpy.random.uniform(low,high,size) 从一个均匀分布[low,high)中随机采样，注意定义域是左闭右开
    x = np.random.uniform(-10.,10.)
    # numpy.random.normal(loc=0.0, scale=1.0, size=None) 均值=0 标准差=0.1的 正态分布
    eps = np.random.normal(0.,0.1)
    y = 1.477 * x + 0.089 + eps
    data.append([x,y])
data = np.array(data) # (1000,2)
#%%
# 【2】 计算误差
def calculate_mse(w,b,points):
    #　根据当前迭代的w,b参数对所有点进行计算
    # points为二维数组
    total_mse = 0 # 计算所有点的总方差
    for i in range(len(points)):
        x = points[i , 0]
        y = points[i , 1] # 第2列是输出y
        total_mse = total_mse + ( y - w * x - b) ** 2
    return total_mse / float(len(points)) # 平均方差MSE
# 【3】 借助计算梯度来更新参数
# 误差损失函数 loss = 1/n * { Σ[i=1,n] ( w*x(i)+b - y(i) ) ** 2 } = L(w,b)
# w梯度向量 : 根据 ∂(g^2)/∂w = 2 * g * ∂g/∂w
# 从而  ∂L/∂w = 1/n * { 2 * Σ[i=1,n] ( w*x(i)+b - y(i) ) } * { ∂( w*x(i)+b - y(i) ) / ∂w}
# 最终表达式为 ∂L/∂w = 2/n * { Σ[i=1,n] ( w*x(i)+b - y(i) ) * x(i) }
# 同理 ∂L/∂b = 2/n * { Σ[i=1,n] ( w*x(i)+b - y(i) ) }
def update_parameters(w_current , b_current , points , lr) :
    # 每次更新当前参数时都初始化w,b参数的梯度值为0
    b_gradient = 0
    w_gradient = 0
    n = float(len(points)) # 总样本数
    # 计算loss函数对每个点的w,b梯度 并累计梯度值(公式要求累加梯度,因为损失是累加的)
    for i in range(len(points)) :
        # 找到点坐标
        x = points[i,0]
        y = points[i,1]
        # 计算当前点对w,b的梯度
        b_gradient = b_gradient + 2 / n * ( w_current  * x + b_current - y)
        w_gradient = w_gradient + 2 / n * x * ( w_current * x + b_current - y)
    # 梯度下降算法更新参数
    b_new = b_current - lr * b_gradient
    w_new = w_current - lr * w_gradient
    return [w_new , b_new]
# 【4】 更新梯度
def update_gradient(points , w_start, b_start, lr ,num_iterations):
    # 从w,b的当前的初始值计算 w_start, b_start在初始值定义一般为0
    w = w_start
    b = b_start
    Loss = [] # 存放每次迭代得到的loss
    # 根据指定迭代次数对w,b迭代
    for step in range(num_iterations) :
        # 对第step步的参数w,b计算梯度并执行梯度下降
        w ,b =  update_parameters(w,b,points,lr)
        # 计算当前的MSE误差
        loss = calculate_mse(w,b,points)
        Loss.append(loss)
        if step%100 ==0:
            print(f"迭代次数{step}, MSE误差为{np.round(loss,5)}, 当前参数w={round(w,5)},b={round(b,5)}")
    # 返回最后一次的参数
    return [w,b] ,Loss
# 【5】主训练函数
def main() :
    lr = 0.001 # 学习率
    num_iterations = 5000 # 迭代次数
    w_start = 0.1
    b_start = 0.1
    # 开始更新w,b得到最后一次的结果
    [w,b],loss = update_gradient(points=data,
                            w_start=w_start,b_start=b_start,
                            lr=lr,
                            num_iterations=num_iterations)
    # 计算此时的loss
    plt.plot(np.arange(len(loss)),loss,label="均方差")
    plt.ylabel("MSE")
    plt.xlabel("Iterations")
    plt.legend()
    plt.show()
    print(f'最终损失:{round(loss[-1],5)}, w:{round(w,5)}, b:{round(b,5)}')
main()
#%% （1）一元线性回归
boston = load_boston()
data = boston.data
feature = boston.feature_names
target = boston.target
x_0 = data[:,-1]
y_0 = target
def calculate_slope_intercept(x, y):
    # 计算斜率和截距
    # k = Σ(x_i-x_mean)(y_i-y_mean) / Σ(x_i-x_mean)^2 = k0 / k1
    # b = y_mean - a * x_mean
    x , y = x.reshape(-1, 1),y.reshape(-1, 1)
    x_mean ,y_mean = np.mean(x),np.mean(y)
    k0 = np.sum((x-x_mean)*(y-y_mean))
    k1 = np.sum((x-x_mean)**2)
    k = k0 / k1
    b = y_mean - k * x_mean
    y_pred = k * x + b
    plt.scatter(x,y)
    plt.plot(x,y_pred)
    plt.show()
calculate_slope_intercept(x_0,y_0)
#%% （2）多元线性回归
class MulLinearRegression():
    '''
    y_pred拟合值与输入值满足的关系如下：
    y_pred = a0 + a1x1 + a2x2 + ... + anxn ①
    将方程①写为如下形式，其中x0为全1列向量
    y_pred = a0x0 + a1x1 + a2x2 + ... + anxn ②
    写为矩阵形式 y_pred = [x0,x1,..,xn] * [a0,a1,..,an]^T = X * W
    y_pred的长度就等于输入矩阵的行数或者说样本数

    x1,x2,x3,...xn都是输入向量 ,波士顿房价为 506 * 13 的矩阵
    对本例的波士顿数据集也就是输入(506,13+1)*(14,)---->(506,)
        [ 1  x1(1)  x2(1)  ...  xn(1)]
    X = [ 1  x1(2)  x2(2)  ...  xn(2)]
        [ ...                   ...  ]
        [ 1  x1(n)  x2(n)  ...  xn(n)]

    a = [a0,a1,..an]^T a是拟合系数列向量，也可以认为是权值矩阵W
    对于方程②如果希望找到1个最佳拟合的方程，其系数应当满足③
    方程③可以应用于梯度下降法，当损失函数小于给定值时不再改变

    a = (X^T*X)^(-1) * X^T * y_true = a_ * a__ * a___ ③
    设输入的形状为m*n，((n+1,m)*(m,n+1))^-1 --->(m,m) * (m,n+1)--->(m,n+1) * (m,)-->(n+1,)
    最后一步是m×n的矩阵的每列和(m,)的列向量分别点积
    得到(n+1,)的向量 对应n+1个拟合系数[a0,a1,...an]
    其中a0就是截距系数，剩下的都是斜率系数a1-->an

    损失函数loss
    y_true * np.log(proba) + (1 - y_true) * np.log(1 - proba)
    其中y_ture为与每个样本对应的实际值，∈{0,1}

    评价得分R2：
    R2  = 1 - k0 / k1
    k0 = Σ(y_true-y_pred)**2 / m # 其实就是均方差损失mse
    k1 = Σ(y_mean - y_true)**2 # 偏离程度，其实就是方差var
    故R2得分还可变形为
    R2 = 1 - mse / var

    '''
    def __init__(self):
        self.coef_ = None
        self.intercept_ = None
        self._a = None # 权重+截距
    def fit(self,train_x,train_y):
        # 得到系数a[a0,a1,..,an]用于预测
        assert train_x.shape[0] == train_y.shape[0]
        # 构造输入向量的矩阵 水平拼接1个全1列向量 输入(506,13)转为(506,14)
        X = np.hstack((np.ones((train_x.shape[0],1)),train_x))
        from numpy import linalg
        a_ ,a__ ,a___ = linalg.inv(X.T.dot(X)) , X.T , train_y
        self._a = a_.dot(a__).dot(a___) # (a0,a1,a2,...,an)
        self.intercept = self._a[0] # a0
        self.coef_ = self._a[1:] # a1,a2,..an
    def predict(self,test_x):
        # 首先将输入形式转为矩阵形式
        X = np.hstack((np.ones((test_x.shape[0],1)),test_x))
        return X.dot(self._a)
    def mse(self,y_true,y_pred):
        return np.sum((y_true-y_pred)**2) / len(y_true)
    def score(self,test_x,test_y):
        test_pred = self.predict(test_x)
        R2 = 1 - (self.mse(test_y,test_pred) / np.var(test_y))
        return R2
mlr = MulLinearRegression()
mlr.fit(data,target)
pred = mlr.predict(data[0:60,:])
print(mlr.score(data[0:60,:],target[0:60]))
#%% （3）逻辑回归：二分类
N_SAMPLES = 50000
TEST_SIZE = 0.3
X, y = make_moons(n_samples = N_SAMPLES, noise=0.8, random_state=100)
X_train, X_test, y_train, y_test = train_test_split(X, y,test_size = TEST_SIZE, random_state=34)
class LogisticRegression():
    def __init__(self,lr=0.02,epoch=4e4,eps=1e-8):
        self.coef = None
        self.intercept = None
        self.w = None # 列向量
        self.lr = lr
        self.epoch = epoch
        self.eps = eps
        self.history = [[],[],[]] # epoch,acu,loss
    def sigmoid(self,x):
        y = 1.0 / (1.0 + np.exp(-x))
        return y
    def fit(self,train_x,train_y):
        # train_x(800,2) train_y(800,)∈{0,1}
        assert train_x.shape[0] == train_y.shape[0]
        self.X = train_x
        self.y = train_y
        self.Xb = np.hstack((np.ones((self.X.shape[0], 1)), self.X))  # (800,3)
        self.gradient_descent()
        assert len(self.w) == self.Xb.shape[1]
        self.intercept = self.w[0]
        self.coef = self.w[1:]
    def loss(self,w):
        # 计算当前w时的损失 w为列向量
        # 首先计算前向输出 : 当前的拟合参数输出800个值
        out = self.Xb.dot(w) # 前向输出 (800,3)*(3,)=(800,) 每个样本都计算得到输出
        # proba = sigmoid(Xb*W)-->(m,n)*(m,)-->(n,)
        proba = self.sigmoid(out) # 将预测的结果转为0-1之间 1/(1+exp(-out))
        try:
            # self.y是和proba等长度的列向量
            loss = self.y * np.log(proba) + (1 - self.y) * np.log(1 - proba)
            #print(-np.sum(loss) / len(self.y))
            return -np.sum(loss) / len(self.y) # 样本的平均损失
        except:
            return float('inf')  # 梯度过大时返回无穷大
    def dw(self):
        # 计算损失函数对W的导数 依据结论导数表达式为
        # 1/m * Σ(sigmoid(Xb*W)-y).*Xb 或 1/m * ΣXb.T.*(sigmoid(Xb*W)-y)
        # ((800,)-(800,))*(800,3)-->(3,)
        # 列向量和Xb的每个列相乘得到1个数，所以最终只有3个数
        # A = np.random.rand(800)
        # B = np.random.rand(800, 3)
        # C = A.dot(B)
        # D = B.T.dot(A) C，D结果是一样的
        return self.Xb.T.dot(self.sigmoid(self.Xb.dot(self.w)) - self.y) / len(self.y)
    def gradient_descent(self):
        self.w = np.zeros(self.Xb.shape[1])  # 列向量(3,) 这里相当于二元回归 y=a0x0+a1x1+a2x2，有3个拟合系数
        i_epoch = 0
        while i_epoch < self.epoch:
            #print(f"epoch={i_epoch},w={self.w}")
            dw = self.dw()
            last_w = self.w
            self.w = self.w - self.lr * dw
            i_epoch += 1
            self.out_label = np.array(self.sigmoid(self.Xb.dot(self.w)) > 0.5, dtype='int')
            self.acu = self.score()
            self.cost = self.loss(self.w)
            self.history[0].append(i_epoch)
            self.history[1].append(self.acu)
            self.history[2].append(self.cost)
            if (abs(self.cost - self.loss(last_w)) < self.eps):
                break
    def score(self):
        return np.sum(self.y == self.out_label) / len(self.y)
    def predict_proba(self,X_test):
        Xb = np.hstack((np.ones((X_test.shape[0],1)),X_test))
        return self.sigmoid(Xb.dot(self.w))
    def predict_label(self,X_test):
        proba = self.predict_proba(X_test)
        return np.array(proba>0.5,dtype='int')
    def predict_score(self,X_test,test_y):
        test_pred = self.predict_label(X_test)
        return np.sum(test_y == test_pred) / len(test_y)
lr = LogisticRegression()
lr.fit(X_train, y_train)
print(lr.predict_score(X_test,y_test),lr.score())
plt.plot(lr.history[0],lr.history[1],label='acu')
plt.plot(lr.history[0],lr.history[2],label='loss')
plt.legend()
plt.show()
#%% （4）多分类
# 多分类使用softmax函数
def softmax(x):
    if x.ndim == 2:
        # 传入的是矩阵时 如(4,6)必须修改，否则矩阵的所有元素和为1了
        # 注：对于sigmoid和relu函数没有影响
        # 现在要求x的每列和为1，故找到每列的最大值
        c = np.max(x, axis=1)  # (4,)
        exp_x = np.exp(x.T - c)  # (4,6)-(4,)是不能广播的，需要转置为(6,4)-(4,)-->(6,4),需要后缘维度相同
        return exp_x / np.sum(exp_x, axis=0)  # np.sum(exp_x,axis=0) =(4,) 每列除对应值
    c = np.max(x)
    exp_x = np.exp(x - c)
    return exp_x / np.sum(exp_x)
A = np.random.rand(4,6)
B = softmax(A)






