#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : December_04_DecisionTree.py
@Author : chenbei
@Date : 2021-12-15 9:03
@Email ：chenbei_electric@163.com
@Address : Beijing Jiaotong University
'''
from matplotlib.pylab import mpl
mpl.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
mpl.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
mpl.rcParams['savefig.dpi'] = 600  # 图片像素
mpl.rcParams['figure.dpi'] = 600  # 分辨率
import os
import pathlib
import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt
# (1)利用tf下载花朵数据集：包含5个文件夹，每个文件夹有对应品种的花朵
# 默认下载到用户文件夹，返回的是下载的路径，例如这里是str类型：'C:\\Users\\chenb\\.keras\\datasets\\flower_photos'
downloaded_path = tf.keras.utils.get_file(
    fname = "flower_photos", # 包含5个文件夹的文件夹名字(自定义)
    origin = "https://storage.googleapis.com/download.tensorflow.org/example_images/flower_photos.tgz",
    untar=True) #是否解压
flower_dataset_path = pathlib.Path(downloaded_path) # 将str类型转为路径类型
dir_paths = [] # 用于存储5个文件夹的路径
for dir_name in os.listdir(flower_dataset_path):
    print(dir_name) # 5个文件夹和1个LICENSE.txt(描述数据集的信息)
    if os.path.isdir(os.path.join(flower_dataset_path,dir_name)): # 是文件夹才append
        dir_paths.append(os.path.join(flower_dataset_path,dir_name))
flower_names = ["daisy","dandelion","roses","sunflowers","tulips"]
# 可视化5张图片
plt.figure(dpi=600, figsize=(7.8, 3.8))
fig, axes = plt.subplots(2, 3, sharey=True, sharex=True)
axes = axes.flatten()
for idx,(flower_name,dir_path) in enumerate(zip(flower_names,dir_paths)):
    img = plt.imread(dir_path+"\\"+os.listdir(dir_path)[0]) # 第一张图片
    plt.subplot(2,3,idx+1)
    plt.title(flower_name)
    plt.axis('off')
    plt.imshow(img)
plt.show()
#%%(2)对数据集进行读取并且分割划分得到X,y(预处理过程)
# (2.1)读取图片需要路径，这里获取5个文件夹的所有图片路径
images_path,labels=[],[]
for idx ,dir_path  in enumerate(dir_paths):
    for image_name in os.listdir(dir_path):
        labels.append(idx)
        images_path.append(os.path.join(dir_path,image_name))
        # print(image_name)
dataset = np.c_[images_path,labels] # 注意dataset全部变为字符对象而不是数值对象
np.random.seed(55)
np.random.shuffle(dataset)
n_samples = len(labels) # 数据集较大可以只取几百个作为样本 n_samples=100 or 1000
dataset_sample = dataset[:n_samples-1]
#(2.2)预先对路径打乱
train_size = 0.7
random_state = 10
from sklearn.model_selection import train_test_split
x_train_path, x_test_path, y_train, y_test = train_test_split(dataset_sample[:,0],dataset_sample[:,1],train_size=train_size,random_state=random_state)
y_test,y_train = np.array([int(x) for x in y_test]),np.array([int(x) for x in y_train]) # 把字符元素变为整型元素
#%%
# 数据量巨大时在tensorflow中可以使用 tf.data.Dataset.from_tensor_slices分批读取数据
# 小型数据集可以使用PIL/skimage/plt/cv2读取 这里使用skimage
def imread_images_and_process(path,clip_shape,noise):
    from skimage.io import imread
    from skimage import img_as_float
    from skimage.util import  random_noise
    from skimage.color import rgb2gray
    from skimage.transform import resize
    from skimage.feature import canny
    image = rgb2gray(imread(path)) # 读取图片并灰度转换
    image = resize(image,output_shape=clip_shape) # 统一图片大小,个别图片会因为采样导致模糊和丢失信息
    image = canny(image) # canny二阶导数锐化增强图片
    if noise :
        image = random_noise(image,seed=random_state,clip=True,mean=0,var=1) # 添加高斯噪声
    image = img_as_float(image).ravel() # 转为浮点数并展平
    return image
def get_image_data(paths,clip_shape=(200,200),noise=False):
    # clip_shape为图片数据要预处理为的shape
    data = []
    count = 0
    for path in paths :
        image = imread_images_and_process(path,clip_shape,noise)
        data.append(image)
        if count < 12:
            # print(path)
            plt.subplot(3,4,count+1)
            plt.imshow(image.reshape(clip_shape))
            # 返回的是分割后剩下的倒数1级文件名称和父目录，如果想得到倒数第2级要重复操作
            plt.title(os.path.split(os.path.split(path)[0])[-1])
            plt.axis("off")
        count = count + 1
    plt.show()
    return np.array(data)
X_train = get_image_data(x_train_path)
X_test = get_image_data(x_test_path)
#%%(3)决策树的特征选择指标：ID3(信息熵),C4.5(信息增益比),CART(基尼系数)
#(3.1)flower图片数据集
from sklearn.tree import DecisionTreeClassifier
from sklearn import tree
plt.figure(dpi=600,figsize=(10,6))
fig ,axes = plt.subplots(1,2)
axes = axes.flatten()
for idx ,criterion in enumerate(["gini", "entropy"]):
    DT = DecisionTreeClassifier(max_depth=3,random_state=random_state,criterion=criterion)
    DT.fit(X_train,y_train)
    print(f"criterion = {criterion} score = {DT.score(X_test,y_test)}")
    tree.plot_tree(DT,max_depth=3,ax=axes[idx],fontsize=4)
fig.show()
# criterion = gini score = 0.2688465031789282
# criterion = entropy score = 0.30154405086285196
#%%(3.2) iris数据集
from sklearn.datasets import load_iris
random_state = 3
iris_X,iris_y = load_iris(return_X_y=True)
import random
random.seed(random_state)
random.shuffle(iris_X)
random.shuffle(iris_y)
train_size = 0.4
# train_X,test_X,train_y,test_y = train_test_split(iris_X,iris_y,random_state=random_state)
train_X,train_y = iris_X[0:int(train_size*len(iris_y))], iris_y[0:int(train_size*len(iris_y))]
test_X,test_y = iris_X[int(train_size*len(iris_y)):],iris_y[int(train_size*len(iris_y)):]
model = DecisionTreeClassifier(random_state=random_state,criterion="entropy")
model.fit(train_X,train_y)
print(model.score(test_X,test_y)) # 0.37777777777777777
# 和svm比较一下
from sklearn.svm import SVC
svm = SVC()
svm.fit(train_X,train_y)
print(svm.score(test_X,test_y)) # 0.3111111111111111










