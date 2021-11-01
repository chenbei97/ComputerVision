#%%
# -*- coding UTF-8 -*-
'''
@Project : MyPythonProjects
@File : Pathlib使用.py
@Author : chenbei
@Date : 2021/8/19 16:28
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
import tensorflow as tf
import pathlib
dataset_url = "https://storage.googleapis.com/download.tensorflow.org/example_images/flower_photos.tgz"
data_dir = tf.keras.utils.get_file('flower_photos', origin=dataset_url, untar=True)
data_dir = pathlib.Path(data_dir) # WindowsPath风格路径 C:\Users\chenbei\.keras\datasets\flower_photos
cwd_path = data_dir.cwd()#C:\Users\chenbei\PycharmProjects\python学习工程文件夹
home_path = data_dir.home()#C:\Users\chenbei
abs_path = data_dir.absolute()#C:\Users\chenbei\.keras\datasets\flower_photos
# stat_path = data_dir.stat()
A = pathlib.WindowsPath(data_dir)
'''
pathlib有多个路径风格类,常用的为Path类
'''