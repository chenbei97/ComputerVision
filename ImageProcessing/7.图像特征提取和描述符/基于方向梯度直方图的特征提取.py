#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 基于方向梯度直方图的特征提取.py
@Author : chenbei
@Date : 2021/9/10 16:16
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
import os
import skimage.io, skimage.feature, skimage.exposure
import skimage
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
im = skimage.io.imread(img_dir+r"\cameraman.jpg")
# out = (n_blocks_row, n_blocks_col, n_cells_row, n_cells_col, n_orient)
out , HoG = skimage.feature.hog(im,orientations=8,
                               pixels_per_cell=(16,16),
                               cells_per_block=(1,1),
                               visualize=True,
                               multichannel=True,
                                feature_vector=False)
# HoG是float类型，输出默认会将HoG的最大值作为1.0，并以此为基准去缩放其他像素
HoG_rescaled_default = skimage.exposure.rescale_intensity(HoG)
# 当修改in_range=(0,20)时，凡是大于20的均为1.0
HoG_rescaled_inrange = skimage.exposure.rescale_intensity(HoG,in_range=(0,20)) # 提高对比度曝光
plot_im1_im2(HoG_rescaled_default,HoG_rescaled_inrange)

#%%
import numpy as np








