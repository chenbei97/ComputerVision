#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 对预训练的CNN网络微调和使用.py
@Author : chenbei
@Date : 2021/10/4 16:32
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
plt.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
plt.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
plt.rcParams['savefig.dpi'] = 600  # 图片像素
#plt.rcParams['figure.dpi'] = 600  # 分辨率
root = os.path.join(os.getcwd(), "ImageProcessing")
img_dir = os.path.join(root, "images")

#%% （1）导入模型和数据
vgg16 = torchvision.models.vgg16(pretrained=True)

vgg = vgg16.features # 只使用特征提取层，不包括全连接
for param in vgg.parameters():
    param.requires_grad_(False) # 不可训练

batch_size = 32

train_transform = torchvison_trans.Compose([
    torchvison_trans.transforms.RandomSizedCrop(224), # vgg16输入是224
    torchvison_trans.transforms.RandomHorizontalFlip(),
    torchvison_trans.transforms.ToTensor(),
    torchvison_trans.transforms.Normalize([0.485,0.456,0.406],[0.229,0.224,0.225])
])
val_transform = torchvison_trans.Compose([
    torchvison_trans.transforms.Resize(256), # vgg16输入是224
    torchvison_trans.transforms.CenterCrop(224), # 从给定的size中心裁剪
    torchvison_trans.transforms.ToTensor(),
    torchvison_trans.transforms.Normalize([0.485,0.456,0.406],[0.229,0.224,0.225])
])

root = "C:\\Users\\chenb\\.torch\\10-monkey-species\\"
train_data = torchvison_data.ImageFolder(root=root+"training",transform=train_transform)
val_data = torchvison_data.ImageFolder(root=root+"validation",transform=val_transform)

train_loader = torch_utils_data.DataLoader(train_data,batch_size=batch_size,shuffle=True,num_workers=2)
val_loader = torch_utils_data.DataLoader(val_data,batch_size=batch_size,shuffle=True,num_workers=2)

#%% （2）利用预训练模型构建自己的模型
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
model = MyVgg16()
print(model)

#%% （3）训练过程
history = hiddenlayer.History() # 耗时
canvas = hiddenlayer.Canvas()
loss_fn = torch.nn.CrossEntropyLoss()
opt = torch.optim.Adam(model.parameters(),lr=0.0001)
epochs = 10
total_train_loss,  total_val_loss = [0, 0]  # 每个epoch总损失和总正确个数
# 全局当前步训练完累积的样本数和正确的个数
total_train_samples, total_train_corrects= 0,0
total_val_samples, total_val_corrects= 0,0
train_loss_lst, train_acu_lst = [], []
val_loss_lst, val_acu_lst = [], []
for  epoch in tqdm(range(epochs)):
    model.train()
    for step , (batch_x,batch_y) in enumerate(train_loader):
        output = model(batch_x)
        loss = loss_fn(output,batch_y)
        label = torch.argmax(output,1)

        opt.zero_grad()
        loss.backward()
        opt.step()

        total_train_loss += loss.item() # 到当前周期当前步的累积损失
        global_step = step + 1 + epoch * len(train_loader) # 当前第多少步
        avarage_train_loss = total_train_loss / global_step # 到当前周期当前步的平均损失

        correct_nums = torch.sum(label == batch_y).item()  # 当前步正确的个数
        # correct_acu = sklearn_metric.accuracy_score(batch_y, label)  # 当前步的得分

        total_train_corrects += correct_nums # 到当前周期当前步的累积正确个数
        total_train_samples += len(batch_y) # 当前步训练完的累积样本数

        avarage_train_acu = total_train_corrects / total_train_samples# 当前步的累积平均得分

        # print(f"epoch={epoch + 1} step={step + 1} correct_nums={correct_nums} correct_acu={correct_acu}\n"
             # f"total_corrects={total_corrects} total_samples={total_samples} avarage_train_acu={avarage_train_acu}\n"
            #  f"total_train_loss={total_train_loss} global_step={global_step} avarage_train_loss={avarage_train_loss}")

        print(f"epoch={epoch + 1} train_step={step + 1} train_acu={avarage_train_acu} val_loss ={avarage_train_loss} correct_nums={correct_nums}")
        train_acu_lst.append(avarage_train_acu)
        train_loss_lst.append(avarage_train_loss)
    model.eval()
    for step , (batch_x,batch_y) in enumerate(val_loader):
        output = model(batch_x)
        loss = loss_fn(output,batch_y)
        label = torch.argmax(output,1)

        total_val_loss += loss.item() # 到当前周期当前步的累积损失
        global_step = step + 1 + epoch * len(val_loader) # 当前第多少步
        avarage_val_loss = total_val_loss / global_step # 到当前周期当前步的平均损失

        correct_nums = torch.sum(label == batch_y).item()  # 当前步正确的个数

        total_val_corrects += correct_nums # 到当前周期当前步的累积正确个数
        total_val_samples += len(batch_y) # 当前步训练完的累积样本数

        avarage_val_acu = total_val_corrects / total_val_samples# 当前步的累积平均得分

        print(f"epoch={epoch + 1} val_step={step + 1} val_acu={avarage_val_acu} val_loss ={avarage_val_loss} correct_nums={correct_nums}")
        val_acu_lst.append(avarage_val_acu)
        val_loss_lst.append(avarage_val_loss)

    # print(f"epoch_train_loss={np.max(train_loss_lst)} epoch_train_acu={np.max(train_acu_lst)}")

    # 只记录每个周期的最好的那步
    # history.log(epoch,train_loss=np.max(train_loss_lst),train_acu=np.max(train_acu_lst))
    # with canvas:
        # canvas.draw_plot(history["total_corrects"])
        # canvas.draw_plot(history["correct_nums"])
        # canvas.draw_plot(history["correct_acu"])
        # canvas.draw_plot(history["train_loss"])
        # canvas.draw_plot(history["train_acu"])

#%% （4）保存网络
torch.save(model,root+"10_monkey_species_model_pycharm.pkl")
df1,df2 = pd.DataFrame(),pd.DataFrame()
df1["train_loss"] =train_loss_lst
df1["train_acu"] =train_acu_lst
df2["val_loss"] =val_loss_lst
df2["val_acu"] =val_acu_lst
df1.to_csv(path_or_buf=root+"train_loss_acu.csv",index=False)
df2.to_csv(path_or_buf=root+"val_loss_acu.csv",index=False)
#%%  (5) 可视化
def plot_train_val():
    plt.subplot(121)
    plt.plot(train_acu_lst,label="train_acu")
    plt.plot(val_acu_lst,label="val_acu")
    plt.xlabel("Step")
    plt.ylabel("Acu")
    plt.title("ACU")
    plt.legend()
    plt.subplot(122)
    plt.plot(train_loss_lst,label="train_loss")
    plt.plot(val_loss_lst,label="val_loss")
    plt.xlabel("Step")
    plt.ylabel("Loss")
    plt.legend()
    plt.title("LOSS")
    plt.show()
plot_train_val()

#%% （6）测试保存的模型预测能力