#%%
# -*- coding UTF-8 -*-
'''
@Project : MyPythonProjects
@File : 电流csv数据处理.py
@Author : chenbei
@Date : 2021/8/19 13:12
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
from time import time
font_set = FontProperties(fname=r"C:\Windows\Fonts\simsun.ttc", size=10.5)
import numpy as np
import pandas as pd
import tensorflow as tf
from tensorflow.keras import layers, Sequential
from sklearn.preprocessing import  LabelEncoder,scale
import os
# 【1】使用pandas从csv读取数据并随即拆分数据集
PATH = os.getcwd()+"\\MyPlatform\\current_pca_features_data.csv"
DATA = pd.read_csv(PATH,encoding='gbk')
Encoder = LabelEncoder()
X = DATA.copy()
y = X.pop("Category")
y = Encoder.fit_transform(y)
TrainSize = 0.6
TrainNum = int(np.ceil(TrainSize * len(y)))
ValSize = 0.2
x_train = X.sample(frac=0.6,axis=0)
y_train = y[x_train.index]
# X.index.isin(x_train.index)比较两个索引 相等为True返回长度和X相同的bool数组
# 表达式返回的实际上是x_train的索引,还需取反操作
x_val = X[~X.index.isin(x_train.index)]
x_test = x_val.sample(frac=0.5,axis=0)
x_val = x_val.drop(index=x_test.index)
y_val = y[x_val.index]
y_test = y[x_test.index]
# 检查分割后的数据集是否有交叉重复的数据
A = set(np.hstack((np.hstack((x_test.index.array,x_train.index.array)),x_val.index.array)))
# 【2】将Dataframe格式转换至张量数据格式
def dataframe_to_tensor(X,y,batch_size=16):
    if  not (isinstance(X,type(pd.DataFrame())) and isinstance(y,type(np.array([])))):
        print("输入类型错误！")
    else:
        X = tf.convert_to_tensor(X.values,dtype=tf.float64)
        y = tf.convert_to_tensor(y,dtype=tf.int64)
        dataset = tf.data.Dataset.from_tensor_slices((X,y))
        def preprocess(X,y):
            # X_mean, X_std = tf.nn.moments(X, axes=1)  # 按列归一化
            pass
        dataset = dataset.shuffle(len(X)).repeat(count=10).batch(batch_size).prefetch(1)
    return dataset
trainSet = dataframe_to_tensor(x_train,y_train)
valSet = dataframe_to_tensor(x_val,y_val)
testSet = dataframe_to_tensor(x_test,y_test)
batch_size = 16
model = Sequential([
    tf.keras.layers.Dense(20, activation=tf.nn.relu, input_shape=(2,)),
    tf.keras.layers.Dense(8)])
loss = tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True)#model没使用softmax
acu = tf.keras.metrics.SparseCategoricalAccuracy()
# 设置指数学习率衰减 initial_learning_rate * decay_rate ^ (step / decay_steps)
exponential_decay = tf.keras.optimizers.schedules.ExponentialDecay(
                        initial_learning_rate = 0.1,
                        decay_steps = TrainNum // batch_size + 1, # 145 // 16 + 1 = 10
                        decay_rate=0.98,# 迭代decay_steps个step后，学习率降为原来的0.98倍
                        staircase=True) #如果是False，学习率会平滑地衰减，而非每迭代10轮才衰减一次
                        # 如果为True，则会每迭代10次才衰减一次，这种称为阶梯函数
optimizer = tf.keras.optimizers.Adam(learning_rate=exponential_decay)
epochs = 20
Loss_Acu = [[],[]] # epoch * step
Val_Loss_Acu = [[],[]] # epoch
for epoch in range(epochs):
    for  step , (feature , y_true) in  enumerate(trainSet):
        step_time_start = time()
        with tf.GradientTape() as tape:
            y_pred = model(feature)
            loss_value = loss(y_true=y_true,y_pred=y_pred)
            acu_value = acu(y_true=y_true,y_pred=y_pred)
        grads = tape.gradient(loss_value, model.trainable_variables)
        optimizer.apply_gradients(zip(grads, model.trainable_variables))
        step_time_end = time()
        # if epoch % 10 == 0:
        print("epoch %d step %d loss %.5f acu %.5f time %.5fs" % (epoch,step,loss_value.numpy(),acu_value.numpy(),step_time_end-step_time_start))
        Loss_Acu[0].append(loss_value.numpy())
        Loss_Acu[1].append(acu_value.numpy())
    for val_feature, val_y_true in (valSet) :
        val_time_start = time()
        val_y_pred = model(val_feature)
        val_loss = tf.keras.losses.sparse_categorical_crossentropy(y_true=val_y_true,y_pred=val_y_pred,from_logits=True)
        val_acu = tf.keras.metrics.sparse_categorical_accuracy(y_true=val_y_true,y_pred=val_y_pred)
        val_loss = tf.reduce_mean(val_loss)
        val_acu = tf.reduce_mean(val_acu)
        val_time_end = time()
        print("epoch {:d} val_loss {:.5f} val_acu {:.5f} val_time {:.5f}s".format(epoch,val_loss.numpy(),val_acu.numpy(),val_time_end-val_time_start))
        Val_Loss_Acu[0].append(val_loss.numpy())
        Val_Loss_Acu[1].append(val_acu.numpy())
#%% 预测数据
Test_Acu = tf.constant([])
for step,(test_feature, test_y_true) in enumerate(testSet) :
    test_y_pred = model.predict(test_feature)
    test_y_pred = tf.nn.softmax(test_y_pred)
    test_y_pred = tf.argmax(test_y_pred,axis=1)
    equal = tf.equal(test_y_pred,test_y_true)
    for i in range(len(test_y_pred)) :
        print(f"step:{step+1} y_pred:{test_y_pred[i].numpy()} y_true:{test_y_true[i].numpy()} correct：{'y'if equal[i] else 'n'}")

#%%
# 找到索引199,399,..,的列表元素
def epoch_loss_acu(list,index):
    assert len(list) == 2
    return [list[index][x] for x in np.where(np.arange(len(list[0])) % (len(list[index]) // epochs) == 0)[0]]
train_loss_epoch = epoch_loss_acu(Loss_Acu,index=0)
train_acu_epoch =  epoch_loss_acu(Loss_Acu,index=1)
val_loss_epoch = epoch_loss_acu(Val_Loss_Acu,index=0)
val_acu_epoch =  epoch_loss_acu(Val_Loss_Acu,index=1)
fig,ax = plt.subplots(2,1,sharex=True)
ax = ax.flatten()
ax[0].plot(train_loss_epoch)
ax[0].plot(val_loss_epoch)
ax[0].legend(labels=['train_loss','val_loss'])
ax[1].plot(train_acu_epoch)
ax[1].plot(val_acu_epoch)
ax[1].legend(labels=['train_acu','val_acu'])
ax[1].set_xlabel("epoch")
plt.show()