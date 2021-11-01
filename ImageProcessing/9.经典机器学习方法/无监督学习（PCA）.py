#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 无监督学习（PCA）.py
@Author : chenbei
@Date : 2021/9/18 11:49
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
import numpy as np
import os
from sklearn import  preprocessing ,decomposition,datasets ,cluster,pipeline
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
def plot_im1_im2(im1,im2,title1="original",title2="reconstruction"):
    fig = plt.figure()
    plt.gray()
    ax1 = fig.add_subplot(121)
    ax2 = fig.add_subplot(122)
    ax1.imshow(im1),ax2.imshow(im2)
    ax1.set_title(title1,size=12),ax2.set_title(title2,size=12)
    ax1.set_axis_off(),ax2.set_axis_off()
    fig.show()
#%%（1）PCA的使用
digits = datasets.load_digits()
# 机器学习中一般处理的数据格式为样本数*维数
images = digits.images # 1797 * 8 * 8
x = digits.data # 使用展平的 1797 * 64
y = digits.target # 0,1,2,..8
pca = decomposition.PCA(n_components=2)
x_pca = pca.fit_transform(x) # 1797 * 2
plt.scatter(x_pca[:,0],x_pca[:,1],c=y)
plt.colorbar(ticks=range(10),label='digit value')
plt.show() # 相同数字的在一撮
#%%（2）基于PCA的特征脸
# 特征脸是components_，也就是前components_个主要的成分，不是降维后的
faces = datasets.fetch_olivetti_faces()
x = faces.data # 400 * 4096
y = faces.target # 0,1,2...,39 40个人,每人10张图片
n_components = 64
# 按链接顺序链接的（名称，变换）元组（实现拟合/变换）列表，最后一个对象是估计器，名称可以随意取
pipe = pipeline.Pipeline([('scaler', preprocessing.StandardScaler()), ('pca', decomposition.PCA(n_components=n_components))])
x_pca = pipe.fit_transform(x) # 拟合且转换，转换就是StandardScaler和PCA 400*300
scaler = pipe.named_steps['scaler'] # 可以找到均值、方差，利用reshape即可得到均值人脸和方差人脸
mean_x = np.reshape(scaler.mean_,(64,64))
var_x = np.reshape(scaler.var_,(64,64))
pca = pipe.named_steps['pca'] # 可以找到累积可解释方差占比，每个维度占据的成分信息，可视化一般需要累加
explained_variance_ratio_ = np.cumsum(pca.explained_variance_ratio_)
#%%
# 1）累计方差贡献率
for idx , value in enumerate(explained_variance_ratio_) :
    if value >=0.9 :
        x0 = idx
        y0 = value
        break
plt.plot(explained_variance_ratio_),plt.vlines(x0,ymin=0, ymax=y0,colors='r'),plt.hlines(y=y0, xmin=0, xmax=x0,colors='r')
plt.show()
#%%
# 2）特征脸
# 输入数据格式为样本数*输入维数，输出格式为样本数*n_components
# components_为前向转换矩阵的转置，格式为n_components*输入维数也就是前components_个主要的成分
# 它们相互正交，在图像降维中可以认为是特征脸
# input * components^T = output
pca_components_ = pca.components_ # (64,4096)
pca_components_reshape = np.reshape(pca_components_,(n_components,64,64)) #  (64,64,64)
# 这些特征脸可以叠加,每个人脸都是这些特征脸的线性组合，权重即是output
# 因为 input = output * components , output的每行对应每个样本，每列是每个样本在特征脸上的权重
# 每行是一个样本在64个特征脸的权重
for i in range(x_pca.shape[1]) :
    print(f"第一个样本第{i+1}个特征脸的权重为{np.round(x_pca[0][i],2)}")
#%%
# 3）降维后的图像展示
x_pca_resahpe = np.reshape(x_pca,(400,8,8))
plot_im1_im2(x_pca_resahpe[0],x_pca_resahpe[10])
#%%
# 4）重建图像
x_re = np.reshape(pca.inverse_transform(x_pca),(400,64,64))# 400 * 100 -> 400 * 4096 不过这个图像是标准化后的
x_re= mean_x + x_re * var_x # 广播效应 按第一个维度广播到每个样本
x_re_0 = np.reshape(x_pca[0]@pca_components_ ,(64,64))# inverse_transform的实现机制就是矩阵乘法
x_re_0 = mean_x + x_re_0 * var_x # 注意到x_re_0和x_re[0]是相等的
plot_im1_im2(np.reshape(x,(400,64,64))[0],x_re[0]) # 比对重建的第一个样本
#%%










