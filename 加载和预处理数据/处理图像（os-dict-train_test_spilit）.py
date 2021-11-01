#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 处理图像（os-dict-train_test_spilit）.py
@Author : chenbei
@Date : 2021/8/25 16:32
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
from matplotlib.font_manager import FontProperties
import numpy as np
import pandas as pd
import tensorflow as tf
from tensorflow.keras import layers, Sequential
import os
plt.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
plt.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
plt.rcParams['savefig.dpi'] = 600  # 图片像素
plt.rcParams['figure.dpi'] = 600  # 分辨率
font_set = FontProperties(fname=r"C:\Windows\Fonts\simsun.ttc", size=10.5)
#%% 例如读取.kera下的花数据集
home = r"C:\Users\chenb\.keras\datasets\flower_photos"
home_sonName = os.listdir(home) # 文件夹的名字
home_sonPath = [os.path.join(home,element) for element in home_sonName]
home_sonPath = [element if os.path.isdir(element) else "" for  element in home_sonPath]
home_sonPath.remove("") # 只保留文件夹路径
home_son_sonPath = {} # 文件夹名字+文件夹路径
flower_path_dict = {} # 文件夹名字+图片路径列表
#　得到每个文件夹路径 用于得到每个文件夹下的所有文件
for element in home_sonPath :
    home_son_sonPath[os.path.basename(element)] = element
# 得到每个每个文件夹下的图片路径
for flower, flower_path in home_son_sonPath.items():
    flower_pathName = os.listdir(flower_path) # 存放了每个文件夹下所有文件的名字 列表
    flower_path = [os.path.join(flower_path,element) for element in flower_pathName] # 得到所有图片的地址
    print(f"{flower}文件夹下有{len(flower_path)}张图片")
    flower_path_dict[flower] = flower_path
# 合并图片路径 并进行标注
all_flower_paths = []
for flower_path in flower_path_dict.values() :
    for element in flower_path :
        all_flower_paths.append(element)
import random
random.shuffle(all_flower_paths) # 随机打乱路径
all_flower_labels = []
for element in all_flower_paths :
    all_flower_labels.append(os.path.basename(os.path.dirname(element)))
from sklearn.preprocessing import LabelEncoder
Label_Encoder = LabelEncoder()
all_flower_labels = Label_Encoder.fit_transform(all_flower_labels) # 转为整型标签编码
# 划分训练、测试和验证集
from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(all_flower_paths,all_flower_labels,train_size=0.6)
X_val,X_test,y_val,y_test = train_test_split(X_test,y_test,train_size=0.5)

#%%
repeat_num = 2
batch_size = 32
def preprocess(X,y,training=False,repeat_num=repeat_num,batch_size=batch_size):
    path_dataset = tf.data.Dataset.from_tensor_slices((X,y)) # 路径字符串张量
    def decode_path(path,y):
        img_io = tf.io.read_file(path)
        img_tensor = tf.image.decode_jpeg(img_io, channels=3)
        img = tf.image.resize(img_tensor, [192, 192])
        img = 2 * img / 255.0 - 1
        return img,y
    if training:
        img_dataset = path_dataset.map(decode_path).shuffle(len(path_dataset)).repeat(repeat_num).batch(batch_size).prefetch(1) # 把路径张量解码为图像张量
    else:
        img_dataset = path_dataset.map(decode_path).shuffle(len(path_dataset)).batch(batch_size).prefetch(1)
    # y = tf.data.Dataset.from_tensors(y) # 不要使用维度切片命令from_tensor_slices
    # dataset = tf.data.Dataset.zip((img_dataset,y))
    return img_dataset
train_set = preprocess(X_train,y_train)
val_set = preprocess(X_val,y_val)
test_set = preprocess(X_test,y_test)
epochs = 30
step = len(y_train) * repeat_num  // batch_size # 2202 * 2 // 32 = 137
lr_sch = tf.keras.optimizers.schedules.ExponentialDecay(initial_learning_rate=0.1,decay_steps=epochs*step,decay_rate=0.98)
opt = tf.keras.optimizers.Adam(lr_sch)
loss = tf.keras.losses.SparseCategoricalCrossentropy()
acu = tf.keras.metrics.SparseCategoricalAccuracy()
mobile_net = tf.keras.applications.MobileNetV2(input_shape=(192, 192, 3), include_top=False)
mobile_net.trainable=False
model = tf.keras.Sequential([
        mobile_net,
        tf.keras.layers.GlobalAveragePooling2D(),
        tf.keras.layers.Dense(len(set(y_train)), activation='softmax')])  # 输出层是5个标签
#%%
for epoch in range(epochs) :
    for  step,(x_train_batch , y_train_batch) in enumerate(train_set):
        with tf.GradientTape() as tape:
            output  = model(x_train_batch)
            loss_value = loss(y_true=y_train_batch,y_pred=output)
            acu_value = acu(y_true=y_train_batch,y_pred=output)
            print("epoch {:d} step {:d} acu {:.5f} loss {:.5f}".format(epoch+1,step+1,acu_value.numpy(),loss_value.numpy()))
    grads = tape.gradient(loss_value,model.trainable_variables)
    opt.apply_gradients(zip(grads, model.trainable_variables))
    for x_val_batch,y_val_batch in val_set:
        val_output = model(x_val_batch)
        val_loss = loss(y_true=y_val_batch,y_pred=val_output)
        val_acu = acu(y_true=y_val_batch,y_pred=val_output)
    print(f"epoch {epoch+1} val_loss {val_loss.numpy()} val_acu {acu.result().numpy()}")
    acu.reset_states()

#%%
save_path = r"C:\Users\chenb\.keras\models\MobileNetV2\mobile_net_MobileNetV2.h5"
model.save(save_path)
new_model = tf.keras.models.load_model(save_path)
for x_test_batch,y_test_batch in test_set:
    test_output = new_model.predict(x_test_batch)
    test_acu = acu(y_true=y_test_batch,y_pred=test_output)
    print(f"test_acu : {test_acu.numpy()}")
