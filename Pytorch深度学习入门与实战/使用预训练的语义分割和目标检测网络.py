#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 使用预训练的语义分割和目标检测网络.py
@Author : chenbei
@Date : 2021/10/5 19:19
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
import numpy as np
import pandas as pd
from tqdm import tqdm
import os
import hiddenlayer
import torchviz
import torch
import torchvision
import torch.utils.data as torch_utils_data
import torchvision.datasets as torchvison_data
import  torchvision.transforms as torchvison_trans
import sklearn.datasets as sklearn_datasets
import sklearn.decomposition as sklearn_decompose
import sklearn.preprocessing as sklearn_processing
import sklearn.metrics as sklearn_metric
import sklearn.manifold as sklearn_manifold
import sklearn.model_selection as sklearn_model_selection
import tensorboardX
import seaborn as sns
import copy
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
def plot_im1_im2(im1,im2,title1="original",title2="reconstruction"):
    fig = plt.figure()
    plt.gray()
    ax1 = fig.add_subplot(121)
    ax2 = fig.add_subplot(122)
    ax1.imshow(im1),ax2.imshow(im2)
    ax1.set_title(title1,size=12),ax2.set_title(title2,size=12)
    ax1.set_axis_off(),ax2.set_axis_off()
    fig.show()
lena = cv2.imread(img_dir+"\\plane_10.jpg").astype(np.uint8)
trans = torchvison_trans.Compose([
    torchvison_trans.ToTensor(),
    torchvison_trans.Normalize(mean=[0.485,0.456,0.406],std=[0.229,0.224,0.225])
])
lena_tensor = trans(lena).unsqueeze(dim=0)

#%% （1）语义分割网络
fcn_resnet50 = torchvision.models.segmentation.fcn_resnet50(pretrained=True)
fcn_resnet50.eval()
output = fcn_resnet50(lena_tensor)

out = output["out"].squeeze(dim=0) # (21,220,220)--->21个特征图，认为原图像素可以分为21个类别
# 每个像素都有21个值比较，最大的那个索引位置返回，也就是相应的像素类别
pixel_label = torch.argmax(out,dim=0).numpy()
assert np.max(pixel_label) <= out.shape[0] # label的值一定比21小

lena_re = np.zeros_like(lena).astype(np.uint8)
print(np.unique(pixel_label)) # 最终只有2个类别,别的例子可能有更多的类别

# 某个颜色标签，表示该颜色每个通道应当取的值
label_colors = np.array([(255,0,0),(128,0,0),(0,128,0),(128,128,0),# 0-3
                         (0,0,128),(128,0,128),(0,128,128),(128,128,128),# 4-7
                         (64,0,0),(192,0,0),(64,128,0),(192,128,0), # 8-11
                         (64,0,128),(192,0,128),(64,128,128),(0,0,255),# 12-15 第15个颜色和第0个颜色修改一下
                         (0,64,0),(128,64,0),(0,192,0),(128,192,0),(0,64,128)]) # 15-20



# 虽然本例只有2个类别，但是仍然对每个类别循环
for label in range(out.shape[0]):
    # 循环21次
    mask = (pixel_label == label) # 例如对label=0，会返回1个掩码
    # 像素为类别0的等于True，其他Fasle
    label_color = label_colors[label] # 该类别的颜色，3通道元组对象( , , )
    lena_re[..., 0][mask] = label_color[0] # 第一个通道mask指定的True位置都等于这个数
    lena_re[..., 1][mask] = label_color[1] # 通道2
    lena_re[..., 2][mask] = label_color[2] # 通道3
    # 有相应的类别mask就会为True，就会赋值
    # 本例除了0和15没有其他颜色，这些颜色都是False也就不会改变原有的值分布
    # 如label=0得到了一些分布，label=1如果存在就会在label=0的结果上去影响，以此类推
    # 那么从label=0开始和从label=21开始是没有影响的，最后是相同的结果
    # eg：
    # _mask = pixel_label == 2
    # lena[_mask] = 266
    # np.max(lena)  # False的不会赋值
plot_im1_im2(lena,lena_re)
#%%（2）目标检测网络
# 具有ResNet-50-FPN结构的Fast R-CNN网络
fasterrcnn_resnet50_fpn = torchvision.models.detection.fasterrcnn_resnet50_fpn(pretrained=True)
fasterrcnn_resnet50_fpn.eval()

# 返回边界框、所属类别和得分
pred = fasterrcnn_resnet50_fpn(lena_tensor)
scores = pred[0]["scores"].detach().numpy()
labels = pred[0]["labels"].numpy() # ndarray([1, 1, 3, 1])

boxes = pred[0]["boxes"].detach().numpy() # (4,4) 4个边界框的位置信息
# 根据得分的置信度只保留第1个最可能的
box1 = boxes[0,]
box1 = box1.astype(np.int)
box2  = boxes[1,]
box2 = box2.astype(np.int)
#%% 1）使用cv2绘制
# 返回box为（X，Y，W，H）格式 ，但是cv2要求传入的是2个坐标
lena_re = cv2.rectangle(img=lena,pt1=(box1[0],box1[1]),pt2=(box1[0]+box1[2],box1[1]+box1[3]),color=(0,0,255),thickness=2)
lena_re = cv2.rectangle(img=lena_re,pt1=(box2[0],box2[1]),pt2=(box2[0]+box2[2],box2[1]+box2[3]),color=(0,255,0),thickness=2)
cv2.imshow('lena',lena_re)
cv2.waitKey()
cv2.destroyAllWindows()
#%% 2）使用PIL绘制
from   PIL import ImageDraw ,Image
im =  Image.fromarray(lena)
draw = ImageDraw.Draw(im)
draw.rectangle(box1,outline='red')
im.show()

