#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 常用脚本函数.py
@Author : chenbei
@Date : 2021/9/24 8:28
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
import numpy as np
import pandas as pd
from tqdm import tqdm
import os
import skimage.io, skimage.color, skimage.metrics, skimage.filters, \
    skimage.segmentation, skimage.feature, skimage.transform, skimage.morphology
import sklearn.cluster, sklearn.preprocessing, sklearn.datasets, sklearn.decomposition, \
    sklearn.pipeline, sklearn.neighbors, sklearn.svm, sklearn.model_selection, sklearn.ensemble, sklearn.metrics
import scipy
import sklearn
from threading import Thread
import cv2
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
#%%
# （1）绘制两个图像
def plot_im1_im2(im1,im2,title1="original",title2="reconstruction"):
    fig = plt.figure()
    plt.gray()
    ax1 = fig.add_subplot(121)
    ax2 = fig.add_subplot(122)
    ax1.imshow(im1),ax2.imshow(im2)
    ax1.set_title(title1,size=12),ax2.set_title(title2,size=12)
    ax1.set_axis_off(),ax2.set_axis_off()
    fig.show()

# （2）从指定网址下载指定压缩文件到指定路径
def download_gz_from_url_and_extract(url,filename,loc=r"C://Users//chenb//scikit_learn_data//",
                         extract=False,buffer=None,dtype=None,offset=0):
    '''
        example:
        train_data = download_gz_from_url_and_extract(
                     url="http://yann.lecun.com/exdb/mnist/",
                     loc=r"C://Users//chenb//scikit_learn_data//",
                     filename="train-images-idx3-ubyte.gz",
                     extract=True,
                     dtype=np.uint8,
                     offset=16)
        patch_kw = {'url':"http://yann.lecun.com/exdb/mnist/",
                'loc':r"C://Users//chenb//scikit_learn_data//",
                'extract':True,
                'dtype':np.uint8}
        train_label = download_gz_from_url_and_extract(filename='train-labels-idx1-ubyte.gz',offset=8,**patch_kw)
        test_data = download_gz_from_url_and_extract(filename='t10k-images-idx3-ubyte.gz',offset=16,**patch_kw)
        test_label = download_gz_from_url_and_extract(filename='t10k-labels-idx1-ubyte.gz',offset=8,**patch_kw)'''
    # 判断是否已经下载了该文件，未下载则下载否则直接解压即可
    if not os.path.exists(loc + filename) :
        from urllib.request import urlretrieve # 从网站下载文件到filename,尾部是指定的文件
        urlretrieve(url=url+filename,filename=loc+filename)
    if extract :
        import gzip
        with gzip.open(filename=loc+filename,mode="rb") as f :
            data = np.frombuffer(buffer=f.read(),dtype=dtype,offset=offset) # offset:从该偏移量开始读取缓冲区（字节）
    return data

# （3）加载二分类数据集
def load_train_test_data(keyword,loc=r"C:\\Users\\chenb\\.kaggle\\dogsVScats\\",
                    keyword_idx=None):
    train_file , test_file = loc+"train\\",loc+"test\\"
    # 提取train数据和标签
    train_x ,train_y,test_x = [] , [],[]
    def train():
        bar = tqdm(os.listdir(train_file))
        for path in bar :
            # 列出所有文件 image是文件名 ：dog.9999.jpg
            image_path = train_file + path # 图片路径地址
            # print(image_path)
            image = cv2.imread(image_path)
            train_x.append(image)
            bar.set_description('train img %s' % path)
            if isinstance(keyword ,(str,int)):
                if type(keyword) == str : # 关键字是字符型
                    if keyword in path :
                        # 只适用于二分类数据集
                        label = 1
                    else :
                        label = 0
                    train_y.append(label)
                else: # 关键字是整型 keyword = 3
                    if keyword_idx is None :
                        # 没有给出整型的范围，默认从文件名的首位开始 [0,3]切割字符串
                        # word = path.split(separator) # ['dog', '9999', 'jpg']返回列表
                        word = path[:keyword]
                        train_y.append(word)
                    else:
                        train_y.append(path[keyword_idx[0]:keyword_idx[1]])
            else:
                raise TypeError("type(keyword) must be in (str,int)")
    def test():
        # bar = tqdm(os.listdir(test_file))
        for path in tqdm(os.listdir(test_file)) :
            image_path = test_file + path
            image = cv2.imread(image_path)
            test_x.append(image)
            # bar.set_description('test img %s' % path)
    train()
    test()
    # t1 = Thread(target=train)
    # t2 = Thread(target=test)
    # t1.start(),t2.start()
    return train_x,train_y,test_x
train_x,train_y,test_x  = load_train_test_data(keyword='dog')

# （4）将列表转换为非0即1
def lst_binary_transform(lst,elem):
    def func(element):
        if element == elem:return 0
        else:return 1
    new = list(map(func,lst))
    return new
mask = lst_binary_transform(['cat','cat','dog'],'dog')

# （5） list1从小到大排序，使用同样顺序对lst2排序
def list_order_mapping(lst1,lst2,reverse=False):
    '''
    :param lst1: 数组或者列表
    :param lst2: 列表
    :param reverse: 默认升序的规则映射，使用降序指定reverse=True
    :return: 映射后的列表
    eg :
    a = [10,9,4,2,3,8,5]
    b = [1,2,3,4,5,6,7]
    # sorted(a)=2,3,4,5,8,9,10  idx---> 3,4,2,6,5,1,0
    idxs = np.argsort(a)
        out : 3,4,2,6,5,1,0
    sorted_result = [b[idx] for idx in idxs ]
        out :   4,5,3,7,6,2,1
    '''
    if type(lst1) != np.ndarray :
        # print("========")
        lst1 = np.array(lst1)
    lst1_sort_idxs = np.argsort(lst1)  # lst1的升序索引
    sorted_result = [lst2[idx] for idx in lst1_sort_idxs]  # 对lst2排序
    # if not reverse :
    #     return sorted_result
    # else:
    #     return sorted_result[::-1]  # 直接反转即可
    return sorted_result if not reverse else sorted_result[::-1]

# （6）冒牌排序
def sortbubble(lis):
    for i in range(len(lis)-1):
        for j in range(len(lis)-1-i):
            if lis[j]>lis[j+1]:
                lis[j],lis[j+1] = lis[j+1],lis[j]
    return lis
#%%









