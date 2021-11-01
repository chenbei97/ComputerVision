#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 线性噪声平滑（均值滤波器）.py
@Author : chenbei
@Date : 2021/9/3 16:56
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
from matplotlib.font_manager import FontProperties
import numpy as np
import os
import numpy
from PIL import Image ,  ImageFilter
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
def plot_image(im=None,freq=None,isfreq=False,allplot=False,isre=False):
    if im is None and freq is None:
        print("at least one input")
        return None
    if freq is not None :
        assert type(freq) == numpy.ndarray
        if np.max(freq) > 1 :# 说明是uint8型图像
            freq = np.clip(freq.real, 0, 255)
        else:
            freq = np.clip(freq.real,0,1)
    if im is not None:
        assert type(im) == numpy.ndarray
        if isre : # 如果输入的是重建后的图像,一般是complex128,需要取实部
            im = im.real
        else:
            if np.max(im) > 1 :
                im = np.clip(im,0,255)
            else:
                im = np.clip(im,0,1)
    if allplot :
        fig , (ax1,ax2) = pylab.subplots(1,2)
        ax1.imshow(im, cmap='gray') ,ax1.axis('off'),ax1.set_title("time")
        ax2.imshow((20 * np.log10(np.where(freq <= 0, 0.1, freq))).astype(int), cmap='gray')
        ax2.axis('off'), ax2.set_title("freq")
    else:
        if not isfreq :
            pylab.imshow(im,cmap='gray')
        else:
            pylab.imshow((20*np.log10(np.where(freq<=0 , 0.1 ,freq))).astype(int),cmap='gray')
        pylab.axis('off')
    pylab.show()
#%% （1）基于PIL
# 1）ImageFilter平滑
img = Image.open(img_dir+"\mandrill.jpg")
def add_noise(img , percent=0.05 ,plot=False):
    im = img.copy()
    n = int(im.width*im.height*percent) # 添加的噪声像素个数占据总像素点的percent%
    x ,y = np.random.randint(0,im.width,n),np.random.randint(0,im.height,n) # 随机坐标点(x,y)
    for (x,y) in zip (x,y):
        # 修改给定位置的像素,椒盐噪声是随机将点变为0或255
        im.putpixel((x,y),(0,0,0) if np.random.rand() < 0.5 else(255,255,255) )
    im_blur = im.filter(ImageFilter.BLUR)
    if plot :
        pylab.subplot(121),pylab.imshow(im)
        pylab.subplot(122),pylab.imshow(im_blur),pylab.show()
    return im
img_addnoise = add_noise(img,0.5)
# 2）盒核 : 普通均值滤波器
def create_box_filter(n) :
    kernel = np.reshape(np.ones(n*n),(n,n))/ (n*n) # 普通平均
    filter = ImageFilter.Kernel( (n,n), kernel.flatten())
    return filter
filter = create_box_filter(5)
img_box_blur = img_addnoise.filter(filter)
plot_image(np.asarray(img_box_blur))
# 3）高斯核 : 加权均值滤波器
def gauss_blur(im,radius) :
    im1 = im.filter(ImageFilter.GaussianBlur(radius))
    plot_image(np.asarray(im1))
gauss_blur(img_addnoise,5)
#%% （2）基于Scipy.ndimage
k,s = 7 ,2
t = ((k-1)/2 - 0.5) /s
im_uniform_blur = scipy.ndimage.uniform_filter(img_addnoise,size=(k,k,1)) # 多维均匀滤波器
# truncate表示标准偏差处截断滤波器默认4.0   size或sigma可以给定不同轴不同的值
im_guassian = scipy.ndimage.gaussian_filter(img_addnoise,sigma=(s,s,0),truncate=t) # 多维高斯滤波器
plot_image(im_uniform_blur),plot_image(im_guassian)









