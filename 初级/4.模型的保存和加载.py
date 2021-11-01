#%%
# -*- coding UTF-8 -*-
'''
@Project : MyProjects
@File : 4.模型的保存和加载.py
@Author : chenbei
@Date : 2021/7/21 15:10
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
import os
import tensorflow as tf
from tensorflow.keras import layers
from tensorflow  import keras
#%% # 一、导入数据
(train_images, train_labels), (test_images, test_labels) = tf.keras.datasets.mnist.load_data()
train_labels = train_labels[:1000]
test_labels = test_labels[:1000]
# numpy.arange(n).reshape(a, b)    依次生成n个自然数，并且以a行b列的数组形式显示
# -1表示自动计算行或者列数 reshape(1,-1)转化成1行 reshape(-1,1)转换成1列
# 数组/矩阵 (a,b)-->(-1,d)  当d指定时,自动计算行数 m = a*b/d = 1000*28*28/28*28 = 1000
# reshape 将(10000,28,28)--->(1000,784)
train_images = train_images[:1000].reshape(-1, 28 * 28) / 255.0
test_images = test_images[:1000].reshape(-1, 28 * 28 ) / 255.0
#%% 二、创建模型
def create_model():
  model = tf.keras.models.Sequential([
    keras.layers.Dense(512, activation='relu', input_shape=(784,)),
    keras.layers.Dropout(0.2), # 抑制过拟合的层
    keras.layers.Dense(10)
  ])
  model.compile(optimizer='adam', # 稀疏分类交叉熵
                loss=tf.losses.SparseCategoricalCrossentropy(from_logits=True),
                metrics=['accuracy'])
  return model
model = create_model()
model.summary() # 785 * 512 + 513 * 0 + 513 * 10
#%% 三、训练期间保存模型、以 checkpoints 形式保存
# tf.keras.callbacks.ModelCheckpoint 允许在训练的过程中和结束时回调保存的模型
checkpoint_path = os.path.realpath('_tensorflow\初级\保存模型\cp.ckpt')
# 创建一个保存模型权重的回调
cp_callback = tf.keras.callbacks.ModelCheckpoint(filepath=checkpoint_path,
                                                 save_weights_only=True,
                                                 verbose=1)
model.fit(train_images,
          train_labels,
          epochs=10,
          validation_data=(test_images,test_labels),
          callbacks=[cp_callback])  # 通过回调训练
loss,acc = model.evaluate(test_images,  test_labels, verbose=2)
print("模型对测试集的训练准确率: {:5.2f}%".format(100*acc)) # 模型对测试集的训练准确率: 87.40%
#%% 四、重建一个新的未经训练的模型，与上述模型共享权重 , 并在测试集上进行评估
new_model = create_model()
new_model.load_weights(checkpoint_path)
newloss,newacc = new_model.evaluate(test_images,  test_labels, verbose=2)
print("新模型对测试集的训练准确率: {:5.2f}%".format(100*newacc))# 新模型对测试集的训练准确率: 87.40%
#%% 五、其它选项、手动保存权重或者整个模型
#　也可以手动保存模型权重 TensorFlow checkpoints 格式 .ckpt 扩展名
model.save_weights('./checkpoints/my_checkpoint')
model = create_model()
model.load_weights('./checkpoints/my_checkpoint') # 加载权重

# 手动保存整个模型
model.save('saved_model')
model.save('my_model.h5') # 保存为HDF5文件也可
new__model = tf.keras.models.load_model('saved_model') # 加载模型
new___model = tf.keras.models.load_model('my_model.h5')