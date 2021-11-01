#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 逐点强度变换（像素转换）.py
@Author : chenbei
@Date : 2021/9/6 8:28
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
from matplotlib.font_manager import FontProperties
import numpy as np
import numpy
import os
import skimage.io , skimage.color , skimage.exposure ,skimage.data ,\
    skimage.restoration ,skimage.measure,skimage.util
import skimage
import PIL
from PIL import Image , ImageEnhance
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
def plot_rgb_hist(im,thresold=None,y_scale=False,title=None,floyd_steinberg=False,
                  grey=False ,greyplot=False ,greyhist=False,halftone=False):
    # 分开数组格式还是PIL对象 ,默认是PIL对象
    if not isinstance(im , PIL.Image.Image): # 与type的区别是会考虑继承关系 im、im_log同属于该父类
        im = skimage.img_as_ubyte(im) # fromarray不能直接转换浮点数组为PIL,应对对整数数组进行转换
        im = Image.fromarray(im) # 不是PIL对象将其转换为PIL对象
        # assert type(im) == PIL.PngImagePlugin.PngImageFile
    # 分开灰度图和彩色图
    if grey:
        if thresold is not None :
            if isinstance(thresold , int) :
                if thresold < 0 or thresold > 255 :
                    print("thresold should be in [0,255]")
                    return
            else:
                print("thresold should be int")
                return
            im = im.convert("L") # PIL对象
            if halftone :
                # 如果使用半色调技术 点处理前先加入均匀随机噪声
                im = np.array(im,dtype=np.int32) # ---> ndarray
                im += np.random.randint(-128,128,(im.shape[0],im.shape[1]))
                im = np.clip(im,0,255).astype(np.uint8)
                im = Image.fromarray(im) # ---> PIL
            im_ = im.point(lambda x: 0 if x < thresold else 255)  # 无论是否传入的是不是灰度图
            if floyd_steinberg :
                im_ = np.array(im).copy()
                for raw in range(im_.shape[0]):
                    for col in range(im_.shape[1]):
                        old_pix = im_[raw,col]
                        if old_pix > thresold :
                            new_pix = 255.
                        else:
                            new_pix = 0.
                        im_[raw,col] = new_pix # 这里为止与上述固定阈值法没有区别
                        quant_err = old_pix - new_pix # 替代值与原来存在误差
                        print(quant_err)
                        # 固定阈值法会强行忽略此误差,Floyd法较温和,会把误差逐个像素推加进行误差扩散
                        if (raw > 0) and (raw <im_.shape[0]-1) and (col <im_.shape[1]-1): # 注意边界
                            im_[raw + 1][col] = im_[raw + 1][col] + quant_err * 7 / 16 # 右方扩散系数 7/16
                            im_[raw - 1][col + 1] = im_[raw - 1][col + 1] + quant_err * 3 / 16  # 左下方扩散系数 3/16
                            im_[raw][col + 1] = im_[raw][col + 1] + quant_err * 5 / 16  # 下方扩散系数 5/16
                            im_[raw + 1][col + 1] = im_[raw + 1][col + 1] + quant_err * 1 / 16  # 右下方扩散系数 1/16
                im_ = np.asarray(im_,dtype=np.uint8)
            # print(list(np.array(im_).ravel()).count(0))
            # print(set(np.array(im_).ravel())) # {0,1}
            if greyhist :
                pylab.gray()
                pylab.style.use('ggplot')
                pylab.hist(np.asarray(im_).ravel(),bins=256,range=(0,256),color='r',alpha=0.8)
                pylab.xlabel('gray pixel value'),pylab.ylabel('frequency')
                pylab.grid(None)
                pylab.title('gray_pixel_value_distribution chart')
                if y_scale:
                    pylab.yscale('log', basey=10)  # log10(y)
                if title:
                    pylab.title(title, size=12)
                pylab.show()
            if greyplot :
                plot_image(np.asarray(im_))
        else:
            print("thresold shouldn't be None")
            return
        return # 灰度图不再执行后边
    # 分开三通道和四通道
    try :
        im_r, im_g, im_b = im.split()
    except :
        im_r, im_g, im_b, _ = im.split()
    # 将图像转换为 8 位无符号整数格式
    im_r, im_g, im_b = skimage.img_as_ubyte(im_r),skimage.img_as_ubyte(im_g),skimage.img_as_ubyte(im_b)
    pylab.style.use('ggplot')
    channels = [im_r,im_g,im_b]
    colors = ['r','g','b']
    for channel,color in zip(channels,colors) :
        # bins将直方图转换的更细致,边缘更平滑而非直角 ravel展平二维
        pylab.hist(np.array(channel).ravel(),range=(0,256),bins=256,alpha=0.5,color=color)
        pylab.xlabel('rgb pixel value',size=12),pylab.ylabel('frequency',size=12)
    pylab.grid(None)
    pylab.title('rgb_pixel_value_distribution chart')
    if y_scale:
        pylab.yscale('log',basey=10) # log10(y)
    if title :
        pylab.title(title,size=12)
    pylab.show()
#%% （1）对数变换 ： s = T (r) = c*log(1+r) : 255*log(1+i/255)
im = Image.open(img_dir+"\parrot.png")

plot_rgb_hist(im)
im_log = im.point(lut = lambda x : 255 * np.log(1+x/255))
plot_rgb_hist(im_log) # 分布更集中
# a = np.array(im_log)
# b = np.array(im)
# c = 255*np.log(1+b/255) # b 和 c 结果是一样的,只是没取整
#%% （2）幂律变换 s = c * r^γ
im = pylab.imread(img_dir+"\panda.png")
gamma = 2
im_pow = im ** gamma
plot_rgb_hist(im_pow)
plot_rgb_hist(im)
#%% （3）对比度拉伸 :关于像素值的线性缩放函数
# 1）自定义拉伸函数+PIL.point()
im = Image.open(img_dir+'\cheetah.png')
# plot_rgb_hist(im) # 低对比度图像 高像素值分布较少
# plot_image(np.asarray(im))
def stretch_func(c):
    # 22950/255=90
    return 10 if c < 70 else (200 if c > 150 else (255*c-22950)/50)
im_stretch = im.point(stretch_func)
# plot_rgb_hist(im_stretch,y_scale=True) # 高对比度,0-255均有分布,由于0像素过于突出,故使用对数坐标便于查看
# plot_image(np.asarray(im_stretch))
# 2）PIL.ImageEnhance
def image_enhance(im,factors) :
    imgContrast = ImageEnhance.Contrast(im)  # 此类可用于控制图像的对比度 1.0原始图像,0.0灰度图
    for factor in factors :
        imgCore = imgContrast.enhance(factor=factor).getdata() # Image对象-->ImagingCore对象--->查看bands、size属性
        # np.asarray(imgCore)得到二维数组,列含义为通道,即bands , 需要将其调整形状 PIL对象图片width和height对应数据的列和行
        img_contrast = np.reshape(np.asarray(imgCore).astype(np.uint8),(imgCore.size[1],imgCore.size[0],imgCore.bands))
        plot_rgb_hist(img_contrast,y_scale=True,title=f'factor = {factor}')
        # plot_image(np.asarray(img_contrast))
factors = np.arange(0,100,20)
image_enhance(im,factors)
#%% （4）二值变换
# 1）固定阈值的二值化
im = Image.open(img_dir+'\messi.png')
thresolds = [0,50,100,150,200,250]
for thresold in thresolds:
    plot_rgb_hist(im,grey=True,thresold=thresold,y_scale=True,greyhist=False,greyplot=False,
                  title=f"thresold = {thresold}")
# 2）半色调二值化
for thresold in thresolds:
    plot_rgb_hist(im,grey=True,thresold=thresold,y_scale=True,greyhist=False,greyplot=False,
                  title=f"thresold = {thresold}",halftone=True)
# 3）基于误差扩散的Floyd-Steinberg抖动
for thresold in thresolds:
    print(thresold)
    plot_rgb_hist(im,grey=True,thresold=thresold,y_scale=True,greyhist=False,greyplot=True,
                  title=f"thresold = {thresold}",floyd_steinberg=True)





