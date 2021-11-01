#%%
# -*- coding UTF-8 -*-
'''
@Project : MyPythonProjects
@File : TensorflowHub迁徙学习模型.py
@Author : chenbei
@Date : 2021/8/2 9:50
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
import tensorflow_datasets as tfds
import tensorflow_hub as hub
import os
'''
1、获取数据 : 关于花卉的分类问题(tfds数据集可用) labels=5(5种花) names='tf_flowers'
2、迁徙学习 : pip install tensorflow-hub（Inception v3模块） https:// tfhub.dev
Inception v3模块来自于2015年ILSVRC的的深度学习模型，42层，期望输入尺寸为299*299*3 输出特征向量为8*8*2048
该模块的特征提取器足够好 可以用于本案例中的花卉分类器的构建块
3、微调 : 
'''
# 第一次下载该模型时显示进度条的代码
os.environ["TFHUB_DOWNLOAD_PROGRESS"] = "1" # 创建环境变量
tfds.list_builders() # 可用数据集
# with_info=True将返回元组tf.data.Dataset，tfds.core.DatasetInfo
# 直接官网下载需要翻墙 所以可以通过手动下载数据集放入C:\Users\chenbei\tensorflow_datasets\tf_flowers即可
# 数据集地址: http://download.tensorflow.org/example_images/flower_photos.tgz
# data_path='C:\\Users\\chenbei\\tensorflow_datasets\\tf_flowers\\3.0.1'
dataset ,info = tfds.load("tf_flowers",with_info=True)
print(info)
dataset = dataset['train']
total = len(dataset) # 3670
train_size = total // 2
eval_size =  total - train_size - train_size // 2
test_size = total - train_size - eval_size
#%% 【1】 划训练、验证和测试数据集 图片为tf.uint8类型 即[0,255]
# skip(count) : 创建一个从该数据集中跳过计数元素的数据集
# take(count) : 从该数据集中创建一个最多包含 count 个元素的数据集
train , test , eval = (dataset.take(train_size),\
                      dataset.skip(train_size).take(test_size),\
                      dataset.skip(train_size +test_size).take(eval_size))
# 迁徙学习：依靠先前学习过的任务来学习新任务的过程 在CNN网络成功应用
# 1) 输入层 ： 输入精确分辨率的图像
# 2) 特征提取器 :　卷积、池化、归一化、flatten
# 3) 分类层 :  全连接
# 使用预训练好的模型 在新模型中作为特征提取器 其参数不可训练
# 可以训练的是分类层，加快了训练速度和缓解了过拟合
#%% 【2】 归一化图像到Inception v3要求的格式
def convert_image(images):
    # 调整输入图像RGB格式到[0,1]
    images["image"] = tf.image.convert_image_dtype(images["image"],tf.float32)
    # 调整图片大小
    images["image"] = tf.image.resize(images["image"],(299,299))
    return images
train = train.map(convert_image)
test = test.map(convert_image)
eval = eval.map(convert_image)
#%% 【3】建立模型 : hub.KerasLayer
# 创建一个hub_keras_layer_KerasLayer对象 与tf_keras_layers_layer对象完全一致 可以进行移植
hub_keras_layer_KerasLayer = hub.KerasLayer(
    # 可调用的模型
    handle="https://tfhub.dev/google/tf2_preview/inception_v3/feature_vector/2",
    output_shape=[2048],
    trainable=False # 不可训练的特征提取器
)
# 移植模型
model = tf.keras.Sequential([
    # 移植层
    hub_keras_layer_KerasLayer,
    # 分类层
    tf.keras.layers.Dense(512),
    tf.keras.layers.ReLU(),
    tf.keras.layers.Dense(5)
]
)
#%% 【4】 训练和评估
loss =  tf.losses.SparseCategoricalCrossentropy(from_logits=True)
step = tf.Variable(1,name="global_step",trainable=False)
optimizer = tf.optimizers.Adam(1e-3)





