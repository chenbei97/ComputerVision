#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 常用脚本函数.py
@Author : chenbei
@Date : 2021/9/19 9:49
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
import numpy as np
import os
import skimage.io, skimage.color, skimage.metrics, skimage.filters, \
    skimage.segmentation, skimage.feature, skimage.transform, skimage.morphology
import sklearn.cluster, sklearn.preprocessing, sklearn.datasets, sklearn.decomposition, \
    sklearn.pipeline, sklearn.neighbors, sklearn.svm, sklearn.model_selection, sklearn.ensemble, sklearn.metrics
import scipy
import sklearn

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
def plot_im1_im2(im1,im2,title1="original",title2="reconstruction",colorbar=False):
    fig = plt.figure()
    ax1 = fig.add_subplot(121)
    ax2 = fig.add_subplot(122)
    map1 = ax1.imshow(im1)
    map2 = ax2.imshow(im2)
    if colorbar :
        fig.colorbar(map1,ax=ax1)
    ax1.set_title(title1,size=12),ax2.set_title(title2,size=12)
    ax1.set_axis_off(),ax2.set_axis_off()
    fig.show()












