#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : December_08_AdaBoost.py
@Author : chenbei
@Date : 2021-12-23 8:03
@Email ：chenbei_electric@163.com
@Address : Beijing Jiaotong University
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
import matplotlib.pyplot as plt
import numpy as np
import torch
import torchvision
import torchvision.transforms as ttf
#%% <1> 使用skearn实现,数据集使用torch准备
root = r"C:\Users\chenb\.torch" # 请修改为自己的存储路径
# 用于对图片数据预处理(转为张量、调整通道、裁剪、翻转、旋转、调整尺寸、标准化等)
# 转为张量需要说明的如果自行转换numpy数据,其类型为np.uint8时才能转换为torch.float32
# 调整通道需要说明的是不同于opencv/tensorflow,pytorch图像的通道数在前,即不是HWC格式而是CHW格式
# Compose用于组合各种变换,传入的是列表,且使用transform时必须是PIL的图像或者numpy的ndarray
# 注意：转为张量的操作ToTensor()最好放在最后,因为输入是张量时有些变换操作是不支持的
transform = ttf.Compose([ttf.Resize((28,28)),ttf.RandomHorizontalFlip(p=0.5),ttf.ToTensor()])
# 已下载过数据download=False,从训练子集划分训练数据的选项train=True
train_data = torchvision.datasets.FashionMNIST(root=root,train=True,download=False,transform=transform)
test_data = torchvision.datasets.FashionMNIST(root=root,train=False,download=False,transform=transform)
def process(data):
    X,y = data.data/255.,data.targets.numpy()
    X = torch.reshape(X,(-1,X.shape[1]*X.shape[2])).numpy()
    return X,y
X_train,y_train = process(train_data)
X_test,y_test = process(test_data)
from sklearn.ensemble import AdaBoostClassifier
model = AdaBoostClassifier(n_estimators=100,random_state=10)
model.fit(X_train,y_train)
print(f"test score = {model.score(X_test,y_test)}") # test score = 0.5618
#%% <2> 调参
# <2.1> 改变学习率
def plot_acu(x,y,title):
    plt.plot(x,y)
    plt.xlabel(title)
    plt.ylabel("acu")
    plt.title(f"acu curve with {title}")
    plt.show()
acu = []
lrs = [0.1,0.5,0.8,1,1.5]
for lr in lrs:
    clf = AdaBoostClassifier(n_estimators=100,learning_rate=lr,random_state=10)
    clf.fit(X_train,y_train)
    acu.append(clf.score(X_test,y_test))
plot_acu(lrs,acu,"lr") # 从结果来看lr=0.5最高
#%% <2.2>改变估计器个数
n_estimators = np.arange(50,140,30)
acu.clear()
for n_estimator in n_estimators:
    clf = AdaBoostClassifier(n_estimators=n_estimator,learning_rate=0.5,random_state=10)
    clf.fit(X_train,y_train)
    acu.append(clf.score(X_test,y_test))
plot_acu(n_estimators,acu,"n_estimator")

