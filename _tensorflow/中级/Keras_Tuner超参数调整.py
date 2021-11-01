#%%
# -*- coding UTF-8 -*-
'''
@Project : MyProjects
@File : Keras_Tuner超参数调整.py
@Author : chenbei
@Date : 2021/7/22 10:08
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
import os
from tensorflow.keras import layers
from tensorflow  import keras
import keras_tuner as kt
(img_train, label_train), (img_test, label_test) = keras.datasets.fashion_mnist.load_data()
img_train = img_train.astype('float32') / 255.0
img_test = img_test.astype('float32') / 255.0
#%% 一、构建超调模型
# 当您构建用于超调的模型时，除了模型架构之外，您还定义了超参数搜索空间。 您为超调设置的模型称为超模型
# 您可以通过两种方法定义超模型:
# 1) 通过使用模型构建器功能
# 2) 通过继承 Keras Tuner API 的 HyperModel 类
# 可以将两个预定义的 HyperModel 类 - HyperXception 和 HyperResNet 用于计算机视觉应用程序
def model_builder(hp):
    '''
    使用模型构建器函数来定义图像分类模型
    :param hp: 调谐器
    :return: 可调模型
    '''
    model = keras.Sequential()
    model.add(keras.layers.Flatten(input_shape=(28, 28))) # 展平层 将二维输入转为一维
    # units正整数，输出空间的维数
    hp_units = hp.Int('units', min_value=32, max_value=512, step=32)
    model.add(keras.layers.Dense(units=hp_units, activation='relu'))
    model.add(keras.layers.Dense(10))
    # 调整优化器的学习率
    # 从 0.01、0.001 或 0.0001 中选择一个最佳值
    hp_learning_rate = hp.Choice('learning_rate', values=[1e-2, 1e-3, 1e-4])

    model.compile(optimizer=keras.optimizers.Adam(learning_rate=hp_learning_rate),
                loss=keras.losses.SparseCategoricalCrossentropy(from_logits=True),
                metrics=['accuracy'])

    return model
#%% 二、实例化调谐器并执行超调
# Keras Tuner 有四种可用的调谐器 Tuner - RandomSearch、Hyperband、BayesianOptimization 和 Sklearn
# 本案例中使用 Hyperband 调谐器
# 实例化 Hyperband 调谐器必须指定超模型、要优化的目标和要训练的最大时期数 (max_epochs)
# 该算法在几个 epoch 内训练了大量模型，并且只将表现最好的一半模型推进到下一轮
# Hyperband 通过计算 1 + logfactor(max_epochs) 并将其四舍五入到最接近的整数来确定要在括号中训练的模型数量
# directory目录包含在超参数搜索期间运行的每个试验（模型配置）的详细日志和检查点
# 如果重新运行超参数搜索，Keras Tuner 将使用这些日志中的现有状态来恢复搜索
# 要禁用此行为，请在实例化调谐器时传递额外的 overwrite=True 参数
tuner = kt.Hyperband(model_builder,
                     objective='val_accuracy',
                     max_epochs=10,
                     factor=3,
                     directory=os.path.realpath('_tensorflow\初级\超调保存模型'), # 超调模型保存的文件夹
                     project_name='我的超调模型')
# 引入早期停止防止过拟合 超过patience个周期没有满足最小改善条件即停止
stop_early = tf.keras.callbacks.EarlyStopping(monitor='val_loss', patience=5)
#%% 三、运行超参数搜索、与model.fit的方法参数一致
# 超参数搜索
tuner.search(img_train, label_train, epochs=50, validation_split=0.2, callbacks=[stop_early])
# OutPut:
# Best val_accuracy So Far: 0.893666684627533
# Total elapsed time: 00h 14m 15s

# 获取最优超参数
best_hps=tuner.get_best_hyperparameters(num_trials=1)[0]
print(f"超参数搜索完成\n第一层最佳输入维度为{best_hps.get('units')}\n优化器的最佳学习率为 {best_hps.get('learning_rate')}")
#%% 四、使用得到的最优超参数
model = tuner.hypermodel.build(best_hps)
history = model.fit(img_train, label_train, epochs=50, validation_split=0.2)
val_acc_per_epoch = history.history['val_accuracy']
best_epoch = val_acc_per_epoch.index(max(val_acc_per_epoch)) + 1 # 最佳迭代周期数
print('最佳迭代周期数: %d' % (best_epoch,))
#%%
# 重新实例化超模型并使用上面的最佳时期数对其进行训练
hypermodel = tuner.hypermodel.build(best_hps)
hypermodel.fit(img_train, label_train, epochs=best_epoch, validation_split=0.2)
#%%
# 在测试数据上评估超模型
eval_result = hypermodel.evaluate(img_test, label_test)
print(eval_result)







