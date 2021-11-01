#%%
# -*- coding UTF-8 -*-
'''
@Project : MyProjects
@File : RGB_灰度_二值图像的区别.py
@Author : chenbei
@Date : 2021/7/23 9:01
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl

plt.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
plt.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
plt.rcParams['savefig.dpi'] = 600  # 图片像素
plt.rcParams['figure.dpi'] = 600  # 分辨率
from matplotlib.font_manager import FontProperties

font_set = FontProperties(fname=r"C:\Windows\Fonts\simsun.ttc", size=10.5)
import numpy as np
import pandas as pd
import os
import  tensorflow as tf
import cv2
# （1）RGB图像 : 每个像素值有3个颜色通道,用红（R）、绿（G）、蓝（B）三原色的组合来表示
# 每个像素的颜色值在0~255之间,常用无符号短整型Uint储存
# 设M、N分别表示图像的行列数，三个 M x N的二维矩阵分别表示各个像素的R、G、B三个颜色分量 每个像素表示为(3,M,N)的张量
# （2）灰度图像 : 每个像素只有一个采样颜色的图像 可以使用平均法、加权平均法、最大最小平均法对一个像素值的三个通道进行合并
# （3）二值图像 : 设定某个阈值,高于阈值的设为255为白色,低于阈值的设为0即黑色
# （4）反转图像 :　s = 255-r　适用于增强暗色图像中的白色或灰色细节
adrr = "C:\\Users\\chenbei\\tensorflow_datasets\\lover.jpg" # 要求路径无英文且用双斜杠//
# imread函数有两个参数，第一个参数是图片路径，第二个参数表示读取图片的形式
# cv2.IMREAD_COLOR：加载彩色图片，这个是默认参数，可以直接写1。
# cv2.IMREAD_GRAYSCALE：以灰度模式加载图片，可以直接写0。
# cv2.IMREAD_UNCHANGED：包括alpha，可以直接写-1
img = cv2.imread(filename=adrr) # (683, 1024, 3)
row, col, channel = img.shape
#%% 一、RGB图像  : (683, 1024, 3)
cv2.imshow("RGB(683, 1024, 3)", img.astype("uint8"))
cv2.waitKey()
#%% 二、 灰度图像 :  (683, 1024) 变成二维
# （1）简单平均法
img_gray = np.zeros((row, col))
for r in range(row):
    for l in range(col):
        img_gray[r, l] = 1 / 3 * (img[r, l, 0] +   img[r, l, 1] +   img[r, l, 2])

cv2.imshow("Gray-simple", img_gray.astype("uint8"))
cv2.waitKey()
#%%
# (2) 最大最小平均法
for r in range(row):
    for l in range(col):
        img_gray[r, l] = 1 / 2 * max(img[r, l, 0], img[r, l, 1], img[r, l, 2]) +\
                         1/2 *min(img[r, l, 0], img[r, l, 1], img[r, l, 2])

cv2.imshow("Gray_maxmin", img_gray.astype("uint8"))
cv2.waitKey()
# %%
# (3) 加权平均法
# I(x,y) = 0.3 * I_R(x,y) +0.59 * I_G(x,y)+ 0.11 * I_B(x,y)
# 几个加权系数0.3,0.59,0.11是根据人的亮度感知系统调节出来的参数，是个广泛使用的标准化参数
for r in range(row):
    for l in range(col):
        img_gray[r, l] = 0.11 * img[r, l, 0] + 0.59 * img[r, l, 1] + 0.3 * img[r, l, 2]

cv2.imshow("Gray_weighted", img_gray.astype("uint8"))
cv2.waitKey()
#%%  三、二值图像 : 非0即255
threshold = 100
img_binary = np.zeros_like(img_gray)
for r in range(row):
    for l in range(col):
        if img_gray[r, l] >= threshold: # 对灰度图进行判断
            img_binary[r, l] = 255
        else:
            img_binary[r, l] = 0

cv2.imshow("Binary", img_binary.astype("uint8"))
cv2.waitKey()
#%% 四、反转图像 : 255-r
img_inverse = np.zeros_like(img_gray)
for r in range(row):
    for l in range(col):
        img_inverse[r, l] = 255 - img_gray[r, l]
cv2.imshow("img_gray", img_gray.astype("uint8"))
cv2.imshow("img_inverse", img_inverse.astype("uint8"))
cv2.waitKey()


