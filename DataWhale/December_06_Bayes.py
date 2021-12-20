#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : December_06_Bayes.py
@Author : chenbei
@Date : 2021-12-20 7:54
@Email ：chenbei_electric@163.com
'''
from matplotlib.pylab import mpl
mpl.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
mpl.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
mpl.rcParams['savefig.dpi'] = 600  # 图片像素
mpl.rcParams['figure.dpi'] = 600  # 分辨率
"""
贝叶斯的理论基础：
    设某独立事件A发生的概率为P(A),独立事件B发生的概率为P(B),在B的条件下A发生的概率为P(A|B)
    A在B的条件发生的概率实际上就等于A和B都发生的概率对只有B发生的概率的商,
        即P(A|B)=P(AB)/P(B),那么有P(AB)=P(A|B)P(B)=P(B/A)P(A) ....①
        故P(A/B)=P(B/A)P(A)/P(B) ....②
        由①可知P(A1A2A3)=P(A3|A1A2)P(A1A2)=P(A3|A1A2)P(A2|A1)P(A1)....③
    推广多个独立事件同时发生的概率为
        P(A1A2A3..An)=P(An/A1A2A3..An-1)*P(An-1/A1A2..An-2)*...*P(A2/A1)P(A1) ....④
    ※※※④称为<概率乘积公式>,表示多个独立事件同时发生的概率,需要记住！
    完备事件：
        一个样本空间S可以由多个独立事件B1,B2,..,Bn组成,事件两两互斥,那么有
        B1+B2+...+Bn = S ....⑤
        A = AS = A(B1∪B2∪..∪Bn) = AB1∪AB2∪...∪ABn ....⑥
        P(A) = P(AB1∪AB2∪...∪ABn) = P(AB1)+P(AB2)+...+P(ABn) 
             = P(B1)P(A|B1)+P(B2)P(A|B2)+...+P(Bn)P(A|Bn) ....⑦
    ※※※⑦称为<全概率公式>,某个独立事件A发生的概率等于A在所有事件的条件概率与对应事件的概率的乘积之和
    即A发生的概率等于所有引起A发生的概率之和,[全概率公式可以理解为每个事件发生的概率和对应的权重的乘积之和]
    ②的含义是事件A在条件B下发生的概率,一般的我们可能更希望得到B已经发生,是B(原因)引起A发生的概率
    由②可以得到
        P(B|A) = P(A|B)P(B)/P(A) ....⑧
    由⑦的P(A)表达式带入⑧可以得到
        P(B|A) = P(B)P(A|B)/ΣP(Bi)P(A|Bi) i=1,2,...,n ....⑨
    故对每个可能的原因B1,B2..,Bi,..,Bn,是某个原因Bi引起A发生的概率为
        P(Bi|A) = P(Bi)P(A|Bi)/ΣP(Bi)P(A|Bi) i=1,2,...,n 
        或
        P(Bi|A) = P(A)P(Bi|A)/ΣP(A)P(Bi|A) i=1,2,...,n ....⑩
        特别的对于B只有互斥的情况,即B与~B(B+~B=S),有
        P(B|A) =  P(B)P(A|B)/[P(B)P(A|B)+P(~B)P(A|~B)]                     
优缺点：
    优点对小规模的数据表现很好，能个处理多分类任务，有稳定的分类效率，适合增量式训练
    尤其是数据量超出内存时，可以分批的增量训练，在sklearn中partial_fit实现了该算法
    缺点在于需要预知先验概率，有时候先验概率是不可知的，取决于不同的假设和数据分布
"""
import matplotlib.pyplot as plt
import numpy as np
from sklearn.datasets import make_moons
n_samples = 1000
noise = 0.5
random_state = 2
train_size = 0.7
data = make_moons(n_samples,noise=noise,random_state=random_state,shuffle=True)
X,y = data
plt.scatter(X[:,0],X[:,1],c=y.ravel())
plt.show()
from sklearn.model_selection import train_test_split, cross_val_score
X_train,X_test,y_train,y_test = train_test_split(X,y,shuffle=True,random_state=random_state,train_size=train_size)
#%% <1>使用sklearn实现并说明相关属性
from sklearn.naive_bayes import GaussianNB
model = GaussianNB()
model.fit(X_train,y_train)
y_pred = model.predict(X_test) # 预测标签
y_pred_propa = model.predict_proba(X_test) # 预测概率
y_pred_log_propa = model.predict_log_proba(X_test) # 预测对数概率
# 1.准确率得分score计算
print("test score = ",np.sum((y_pred == y_test)/len(y_pred))) # test score =  0.8133333333333334
# 2.引入交叉验证对比计算
cv_score = cross_val_score(model,X_train,y_train,cv=10)
print("mean cv_score = ",np.mean(cv_score))
# 3.先验概率priors计算(默认)
print(model.class_prior_) # [0.49428571 0.50571429] 两类事件的先验概率
# 不指定priors时默认使用类的样本数/总的样本数作为先验概率
print(1-np.sum(y_train)/len(y_train),np.sum(y_train)/len(y_train)) # 0.49428571428571433 0.5057142857142857
# 4.拟合数据的类别
print(model.classes_) # [0 1]
# 5.每个类别观察到的样本数量class_count_
print(model.class_count_,np.sum(model.class_count_)) # [346. 354.] 700.0
assert np.sum(model.class_count_) == len(y_train)
# 6.每类特征的方差sigma_,shape为(类别数,特征数)
class_var = model.sigma_ # (2,2)
assert class_var.shape == (len(np.unique(y_train)),X_train.shape[1])
data_zero , data_one = [],[]
# 提取出0,1标签对应的样本数据
for label,samples in zip(y_train,X_train):
    if label == 0 :
        data_zero.append(samples)
    else:
        data_one.append(samples)
# 分别计算两类数据每列特征的方差
data_zero_var = np.var(data_zero,axis=0) # X轴方向/每列计算方差
data_one_var = np.var(data_one,axis=0) # X轴方向/每列计算方差
# 可以观察到data_var 其实就是class_var
data_var = np.vstack((data_zero_var, data_one_var)) # 按行拼接/垂直拼接
# 7.类特征的均值theta_,shape为(类别数,特征数)
class_mean = model.theta_
data_zero_mean = np.mean(data_zero,axis=0)
data_one_mean = np.mean(data_one,axis=0)
# 可以观察到data_mean 其实就是class_mean
data_mean = np.vstack((data_zero_mean, data_one_mean)) # 按行拼接/垂直拼接
# 8.数据量很大不能一次性载入内存时也可以使用分批训练函数partial_fit,返回模型描述
model_description = model.partial_fit(X_train,y_train)
#%% <2>使用numpy实现
class GaussianNaiveBayers():
    def __init__(self,priors=None,eps=1e-6):
        self.priors = priors # 每个类别标签的经验先验概率数组 (n_classes,)
        self.eps = eps # float numerical stability
        self.__isfit = False # if fit,__isfit = True
        self.n_samples = None  # int n_samples
        self.n_features = None # int n_features
        self.n_classes = None # int n_classes
        self.X_train = None # (n_samples,n_features)
        self.y_train = None # (n_samples,)
        self.y_pred = None # (n_samples,)

        self.class_ = None # 类别(n_classes,)
        self.class_count_ = None # 每个类别的样本数(n_classes,)
        self.class_vars_ = None # 每个类别每个特征列(轴0)的方差 (n_classes,n_features)
        self.class_means_ = None # 每个类别每个特征列(轴0)的均值 (n_classes,n_features)

    def fit(self,X_train,y_train):
        self.__isfit = True
        if X_train.ndim == 2 :
            self.n_samples, self.n_features = X_train.shape
        else:
            self.n_samples = len(X_train)
            self.n_features = 1
        self.X_train = X_train
        self.y_train = y_train
        self.class_ = np.unique(y_train)
        self.n_classes = len(self.class_)
        self.class_count_ = np.array([list(self.y_train).count(x) for x in self.class_])# class_count_ = np.array([list(y_train).count(x) for x in np.unique(y_train)])
        self.__init_priors__()
        self.class_means_,self.class_vars_ = self.__cal_mean_var__()

    def __init_priors__(self):
        if self.priors is None :
            self.priors = self.class_count_ / np.sum(self.class_count_)
        else:
            if not self.priors.shape == (len(self.class_),):
                raise ValueError("priors is a vector which shape = (n_classes,)!")
            if not np.sum(self.priors) == 1.0 :
                raise ValueError("The sum of a priori probabilities must be 1！")

    def __cal_mean_var__(self):
        """
        1.利用pandas找到所属类别的数据求均值和方差
        耗时大约0.00796818733215332s
        from time import time
        t1 = time()
        import pandas as pd
        Xy = pd.DataFrame(np.hstack((self.X_train, self.y_train.reshape(-1, 1))),
                          columns=[*range(self.X_train.shape[1]), "label"])
        # 先计算出1个类别以便后边使用concatenate进行拼接
        mean = Xy[Xy["label"] == self.class_[0]].iloc[:, :-1].mean(axis=0).values.reshape(1,-1)
        var = Xy[Xy["label"] == self.class_[0]].iloc[:, :-1].var(axis=0).values.reshape(1,-1)
        for label in self.class_[1:] : # 找到所属类别的数据 iloc[:, :-1]是排除掉label列计算 reshape(1,-1)是防止concatenate报轴越界错误,因为拼接要求是已存在的轴
            mean = np.concatenate((mean,Xy[Xy["label"] == label].iloc[:, :-1].mean(axis=0).values.reshape(1,-1)),axis=0)
            var = np.concatenate((var,Xy[Xy["label"] == label].iloc[:, :-1].var(axis=0).values.reshape(1,-1)),axis=0)
        t2 = time()
        print(t2-t1)
        2.巧妙的利用行索引和类别、标签的关系
        找到某个类别的数据只需要找到为该类别的样本的行索引即可
        那么可以遍历每个类别,类别和标签进行比较,可以得到[True,False,..True]的bool列表,True所在的位置就是行索引你位置
        idx用于行索引赋值,也避免拼接的耗时
        耗时几乎为0,可以看出方法2性能更好
        """
        mean = np.zeros((self.n_classes,self.n_features))
        var = np.zeros_like(mean)
        for idx,label in enumerate(self.class_) :
            X_label = self.X_train[self.y_train == label,:] # self.y_train == label相当于给出了需要索引的位置
            mean[idx,:] = np.mean(X_label,axis=0)
            var[idx,:] = np.var(X_label,axis=0) + self.eps
        return mean,var+self.eps

    def predict(self,X_test):
        # predict_proba的shape为(X_test.shape[0],n_classes),样本数和类别数,每个样本都会给出每个类别的概率
        proba = self.predict_proba(X_test)
        assert proba.shape == (X_test.shape[0],self.n_classes)
        # 轴1上也就是每个样本去找最大概率的位置,也就是列索引,这个索引恰好就是预测类别
        # a = np.random.rand(700,10).argmax(axis=1),0≤a[i]≤9,a[i]=3表示第4个类别
        # 严格来说应该是返回self.class_[proba.argmax(axis=1)],只是因为标签是整数标签且从0开始标的
        # self.class_[]可以传入一个数索引也可以传入一个序列去索引,结果会得到一个这个索引序列对应的索引值
        # y_pred = self.class_[proba.argmax(axis=1)]
        y_pred = proba.argmax(axis=1) # 轴1上也就是每个样本确定最大概率的所处位置
        return y_pred

    def predict_proba(self,X_test):
        if not self.__isfit :
            print("you should fit(X,y) first!")
            return
        proba = np.zeros((X_test.shape[0],self.n_classes)) # 样本数*类别数
        for class_idx in range(self.n_classes):# 每个类别中遍历计算X_test对应类别的可能性
            proba[:,class_idx] = self.__cal_proba__(X_test,class_idx)
        return proba

    def __cal_proba__(self,X_test,class_idx):
        # (n_classes,n_features) and (n_classes,)
        mean = self.class_means_[class_idx] # 得到对应class的均值(1个行向量) (n_features,)
        var = self.class_vars_[class_idx] # 得到对应class的方差(1个行向量) (n_features,)
        prior = self.priors[class_idx] # 得到对应class的先验概率(1个0-1内的浮点数)
        # print(mean,"\n",var,"\n",prior) # X_train得到的特征是行向量

        # 对于指定类别的数据,首先计算每个特征列的方差与2Π乘积的对数和,再乘系数-0.5得到中间值1,这是X_train的特征
        # 其次对传入的X_test进行标准化,去均值平方除方差再乘系数0.5得到中间值2,这是X_test的特征,(X_test.shape[0],)
        # 最后用计算得到的中间值1[1个数]减去这个向量,使用广播机制利用X_train得到的特征减去每个X_test样本
        midval1 = -0.5 * np.sum(np.log(2 * np.pi * var)) # -0.5*Σlog(2Πσ) 1个数
        midval2 = 0.5 * np.sum(((X_test - mean) ** 2) / var, axis=1) # 按轴1计算就是每个样本进行计算,其实就是样本的所有特征标准化后求和
        #print(midval1,midval2.shape) # 1个数和1个向量(X_test.shape[0],)
        log_proba = midval1 - midval2
        return log_proba + np.log(prior)

    def score(self,y_true,y_pred):
        return np.sum(y_true==y_pred)/len(y_pred)

clf = GaussianNaiveBayers()
clf.fit(X_train,y_train)
y_pred = clf.predict(X_test)
y_pred_proba = clf.predict_proba(X_test)
print("test score = ",clf.score(y_pred,y_test)) # test score =  0.8133333333333334 完全一样












