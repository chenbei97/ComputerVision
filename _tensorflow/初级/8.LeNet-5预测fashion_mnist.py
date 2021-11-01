#%%
# -*- coding UTF-8 -*-
'''
@Project : MyPythonProjects
@File : 8.LeNet-5预测fashion_mnist.py
@Author : chenbei
@Date : 2021/8/13 14:07
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
from tensorflow.keras.metrics import CategoricalAccuracy
from tensorflow .keras .datasets import fashion_mnist
network = Sequential([
    # 网络容器 输入(4,28,28,1)单通道
    # paras = 3*3*1*6(权重)+6*1(偏置)=60
    layers.Conv2D(6,kernel_size=3,strides=1), # 第一个卷积层, 6个 3x3 卷积核 out_shape=(28-3+0)/1+1=26 (4,26,26,6)
    layers.BatchNormalization(), # 插入BN层
    layers.MaxPooling2D(pool_size=2,strides=2), # 高宽各减半的池化层 (4,13,13,6)
    layers.ReLU(), # 激活函数
    # paras = 3*3*6*16(权重)+16*1(偏置)=880
    layers.Conv2D(16,kernel_size=3,strides=1), # 第二个卷积层, 16 个 3x3 卷积核 (13-3+0)/1+1=11 (4,11,11,16)
    layers.BatchNormalization(),
    layers.MaxPooling2D(pool_size=2,strides=2), # 高宽各减半的池化层 (4,5,5,16)
    layers.ReLU(), # 激活函数
    layers.Flatten(), # 打平层，方便全连接层处理 (4,5*5*16)=(4,400)
    # 400*120+120=48120
    layers.Dense(120, activation='relu'), # 全连接层，120 个节点 (4,120)
    # 120*84+84=10164
    layers.BatchNormalization(),
    layers.Dense(84, activation='relu'), # 全连接层，84 节点 (4,84)
    # 84*10+10=850
    layers.BatchNormalization(),
    layers.Dense(10) # 全连接层，10 个节点 (4,10)
    ])
network.build(input_shape=(4, 28, 28, 1))
network.summary()
loss = losses.CategoricalCrossentropy(from_logits=True)#输出没有使用softmax层就可以使用from_logits=True
optimizer = optimizers.Adam(0.001)
categorical_accuracy = CategoricalAccuracy()
(train_x,train_y),(test_x,test_y) = fashion_mnist .load_data()
train_x = train_x / 255. * 2 -1
test_x = test_x / 255. * 2 -1  # [-1,1]
train_x = tf.expand_dims(train_x,-1).numpy() # 拓展维度 与模型要求的输入匹配
test_x  = tf.expand_dims(test_x, -1).numpy()
#%%
epochs = 50
for epoch in range(epochs):
    with tf.GradientTape() as tape:
        out = network(train_x,training=True) # training=True 以区分 BN 层是训练还是测试模型
        # print(out.shape) # (60000,10)
        train_y_onehot = tf.one_hot(train_y, depth=10)
        loss_value = loss(train_y_onehot, out)
        acu = categorical_accuracy(train_y_onehot,out)
        print("第 %d 周期：loss=%.3f acu=%.3f" % (epoch+1,loss_value,acu))
    grads = tape.gradient(loss_value, network.trainable_variables)
    optimizer.apply_gradients(zip(grads, network.trainable_variables))
test_y_pred = network.predict(test_x)
test_y_true = tf.cast(test_y,dtype=tf.int64)
test_y_class = tf.argmax(test_y_pred,axis=1)
test_acu = tf.reduce_sum(tf.cast(tf.equal(test_y_class,test_y_true),tf.float32) / len(test_y_class))
test_acu.numpy()
#%%
network.save(r"C:\Users\chenb\.keras\models\LeNet-5网络\LeNet_5.h5")
new_model = tf.keras.models.load_model(r"C:\Users\chenb\.keras\models\LeNet-5网络\LeNet_5.h5")