#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 离散傅里叶变换.py
@Author : chenbei
@Date : 2021/8/31 16:15
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
from matplotlib.font_manager import FontProperties
import numpy as np
import os
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
import  scipy.fftpack
import numpy.fft
import matplotlib.pylab as pylab
root = os.path.join(os.getcwd(),"ImageProcessing")
img_dir = os.path.join(root,"images")
def signaltonoise(array):
    array = np.asanyarray(array)# 转换为array格式
    m = array.mean()
    sd = array.std()
    # where(condition, [x, y]) 防止出现0除 图片方差为0则返回0
    return np.where(sd == 0, 0, m / sd)
#%% （1）使用scipy.fftpack计算
im = np.array(Image.open(img_dir +  "/rhino.jpg").convert(mode='L'))
snr_orginal = signaltonoise(im)
freq = scipy.fftpack.fft2(im)
im1 = scipy.fftpack.ifft2(freq).real # 使用实部信息重建图像
snr_freq = signaltonoise(im1)
assert np.allclose(im,im1) == True # 在相对和绝对容差内相等返回True
# 绘制频谱图
freq2 = scipy.fftpack.fftshift(freq) # 将零频率分量移动到频谱的中心,此时边角的低频分量集中在中心区域
# 原点由(0,0)变为(160,240)
print(freq[0][0],freq2[321//2][481//2]) # F(0,0)=2250万,虚部基本忽略不计,该值也叫直流系数DC
print(freq[-1,-1],freq[-1,0],freq[0,-1]) # 数量级在百万左右 低于F(0,0),虚部不可忽略
pylab.imshow((20*np.log(0.1+freq2)).astype(dtype=int)) # 由于数值巨大需要取对数方便显示,20log具有物理意义转为dB astype是转为实数
pylab.show()
A = 20*np.log(0.1+freq)
B = A.astype(int)
print(freq[-1,-1],A[-1,-1],B[-1,-1])
#%% （2）使用numpy.fft计算
im = np.array(Image.open(img_dir +  "/house.png").convert(mode='L'))
freq = numpy.fft.fft2(im)
im1 = numpy.fft.ifft2(freq).real # 使用实部信息重建图像
snr_freq1 = signaltonoise(im1)
assert np.allclose(im,im1) == True
freq1 = numpy.fft.fftshift(freq) # 平移
pylab.subplot(121),pylab.imshow(20*np.log(0.01+np.abs(freq1))),pylab.title("FFT Spectrum Magnitude",size=12)
pylab.subplot(122),pylab.imshow(np.angle(freq1)),pylab.title("FFT Phase",size=12),pylab.show()
#%% （3）重建图像失败的问题
# ① 读取图像
im1 = np.array(Image.open(img_dir +  "/house.png").convert(mode='L'))
im2 = np.array(Image.open(img_dir +  "/house2.png").convert(mode='L'))
# ② 时域-->频域
freq1 = numpy.fft.fft2(im1)
freq2 = numpy.fft.fft2(im2)
# ③ 重组频域 图像1的实部和图像2的虚部,图像1的虚部和图像2的实部进行组合
freq1_ = np.vectorize(pyfunc=complex)(freq1.real,freq2.imag)
freq2_ = np.vectorize(pyfunc=complex)(freq2.real,freq1.imag)
# ④ 频域-->时域
im1_ = numpy.fft.ifft2(freq1_).real
im2_ = numpy.fft.ifft2(freq2_).real
# ⑤ 可视化比较
# np.clip(im1_,0,255) 限制范围
pylab.subplot(221),pylab.imshow(im1,cmap='gray'),pylab.title("house1",size=12)
pylab.subplot(222),pylab.imshow(im2,cmap='gray'),pylab.title("house1",size=12)
pylab.subplot(223),pylab.imshow(np.clip(im1_,0,255),cmap='gray'),pylab.title("reconstructed house1",size=12)
pylab.subplot(224),pylab.imshow(np.clip(im2_,0,255),cmap='gray'),pylab.title("reconstructed house2",size=12),pylab.show()

#%%
func = np.vectorize(pyfunc=complex) # 本质上是一个迭代器类似于map(func,*iterables)








