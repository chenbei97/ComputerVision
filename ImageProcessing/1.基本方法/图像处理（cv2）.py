#%%
# -*- coding UTF-8 -*-
'''
@Project : MyPythonProjects
@File : ImageProcessing（cv2）.py
@Author : chenbei
@Date : 2021/8/23 15:30
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
import numpy as np
import pandas as pd
import cv2
#　要求路径无英文 返回张量数组类型
'''

'''
# （1）图像匹配算法
cv2.SIFT_create()
cv2.ORB_create()
#（2）匹配器
matcher = cv2.BFMatcher()
matcher.match()
matcher.knnMatch()
# （3）绘制匹配器
cv2.drawMatches()
cv2.drawMatchesKnn()
# （4）更改图像格式
cv2.cvtColor()
