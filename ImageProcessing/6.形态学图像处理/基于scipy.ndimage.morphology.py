#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 基于scipy.ndimage.morphology.py
@Author : chenbei
@Date : 2021/9/10 14:20
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
from matplotlib.font_manager import FontProperties
import numpy as np
import os
import skimage.io , skimage.color
import skimage
import  scipy.ndimage ,scipy.signal
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
    plt.gray()
    ax1 = fig.add_subplot(121)
    ax2 = fig.add_subplot(122)
    ax1.imshow(im1),ax2.imshow(im2)
    ax1.set_title(title1,size=12),ax2.set_title(title2,size=12)
    ax1.set_axis_off(),ax2.set_axis_off()
    fig.show()
im = skimage.color.rgb2gray(skimage.io.imread(img_dir+"\lena.jpg"))
##%%（1）填充二值图像孔洞
im[im < 0.5] = 0
im[im>0.5] = 1
im_fillhole = scipy.ndimage.binary_fill_holes(im,structure=np.ones((3,3))) # 方形边越大填充的孔越少
# （2）开闭运算去噪
# 灰度图像开闭运算，可以去除椒盐噪声
im = skimage.color.rgb2gray(skimage.io.imread(img_dir+"\lena.jpg"))
im_open_close = scipy.ndimage.grey_closing(scipy.ndimage.grey_opening(im,size=(2,2)),size=(2,2))
# （3）计算形态学Beucher梯度
# 定义为输入灰度图像的膨胀运算和腐蚀运算的差值图像,两者相同
im_bg = scipy.ndimage.grey_dilation(im,size=(3,3)) - scipy.ndimage.grey_erosion(im,size=(3,3))
im_beucher = scipy.ndimage.morphological_gradient(im,size=(3,3))
# （4）计算形态学拉普拉斯
# 使用形态学梯度，结构元素要小 ，使用形态学拉普拉斯，结构元素要大
im_laplace = scipy.ndimage.morphological_laplace(im,size=(5,5))








