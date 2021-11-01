#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 采样和量化.py
@Author : chenbei
@Date : 2021/8/31 13:15
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
from PIL import Image
import skimage.io ,skimage.transform
import matplotlib.pylab as pylab

root = os.path.join(os.getcwd(),"ImageProcessing")
img_dir = os.path.join(root,"images")
# print(img_dir)
#%% （1）采样
# 1）上采样
# ① 使用聚合值
im = Image.open(img_dir + "\\clock.png")
pylab.imshow(im),pylab.show()
im1 = im.resize((im.width*5,im.height*5),Image.NEAREST)
pylab.imshow(im1),pylab.show() # 容易失真
# ② 使用双线性插值
im1 = im.resize((im.width*5,im.height*5),Image.BILINEAR)
pylab.imshow(im1),pylab.show()
# ③ 双三次插值
im1 = im.resize((im.width*5,im.height*5),Image.BICUBIC)
pylab.imshow(im1),pylab.show()
# 2）下采样
im = Image.open(img_dir + "\\tajmahal.jpg")
# plt.imshow(im),plt.show() # plt 和 pylab是一样的
pylab.imshow(im),pylab.show()
im1 = im.resize((im.width//5,im.height//5),Image.NEAREST)
pylab.imshow(im1),pylab.show() # 容易失真和混叠
im1 = im.resize((im.width//5,im.height//5),Image.ANTIALIAS) # 区域求平均
pylab.imshow(im1),pylab.show() # 相对而言提高
# 使用skimage的rescale来调整图像大小,参数anti_aliasing=True表示开启抗混叠
# multichannel 图像的最后一个轴是否被解释为多个通道或另一个空间维度
# 使用skimage的方法必须使用图像的数组对象而非PIL对象
im = skimage.io.imread(img_dir + "\\tajmahal.jpg") # umbc.png
im1 = im.copy()
im2 = im.copy()
for i in np.arange(0,8,2):
    pylab.subplot(4,2,i+1),plt.imshow(im1),plt.axis('off') # 证明plt/pylab完全相同
    pylab.title("img1 height = " + str(im1.shape[0]) + " img1 width = " + str(im1.shape[1]),size=5)
    pylab.subplot(4,2,i+2),pylab.imshow(im2),pylab.axis('off')
    pylab.title("img2 height = "+ str(im2.shape[0]) + " img2 width = " + str(im2.shape[1]),size=5)
    # 每次向下0.5采样,先不抗混叠,再抗混叠
    im1 = skimage.transform.rescale(im1, scale=0.5,multichannel=True,anti_aliasing=False)
    im2 = skimage.transform.rescale(im2, scale=0.5, multichannel=True, anti_aliasing=True)
pylab.subplots_adjust(wspace=0.1,hspace=0.1),pylab.show()

#%%（2）量化
im = Image.open(img_dir + "\\parrot.jpg")
print(im.mode,im.format)
# 对[8, 7, 6, 5, 4, 3, 2, 1]依次做位运算 1<<8 ,1<<7,...,1<<1 = 256,128,..,1
num_colors_list = [ 1 << n for n in range(8,0,-1)]
snr_list = []
def signaltonoise(array):
    array = np.asanyarray(array)# 转换为array格式
    m = array.mean()
    sd = array.std()
    # where(condition, [x, y]) 防止出现0除 图片方差为0则返回0
    return np.where(sd == 0, 0, m / sd)
for idx , color in enumerate(num_colors_list):
    # palette=WEB(默认216种颜色),ADAPTIVE(256种颜色) colors=256表示需要0-255之间的数去描述像素强度 在计算机中为8bit存储
    # 最简单的2bit存储即二值图像,只用255和0来表示图像,可以通过改变colors的默认bit来观察图像信噪比变化
    im1 = im.convert(mode='P',palette=Image.ADAPTIVE,colors=color) # 将RGB图像转为调色板模式
    print(f"img{idx+1} size : ",im1.width,im1.height)
    pylab.subplot(4,2,idx+1),pylab.imshow(im1),pylab.axis('off')
    snr_list.append(signaltonoise(im1))
    pylab.title("colors = " +str(color)+" snr = " + str(np.round(signaltonoise(im1),3)),size=10)
pylab.subplots_adjust(wspace=0.01,hspace=0),pylab.show()
def plot_snr_colors():
    pylab.plot(num_colors_list,snr_list,'r.-')
    pylab.xlabel("Max colors in image")
    pylab.ylabel("SNR")
    pylab.title("SNR_Colors Charts")
    pylab.xscale('log',basex=2) # 刻度使用对数坐标 且以2为底
    pylab.gca().invert_xaxis() # 翻转x坐标 从大到小
    pylab.show()
plot_snr_colors()
#%%
# A = np.arange(0,8,2)
# for i in A :
#     print (i)























