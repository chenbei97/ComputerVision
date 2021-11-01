#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 图像复原.py
@Author : chenbei
@Date : 2021/9/3 15:10
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
from matplotlib.font_manager import FontProperties
import numpy as np
import os
import skimage.io ,skimage.color,skimage.restoration
import scipy.signal , scipy.fftpack ,scipy.ndimage,scipy.misc
import numpy.fft
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
def plot_surface(array,freq,titles,allfreq=False) :
    def prepare(array):
        # x, y = np.mgrid[-2:2:0.01, -2:2:0.01]
        # z = (1 / 2 * np.pi * sigma ** 2) * np.exp(-(x ** 2 + y ** 2) / 2 * sigma ** 2)
        if allfreq :  # 绘制2个频谱图时先进入此函数array是complex类型的
            array = array.real
        assert array.dtype != "complex128"
        delta_x = (np.max(array) - np.min(array))/array.shape[0]
        delta_y = (np.max(array) - np.min(array))/array.shape[1]
        delta_x,delta_y = complex(delta_x),complex(delta_y) # 变成负数再取实部
        xx ,yy = np.mgrid[np.min(array):np.max(array):delta_x.real,np.min(array):np.max(array):delta_y.real]
        if (xx.shape != yy.shape) or (xx.shape!=array.shape) :
            xx , yy = xx[:-1,:-1],yy[:-1,:-1]
        # print(array.shape, xx.shape, yy.shape)
        # 一般而言是可以恰好等分为array.shape,但是可能会出现进1的情况
        assert xx.shape==yy.shape and xx.shape==array.shape # 出现进1报错
        return xx ,yy
    xx , yy = prepare(array)
    freq = freq.real
    ax1 = plt.subplot(121, projection='3d')
    if not allfreq :
        ax1.plot_surface(xx,yy,array,cmap='coolwarm'),ax1.set_title(titles[0],size=14)
    else:
        freq_ = array.real
        xx ,yy = prepare(freq_)
        ax1.plot_surface(xx, yy, 20 * np.log10(np.where(freq_ <= 0, 0.01, freq_)), cmap='coolwarm'), ax1.set_title(titles[0], size=14)
    ax2 = plt.subplot(122,projection='3d')
    ax2.plot_surface(xx,yy,20*np.log10(np.where(freq<=0,0.01,freq)),cmap='coolwarm'),ax2.set_title(titles[1],size=14)
    plt.show()
#%%
# （1）逆滤波器HPF 要求卷积核H已知,输入存在噪声时性能不好
# 1）得到模糊图像
im = skimage.io.imread(img_dir+"\lena.jpg")
im = skimage.color.rgb2gray(im)
# 输入噪声较大时效果会很差
for col in range(im.shape[1]):
    im[:,col] += 0.01* col * np.cos(2*np.pi*col)
im_freq = numpy.fft.fft2(im) # F
sigma = 3
filter = np.outer(scipy.signal.gaussian(im.shape[0],sigma),scipy.signal.gaussian(im.shape[1],sigma))
filter_freq = numpy.fft.fft2(im) # H
out_freq = im_freq * filter_freq # F × H = G
out = numpy.fft.ifft2(out_freq) # g
plot_image(im=out,isre=True)
# 2）对模糊图像去卷积
epsilon = 10**-6 # avoid division by zero
filter_freq_ = 1 / (epsilon + filter_freq) #  1 / H
out_freq_ = scipy.fftpack.fft2(out) # G'
im_freq_ = out_freq_ * filter_freq_ # G' * 1/H
im_ = scipy.fftpack.ifft2(im_freq_) # f'
plot_image(im_,isre=True)
# 3）比较
# 滤波器的时域和频域3D
# plot_surface(1/(epsilon+filter),filter_freq_,titles=["filter_inverse","filter_freq_inverse"])
# 模糊后的输出图像频谱 和 输出图像的fft2频谱 3D
# plot_surface(out_freq,out_freq_,titles=["out_freq","out_freq_inverse"],allfreq=True)
# 4）运动模糊核(了解)滤波器频谱会出现明显的强条纹
kernel_size = im.shape
kernel = np.zeros((kernel_size[0],kernel_size[1]))
print(int((kernel_size[0]-1)/2))
kernel[int((kernel_size[0]-1)/2),:] = np.ones(kernel_size[0]) # np.ones(kernel_size)默认1×kernel_size
kernel = kernel / max(kernel_size)
kernel_freq = scipy.fftpack.fft2(kernel) # H
kernel_freq_ = 1 / (epsilon + kernel_freq) # 1/H
# kernel_freq_shift = scipy.fftpack.ifftshift(kernel_freq)
# plot_image(freq=kernel_freq_shift,isfreq=True) # 查看滤波器的频谱 强条纹
out_freq = im_freq * kernel_freq # G = F × H
out = numpy.fft.ifft2(out_freq) # g
plot_image(im=out,isre=True)
out_freq_ = scipy.fftpack.fft2(out)
im_freq_ = out_freq_ * kernel_freq_ # G' * 1/H
im_ = scipy.fftpack.ifft2(im_freq_) # f'
plot_image(im_,isre=True)
#%%（2）维纳滤波器
n1 ,n2 = 5 , 2
filter1 = np.ones((n1,n1)) / n1**2
filter2 = np.ones((n2,n2)) / n2**2
im_blur = scipy.signal.convolve2d(im,filter1,'same')
plot_image(im=im_blur) # 模糊图像
im_wena = skimage.restoration.unsupervised_wiener(im_blur,filter2) # 可以用的不一样
plot_image(im=im_wena[0],isre=True) # 维纳重建图像
#%% 一个图像复原的例子
im = skimage.io.imread(img_dir+"\moonlanding.png")
from matplotlib.colors import LogNorm # 在对数刻度上将给定值标准化为 0-1 范围
# normalize value data in the [vmin, vmax] interval into the [0.0, 1.0] interval and return it.
# If vmin and/or vmax is not given, they are initialized from the minimum and maximum value
im_fft = scipy.fftpack.fft2(im)
def plot_spectrum(im_fft):
    im_fft_shift = scipy.fftpack.ifftshift(im_fft)
    pylab.imshow(np.abs(im_fft_shift),cmap=plt.cm.afmhot,norm=LogNorm()),pylab.colorbar()
    pylab.title("im_spectrum",size=14)
    pylab.show()
# plot_spectrum(im_fft)
im_fft_ = im_fft.copy()
height , width = im_fft_.shape
im_fft_[int(height*0.1):int(height*0.9)] = 0 # 47:426 , : 去除高频分量 只保留四个角的频谱
im_fft_[:,int(width*0.1):int(width*0.9)] = 0 # : , 63:567
plot_spectrum(im_fft_)
im_new = scipy.fftpack.ifft2(im_fft_).real
plot_image(im)
plot_image(im_new,isre=True)
#%%
int(width*0.9)







