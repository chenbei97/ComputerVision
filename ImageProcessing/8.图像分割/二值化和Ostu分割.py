#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 二值化和Ostu分割.py
@Author : chenbei
@Date : 2021/9/16 15:26
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
import os
import skimage.io, skimage.color, skimage.filters
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

horse = skimage.io.imread(img_dir+"\horse.jpg")
grey = skimage.color.rgb2gray(horse)
ostu_threshold = skimage.filters.threshold_otsu(grey)
binary = (grey > ostu_threshold).astype(float) # 高于阈值为1
axe1 ,axe2 = plt.subplot(121),plt.subplot(122)
axe1.imshow(binary),axe2.hist(grey.ravel(),bins=256),axe2.axvline(x=ostu_threshold)
plt.show()




