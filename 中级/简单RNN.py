#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 简单RNN.py
@Author : chenbei
@Date : 2021/8/25 15:05
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
from matplotlib.font_manager import FontProperties
import numpy as np
import pandas as pd
import tensorflow as tf
from tensorflow.keras import layers, Sequential
from tensorflow.keras.layers import Dense,SimpleRNN
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

input_words = "abcde"
sparse_label = {'a':0,'b':1,'c':2,'d':3,'e':4}
onehot_label = {0:[1.,0.,0.,0.,0.],1:[0.,1.,0.,0.,0.],2:[0.,0.,1.,0.,0.],3:[0.,0.,0.,1.,0.],4:[0.,0.,0.,0.,1.]}
x_train = [
    onehot_label[sparse_label['a']],onehot_label[sparse_label['b']],onehot_label[sparse_label['c']],
    onehot_label[sparse_label['d']],onehot_label[sparse_label['e']]]
y_train = [sparse_label['b'],sparse_label['c'], sparse_label['d'], sparse_label['e'], sparse_label['a'] ]
np.random.seed(7)
np.random.shuffle(x_train)
np.random.seed(7)
np.random.shuffle(y_train)
tf.random.set_seed(7)
# 整个数据集送入，(送入样本数，输入一个字母出结果循环核时间展开步数=1,独热码有5个输入特征:每个时间步输入特征个数5)
x_train = np.reshape(x_train,(len(y_train),1,5))
y_train = np.array(y_train)
model = Sequential([SimpleRNN(3),Dense(5,activation='softmax')])
model.compile(optimizer=tf.keras.optimizers.Adam(0.01),
              loss = tf.keras.losses.SparseCategoricalCrossentropy(from_logits=False),
              metrics=['sparse_categorical_accuracy'])
home  =  r'C:\Users\chenb\.keras\models'
checkpoint_save_path = home + r'/SimpleRNN/rnn_simple.ckpt'
if os.path.exists(checkpoint_save_path):
    print("----------load the model------------")
    model.load_weight(checkpoint_save_path)
cp_callback = tf.keras.callbacks.ModelCheckpoint(filepath=checkpoint_save_path,save_best_only=True,save_weights_only=True,monitor='loss')
#%%
history = model.fit(x_train,y_train,batch_size=32,epochs=100,callbacks=[cp_callback])
model.summary()
#%%
np.set_printoptions(threshold=np.inf)
print(model.trainable_variables)
file = open(os.path.dirname(checkpoint_save_path)+'\simple_rnn_weights.txt','w')
for var in model.trainable_variables :
    file.write(str(var.name)+'\n')
    file.write(str(var.shape)+'\n')
    file.write(str(var.numpy())+'\n')
file.close()
train_acc = history.history['sparse_categorical_accuracy']
# val_acc = history.history['val_sparse_categorical_accuracy']
train_loss = history.history['loss']
# val_loss = history.history['val_loss']
fig ,axes = plt.subplots(nrows=2, ncols=1)
axes.flatten()
# axes[0].plot(val_acc,label='val_acc')
axes[0].plot(train_acc,label='train_vcc')
axes[0].legend()
# axes[1].plot(val_loss,label='val_loss')
axes[1].plot(train_loss,label='train_loss')
axes[1].legend()
plt.show()
#%%
for i in range(5) :
    alpha = input("请输入预测字母：")
    alpha1 = [onehot_label[sparse_label[alpha]]]
    alpha1 = np.reshape(alpha1,(1,1,5))
    result = model.predict([alpha1])
    pred = tf.argmax(result,axis=1)
    pred = int(pred)
    tf.print(alpha + "->" + input_words[pred])
