#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : ImageProcessing（scipy）.py
@Author : chenbei
@Date : 2021/8/31 13:18
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
from matplotlib.font_manager import FontProperties
import numpy as np
import pandas as pd
import os
plt.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
plt.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
plt.rcParams['savefig.dpi'] = 600  # 图片像素
plt.rcParams['figure.dpi'] = 600  # 分辨率
font_set = FontProperties(fname=r"C:\Windows\Fonts\simsun.ttc", size=10.5)
import  scipy.fftpack,scipy.ndimage,scipy.signal
from  PIL import  Image
import matplotlib.pylab as pylab
root = os.path.join(os.getcwd(),"ImageProcessing")
img_dir = os.path.join(root,"images")
im1 = np.array(Image.open(img_dir +  "/rhino.jpg").convert(mode='L'))
#%%
# （1）scipy.fftpack模块
freq1 = scipy.fftpack.fft2(im1)
im1_ = scipy.fftpack.ifft2(freq1).real # 以频域的实部重建图像
freq1_shift = scipy.fftpack.fftshift(freq1)  # 将零频率分量移动到频谱的中心
im1_shift = scipy.fftpack.ifftshift() # 对中心区域为原点的时域图像平移回左上方
#%%
# （2）scipy.signal  对RGB或RGBA多通道图像必须分通道进行卷积
# 1）计算卷积
# mode参数
# ① mode="full" 输出是输入的完全离散线性卷积 default
# ② mode="valid" 忽略边缘像素，只计算所有相邻像素无需零填充 除了1×1的核输出图像都小于输入图像大小
# ③ mode="same" 输入输出图像大小相同 以full输出为中心
conv_kernel_box = np.ones((3,3)) / 9
im_conv_box = scipy.signal.convolve2d(in1=im1, in2=conv_kernel_box,
                                  mode='valid',boundary='fill',fillvalue=0)
# 2）计算相关
im_corr = scipy.signal.correlate2d(in1=im1,in2=conv_kernel_box)
# 3）快速卷积
sigma = 2
filterX = scipy.signal.gaussian(M=im1.shape[0],std=sigma) # x方向的正态分布滤波器 一维数组
filterY = scipy.signal.gaussian(M=im1.shape[1],std=sigma)
filter = np.outer(filterX,filterY)
im_method_1 = scipy.signal.fftconvolve(in1=im1,in2=filter,mode='same')
# 4）直接卷积
im_method_2 = scipy.signal.convolve(in1=im1,in2=filter,mode='same')
#%%
# （3）scipy.ndimage模块 无需对不同通道分别卷积可以直接使用
# mode = "reflect","constant","nearest"
# 1）scipy.ndimage.convolve
sigma = 2
conv_kernel_sharpen = np.array([0,-1,0,-1,5,-1,0,-1,0]).reshape((3,3,1))
im_sharpen = scipy.ndimage.convolve(input=im1,weights=conv_kernel_sharpen,mode='nearest')
# 2）scipy.ndimage.fourier_gaussian 多维高斯傅立叶滤波器 输入数组与高斯核的傅立叶变换相乘
# 输入图像的频域得到图像的频域
out_freq_ = scipy.ndimage.fourier_gaussian(freq1,sigma=sigma)
out_freq__ = scipy.ndimage.fourier_uniform(freq1,size=sigma)
out_freq___ = scipy.ndimage.fourier_ellipsoid(freq1,size=sigma)
pylab.imshow(scipy.fftpack.ifft2(out_freq_).real,cmap='coolwarm')
# 3）scipy.ndimage.uniform_filter 和 scipy.ndimage.gaussian_filter 直接滤波输出
# 输入图像的时域得到图像的时域
k,s = 7 ,2
t = ((k-1)/2 - 0.5) /s
out = scipy.ndimage.uniform_filter(im1,size=(k,k,1)) # 多维均匀滤波器 size或sigma可以给定不同轴不同的值
out_ = scipy.ndimage.gaussian_filter(im1,sigma=(s,s,0),truncate=t) # 多维高斯滤波器,truncate表示标准偏差处截断滤波器默认4.0
# 3）计算多维百分位过滤器 percentile 为百分位可以传入负数 -20%等价于80%
im1_percentilefiltered = scipy.ndimage.percentile_filter(im1,percentile=-20,size=(3,3,1))
# 4）LoG带通二阶滤波器
im_guasslaplace = scipy.ndimage.gaussian_laplace(im1, sigma=sigma)
# 5）形态学计算
scipy.ndimage.binary_fill_holes(im1,structure=np.ones((3,3)))
scipy.ndimage.grey_opening(im1,size=(2,2))
scipy.ndimage.grey_closing(im1,size=(2,2))
scipy.ndimage.grey_dilation(im1,size=(3,3))
scipy.ndimage.grey_erosion(im1,size=(3,3))
scipy.ndimage.morphological_gradient(im1,size=(3,3))
scipy.ndimage.morphological_laplace(im1,size=(5,5))
# 6）计算图像标签区域分布
# 输入input中的任何非零值都被视为特征，零值被视为背景
# 理解为重新调整分布，原来的特征是1，但是1的分布不是连续的，将这些1继续细分多个区域，改变了像素亮度
# num_features 为细分后的区域种类
# label分成了num_features个特征+1个背景
label , num_features = scipy.ndimage.label(input=im1)




































