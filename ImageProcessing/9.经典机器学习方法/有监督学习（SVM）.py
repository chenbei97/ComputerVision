#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 有监督学习（SVM）.py
@Author : chenbei
@Date : 2021/9/24 11:39
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
import numpy as np
import seaborn as  sns
import pandas as pd
import os
from sklearn import  preprocessing ,decomposition,datasets ,cluster,pipeline,neighbors,metrics,svm

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
clf = svm.SVC(C=1,kernel='poly',degree=2)
clf.fit(train_x,train_y)
print(clf.score(test_x,test_y))

test_y_pred = clf.predict(test_x)
cm = metrics.confusion_matrix(test_y,test_y_pred)
df_cm = pd.DataFrame(cm)
# context – 缩放参数
# style – 轴样式参数
# palette – 调色板
# font – 字体系列
# font_scale – 单独的缩放因子以独立缩放字体元素的大小
# rc – rc 参数映射字典以覆盖上述内容
sns.set(font_scale=1.2)
# annot使用fmt和annot_kws的格式注释
# center = 0 使用发散颜色图绘制以0为中心的数据的热图
# 颜色棒用cbar控制，范围vmin和vmax控制
# linecolor='r',linewidths=1,控制表格线宽和颜色
# xticklabels=2, yticklabels=False 控制表格的刻度
sns.heatmap(df_cm,annot=True,annot_kws={"size":16},fmt=".3g",cbar=True)
plt.show()

#%%
# 保存和加载模型
import joblib
# joblib.dump(clf,'mnist_svm.joblib')
model = joblib.load(root+'\\9.经典机器学习方法\\'+'mnist_svm.joblib')
#%%
import pickle
path = root+'\\9.经典机器学习方法\\'+'mnist_svm.pickle'
with open(path, 'wb') as f:
      pickle.dump(clf, f)
with open(path, 'rb') as f:
    model_ = pickle.load(f)








