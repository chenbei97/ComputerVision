#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 无监督学习（KMeans）.py
@Author : chenbei
@Date : 2021/9/18 11:48
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
import numpy as np
import os
import skimage.io
from time import  time
from sklearn import cluster ,utils
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
def plot_im1_im2(im1,im2,title1="original",title2="reconstruction"):
    fig = plt.figure()
    plt.gray()
    ax1 = fig.add_subplot(121)
    ax2 = fig.add_subplot(122)
    ax1.imshow(im1),ax2.imshow(im2)
    ax1.set_title(title1,size=12),ax2.set_title(title2,size=12)
    ax1.set_axis_off(),ax2.set_axis_off()
    fig.show()
img = skimage.io.imread(img_dir+"\pepper.jpg")
width , height , channel = img_shape = tuple(img.shape)
x = np.reshape(img,(width*height,channel)) # 展平
def my_kmeans(x,n_clusters=64,n_samples=1000):
    x = x / 255.
    # n_samples不能太大，花费时间变长
    train_x = utils.shuffle(x,random_state=0,n_samples=n_samples)
    print(len(train_x))
    kmeans = cluster.KMeans(n_clusters=n_clusters, random_state=0).fit(train_x)
    #  可以返回 kmeans.labels_ 和 cluster_centers_
    #  分别表示聚类数据的实际标签和指定聚类的中心坐标
    x_pred = kmeans.predict(x) # 每个数据预测的结果，属于何种标签，标签和聚类中心一一对应
    cluster_centers = kmeans.cluster_centers_ # 聚类中心坐标
    # train_y = kmeans.labels_ # 无监督学习没有标签，这是自动生成的实际标签
    # 根据标签重构图像（但是图像必须要全部的像素）
    img_re  = np.zeros((width,height,channel))
    idx = 0 # 每个像素点的索引，从0遍历置width*height所有像素点
    for i in range(width) :
        for j in range(height) :
            current_pixel_label = x_pred[idx] # 当前像素点的标签为0,1,2,...n_clusters中的1类
            current_pixel = cluster_centers[current_pixel_label] # 聚类中心label=0,1,2,...k对应第0,1,2,..k个聚类中心
            img_re[i, j] = current_pixel # 以聚类中心像素值代替原本的像素
            idx += 1
            # print(idx)
    return img_re
#%% （1）K均值聚类
# 1）n_samples的影响（模型训练数据的个数）
for n_samples in [1000,50000,200000,400000] :
    t0 = time()
    img_re = my_kmeans(x,n_samples=n_samples)
    print(f"n_samples = {n_samples} 时花费的时间为 {time()-t0}")
    plot_im1_im2(img,img_re,title2="n_samples="+str(n_samples))
#%%
# 2）n_clusters的影响
for n_clusters in [128,64,32,8,4] :
    t0 = time()
    img_re = my_kmeans(x,n_clusters=n_clusters)
    print(f"n_clusters = {n_clusters} 时花费的时间为 {time()-t0}")
    plot_im1_im2(img,img_re,title2="n_clusters="+str(n_clusters))

#%% （2）小批量K均值
img = skimage.io.imread(img_dir+"\messi.png")
x = np.reshape(img,(-1,img.shape[-1])) # 保持最后一个维度，其他自动 （W*H,C=3）
two_means = cluster.MiniBatchKMeans(n_clusters=2,random_state=10).fit(x)
y_pred = two_means.predict(x) # （W*H，）
y_pred = np.reshape(y_pred,img.shape[:2]) # 重构为（W，H），此时恰好是二值图像的标签
labels = two_means.labels_.reshape(img.shape[:2])
plt.subplot(121),plt.imshow(y_pred),plt.contour(y_pred==0,contours=1,colors='green')
plt.subplot(122),plt.imshow(img)
# y_pred==0  返回bool掩码，是二维的 ,labels和y_pred是差不多的
plt.contour(labels==0,contours=1,colors='red'),plt.show()

#%% （3）谱聚类（常用于图像分割）
spectral = cluster.SpectralClustering(affinity="nearest_neighbors",n_neighbors=100,random_state=10,
                               eigen_solver='arpack', n_clusters=2)
spectral.fit(x[:10000])
#%%
labels = spectral.labels_.reshape(img.shape[:2]) # 和用预测的区别不大
plt.contour(labels==0,contours=1,colors='red'),plt.show()










