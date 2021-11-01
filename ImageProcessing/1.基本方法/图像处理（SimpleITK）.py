#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 图像处理（SimpleITK）.py
@Author : chenbei
@Date : 2021/9/18 9:10
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
import numpy as np
import os
import  skimage.io , skimage.color
import SimpleITK as sitk
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
head = skimage.io.imread(img_dir+"\head.png")
head_grey = skimage.color.rgb2gray(head) * 255

# （1）GetImageFromArray 数组转换为SimpleITK图像
head_sitk = sitk.GetImageFromArray(head) # 从 numpy 数组中获取 SimpleITK 图像
# （2）SimpleITK图像变为数组
head_ = sitk.GetArrayFromImage(head_sitk)
# （3）调整对比度
head_rescale_intensity = sitk.RescaleIntensity(head_sitk)
# （4）转换图像格式
head_cast = sitk.Cast(head_rescale_intensity,sitk.sitkUInt8)

















