#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 基于LoG、DoG和DoH的斑点检测器.py
@Author : chenbei
@Date : 2021/9/10 16:14
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
import numpy as np
import os
import skimage.io, skimage.color,  skimage.feature
import skimage
import matplotlib.pylab as pylab
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
def plot_ax(im,ax,title):
    ax.imshow(im),ax.set_title(title,size=12),ax.set_axis_off()
#%% （1）基于scipy.ndimage.gaussian_lapalce()的高斯拉普拉斯LoG算子
# （2）使用高斯差分DoG近似LoG 需要自定义核
# （1）和（2）详见第5章<利用导数和滤波器边缘检测.py>
#（3）黑塞矩阵DoH
im = skimage.io.imread(img_dir+r"\butterfly.jpg")
im_gray = skimage.color.rgb2gray(im)
# max_sigma,min_sigma高斯核最大最小标准差可以检测较大或较小的斑点
# num_sigma考虑标准偏差的中间值的个数,介于[min_sigma,max_sigma]
# thresold适用于颜色较少的斑点，越小越易检测
# 返回(r, c, sigma) sigma是Hessian矩阵的高斯核的标准偏差
LoG = skimage.feature.blob_log(im_gray,max_sigma=50,num_sigma=10,threshold=0.1)
# LoG[:,2] = np.sqrt(LoG[:,2])
DoG = skimage.feature.blob_dog(im_gray,max_sigma=50,threshold=0.1)
# DoG[:,2] = np.sqrt(DoG[:,2])
DoH  = skimage.feature.blob_doh(im_gray,max_sigma=50,threshold=0.005)
# DoH[:,2] = np.sqrt(DoH[:,2])
# from matplotlib.patches import Circle
blobs = [LoG,DoG,DoH]
colors = ['blue','cyan','red']
titles = ['Original','LoG','DoG','DoH']
fig ,axes = pylab.subplots(2,2)
axes = axes.flatten()
for axe,title in zip(axes,titles):
    plot_ax(im,axe,title) # 先 生成4个蝴蝶
for axe ,color,blob in zip(axes[1:],colors,blobs) :
    axe.set_xlim((-50,np.max(blob)+50)),axe.set_ylim((-50,np.max(blob)+50))
    axe.set_axis_on()
    for point in blob : # 每个斑点算子坐标集合的每一个坐标
        x , y , radius = point # blob[:,0],blob[:,1],blob[:,-1]
        # clip_on超出范围的不裁剪也显示
        patch = plt.Circle((x,y),radius,color=color,linewidth=0.5,fill=False,clip_on=False,alpha=0.5)
        axe.add_patch(patch)
fig.tight_layout()
fig.show()

