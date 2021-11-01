#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : ImageProcessing（matplotlib）.py
@Author : chenbei
@Date : 2021/8/31 11:25
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
from matplotlib.font_manager import FontProperties
import numpy as np
import pandas as pd
import tensorflow as tf
import os
from tensorflow.keras import layers, Sequential

plt.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
plt.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
plt.rcParams['savefig.dpi'] = 600  # 图片像素
plt.rcParams['figure.dpi'] = 600  # 分辨率
font_set = FontProperties(fname=r"C:\Windows\Fonts\simsun.ttc", size=10.5)
root = os.path.join(os.getcwd(), "ImageProcessing")
img_dir = os.path.join(root, "images")
address = os.path.join(img_dir,"lena.jpg")
address1 = os.path.join(img_dir,"me.jpg")
import matplotlib.pylab as pylab
import matplotlib.image as mpimg
img = mpimg.imread(address)/255
import skimage.color
# 1）绘制图像轮廓线和轮廓填充
img_gray = skimage.color.rgb2gray(img)
plt.subplot(131),plt.imshow(img_gray,cmap='gray'),plt.title("原始图像",size=20)
# np.flipud上下方向翻转阵列 end->start,end-1->start+1,...第1行变为最后1行,最后1行变为第1行
plt.subplot(132),plt.contour(np.flipud(img_gray),colors='k',levels=np.logspace(-15,15,100)),plt.title("轮廓线",size=20)
plt.subplot(133),plt.contourf(np.flipud(img_gray),cmap='inferno'),plt.title("轮廓填充",size=20),plt.show()
