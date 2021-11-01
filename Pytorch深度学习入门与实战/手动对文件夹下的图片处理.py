#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 手动对文件夹下的图片处理.py
@Author : chenbei
@Date : 2021/10/8 9:49
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
import numpy as np
import torch
import os
from PIL import Image
from torchvision import transforms
from sklearn.metrics import accuracy_score
import cv2
import skimage

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
im_lst = []
label_lst = []
test_path = r"C:\Users\chenb\.torch\10-monkey-species\testing"
size = 224
for idx, path in enumerate(os.listdir(test_path)):
    label_lst.append(int(path[1]))
    image_path = os.path.join(test_path, path)
    im = Image.open(image_path)

    transform = transforms.Compose([
        transforms.Resize((size, size)),
        transforms.ToTensor(),

    ])
    im_adjust = transform(im)
    if idx < 1:
        result = im_adjust
        continue
    if idx < 2:
        result = torch.stack((result, im_adjust), dim=0)
        print(result.shape, )
    else:
        im_adjust = torch.unsqueeze(im_adjust, dim=0)
        result = torch.cat((result, im_adjust), dim=0)
label = np.array(label_lst)
print(result.shape, result.dtype, result)
#%%
class MyVgg16(torch.nn.Module):
    def __init__(self):
        super(MyVgg16, self).__init__()
        self.vgg = vgg
        # 自定义的全连接层
        self.classifier = torch.nn.Sequential(
            torch.nn.Flatten(), # 512*7*7=25088
            torch.nn.Linear(25088,512),
            torch.nn.ReLU(),
            torch.nn.Dropout(0.5),
            torch.nn.Linear(512,256),
            torch.nn.ReLU(),
            torch.nn.Dropout(0.5),
            torch.nn.Linear(256,10),
            torch.nn.Softmax(dim=1)
        )
    def forward(self,x):
        x = self.vgg(x)
        #print(x.shape)# 32, 512, 7, 7
        x = self.classifier(x)
        return x
root = "C:\\Users\\chenb\\.torch\\10-monkey-species\\"
model_new = torch.load(root+"10_monkey_species_model_pycharm.pkl")
#%%
# 预测标签
output = model_new(result)
pred_label = torch.argmax(output,dim=1)
print(accuracy_score(pred_label.numpy(),label))







