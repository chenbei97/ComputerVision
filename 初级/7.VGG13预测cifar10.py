#%%
# -*- coding UTF-8 -*-
'''
@Project : MyPythonProjects
@File : 7.VGG13预测cifar10.py
@Author : chenbei
@Date : 2021/8/13 16:42
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
from tensorflow.keras import Sequential,layers,losses, optimizers
from tensorflow.keras.metrics import CategoricalAccuracy ,SparseCategoricalAccuracy
from tensorflow.keras.datasets import cifar10
#【1】构建数据集
(x,y), (x_test, y_test) = cifar10.load_data() # 标记了 100 个细类别，这些类别分为 10 个粗类别
# x ,y = x[0:5000],y[0:5000]
# x_test ,y_test = x_test[0:2000],y_test[0:2000]
print(x.shape, y.shape)
# (50000, 32, 32, 3) (50000, 1) (10000, 32, 32, 3) (10000, 1)
# 删除 y 的一个维度，[b,1] => [b]
y = tf.squeeze(y, axis=1)
set(y.numpy()) # 查看y的标签
y_test = tf.squeeze(y_test, axis=1)
print(x.shape, y.shape)
# (50000, 32, 32, 3) (50000,) (10000, 32, 32, 3) (10000,)
def preprocess(x,y):
    x = tf.cast(x,dtype=tf.float32)
    x /= 2 * 255.0 - 1
    y = tf.cast(y, dtype=tf.int32)
    # x = tf.reshape(x,(32,32,3))
    # y = tf.one_hot(y,depth=10)
    return x,y
batch_size = 256
train_db = tf.data.Dataset.from_tensor_slices((x,y))
train_db = train_db.shuffle(1000).map(preprocess).batch(batch_size)
test_db = tf.data.Dataset.from_tensor_slices((x_test,y_test))
test_db = test_db.map(preprocess).batch(batch_size=batch_size)
x0 ,y0 = next(iter(train_db))
print('sample:', x0.shape, y0.shape) # (128, 1024, 3) (128,)
# 【2】对VGG13的调整
# ① 原网络输入为 224x224 调整为32x32 ② 全连子网络=3个全连接层的维度调整为[256,64,10]
# 卷积子网络=5个Convd-Convd-Pooling模块 filters=64,kernel_size=(3,3) pool_size=(2,2) strides=2
conv_layers = [
        # CBAPD = Convd + BatchNormalization + Activation + Pooling + Dropout
        # 当S=1时 padding="same"表示输入输出同大小 3个输入通道*kernel_size*64个输出通道+64个偏置=1792
        layers.Conv2D(64, kernel_size=[3, 3], padding="same", activation=tf.nn.relu),# N1/S
        layers.Conv2D(64, kernel_size=[3, 3], padding="same"),# 64*9*64+64=36928
        layers.BatchNormalization(), # 4个归一化参数(μr,μB,σr,σB)*通道数(按照通道数计算) 4*64=256
        layers.Activation(tf.nn.relu),
        layers.MaxPool2D(pool_size=[2, 2], strides=2, padding='same'), # 输出尺寸:32//2=16
        layers.Dropout(0.2),
        layers.Conv2D(128, kernel_size=[3, 3], padding="same", activation=tf.nn.relu),# 64*9*128+128=73856
        layers.Conv2D(128, kernel_size=[3, 3], padding="same"),# 128*9*128+128=147584
        layers.BatchNormalization(),# 4*128=512
        layers.Activation(tf.nn.relu),
        layers.MaxPool2D(pool_size=[2, 2], strides=2, padding='same'),# 输出尺寸:16//2=8
        layers.Dropout(0.2),
        layers.Conv2D(256, kernel_size=[3, 3], padding="same", activation=tf.nn.relu),#128*9*256+256=295168
        layers.Conv2D(256, kernel_size=[3, 3], padding="same"),#256*9*256+256=590080
        layers.BatchNormalization(),  # 4*256=1024
        layers.Activation(tf.nn.relu),
        layers.MaxPool2D(pool_size=[2, 2], strides=2, padding='same'),# 输出尺寸:8//2=4
        layers.Dropout(0.2),
        layers.Conv2D(512, kernel_size=[3, 3], padding="same", activation=tf.nn.relu),#256*9*512+512=1180160
        layers.Conv2D(512, kernel_size=[3, 3], padding="same"),#512*9*512+512=2359808
        layers.BatchNormalization(), # 4*512=2048
        layers.Activation(tf.nn.relu),
        layers.MaxPool2D(pool_size=[2, 2], strides=2, padding='same'),# 输出尺寸:4//2=2
        layers.Dropout(0.2),
]
conv_net = Sequential(conv_layers) # 卷积子网络
dens_net = Sequential([ # 全连接子网络输入形状 (256, 2, 2, 512)
    layers.Flatten(), # 输入为512*4=2048个节点
    layers.Dropout(0.5),
    layers.Dense(256, activation=tf.nn.relu),#2048*256+256=524544
    layers.Dropout(0.5),
    layers.Dense(128, activation=tf.nn.relu),#256*128+128=32896
    layers.Dropout(0.5),
    layers.Dense(10, activation="softmax"),#128*10+10=1290
])
# conv_net.build(input_shape=[batch_size, 32,32, 3])
# dens_net.build(input_shape=[batch_size, 512])
# conv_net.summary() # Total params: 4,689,216 Trainable params: 4,687,296 Non-trainable params: 1,920
# dens_net.summary() # Total params: 165,514 Trainable params: 165,514 Non-trainable params: 0
# 注：单独编译时dens_net实际上指定输入为512个节点那么第一层参数为512*256+256
# 但是合并编译net输入节点为512*2*2，第一层参数量是2048*256+256=524544 那么dens_net总参数量为558730而非165514
net = Sequential([])
net.add(conv_net)
net.add(dens_net)
net.build(input_shape=[batch_size, 32,32, 3])
net.summary() # Total params: 5,247,946 Trainable params: 5,246,026 Non-trainable params: 1,920
#%%
#【3】构建迭代器
epochs = 30
opt = optimizers.Adam(learning_rate=0.0001)
loss = losses.SparseCategoricalCrossentropy(from_logits=False) # 稀疏标签使用 且输出已经softmax符合概率分布from_logits=False
acu = SparseCategoricalAccuracy()
#%% 自动训练模型
# net.save("123.h5")
# del net
# net = tf.keras.models.load_model("123.h5")
# net.evaluate(x_test/255.,y_test)
callback = tf.keras.callbacks.ModelCheckpoint(filepath="./checkpoints/my_checkpoint",save_best_only=True)
net.compile(optimizer=opt, loss=losses.SparseCategoricalCrossentropy(), metrics=['accuracy'])
#metrics=['accuracy']使用的是sparse_categorical_accuracy 所以要使用SparseCategoricalCrossentropy去匹配
net.fit(x/255., y, epochs=20, batch_size=256,
        verbose=1,validation_data=(x_test/255., y_test),
        validation_freq=1,
        callbacks=[callback])
#%% 手动训练
for epoch in range(epochs):
    for step,(train_x_batch,train_y_batch) in enumerate(train_db):
        with tf.GradientTape() as tape:
             output = net(train_x_batch)
             step_loss = loss(train_y_batch,output)
             step_acu = acu(train_y_batch, output)
        print("第%d步：step_loss %.5f step_acu %.5f"% (step+1,step_loss,step_acu)) # 50000//128=391
        grads = tape.gradient(step_loss, net.trainable_variables)
        opt.apply_gradients(zip(grads, net.trainable_variables))
net.save("C:\\Users\\chenb\\.keras\\models\\手动保存VGG13模型.h5")
#%%


