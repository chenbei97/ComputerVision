#%%
# -*- coding UTF-8 -*-
'''
@Project : MyProjects
@File : 0.Numpy的shape问题.py
@Author : chenbei
@Date : 2021/7/21 9:47
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
# input_shape : 第一层(黄色不计入),然后从第二层到内层计算每层有几个下一层,最后为元素的个数
# 特别说明的是: 同一层每个组拥有的下一层组数必须相同
# input_dim : 代表张量的阶数,看有几层括号 例子当中阶数为4
# 1阶绿色3层、2阶浅蓝色2层、3阶深蓝色5层、4阶元素个数3个
# 特别的对于向量而言,阶数的含义退化成了维度,例如指定input_dim=32实际上是一个32个元素/维度的向量,但是一个一阶张量(32,)
# 4个中括号+1个小括号 中括号层数=维度数
# 标量Scalar shape=()) D=0
# 向量Vector shape=(n,) D=1 元素长度n
# 矩阵Matrix shape=(n,n) D=2 n*n
# 张量Tensor shape=(h,w,c) D>2 统称张量 or (b,h,w,c)
a = np.array([  # 3个绿色层 shape={tuple:4} (3,2,5,3)
    [   # 绿色层1 下方有2个浅蓝色层,每个浅蓝色层有5个深蓝层,并带有3个元素
        [
            [1,3,4],[2,4,5],[5,6,7],[3,5,3],[5,3,2] # 浅蓝色层1的深蓝色有5层 元素3个
        ],
        [
            [1,3,4],[3,4,5],[1,3,4],[4,5,6],[3,5,3] # 浅蓝色层2的深蓝色层必须也是5层且元素3个 否则需要dtype=object
        ]
    ],
    [
        [
            [1, 3, 4], [2, 4, 5], [5, 6, 7], [3, 5, 3], [5, 3, 2]
        ],
        [
            [1, 3, 4], [3, 4, 5], [1, 3, 4], [4, 5, 6], [3, 5, 3]
        ]
    ],
    [
        [
            [1, 3, 4], [2, 4, 5], [5, 6, 7], [3, 5, 3], [5, 3, 2]
        ],
        [
            [1, 3, 4], [3, 4, 5], [1, 3, 4], [4, 5, 6], [3, 5, 3]
        ]
    ]
])
#%% 【索引】
x = tf.random.normal([4,32,32,3]) # 4个中括号
x[0] # 访问第一张图片 shape=(32, 32, 3)
# 取第 1 张图片的第 2 行
x[0][1] # shape=(32, 3) 有32个长度为3的向量
x[0][1][-1] # shape=(3,) 长度为3的向量
# 取第 2 张图片，第 10 行，第 3 列
x[1,9,2]
#%% 【切片】
# 𝑠𝑡𝑎𝑟𝑡: 𝑒𝑛𝑑: 𝑠𝑡𝑒𝑝切片
x[1:3] # 读取第 2,3 张图片
x[:,0:28:2,0:28:2,:] # 示取所有图片，隔行采样，隔列采样，所有通道信息 高宽缩放50%
x[0,::] # 读取第 1 张图片的所有行
#%% 【维度相加】
z = tf.random.normal([4,2]) # 矩阵shape=(4,2) 4个样本
b = tf.ones([2]) # 向量[0,0] shape=(2,) 自动生成4个相同偏置 样本共享
out = z + b # 可以相加 b复制次数等于样本数 b按行叠加
print(z.numpy(),out.numpy())
print(z.shape,out.shape)
# 创建一层 Wx+b，输出节点为 3
fc = tf.keras.layers.Dense(3)
# 通过 build 函数创建 W,b 张量，输入节点为 4
fc.build(input_shape=(2,4)) # [last_dim, self.units]  2个样本长度为4
# 类的偏置成员 bias 初始化为全 0，这也是偏置𝒃的默认初始化方案
# fc.bias # 偏置向量 b 的长度应为 3
fc.kernel # shape=(4, 3)
# x@w+b 网络层称为线性层
x = tf.random.normal([2,4]) # 2个样本
w = tf.ones([4,3]) # 定义 W 张量
b = tf.zeros([3]) # 定义 b 张量
o = x@w+b # X@W+b 运算
#%% 【reshape】
# 基本的维度变换包含了改变视图 reshape，插入新维度 expand_dims，删除维度
# squeeze，交换维度 transpose，复制数据 tile 等
x = tf.range(96) # shape=(96,) D=1
x=tf.reshape(x,[2,4,4,3]) # shape=(2, 4, 4, 3) D=4
y = tf.reshape(x,[2,-1]) # 参数-1 表示当前轴上长度需要根据视图总元素不变的法则自动推导
y.ndim,y.shape # (2, TensorShape([2, 48]))
#%% 【expand_dims、squeeze】
x = tf.random.uniform([28,28],maxval=10,dtype=tf.int32)
print(tf.expand_dims(x,axis=2).shape) # (28, 28, 1)
print(tf.expand_dims(x,axis=1).shape) # (28, 1, 28)
print(tf.expand_dims(x,axis=0).shape) # (1, 28, 28)
y = tf.random.uniform([1,28,28,1],maxval=10,dtype=tf.int32)
print(tf.squeeze(y).shape)# (28, 28) 不指定维度参数axis默认删除所有长度为 1 的维度
#%% 【transpose】
# 改变视图、增删维度都不会影响张量的存储
# 但交换维度可以改变张量的存储顺序，同时改变张量的视图
# 完成维度交换后，张量的存储顺序已经改变
# 后续的所有操作必须基于新的存续顺序进行
# 部分库的图片格式是通道先行 [𝑏, ℎ, w, 𝑐] ----> [𝑏, 𝑐, ℎ, w]
x = tf.random.normal([2,32,32,3])
# 新维度的排序为图片数量、通道数、行、列，对应的索引号为[0,3,1,2]
print(tf.transpose(x,perm=[0,3,1,2]).shape)
#%% 【tile复制数据】
# 通过增加维度操作插入新维度后，可能希望在新的维度上面复制若干份数据
# 考虑𝑌 = 𝑋@𝑊 + 𝒃的例子，偏置𝒃插入新维度后，需要在新维度上复制 batch size 份数据
input = tf.random.normal([2,4])
w = tf.ones([4,3]) # 定义 W 张量
# 输入2个样本 故偏置b也应当有2个 输出节点3 故b长度3
b = tf.constant([1.,2.]) # D=1 shape=(2,)
print(b.shape)
b = tf.expand_dims(b,axis=1) # D=2 shape=(2, 1)
print(b.shape)
b = tf.tile(b,multiples=[1,3]) # D=3 shape=(2, 3)
print(b.shape)
print(b.numpy()) # [[1 1 1],[2 2 2]]
output = input@w+b
print(output.shape) # shape=(2, 3)
output = tf.tile(output,multiples=[2,1])
print(output.shape) # shape=(4, 3) 注意是全部成倍复制
#%% 【Broadcasting】
# tf.tile 会创建一个新的张量来保存复制后的张量 计算代价高
# Broadcasting 操作 叫广播机制 轻量级张量复制的手段
# Broadcasting 机制都能通过优化手段避免实际复制数据而完成逻辑运算
# Broadcasting 的效果和 tf.tile 一样，都能在此维度上逻辑复制数据若干份 但是不是真的复制数据
input = tf.random.normal([2,4])
w = tf.ones([4,3])
b = tf.constant([1.,2.])
b = tf.expand_dims(b,axis=1) # 拓展维度,维度保持一致时省略了数据复制操作
# output = input@w+b # 也可以直接相加 利用广播效应
# 等价于 output = input@w + tf.broadcast_to(b,[2,3])
output = input@w + tf.broadcast_to(b,shape=[2,3])
print(output.shape) # shape=(2, 3)
# 下方案例展示了如何从[w,1]--->拓展到[b,h,w,c]
# 首先默认右对齐进行扩展
A = tf.constant([1,2]) # (2,)
A = tf.expand_dims(A,axis=1) # (2,1)
A = tf.tile(A,multiples=[2,1]) # (4,1)
print(A.numpy()) # [ [1] [2] [1] [2] ]
B = tf.broadcast_to(A, [2,4,4,3]) # c维度扩展3份 然后在b、w继续复制
print(B[0]) # 4个4×3的矩阵 [ [ [1] [2] [1] [2] ] , [ [1] [2] [1] [2] ] , [ [1] [2] [1] [2] ]]
#%% 【matual】矩阵相乘 维度D>2时 会只计算最后2个维度
a = tf.random.normal([4,3,23,32])
b = tf.random.normal([4,3,32,2])
print((a@b).shape) # (4, 3, 23, 2)
# 矩阵相乘函数支持自动 Broadcasting 机制
a = tf.random.normal([4,28,32])
b = tf.random.normal([32,16]) # 会自动广播到[4,32,16]
print((a@b).shape) # (4, 28, 16)
