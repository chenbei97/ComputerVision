#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 图像处理的高级问题.py
@Author : chenbei
@Date : 2021/9/27 13:15
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
import numpy as np
import os
import skimage.io, skimage.color, skimage.restoration, skimage.filters, \
    skimage.segmentation, skimage.feature, skimage.transform, skimage.morphology
from sklearn import preprocessing, decomposition, datasets, cluster, pipeline, neighbors, metrics
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
def plot_im1_im2(im1,im2,title1="original",title2="reconstruction"):
    fig = plt.figure()
    plt.gray()
    ax1 = fig.add_subplot(121)
    ax2 = fig.add_subplot(122)
    ax1.imshow(im1),ax2.imshow(im2)
    ax1.set_title(title1,size=12),ax2.set_title(title2,size=12)
    ax1.set_axis_off(),ax2.set_axis_off()
    fig.show()
root = os.path.join(os.getcwd(), "ImageProcessing")
img_dir = os.path.join(root, "images")
plane = skimage.io.imread(img_dir+"\plane.jpg")
#%% （1）接缝雕刻
# 1）接缝雕刻调整图片大小
# ① 直接调整
resized = skimage.transform.resize(plane,(plane.shape[0],plane.shape[1]-300,3),mode='reflect')
# ② 接缝调整
# 计算像素能量，一般使用双梯度能量函数，如sobel
energy = skimage.filters.sobel(plane)
# 接缝识别和接缝移除
# 15版本及其以下才有此函数
# out = skimage.transform.seam_carve(image=plane, energy_map=energy, mode='vertical', num=200, border=1, force_copy=True)
# plot_im1_im2(plane,resized)
#%% （2）图像修复
# 基于已知的二进制掩膜D，这个D标定了图像的受损像素
# 使用双调和方程假设修复图像 inpaint_biharmonic
im = skimage.io.imread(img_dir+'\lena.jpg')
mask = skimage.io.imread(img_dir+r'\text.jpg')
mask = skimage.transform.resize(skimage.color.rgb2gray(mask),(im.shape[0],im.shape[1]))
mask[mask>0.5] = 1
mask[mask<=0.5] = 0 # 二进制
im_bad = im.copy()
for raw in range(im_bad.shape[-1]) : # 每个通道用相同的掩码制造受损图像
    im_bad[np.where(mask)] = 0

im_re = skimage.restoration.inpaint.inpaint_biharmonic(im_bad,mask,multichannel=True)
plot_im1_im2(im_bad,im_re)
# %%（3）全变分去噪TVD
im = skimage.io.imread(img_dir+'\lena.jpg')
im_noise = skimage.util.random_noise(im)
# 去噪权重越大去噪效果越好，但是会牺牲图像的保真度从而导致图像模糊
im_re_ = skimage.restoration.denoise_tv_chambolle(im_noise,weight=1)
plot_im1_im2(im_noise,im_re)
#%% （4）






