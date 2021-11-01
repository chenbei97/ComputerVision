#%%
# -*- coding UTF-8 -*-
'''
@Project : MyProjects
@File : 3.fashion_mnist图像分类.py
@Author : chenbei
@Date : 2021/7/20 14:35
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl

plt.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
#plt.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
plt.rcParams['savefig.dpi'] = 600  # 图片像素
#plt.rcParams['figure.dpi'] = 600  # 分辨率
from matplotlib.font_manager import FontProperties

font_set = FontProperties(fname=r"C:\Windows\Fonts\simsun.ttc", size=10.5)
import numpy as np
import pandas as pd
from tensorflow import keras
import tensorflow as tf
fashion_mnist = keras.datasets.fashion_mnist
#%% 一、观察数据类型、维度和具体的图像，并归一化处理
# 训练集中有 60,000 个图像，每个图像由 28 x 28 的像素表示
(train_images, train_labels), (test_images, test_labels) = fashion_mnist.load_data()
class_names = ['T恤', '裤子', '套头衫', '连衣裙', '大衣',
               '凉鞋', '衬衫', '运动鞋', '背包', '短靴']
# 查看图像
# plt.imshow(train_images[0])
# plt.colorbar()# 添加颜色棒
# plt.show()
# 归一化处理
train_images = train_images / 255.0
test_images = test_images / 255.0
# 查看前9个图像检验是否正确
plt.figure(figsize=(10,10))
for i in range(25):
    plt.subplot(5,5,i+1) # 5行5列第i+1个图像
    plt.xticks([])
    plt.yticks([])
    plt.grid(False)
    plt.imshow(train_images[i], cmap=plt.cm.binary)
    plt.xlabel(class_names[train_labels[i]])
plt.show()
#%% 二、创建模型、添加层，编译模型并拟合数据和模型
# 创建一个“顺序”模型并添加一个 Dense 层作为第一层 第一个 Dense 层有 128 个节点
# 将图像格式从二维数组 28 x 28 像素转换成一维数组 28 x 28 = 784 像素
# 第二个(也是最后一个层)会返回一个长度为 10 的逻辑数组。每个节点都包含一个得分，用来表示当前图像属于 10 个类中的哪一类。
model = keras.Sequential([
    keras.layers.Flatten(input_shape=(28, 28)),
    keras.layers.Dense(128, activation='relu'),
    keras.layers.Dense(10)])
# 使用adam优化器,损失函数使用稀疏分类交叉熵SparseCategoricalCrossentropy或sparse_categorical_crossentropy
# 都需要传入非onehot编码的y_true, y_pred
# tf.keras.losses.sparse_categorical_crossentropy是直接传入,
# tf.keras.losses.SparseCategoricalCrossentropy是类实例化后再传入
# @@ categorical_crossentropy 要求target为onehot编码
# from_logits = False 表示输入进来的y_pred已符合某种分布, 系统只会帮你把概率归一化。比如把[ 0.2 , 0.6 ]变成[0.25, 0.75]
# from_logits = True 表示是原始数据，系统会帮你做softmax后再进行计算
model.compile(optimizer='adam',
              loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
              metrics=['accuracy', 'mse'])
model.fit(train_images, train_labels,batch_size=50 ,epochs=10) # 0.91 默认batch_size=32
# Batch Size定义：一次训练所选取的样本数 迭代次数 iteration * Batch Size = 总的训练样本数 N
# Epoch是完整遍历一次训练样本
test_loss,test_acc,test_mse = model.evaluate(test_images,  test_labels, verbose=1)
print('\nTest accuracy:', test_acc) # 0.884 < 0.91
#%% 三、对测试样本进行模型评估和预测，提及过拟合的概念
# 评估测试样本,得到损失和准确率
# verbose：日志显示 verbose = 0 为不在标准输出流输出日志信息 ; verbose = 1 为输出进度条记录 ; verbose = 2 没有进度条，只是输出一行记录
# 模型在测试数据集上的准确率略低于训练数据集。训练准确率和测试准确率之间的差距代表过拟合
# 过拟合是指机器学习模型在新的、以前未曾见过的输入上的表现不如在训练数据上的表现
# 关于过拟合，提升模型容量和降低过拟合(提高泛化能力)是一对矛盾，模型的主要任务是泛化而非拟合
# 从较少的层和参数开始，然后开始增加层的大小或添加新层，直到看到验证损失的收益递减
# @@ 如果在训练过程中逐渐降低学习率，许多模型的训练效果会更好  使用 optimizers.schedules 随时间降低学习率
# 逆时间衰减模型 initial_learning_rate / (1 + decay_rate * step / decay_steps)
# lr_schedule是一个类,还需要指定参数 iterations = epoch * iteration 总的迭代次数
# 简化模型含义其实就是反比例模型,lr = l0 / (1 + step / decay)
# 当 decay = decay_rate / decay_steps 取为 iterations 时, 且对应的step上限也是iterations时即学习率会降到 l0/2
# 可以对decay进行调整,从而可控制学习率下限,lr = l0 * decay / ( decay + step )
# 其他模型xponentialDecay(指数衰减), PiecewiseConstantDecay(分段常数衰减) , PolynomialDecay(多项式衰减)
# 以及callbacks来实现动态、自定义学习率衰减策略
BATCH_SIZE = 50 # 一次训练样本数
N_TRAIN = int(6e4) # 总的训练样本个数60000
Iteration = N_TRAIN / BATCH_SIZE # 单Epoch的迭代次数 Iteration = 1200
Epoch = 10 # 遍历次数
Iterations = Epoch * Iteration # 总的迭代次数 12000
lr_schedule = tf.keras.optimizers.schedules.InverseTimeDecay(
  initial_learning_rate = 0.001,#初始学习率
  decay_steps=Iterations,
  decay_rate=1 )# 衰减率
# 反比例曲线模型的下降率
step = np.linspace(0,Iterations,num=Epoch ) # (0,Iteration,2*Iteration,...,Epoch*Iteration=Iterations)
lr = lr_schedule(step) # 指定参数step
plt.figure(figsize = (8,6))
plt.plot(step/Iterations, lr)
plt.ylim([0,max(plt.ylim())])
plt.xlabel('Epoch')
_ = plt.ylabel('Learning Rate')
plt.show()
pre_logits = model.predict(test_images) # 此模型没有对最后一层归一化,所以不是比较容易理解的概率模型,正值最大的认为是预测标签
probability_model = tf.keras.Sequential([model, tf.keras.layers.Softmax()]) # 加一个 softmax 层，将 logits 转换成更容易理解的概率
pre_softmax = probability_model.predict(test_images)
pre_label = [np.argmax(i) for i in pre_softmax] # 找到测试集所有样本预测的标签 argmax找到数组元素最大值的下标
result = []
for index , item in enumerate(pre_label) :
    result.append(pre_label[index] - test_labels[index])
pre_false_index = [result.index(i)  for i in result if i !=0 ]
pre_acc = len(pre_false_index) / len(pre_label)
print('测试集预测正确的概率为 : ', 1 - pre_acc)
#%% 四、查看预测的图像和概率
def plot_image(i, pre_softmax, test_labels, test_imgs):
    '''
    :param i: 指代测试集的第i个样本的图像/概率得分/标签 i=0~9999
    :param pre_softmax: 测试集样本的预测概率
    :param test_labels: 测试集样本的实际标签
    :param test_imgs:测试样本的图像 10000*28×28
    :return: 绘制测试集第i个样本的图像并在括号内说明所预测的对象及其概率,正确为蓝色,错误为红色
    '''
    pre_probal, test_label, test_img = pre_softmax[i], test_labels[i], test_imgs[i]
    plt.grid(False)
    plt.xticks([])
    plt.yticks([])
    plt.imshow(test_img, cmap=plt.cm.binary)
    pre_label = np.argmax(pre_probal)
    if pre_label == test_label:
       color = 'blue'
    else:
       color = 'red'

    plt.xlabel("实际类别:{} 预测类别:{} 预测概率:{:2.0f}%".format(class_names[test_label],
                                class_names[pre_label],
                                100*np.max(pre_probal)),color=color)
def plot_pre_probal_label(i, pre_softmax, test_labels):
    '''
    :param i: 指代测试集的第i个样本的图像/概率得分/标签 i=0~9999
    :param pre_softmax: 测试集样本的预测概率
    :param test_labels: 测试集样本的实际标签
    :return: 第i个样本被预测为某个类别的得分条形图(10个类别)
    '''
    pre_softmax, test_label = pre_softmax[i], test_labels[i]
    plt.grid(False)
    plt.xticks(range(10))
    plt.yticks([])
    plt.ylabel('得分')
    plt.xlabel('类别')
    reats = plt.bar(range(10), pre_softmax, color="#777777",align='center',alpha=0.8) # 条形图
    plt.ylim([0, 1]) # 得分限制在0~1
    pre_label = np.argmax(pre_softmax)
    reats[pre_label].set_color('red')
    reats[test_label].set_color('blue') # 如果预测=实际则red会被blue覆盖,否则出现2个颜色条
    for reat in reats:  # 每一个柱子循环标注数值大小
        reat_height = reat.get_height()  # 获取柱子高度
        plt.text(reat.get_x() + reat.get_width() / 2, reat_height, str(round(reat_height,3)), size=8.5, ha='center', va='bottom')
# ①测试某一个样本
i = 12
plt.figure(figsize=(6,3))
plt.subplot(1,2,1)
plot_image(i, pre_softmax, test_labels, test_images)
plt.subplot(1,2,2)
plot_pre_probal_label(i, pre_softmax,  test_labels)
plt.show()
# ②测试多个样本 5行6列 30个样本
plt.figure(figsize=(20,8)) # 图片内存问题,高度要≤8,否则会崩溃
for i in range(15): # 2*i+1<31 i<15
  plt.subplot(5, 6, 2*i+1) # 1,3,5列
  plot_image(i, pre_softmax, test_labels, test_images) # 绘制的是样本1,3,5,...,59的第一个图
  plt.subplot(5, 6, 2*i+2) # 2,4,6列
  plot_pre_probal_label(i, pre_softmax, test_labels) # 绘制的是样本1,3,5,...,59的第二个图
plt.tight_layout()
plt.show()
#%% 五、预测单个或者一批样本
# 即使一个样本也要拓展维度 否则使用模型预测时会因为变量的数据格式不匹配出错
img = test_images[100]
img = (np.expand_dims(img,0)) # 拓展维度 28*28--->1*28*28
img_label = test_labels[100]
img_label = (np.expand_dims(img_label,0)) # 标签也要拓展维度
img_probal = probability_model.predict(img)
img_pre_label = np.argmax(img_probal)
if img_label == img_pre_label :
    print(f"预测正确,预测概率为{img_probal[0,img_pre_label]*100}%")
else:
    print(f'预测错误,预测概率为{img_probal[0,img_pre_label]*100}%')
plot_pre_probal_label(0,img_probal,img_label) # 使用拓展维度后的单个img及其标签去预测
_ = plt.xticks(range(10), class_names, rotation=45)
plt.show()