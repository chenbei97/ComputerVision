#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 类Haar特征及其在人脸检测的应用.py
@Author : chenbei
@Date : 2021/9/10 16:16
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
import numpy as np
import os
import skimage.feature
import skimage
import  cv2
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
#%%（1）5种类Haar特征描述符
im = np.zeros((3,3))
# width – 检测窗口的宽度。
# height – 检测窗口的高度
# feature_type = [type-2-x,type-2-y,type-3-x,type-3-y,type-4]
# Return feature_coord : (n_features, n_rectangles, 2, 2)
feature_coord ,feature_type = skimage.feature.haar_like_feature_coord(width=3,height=3,feature_type='type-3-y')
haar_feature = skimage.feature.draw_haar_like_feature(image=im, r=0, c=0, width=3, height=3,
                                                      feature_coord=feature_coord,max_n_features=1,alpha=0.8)
plt.imshow(haar_feature),plt.show()
#%%（2）使用已有的opencv人脸检测和眼睛检测模型识别人脸
model_addr = r"C:\Users\chenb\opencv-4.5.3\data\haarcascades"
frontface_detector = cv2.CascadeClassifier(model_addr+"\haarcascade_frontalface_default.xml")
eye_detector = cv2.CascadeClassifier(model_addr+"\haarcascade_eye.xml")
im = cv2.imread(img_dir+"\lena.jpg")
gray = cv2.cvtColor(im,cv2.COLOR_BGR2GRAY)
faces = frontface_detector.detectMultiScale(gray,scaleFactor=1.2,minNeighbors=5)
for (x,y,w,h) in faces :
    im = cv2.rectangle(im,(x,y),(x+w,y+h),color=(255,0,0))#绘制人脸矩形框
    ro_gray = gray[y:y+h,x:x+w] # 眼睛灰色区域
    ro_color = im[y:y+h,x:x+w] # 眼睛彩色区域
    eyes = eye_detector.detectMultiScale(ro_gray)
    for (ex,ey,ew,eh) in eyes:
        cv2.rectangle(ro_color,(ex,ey),(ex+ew,ey+eh),(0,255,0))# 绘制眼睛矩形框
plt.imshow(im),plt.show()
