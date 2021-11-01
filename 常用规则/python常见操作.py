#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : python常见操作.py
@Author : chenbei
@Date : 2021/8/31 15:06
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
import numpy as np
import os
import matplotlib.pylab as pylab
plt.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
plt.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
plt.rcParams['savefig.dpi'] = 600  # 图片像素
plt.rcParams['figure.dpi'] = 600  # 分辨率
from  PIL import Image
root = os.path.join(os.getcwd(),"ImageProcessing")
img_dir = os.path.join(root,"images")
im = np.array(Image.open(img_dir +  "/house.png").convert(mode='L'))
# 对[8, 7, 6, 5, 4, 3, 2, 1]依次做位运算 1<<8 ,1<<7,...,1<<1 = 256,128,..,1
num_colors_list = [ 1 << n for n in range(8,0,-1)]
#%%
pylab.xscale('log', basex=2)  # 刻度使用对数坐标 且以2为底
pylab.gca().invert_xaxis()  # 翻转x坐标 从大到小

im1 = np.zeros_like(im)
func = np.vectorize(pyfunc=complex) # 本质上是一个迭代器类似于map(func,*iterables)

row , col = np.unravel_index(np.argmax(im),im.shape) # 找到展平数组最大处于的位置,然后将其反转得到展平前的位置
print(np.argmax(im) // im.shape[1] ,np.argmax(im) % im.shape[1])

# plt.title(r'$\sigma_r=$'+str(sigma_color)+r' $\sigma_s=$'+str(sigma_spatial))

# 利用plt.Circle()来绘制斑点，单次只能绘制1个坐标生成patch,然后使用axe.add_patch(patch)添加