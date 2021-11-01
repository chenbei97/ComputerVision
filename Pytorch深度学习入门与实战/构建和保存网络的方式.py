#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 构建和保存网络的方式.py
@Author : chenbei
@Date : 2021/10/2 15:03
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
import numpy as np
from tqdm import tqdm
import os
import hiddenlayer
import torchviz
import torch
import torch.utils.data as torchdata
import sklearn.datasets as sklearndata
import sklearn.preprocessing as sklearprocess
import sklearn.metrics as sklearnmetric
import tensorboardX
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
#  ①使用tensorboardX可视化训练过程
summaryWriter = tensorboardX.SummaryWriter(log_dir=os.getcwd()+"\\Pytorch深度学习入门与实战\\tensorboardXlog")
#  ②使用hiddenlayer可视化训练过程
canvas = hiddenlayer.Canvas() # 生成1个画布用于绘制
history = hiddenlayer.History() # 用于记录

ss = sklearprocess.StandardScaler(copy=True, with_mean=True, with_std=True)
batch_size = 16
boston_X , boston_y = sklearndata.load_boston(return_X_y=True)
boston_X = ss.fit_transform(X=boston_X, y=None)
train_xt, train_yt = torch.from_numpy(boston_X.astype(np.float32)),torch.from_numpy(boston_y.astype(np.float32))
train_data = torchdata.TensorDataset(train_xt,train_yt)
train_dataset = torchdata.DataLoader(dataset=train_data,batch_size=batch_size,shuffle=True,num_workers=2)
print(len(train_dataset))
# 两种方式创建类都最好继承nn.Module
#%% （1）使用函数式结构构建
class Model_1(torch.nn.Module):
    def __init__(self):
        super(Model_1, self).__init__()
        self.hidden1 = torch.nn.Linear(in_features=boston_X.shape[1],out_features=10,bias=True)
        self.active1 = torch.nn.ReLU()
        self.hidden2 = torch.nn.Linear(10,10)
        self.active2 = torch.nn.ReLU()
        self.regression = torch.nn.Linear(10,1)
    def forward(self,x):
        x = self.hidden1(x)
        x = self.active1(x)
        x = self.hidden2(x)
        x = self.active2(x)
        x = self.regression(x)
        self.out = x
        return x
model_1 = Model_1()
print(model_1)
opt = torch.optim.SGD(model_1.parameters(),momentum=0.9,lr=0.001)
scheduler = torch.optim.lr_scheduler.ExponentialLR(opt,gamma=0.1) # new_lr=initial_lr×γ ^epoch
loss_fn = torch.nn.MSELoss(reduction='mean') # 回归
Train_loss = [] # 存放每个批的平均损失
Acu = []
epochs = 100
# step = len(train_xt) // batch_size  506 = 15 * 32 + 26
# step 要执行 15 + 1 = 16 次 step = 0,1,2,...,15
# max(step)+1=len(train_dataset)=16
# 一共执行 epoch * len(train_dataset)=800次
# 故这里考虑每5步记录一次 800/5=160
print_step = 5
loss_scalar_value = 0 # 全局每步损失的累计值
acu_scalar_value = 0
bar = tqdm(range(epochs))
for epoch in bar:
    for step , (batch_x,batch_y) in enumerate(train_dataset):
        out = model_1(batch_x).flatten()
        # print(out.shape) # torch.Size([64, 1])
        train_loss = loss_fn(out,batch_y)
        acu = sklearnmetric.explained_variance_score(y_true=batch_y.detach().numpy(), y_pred=out.detach().numpy())
        #print("epoch %s step %s loss %.5f acu %.5f"%(epoch,step,train_loss.detach().numpy(),acu))
        # 全局来看当前执行到的步数=当前epoch正在执行的step+以往执行完的epoch*(max(step)+1)=epoch*len(train_dataset)
        global_step = step + 1 + epoch * len(train_dataset)
        loss_scalar_value += train_loss.item()
        acu_scalar_value += acu
        if global_step % print_step == 0 :
            # ①使用tensorboardX可视化训练过程
            # 每 print_step步记录一次执行到当前的损失 = 累加损失/当前迭代次数
            #summaryWriter.add_scalar(tag='mse_Loss',scalar_value=loss_scalar_value/global_step,global_step=global_step)# 添加标量
            #summaryWriter.add_scalar(tag='explained_variance_score', scalar_value=acu_scalar_value/global_step, global_step=global_step)
            #print(loss_scalar_value/global_step,acu_scalar_value/global_step)
            # for name,param in model_1.named_parameters():
            #     summaryWriter.add_histogram(name,param.data.numpy(),global_step)
            #  ②使用hiddenlayer可视化训练过程
            history.log((epoch,step),mse_loss=loss_scalar_value/global_step,
                        explained_variance_score=acu_scalar_value/global_step,hidden_weight=model_1.hidden1.weight)
            with canvas :
                canvas.draw_plot(history["mse_loss"])
                canvas.draw_plot(history["explained_variance_score"])
                canvas.draw_image(history["hidden_weight"])
        opt.zero_grad()  # 梯度清零
        train_loss.backward() # 反向传播
        opt.step() # 更新梯度
    Train_loss.append(train_loss.item()) # 只要每个epoch结束的值
    Acu.append(acu)
    bar.set_description("epoch %s  loss %.5f acu %.5f"
                            % (epoch,train_loss.detach().numpy(),acu))
    scheduler.step()

#%%
# assert len(Train_loss) == epochs * (len(train_data)//batch_size+1)
fig , ax = plt.subplots()
axx = ax.twinx()
ax.plot(Train_loss,label='loss',color='b')
ax.set_xlabel("epoch")
ax.set_ylabel("loss")
axx.plot(Acu,label='acu',color='r')
axx.set_xlabel("acu")
axx.set_ylim((0,1))
ax.set_title("loss/acu per epoch")
fig.legend()
fig.show()
#%%
# 保存整个模型
path = os.getcwd()+"\\Pytorch深度学习入门与实战\\保存模型.pkl"
# torch.save(model_1,path)
# model = torch.load(path) # 加载模型
# 只保存模型参数
torch.save(model_1.state_dict(),path)
model_param = torch.load(path)
print(model_param)
#%% 保存网络结构图片
# ① 使用hiddenlayer保存
model = Model_1()
graph = hiddenlayer.build_graph(model=model,args=torch.zeros([516,13]))
graph.theme = hiddenlayer.graph.THEMES["blue"]
graph.save("graph.png",format="png")
# ②使用torchviz保存
output = model(train_xt)#需要计算输出,作为make_dot的参数
graph_ = torchviz.make_dot(output,params=dict(list(model.named_parameters())+[('input',train_xt)]))
graph_.format = "png"
graph_.directory = "graph"
graph_.view()
#%%（2）使用顺序结构nn.Sequential构建
class Model_2(torch.nn.Module):
    def __init__(self):
        super(Model_2, self).__init__()
        self.hidden = torch.nn.Sequential(
            torch.nn.Linear(in_features=boston_X.shape[1], out_features=10, bias=True),
            torch.nn.ReLU(),
            torch.nn.Linear(10, 10),
            torch.nn.ReLU(),
        )
        self.regression = torch.nn.Linear(10, 1)
    def forward(self,x):
        x = self.hidden(x)
        x = self.regression(x)
        self.out = x
        return x
model_2 = Model_2()












