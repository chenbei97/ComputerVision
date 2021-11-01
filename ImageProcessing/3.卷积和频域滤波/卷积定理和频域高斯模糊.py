#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 卷积定理和频域高斯模糊.py
@Author : chenbei
@Date : 2021/9/1 13:22
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
from matplotlib.font_manager import FontProperties
import numpy as np
import os
import skimage.color,skimage.transform
import scipy.signal , scipy.fftpack ,scipy.ndimage,scipy.misc
import timeit
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
#%% （1）卷积定理的应用---手动完成
# 1）一维和二维高斯低通滤波器
# ① 得到输入图像和手动得到输入滤波器 两个形状完全相同
sigma = 2
im = pylab.imread(img_dir+r"\bunny.png")
im = skimage.color.rgb2gray(im).astype(np.float)
# ②  1D高斯低通滤波器的时域和频域图像
filterX = scipy.signal.gaussian(M=im.shape[0],std=sigma) # x方向的正态分布滤波器 一维数组
filterY = scipy.signal.gaussian(M=im.shape[1],std=sigma)
# filterX_shift = list(filterX.copy())
# filterX_shift.reverse()
plt.plot(filterX,label='filter')
plt.plot(scipy.fftpack.fft(np.where(filterX<=0,0.01,filterX)).real,label='filter_freq')
plt.title("Gauss1D_TF_Charts",size=16)
font = {'family':'Times New Roman','weight':'normal','size':14}
plt.legend(loc="upper right",prop=font),plt.show()
# ③ 手动构建2D高斯低通滤波器
filter = np.outer(filterX,filterY) # 计算两个向量的外积 手动生成二维正态滤波器
print("滤波器最大值点坐标为：",np.unravel_index(np.argmax(filter),filter.shape)) # (109, 109)
shift_filter = scipy.fftpack.ifftshift(filter)
print("滤波器最大值点坐标为：",np.unravel_index(np.argmax(shift_filter),shift_filter.shape)) # (0, 0)
assert filter.shape == im.shape # 滤波器、输入图像形状相同
# ④ 分别对两个输入得到频域下的输出 （FFT之前时域的坐标系要求原点在左上方,变为频域后再进行平移到中心位置）
im_freq = scipy.fftpack.fft2(im)
filter_freq = scipy.fftpack.fft2(shift_filter)
# ⑤ 应用卷积定理 在频域进行乘积得到输出
out_freq = im_freq * filter_freq
assert filter_freq.shape == out_freq.shape # 滤波器、输出图像的频域形状相同
# ⑥ 反变换得到时域输出图像
out = scipy.fftpack.ifft2(out_freq).real
# ⑦ 计算im_freq,filter_freq,out_freq的频谱 只需要先平移然后取实部或者转为整型即可
def return_spectrum(input_freq):
    input_freq_shift = scipy.fftpack.fftshift(input_freq)
    input_spectrum = input_freq_shift.astype(int)
    # 根据条件当input_spectrum<=0 避免0除则给定0.01
    return 20 * np.log10(np.where(input_spectrum <= 0. ,0.01, input_spectrum ))
im_spectrum = return_spectrum(im_freq)
filter_spectrum = return_spectrum(filter_freq)
out_spectrum = return_spectrum(out_freq)
# ⑧ 2D高斯低通滤波器的时域和频域图像、输入、输出的时域和频域图像 6+4=10张图像
img_combine = [im,filter,out,im_spectrum,filter_spectrum,out_spectrum]
titles = ['im','filter','out','im_freq','filter_freq','out_freq']
idx = 1
for img ,title in zip(img_combine,titles):
    pylab.subplot(2,3,idx)
    pylab.imshow(img,cmap='coolwarm'),pylab.title(title)
    idx += 1
    pylab.colorbar()
pylab.subplots_adjust(hspace=0,wspace=0.01)
pylab.show()
# ⑨ 可以不手动构建高斯低通滤波器 直接使用函数fourier_gaussian(多维高斯傅立叶滤波器) 结果完全一致
# 输入数组与高斯核的傅立叶变换相乘
out_freq_ = scipy.ndimage.fourier_gaussian(im_freq,sigma=sigma)# 函数对图像的频域进行应用高斯滤波
fig,(ax1,ax2)=pylab.subplots(1,2)
ax1_fig = ax1.imshow(return_spectrum(out_freq_),cmap='coolwarm'),ax1.set_title("out_freq_")
ax2_fig = ax2.imshow(scipy.fftpack.ifft2(out_freq_).real,cmap='coolwarm'),ax2.set_title("out_")
# 使用图和坐标轴分离的方式需要得到返回值并指定坐标轴ax,进行绘制
fig.colorbar(ax1_fig[0],ax=ax1),fig.colorbar(ax2_fig[0],ax=ax2),pylab.show()
# ⑩ 使用不同的滤波器
# fourier_uniform 多维均匀傅立叶滤波器(盒核) 输入数组与给定大小的盒子的傅立叶变换相乘
# fourier_ellipsoid 多维椭球傅立叶滤波器(椭球核) 输入数组与给定大小的椭球的傅立叶变换相乘
out_freq__ = scipy.ndimage.fourier_uniform(im_freq,size=sigma)
out_freq___ = scipy.ndimage.fourier_ellipsoid(im_freq,size=sigma)
outs = [scipy.fftpack.ifft2(out_freq__),scipy.fftpack.ifft2(out_freq___)]
out_freqs = [out_freq__,out_freq___]
titles = [["out_freq_uniform","out_uniform"],["out_freq_ellipsoid","out_ellipsoid"]]
idx = 1
for freq , ou , title in zip(out_freqs,outs,titles) : # 没有绘制这两种滤波器的时域和频域因为都不知道
    pylab.subplot(2,2,idx),pylab.imshow(freq.real,cmap='coolwarm'),pylab.title(title[0]),pylab.colorbar()
    pylab.subplot(2,2,idx+1),pylab.imshow(ou.real,cmap='coolwarm'),pylab.title(title[1]),pylab.colorbar()
    idx += 2
pylab.show()
# 2）三维高斯低通滤波器 共10个图像
def plot_surface(array,freq,titles,allfreq=False) :
    def prepare(array):
        # x, y = np.mgrid[-2:2:0.01, -2:2:0.01]
        # z = (1 / 2 * np.pi * sigma ** 2) * np.exp(-(x ** 2 + y ** 2) / 2 * sigma ** 2)
        if allfreq : # 绘制2个频谱图时先进入此函数array是complex类型的
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
# plot_surface(im,im_freq,titles=["im","im_freq"]) # 输入图像的3D时域和3D频域
# plot_surface(filter,filter_freq,titles=["filter","filter_freq"]) # gauss卷积核的3D时域和频域(其他两个频域时域都不知道)
plot_surface(out,out_freq_,titles=["out_gauss","out_freq_gauss"]) # 输出图像的3D时域和频域（gauss） out_freq和out_freq_是相同的
# plot_surface(out_freq__,out_freq___,titles=["out_freq_uniform","out_freq_ellipsoid"],allfreq=True) # 输出图像的3D时域（uniform，ellipsoid）
# plot_surface(outs[0],outs[1],titles=["out_uniform","out_ellipsoid"],allfreq=True)

#%% （2）卷积定理的应用---直接完成
im_out = scipy.signal.fftconvolve(in1=im,in2=filter,mode='same')
pylab.subplot(121),pylab.imshow(im_out),pylab.title("直接输出")
pylab.subplot(122),pylab.imshow(out),pylab.title("间接输出"),pylab.show()
#%% （3）时域卷积和频域卷积的计算速度
def decorator(func):
    def wrapper(im_,filter_,fft_=None,mode_='same',hh="hello"):
        # 可以重新定义参数,增加参数(一般是继承原有参数变量,这里更改是为了区分)
        print(hh)
        func(in1=im_, in2=filter_, mode=mode_)
    return wrapper
func_wrapper = decorator(scipy.signal.fftconvolve) # 得到1个函数
a = func_wrapper(im,filter) # 函数依然能够计算a且新增了功能输出hello

#%%
def wrapper_convolve(func,im,filter,mode='same'):
    # 闭包函数：函数内部定义的函数,引用了外部变量但非全局变量
    # python装饰器本质是一个函数，可让其他函数不需要做任何变动增加额外的功能
    # 装饰器的返回值也是一个函数对象，可以理解为函数的指针
    # 输入外部函数(非函数调用)--->装饰器--->被闭包函数修饰--->返回装饰后的函数(非函数调用)
    # 实际上就是使用闭包函数将输入函数重写返回
    def wrappered_convolve():
        result = func(im, filter, mode)
        print(result.shape)
        # return func(im,filter,mode)
    return wrappered_convolve
wrapped_convolve = wrapper_convolve(scipy.signal.convolve,im=im,filter=filter)


#%%
wrapped_fftconvolve = wrapper_convolve(scipy.signal.fftconvolve,im=im,filter=filter)
time_1 = timeit.repeat(stmt=wrapped_convolve, number=1, repeat=100)
time_2 = timeit.repeat(stmt=wrapped_fftconvolve, number=1, repeat=100)
box = pylab.boxplot([time_1,time_2],patch_artist=True)
for patch ,color in zip(box["boxes"],["cyan","pink"]):
    patch.set_facecolor(color)
pylab.xticks(np.arange(3),("","convolve","fftconvolve"),size=15)
pylab.yticks(fontsize=15)
pylab.xlabel("scipy.signal.method",size=15)
pylab.ylabel("time coss",size=15)
pylab.show()

