#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 二维卷积.py
@Author : chenbei
@Date : 2021/9/1 9:41
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
from matplotlib.font_manager import FontProperties
import numpy as np
import os
from PIL import Image
import skimage.io ,skimage.color,skimage.transform
import scipy.signal ,scipy.ndimage,scipy.misc
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

#%% （1）scipy.signal_convolve2d 对RGB或RGBA多通道图像必须分通道进行卷积
# 1）灰度图像卷积
img = skimage.io.imread(img_dir +  "/cameraman.jpg")
im = skimage.color.rgb2gray(img).astype(float)
conv_kernel_box = np.ones((3,3)) / 9 # 模糊 [[cornor,edge,cornor],[edge,inner,edge],[cornor,edge,cornor]]
conv_kernel_edge = np.array([[0,1,0],[1,-4,1],[0,1,0]]) # 使用拉普拉斯核 锐化检测图像边缘
im_conv_box = scipy.signal.convolve2d(in1=im, in2=conv_kernel_box,
                                  mode='valid',boundary='fill',fillvalue=0) # (225-3+2p)/s + 1 = 225 p=2
im_conv_edge = scipy.signal.convolve2d(in1=im,in2=conv_kernel_edge,mode='valid')
img_conv_edge_clip = np.clip(im_conv_edge,0,1) # RGB要求为浮点数
fig , axes = pylab.subplots(ncols=3,sharex=True,sharey=True)
axes[0].imshow(im,cmap=plt.cm.gray)
axes[1].imshow(im_conv_box,cmap=plt.cm.gray)
axes[2].imshow(img_conv_edge_clip,cmap=plt.cm.gray)
titles = ["original","box blur","laplace edge detection"]
for ax,title in zip(axes,titles) :
    ax.set_title(title)
    ax.axis('off')
pylab.show()
#%%
# 2）彩色图像卷积 需要分通道
im = skimage.img_as_float(skimage.io.imread(img_dir +  "/tajmahal.jpg"))
conv_kernel_box = np.array([[-2,-1,0],[-1,1,1],[0,1,2]]) # 浮雕
conv_kernel_edge = np.array([[-3-3j,0-10j,3-3j],[-10,0,10],[-3+3j,10j,3+3j]]) # 使用scharr滤波器
im_box , im_edge = np.ones(im.shape),np.ones(im.shape)
channels = 3
for channel in range(channels):
    im_conv_box_channel = scipy.signal.convolve2d(im[...,channel],conv_kernel_box,mode='same',boundary='symm') # 对每个通道进行卷积
    im_conv_edge_channel = scipy.signal.convolve2d(im[...,channel],conv_kernel_edge,mode='same',boundary='symm').real
    # 对卷积后的输出进行限制在 [0,1],限制后的结果送入创建好的对象
    im_box[...,channel] = np.clip(im_conv_box_channel,0,1)
    im_edge[...,channel] = np.clip(im_conv_edge_channel,0,1)
print((im[...,2]==im[:,:,2]).all()) # 是否全部为True any()是否全部为False
fig , axes = pylab.subplots(ncols=3)
axes[0].imshow(im)
axes[1].imshow(im_box)
axes[2].imshow(im_edge)
titles = ["original","box emboss","scharr edge detection"]
for ax,title in zip(axes,titles) :
    ax.set_title(title)
    ax.axis('off')
pylab.show()
#%% （2）scipy.ndimage_convolve进行卷积 无需对不同通道分别卷积可以直接使用
im = skimage.img_as_float(skimage.io.imread(img_dir +  "/vic.png"))
print(Image.open(img_dir +  "/vic.png").mode) # RGBA 图像是4通道的
# 浮雕 [[-diag,-iden,0],[-iden,iden,iden],[0,iden,diag]]
conv_kernel_emboss = np.array([-2,-1,0,-1,1,1,0,1,2]).reshape((3,3,1))
# 锐化 [[0,edge,0],[edge,inner,edge],[0,edge,0]]
conv_kernel_sharpen = np.array([0,-1,0,-1,5,-1,0,-1,0]).reshape((3,3,1))
im_emboss = scipy.ndimage.convolve(input=im, weights=conv_kernel_emboss,  mode='nearest')
im_emboss = np.clip(im_emboss,0,1)
im_sharpen = scipy.ndimage.convolve(input=im,weights=conv_kernel_sharpen,mode='nearest')
im_sharpen = np.clip(im_sharpen,0,1)
fig , axes = pylab.subplots(ncols=3)
axes[0].imshow(im)
axes[1].imshow(im_emboss)
axes[2].imshow(im_sharpen)
titles = ["original","emboss","sharpen"]
for ax,title in zip(axes,titles) :
    ax.set_title(title)
    ax.axis('off')
pylab.show()
#%% （3）卷积和相关的区别
# 定义上卷积运算之前先对卷积核进行2次翻转(相对于水平和垂直轴)然后计算核与图像的加权组合
# 相关运算无需翻转卷积核直接计算，下方的代码展示了对图像直接进行卷积、对图像直接相关和卷积翻转后相关的区别
# 1）原始
im = skimage.img_as_float(skimage.color.rgb2gray(skimage.io.imread(img_dir +  "/lena_g.png")))
# 2）卷积 : 使用scipy.signal对灰度图卷积 波纹核
conv_kernel_rev = np.array([0,-1,np.sqrt(2),1,0,1,-np.sqrt(2),1,0]).reshape((3,3))
im_conv = scipy.signal.convolve2d(in1=im, in2=conv_kernel_rev)
im_conv = np.clip(im_conv,0,1)
# 3）直接相关
im_corr = scipy.signal.correlate2d(in1=im,in2=conv_kernel_rev)
im_corr = np.clip(im_corr,0,1)
# 4）翻转卷积核后相关
conv_kernel_rev_ud = np.flipud(conv_kernel_rev)
conv_kernel_rev_ud_lr = np.fliplr(conv_kernel_rev_ud)
im_ud_lr_corr = scipy.signal.correlate2d(in1=im,in2=conv_kernel_rev_ud_lr)
im_ud_lr_corr = np.clip(im_ud_lr_corr,0,1)
# 5）直接卷积和直接相关的差值图像
im_conv_corr = im_conv - im_corr
# 6）直接卷积和间接相关的差值图像
im_conv_flipcorr = im_conv  - im_ud_lr_corr
# 7）可视化图像比较
fig , axes = pylab.subplots(nrows=3,ncols=2,sharex=True, sharey=True)
axes = axes.flatten()
axes[0].imshow(im,cmap=plt.cm.gray),axes[1].imshow(im_conv,cmap=plt.cm.gray)
axes[2].imshow(im_corr,cmap=plt.cm.gray),axes[3].imshow(im_ud_lr_corr,cmap=plt.cm.gray)
axes[4].imshow(im_conv_corr,cmap=plt.cm.gray),axes[5].imshow(im_conv_flipcorr,cmap=plt.cm.gray)
titles = ["original","conv","corr","flipcorr","subtract(conv,corr)","siubtract(conv,flipcorr)"]
for ax,title in zip(axes,titles) :
    ax.set_title(title)
    ax.axis('off')
pylab.show()

#%%
face_image = scipy.misc.face(gray=True) # 获取 1024 x 768 的浣熊脸灰色图像
face_image_mean = face_image.mean()
face_image  = face_image - face_image_mean # 去中心
# 得到浣熊眼睛图像
eye_image = np.copy(face_image[300:365,670:750])
eye_image -= eye_image.mean()
# 加入标准正态分布随机噪声
face_image += np.random.randn(*face_image.shape) * 50 #  * 的作用：在函数调用中，* 能够将元组或者列表解包成不同的参数
# 计算相关
image_corr = scipy.signal.correlate2d(face_image,eye_image,mode='same',boundary='symm')
row , col = np.unravel_index(np.argmax(image_corr),image_corr.shape) # 找到展平数组最大处于的位置,然后将其反转得到展平前的位置
# 返回的是行和列位置,对应的高度和宽度
print(np.argmax(image_corr) // image_corr.shape[1] ,np.argmax(image_corr) % image_corr.shape[1]) # 332,709
fig,(ax1,ax2,ax3) = pylab.subplots(1,3)
ax1.imshow(face_image,cmap='gray'),ax1.set_axis_off(),ax1.set_title("face")
ax2.imshow(eye_image,cmap='gray'),ax2.set_axis_off(),ax2.set_title("eye")
ax3.imshow(image_corr),ax3.set_axis_off(),ax3.set_title("corr")
# 回到图像,描述图像的像素位置使用(宽度,高度)进行描述
ax1.plot(col,row,'ro',markersize=10),fig.show() # 圈出眼睛的一个点
#%%














