#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 目标检测.py
@Author : chenbei
@Date : 2021/8/30 13:10
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
from matplotlib.font_manager import FontProperties
import numpy as np
import pandas as pd
import tensorflow as tf
import os
from tensorflow.keras import layers, Sequential
import tensorflow_datasets as tfds
import tensorflow_hub as hub
plt.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
plt.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
plt.rcParams['savefig.dpi'] = 600  # 图片像素
plt.rcParams['figure.dpi'] = 600  # 分辨率
font_set = FontProperties(fname=r"C:\Windows\Fonts\simsun.ttc", size=10.5)
inputs = tf.keras.layers.Input(shape=(299,299,3))
net = hub.KerasLayer(
    "https://tfhub.dev/google/tf2-preview/inception_v3/feature_vector/2",
    output_shape=(2048),trainable=False)(inputs)
net = tf.keras.layers.Dense(512)(net)
net = tf.keras.layers.ReLU()(net)
cooridinates = tf.keras.layers.Dense(4,use_bias=False)(net)
regressor  = tf.keras.Model(inputs=inputs,outputs=cooridinates)
(train,test,validation),info = tfds.load("voc",split=["train","test","validation"],with_info=True)
def Filter(dataset):
    return dataset.filter(lambda row : tf.equal(tf.shape(row["objects"]["label"])[0],1))
# train,test,validation = Filter(train),Filter(test),Filter(validation)
def prepare(dataset):
    def _fn(row):
        row["image"] = tf.image.convert_image_dtype(row["image"],tf.float32)
        row["image"] = tf.image.resize(row["image"],(299,299))
        return row
    return dataset.map(_fn)
train,test,validation = prepare(train),prepare(test),prepare(validation)
#%%
with tf.device("/CPU:0"):
    for row in train.take(10):
        obj = row["objects"]
        image = tf.image.convert_image_dtype(row["image"],tf.float32)

        for idx in tf.range(tf.shape(obj["label"])[0]):
            image = tf.squeeze(
                              tf.image.draw_bounding_boxes(
                                              images=tf.expand_dims(image, axis=[0]),
                                              boxes=tf.reshape(obj["bbox"][idx],(1,1,4)),
                                              colors=tf.reshape( tf.constant((1.0,1.0,0,0)),(1,4))
                                                          )
                              ,axis=[0]
                              )
            print("label：",info.features["objects"]["label"].int2str(obj["label"][idx]))
        plt.imshow(image)
        plt.show()


