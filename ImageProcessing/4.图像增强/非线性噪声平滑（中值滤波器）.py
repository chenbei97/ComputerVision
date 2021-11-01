#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 非线性噪声平滑（中值滤波器）.py
@Author : chenbei
@Date : 2021/9/3 16:56
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
from matplotlib.font_manager import FontProperties
import numpy as np
import os
import skimage.io , skimage.color ,\
    skimage.restoration ,skimage.util,skimage.metrics
import skimage
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
def plot_im1_im2(im1,im2):
    fig = plt.figure()
    plt.gray()
    ax1 = fig.add_subplot(121)
    ax2 = fig.add_subplot(122)
    ax1.imshow(im1),ax2.imshow(im2)
    ax1.set_title("original",size=12),ax2.set_title("reconstruction",size=12)
    ax1.set_axis_off(),ax2.set_axis_off()
    plt.show()
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
#%% （1）基于PIL
#     1）中值滤波器
img = Image.open(img_dir+"\mandrill.jpg")
for percent in [0.2,0.3]:
    img_addnoise = add_noise(img,percent) # 噪声水平
    for size in [3,7] : # 核大小
        im_medianfiltered = img_addnoise.filter(ImageFilter.MedianFilter(size))
        plot_im1_im2(img_addnoise,im_medianfiltered)
#     2）最大、最小滤波器
img_addnoise = add_noise(img,0.3)
size = 3
im_maxfiltered = img_addnoise.filter(ImageFilter.MaxFilter(size))
im_minfiltered = img_addnoise.filter(ImageFilter.MinFilter(size))
plot_im1_im2(im_minfiltered,im_maxfiltered)
#%% （2）基于skimage
#     1）双边滤波器
# 不使用add_noise函数 使用skimage.util.random_noise()
img = skimage.io.imread(img_dir+"\man.png")
img = skimage.color.rgb2gray(skimage.color.rgba2rgb(skimage.img_as_float(img)))
sigma = 0.155
img_addnoise = skimage.util.random_noise(img,var=sigma**2)
for sigma_color in [5,20]:
    for sigma_spatial in [0.1,0.25] :
        plot_im1_im2(img_addnoise,
                     skimage.restoration.denoise_bilateral(img_addnoise,
                                                           sigma_color=sigma_color,
                                                           sigma_spatial=sigma_spatial,
                                                           multichannel=False))
#     2）非局部均值滤波器 : 对 2-D 或 3-D 灰度图像和 2-D RGB 图像执行非局部均值去噪
# 不使用add_noise函数 使用np.random.standard_normal
img = skimage.img_as_float(skimage.io.imread(img_dir+"\parrot.png"))
img_noise = img + 0.25*np.random.standard_normal(img.shape)
img_noise = np.clip(img_noise,0,1)
#     ①（高斯）噪声标准偏差的稳健的基于小波的估计器
sigma_est = np.mean(skimage.restoration.estimate_sigma(img_noise,multichannel=True))
print("噪声偏差估计：%.5f" % (sigma_est))
pacth_kw = dict(patch_size=5,patch_distance=6,multichannel=True) # 定义一个打包参数字典，指定斑块的大小和之间的距离
#     ② 慢速算法
img_denoise_slow = skimage.restoration.denoise_nl_means(img_noise,h=1.15*sigma_est,
                                                        fast_mode=False,**pacth_kw)
#     ③ 快速算法
img_denoise_fast = skimage.restoration.denoise_nl_means(img_noise,h=0.8*sigma_est,
                                                        fast_mode=True,**pacth_kw)
plot_im1_im2(img_denoise_slow,img_denoise_fast)
#     ④ 峰值信噪比
psnr_noise = skimage.metrics.peak_signal_noise_ratio(img,img_noise)
psnr_denoise_slow = skimage.metrics.peak_signal_noise_ratio(img,img_denoise_slow)
psnr_denoise_fast = skimage.metrics.peak_signal_noise_ratio(img,img_denoise_fast)
print("去噪前峰值信噪比为：%.5f" % (psnr_noise))
print("去噪后峰值信噪比为(slow)：%.5f" % (psnr_denoise_slow))
print("去噪后峰值信噪比为(fast)：%.5f" % (psnr_denoise_fast))
#%% （3）基于scipy ndimage
# 函数为percentile_filter()中值滤波器的一个通用版本 计算多维百分位过滤器
lena = pylab.imread(img_dir+"\lena.jpg")
noise = np.random.random(lena.shape)
lena[ noise > 0.9] = 255
lena[ noise < 0.1] = 0
for p in range(25,100,25):
    for s in [10,20]:
        # percentile 为百分位可以传入负数 -20%等价于80%
        lena_denoise = scipy.ndimage.percentile_filter(lena,percentile=p,size=(s,s,1))
        plot_im1_im2(lena,lena_denoise)














