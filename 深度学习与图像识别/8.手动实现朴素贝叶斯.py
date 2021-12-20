#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 8.手动实现朴素贝叶斯.py
@Author : chenbei
@Date : 2021-12-20 15:07
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
# 参考实现：https://github.com/chenbei97/numpy-ml/blob/master/numpy_ml/linear_models/naive_bayes.py
import numpy as np
import matplotlib.pyplot as plt
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
class GaussianNBClassifier():
    def __init__(self, eps=1e-6):
        self.labels = None
        self.hyperparameters = {"eps": eps} # 添加到方差中以防止数值错误的值
        self.parameters = {
            "mean": None,  # shape: (K, M)
            "sigma": None,  # shape: (K, M)
            "prior": None,  # shape: (K,) # 每个类别标签的经验先验概率数组
        }
    def fit(self, X, y):
        P = self.parameters
        H = self.hyperparameters

        self.labels = np.unique(y) # 0,1 对标签过滤 使用set也可以去重

        K = len(self.labels) # 2 类别的个数
        N, M = X.shape # 例如X_train为700,2的数据

        P["mean"] = np.zeros((K, M)) # (n_classes,n_features)
        P["sigma"] = np.zeros((K, M))# (n_classes,n_features)
        P["prior"] = np.zeros((K,))# (n_classes,)

        for i, c in enumerate(self.labels): # (i,c)=(0,0),(1,1),遍历每个类别
            X_c = X[y == c, :] # y==c就是找到这个类别的数据,y==c=>[True,False,..,False],
            # y == c会得到每个样本是否属于当前类别c的掩码,True的位置就是属于该类别的数据
            P["mean"][i, :] = np.mean(X_c, axis=0)
            P["sigma"][i, :] = np.var(X_c, axis=0) + H["eps"]
            P["prior"][i] = X_c.shape[0] / N # 不指定时默认使用当前类别的样本数/总样本数作为该类别的先验概率
        return self
    def predict(self, X):
        return self.labels[self._log_posterior(X).argmax(axis=1)]
    def _log_posterior(self, X):
        K = len(self.labels)
        log_posterior = np.zeros((X.shape[0], K))
        for i in range(K): # 每个类别遍历,在_log_class_posterior中计算X_test对应类别的可能性
            log_posterior[:, i] = self._log_class_posterior(X, i)
        return log_posterior
    def _log_class_posterior(self, X, class_idx):
        P = self.parameters
        mu = P["mean"][class_idx]
        prior = P["prior"][class_idx]
        sigsq = P["sigma"][class_idx]
        # log likelihood = log X | N(mu, sigsq)
        log_likelihood = -0.5 * np.sum(np.log(2 * np.pi * sigsq))
        log_likelihood -= 0.5 * np.sum(((X - mu) ** 2) / sigsq, axis=1)
        return log_likelihood + np.log(prior)
clf = GaussianNBClassifier()
clf.fit(X_train,y_train)
y_pred = clf.predict(X_test)
print("test score = ",np.sum(y_pred==y_test)/len(y_pred))












