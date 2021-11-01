#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 一个提升的例子（图像分类）.py
@Author : chenbei
@Date : 2021/10/4 14:14
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
import torch.utils.data as torch_utils_data
import torchvision.datasets as torchvison_data
import sklearn.datasets as sklearn_datasets
import sklearn.decomposition as sklearn_decompose
import sklearn.preprocessing as sklearn_processing
import sklearn.metrics as sklearn_metric
import sklearn.manifold as sklearn_manifold
import sklearn.model_selection as sklearn_model_selection
import tensorboardX
import seaborn as sns
import copy
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
root = r"C:\Users\chenb\.torch"

#%% （1）获取数据和处理数据
# torch.set_default_dtype(torch.float32)
train_data = torchvison_data.FashionMNIST(root=root,train=True,download=False )
test_data = torchvison_data.FashionMNIST(root=root,train=False,download=False )

def process(data):
    x , y = data.data.type(torch.float32)/255.,data.targets
    x = torch.unsqueeze(x,dim=1)
    return x,y

train_x , train_y = process(train_data)
test_x , test_y = process(test_data)
batch_size = 128

train_data_ = torch_utils_data.TensorDataset(train_x,train_y)
train_loader = torch_utils_data.DataLoader(dataset=train_data_,shuffle=True,num_workers=2,batch_size=batch_size)
#%% （2）定义模型
class MyCNN(torch.nn.Module):
    def __init__(self):
        super(MyCNN,self).__init__()
        # 第一个卷积层 : (N,1,28,28)->(N,16,28,28)->(N,16,14,14)
        self.conv1 = torch.nn.Sequential(
            # (28 - 3 + 2)/1 + 1 = 28 <=> same
            torch.nn.Conv2d(in_channels=1,out_channels=16,kernel_size=(3,3),stride=(1,1),padding=1),
            torch.nn.ReLU(),
            torch.nn.AvgPool2d(kernel_size=2,stride=2),)
        # 第二个卷积层 : (N,16,14,14)->(N,32,12,12)->(N,32,6,6)
        self.conv2 = torch.nn.Sequential(
            torch.nn.Conv2d(16,32,(3,3),(1,1),0),
            torch.nn.ReLU(),
            torch.nn.AvgPool2d(2,2)
        )
        # 全连接输入(N,32*6*6)->(N,)
        self.classifier = torch.nn.Sequential(
            torch.nn.Flatten(),
            torch.nn.Linear(in_features=32*6*6,out_features=256,bias=True),
            torch.nn.ReLU(),
            torch.nn.Linear(256,128),
            torch.nn.ReLU(),
            torch.nn.Linear(128, 10),
            torch.nn.Softmax(dim=1)
        )
    def forward(self,input):
        x  = self.conv1(input)
        x = self.conv2(x)
        x = self.classifier(x)
        return x
model = MyCNN()

#%% （3）训练准备
opt  = torch.optim.Adam(model.parameters(),lr=0.0003)
loss_fn = torch.nn.CrossEntropyLoss()
epochs = 25
train_valid_rate = 0.8
best_val_acu = 0.

train_loss_lst,valid_loss_lst ,train_acu_lst,valid_acu_lst  = [],[],[],[]

#%%（4）开始训练
for epoch in tqdm(range(epochs)):

    for step , (batch_x , batch_y) in enumerate(train_loader):

        if step < round( len(train_loader) * train_valid_rate) :
            # 指定的前多少批为训练用，后面的验证用
            model.train()
            output_value = model(batch_x) # (batch_size,10)
            output_label = torch.argmax(output_value,dim=1) # 每个样本得到最大值索引(batch_size,1)
            train_loss = loss_fn(output_value,batch_y)
            train_acu = sklearn_metric.accuracy_score(batch_y,output_label)
            opt.zero_grad()
            train_loss.backward()
            opt.step()
            print("epoch %s step %s train_loss %.4f train_acu %.4f" % (epoch+1,step+1,train_loss,train_acu))

        else:
            model.eval()
            output_value = model(batch_x)
            output_label = torch.argmax(output_value, dim=1)
            val_loss = loss_fn(output_value, batch_y)
            val_acu = sklearn_metric.accuracy_score(batch_y,output_label)
            opt.zero_grad()
            val_loss.backward()
            opt.step()
            print("epoch %s step %s val_loss %.4f val_acu %.4f" % (epoch+1, step+1, val_loss, val_acu))
    # 只在每个epoch才append
    valid_loss_lst.append(val_loss)
    valid_acu_lst.append(val_acu)
    train_loss_lst.append(train_loss)
    train_acu_lst.append(train_acu)

    # valid_acu_lst至少1个元素 先和0比
    # 然后每个epoch都会和上个epoch去比
    # 所有epoch就结束后会得到最好的准确率和那时候的模型参数
    if valid_acu_lst[-1] > best_val_acu :
        best_val_acu = valid_acu_lst[-1]
        best_model_state = copy.deepcopy(model.state_dict())

#%% （5）使用最好的参数预测
model.load_state_dict(best_model_state)
model.eval()
test_output_values = model(test_x)
test_output_labels = torch.argmax(test_output_values,dim=1)
num = torch.sum(test_output_labels == test_y)
print("test_acu = %.5f" % (num.item()/len(test_y)))
confusion = sklearn_metric.confusion_matrix(y_true=test_y, y_pred=test_output_labels)
df = pd.DataFrame(confusion,index=test_data.classes,columns=test_data.classes)
heatmap = sns.heatmap(df,annot=True,fmt='d',cmap="rocket",annot_kws={"size":10})
heatmap.yaxis.set_ticklabels(heatmap.yaxis.get_ticklabels(),rotation=0,ha="right")
heatmap.xaxis.set_ticklabels(heatmap.xaxis.get_ticklabels(),rotation=45,ha="right")
plt.ylabel("True Label"),plt.xlabel("Predicted Label")
plt.show()
#%% （6）可视化结果
def plot_train_val():
    plt.subplot(121)
    plt.plot(train_acu_lst,label="train_acu")
    plt.plot(valid_acu_lst,label="val_acu")
    plt.xlabel("Epoch")
    plt.ylabel("Acu")
    plt.title("ACU")
    plt.legend()
    plt.subplot(122)
    plt.plot(train_loss_lst,label="train_loss")
    plt.plot(valid_loss_lst,label="val_loss")
    plt.xlabel("Epoch")
    plt.ylabel("Loss")
    plt.legend()
    plt.title("LOSS")
    plt.show()
plot_train_val()
#%% 保存模型
path = os.getcwd()+"\\Pytorch深度学习入门与实战\\fashion_mnist_cnn.pkl"
torch.save(model,path)
