#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 利用导数和滤波器边缘检测.py
@Author : chenbei
@Date : 2021/9/8 11:44
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
from matplotlib.font_manager import FontProperties
import numpy as np
import os
import skimage.io , skimage.color , skimage.filters,skimage.feature
import skimage
from PIL import Image , ImageFilter
import  scipy.ndimage ,scipy.misc , scipy.fftpack ,scipy.signal
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
def plot_im1_im2(im1,im2,title1="original",title2="reconstruction",colorbar=False):
    fig = plt.figure()
    ax1 = fig.add_subplot(121)
    ax2 = fig.add_subplot(122)
    map1 = ax1.imshow(im1)
    map2 = ax2.imshow(im2)
    if colorbar :
        fig.colorbar(map1,ax=ax1)
    ax1.set_title(title1,size=12),ax2.set_title(title2,size=12)
    ax1.set_axis_off(),ax2.set_axis_off()
    fig.show()
def plot_ax(im,ax,title):
    ax.imshow(im),ax.set_title(title,size=12),ax.set_axis_off()
im = skimage.color.rgb2gray(skimage.io.imread(img_dir+r"\tajmahal.jpg"))
#%% （1）基于skimage.filters
# 1）sobel边缘检测
im_x = skimage.filters.sobel_h(im) # 使用了水平右掩膜
im_y = skimage.filters.sobel_v(im) # 使用了垂直下掩膜
im_xy = skimage.filters.sobel(im) # 2个方向均使用
imgs = [im,im_x,im_y,im_xy]
fig ,axes = pylab.subplots(2,2)
axes = axes.flatten()
titles = ['original','$grad_x$','$grad_y$',r'$grad|_{xy}$']
for img ,axe,title in zip(imgs,axes,titles):
    plot_ax(img,axe,title)
fig.show()
# 2）比较sobel,prewitt,scharr,roberts
im_sobel = skimage.filters.sobel(im)
im_roberts = skimage.filters.roberts(im)
im_prewitt = skimage.filters.prewitt(im)
im_scharr = skimage.filters.scharr(im)
imgs = [im_sobel,im_roberts,im_prewitt,im_scharr]
fig ,axes = pylab.subplots(2,2)
axes = axes.flatten()
titles = ['sobel','roberts','prewitt','scharr']
for img ,axe,title in zip(imgs,axes,titles):
    plot_ax(img,axe,title)
fig.show()
# （3）canny强边缘检测 : 比对不同sigma和固定sigma添加噪声的影响
im_gaussblur = scipy.ndimage.gaussian_filter(im,4)
im_addnoise = im_gaussblur +  0.05 * np.random.random(im_gaussblur.shape)
im_canny_1 = skimage.feature.canny(im)
im_canny_3 = skimage.feature.canny(im,sigma=3)
im_canny_3_noise = skimage.feature.canny(im,sigma=3)
plot_im1_im2(im_canny_1,im_canny_3,'candy $\sigma=1$','candy $\sigma=3$')
plot_im1_im2(im_canny_3,im_canny_3_noise,'candy $\sigma=3$','candy_noise $\sigma=3$')
#%%
# （2）基于scipy.ndimage
# LoG和DoG滤波器 : DoG是对LoG的近似，采用指定sigma的差分计算而非二阶导数
# 1）自定义核
def LoG(k=12, sigma=3) :
    ''':arg k : 坐标轴半径，或者说点坐标(x,y)的上下限绝对值
       :arg sigma : 方差
       :return LoG Kernel
       LoG(x,y) = -1/( pi * σ^4) * ( 1 - (x^2+y^2)/2σ^2 ) * exp( - (x^2+y^2)/2σ^2 )
       LoG(x,y) = c * (1 + t) * e^t'''
    n = 2 * k + 1 # 半径为k,整个核的大小应当是n,加上原点1个
    kernel = np.zeros((n,n))
    for i in range(n) :
        for j in range(n):
            x , y = i - k , j - k # 由于i,j是正数,需要作个变换才是(x,y)坐标 如i=0,j=0，对应坐标(-12,12)
            c = - 1/(np.pi * sigma**4) # 高斯二阶导数推导表达式的常系数
            t = - ( x**2 + y**2 ) / (2*sigma**2)
            kernel[i,j] = c * (1+t) * np.exp(t)
    # print(np.max(np.abs(kernel)),np.sqrt(kernel**2).sum())
    return np.round( kernel / np.sqrt(kernel**2).sum() , 3 )
def DoG(k=12, sigma=3) :
    ''':arg k : 坐标轴半径，或者说点坐标(x,y)的上下限绝对值
       :arg sigma : 方差
       :return LoG Kernel
       DoG(x,y) ≈ Gσ1(x,y) - Gσ2(x,y) 其中 σ1 = sqrt(2)*σ，σ2 = σ/ sqrt(2)
       G(x,y) = 1 / ( 2pi*σ^2 ) * exp( - (x^2+y^2)/2σ^2 )
       DoG(x,y) = c1 * e^t1 - c2 * e^t2 '''
    n = 2 * k + 1 # 半径为k,整个核的大小应当是n,加上原点1个
    s1 , s2  = sigma * np.sqrt(2) , sigma / np.sqrt(2)
    kernel = np.zeros((n,n))
    for i in range(n) :
        for j in range(n):
            x , y = i - k , j - k # 由于i,j是正数,需要作个变换才是(x,y)坐标 如i=0,j=0，对应坐标(-12,12)
            c1 ,c2 =  1/(2 * np.pi * s1**2),1/(2 * np.pi * s2**2) # 两个高斯核表达式的常系数
            t1 , t2 = - ( x**2 + y**2 ) / (2*s1**2) , - ( x**2 + y**2 ) / (2*s2**2)
            kernel[i,j] = c1 * np.exp(t1) - c2 * np.exp(t2)
    return np.round( kernel / np.sqrt(kernel**2).sum() , 3 )
LoG_Kernel = LoG()
DoG_Kernel = DoG()
im_LoG = scipy.signal.convolve2d(im,LoG_Kernel)
im_DoG = scipy.signal.convolve2d(im,DoG_Kernel)
plot_im1_im2(np.clip(LoG_Kernel,0,1),np.clip(im_LoG,0,1),title1="LoG",title2="im_LoG",colorbar=True)
plot_im1_im2(np.clip(DoG_Kernel,0,1),np.clip(im_DoG,0,1),title1="DoG",title2="im_DoG",colorbar=True)
# 2）直接使用函数 scipy.ndimage.gaussian_lapalce()高斯拉普拉斯
def zero_crossing(im) :
    im = im.copy()
    im_binary = np.asarray(Image.fromarray(im,mode='1')).astype(int) # 二值图用来寻找位置
    raw , col = im_binary.shape[0],im_binary.shape[1]
    for i in range(raw): # 每行
        for j in range(col): # 每列
            isbeyond = [i>0,i+1<raw,j+1<col,j>0] # 边界行列不进行检测
            isnotbeyond = np.all(isbeyond) # 全部True返回True
            if im_binary[i,j] == 1 : # 边缘只可能处于强度为1的位置
                #print(isnotbeyond)
                if isnotbeyond :
                    top,bottom = im_binary[i-1,j],im_binary[i+1,j]
                    left,right = im_binary[i,j-1],im_binary[i,j+1]
                    top_right , bottom_left = im_binary[i-1,j+1] , im_binary[i+1,j-1]
                    top_left , bottom_right = im_binary[i-1,j-1],im_binary[i+1,j+1]
                    near_pixels = [top,bottom,left,right,top_left,bottom_left,top_left,bottom_right]
                    if 0 in near_pixels : # 只要相邻元素任一个为0则判定为边界
                        pass # 该元素不变仍为1 筛选出属于边界的像素位置
                    else:
                        # print(i, j)
                        im[i,j] = 0 # 不是边界置0
                else:
                    pass
            else:
                pass
    return im
def plot_guass_laplace(zero_cross=False):
    fig ,axes = pylab.subplots(3,3)
    axes = axes.flatten()
    sigmas = range(1,10)
    titles = ['LoG $\sigma='+str(x)+'$' for x in range(1,10)]
    for axe,title,sigma in zip(axes,titles,sigmas):
        im_guasslaplace = scipy.ndimage.gaussian_laplace(im, sigma=sigma)
        if zero_cross :
            # 使用零交叉技术
            im_zero = zero_crossing(np.clip(im_guasslaplace, 0, 1))
            print("使用zero_cross前后像素相等的个数",np.count_nonzero((im_zero == im_guasslaplace).astype(int)))
            plot_ax(np.clip(im_zero,0,1),axe,"zero cross "+title)
        else:
            plot_ax(np.clip(im_guasslaplace, 0, 1), axe, title)
    fig.show()
plot_guass_laplace(zero_cross=True)
plot_guass_laplace()
#%% （3）基于PIL.ImageFilters
im = Image.open(img_dir+r"\umbc.png")
fig ,axes = pylab.subplots(1,3)
axes = axes.flatten()
filters = [ImageFilter.FIND_EDGES,ImageFilter.EDGE_ENHANCE,ImageFilter.EDGE_ENHANCE_MORE]
titles = ['find_edge','edge_enhance','edge_enhance_more']
for axe,title,filter in zip(axes,titles,filters):
    im_filtered = im.filter(filter) # PIL滤波后的使用uint8
    im_filtered = np.asarray(im_filtered)
    plot_ax(np.clip(im_filtered,0,255),axe,title)
fig.show()
