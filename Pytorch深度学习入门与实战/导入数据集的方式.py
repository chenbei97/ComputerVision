#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 导入数据集的方式.py
@Author : chenbei
@Date : 2021/10/1 21:04
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
import numpy as np
import os
import torch
import torch.utils.data as torchdata
import sklearn.datasets as sklearndata
import torchvision.datasets as torchvisondata
import torchvision.transforms as torchvisiontrans
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
#%% （1）如何使用torch.utils.data模块加载数据集
boston_X , boston_y = sklearndata.load_boston(return_X_y=True)
train_xt, train_yt = torch.from_numpy(boston_X.astype(np.float32)),torch.from_numpy(boston_y.astype(np.float32))
train_data = torchdata.TensorDataset(train_xt,train_yt) # 张量的元组
# 返回一个迭代器，迭代器每次可以输出批样本数据和批样本标签
# 类似于train_dataset=tensorflow的from_tensor_slices.shuffle.batch.repeat的数据流程
# for step, (x,y) in enumerate(train_dataset)
train_loader = torchdata.DataLoader(dataset=train_data,batch_size=64,shuffle=True,num_workers=2)
for step , (bx,by) in enumerate(train_loader):
    print(bx.shape,by.shape) # torch.Size([64, 13]) torch.Size([64])

#%%（2）使用torchvision.datasets得到数据集
root = r"C:\Users\chenb\.torch"
train_data = torchvisondata.FashionMNIST(root=root,
                            train=True, # 只使用训练集
                            transform= torchvisiontrans.ToTensor(), # 将图片数据转为张量0-1之间,[H,W,C]转换为[C,H,W]
                            download=False # 第一次要下载数据
                            )
test_data = torchvisondata.FashionMNIST(root=root,
                            train=False, # 使用测试集
                            # transform= torchvisiontrans.ToTensor(),
                            download=False # 第一次要下载数据
                            )
# train_data原本可能不是uint8类型，所以映射不起作用
# 不使用torchvisiontrans.ToTensor() 也可以找到test_data.data.type()
test_data_x = test_data.data.type(torch.FloatTensor)/255. # float.32
test_data_x= torch.unsqueeze(test_data_x,dim=1) # 在通道参数拓展一个维度
test_data_y = test_data.targets # int.64
train_loader = torchdata.DataLoader(dataset=train_data,batch_size=64,shuffle=True,num_workers=2)
#%%（3）从文件夹加载数据集
path = "C:\\Users\chenb\\.torch\\flower_photos\\"
# 转换之前数据是uint8类型和HWC的格式，各个图片大小不同
transform = torchvisiontrans.Compose([torchvisiontrans.Scale((224,224)),
                                      torchvisiontrans.ToTensor(),
                                      torchvisiontrans.Normalize(mean=[0,0,0],std=[1,1,1],inplace=False),])
# 使用ToTensor()此时才会映射为float.32，标签int64
train_data = torchvisondata.ImageFolder(path,transform=transform,target_transform=None)
# a = plt.imread(train_data.imgs[0][0])
# print(a.shape,a.dtype)# (263, 320, 3) uint8
train_loader_ = torchdata.DataLoader(dataset=train_data,batch_size=64,shuffle=True,num_workers=2)
for step,(bx,by) in enumerate(train_loader_):
    print(step,bx.shape, bx.dtype,by.shape,by.dtype,torch.max(bx),torch.min(bx))
# torch.Size([22, 3, 224, 224]) torch.float32 torch.Size([22]) torch.int64 tensor(1.) tensor(0.)
#%%
a = np.array([[[255,255,127],[255,255,127]],
              [[255,255,127],[255,255,127]],
              [[255,255,127],[255,255,127]]]).astype(np.uint8)
trans = torchvisiontrans.ToTensor()
b = trans(a)
print(a.shape,b.shape,a.dtype,b.dtype)

#%%





