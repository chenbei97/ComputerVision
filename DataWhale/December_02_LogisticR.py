#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : December_02_LogisticR.py
@Author : chenbei
@Date : 2021-12-13 9:36
@Email ：chenbei_electric@163.com
'''
from matplotlib.pylab import mpl
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns
import os
mpl.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
mpl.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
mpl.rcParams['savefig.dpi'] = 600  # 图片像素
mpl.rcParams['figure.dpi'] = 600  # 分辨率
from sklearn.datasets import  make_moons
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import confusion_matrix, accuracy_score, classification_report
#%% (1)sklearn实现
# (1.1)导入数据
def generate_data(train_size = 0.7,n_samples=1000):
    data = make_moons(n_samples=n_samples,shuffle=True,noise=0.5,random_state=10)
    X ,y = data[0],data[1]
    X_train,X_test,y_train,y_test = train_test_split(X,y,shuffle=True,random_state=15,train_size=train_size)
    return X_train, X_test, y_train, y_test
def compare_param(train_size=0.7,solver="lbfgs",idx=0):
    X_train,X_test,y_train,y_test = generate_data(train_size=train_size)
    LR = LogisticRegression(solver=solver)
    LR.fit(X_train,y_train)
    test_score = LR.score(X_test,y_test) # 可以看出0.7的训练集比例测试集评估得分0.78
    acu = accuracy_score(y_test,LR.predict(X_test))
    assert test_score == acu  # score用的默认方法就是准确率
    plt.figure(dpi=600,figsize=(5,5))
    cm = confusion_matrix(y_test,LR.predict(X_test))
    cm = pd.DataFrame(cm)
    sns.set_style("whitegrid") # 默认白色背景
    sns.set(font_scale=1.2) # 字体
    sns.heatmap(cm,annot=True,annot_kws={"size":16},fmt="d",cbar=True) # 单元格写入数值和绘制颜色条
    plt.xlabel("y_true")
    plt.ylabel("y_pred")
    if idx == 0 :
        plt.title("train_size = {:.2f}".format(train_size))
    else:
        plt.title("solver = {:s}".format(solver))
    plt.show()
    print(f"train_size = {train_size},solver = {solver}\n",classification_report(y_test,LR.predict(X_test)))
    return acu
# (1.2)比较不同测试集比例对测试得分的影响
for train_size in [0.7,0.8,0.9,0.95]:
    # 可以看出过高的训练集比例过拟合得分反而下降
    print("test_score = %.3f" %(compare_param(train_size))) # 0.78,0.79,0.84,0.78
# (1.3)其他可调参数可以调整LogisticRegression的参数，例如迭代次数max_iter，优化器solver
# 这里以优化器为例说明，以上可以知道train_size=0.9最高，那么在这个参数下继续比较优化器的选择
solvers = ["lbfgs","newton-cg","liblinear","sag"] # solver : {'newton-cg', 'lbfgs', 'liblinear', 'sag', 'saga'}
for solver in solvers:
    # 很遗憾从结果来看没有任何提升 (滑稽)
    print("test_score = %.3f" % (compare_param(train_size=0.9,solver=solver,idx=1)))
#%% (2)numpy自定义实现
class myLogisticR():
    def __init__(self,X,y,train_size=0.7,lr=0.1,max_iter=10000,eps=1e-8,norm=True,
                 random_state=0,init_method="gauss",mean=None,std=None,a=None,b=None):
        """
        :param X: [Array]要求是样本数×特征数的矩阵格式,如本例使用的数据X,y为[1000,2]和(1000,)
        :param y: [Array]要求是一维向量，长度为样本数
        :param train_size: 训练集比例，默认0.7
        :param lr: 学习率，默认0.1
        :param max_iter: 最大迭代次数，默认10000，满足eps条件就会提前终止迭代
        :param eps: 最小容许误差，默认1e-8，表示更新梯度前后输入与输出的损失loss变化＜eps时停止迭代
        :param norm: 是否对数据归一化，默认为True
        :param random_state: 随机种子，保证结果复现
        :param init_method: 初始化权重weight的方法，{"uniform","gauss"},均匀初始化或者高斯初始化
        :param mean: init_method = "gauss"时必须给定均值
        :param std: init_method = "gauss"时必须给定方差
        :param a: init_method = "uniform"时必须给定上界a
        :param b: init_method = "uniform"时必须给定下界b
        :param history：用于记录训练过程时每个周期的损失和得分
        """
        self.X = X
        self.y = y
        self.lr = lr
        self.max_iter = max_iter
        self.train_size = train_size
        self.random_state = random_state
        self.eps = eps
        self.init_method = init_method
        self.history = [[],[]]
        if self.init_method == "gauss":
            if mean is None or std is None :
                raise ValueError("if init_method use 'gauss' , param 'mean' and 'std' must be give！")
            self.mean = mean
            self.std = std
        elif self.init_method == "uniform":
            if a is None or b is None:
                raise ValueError("if init_method use 'uniform' , param 'a' and 'b' must be give！")
            self.a = a
            self.b = b
        else:
            raise ValueError("init_method only support 'gauss' or 'uniform'!")

    @staticmethod
    def sigmoid(x):
        return 1.0 / (1 + np.exp(-x))

    @staticmethod
    def normalize(X):
        assert X.ndim == 1
        maxval, minval = np.max(X), np.min(X)
        X = [(x - minval) / (maxval - minval) for x in X]
        return np.array(X)

    @classmethod
    def generate_data(self,X,y,train_size=0.7,random_state=0,norm=True):
        X_train, X_test, y_train, y_test = train_test_split(X, y,shuffle=True,random_state=random_state, train_size=train_size)
        if norm :
            for i in range(X_train.shape[1]):
                X_train[:,i] = self.normalize(X_train[:,i])# 每列进行归一化,1列对应多个行样本
            for i in range(X_test.shape[1]):
                X_test[:, i] = self.normalize(X_test[:, i])  # 每列进行归一化,1列对应多个行样本
        return X_train, X_test, y_train, y_test

    def init_weight_bias(self):
        self.bias = np.ones((self.X_train.shape[0], 1))  # 偏置的长度和样本长度一致 = 700
        # y = b+w1x1+w2x2+..+wnxn = bx0+w1x1+w2x2+..+wnxn=xb@w (其中x0这条列向量的元素都必须是0,x00,x01,..x0n=0)
        self.Xb_train = np.hstack((self.bias.reshape(-1, 1), self.X_train))  # x@w+b=>xb@w,b就是那个系数a0
        # print(self.Xb_train.shape) # (700, 3) 把bias拉直为列向量拼接在X_train的前边
        np.random.seed(self.random_state)  # 保证每次结果能够复现
        self.weight = np.zeros(self.Xb_train.shape[1],) # 默认0初始化
        if self.init_method == "gauss" : # 高斯分布初始化
            self.weight = np.random.normal(self.mean, self.std, self.Xb_train.shape[1]) # 权重的长度应和xb的维度(列数)一致,即3
        elif self.init_method == "uniform" :# 均匀分布初始化
            self.weight = np.random.uniform(self.a, self.b, self.Xb_train.shape[1])

    def loss(self):
        # 计算当前weight时的损失 w为列向量
        # 首先计算前向输出 : 当前的拟合参数输出700个值
        self.output = self.forward(self.Xb_train)  # 前向输出 (700,3)*(3,)=(700,) 每个样本都计算得到对应输出
        # proba = sigmoid(Xb*W)-->(m,n)*(m,)-->(n,)
        proba = self.sigmoid(self.output)  # 将预测的结果转为0-1之间 1/(1+exp(-output))
        try:
            # self.y是和proba等长度的列向量 700
            loss = self.y_train * np.log(proba) + (1 - self.y_train) * np.log(1 - proba) # 交叉熵损失的定义
            return -np.sum(loss) / len(self.y_train)  # 样本的平均损失
        except:
            return float('inf')  # 梯度过大时返回无穷大

    def dw(self):
        # 计算损失函数对weight的导数 依据结论导数表达式为
        # 1/m * Σ(sigmoid(Xb*W)-y).*Xb 或 1/m * ΣXb.T.*(sigmoid(Xb*W)-y)
        # ((800,)-(800,))*(800,3)-->(3,) dw的长度应当也是3
        # 列向量和Xb的每个列相乘得到1个数，所以最终只有3个数
        return self.Xb_train.T.dot(self.sigmoid(self.Xb_train.dot(self.weight)) - self.y_train) / len(self.y_train)

    def gradient(self):
        for iter in range(self.max_iter):  # 每代循环
            loss1 = self.loss()  # 计算当前weight的损失
            y_pred_epoch = np.array( self.output> 0.5, dtype='int')
            self.history[0].append(self.score(y_true=self.y_train,y_pred=y_pred_epoch))# 每次迭代的得分
            self.history[1].append(loss1)# 每次迭代的损失
            dw = self.dw() # 计算当前weight时的梯度
            self.weight = self.weight - self.lr * dw # 更新的weight
            loss2 = self.loss()  # 计算更新weight后得到的损失
            if (abs(loss1 - loss2) < self.eps): # 满足误差要求就停止更新weight
                break

        # 梯度下降结束后的最后一步输出self.out是长度700的列向量,将其元素根据与0.5的关系判定为0或1
        y_pred = np.array( self.output> 0.5, dtype='int') # np.array用于bool=>int
        print("train score = ",self.score(y_true=self.y_train,y_pred=y_pred))

    def fit(self):
        # 1)生成训练、测试数据
        self.X_train, self.X_test, self.y_train, self.y_test = self.generate_data(X, y, self.train_size,self.random_state,self.norm)
        # 2)初始化weight、bias以及bias和X_train拼接后的Xb_train
        self.init_weight_bias()
        # print(self.weight.shape,self.bias.shape,self.Xb_train.shape) # (3,) (700, 1) (700, 3)
        assert self.Xb_train.shape[1] == len(self.weight) # (700, 3)[1] = len((3,))
        # 3)执行梯度下降
        self.gradient()

    def forward(self,Xb):
        output = Xb.dot(self.weight)
        return output

    def score(self,y_true,y_pred):
        return np.sum(y_true == y_pred) / len(y_pred)

    def predict(self):
        Xb = np.hstack((np.ones((self.X_test.shape[0], 1)), self.X_test)) # 对测试集也是先拼接
        output = self.forward(Xb)
        y_pred = np.array(output > 0.5, dtype='int')
        print("test score = ",self.score(y_pred,self.y_test))
    def plot_loss_score(self):
        plt.figure(dpi=600,figsize=(7.9,3.8))
        plt.plot(np.arange(0,self.max_iter,1),self.history[0],"g-o",label="score")
        plt.plot(np.arange(0, self.max_iter, 1), self.history[1], "b-*", label="loss")
        plt.xlabel("epoch")
        plt.ylabel("score/loss")
        plt.legend(loc="upper right")
        plt.title("score_loss curve")
        plt.show()
# (2.1)任选一组数据测试
n_samples = 1000
data = make_moons(n_samples=n_samples,shuffle=True,noise=0.5,random_state=10)
X ,y = data[0],data[1]
LR = myLogisticR(X,y,train_size=0.7,init_method="gauss",lr=0.1,max_iter=10000,mean=0,std=1)
# X_train, X_test, y_train, y_test = LR.generate_data(X,y) # 测试类方法是否能够使用
LR.fit() # train score =  0.7871428571428571
LR.predict() # test score =  0.82
LR.plot_loss_score()
#%%
# (2.2)调参：train_size
for train_size in [0.5,0.6,0.7,0.8,0.85,0.9,0.95]:
    LR = myLogisticR(X,y,train_size=train_size,mean=0,std=1)
    LR.fit()
    LR.predict()
# train score =  0.784 test score =  0.814 => 测试训练集比例0.5时的得分
# train score =  0.7883333333333333  test score =  0.8 => 准确率下降,猜测训练集占比不够,因为0.7时提升
# train score =  0.7871428571428571 test score =  0.82 => 准确率提升
# train score =  0.7875  test score =  0.84 => 准确率下降，过拟合原因
# train score =  0.7894117647058824 test score =  0.8333333333333334 => 准确率继续下降，过拟合原因
# train score =  0.7911111111111111 test score =  0.81 => 准确率继续下降，过拟合原因
# train score =  0.791578947368421 test score =  0.84 => 准确率提升只是因为测试集的数量过少导致

#（2.3）调参：init_method = uniform
for train_size in [0.5,0.6,0.7,0.8,0.85,0.9,0.95]:
    LR = myLogisticR(X,y,train_size=train_size,a=0,b=1,init_method="uniform")
    LR.fit()
    LR.predict()
# 从结果来看权重选择均匀初始化还是高斯初始化没有区别,完全一样
#（2.4）调参：max_iter
for epoch in [3000,5000,10000,15000,18000,20000]:
    LR = myLogisticR(X,y,train_size=0.7,a=0,b=1,init_method="uniform",max_iter=epoch)
    LR.fit()
    LR.predict()
# 从结果来看大致超过迭代次数15000就不会再有提升了
# train score =  0.7771428571428571 test score =  0.8133333333333334
# train score =  0.7814285714285715 test score =  0.8166666666666667
# train score =  0.7871428571428571 test score =  0.8166666666666667
# train score =  0.7885714285714286 test score =  0.82
# train score =  0.7885714285714286 test score =  0.82
# train score =  0.7885714285714286 test score =  0.82
#（2.5）调参：lr
for lr in [1.0,0.8,0.5,0.1,0.05,0.01,0.005,0.001,0.0001]:
    LR = myLogisticR(X,y,train_size=0.7,a=0,b=1,init_method="uniform",max_iter=15000,lr=lr)
    LR.fit()
    # LR.predict()
# 从结果来看高于0.1再大也不会提升,低于0.1反而变差
# max_iter和lr应当是动态的，lr很小要求max_iter大才可
# 所以正确的结论是在最大迭代次数为15000的时候lr=0.1时是最高的
# train score =  0.7885714285714286
# train score =  0.7885714285714286
# train score =  0.7885714285714286
# train score =  0.7885714285714286
# train score =  0.7857142857142857
# train score =  0.7542857142857143
# train score =  0.7185714285714285
# train score =  0.5071428571428571
# train score =  0.5142857142857142












