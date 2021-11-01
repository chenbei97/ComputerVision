#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 一个完整的例子（邮件分类）.py
@Author : chenbei
@Date : 2021/10/3 16:00
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
import sklearn.datasets as sklearn_datasets
import sklearn.decomposition as sklearn_decompose
import sklearn.preprocessing as sklearn_processing
import sklearn.metrics as sklearn_metric
import sklearn.manifold as sklearn_manifold
import sklearn.model_selection as sklearn_model_selection
import tensorboardX
import seaborn as sns
from Pytorch深度学习入门与实战 import pytorchtools

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
#%% （0）处理数据
root = r"C:\Users\chenb\.torch\spambase.csv"
data = pd.read_csv(root,encoding="gbk")
X = data.iloc[:,0:-1].values
y = data["category"].values
train_x,test_x,train_y,test_y = sklearn_model_selection.train_test_split(X, y, random_state=123, test_size=0.3)
scaler = sklearn_processing.MinMaxScaler(feature_range=(0, 1), copy=True)
# 不标准化可能会导致训练不收敛，loss和acu反复震荡
train_x ,test_x = scaler.fit_transform(train_x),scaler.fit_transform(test_x)
# 转换为张量之前随机好
train_x_tensor,test_x_tensor = torch.from_numpy(train_x.astype(np.float32)),torch.from_numpy(test_x.astype(np.float32))
train_y_tensor,test_y_tensor = torch.from_numpy(train_y.astype(np.int64)),torch.from_numpy(test_y.astype(np.int64))
#%% （1）可视化不同类别在所有特征上的数据分布情况
feature_names = data.columns.values[:12] # 所有特征的名称(不包含category列)
plt.figure()
for i in tqdm(range(len(feature_names))):
    plt.subplot(3,4,i+1)
    # 循环绘制每个列/特征 只画12个
    sns.boxplot(x=train_y,y=train_x[:,i])# y轴是某个特征的个数，x轴标签
    plt.title(feature_names[i])
plt.subplots_adjust(hspace=0.8)
plt.show()
#%% （2）搭建网络
class SpambaseNet(torch.nn.Module):
    def __init__(self):
        super(SpambaseNet,self).__init__()
        self.dense1 = torch.nn.Sequential(torch.nn.Linear(in_features=57,out_features=40,bias=True),
                                        torch.nn.ReLU(),)
        self.dense2 = torch.nn.Sequential(torch.nn.Linear(in_features=40,out_features=20,bias=True),
                                        torch.nn.ReLU(),)
        self.dense3 = torch.nn.Sequential(torch.nn.Linear(in_features=20,out_features=10,bias=True),
                                        torch.nn.ReLU(),)
        self.classifier = torch.nn.Sequential(torch.nn.Linear(in_features=10,out_features=2,bias=True),
                                        torch.nn.Sigmoid(),)
    def forward(self,input):
        d1 = self.dense1(input)
        d2 = self.dense2(d1)
        d3 = self.dense3(d2)
        output = self.classifier(d3)
        self.output = output
        return d1,d2,d3,output
model = SpambaseNet()

#%% （3）可视化网络层和保存为pdf
temp_x = torch.from_numpy(X.copy().astype(np.float32))
temp_x.requires_grad = True
temp_y = model(temp_x)
print(temp_y[-1][0]) # 预测结果
# 返回值和索引 dim=1表示在第2个维度去比较大小 也就是某行的列元素之间比较
values,indices = torch.max(temp_y[-1],dim=1)
indices_ = torch.argmax(temp_y[-1],dim=1)
print(torch.all(indices == indices_))
#%%
netView = torchviz.make_dot(temp_y,params=dict( [("input",temp_x)]+list(model.named_parameters()))) # 给定每个层的名称
netView.directory = os.getcwd()+ "\\Pytorch深度学习入门与实战"
netView.view()
#%% （4）数据加载器
model = SpambaseNet()
batch_size = 64
print_step = 25
epochs = 50
patience = 8	# 当验证集损失在连续20次训练周期中都没有得到降低时，停止模型训练，以防止模型过拟合
early_stop = False # 发现早期停止时break
train_set = torch.utils.data.TensorDataset(train_x_tensor,train_y_tensor)
dataLoader = torch.utils.data.DataLoader(dataset=train_set,batch_size=batch_size,shuffle=True,num_workers=2)

opt = torch.optim.Adam(model.parameters(),lr=0.01)
scheduler = torch.optim.lr_scheduler.ExponentialLR(opt,gamma=0.1)
loss_fn = torch.nn.CrossEntropyLoss()
early_stopping = pytorchtools.EarlyStopping(patience, verbose=True)

# 需要打开绘图的交互式后端
history = hiddenlayer.History()
canvas = hiddenlayer.Canvas()
#%% （5）训练模型
for epoch in tqdm(range(epochs)):
    if early_stop :
        break
    for step , (batch_x , batch_y) in enumerate(dataLoader):

        _,_,_,train_output = model(batch_x)

        train_loss = loss_fn(train_output ,batch_y) # 训练损失

        train_output = torch.argmax(train_output, dim=1)
        train_acu = sklearn_metric.accuracy_score(y_true=batch_y, y_pred=train_output)

        opt.zero_grad()
        train_loss.backward()
        opt.step()

        global_step =  step + 1  + epoch * len(dataLoader)

        if global_step % print_step == 0 :
            # 每 print_step 对测试集验证
            _,_,_,test_output = model(test_x_tensor)
            test_loss = loss_fn(test_output, test_y_tensor)
            # dim=1表示在第2个维度去比较大小 也就是某行的列元素之间比较
            # 返回较大值的值和对应索引,二分类非0即1，恰好是标签值
            # _ , test_output = torch.max(test_output,dim=1)

            test_output = torch.argmax(test_output,dim=1)
            test_acu = sklearn_metric.accuracy_score(y_true=test_y_tensor, y_pred=test_output)

            history.log(global_step,train_loss = train_loss.item(),train_acu=train_acu,
                        test_acu=test_acu,test_loss=test_loss.item())

            with canvas :
                canvas.draw_plot(history["train_loss"])
                canvas.draw_plot(history["train_acu"])
                canvas.draw_plot(history["test_loss"])
                canvas.draw_plot(history["test_acu"])

            early_stopping(test_loss, model)
            if early_stopping.early_stop:
                early_stop = True
                print("Find Early Stopping ,Break。。。")
                break
    scheduler.step()
#%% （6）模型预测
d1,d2,d3,label = model(test_x_tensor)

label = torch.argmax(label,dim=1)

print(sklearn_metric.accuracy_score(test_y_tensor,label))

#%% （7）对隐含层的输出可视化

tsne = sklearn_manifold.TSNE(n_components=2).fit_transform(d3.data.numpy())
pca = sklearn_decompose.PCA(n_components=2).fit_transform(d3.data.numpy())

def compare_tsne_pca():
    plt.subplot(121)
    plt.scatter(tsne[:,0],tsne[:,1],c=label.ravel())
    plt.title("TSNE")

    plt.subplot(122)
    plt.scatter(pca[:, 0], tsne[:, 1],c=label.ravel())
    plt.title("PCA")

    plt.show()
compare_tsne_pca()

#%% （8）利用钩子获取中间层的输出
layer_output = {}
def get_layer_output(layer_name):
    # 字典的key=层的名字 value=层的输出
    def hook(model,input,output):
        layer_output[layer_name] = output.detach()
    return  hook
model.dense3.register_forward_hook(hook=get_layer_output(layer_name="dense3"))
_,_,_,_ = model(test_x_tensor)
dense3_output = layer_output["dense3"].data.numpy()





