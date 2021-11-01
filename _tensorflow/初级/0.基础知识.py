#%%
# -*- coding UTF-8 -*-
'''
@Project : MyProjects
@File : 0.基础知识.py
@Author : chenbei
@Date : 2021/7/22 8:50
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
from tensorflow .keras .datasets import fashion_mnist
'''
Epochs : 遍历/训练整个训练集的次数
Iteration : 单次遍历/one_epoch 进行的迭代次数
Iterations : 总迭代次数
Batch_Size : 单次迭代/one_Iteration 使用的样本数量
N_Train : 训练集样本数
存在公式 : N_Train = Iteration * Batch_Size 训练样本数 = 单次遍历需要的迭代数 * 单次迭代需要的样本数
Iterations = Epochs * Iteration 总迭代次数 = 总遍历次数 * 单次遍历需要的迭代数
1、layer层的分类
2、稀疏分类交叉熵
3、回调保存模型 
4、早期停止技术
5、evaluate和predict的区别
6、str和repr的区别
7、map函数的使用
8、建立图像通道
9、shuffle、repeat、batch的先后顺序问题
10、next(iter(iterable),default)
11、CNN卷积过程
12、常见OP运算
13、tf.data.Dataset对象
14、标准的ETL过程
'''
# 【1】layer层的分类
# 关于层大类: 网络层Core、卷积层Convolutiional、池化层Pooling、局部连接层/递归层Recurrent、嵌入层Embedding、高级激活层、噪声层、包装层
# <1>网络层Core:
# 1) Dense全连接层 : keras.layers.core.Dense()  本层实现的运算为output=activation(dot(input,kernel)+bias)
# 2) Activation激活层 :　keras.layers.core.Activation(activation) 激活层对一个层的输出施加激活函数
# 3) Dropout层 : keras.layers.core.Dropout(rate, noise_shape=None, seed=None) Dropout层用于防止过拟合
# 为输入数据施加Dropout,Dropout将在训练过程中每次更新参数时按一定概率（rate）随机断开输入神经元
# 4) Flatten层 : keras.layers.core.Flatten() Flatten层用来将输入“压平”，即把多维的输入一维化，常用在从卷积层到全连接层的过渡
# 5) Reshape层
# 6) Permute层
# 7) RepeatVector层
# 8) Lambda层
# 9) ActivityRegularizer层
# 10) Masking层
# <2>卷积层Convolutional
# 1)一维卷积层Conv1D : keras.layers.convolutional.Conv1D
# 2)二维卷积层Conv2D : keras.layers.convolutional.Conv2D
# 3)SeparableConv2D层 : keras.layers.convolutional.SeparableConv2D 深度方向上的可分离卷积
# 4)Conv2DTranspose层 : keras.layers.convolutional.Conv2DTranspos 转置的卷积操作（反卷积）
# 5)Conv3D层 : keras.layers.convolutional.Conv3D 三维卷积对三维的输入进行滑动窗卷积
# 6)Cropping1D层 : keras.layers.convolutional.Cropping1D 在时间轴（axis1）上对1D输入（即时间序列）进行裁剪
# 7)Cropping2D层 : keras.layers.convolutional.Cropping2D 对2D输入（图像）进行裁剪，将在空域维度，即宽和高的方向上裁剪

# 【2】稀疏分类交叉熵
# 损失函数使用稀疏分类交叉熵SparseCategoricalCrossentropy或sparse_categorical_crossentropy
loss=tf.losses.SparseCategoricalCrossentropy(from_logits=True)
# 都需要传入非onehot编码的y_true, y_pred
# tf.keras.losses.sparse_categorical_crossentropy是直接传入,
# tf.keras.losses.SparseCategoricalCrossentropy是类实例化后再传入
# @@ categorical_crossentropy 要求target为onehot编码
# from_logits = False 表示输入进来的y_pred已符合某种分布, 系统只会帮你把概率归一化。比如把[ 0.2 , 0.6 ]变成[0.25, 0.75]
# from_logits = True 表示是原始数据，系统会帮你做softmax后再进行计算

# 【3】回调保存模型
# tf.keras.callbacks.ModelCheckpoint 允许在训练的过程中和结束时回调保存的模型
checkpoint_path = "training_1/cp.ckpt"
tf.keras.callbacks.ModelCheckpoint(
    filepath=checkpoint_path, monitor='val_loss', verbose=0, save_best_only=False,
    save_weights_only=False, mode='auto', save_freq='epoch',
    options=None)

# 【4】早期停止
stop_early = tf.keras.callbacks.EarlyStopping(monitor='val_loss', patience=5)
# patience : 超过patience个周期没有满足最小改善条件即停止
# monitor : 监控的指标
# min_delta :　最小改善条件 当训练集上的loss不在减小(即减小的程度小于某个阈值)则停止训练

# 【5】 evaluate和predict的区别
# 1.输入输出不同
# model.evaluate  测试集数据和测试集标签,然后将预测结果与真实标签相比较,得到两者误差并输出
# model.predict   输入测试集数据(data)，输出预测结果
# 2.是否需要真实标签
# model.evaluate  需要，因为需要比较预测结果与真实标签的误差
# model.predict   不需要，只是单纯输出预测结果，全程不需要标签的参与

# 【6】str和repr的区别
# str()和repr()都可以将python中的对象转换为字符  两者之间的目标不同 :
# str()主要面向用户，其目的是可读性，返回形式为用户友好性和可读性都较强的字符串类型；
# repr()面向的是python解释器，或者说开发人员，其目的是准确性，其返回值表示python解释器内部的含义，常作为编程人员debug用途。
# repr()的返回值一般可以用eval()函数来还原对象，通常来说有如下等式：
# obj = eval(repr(obj))
#%%
# 【7】map函数的使用
# map(function, iterable, ...)function -- 函数 iterable -- 一个或多个序列
# 当需要对序列进行某些操作或者处理，将其转换为新的列表时，用map函数
# 以参数序列中的每一个元素调用 function 函数，返回包含每次 function 函数返回值的新列表或者迭代器
def square(x) :
     return x ** 2
print(map(square, [1,2,3,4,5])) # <map object at 0x000001ED52D97780>
# 需要使用list将其转换输出
print(list(map(square, [1,2,3,4,5])))

# 【8】建立图像通道
# 假设我们已经有了一个包含所有JPEG图像名称的列表和一个与之对应的标签列表。
# 通道建立步骤如下：
# 1) 从文件名和标签的切片创建数据集
# 2) 使用长度等于数据集大小的buffer size，打乱数据集。这确保了良好的改组。
# 3) 从图像文件名中解析像素值。使用多线程提升预处理的速度
# 4)（可选操作）图像数据扩增。使用多线程提升预处理的速度。
# 5) 批量处理图片
# 6) 预取一个批次以确保批处理可以随时使用
# dataset = tf.data.Dataset.from_tensor_slices((filenames, labels))
# dataset = dataset.shuffle(len(filenames))
# dataset = dataset.map(parse_function, num_parallel_calls=4)
# dataset = dataset.map(train_preprocess, num_parallel_calls=4)
# dataset = dataset.batch(batch_size)
# dataset = dataset.prefetch(1)
def parse_function(filename, label):
    # 读取图像文件内容
    # 使用JPEG图像格式解码
    # 转化为0到1的浮点值
    # 修改尺寸到（64， 64）
    image_string = tf.io.read_file(filename)
    image = tf.image.decode_jpeg(image_string, channels=3)
    image = tf.image.convert_image_dtype(image, tf.float32)
    resized_image = tf.image.resize(image, [64, 64])
    return resized_image, label
def train_preprocess(image, label):
    # 函数train_preprocess（optionally）可用于执行数据扩增
    # 以1 / 2的概率水平翻转图像,应用随机亮度和饱和度
    image = tf.image.random_flip_left_right(image)
    image = tf.image.random_brightness(image, max_delta=32)
    image = tf.image.random_saturation(image, lowe=0.5, upper=1.5)
    image = tf.clip_by_value(image, 0.0, 1.0)
    return image, label

# 【9】 shuffle、repeat、batch的先后顺序问题
# 参考网址 :　https://blog.csdn.net/lichaobxd/article/details/106476115
# 数据处理的需求 : 被充分打乱; 被分割为 batch;永远重复;尽快提供 batch 使用tf.data方法即可
# 在 .repeat 之后 .shuffle，会在 epoch 之间打乱数据 有些数据出现两次的时候，其他数据还没有出现过
# 在 .batch 之后 .shuffle，会打乱 batch 的顺序，但是不会在 batch 之间打乱数据
# 例如np.arange(20)有20个元素
dataset = tf.data.Dataset.range(10)
# ① shuffle->batch(3)->repeat(2)
# 如生成[ [0,1,2,3,4],[5,6,7,8,9],[15,16,17,18,19] ] 和 [ [10,11,12,13,14] ]
# 所有数据先打乱，然后打包成batch输出，整体数据重复2个epoch
# 先打包3个,再重复打包只能找剩下的,1.一个batch中的数据不会重复；2.每个epoch的最后一个batch的尺寸小于等于batch_size
list((dataset.shuffle(10).batch(3).repeat(2)).as_numpy_iterator())
# ② shuffle->repeat(3)->batch
# 如生成 [ [0,1,2,3,4],[10,11,12,13,14],[5,6,7,8,9] ] 和 [ [15,16,17,18,19],[15,16,17,18,19],[10,11,12,13,14] ]
# 重复打乱2次数据集进行拼接, 再这些数据随机进行打包
# batch的数据可能重复，每个epoch的最后一个batch的尺寸小于等于batch_size
eam = dataset.shuffle(10).repeat(2)
print(list(eam.as_numpy_iterator()))
print(list(eam.batch(3).as_numpy_iterator()))
# ③ batch(3)->repeat(2)->shuffle
# 如生成[ [0,1,2,3,4],[5,6,7,8,9],[10,11,12,13,14] ] ; [ [0,1,2,3,4],[5,6,7,8,9],[10,11,12,13,14] ]
# 以及 [ [15,16,17,18,19] ] ; [ [15,16,17,18,19] ]
# 先把所有数据按指定大小依次先打包成batch，然后把打包成batch的数据重复两遍，最后再将所有batch打乱进行输出
# 1.打乱的是batch；2.某些batch的尺寸小于等于batch_size
eam = dataset.batch(3).repeat(2)
print(list(eam.as_numpy_iterator()))
print()
print(list(eam.shuffle(len(eam)).as_numpy_iterator()))
# 【10】 next(iter(iterable),default)
# 对可迭代对象生成迭代器再使用next可以得到迭代输出

#%%
# 【11】 CNN卷积过程
# 输入图像尺寸 N1 * N1 * D1  输出尺寸 Y * Y * D2
# 输入通道的通道数D1决定了卷积核的通道数D1 无论输入通道数D1多少 1个卷积核只能得到1个输出矩阵 因为多通道矩阵还要继续对应相加
# 一个固定的卷积核只能完成某种逻辑的特征提取，例如图片的亮度， 如果需要提取多个维度的特征诸如图片的颜色、分布、饱和度等等可设置多个卷积核
# 卷积核尺寸 N2 * N2 * D1  卷积核个数 K   滑动步长 S   零值填充拓展维度 zero-padding = P (针对图片拓展)
# 设置了步长之后，很有可能某些位置滑不到，为了避免了边缘信息被一步步舍弃的问题，我们需要设置填充值来解决这个问题
# Y = (N1 - N2 + 2P ) / S + 1   D2 = K 输出层的个数 D2 取决于上一层卷积核的个数 K 而非通道数 D1，K个卷积核有K个输出矩阵Y代表不同的维度特征
# 多输入多卷积核的输出Y具有 D2 个特征图，类似的也可以使用通道的概念，即输出形状为 Y * Y * D2 (stack拼接操作)
# 卷积核1-->张量Y通道1,卷积核2-->张量Y通道2,...,卷积核K-->张量Y通道K (见书P226页的示意图)
# 每个卷积核的大小 N2，步长 S，填充设定 P 等都是统一设置，这样才能保证输出的每个通道大小一致，从而满足拼接的条件
# 常规设置 D1 = 3 S = 1 P = 1
# 多通道时单个卷积核的不同通道卷积矩阵是不相同的，但是多个卷积核之间可以是相同的，也就是卷积核权值共享，单和多通道都可以有多个卷积核
# 对于灰度图单通道, 卷积核由于共享机制 卷积核矩阵或者说权重矩阵个数就是 N2 * N2 对于多通道 N2 * N2 * D1
# 每个卷积核有 1 个偏置 那么总的参数个数为 N2 * N2 * D1 * K 个权重参数和 K 个偏置参数
# 若想要保持输入输出尺寸不变 即 Y = N1 ; 固定 S = 1 时取 P = 1 N2 = 3、 P = 2 时 取 N2 = 5 即 N2 = 2 * P + 1
# 在 S = 1 时设置参数 padding=SAME 即可使得输入输出形状相同
# 3x3的filter考虑到了像素与其距离为1以内的所有其他像素的关系，而5x5则是考虑像素与其距离为2以内的所有其他像素的关系
# 卷积核的作用 :
# 1) 1个卷积层具有 K 个卷积核 , 每个卷积核提取了输入图片的某个维度特征 并得到 K 个特征图
# 2) 特征图作为输入再被卷积的话,可以则可以由此探测到"更大"的形状概念 即多个卷积层 随着卷积神经网络层数的增加，特征提取的越来越具体化

# 卷积层结束后进入激励层 激励层的作用可以理解为把卷积层的结果做非线性映射 f(Σwixi+b)
# 常见的激活函数有 Sigmoid Tanh Relu LeakyRelu ELU Maxout
# 一般不要用sigmoid，首先试RELU，因为快，但要小心点，如果RELU失效，请用Leaky ReLU，某些情况下tanh倒是有不错的结果

# 池化层 : 降低了各个特征图的维度，但可以保持大分重要的信息。池化层夹在连续的卷积层中间 （见书P240页）
# 压缩数据和参数的量，减小过拟合，池化层并没有参数，它只不过是把上层给它的结果做了一个下采样（数据压缩）
# pooling在不同的通道depth上是分开执行的，也就是depth=5的话，pooling进行5次，产生5个池化后的矩阵
# pool_size(2,2)表示扫描区域大小2×2 , strides=(1,1)表示水平和竖直跳跃步长
# 池化操作是分开应用到各个通道特征图的，我们可以从64个输入图中得到64个输出图 即512*512*64 (pooling)----> 128*128*64
# 1) 最大值池化 : Max pooling 定义一个空间邻域如 2×2 的矩阵选择一个最大的元素作为被采样的点 那么4×4的图片可以压缩到 2×2
# 2) 平均值池化 :　Average pooling　取平均值

# 参数标准化层(BN层)：Batch Nomalization 一般堆叠层顺序为 Conv-BN-ReLU-Pooling 先卷积再标准化再激活
# BN 层的提出，使得网络的超参数的设定更加自由，比如更大的学习率，更随意的网络初始化等 同时网络的收敛速度更快，性能也更好
# 网络层输入𝑥分布相近，并且分布在较小范围内时(如 0 附近)，更有利于函数的优化
# 归一化公式(x-μ)/sqrt(σ^2+ε) ε是为了防止除0错误
# scale and shift 技巧 对归一化的数据再进行缩放和平移 x_norm = x_norm *γ +β
# 𝛾 𝛽参数均由反向传播算法自动优化，实现网络层“按需”缩放平移数据的分布的目的
# BN层对输入的x_train归一化得到x~_train，x~_train = (x_train-μB)/σB * γ +β 使用的是当前训练batch的平均值和方差
# 然后对全局训练数据的μr 和σr按照公式 M*μr+(1-M)μB      M*σr^2 + (1-M)σr^2  进行更新
# 即M=0时使用当前最新的batch统计值，M=1忽略当前batch，一般M=0.99
# 测试阶段直接使用训练数据的全局参数不更新 x~_test = (x_test-μr)/σr * γ +β
# 训练模式下的反向更新阶段，反向传播算法根据损失L求解梯度∂L/γ 和 ∂L/β
# 统计时按照通道进行计算，c个通道则有c个均值
# Layer Norm：统计每个样本的所有特征的均值和方差
# Instance Norm：统计每个样本的每个通道上特征的均值和方差
# Group Norm：将 c 通道分成若干组，统计每个样本的通道组内的特征均值和方差

# 空洞卷积在不增加网络参数的条件下，提供了更大的感受野窗口
# layers.Conv2D()类的 dilation_rate 参数来选择使用普通卷积还是空洞卷积

# 转置卷积：通过在输入之间填充大量的 padding 来实现输出高宽大于输入高宽的效果，从而实现向上采样的目的
# tf.nn.conv2d_transpose，layers.Conv2DTranspose，padding='VALID'或"SAME"不支持自定义


# 全连接层 : 通常在神经网络的尾部 , 此时已经极大降低了输入数据的维度、总参数个数
# 通常卷积网络的最后会将末端得到的长方体平摊成一个长长的向量，并送入全连接层配合输出层进行分类
# 可以认为全连接层之间的在做特征提取，而全连接层在做分类，这就是卷积神经网络的核心

# 2012 AlexNet-->2014 VGG-->GoogLeNet 2015 -->ResNet 2015 --> DenseNet 2016

# 常见的CNN卷积网络流程
# input-->conv2d-->max_pooling-->conv2d_1-->max_pooling_1-->reshape-->dense-->dropout-->dense_1-->output
# examples :
# 1) 顺序式API : 最常见的一类模型是一组层的堆叠
n_classes = 10
(train_x,train_y),(test_x,test_y) = fashion_mnist .load_data()
train_x = train_x / 255. * 2 -1
test_x = test_x / 255. * 2 -1  # [-1,1]
epochs = 10
batch_size = 32
per_epoch_iters = int(train_x.shape[0] / batch_size)
model = tf.keras.Sequential([
    # filters = 32 卷积核的数量 也就是下一层的输出个数 kernel_size 卷积核的高度和宽度
    # 第一层权重参数为 filters * kernel_size^2 * D1(输入层的深度) = 32*5*5*1(灰度图)
    # 第一层的偏置参数为filters个偏置 32
    # parms_1 = 840 + 32 = 832
    # 输入尺寸 :　28 * 28
    # output_shape = (input_shape - kernel_size + 1) / strides) = (28 - 5) + 1 = 24 * 24
    # (None, 24, 24, 32) 输出深度 = filters = 32
    tf.keras.layers.Conv2D(filters=32 ,kernel_size= (5,5),strides=(1,1),activation=tf.nn.relu,input_shape=(28,28,1)),

    # 池化层不影响参数个数 只是进行数据压缩采样 (None, 12, 12, 32)
    # 输入尺寸 = 24 * 24
    # pooling在不同的depth上是分开执行的 故 输出深度 = 32不变
    # pool_size=(2, 2)表示每4个像素得到一个值,每2行缩成1行
    # 故输出尺寸为 12 * 12
    tf.keras.layers.MaxPooling2D(pool_size=(2, 2),strides=(2,2), padding='valid'),

    # 继续卷积
    # 第二层权重参数 = 64*3*3*32 = 18432  + 64个偏置参数 = 18496
    # 输入尺寸  = 12 * 12
    # 输出尺寸 = 12 - 3 + 1 = 10
    # 输出深度 = 64
    # (None, 10, 10, 64)
    tf.keras.layers.Conv2D(filters=64,kernel_size=(3,3),activation=tf.nn.relu),

    # 输入尺寸 = 10 * 10
    # 输出深度 = 64 不变
    # 输出尺寸 = 10 / 2 = 5 * 5
    # (None, 5, 5, 64)
    tf.keras.layers.MaxPooling2D(pool_size=(2, 2),strides=(2,2), padding='valid'),

    # 展平层向量用于衔接全连接层Dense
    # 5*5*64 = 1600
    tf.keras.layers.Flatten(),

    # 第一个全连接层指定1024个神经元 1600*1024 个权重参数 + 1024 个偏置参数 = 1639424
    tf.keras.layers.Dense(units=1024,activation=tf.nn.relu),

    # 引入Dropout防止过拟合
    # 训练期间的每一步以 rate 的频率随机将输入单元设置为 0，这有助于防止过拟合。
    # 未设置为 0 的输入按 1（1 - rate）放大，以便所有输入的总和保持不变
    tf.keras.layers.Dropout(rate=0.5),

    # 最后一层,分类层的全连接层 参数 = 1024*10+10=10250
    tf.keras.layers.Dense(n_classes)
])
# tf.expand_dims可以1:1替代np.expand_dims 即对train_x添加一个维度 但是区别在于生成的是tf.Tensor对象
# 由于model.compile方法需要np.array对象 所以继续使用了numpy方法
# 每个tf.Tensor都有对应的Tensor对象包含的Numpy值
# shape=(60000, 28, 28, 1), dtype=float64) ----> shape=(60000, 28, 28, 1, dtype=float64)
train_x = tf.expand_dims(train_x,-1).numpy()
# 对输入的张量增加维度,至于数字没有太大意义 axis指定插入的维度所在位置
test_x  = tf.expand_dims(test_x, -1).numpy()
model.summary()
model .compile(optimizer= tf.keras.optimizers .Adam(learning_rate=1e-5),loss='sparse_categorical_crossentropy',metrics=['accuracy'])
# N=60000,batch_size = 32 , per_epoch_iters = 1875 , epochs = 10, total_iters = 18750
model.fit(train_x,train_y,epochs=epochs,batch_size=None)

# N_ = 10000 batch_size = 32 per_epoch_iters = 313
model.evaluate(test_x,test_y)
# 313/313 [==============================] - 5s 15ms/step - loss: 0.7884 - accuracy: 0.7809

#%%
# 2) 函数式API : 可以定义复杂的拓扑无需考虑顺序层的限制 可以定义多输入多输出的模型
# 展示一个使用函数型接口的Keras模型 该神经网络接收100维输入 输出一个数
# 网络层的实例是可调用的，它以张量为参数，并且返回一个张量
# 输入和输出均为张量，它们都可以用来定义一个模型（Model）
# 利用函数式 API，可以轻易地重用训练好的模型：可以将任何模型看作是一个层，然后通过传递一个张量来调用它
# 注意，在调用模型时，不仅重用模型的结构，还重用了它的权重
# 这部分返回一个张量
input_shape = (100,)
# 层的实例是可调用的，它以张量为参数，并且返回一个张量
inputs = tf.keras.layers.Input(input_shape)  # 用于实例化 Keras 张量
# Keras张量的属性使我们能够仅通过了解模型的输入和输出来构建 Keras 模型
# 假设存在张量a、b、c 那么 model = Model(input=[a, b], output=c)
net = tf.keras.layers.Dense(units=64,activation=tf.nn.relu,name='fc1')(inputs) # 64 * 100 + 64
net = tf.keras.layers.Dense(units=64,activation=tf.nn.relu,name='fc2')(net) # 64 * 64 + 64
net = tf.keras.layers.Dense(units=1,activation=tf.nn.relu,name='G')(net)# 64 * 1 + 1
# 这部分创建了一个包含输入层和三个全连接层的模型
model = tf.keras.Model(inputs=inputs,outputs=net)
model.compile(optimizer='rmsprop',
              loss='categorical_crossentropy',
              metrics=['accuracy'])
model.summary()
#%%
# 3) 子类方法 : 面向对象更灵活但是难以调试
class Generator(tf.keras.Model) :

    def __init__(self):
        # 对继承自父类的属性进行初始化。而且是用父类的初始化方法来初始化继承的属性
        # 子类继承了父类的所有属性和方法，父类属性自然会用父类方法来进行初始化
        # 初始化的逻辑与父类的不同，不使用父类的方法，自己重新初始化也是可以的
        super(Generator,self).__init__()
        self.dense_1 = tf.keras.layers.Dense(
            units=64,activation=tf.nn.relu,name='fc1'
        )
        self.dense_2 = tf.keras.layers.Dense(
            units=64,activation=tf.nn.relu,name='fc2'
        )
        self.output_1 = tf.keras.layers.Dense(units=1,name='G')

    def call(self , inputs):
        net = self.dense_1(inputs)
        net = self.dense_2(net)
        net = self.output_1(net)
        return net
# %%
# 【12】 常见的OP运算
# 1) 标量运算 add、sub、div、mul、log、greater、less、equal
# 2) 向量运算 concat、slice、constant、rank、shape、shuffle
# 3) 矩阵运算 matmul、matrixinverse、matrixdateminant
# 4) 带状态的运算 variable 、assign 、assignadd
# 5) 神经网络组件 softmax、sigmoid、relu、convolution、max_pool
# 6) 存储、恢复 save 、restore
# 7) 队列和同步运算 Enqueue、Dequeue、MutexAcquire、MutexRelease
# 8) 控制流 Merge、Switch、Leave、NextIteration
#%%
# 【13】 tf.data.Dataset数据集对象
# 该对象将一个输入流水线变为一系列元素，每个元素包含了1个或多个tf.Tensor对象
# tf.data.Dataset本身是可迭代的，但不是迭代器 一般需要next(iter)配合使用来枚举元素 或者使用for循环


# Raw data ---> .map() ---> .cache() ---> .shuffle() ---> .batch() ---> .prefetch ---> Model input
# CPU执行生产数据 CPU/GPU/TPU消费数据 需要平衡目标设备和生产设备的处理速度 用到并行计算技术
# 并行计算可以提高目标设备的资源利用率 后台不断工作产生下一轮迭代消费者需要的数据
# .cache()是将数据缓存到数据内存中 可以加速接下来的运算
# .repeat()目的是在多轮训练中将训练集的全部数据喂给模型 所以需要重复
# 预取方法.prefetch(n)用来应用生产者和消费者工作重叠的变换 n的单位是多少个batch 表示一次迭代消费的样本数

# 创建数据集对象取决于数据源的格式，主要有以下五种
# 1) 从内存中的张量获取 : tf.data.Dataset.from_tensors 或者 tf.data.Dataset.from_tensor_slices
# 这些张量可以是Numpy数组或者tf.Tensor对象
# 作用是把给定的元组、列表和张量等数据进行特征切片,范围从最外层维度开始
# 如果有多个特征进行组合，那么一次切片是把每个组合最外维度的数据切开，分成多组
dataset = tf.data.Dataset.from_tensor_slices(
    # tf.random.uniform(shape=[])得到张量
    {"a": tf.random.uniform(shape=[4]) , # 从均匀分布中输出随机值 ,默认范围是 [0, 1)
     "b": tf.random.uniform(shape=[4,100],maxval=100,dtype=tf.int32 )}
) # 得到TensorSliceDataset数据集 压缩了4×100的字典
list(dataset.as_numpy_iterator()) # 将数据集的所有元素转换为 numpy 得到一个迭代器输出 list是转换输出
for value in dataset : # 表示dataset的数据子集
    print(value["a"]) # 打印子集关键词"a"的数组
#%%
# 2) 从一个Python生成器/迭代器获取 tf.data.Dataset.from_generator
# 关于生成器的生成方法主要是两种，一种是使用列表产生，一种是借助函数+yield产生

# 1. g = (表达式 for 变量 in 列表)
generator = (x*x  for x in range(10))
# 相对于list = [x*x  for x in range(20) ]好处在于不需要创建完整的数据列表 节省内存
print(generator.__next__()) # 或者
print(next(generator)) # 语句出现多少次才会迭代多少次 所以需要配合循环
# 或者借助list(map(func,iter))输出元素
def func(value):
    return value * 2
print(list(map(func,generator )))

# 2. 函数 + yield 利用函数得到生成器
def func_1():
    n = 0
    while 1:
        n += 1
        yield n
g = func_1()  # 此函数为生成器对象
print(next(g))
print(next(g))

def noise():
    # 定义一个产生无限数量的随机向量的数据集 每个向量有100个元素
    while 1 :
        yield  tf.random.uniform((100,))
dataset = tf.data.Dataset.from_generator(noise,(tf.float32)) # 参数类型必须指定
# <FlatMapDataset shapes: <unknown>, types: tf.float32>
# tf.data.Dataset.from_generator用法类似于map,得到的数据类型是FlatMapDataset
# 链式调用创建新的数据集对象，map方法允许将一个函数应用在输入数据集的每一个元素上，生成一个新的变换过的数据集
dataset = dataset.map(map_func=lambda x:x+10).shuffle(buffer_size=10).batch(batch_size=32)
# <BatchDataset shapes: <unknown>, types: tf.float32>
#%%
# 3) 从模式匹配的文件 tf.data.Dataset.list_files
# 4) 处理TFRecord文件 tf.data.TFRecordDataset
# TFRecord格式是一个二进制的与语言无关的格式、使用protobuf定义用来存储一系列二进制记录
# Tensorflow可以读写一系列tf.Example消息组成的TFRecord文件
# tf.Example作为消息类型 存在字典映射 key(特征名称)-->value(二进制表示)
# 读取的图像不是压缩格式而是二进制格式 读取速度加快无需解码 但耗费硬盘空间
import tensorflow_datasets # tfds-->基于TFRecord文件规范的高级API
# 5) 处理文本文件 tf.data.TextLineDataset 以行为单位读取

# 6) 数据增强/扩充技术 tf.image包提供的API
# 可以先定义个增强函数再使用dataset.map方法进行变换
# 还可使用第三方库imgaug、albumentations对数据进行扩充
def convert_image(image):
    # 随机水平翻转图像（从左到右）宽度
    image = tf.image.random_flip_left_right(image)
    # 以二分之一的机会，输出沿第一个维度翻转的图像的内容，即高度
    image = tf.image.random_flip_up_down(image)
    # 通过随机因子调整图像的亮度
    image = tf.image.random_brightness(image,max_delta=0.1)
    return image

# example : 定义的函数可立即返回tf.data.Dataset对象
def train_dataset(batch_size=32,num_epochs=1):
    (train_x,train_y),(test_x,test_y) = fashion_mnist.load_data()
    input_x , input_y = train_x , train_y
    def scale_fn(image,label) :
       # 归一化图像格式到[-1,1]
        return (tf.image.convert_image_dtype(image,tf.float32) - 0.5 ) *2.0 ,label
    dataset = tf.data.Dataset.from_tensor_slices(
        (tf.expand_dims(input_x,-1) , tf.expand_dims(input_y,-1))
    ).map(scale_fn)

    dataset = dataset.cache().repeat(num_epochs)
    dataset = dataset.shuffle(batch_size)

    return dataset.batch(batch_size).prefetch(1) # 抓取的样本预取一个迭代数量

dataset_ = train_dataset()

#%% 【14】 标准的ETL过程
# 提取Extract 转换Transform 载入Load
# 通过定义get_input_fn函数将ET过程封装 input_fn函数返回features和labels对象
# 模型、数据集可以处于不同的模式，这个模式决定处于数据流水线的阶段
# 可以通过枚举enum类型tf.estimator.ModeKeys实现 包括Train、Eval、Predict，即训练、评估、推理模式
# 定义获取输入流水线函数get_input_fn
def get_input_fn(mode,batch_size=32,num_epochs=1):
    '''
    :param mode: 根据tf.estimator.ModeKeys的模式获取输入函数
    :param batch_size: 一次迭代抓取的样本数
    :param num_epochs: 模型遍历训练集的次数
    :return: 返回输入函数input_fn  训练模式时执行随机重复否则不执行
             input_fn的返回值为features和labels
    '''
    (train_x,train_y),(test_x,test_y) = fashion_mnist.load_data()
    half = test_x.shape[0] // 2
    if mode == tf.estimator.ModeKeys.TRAIN :
        input_x ,input_y = train_x , train_y
        train = True
    elif mode == tf.estimator.ModeKeys.EVAL:
        input_x , input_y = test_x[:half] ,test_y[:half]
        train = False
    elif mode == tf.estimator.ModeKeys.PREDICT :
        input_x, input_y = test_x[half:-1], test_y[half:-1]
        train = False
    else:
        raise ValueError("tf.estimator.ModeKeys required!")

    def scale_fn(image,label) :
        return ( 2 * tf.image.convert_image_dtype(image,tf.float32) - 1 ,
                 # tf.cast()函数的作用是执行 tensorflow 中张量数据类型转换
                 # 将label的Tensor或SparseTensor或IndexedSlices转换成dtype类型
                 tf.cast(label,tf.int32))
    def input_fn():
        # 1、将完整的训练集张量数据集切片返回DataSet对象 使用map归一化
        dataset = tf.data.Dataset.from_tensor_slices((tf.expand_dims(input_x,-1),
                                                     tf.expand_dims(input_y,-1))).map(scale_fn)
        # 2、当指定为模型训练阶段时进入执行随机操作
        if train :
            dataset = dataset.shuffle(10).repeat(count=num_epochs)
            # 重复此数据集，因此每个原始值都会被看到count次 即一个周期
        # 3、否则直接预取1个batch的数据集并返回
        return dataset.batch(batch_size).prefetch(1) # 预取1个batch的样本数

    return input_fn
#  定义模型生成和函数make_model
def make_model(n_classes=10):
    model = tf.keras.Sequential([
    # filters = 32 卷积核的数量 也就是下一层的输出个数 kernel_size 卷积核的高度和宽度
    # 第一层权重参数为 filters * kernel_size^2 * D1(输入层的深度) = 32*5*5*1(灰度图)
    # 第一层的偏置参数为filters个偏置 32
    # parms_1 = 840 + 32 = 832
    # 输入尺寸 :　28 * 28
    # output_shape = (input_shape - kernel_size + 1) / strides) = (28 - 5) + 1 = 24 * 24
    # (None, 24, 24, 32) 输出深度 = filters = 32
    tf.keras.layers.Conv2D(filters=32 ,kernel_size= (5,5),strides=(1,1),activation=tf.nn.relu,input_shape=(28,28,1)),

    # 池化层不影响参数个数 只是进行数据压缩采样 (None, 12, 12, 32)
    # 输入尺寸 = 24 * 24
    # pooling在不同的depth上是分开执行的 故 输出深度 = 32不变
    # pool_size=(2, 2)表示每4个像素得到一个值,每2行缩成1行
    # 故输出尺寸为 12 * 12
    tf.keras.layers.MaxPooling2D(pool_size=(2, 2),strides=(2,2), padding='valid'),

    # 继续卷积
    # 第二层权重参数 = 64*3*3*32 = 18432  + 64个偏置参数 = 18496
    # 输入尺寸  = 12 * 12
    # 输出尺寸 = 12 - 3 + 1 = 10
    # 输出深度 = 64
    # (None, 10, 10, 64)
    tf.keras.layers.Conv2D(filters=64,kernel_size=(3,3),activation=tf.nn.relu),

    # 输入尺寸 = 10 * 10
    # 输出深度 = 64 不变
    # 输出尺寸 = 10 / 2 = 5 * 5
    # (None, 5, 5, 64)
    tf.keras.layers.MaxPooling2D(pool_size=(2, 2),strides=(2,2), padding='valid'),

    # 展平层向量用于衔接全连接层Dense
    # 5*5*64 = 1600
    tf.keras.layers.Flatten(),

    # 第一个全连接层指定1024个神经元 1600*1024 个权重参数 + 1024 个偏置参数 = 1639424
    tf.keras.layers.Dense(units=1024,activation=tf.nn.relu),

    # 引入Dropout防止过拟合
    # 训练期间的每一步以 rate 的频率随机将输入单元设置为 0，这有助于防止过拟合。
    # 未设置为 0 的输入按 1（1 - rate）放大，以便所有输入的总和保持不变
    tf.keras.layers.Dropout(rate=0.5),

    # 最后一层,分类层的全连接层 参数 = 1024*10+10=10250
    tf.keras.layers.Dense(n_classes)
])
    return model
#  定义估计器生成函数model_fn
def model_fn(features,labels,mode):
    # 训练和记录summary操作必须使用tf.compat.v1兼容模块
    # 确保高版本的TF支持低版本的TF代码
    v1 = tf.compat.v1
    model = make_model(n_classes=10)

    preictions_onehot = model(features) # 得到独热编码

    mode_list = [tf.estimator.ModeKeys.TRAIN ,
                 tf.estimator.ModeKeys.EVAL ,
                 tf.estimator.ModeKeys.PREDICT ]

    # For mode==ModeKeys.TRAIN: 需要的参数是 loss and train_op.
    # For mode==ModeKeys.EVAL:  需要的参数是  loss.
    # For mode==ModeKeys.PREDICT: 需要的参数是 predictions.
    # 定义了一个具体的估计器模型对象

    # 1) PREDICT阶段
    if mode == mode_list[-1]:
        predictions = v1.argmax(preictions_onehot,-1) # 找到独热编码1的位置 也就是预测的标签
        return tf.estimator.EstimatorSpec(mode,predictions=predictions)

    # reduce_mean中axis=None默认计算所有维度返回一个值 axis=0按列计算平均值返回列张量 axis=1按行
    loss =v1.reduce_mean(v1.nn.sparse_softmax_cross_entropy_with_logits(
        # 计算logits和labels之间的稀疏 softmax 交叉熵
        # 测量离散分类任务中的概率误差，其中类是互斥
        logits=preictions_onehot,
        # 从张量的形状中删除大小为 1 的维度
        labels=v1.squeeze(labels)),
        axis=None)

    # 2) EVAL阶段
    # 计算准确率
    accuary = v1.metrics.accuracy(
        labels=labels , predictions=v1.argmax(preictions_onehot ,-1),name='accuracy')
    metrics = {"accuracy":accuary}
    if mode  == mode_list[-2] :
        # 使用准确率来验证
        return tf.estimator.EstimatorSpec(mode,loss=loss,eval_metric_ops= metrics)

    # 3) TRAIN阶段
    # 获取全局步长张量 在train_op的定义中使用
    global_step = v1.train.get_global_step()
    if mode == mode_list[0]:
        opt = v1.train.AdamOptimizer(1e-4)
        # 通过更新 var_list 添加操作以最小化 loss
        train_op = opt.minimize (
            loss=loss,
            var_list=model.trainable_variables,
            global_step=global_step
        )
        return tf.estimator.EstimatorSpec(mode,loss=loss,train_op =train_op)
    # 抛出错误 : 方法或函数尚未实现
    raise NotImplementedError (f"Unknown mode {mode}")
#  实例化估计器
#%% 定义两用对象tf.estimator.EstimatorSpec 使用mode决定模式
# tf.estimator.Estimator内部对模型编译过
estimator = tf.estimator.Estimator(model_fn=model_fn,model_dir="log")
epochs = 5
for epoch in range(epochs) :
    print(f"第{epoch}次迭代")
    # 训练函数需要数据集 只是这里使用的输入流函数以迭代方式提供数据集
    estimator.train(get_input_fn(
        mode=tf.estimator.ModeKeys.TRAIN,
        num_epochs= 1
    ))
    estimator.evaluate(get_input_fn(
        mode = tf.estimator.ModeKeys.EVAL
    ))
#%%
# 也可以不定义  tf.estimator.EstimatorSpec对象
# 直接定义train_spec和eval_spec对象
train_spec = tf.estimator.TrainSpec(input_fn=get_input_fn(tf.estimator.ModeKeys.TRAIN,num_epochs=5))
eval_spec = tf.estimator.EvalSpec(input_fn=get_input_fn(tf.estimator.ModeKeys.EVAL,num_epochs=1))
model = make_model(10)
# 模型手动编译
model.compile(optimizer='adam',loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])
# 模型手动转换为估计器
estimator = tf.keras.estimator.model_to_estimator(keras_model=model)
# 使用train_and_evaluate方法
tf.estimator.train_and_evaluate(estimator,train_spec,eval_spec)




