#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 3.手动实现KNN算法.py
@Author : chenbei
@Date : 2021/10/11 10:39
'''
from matplotlib.pylab import mpl
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.datasets import load_digits
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
plt.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
#mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
plt.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
plt.rcParams['savefig.dpi'] = 600  # 图片像素
#plt.rcParams['figure.dpi'] = 600  # 分辨率
root = os.path.join(os.getcwd(), "ImageProcessing")
img_dir = os.path.join(root, "images")
#%% （1）手动实现
def knn_fit_predict(k,dist,X_train,y_train,X_test,y_test,num=1000,norm=False):
    assert dist == 'L1' or dist == 'L2' # 使用欧氏距离L2，曼哈顿距离L1
    y_test_pred = []
    X_train  = X_train.reshape(-1,X_train.shape[1]*X_train.shape[2])
    X_test = X_test.reshape(-1,X_test.shape[1]*X_test.shape[2])
    if norm :
        scaler = StandardScaler()
        X_train, X_test = scaler.fit_transform(X_train), scaler.fit_transform(X_test)
    X_test ,y_test = X_test[:num] ,y_test[:num]
    # 对每个测试样本进行循环,与所有训练样本计算距离
    from time import time
    T = time()
    for i in range(X_test.shape[0]): # 输入的样本形状为(样本数,特征数)=(60000,784)
        current = X_test[i] # 当前的测试样本shape=(1,784)
        current_ = np.tile(A=current,reps=(X_train.shape[0],1)) # 轴0填充至60000,轴1不填充,(60000,784),但是是相同的
        if dist == 'L1':
            # L1 距离
            distances = np.sum(np.abs((X_train - current_)),axis=1)
        elif dist == 'L2':
            # L2 距离
            distances = np.sqrt(np.sum(( X_train - current_)**2,axis=1)) # 两个行向量的列元素之间做差平方，所以axis=1,然后开根号，得到列距离矩阵
        else:
            pass
        sorted_dist_index = np.argsort(distances) # 对所有距离升序排序并给出索引即图片序号
        nearest_k_index = sorted_dist_index[:k] # 最近的k个图片的序号
        label_num = defaultdict(int) # 统计标签的数量 key = label,value = num
        for index in nearest_k_index :
            label = y_train[index] # 利用图片的标号找到图片的标签
            # k个图片标签分属不同的类别,根据投票原则需要统计每个类别的数量
            label_num[label] += 1 # 可以避免因没有key值报错,还可以自动计数
        # 字典是无序的，需要排序,使用降序,投票最多的在第1个,返回的是多个元组对象的列表
        sorted_label_num = sorted(label_num.items(),reverse=True,key=operator.itemgetter(1))
        y_test_pred.append(sorted_label_num[0][0]) # 每个测试样本投票数最多的结果的对应标签
        print(i,sorted_label_num[0][0])
    time = time() - T
    score = np.sum(np.array(y_test_pred)==y_test)/len(y_test)
    return np.array(y_test_pred) ,score,time
(train_x,train_y),(test_x,test_y)=mnist.load_data()
# 1）未标准化数据预测
y_test_pred ,score,time = knn_fit_predict(5,"L2",train_x,train_y,test_x,test_y,num=1000,norm=False)
print("score %.5f time %.5f " % (score,time)) # score 0.27700 time 110.83425
#%%
# 2）标准化以后预测
y_test_pred ,score,time = knn_fit_predict(5,"L2",train_x,train_y,test_x,test_y,num=1000,norm=True)
print("score %.5f time %.5f " % (score,time)) # score 0.93500 time 336.69147
#%%
# 为了使用交叉验证方法，需要将函数写为类作为估计器
class Knn():
    def __init__(self,k=3,dist="L2",norm=True):
        self.k = k
        self.dist = dist
        self.norm = norm
    def process(self,data):
        data = data.reshape(-1, data.shape[1] * data.shape[2])
        if self.norm:
            scaler = StandardScaler()
            data = scaler.fit_transform(data)
        return data
    def fit(self,X_train,y_train):
        self.X_train = self.process(X_train)
        self.y_train = y_train
    def predict(self,X_test):
        # 对每个测试样本进行循环,与所有训练样本计算距离
        X_test = self.process(X_test)
        assert self.dist == 'L1' or self.dist == 'L2'  # 使用欧氏距离L2，曼哈顿距离L1
        y_test_pred = []
        from time import time
        T = time()
        for i in range(X_test.shape[0]):  # 输入的样本形状为(样本数,特征数)=(60000,784)
            current = X_test[i]  # 当前的测试样本shape=(1,784)
            current_ = np.tile(A=current, reps=(self.X_train.shape[0], 1))  # 轴0填充至60000,轴1不填充,(60000,784),但是是相同的
            if self.dist == 'L1':
                # L1 距离
                distances = np.sum(np.abs((self.X_train - current_)), axis=1)
            elif self.dist == 'L2':
                # L2 距离
                distances = np.sqrt(np.sum((self.X_train - current_) ** 2, axis=1))  # 两个行向量的列元素之间做差平方，所以axis=1,然后开根号，得到列距离矩阵
            else:
                pass
            sorted_dist_index = np.argsort(distances)  # 对所有距离升序排序并给出索引即图片序号
            nearest_k_index = sorted_dist_index[:self.k]  # 最近的k个图片的序号
            label_num = defaultdict(int)  # 统计标签的数量 key = label,value = num
            for index in nearest_k_index:
                label = self.y_train[index]  # 利用图片的标号找到图片的标签
                # k个图片标签分属不同的类别,根据投票原则需要统计每个类别的数量
                label_num[label] += 1  # 可以避免因没有key值报错,还可以自动计数
            # 字典是无序的，需要排序,使用降序,投票最多的在第1个,返回的是多个元组对象的列表
            sorted_label_num = sorted(label_num.items(), reverse=True, key=operator.itemgetter(1))
            y_test_pred.append(sorted_label_num[0][0])  # 每个测试样本投票数最多的结果的对应标签
            print(f"test sample : {i}")
        time = time() - T
        return np.array(y_test_pred),time
    def score(self,y_pred,y_true):
        score = np.sum(y_pred == y_true) / len(y_true)
        return score
# 3）不使用交叉验证
knn = Knn()
knn.fit(train_x[:5000], train_y[:5000])
pred ,time = knn.predict(test_x[:500])
print(knn.score(y_true=test_y[:500],y_pred=pred),time)
#%%
# 4）使用交叉验证
(train_x,train_y),(test_x,test_y)=mnist.load_data()
train_x,train_y = train_x[:5000], train_y[:5000]
folds = 10
ks = [3,5,8,10,12,15,20]
train_x_folds,train_y_folds = [],[]
indices = np.array_split(np.arange(train_x.shape[0]),indices_or_sections=folds)
assert len(indices) == folds # 索引拆分为10份
for indice in indices:
    train_x_folds.append(train_x[indice])
    train_y_folds.append(train_y[indice])
k_val_acu = {}
for k in ks :
    val_acu = []
    for fold in range(folds):
        print(f"k={k} fold={fold+1}")
        # 第fold折作为验证集,因为是列表所以可以使用+来拼接
        train_x_fold = train_x_folds[0:fold] + train_x_folds[fold+1:] # 长度为9的列表
        train_x_fold = np.concatenate(train_x_fold,axis=0) # 会将列表解包按行拼接
        train_y_fold = train_y_folds[0:fold] + train_y_folds[fold+1:]
        train_y_fold = np.concatenate(train_y_fold, axis=0)
        val_x_fold ,val_y_fold = train_x_folds[fold],train_y_folds[fold]
        knn = Knn(k=k)
        knn.fit(train_x_fold,train_y_fold)
        val_y_pred ,_ = knn.predict(val_x_fold)
        val_acu.append(knn.score(val_y_pred,val_y_fold))
    k_val_acu[k] = val_acu
for key , val_acu in k_val_acu.items():
    for fold , acu in enumerate(val_acu):
        print(f"k = {key} fold = {fold+1} acu = {acu}")
plt.plot(ks,[np.mean(k_val_acu[k]) for k in ks]) # 可以看出k=5最好
plt.show()

#%% （2）使用sklearn实现
# 1）不使用交叉验证
digits = load_digits()
data = digits.data
target = digits.target
train_x,test_x,train_y,test_y = train_test_split(data,target,train_size=0.7,test_size=None,
                                                 random_state=10,shuffle=True,stratify=None)
knn = KNeighborsClassifier()
knn.fit(train_x,train_y)
test_pred = knn.predict(test_x)
print(accuracy_score(test_y,test_pred),knn.score(test_x,test_y))
cm = confusion_matrix(test_y,test_pred)
df_cm = pd.DataFrame(cm,index=digits.target_names,columns=digits.target_names)
sns.heatmap(df_cm,annot=True)
plt.show()
print(classification_report(test_y,test_pred))
#%% 2）使用K折交叉验证
kfold = KFold(n_splits=10,random_state=10,shuffle=True)
scores = cross_val_score(estimator=knn, X=digits.data, y=digits.target,cv=kfold)
print(scores.mean())
#%% 3）同时使用多个估计器比较
svm = SVC(C=1.0,kernel='rbf',degree=3,gamma='scale',class_weight=None,random_state=10)
gb = GaussianNB(priors=None,var_smoothing=1e-9)
estimator = {"KNN":knn,"SVM":svm,"GB":gb}
for key , value in estimator.items():
    kfold = KFold(n_splits=10,random_state=10,shuffle=True)
    scores = cross_val_score(estimator=value,X=digits.data, y=digits.target,cv=kfold)
    print(f"{key} : acu={scores.mean()} std={scores.std()}")
# 交叉验证
cv_results = cross_validate(estimator=knn, X=digits.data, y=digits.target,cv=kfold,
               return_train_score=True,return_estimator=True)
print(cv_results["train_score"])











