#%%
# -*- coding UTF-8 -*-
'''
@Project : MyPythonProjects
@File : 解压文件.py
@Author : chenbei
@Date : 2021/8/23 14:48
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
from tensorflow.keras import layers, Sequential
import tarfile
path_root = "https://www.dcc.fc.up.pt/~ltorgo/Regression/cal_housing.tgz"
data_root = tf.keras.utils.get_file("cal_housing",path_root,untar=True) # untar表示应当解压,解压格式为.tar.gz
data_root = data_root + ".tar.gz"
with tarfile.open(mode="r:gz", name=data_root) as tar:
    cal_housing = np.loadtxt(tar.extractfile('CaliforniaHousing/cal_housing.data'),delimiter=',')
    for tarinfo in tar:
        print(tarinfo.name)
column_names = ["经度","纬度","房龄中位数", "房间总数","卧室总数", "人口总数",
                 "家庭总数","家庭收入","平均房价"]
data = pd.DataFrame(cal_housing,columns=column_names)
data.info()
data.plot(kind="scatter",x="经度",y="纬度",alpha=0.4,s=data["人口总数"]/100,label="人口总数",c="平均房价",
          cmap=plt.get_cmap('jet'),colorbar=True)
plt.legend()
plt.show()
# target = data.pop(column_names[-1])