#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 频域滤波.py
@Author : chenbei
@Date : 2021/9/1 13:23
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
from matplotlib.font_manager import FontProperties
import numpy as np
import os
from PIL import Image
import skimage.transform
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
def signaltonoise(array):
    array = np.asanyarray(array)# 转换为array格式
    m = array.mean()
    sd = array.std()
    # where(condition, [x, y]) 防止出现0除 图片方差为0则返回0
    return np.where(sd == 0, 0, m / sd)
#%%
im = Image.open(img_dir+"\\rhino.jpg").convert("L")
print("im width %d  im height %d" % (im.width,im.height))
im = np.array(im)
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
freq = scipy.fftpack.fft2(im)
# （1）高通滤波器HPF
# 1）展现原始图像和频谱
# plot_image(im,scipy.fftpack.fftshift(freq),allplot=True)
# 2）阻断低频分量：中心位置
freq_shift = scipy.fftpack.fftshift(freq.copy())
height , width = freq_shift.shape
height , width = int(height/2) , int(width/2) # 寻找中心区域(低频分量区域)
radius = 10 # 阻断半径
freq_shift[height-radius : height+radius , width-radius :width+radius] =0  # 阻断低频区域(30×30置0)
# plot_image(freq=freq_shift,isfreq=True)
# 3）重建图像对比
im_re = scipy.fftpack.ifft2(scipy.fftpack.ifftshift(freq_shift)).real # 重建图像需把坐标系变回左上方
im_re = np.clip(im_re,0,255) # 限制范围
 # plot_image(im=im_re)
# 4）不同截止频率对图像的影响
freq_list = list(range(1,max(im.shape)//20)) # 一般截止频率选择图像大小的1/20以内比较好
def cut_off_freq_snr(im,freq_list,filter='low'):
    snr_list = []
    freq = scipy.fftpack.fft2(im)
    height, width = freq.shape
    height , width = height//2 , width//2
    assert len(freq_list) >= 5 # 至少5个截止频率以上
    if len(freq_list) % 5 == 0 :
        row = len(freq_list) // 5 # / 会出现float应使用//5
    else:
        row = len(freq_list) // 5 + 1
    assert type(row) == int
    filters = ['low','high']
    assert filter in filters
    for radius in freq_list :
        assert radius >= 1 # radius从1开始
        freq_shift = scipy.fftpack.fftshift(freq.copy())  # copy避免平移冲突 high + low
        freq_shift[height - radius: height + radius, width - radius:width + radius] = 0 # only high
        im_re = scipy.fftpack.ifft2(scipy.fftpack.ifftshift(freq_shift)).real # high pass
        if filter=='low':
            freq_shift_low = scipy.fftpack.fftshift(freq.copy()) # high + low
            freq_shift_low -= freq_shift # only low
            im_re = scipy.fftpack.ifft2(scipy.fftpack.ifftshift(freq_shift_low)).real # low pass
        im_re = np.clip(im_re, 0, 255)
        snr_list.append(signaltonoise(im_re))
        fig = pylab.figure("HPF-COF Images")
        ax = fig.add_subplot(row,5,radius)
        ax.imshow(im_re, cmap='gray') ,ax.axis('off'),ax.set_title("COF = %d Hz" % (radius),size=10)
    pylab.subplots_adjust(hspace=0.01,wspace=0.01)
    pylab.show()
    return snr_list
def plot_snr_cof(snr_list,freq_list):
    pylab.plot(freq_list,snr_list)
    pylab.title("SNR-COF Charts")
    font = {'family': 'Times New Roman', 'weight': 'normal', 'size': 11}
    pylab.xlabel("cut off frequency",fontdict=font),pylab.ylabel("snr",fontdict=font)
    pylab.show()
# snr_list = cut_off_freq_snr(im,freq_list,filter='high')
# plot_snr_cof(snr_list,freq_list)
#%%
# （2）低通滤波器LPF
addr = r"C:\Users\chenb\Desktop\2021.8.·25备份\我和宝宝的恋爱相册\望京公园\合照\0.jpg"
# im = np.array(Image.open(img_dir+"\\lena.jpg").convert("L"))
im = np.array(Image.open(addr).convert("L"))
# 1）使用低通滤波函数实现 scipy.ndimage.fourier_gaussian
# 此函数的应用在卷积定理和频域高斯模糊.py文件已经使用
# 2）手动阻断 置零高频分量后再取负片
freq_list = list(range(1,max(im.shape)//200))
snr_list = cut_off_freq_snr(im,freq_list,filter='low')
plot_snr_cof(snr_list,freq_list)
#%%
# （3）带通滤波器BPF DoG高斯差分核
im = pylab.imread(img_dir+"\\tiger.jpg")
im = skimage.img_as_float(im) # [0,1]
x = np.linspace(-20,20,300)
sigma1  ,sigma2 = 10 , 1/np.sqrt(10)
# 没有直接的函数可以实现,需要自定义滤波核,使用scipy.signal.fftconvolve
kernel1 = np.exp(-0.5 * x**2 / sigma1**2) /( np.sqrt(2*np.pi) * sigma1)# 生成一维高斯核
kernel1 /= np.trapz(kernel1) # 使用复合梯形规则沿给定轴积分,默认dx=1时结果等于(首元素+尾部元素)/2 + 其他元素和
print("kernel sum = ",sum(kernel1))
print(np.trapz([1,4,6])) # (1+4)*1/2+(4+6)*1/2 = 4 + 1/2 + 4/2 = 7.5
print(np.newaxis) # 1个常数 就是None
guass_kernel_1 = kernel1[:,np.newaxis] * kernel1[None,:] # kernel[:,np.newaxis]可以将(15,)变成(15,1) high filter
kernel2 = np.exp(-0.5 * x**2 / sigma2**2)/( np.sqrt(2*np.pi) * sigma2)
plt.plot(np.arange(-len(kernel2)//2,len(kernel2)//2),kernel2,label="high filter")
plt.plot(np.arange(-len(kernel1)//2,len(kernel1)//2),kernel1,label="low filter")
plt.legend(),plt.show()
kernel2 /= np.trapz(kernel2)
guass_kernel_2 = kernel2[:,np.newaxis] * kernel2[None,:] # low filter
DoGKernel = guass_kernel_1[:,:,None] - guass_kernel_2[:,:,None] # band filter
im_re = scipy.signal.fftconvolve(im,DoGKernel,mode='same')
plot_image(im_re)
#%%
# （4）带阻滤波器、陷波滤波器 BSF
im = pylab.imread(img_dir+"\\parrot.jpg")
im = np.mean(im,axis=-1) / 255 # 按通道方向平均转为灰度图
im_freq= numpy.fft.ifftshift(numpy.fft.fft2(im))
plot_image(im=im,freq=im_freq,allplot=True)
im_noise = im.copy()
for col in range(im_noise.shape[1]) :
    # 按行添加噪声
    im_noise[:,col] += np.cos(0.1*np.pi*col)
im_noise_freq = numpy.fft.ifftshift(numpy.fft.fft2(im_noise))
plot_image(im=im_noise,freq=im_noise_freq,allplot=True)
# 观察到水平线175左右的噪声比较明显,故创造1个竖直范围在170-176,水平范围[0:220][230:486]的两个矩形区域
# 中心区域不要滤除,只能怪中心点为(181,243)
im_noise_freq[180:183,:235] = im_noise_freq[180:183,245:] = 0
im_re_noise = numpy.fft.ifft2(numpy.fft.ifftshift(im_noise_freq))
im_re_noise = np.clip(im_re_noise,0,1)
plot_image(im=im_re_noise,freq=im_noise_freq,allplot=True,isre=True)
#%%


















