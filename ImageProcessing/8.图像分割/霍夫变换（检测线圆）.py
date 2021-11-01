#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 霍夫变换（检测线圆）.py
@Author : chenbei
@Date : 2021/9/16 15:25
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
import numpy as np
import os
import skimage.io, skimage.color,skimage.draw, skimage.transform
import skimage
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
#%%（1）线变换
im = skimage.io.imread(img_dir+"\circle.jpg")
gray = skimage.color.rgb2gray(im)
# 默认theta为从 -pi/2 到 pi/2 均匀间隔的 180 个角的向量
# 返回霍夫变换累加器,计算变换的角度(弧度),距离
# 原点是原始图像的左上角
# X 轴和 Y 轴分别是水平和垂直边缘
# 距离是从原点到检测线的最小代数距离
# 可以通过减小theta数组中的步长来提高角度精度
hspace ,angles , distances = skimage.transform.hough_line(gray,theta=None)
# 标识在霍夫变换中以特定角度和距离分隔的最突出的线
# 返回 霍夫空间、直线极坐标系的角度和距离
accum, angles, dists = skimage.transform.hough_line_peaks(hspace=hspace,
                                                          angles=angles,
                                                          dists=distances,
                                                          min_distance=9,
                                                          min_angle=10,
                                                          threshold=None,
                                                          num_peaks=np.inf)
angle_positive = np.rad2deg(angles[0]) # 角度的范围
angle_negative = np.rad2deg(angles[-1]) # 180 * x / pi
fig = plt.figure()
ax1 = fig.add_subplot(121)
ax2 = fig.add_subplot(122)
for angle,dist in zip(angles,dists) :
    line_y0 = dist / np.sin(angle)
    line_y1 = ( dist - im.shape[1]*np.cos(angle) ) / np.sin(angle)
    ax1.imshow(im)
    ax1.plot((0,im.shape[1]),(line_y0,line_y1),'-r')
ax1.set_ylim((im.shape[0],0)),ax1.set_xlim((0,im.shape[1]))
# extent = floats (left, right, bottom, top) 指定图像将填充的数据坐标中的边界框
ax2.imshow(hspace,extent=(150*angle_negative,angle_positive,distances[-1],distances[0]),cmap='hot')
ax1.set_axis_off(),ax2.set_axis_off()
fig.show()

#%% （2）圆变换
im = skimage.io.imread(img_dir+"\coin.jpg")
gray = skimage.color.rgb2gray(im)
total_num_peaks = 2 # 最大峰值数
search_radius = np.arange(180,220,1) # 根据图中圆的大小估计
# 返回每个半径的Hough变换累加器
H = skimage.transform.hough_circle(image=gray,radius=search_radius,normalize=True,
                                   full_output=False #if true 将输出大小扩大两倍最大半径，以便检测输入图片外的中心
                                   )
assert H.shape[0] == len(search_radius)
# 根据total_num_peaks图片指定返回几个圆(使用投票)
# 返回霍夫空间、以及圆心x,y坐标及其半径
hspace,xs,ys,rs = skimage.transform.hough_circle_peaks(hspaces=H,
                                                       radii=search_radius,
                                                       min_xdistance=1,# 在x维度中分隔中心的最小距离
                                                       min_ydistance=1,
                                                       threshold=None,#每个Hough空间中峰值的最小强度,默认0.5 * max(hspace)
                                                       num_peaks=np.inf,#每个Hough空间中的最大峰值数
                                                       total_num_peaks=total_num_peaks,#最大峰值数
                                                       normalize=False # if True 通过半径对累加器进行规格化，以对突出的峰值进行排序
                                                       )
new_gray = np.zeros_like(gray)
im_new = im.copy()
for x,y,r in zip(xs,ys,rs) : # 对分割出的圆绘制
    x_idx,y_idx = skimage.draw.circle_perimeter(r=x,c=y,radius=r)# 返回属于圆周长的像素索引
    # 在原图中认为是属于圆的坐标索引(x_idx,y_idx),是(w,h)坐标系,对应数组的(col,raw),故应调换顺序
    im_new[y_idx,x_idx,:] = (0,255,0) # 颜色 im.shape(401,753) max(col)=286,max(raw)=462
    new_gray[y_idx,x_idx] = 1
plot_im1_im2(new_gray,im_new)

#%%

