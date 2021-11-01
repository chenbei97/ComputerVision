#%%
# -*- coding UTF-8 -*-
'''
@Project : MyPythonProjects
@File : 9.典型Net结构.py
@Author : chenbei
@Date : 2021/8/24 8:48
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
import hiddenlayer
font_set = FontProperties(fname=r"C:\Windows\Fonts\simsun.ttc", size=10.5)
import numpy as np
import pandas as pd
import  hiddenlayer
import os
import tensorflow as tf
from tensorflow.keras import layers,optimizers, Sequential,initializers,Model,losses
from tensorflow.keras.layers import Input,Dense,Conv2D,BatchNormalization,Dropout,Activation,MaxPooling2D,Flatten,GlobalAveragePooling2D
minst = tf.keras.datasets.mnist
fashion_minst = tf.keras.datasets.fashion_mnist
# (x_train,y_train),(x_test,y_test) = minst.load_data()
# (x_train,y_train),(x_test,y_test) = fashion_minst.load_data()
(x_train,y_train),(x_test,y_test) = tf.keras.datasets.cifar10.load_data()
x_train ,x_test = x_train/255. , x_test/255.
class LeNet5(Model):
    '''1998 5层'''
    def __init__(self):
        super(LeNet5, self).__init__()
        self.c1 = Conv2D(filters=6,kernel_size=(5,5),activation='sigmoid',name="Conv2d_1")
        self.p1 = MaxPooling2D(pool_size=(2,2),strides=2,name="MaxPool2d_1")
        self.c2 = Conv2D(filters=16,kernel_size=(5,5),activation='sigmoid',name="Conv2d_2")
        self.p2 = MaxPooling2D(pool_size=(2,2),strides=2,name="MaxPool2d_2")
        self.flatten = Flatten(name="Flatten")
        self.f1 = Dense(120,activation='sigmoid',name="Dense_1")
        self.f2 = Dense(84, activation='sigmoid',name="Dense_2")
        self.f3 = Dense(10, activation='softmax',name="Output")
    def call(self,x):
        x = self.c1(x)
        x = self.p1(x)
        x = self.c2(x)
        x = self.p2(x)
        x = self.flatten(x)
        x = self.f1(x)
        x = self.f2(x)
        x = self.f3(x)
        return x
# model = LeNet5()
# model.compile(optimizer='adam',
#               loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
#               metrics=['accuracy'])
# y = model(x_test)
# model.build(input_shape=(10000,32,32,1))
# model()
#%%
class AlexNet8(Model):
    '''2012 8层'''
    def __init__(self):
        super(AlexNet8, self).__init__()
        self.c1 = Conv2D(filters=96,kernel_size=(11,11),strides=4)
        self.b1 = BatchNormalization()
        self.a1 = Activation("relu")
        self.p1 = MaxPooling2D(pool_size=(3,3),strides=2)

        self.c2 = Conv2D(filters=256, kernel_size=(5, 5),padding='same',strides=1)
        self.b2 = BatchNormalization()
        self.a2 = Activation("relu")
        self.p2 = MaxPooling2D(pool_size=(3, 3), strides=2)

        self.c3 = Conv2D(filters=384, kernel_size=(3, 3),padding='same',activation='relu')

        self.c4 = Conv2D(filters=384, kernel_size=(3, 3), padding='same', activation='relu')

        self.c5 = Conv2D(filters=256, kernel_size=(3, 3), padding='same', activation='relu')
        self.p5 = MaxPooling2D(pool_size=(3, 3), strides=2)

        self.flatten = Flatten()

        self.f6 = Dense(4096,activation='relu')
        self.d6 = Dropout(0.5)
        self.f7 = Dense(4096,activation='relu')
        self.d7 = Dropout(0.5)
        self.f8 = Dense(1000, activation='softmax')
    def call(self,x):
        x = self.p1(self.a1(self.b1(self.c1(x))))
        x = self.p2(self.a2(self.b2(self.c2(x))))
        x = self.c3(x)
        x = self.c4(x)
        x = self.p5(self.c5(x))
        x = self.flatten(x)
        # model = AlexNet8()
        # A = model(np.random.rand(2,227,227,3))
        # print(x.shape) # (2, 9216) 9216 = 6*6*256
        x = self.d6(self.f6(x))
        x = self.d7(self.f7(x))
        x = self.f8(x)
        return x

#%%
class VGGNet16(Model):
    '''2014 16层/19层'''
    def __init__(self):
        super(VGGNet16, self).__init__()
        # 13个Convd层+3个Dense层
        # CBA-CBAPD, CBA-CBAPD
        self.c1 = Conv2D(filters=64, kernel_size=(3, 3),padding='same')
        self.b1 = BatchNormalization()
        self.a1 = Activation("relu")
        self.c2 = Conv2D(filters=64, kernel_size=(3, 3),padding='same')
        self.b2 = BatchNormalization()
        self.a2 = Activation("relu")
        self.p2 = MaxPooling2D(pool_size=(2, 2), strides=2,padding='same')
        self.d2 = Dropout(0.2)
        # 此时输入形状(112,112,64)

        self.c3 = Conv2D(filters=128, kernel_size=(3, 3),padding='same')
        # 此时输入形状(112,112,128)
        self.b3 = BatchNormalization()
        self.a3 = Activation("relu")
        self.c4 = Conv2D(filters=128, kernel_size=(3, 3),padding='same')
        self.b4 = BatchNormalization()
        self.a4 = Activation("relu")
        self.p4 = MaxPooling2D(pool_size=(2, 2), strides=2,padding='same')
        self.d4 = Dropout(0.2)
        # 此时输入形状(56,56,128)

        # CBA_CBA_CBAPD ,CBA_CBA_CBAPD ,CBA_CBA_CBAPD
        self.c5 = Conv2D(filters=256, kernel_size=(3, 3),padding='same')
        # 此时输入形状(56,56,256)
        self.b5 = BatchNormalization()
        self.a5 = Activation("relu")
        self.c6 = Conv2D(filters=256, kernel_size=(3, 3),padding='same')
        self.b6 = BatchNormalization()
        self.a6 = Activation("relu")
        self.c7 = Conv2D(filters=256, kernel_size=(3, 3),padding='same')
        self.b7 = BatchNormalization()
        self.a7 = Activation("relu")
        self.p7 = MaxPooling2D(pool_size=(2, 2), strides=2,padding='same')
        self.d7 = Dropout(0.2)
        # 此时输入形状(28,28,256)

        self.c8 = Conv2D(filters=512, kernel_size=(3, 3),padding='same')
        # 此时输入形状(14,14,512)
        self.b8 = BatchNormalization()
        self.a8 = Activation("relu")
        self.c9 = Conv2D(filters=512, kernel_size=(3, 3),padding='same')
        self.b9 = BatchNormalization()
        self.a9 = Activation("relu")
        self.c10 = Conv2D(filters=512, kernel_size=(3, 3),padding='same')
        self.b10 = BatchNormalization()
        self.a10 = Activation("relu")
        self.p10 = MaxPooling2D(pool_size=(2, 2), strides=2,padding='same')
        self.d10 = Dropout(0.2)
        # 此时输入形状(7,7,512)

        self.c11 = Conv2D(filters=512, kernel_size=(3, 3),padding='same')
        # 此时输入形状(7,7,512)
        self.b11 = BatchNormalization()
        self.a11 = Activation("relu")
        self.c12 = Conv2D(filters=512, kernel_size=(3, 3),padding='same')
        self.b12 = BatchNormalization()
        self.a12 = Activation("relu")
        self.c13 = Conv2D(filters=512, kernel_size=(3, 3),padding='same')
        self.b13 = BatchNormalization()
        self.a13 = Activation("relu")
        self.p13 = MaxPooling2D(pool_size=(2, 2), strides=2,padding='same')
        self.d13 = Dropout(0.2)
        # 此时输入形状(3,3,512) ，4096

        # 全连接层 (1,3*3*512)，这里不是真正的VGG16，原本是4608->4096->1000
        self.flatten = Flatten()
        self.f14 = Dense(512,activation='relu')
        # 全连接层 (1,512)
        self.d14 = Dropout(0.2)
        self.f15 = Dense(512,activation='relu')
        # 全连接层 (1,512)
        self.d15 = Dropout(0.2)
        # 输出层 (1,10)
        self.f16 = Dense(10, activation='softmax')
    def call(self,x):
        pass
class ConvBNRelu(Model):
    '''Inception结构块'''
    def __init__(self,channels,kernel_size=3,strides=1,padding='same'):
        super(ConvBNRelu, self).__init__()
        self.model = Sequential([
            Conv2D(filters=channels,kernel_size=kernel_size,strides=strides,padding=padding),
            BatchNormalization(),
            Activation(activation='relu')])
    def call(self,x):
        x = self.model(x)
        return x
class InceptionNet(Model):
    '''2014
    四个分支：
    ①input->1×1卷积核->卷积连接器 ：CBA [16*1×1 strides=1 padding='same']
    ②input->1×1卷积核->3×3卷积核->卷积连接器 CBA [16*1×1 strides=1 padding='same'] --> CBA [16*3×3 strides=1 padding='same']
    ③input->1×1卷积核->5×5卷积核->卷积连接器 CBA [16*1×1 strides=1 padding='same'] --> CBA [16*5×5 strides=1 padding='same']
    ④input->3×3池化核->1×1卷积核->卷积连接器 P [Max 3×3 strides=1 padding='same'] --> CBA [16*1×1 strides=1 padding='same']
    然后卷积连接器按深度方向进行合并形成4个Inception结构块,每个结构块深度都是16,拼接后为64个
    '''
    def __init__(self,channels,strides=1):
        super(InceptionNet, self).__init__()
        self.channels = channels
        self.strides  = strides
        self.incept1 = ConvBNRelu(channels=channels,kernel_size=1,strides=strides)
        self.incept2_1 = ConvBNRelu(channels=channels,kernel_size=1,strides=strides)
        self.incept2_2 = ConvBNRelu(channels=channels,kernel_size=3,strides=strides)
        self.incept3_1 = ConvBNRelu(channels=channels,kernel_size=1,strides=strides)
        self.incept3_2 = ConvBNRelu(channels=channels,kernel_size=5,strides=strides)
        self.incept4_1 = MaxPooling2D(pool_size=3,strides=1,padding='same')
        self.incept4_2 = ConvBNRelu(channels=channels,kernel_size=1,strides=strides)
    def call(self,x):
        x1 =  self.incept1(x)
        x2 = self.incept2_2(self.incept2_1(x))
        x3 = self.incept3_2(self.incept3_1(x))
        x4 = self.incept4_2(self.incept4_1(x))
        x = tf.concat([x1,x2,x3,x4],axis=3)
        return x
class Inception10(Model):
    '''2014 10层'''
    def __init__(self,num_blocks,num_classes,init_channels=16,**kwargs):
        super(Inception10, self).__init__()
        self.in_channels = init_channels # 第一层使用16*3×3的卷积核
        self.out_channels = init_channels
        self.init_channels = init_channels
        self.num_blocks = num_blocks
        self.incept = ConvBNRelu(init_channels) # 第1个结构块
        self.blocks  =  Sequential() # 第2-num_blocks个结构块

        for block_id in range(num_blocks):
            # 每个结构块有2层InceptionNet,即8个incept 故Inception10有1+8*num_blocks个incept
            # 第一层block的输出深度out_channels=16,拼接后为64,第二层block的out_channels=32,拼接后为128,以此类推
            for layer_id in range(2):
                if layer_id == 0 :
                    # 每个block的第一层InceptionNet的所有incept的卷积核步长为2 输出深度为out_channels*(block_id+1)
                    block = InceptionNet(channels=self.out_channels,strides=2)
                else:
                    # 每个block的第二层InceptionNet的所有incept的卷积核步长为1 输出深度为out_channels*(block_id+1)
                    block = InceptionNet(channels=self.out_channels,strides=1)
                self.blocks.add(block)
            self.out_channels *=2

        self.pooling = GlobalAveragePooling2D() # 全局池化
        self.dense = Dense(units=num_classes,activation='softmax') # 全连接

    def call(self,x):
        x = self.incept(x) # 第1个结构快 输出深度channels=16
        x = self.blocks(x) # 第2-num_blocks个结构块 block_1输出深度channels=64,block_2_channels=128
        x = self.pooling(x) # 全局池化
        x = self.dense(x) # 全连接
        return x
class ResBlock(Model):
    def __init__(self,channels,strides,residual_path=False):
        super(ResBlock, self).__init__()
        self.channels = channels
        self.strides = strides
        self.residual_path = residual_path

        self.c1 = Conv2D(filters=channels,kernel_size=(3,3),strides=strides,padding='same',use_bias=False)
        self.b1 = BatchNormalization() # use_bias:该层是否使用偏置向量
        self.a1 = Activation(activation='relu')
        self.c2 = Conv2D(filters=channels, kernel_size=(3, 3), strides=1, padding='same', use_bias=False)
        self.b2 = BatchNormalization() # F(x)

        if residual_path : # 需要调整时使用1×1的卷积核
            # 调整输入x和主输出F(x)为尺寸相同
            # 深度一定相同均为channels ,尺寸通过strides调节
            self.down_c1 = Conv2D(filters=channels,kernel_size=(1,1),strides=strides,padding='same',use_bias=False)
            self.down_b1 = BatchNormalization()

        self.a2 = Activation(activation='relu')

    def call(self,x):
        residual = x # x
        x = self.a1(self.b1(self.c1(x)))
        x = self.b2(self.c2(x)) # F(x)
        if self.residual_path:  #F(x)和x的尺寸是否相同,需要调整则使用卷积核
            residual = self.down_b1(self.down_c1(residual)) # W(x)
        # 特征图元素值对应相加，而非深度方向的堆叠(与Inception块的区别)
        # H(x)=F(x)+x或者H(x)=F(x)+W(x)
        out = self.a2(x+residual)
        return out
class ResNet18(Model):
    '''
    输入：图片尺寸32*32*3
    第一层卷积核：channels=64 , kernel_size=3 , s=1 padding='same'经历CBA的操作 outchannels=64,shape=32*32
    第二层block_list: 实例化[2,2,2,2] 有4个Block,每个Block有2个ResBlock
    ① block_1 : 第1个Block不进行调整 即2个ResBlock都不调整 channels=64
    ② block_2 : 第2个Block的第1个ResBlock进行调整S=2,第2个ResBlock不调整S=1 channels=128
    ③ block_3 : 第1个ResBlock进行调整S=2 ,第2个ResBlock不调整S=1 channels=256
    ④ block_4 : 第1个ResBlock进行调整S=2 ,第2个ResBlock不调整S=1 channels=512
    全局池化
    全连接
    '''
    def __init__(self,block_list,init_channels=64):
        super(ResNet18, self).__init__()
        self.num_blocks = len(block_list)
        self.out_channels = init_channels
        self.block_list = block_list

        self.c1 = Conv2D(filters=self.out_channels,kernel_size=(3,3),strides=1,padding='same',use_bias=False,kernel_initializer='he_normal')
        self.b1 = BatchNormalization()
        self.a1 = Activation(activation='relu') # (64-3+2P)+1=64

        self.blocks = Sequential()
        for block_id in range(self.num_blocks): # 每个Block模块的输出深度都加倍
            for resblock_id in range(block_list[block_id]): # 每个Block模块的每个ResBlock
                if  block_id!=0 and resblock_id==0:
                    # 从第2个Block开始,对每个Block的1个ResBlock进行调整 第2个不调整
                    block = ResBlock(channels=self.out_channels,strides=2,residual_path=True)
                else:
                    block = ResBlock(channels=self.out_channels,strides=1, residual_path=False)
                self.blocks.add(block)
            self.out_channels *=2

        self.pooling = GlobalAveragePooling2D()
        self.dense = Dense(10)

    def call(self,x):
        x = self.a1(self.b1(self.c1(x)))
        x = self.blocks(x)
        x = self.pooling(self.dense(x))
        return x
# resNet18 = ResNet18(block_list=[2,2,2,2])
# model = LeNet5()
#%%
# model = Sequential([Flatten(),Dense(128,activation='relu'),Dense(10,activation='softmax')])
# model = LeNet5()
model = AlexNet8()
model.compile(optimizer=optimizers.Adam(0.001),
              loss = losses.SparseCategoricalCrossentropy(),
              metrics=['sparse_categorical_accuracy'])
home_path = r"C:\Users\chenb\.keras\models"
# LeNet5_path = "\LeNet5\cifar10.ckpt"
AlexNet8_path = "\AlexNet8\cifar10.ckpt"
# checkpoint_save_path = home_path  + LeNet5_path
checkpoint_save_path = home_path  + AlexNet8_path
if os.path.exists(checkpoint_save_path+'.index'):
    print('-----------load the model------------')
    model.load_weights(checkpoint_save_path)
#%%
cp_callback = tf.keras.callbacks.ModelCheckpoint(filepath=checkpoint_save_path,save_best_only=True,save_weights_only=True)
history = model.fit(x_train,y_train,batch_size=32,epochs=5,validation_freq=1,validation_data=(x_test,y_test),callbacks=[cp_callback])
np.set_printoptions(threshold=np.inf)
print(model.trainable_variables)
file = open(os.path.dirname(checkpoint_save_path)+'\cifar10_weights.txt','w')
for var in model.trainable_variables :
    file.write(str(var.name)+'\n')
    file.write(str(var.shape)+'\n')
    file.write(str(var.numpy())+'\n')
file.close()
train_acc = history.history['sparse_categorical_accuracy']
val_acc = history.history['val_sparse_categorical_accuracy']
train_loss = history.history['loss']
val_loss = history.history['val_loss']
fig ,axes = plt.subplots(nrows=2, ncols=1)
axes.flatten()
axes[0].plot(val_acc,label='val_acc')
axes[0].plot(train_acc,label='train_vcc')
axes[0].legend()
axes[1].plot(val_loss,label='val_loss')
axes[1].plot(train_loss,label='train_loss')
axes[1].legend()
plt.show()
# 使用plt.subplot(1,2,1),plt.plot(label),plt.legend(),plt.subplot(1,2,1),...也可以
