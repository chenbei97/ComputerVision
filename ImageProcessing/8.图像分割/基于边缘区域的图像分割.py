#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 基于边缘区域的图像分割.py
@Author : chenbei
@Date : 2021/9/16 15:26
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
import numpy as np
import os
import  skimage.color,skimage.filters, skimage.feature, skimage.morphology
import scipy.ndimage
plt.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
plt.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
plt.rcParams['savefig.dpi'] = 600  # 图片像素
plt.rcParams['figure.dpi'] = 600  # 分辨率
root = os.path.join(os.getcwd(), "ImageProcessing")
img_dir = os.path.join(root, "images")
def plot_im1_im2(im1,im2,title1="original",title2="reconstruction"):
    fig = plt.figure()
    plt.gray()
    ax1 = fig.add_subplot(121)
    ax2 = fig.add_subplot(122)
    ax1.imshow(im1),ax2.imshow(im2)
    ax1.set_title(title1,size=12),ax2.set_title(title2,size=12)
    ax1.set_axis_off(),ax2.set_axis_off()
    fig.show()
im = skimage.data.coins() # 硬币图像
plt.hist(im.ravel(),bins=256),plt.show() # 像素直方图
#%%（1）基于边缘
# im = skimage.color.rgb2gray(skimage.io.imread(img_dir+"\coin.jpg"))
edges = skimage.feature.canny(im,sigma=2)
fill_holes = scipy.ndimage.binary_fill_holes(edges)
plot_im1_im2(edges,fill_holes) # 有一些轮廓没有被填充
remove_small_obeject = skimage.morphology.remove_small_objects(fill_holes,min_size=50)
plot_im1_im2(fill_holes,remove_small_obeject)
#%%（2）基于区域（形态学分水岭算法）
edges = skimage.filters.sobel(im)
distribute = np.bincount(im.ravel()) # 寻找一维数组的分布，每个值出现的次数
peak = np.argmax(distribute) # 最大值的位置，也就是出现次数最多的位置
valley = 150
marker = np.zeros_like(im)
marker[ im < peak ] = 1 # 高频率像素出现以前置为1
marker[ im > valley] = 2 # 置为2
# plt.imshow(marker,cmap='hot'),plt.colorbar(),plt.show()
seg = skimage.morphology.watershed(edges,markers=marker) # 分水岭算法,返回的就是二值标记
seg_ = scipy.ndimage.binary_fill_holes(seg-1).astype(float)
print('label前的像素分布范围：',np.min(seg_),np.max(seg_))
# 输入input中的任何非零值都被视为特征，零值被视为背景
# 理解为重新调整分布，原来的特征是1，但是1的分布不是连续的，将这些1继续细分多个区域，改变了像素亮度
# num_features 为细分后的区域种类
label , num_features = scipy.ndimage.label(input=seg_)
print('label后的像素分布范围：',np.min(label),np.max(label))
assert len(set(label.ravel())) == num_features + 1 # label分成了num_features个特征+1个背景
# 标签并不是像素强度，还需要根据标签转换，给定参数标签和被转换对象
label_invert = skimage.color.label2rgb(label=label,image=im)
plot_im1_im2(im, label_invert)
#%%




