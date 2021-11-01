#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 7.卷积池化层的设计（手推）.py
@Author : chenbei
@Date : 2021/10/11 8:12
'''
from matplotlib.pylab import mpl
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.datasets import load_digits
from sklearn.model_selection import train_test_split, KFold, cross_val_score, cross_validate
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import confusion_matrix, accuracy_score, classification_report
from sklearn.svm import SVC
from sklearn.naive_bayes import GaussianNB
import seaborn as sns
from collections import defaultdict
import os
import operator
from tensorflow.keras.datasets import mnist
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
plt.rcParams['figure.dpi'] = 600  # 分辨率
root = os.path.join(os.getcwd(), "ImageProcessing")
img_dir = os.path.join(root, "images")
(train_x,train_y),(test_x,test_y)=mnist.load_data()
X = train_x[:64]
#%% （1）单通道卷积层
class Conv():
    def __init__(self,filters,kernel_size=(3,3),strides=(1,1),padding='valid'):
        self.filters = filters
        self.kernel_size = kernel_size
        self.strides = strides
        self.padding = padding
        self.weight = np.random.rand(filters,kernel_size[0],kernel_size[1]) # 输出通道

    def forward(self,input):
        if isinstance(self.padding,str):
            if self.padding == 'valid':
                self.input = input
            else:
                if self.padding != 'same':
                    raise ValueError("padding should be tuple or str in ('same','valid')")
                # s=1,(n-f+2p)/s+1 = n ---> f=2p+1
                self.strides = (1,1)
                if self.kernel_size[0]%2 ==0 or self.kernel_size[1]%2 ==0 :
                    raise ValueError("kernel_size should be odd number !")
                p_h,p_w = (self.kernel_size[0] - 1)//2,(self.kernel_size[1] - 1)//2
                input = np.pad(input, pad_width=((0, 0), (p_h, p_h), (p_w, p_w)), mode='constant',
                               constant_values=((None, None), (0, 0), (0, 0)))
                self.input = input
        else:
            p_h,p_w = self.padding
            # 填充时默认上下同时填充高度p_h，左右同时填充宽度p_w
            input = np.pad(input, pad_width=((0,0),(p_h,p_h),(p_w,p_w)), mode='constant',
                           constant_values=((None,None),(0,0),(0,0)))
            self.input = input
        k_x ,k_y = self.kernel_size
        s_x,s_y = self.strides
        # 输出尺寸为[(input.shape-kernel_size)/strides)+1]，如输入28,核3,变为输出26，这里没考虑padding参数,
        output = np.zeros(shape=(input.shape[0],self.filters,(input.shape[1]-k_x)//s_x+1,
                                 (input.shape[-1]-k_y)//s_y+1), dtype=np.float32)
        for n in range(output.shape[0]): # 对每个样本进行循环
            for k in range(self.filters): # 对每个通道进行循环，卷积核与滑窗进行点积，使用np.dot即可
                for i in range(output[0][0].shape[0]): # 卷积核滑动的次数=输出的尺寸
                    for j in range(output[0][0].shape[1]):
                        # 若输出为26,s=1,k=3,那么i取值0,1,...,25,[25,28)并未越界
                        # 考虑步长时,input的x,y从(0-3)->(1,4)变为(0-3)->(2,5)
                        sliding_window = self.input[n,i*s_x:i*s_x+k_x,j*s_y:j*s_y+k_y]
                        # 对相应通道进行计算，只有向量之间点积才为数，必须要展平
                        output[n,k,i,j] = np.dot(self.weight[k].flatten(),sliding_window.flatten())
        return output
conv = Conv(filters=64,kernel_size=(5,5),strides=(1,1),padding='same')
y = conv.forward(X) # （64,64,28,28）
#plt.imshow(y[0][0]),plt.show()
#%% （2）单通道池化层
class Pool():
    def __init__(self,pool_size=(2,2),strides=(2,2),padding=(0,0)):
        self.pool_size = pool_size
        self.strides = strides
        self.padding = padding
    def forward(self,X):
        # 输入形如（64,64,28,28）
        po_h,po_w = self.pool_size
        s_h,s_w = self.strides
        p_h,p_w = self.padding
        # 相比于卷积层，样本数和通道数的维度不填充，shape则上下左右扩充0
        X = np.pad(X,pad_width=((0,0),(0,0),(p_h,p_h),(p_w,p_w)),mode='constant',constant_values=((None,None),(None,None),(0,0),(0,0)))
        # 输出尺寸为[(X.shape-pool_size+2p)/strides)+1] （64,64,14,14）
        out = np.zeros((X.shape[0],X.shape[1],(X.shape[2]-po_h)//s_h+1,(X.shape[-1]-po_w)//s_w+1))
        for n in range(out.shape[0]):
            for c in range(out.shape[1]): # 样本数和通道数不用变
                for i in range(out.shape[2]):
                    for j in range(out.shape[-1]):
                        out[n,c,i,j] = np.max(X[n,c,i*s_h:i*s_h+po_h,j*s_w:j*s_w+po_w])
        return out
pool = Pool()
y_pool = pool.forward(y) # (64,64,14,14)


