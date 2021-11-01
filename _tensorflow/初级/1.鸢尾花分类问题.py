# %%
# -*- coding UTF-8 -*-
'''
@Project : MyPythonProjects
@File : 1.鸢尾花分类问题.py
@Author : chenbei
@Date : 2021/8/18 15:53
'''
from tensorflow.keras import layers, Sequential
from time import time
import tensorflow as tf
import os
import pandas as pd
import numpy as np
from matplotlib.font_manager import FontProperties
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

font_set = FontProperties(fname=r"C:\Windows\Fonts\simsun.ttc", size=10.5)
train_dataset_url = "https://storage.googleapis.com/download.tensorflow.org/data/iris_training.csv"
train_dataset_fp = tf.keras.utils.get_file(
    fname=os.path.basename(train_dataset_url),
    origin=train_dataset_url)  # 'C:\\Users\\chenbei\\.keras\\datasets\\iris_training.csv'
test_url = "https://storage.googleapis.com/download.tensorflow.org/data/iris_test.csv"
test_fp = tf.keras.utils.get_file(fname=os.path.basename(test_url),
                                  origin=test_url)
train_nums = 120
test_nums = 30
# %%
batch_size = 16
column_names = [
    'sepal_length',
    'sepal_width',
    'petal_length',
    'petal_width',
    'species']
label_name = column_names[-1]  # 指定特征列和标签列
feature_names = column_names[:-1]
class_names = [
    'Iris setosa',
    'Iris versicolor',
    'Iris virginica']  # 类别 原始数据标签已经是0、1、2
train_dataset = tf.data.experimental.make_csv_dataset(
    train_dataset_fp,  # csv路径地址
    batch_size=batch_size,
    column_names=column_names,  # 自动忽略第一行
    label_name=label_name,
    num_epochs=1)
test_dataset = tf.data.experimental.make_csv_dataset(
    test_fp,
    batch_size=32,
    column_names=column_names,
    label_name=label_name,
    num_epochs=1)
# 返回一个(features, label) 对构建的 tf.data.Dataset 其中features 是一个字典: {'feature_name': value}
# features, labels = next(iter(train_dataset)) # 查看一个batch
# plt.scatter(features['petal_length'],
#             features['sepal_length'],
#             c=labels,
#             cmap='viridis')
# plt.xlabel("Petal length")
# plt.ylabel("Sepal length")
# plt.show() # 绘制一个batch
# 构建指定输入格式
def pack_features_vector(features, labels):
    """将特征打包到一个数组中"""
    # A = features.values() # odict_values 以列(样本数)为主的数据格式 即特征数*样本数 4个(32,)
    # B = list(A) # list
    # C = tf.stack(B, axis=1) #(32,4) # 按列堆叠 切换为正常的样本数*特征数
    features = tf.stack(list(features.values()), axis=1)
    return features, labels
train_dataset = train_dataset.map(pack_features_vector)
test_dataset = test_dataset.map(pack_features_vector)
# train_dataset = train_dataset.take(int(len(train_dataset)*0.6))
# val_dataset = train_dataset.skip(int(len(train_dataset)*0.6))
# test_dataset = val_dataset.skip(int(len(val_dataset)*0.5))
# val_dataset = val_dataset.take(int(len(val_dataset)*0.5))
# features, labels = next(iter(train_dataset))
#%%
model = tf.keras.Sequential([
    tf.keras.layers.Dense(
        10, activation=tf.nn.relu, input_shape=(
            4,)),  # 每个样本特征向量是(4,)的格式
    tf.keras.layers.Dense(10, activation=tf.nn.relu),
    tf.keras.layers.Dense(3)])
loss = tf.keras.losses.SparseCategoricalCrossentropy(
    from_logits=True)  # model没使用softmax
acu = tf.keras.metrics.SparseCategoricalAccuracy()
# 设置指数学习率衰减 initial_learning_rate * decay_rate ^ (step / decay_steps)
exponential_decay = tf.keras.optimizers.schedules.ExponentialDecay(
    initial_learning_rate=0.1,
    decay_steps=train_nums // batch_size + 1,  # 120 // 16 + 1 = 8
    decay_rate=0.98,  # 迭代decay_steps个step后，学习率降为原来的0.98倍
    staircase=True)  # 如果是False，学习率会平滑地衰减，而非每迭代1000轮才衰减一次
# 如果为True，则会每迭代1000次才衰减一次，这种称为阶梯函数
optimizer = tf.keras.optimizers.Adam(learning_rate=exponential_decay)
# 早期停止技术的回调
# callback = tf.keras.callbacks.EarlyStopping\
#     (monitor='',min_delta=0.0001, patience=10, restore_best_weights=True)
epochs = 500
Loss_Acu = [[], []]  # epoch * step
Val_Loss_Acu = [[], []]  # epoch
for epoch in range(epochs):
    for step, (feature, y_true) in enumerate(train_dataset):
        step_time_start = time()
        with tf.GradientTape() as tape:
            y_pred = model(feature)
            loss_value = loss(y_true=y_true, y_pred=y_pred)
            acu_value = acu(y_true=y_true, y_pred=y_pred)
        grads = tape.gradient(loss_value, model.trainable_variables)
        optimizer.apply_gradients(zip(grads, model.trainable_variables))
        step_time_end = time()
        # if epoch % 10 == 0:
        print(
            "epoch %d step %d loss %.5f acu %.5f time %.5fs" %
            (epoch,
             step,
             loss_value.numpy(),
             acu_value.numpy(),
             step_time_end -
             step_time_start))
        Loss_Acu[0].append(loss_value.numpy())
        Loss_Acu[1].append(acu_value.numpy())
    for val_feature, val_y_true in (test_dataset):
        val_time_start = time()
        val_y_pred = model(val_feature)
        val_loss = tf.keras.losses.sparse_categorical_crossentropy(
            y_true=val_y_true, y_pred=val_y_pred, from_logits=True)
        val_acu = tf.keras.metrics.sparse_categorical_accuracy(
            y_true=val_y_true, y_pred=val_y_pred)
        val_loss = tf.reduce_mean(val_loss)
        val_acu = tf.reduce_mean(val_acu)
        val_time_end = time()
        print("epoch{:d} val_loss {:.5f} val_acu {:.5f} val_time {:.5f}s".format(
            epoch, val_loss.numpy(), val_acu.numpy(), val_time_end - val_time_start))
        Val_Loss_Acu[0].append(val_loss.numpy())
        Val_Loss_Acu[1].append(val_acu.numpy())
# %%
# 找到索引199,399,..,的列表元素


def epoch_loss_acu(list, index):
    assert len(list) == 2
    return [list[index][x] for x in np.where(
        np.arange(len(list[0])) % (len(list[index]) // epochs) == 0)[0]]


train_loss_epoch = epoch_loss_acu(Loss_Acu, index=0)
train_acu_epoch = epoch_loss_acu(Loss_Acu, index=1)
val_loss_epoch = epoch_loss_acu(Val_Loss_Acu, index=0)
val_acu_epoch = epoch_loss_acu(Val_Loss_Acu, index=1)
fig, ax = plt.subplots(2, 1, sharex=True)
ax = ax.flatten()
ax[0].plot(train_loss_epoch)
ax[0].plot(val_loss_epoch)
ax[0].legend(labels=['train_loss', 'val_loss'])
ax[1].plot(train_acu_epoch)
ax[1].plot(val_acu_epoch)
ax[1].legend(labels=['train_acu', 'val_acu'])
ax[1].set_xlabel("epoch")
plt.show()
