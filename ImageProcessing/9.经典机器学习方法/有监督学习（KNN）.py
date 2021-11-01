#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 有监督学习（KNN）.py
@Author : chenbei
@Date : 2021/9/24 11:38
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
import numpy as np
import os
import pandas as pd
from sklearn import  preprocessing ,decomposition,datasets ,cluster,pipeline,neighbors,metrics
import seaborn as sns
plt.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
plt.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
plt.rcParams['savefig.dpi'] = 600  # 图片像素
plt.rcParams['figure.dpi'] = 600  # 分辨率
def download_gz_from_url_and_extract(url,filename,loc=r"C://Users//chenb//scikit_learn_data//",
                         extract=False,buffer=None,dtype=None,offset=0):
    # url = http://yann.lecun.com/exdb/mnist/
    # loc = 'C:\\Users\\chenb\\scikit_learn_data\\'
    # 判断是否已经下载了该文件，未下载则下载否则直接解压即可
    if not os.path.exists(loc + filename) :
        from urllib.request import urlretrieve # 从网站下载文件到filename,尾部是指定的文件
        urlretrieve(url=url+filename,filename=loc+filename)
    if extract :
        import gzip
        with gzip.open(filename=loc+filename,mode="rb") as f :
            data = np.frombuffer(buffer=f.read(),dtype=dtype,offset=offset) # offset:从该偏移量开始读取缓冲区（字节）
    return data
patch_kw = {'url':"http://yann.lecun.com/exdb/mnist/",
            'loc':r"C://Users//chenb//scikit_learn_data//",
            'extract':True,
            'dtype':np.uint8}
filenames = ["train-images-idx3-ubyte.gz",'train-labels-idx1-ubyte.gz',
             't10k-images-idx3-ubyte.gz','t10k-labels-idx1-ubyte.gz']
lst = []
for filename ,offset in  zip(filenames,[16,8,16,8]) :
    lst.append(download_gz_from_url_and_extract(filename=filename,offset=offset,**patch_kw))
train_data ,train_y ,test_data ,test_y =  tuple(lst)
train_x ,test_x= np.reshape(train_data,(-1,28*28)),np.reshape(test_data,(-1,28*28))
#%% （1）球树
ball_tree = neighbors.BallTree(train_x[:1000])
# k指定要返回的最近邻居数，某个数据最靠近的k个数据属于的标签索引 数组格式=(len(test_x),k)
neighbors_pred = ball_tree.query(X=test_x, k=1, return_distance=False)
# 与当前测试数据点最近的那个点的索引是neighbors_pred,带入train_y得到预测的标签
test_y_pred = train_y[neighbors_pred]
acu =  sum(sum(test_y_pred.reshape(1,-1) == test_y)) / test_y_pred.shape[0]
cm = metrics.confusion_matrix(test_y,test_y_pred)
df_cm = pd.DataFrame(cm)
sns.set(font_scale=1.2)
sns.heatmap(df_cm,annot=True,annot_kws={"size":16},fmt="g")
plt.show()
# metrics.plot_confusion_matrix() # 需要估计器
#%%
kd_tree = neighbors.KDTree(train_x[:3000])
# k指定要返回的最近邻居数，某个数据最靠近的k个数据属于的标签索引 数组格式=(len(test_x),k)
neighbors_pred = kd_tree.query(X=test_x, k=1, return_distance=False)
# 与当前测试数据点最近的那个点的索引是neighbors_pred,带入train_y得到预测的标签
test_y_pred = train_y[neighbors_pred]
acu =  sum(sum(test_y_pred.reshape(1,-1) == test_y)) / test_y_pred.shape[0]
cm = metrics.confusion_matrix(test_y,test_y_pred)
df_cm = pd.DataFrame(cm)
sns.set(font_scale=1.2)
sns.heatmap(df_cm,annot=True,annot_kws={"size":16},fmt="g")
plt.show()






