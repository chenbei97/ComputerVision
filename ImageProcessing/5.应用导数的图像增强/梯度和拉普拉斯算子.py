#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 梯度和拉普拉斯算子.py
@Author : chenbei
@Date : 2021/9/8 11:43
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
from matplotlib.font_manager import FontProperties
import numpy as np
import os
import skimage.util
import skimage
from PIL import Image
import  scipy.signal
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
#%% （1）梯度
fowardker_x,fowardker_y = [[-1,1]],[[-1],[1]]
im = Image.open(img_dir+"\chess.jpg").convert("L")
im = np.asarray(im)
im_dx = scipy.signal.convolve2d(im,fowardker_x,mode='same')
im_dy = scipy.signal.convolve2d(im,fowardker_y,mode='same')
im_mag = np.sqrt(im_dx**2+im_dy**2)
im_ang = np.arctan(im_dy/im_dx)
imgs = [im,im_dx,im_dy,im_mag,im_ang]
fig ,axes = pylab.subplots(2,3)
axes = axes.flatten()
titles = ['original','$grad_x$','$grad_y$','||grad||',r'$\theta$']
for img ,axe,title in zip(imgs,axes[:-1],titles):
    plot_ax(img,axe,title)
# 绘制最后1个子图,图像第一行像素核图像对x骗偏导的第121行随y的变化f(0,y)、f'(0,y)
axes[-1].plot(range(im.shape[1]),im[121,:],'r-',label=r'$f(x,y)|_{x=121}$')
axes[-1].plot(range(im.shape[1]),im_dx[121,:],'g-',label=r'$grad_x(f(x,y))|_{x=121}$')
axes[-1].plot(range(im.shape[1]),im_dy[:,121],'b-',label=r'$grad_y(f(x,y))|_{y=121}$')
axes[-1].legend(prop=dict(size=8))
axes[-1].set_title("$grad|_{xy}(f(x,y))|_{x,y=121}$")
fig.show()
#%%（2）拉普拉斯算子
"""[1]
[1][-4][1]
   [1]
"""
im_noise = skimage.util.random_noise(im,var=1) # 拉普拉斯算子对噪声十分敏感
ker_laplacian = [[0,1,0],[-1,4,-1],[0,-1,0]]
im_laplacian = scipy.signal.convolve2d(im,ker_laplacian,mode='same')
im_laplacian_noise = scipy.signal.convolve2d(im_noise,ker_laplacian,mode='same')
im_laplacian , im_laplacian_noise = np.clip(im_laplacian,0,255),np.clip(im_laplacian_noise,0,255)
plot_im1_im2(im_laplacian,im_laplacian_noise,title1="no noise",title2='add noise')




