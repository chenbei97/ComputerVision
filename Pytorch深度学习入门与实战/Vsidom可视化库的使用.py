#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : Vsidom可视化库的使用.py
@Author : chenbei
@Date : 2021/10/3 9:39
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
import numpy as np
from tqdm import tqdm
import os
import cv2
import hiddenlayer
import torchviz
import torch
import torch.utils.data as torchdata
import sklearn.datasets as sklearndata
import sklearn.preprocessing as sklearprocess
import sklearn.metrics as sklearnmetric
import tensorboardX
import visdom
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
ss = sklearprocess.StandardScaler(copy=True, with_mean=True, with_std=True)
vis = visdom.Visdom()
batch_size = 16
iris_X , iris_y = sklearndata.load_iris(return_X_y=True)
iris_X = ss.fit_transform(X=iris_X, y=None)
#%%
opts = {"markersize":4,"xlabel":"feature1","ylabel":"feature2","title":"特征散点图"}
vis.scatter(X=iris_X[:,0:2],Y=iris_y+1,win="scatter2d",env="main",opts=opts) # assert Y.min() >= 1
# opts.update({"zlabel":"feature3"})
vis.scatter(X=iris_X[:,0:3],Y=iris_y+1,win="scatter3d",env="main",opts=opts)


#%%
x = torch.linspace(-6,6,100).view((-1,1)) # view的作用 shape=100 --->shape=类似于reshape
sigmoidy = torch.nn.Sigmoid()(x)
reluy = torch.nn.ReLU()(x)
tanhy = torch.nn.Tanh()(x)
ploty = torch.cat((sigmoidy,reluy,tanhy),dim=1) # 默认按列水平拼接,dim=1可以按行垂直拼接
plotx = torch.cat((x,x,x),dim=1)
vis.line(Y=ploty,X=plotx,win="line plot",env="main",
         opts=dict(dash=np.array(["solid","dash","dashdot"]),legend=["sigmod","Relu","Tanh"])) # 支持同时绘制多条折线

#%%
sin = torch.sin(x)
cos = torch.cos(x)
ploty = torch.cat((sin,cos),dim=1) # 默认按列水平拼接,dim=1可以按行垂直拼接
plotx = torch.cat((x,x),dim=1)
vis.stem(Y=ploty,X=plotx,win="stem plot",env="main",opts=dict(title="茎叶图",legend=["sin","cos"]))
#%%
# iris_X 的每列是变量，所以rowvar=False
# 不给出y说明是自己和自己的相关系数，4个列
# 每个列向量依次和自己、其他列进行相关
iris_Corr = torch.from_numpy(np.corrcoef(x=iris_X,y=None,rowvar=False))
vis.heatmap(iris_Corr,win="heatmap",env="main",opts=
            dict(rownames=["x1","x2","x3","x4"],colnames=["x1","x2","x3","x4"]))

#%%
im = cv2.imread(img_dir+"\lena.jpg")/255.
im = torch.from_numpy(im).view((-1,220,220))
im = torch.unsqueeze(im,dim=0) # NCHW模式
vis.image(im[0,...], win="image", env="new env")
vis.text("chenbei", win="text", env="new env")
#%%


