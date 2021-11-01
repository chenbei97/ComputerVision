#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 基于skimage.filter.rank.py
@Author : chenbei
@Date : 2021/9/10 14:19
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
from matplotlib.font_manager import FontProperties
import os
import skimage.io , skimage.color ,skimage.filters,skimage.morphology
import skimage
plt.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
plt.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
plt.rcParams['savefig.dpi'] = 600  # 图片像素
plt.rcParams['figure.dpi'] = 600  # 分辨率
font_set = FontProperties(fname=r"C:\Windows\Fonts\simsun.ttc", size=10.5)
root = os.path.join(os.getcwd(),"ImageProcessing")
img_dir = os.path.join(root,"images")
def plot_im1_im2(im1,im2,title1="original",title2="reconstruction"):
    fig = plt.figure()
    ax1 = fig.add_subplot(121)
    ax2 = fig.add_subplot(122)
    ax1.imshow(im1)
    ax2.imshow(im2)
    ax1.set_title(title1,size=12),ax2.set_title(title2,size=12)
    ax1.set_axis_off(),ax2.set_axis_off()
    fig.show()
#%% （1）对比度增强
# 和曝光模块的自适应直方图均衡可以对比使用，都是局部的提升对比度
im = skimage.color.rgb2gray(skimage.io.imread(img_dir+"\lena.jpg"))
im_contrast = skimage.filters.rank.enhance_contrast(im,skimage.morphology.disk(5))
# plot_im1_im2(im,im_contrast)
# （2）中值滤波器去噪
im_median = skimage.filters.rank.median(im,skimage.morphology.disk(5))
# （3）计算局部熵 : 定义 H = -Σ(0-255)Pilog2(Pi)
im_enntropy = skimage.filters.rank.entropy(im,skimage.morphology.disk(5))
plot_im1_im2(im,im_enntropy)






