#%%
# -*- coding UTF-8 -*-
'''
@Project : MyPythonProjects
@File : Os使用.py
@Author : chenbei
@Date : 2021/8/19 16:29
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
import tensorflow as tf
from  tensorflow.keras import  layers,Sequential
import os
#%%
# os.stat()
csw_path = os.getcwd() # 'C:\\Users\\chenbei\\PycharmProjects\\python学习工程文件夹'
path_abs_path = os.path.abspath(csw_path)#'C:\\Users\\chenbei\\PycharmProjects\\python学习工程文件夹'
path_dirname_path = os.path.dirname(path_abs_path) # 'C:\\Users\\chenbei\\PycharmProjects' 所在文件夹
path_real_path = os.path.realpath(path_abs_path) # 'C:\\Users\\chenbei\\PycharmProjects\\python学习工程文件夹'
path_join_path = os.path.join(path_abs_path,"MyPlatform")# 'C:\\Users\\chenbei\\PycharmProjects\\python学习工程文件夹\\MyPlatform'
path_basename_path1 = os.path.basename(csw_path) # 'python学习工程文件夹' 最后一级
path_basename_path2 = os.path.basename("python学习工程文件夹\\MyPlatform")# 'MyPlatform'
paths = [csw_path, # 返回最小的公共路径
        "C:\\Users\\chen",
        "C:\\Users\\chenbei",
        "C:\\Users\\chenbei\\PycharmProjects\\python学习工程文件夹\\MyPlatform",
        "C:\\Users\\chenbei\\PycharmProjects"]
path_common_path = os.path.commonpath(paths) # 'C:\\Users'
path_prefix_path = os.path.commonprefix(paths) # 'C:\\Users\\chen'
isAbs1 = os.path.isabs(csw_path) # T
isAbs2 = os.path.isabs(path_join_path) # T
isAbs3 = os.path.isabs("python学习工程文件夹\\MyPlatform") # F
isAbs4 = os.path.isabs("Users\\chenbei\\PycharmProjects\\python学习工程文件夹\\MyPlatform") # F
isAbs5 = os.path.isabs("\\C:\\Users\\chenbei\\PycharmProjects\\python学习工程文件夹\\MyPlatform") # T
isAbs6 = os.path.isabs("C:\\Users\\chenbei\\PycharmProjects\\python学习工程文件夹\\MyPlatform") # T
isDir = os.path.isdir(csw_path) # 是否为文件夹
isFile = os.path.isfile(csw_path) # 是否为文件
isExist = os.path.exists("C:\\Users\\chenbei\\PycharmProjects\\python学习工程文件夹\\MyPlatform\\lover.jpg") # 文件是否存在
path_relative_path1 = os.path.relpath("C:\\Users\\chenbei\\PycharmProjects\\python学习工程文件夹"
                ,"C:\\Users\\chenbei\\PycharmProjects\\python学习工程文件夹\\MyPlatform\\lover.jpg") # '..\\..'
path_relative_path2 = os.path.relpath("C:\\Users\\chenbei\\PycharmProjects\\python学习工程文件夹\\MyPlatform\\lover.jpg"
                ,"C:\\Users\\chenbei\\PycharmProjects\\python学习工程文件夹") # 'MyPlatform\\lover.jpg'
#%%
listdir = os.listdir(os.getcwd()) # 获取当前文件夹下的文件(夹)名字列表
path_dict = {} # 关键字为listdir 值为拼接的字符串路径
for element in listdir :
    path_dict[element] = os.path.join(os.getcwd(),element)
platform_files = os.listdir(path_dict["MyPlatform"]) # 类似思路可以得到一个图片文件夹的所有名字















