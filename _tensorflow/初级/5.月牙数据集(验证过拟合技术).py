#%%
# -*- coding UTF-8 -*-
'''
@Project : MyPythonProjects
@File : 5.月牙数据集(验证过拟合技术).py
@Author : chenbei
@Date : 2021/8/12 11:22
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl

plt.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
plt.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
plt.rcParams['savefig.dpi'] = 600  # 图片像素
plt.rcParams['figure.dpi'] = 600  # 分辨率
from matplotlib.font_manager import FontProperties
font_set = FontProperties(fname=r"C:\Windows\Fonts\simsun.ttc", size=10.5)
import numpy as np
import pandas as pd
import tensorflow as tf
from sklearn.datasets import make_moons
from sklearn.model_selection import train_test_split
N_SAMPLES = 1000
TEST_SIZE = 0.2
X, y = make_moons(n_samples = N_SAMPLES, noise=0.25, random_state=100)
X_train, X_test, y_train, y_test = train_test_split(X, y,test_size = TEST_SIZE, random_state=42)
xx = np.linspace(int(X[:,0].min())-1, int(X[:,0].max())+1, N_SAMPLES )
yy = np.linspace(int(X[:,1].min())-1, int(X[:,1].max())+1, N_SAMPLES )
XX , YY = np.meshgrid(xx, yy)
def make_plot(X, y, plot_name, XX=None, YY=None, preds=None):
     X = np.array(X)
     y = np.array(y)
     plt.figure()
     axes = plt.gca()
     axes.set_xlim([X.min()-1,X.max()+1])
     axes.set_ylim([y.min()-1,y.max()+1])
     axes.set(xlabel="$x_1$", ylabel="$x_2$")
     # 根据网络输出绘制预测曲面
     if(XX is not None and YY is not None and preds is not None):
         # 先将1000000*1的preds也就是预测标签重塑形状为二维平面(1000,1000)坐标的取值，这里是非0即1的
         # 然后对这些点进行绘制
         plt.contourf(XX, YY, preds.reshape(XX.shape), 25, alpha = 0.5,cmap=plt.cm.cool)# 三维等高线的轮廓填充图
         plt.contour(XX, YY, preds.reshape(XX.shape), levels=[0.5,1],cmap="winter",vmin=0, vmax=.6) # 三维等高线的轮廓线
     # 绘制正负样本
     postive_x = X[y==1]
     negative_x = X[y==0]
     plt.scatter(postive_x[:, 0], postive_x[:, 1], c='r', s=20, edgecolors='none', marker='o')
     plt.scatter(negative_x[:, 0], negative_x[:, 1], c='b', s=20,  edgecolors='none', marker='+')
     plt.title(plot_name, fontsize=30)
     plt.show()
make_plot(X, y, '月牙数据集可视化')
N_EPOCHS = 100
#%% 【1】网络层数对数据集区分的影响
for n in range(5): # 构建 5 种不同层数的网络
    model = tf.keras.Sequential()# 创建容器
    # 创建第一层 输出节点8 要求输入形状2
    model.add(tf.keras.layers.Dense(8,input_dim=2,activation='relu'))
    for _ in range(n): # 添加 n 层，共 n+2 层
        model.add(tf.keras.layers.Dense(32, activation='relu'))
    model.add(tf.keras.layers.Dense(1, activation='sigmoid')) # 创建最末层
    model.compile(loss='binary_crossentropy', optimizer='adam',metrics=['accuracy']) # 模型装配与训练
    history = model.fit(X_train, y_train, epochs=N_EPOCHS, verbose=1)
    # 绘制不同层数的网络决策边界曲线
    preds = model.predict_classes(np.c_[XX.ravel(), YY.ravel()])
    # 按行连接两个展开的网格点 1000000*2 送入predict_classes
    # 相当于不仅预测实际的数据，而是对实际数据所产生的等分1000份的所有二维数据点都进行预测
    # 一个坐标点得到1个标签preds 故preds.shape=(1000000,1)
    title = "隐含层数({})网络容量({})".format(n,2+n*1)
    make_plot(X_train, y_train, title, XX, YY, preds)
#%% 【2】Droput的影响
for n in range(5): # 构建 5 种不同数量 Dropout 层的网络
    model = tf.keras.Sequential()  # 创建
    # 创建第一层 输出节点8 要求输入形状2
    model.add(tf.keras.layers.Dense(8, input_dim=2, activation='relu'))
    counter = 0
    for _ in range(5):  # 网络层数固定为 5
        # n=0 : Dense + 5个Dense
        # n=1 : Dense + Dense + Dropout + 4个Dense
        # n=2 ：Dense + Dense + Dropout + Dense + Dropout + 3个Dense
        # ...
        # n=4 ：Dense + (Dense,Dropout) + (Dense,Dropout) + (Dense,Dropout) + (Dense,Dropout) + Dense
        model.add(tf.keras.layers.Dense(64, activation='relu'))
        if counter < n:  # 添加 n 个 Dropout 层 n最大取到4
            counter += 1
            model.add(tf.keras.layers.Dropout(rate=0.5))
    model.add(tf.keras.layers.Dense(1, activation='sigmoid'))  # 输出层
    model.compile(loss='binary_crossentropy', optimizer='adam',metrics=['accuracy']) # 模型装配
    history = model.fit(X_train, y_train, epochs=N_EPOCHS, verbose=1)
    # 绘制不同 Dropout 层数的决策边界曲线
    preds = model.predict_classes(np.c_[XX.ravel(),YY.ravel()])
    title = "Dropout层数({})".format(counter)
    make_plot(X_train, y_train, title, XX, YY, preds)
#%%【3】正则化系数的影响
def build_model_with_regularization(_lambda):
    # 创建带正则化项的神经网络
    model = tf.keras.Sequential()
    model.add(tf.keras.layers.Dense(8, input_dim=2,activation='relu')) # 不带正则化项
    model.add(tf.keras.layers.Dense(256, activation='relu', kernel_regularizer=tf.keras.regularizers.l2(_lambda)))# 带 L2 正则化项
    model.add(tf.keras.layers.Dense(256, activation='relu', kernel_regularizer=tf.keras.regularizers.l2(_lambda)))# 带 L2 正则化项
    model.add(tf.keras.layers.Dense(256, activation='relu', kernel_regularizer=tf.keras.regularizers.l2(_lambda)))# 带 L2 正则化项
    # 输出层
    model.add(tf.keras.layers.Dense(1, activation='sigmoid'))
    model.compile(loss='binary_crossentropy', optimizer='adam',metrics=['accuracy']) # 模型装配
    return model
def plot_weights_matrix(model,weightIndex,plot_title) :
    # weightIndex 指定绘制的权重
    trainable_weights  = model.trainable_weights
    weights = trainable_weights[weightIndex].numpy()
    # np.set_printoptions(precision=4,suppress=True)
    # print("W2权值：平均值{} 最大值{} 最小值{}".format(np.mean(weights),weights.max(),weights.min()))
    xx = np.linspace(int(weights.min())-1, int(weights.max())+1, len(weights))
    yy = np.linspace(int(weights.min())-1, int(weights.max())+1, len(weights))
    XX , YY = np.meshgrid(xx,yy)
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.plot_surface(XX,YY,weights,cmap = plt.get_cmap('rainbow'))
    ax.set_zlim(-int(weights.min())-0.5, int(weights.max())+0.5)
    ax.set_xlabel("w2")
    ax.set_ylabel("w2")
    para = [np.round(weights.max(),2),np.round(weights.min(),2),np.round(np.mean(weights),2)]
    ax.set_title(plot_title+" W{:d}：最大值{:.5f} 最小值{:.5f} 平均值{:.5f}"
                 .format(weightIndex//2,para[0],para[1],para[-1]))
    plt.show()
# 保持网络结构不变的条件下，调节正则化系数𝜆测试网络的训练效果
def model_test_lambda(_lambdas,weightIndex):
    for _lambda in _lambdas :
        model = build_model_with_regularization(_lambda)
        history = model.fit(X_train, y_train, epochs=N_EPOCHS, verbose=1)
        # 绘制权值范围
        plot_title = "lambda = {}".format(str(_lambda))
        # 绘制网络权值范围图
        plot_weights_matrix(model,weightIndex=weightIndex,plot_title=plot_title)
        preds = model.predict_classes(np.c_[XX.ravel(), YY.ravel()])
        title = "正则化{}".format(_lambda)
        #make_plot(X_train, y_train, title, XX, YY, preds)
_lambdas = [0.00001,0.001,0.1,0.13]
model_test_lambda(_lambdas=_lambdas,weightIndex=4)
#%%




