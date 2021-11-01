#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 读取图像的方式.py
@Author : chenbei
@Date : 2021/8/30 14:12
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
root = os.path.join(os.getcwd(), "ImageProcessing")
img_dir = os.path.join(root, "images")
address = os.path.join(img_dir,"lena.jpg")
address1 = os.path.join(img_dir,"me.jpg")
# PIL (width, height) skimage (height,width, channel) 因为数组习惯先行后列对应的为先高后宽
# PIL得到的是PIL对象 skimage的得到的是Numpy对象 通过np.array(PIL)和skimage.Image.fromarray(skimage)相互转换
# matplotlib读取得到的也是Numpy对象
#%% 使用 pillow
from PIL import  Image,ImageFont,ImageDraw
img = Image.open(address)
print(img.width,img.height,img.mode,img.format,type(img))
# img.convert('RGBA') 图片为为RGBA(四通道+透明度)格式时转换为RGB(三通道)
img.show()
#  转为灰度图像 "L", "RGB" and "CMYK."
img_grey = img.convert('L') # L = R * 299/1000 + G * 587/1000 + B * 114/1000
img_grey = np.array(img_grey) # 可以利用np.array将PIL对象转换,与Image.fromarray功能相反
# img_grey.show()
# img.save(address)
#%% 使用 matplotlib
import matplotlib.image as mpimg
import PIL
img = mpimg.imread(address)/255
img_ = mpimg.imread(address1)
img_ = PIL.Image.fromarray(img_)
img_ = img_.resize((img.shape[1], img.shape[0])) # (width, height)
img_ = np.array(img_)/255
print(img_.size,img_.shape,img_.dtype,type(img_))
i  = 1
for alpha in np.linspace(0,1,20):
    plt.subplot(4,5,i)
    plt.imshow((1-alpha)*img+alpha*img_)
    plt.axis('off')
    i+=1
plt.subplots_adjust(wspace=0.05,hspace=0.05),plt.show()
#%%
# plt.axis("off"),plt.imshow(img),plt.show()
img1 = img / 255
img1[img1<0.5] = 0 # 转换成较暗的图像
# plt.imshow(img1) # interpolation表示插值方法,有多种 在小图像中有明显差异
# 最近邻插值、双线性插值、双三次插值、16样条插值、兰索斯插值
methods = ['none','nearest','bilinear','bicubic','spline16','lanczos']
plt.axis("off")
plt.tight_layout()
plt.show()
fig ,axes = plt.subplots(2,3,subplot_kw={'xticks':[],'yticks':[]})
fig.subplots_adjust(hspace=0.05,wspace=0.05)
for ax , method in zip(axes.flatten(),methods):
    ax.imshow(img1,interpolation=method)
    ax.set_title(str(method),size=20)
plt.tight_layout()
plt.show()
# plt.savefig(address)
#%% 使用 scikit-image
import skimage
from skimage import viewer
from skimage.io import imread,imsave,imshow,show ,imread_collection,imshow_collection
# imread_collection,imshow_collection 一次性读取多个图像
img = imread(address,as_gray=False) # 灰度图
print(img.shape,img.dtype,type(img))
# img = skimage.color.gray2rgb(img)
hsv = skimage.color.rgb2hsv(img) # (h,s,v)=(色调、饱和度、值)=(颜色、色彩、亮度)
plt.subplot(131),imshow(hsv[:,:,0]),plt.title("H",size=20)
plt.subplot(132),imshow(hsv[:,:,1]),plt.title("S",size=20)
plt.subplot(133),imshow(hsv[:,:,2]),plt.title("V",size=20)
show()
# 饱和度为颜色和白色的混合程度，亮度为颜色和黑色的混合程度
hsv[:,:,1] = 0.5 # 饱和度更改为常量，色调和值通道保持不变
img1 = skimage.color.hsv2rgb(hsv)
# imsave(address,img1)
# plt.axis("off")
# imshow(img),show()
# imshow(img1),show()

# 使用viewer模块也可 但是需要PyQt5
# viewer = viewer.ImageViewer(img1)

img2 = skimage.data.astronaut()
# imshow(img2),show()

img2 = Image.fromarray(img2) # array对象变为PIL对象
#%% 使用scipy的 misc 和 imageio
import scipy ,imageio
img = scipy.misc.face()
# scipy.misc.imsave("face.png",img) # misc借助了PIL模型
plt.imshow(img),plt.show()
# img = scipy.misc.imread(address) # 高版本已弃用
img = imageio.imread(address)
plt.imshow(img),plt.show()

