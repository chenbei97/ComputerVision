#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 锐化和反锐化掩膜.py
@Author : chenbei
@Date : 2021/9/8 11:43
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
from matplotlib.font_manager import FontProperties
import numpy as np
import os
import skimage.io , skimage.color ,skimage.filters
import skimage
import  scipy.ndimage ,scipy.signal
import matplotlib.pylab as pylab
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
def plot_ax(im,ax,title):
    ax.imshow(im),ax.set_title(title,size=12),ax.set_axis_off()
#%% （1）拉普拉斯滤波器 : 对原始图像应用拉普拉斯滤波器后的输出再叠加到原图像即可得到锐化图像
im = pylab.imread(img_dir+r'\rhino.jpg')
im = skimage.color.rgb2gray(im)
im_laplace = np.clip(skimage.filters.laplace(im) + im ,0,1)
plot_im1_im2(im,im_laplace)
#%%（2）反锐化掩膜 : 锐化图像 = 原始图像 + (原始图像 - 模糊图像) × 总数(α)
# 1）得到细节图像 (原始图像 - 模糊图像)
im = skimage.io.imread(img_dir+"\lena.jpg")
im = skimage.img_as_float(skimage.color.rgb2gray(im))
im_blur = scipy.ndimage.gaussian_filter(im,sigma=5)
im_detail = np.clip(im - im_blur , 0 , 1)
imgs = [im,im_blur,im_detail]
alphas = [1,5,10] # 总数参数
for alpha in alphas :
    imgs.append(np.clip(im + alpha * im_detail , 0 ,1))
fig ,axes = pylab.subplots(2,3)
axes = axes.flatten()
titles = ['original','blur','detail',r'sharpen $\alpha$ = '+str(alphas[0]),
          r'sharpen $\alpha$ = '+str(alphas[1]),r'sharpen $\alpha$ = '+str(alphas[-1])]
for img ,axe,title in zip(imgs,axes,titles):
    plot_ax(img,axe,title)
fig.tight_layout()
fig.show()












