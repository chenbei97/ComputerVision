#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 金字塔融合图像.py
@Author : chenbei
@Date : 2021/9/8 11:44
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
from matplotlib.font_manager import FontProperties
import numpy as np
import os
import skimage.io , skimage.color , skimage.exposure ,skimage.data ,\
    skimage.restoration ,skimage.measure,skimage.util,skimage.metrics,\
    skimage.filters,skimage.feature,skimage.transform
import skimage
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
def plot_im1_im2(im1,im2,title1="original",title2="reconstruction"):
    fig = plt.figure()
    plt.gray()
    ax1 = fig.add_subplot(121)
    ax2 = fig.add_subplot(122)
    ax1.imshow(im1),ax2.imshow(im2)
    ax1.set_title(title1,size=12),ax2.set_title(title2,size=12)
    ax1.set_axis_off(),ax2.set_axis_off()
    fig.show()
def plot_ax(im,ax,title):
    ax.imshow(im),ax.set_title(title,size=12),ax.set_axis_off()
def get_guass_pyramid(im) :
    guassian_pyramid = []
    guassian_pyramid.append(im)
    while min(im.shape[0:2]) != 1 :
        im = skimage.transform.pyramid_reduce(im, sigma=3,multichannel=True)  # 先平滑然后下采样图像
        guassian_pyramid.append(im)
    return guassian_pyramid
def get_laplace_pyramid(guassian_pyramid) :
    '''
    公式 : L(i) = G(i) - Resize(Smooth(Up(G(i+1)))) i = -2,...,1,0
    注 : G(i+1).shape < G(i).shape G(10)[1×1]<G(9)[2×2]<G(8)[3×3]<...<G(1)<G(0) 底层---->高层
    对于负索引 : G(-1)<G(-2)<G(-3)<....<G(-11) 底层---->高层
    公式等价于 : ∵ G(i) = Up(G(i+1)) ∴ L(i) = Up(G(i+1)) - Resize(Smooth(Up(G(i+1))))

    L(-1) = G(-1)
    L(-2) = G(-2) - RSU(G(-1))
    L(-3) = G(-3) - RSU(G(-2))
    ...
    L(-10) = G(-10) - RSU(G(-9)) <=> L(1) = G(1) - RSU(G(2))
    L(-11) = G(-11) - RSU(G(-10)) <=> L(0) = G(0) - RSU(G(1))

    伪代码:
    创建金字塔容器
    定义拉普拉斯当前层为高斯底层并加入金字塔底层
    while 拉普拉斯当前层形状 ！= 高斯顶层形状 :
          循环迭代
          拉普拉斯当前层 = 高斯当前层 - 调整尺寸[拉普拉斯当前层的下层上采样平滑,高斯当前层尺寸]
          更新拉普拉斯当前层索引
          添加当前层至金字塔容器
    返回金字塔容器
    '''
    laplace_pyramid = [[] for _ in range(len(guassian_pyramid))]
    layer_bottom , layer_top = guassian_pyramid[-1] ,guassian_pyramid[0] # G(-1), G(0)
    laplace_pyramid[-1] = layer_bottom # L(-1)=G(-1) <=> L(10)=G(10)
    i = -1 # 计数
    layer_current  = layer_bottom
    while layer_current.shape != layer_top.shape :
        # # 开始对高斯金字塔-1层上采样并平滑 SU(G(-1))
        SU = skimage.transform.pyramid_expand(guassian_pyramid[i],multichannel=True)
        print(np.max(SU),np.min(SU))
        # 调整层图片大小与高斯金字塔的-2层保持一致,这一步是while循环终止的条件
        RSU = skimage.transform.resize(SU, guassian_pyramid[i-1].shape) # R [SU(G(-1))]
        # L(-2) = G(-2) - RSU(G(-1))
        layer_current = guassian_pyramid[i-1] - RSU
        i -= 1
        laplace_pyramid[i] = layer_current # -2,-3,...,
        print('layer'+str(i)+ '=layer'+str(len(guassian_pyramid)-np.abs(i)),layer_current.shape)
    return list(laplace_pyramid) # 返回的不要进行限制 否则重构不回图像
def plot_pyramid(im,laplace=False,multichannel=True,sigma=3):
    if laplace :
        im_laplace_generator = skimage.transform.pyramid_laplacian(im,downscale=2,sigma=sigma,multichannel=multichannel) # 返回一个迭代器
        im_pyramid = list(im_laplace_generator) # 存放了金字塔图像
        title = 'laplace pyramid'
    else:
        im_guass_generator = skimage.transform.pyramid_gaussian(im,downscale=2,sigma=sigma,multichannel=multichannel) # 返回一个迭代器
        im_pyramid = list(im_guass_generator) # 存放了金字塔图像
        title = 'guass pyramid'
    if len(im.shape) == 3 :
        raws , cols ,channels = im.shape
        im_new = np.zeros((raws , cols + cols // 2 , channels),dtype=np.double)
        im_new[:, :cols, :] = im_pyramid[0]  # 空图像的左边开始cols列放置原图像
    else:
        raws , cols  = im.shape
        im_new = np.zeros((raws , cols + cols // 2 ),dtype=np.double)
        im_new[:, :cols] = im_pyramid[0]
    current_raw = 0 # 当前行从第0行开始
    for p in im_pyramid[1:] :
        nraw , ncol = p.shape[:2] # 不返回通道数 使用[0:2]
        #print(p.shape[:2])
        #print(current_raw,nraw,ncol)
        if current_raw+nraw > raws :
            break
        else:
            if ncol > cols // 2 :
               p = p[:,:cols // 2] # 如果p的宽度大于了im_new扩展的宽度,只取p的前cols/2去填充
            im_new[current_raw : current_raw + nraw , cols : cols + ncol] = p # 当前行到当前图像占据的行,列不需要更改
            current_raw += nraw # 更改当前行位置
    fig = plt.figure()
    ax = fig.add_subplot()
    plot_ax(np.clip(im_new,0,1),ax,title=title)
    fig.show()
def reconstruct_image_only_by_laplace_pyramid(laplace_pyramid):
    '''
    L(i) = G(i) - Resize(Smooth(Up(G(i+1)))) i = -2,...,1,0
    根据公式只从拉普拉斯金字塔构建，已知L(i)求G(i)
    突破点在于拉普拉斯金字塔的最小分辨率和高斯金字塔相同,那么不需要引入高斯金字塔
    G(-1) = L(-1)
    G(-2) = L(-2) + RSU(G(-1))
    G(-3) = L(-3) + RSU(G(-2))
    ...
    G(-10) = L(-10) + RSU(G(-9)) <=> G(1) = L(1) + RSU(G(2))
    G(-11) = L(-11) + RSU(G(-10)) <=> G(0) = L(0) + RSU(G(0))

    伪代码:
    定义高斯当前层为拉普拉斯底层并加入金字塔底层
    while 高斯当前层形状 ！= 拉普拉斯顶层形状 :
          循环迭代
          高斯当前层 = 拉普拉斯当前层 + 调整尺寸[高斯当前层的下层上采样平滑,拉普拉斯当前层尺寸]
          更新高斯当前层索引
    返回高斯当前层
    '''
    pyramid = []
    maxidx = len(laplace_pyramid) - 1 # 12
    layer_current , layer_top = laplace_pyramid[-1],laplace_pyramid[0] # G(-1) = L(-1) <=> G(12) = L(12)
    i =  maxidx - 1 # 11
    print(maxidx)
    print("layer_current = ",layer_current[0,0,0])
    while  layer_current.shape != layer_top.shape :
        SU = skimage.transform.pyramid_expand(laplace_pyramid[i+1],multichannel=True) # SU = SU(G(12))
        RSU = skimage.transform.resize(SU,laplace_pyramid[i].shape) # RSU = Resize(SU,G(11).shape)
        #print('layer ' + str(i), layer_current.shape)
        print(i)
        layer_current = laplace_pyramid[i] +  RSU # G(-2) = L(-2) + RSU(G(-1)) <=> G(11) = L(11) + RSU(G(12))
        print("layer_current = " ,str(laplace_pyramid[i][0,0,0])+" + "+str(SU[0,0,0]))
        i -= 1
        pyramid.append(np.clip(layer_current,0,1))
    return list(reversed(pyramid))
#%% （1）高斯金字塔和拉普拉斯金字塔基于调用实现,两者都是向下采样
im = skimage.io.imread(img_dir+r"\apple.jpg")
plot_pyramid(im)
plot_pyramid(im,laplace=True)
#%% （2）自定义金字塔
# 拉普拉斯和高斯的最小分辨率图像是不同的，希望构建一个两者最小分辨率相同的金字塔
# 1）自定义高斯金字塔
im = skimage.img_as_float(skimage.io.imread(img_dir+r"\lena.jpg"))
guassian_pyramid = get_guass_pyramid(im)
# 2）自定义拉普拉斯金字塔(基于高斯金字塔构建)
laplace_pyramid = get_laplace_pyramid(guassian_pyramid)
print("最小分辨率是否完全相等",np.all(guassian_pyramid[-1] == laplace_pyramid[-1]))
for n in range(len(guassian_pyramid)) :
    plot_im1_im2(guassian_pyramid[n],np.clip(laplace_pyramid[n],0,1),title1='guass',title2='laplace')
# 3) 只通过拉普拉斯金字塔重建图像 即2）的逆过程
pyramid = reconstruct_image_only_by_laplace_pyramid(laplace_pyramid)
for i in range(len(pyramid)):
    plot_im1_im2(im,pyramid[i])
#%% （3）金字塔融合
melon = skimage.img_as_float(skimage.io.imread(img_dir+r"\me.jpg"))
orange = skimage.img_as_float(skimage.io.imread(img_dir+r"\baby.jpg"))
if max(melon.shape) < max(orange.shape) :
    orange = skimage.transform.resize(orange,output_shape=melon.shape)
    mask = np.zeros(melon.shape)
else:
    melon = skimage.transform.resize(melon, output_shape=orange.shape)
    mask = np.zeros(orange.shape)
laplace_melon = get_laplace_pyramid(get_guass_pyramid(melon))
laplace_orange = get_laplace_pyramid(get_guass_pyramid(orange))
mask[:,150:,:] = 1
mask = np.fliplr(mask)
gauss_mask = get_guass_pyramid(mask)
plot_pyramid(melon)
plot_pyramid(orange)
laplace_re = []
for i in range(len(gauss_mask)) :
    im_mask = gauss_mask[i] * laplace_melon[i] + (1-gauss_mask[i]) * laplace_orange[i]
    laplace_re.append(im_mask)
im_re = reconstruct_image_only_by_laplace_pyramid(laplace_re)
plt.imshow(im_re[1]),plt.show()






