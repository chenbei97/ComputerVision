#%%
# -*- coding UTF-8 -*-
'''
@Project : MyPythonProjects
@File : 2.手写数字图片分类问题.py
@Author : chenbei
@Date : 2021/8/3 11:29
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl

plt.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
# plt.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
# plt.rcParams['savefig.dpi'] = 600  # 图片像素
# plt.rcParams['figure.dpi'] = 600  # 分辨率
from matplotlib.font_manager import FontProperties
font_set = FontProperties(fname=r"C:\Windows\Fonts\simsun.ttc", size=10.5)
import numpy as np
import pandas as pd
import tensorflow as tf
from keras.utils.np_utils import to_categorical
import os
# 【1】加载数据
(x_train,y_train) ,(x_test,y_test) = tf.keras.datasets.mnist.load_data() # ndarray格式
# 转换为张量 并缩放到[-1,1]
x_train = tf.convert_to_tensor(x_train,dtype=tf.float32)/255.
y_train = tf.convert_to_tensor(y_train,dtype=tf.int32)
x_train = tf.reshape(x_train, (-1, 28 * 28))
y_train = tf.one_hot(y_train,depth=10) # 手写数字0-9 共10类
x_test =  tf.convert_to_tensor(x_test,dtype=tf.float32)/255.
y_test = tf.convert_to_tensor(y_test,dtype=tf.int32)
x_test = tf.reshape(x_test, (-1, 28 * 28))
y_test = tf.one_hot(y_test,depth=10) # 手写数字0-9 共10类
# [数量维度,高度,宽度,通道数]=[b,h,w,c] 灰度图片c=1 RGBc=3
# print(x_train.shape,y_train.shape) # (60000, 28, 28, 1) (60000, 10)
#%% 【前向传播手动搭建网络】 o𝑢𝑡 = 𝑟𝑒𝑙𝑢{𝑟𝑒𝑙𝑢{𝑟𝑒𝑙𝑢[𝑋@𝑊1 + 𝑏1]@𝑊2 + 𝑏2}@𝑊 + 𝑏 }
# 最终结论 ：学习率要大一些=0.1 且使用交叉熵损失函数的平均值而不宜使用mse函数 准确率很低 迭代次数要超过50次较为合理
lr = 0.1
Loss = []
Output = []
# 输入节点数为 784，第一层的输出节点数是256
# 1) 首先将 shape 为[𝑏, 28,28]的输入数据 Reshape 为[𝑏, 784]
# -1表示自动推导 那么等于60000*28*28*1/(28*28) D=2 (60000, 784)
x_train = tf.reshape(x_train, [-1, 28 * 28])
# 2) 定义权重w和偏置b参数 第一层应当有784*256个w b的长度为256 个数为784
# 但是只需要定义1个b 不需要定义784个b
# 使用tf.Variable表示是可以训练优化的 b一般初始化为0
w1 = tf.Variable(tf.random.truncated_normal([784, 256], stddev=0.1))  # (784,256)
b1 = tf.Variable(tf.zeros([256]))  # (256,)
# 第二层的输出节点数是 128
w2 = tf.Variable(tf.random.truncated_normal([256, 128], stddev=0.1))
b2 = tf.Variable(tf.zeros([128]))
# 第三层的输出节点是 10
w3 = tf.Variable(tf.random.truncated_normal([128, 10], stddev=0.1))
b3 = tf.Variable(tf.zeros([10]))
epochs = 100
for epoch in range(epochs) :
    with tf.GradientTape() as tape :
        # 3) 开始逐层计算矩阵
        # print(b1) # 可以观察到b1一开始初始化为0 之后b1确实被更新
        # (b,784)*(784,256) + (256,)-->(b,256) 拓展到b行 也就是b的个数=输入样本个数
        # h1 shape = b * 256  w1 shape = 784 * 256
        h1 = x_train@w1 + tf.broadcast_to(b1, [x_train.shape[0], 256])
        # 激活函数
        h1 = tf.nn.relu(h1)
        # (b,256)*(256,128) + (128,)-->(b,128)
        # h2 shape = b * 128 w2 shape = 256 *128
        h2 = h1@w2 + b2
        h2 = tf.nn.relu(h2)
        # (b,128)*(128,10) + (128,)-->(b,10)
        # out shape = 60000 * 10  w3 shape = 128 * 10
        out = h2@w3 + b3
        # print(tf.reduce_max(out).numpy(),tf.reduce_min(out).numpy())
        out = tf.nn.softmax(out) # 将其归一化到0-1之间 且概率和为1
        # 断定输出在0-1之间 否则抛出错误
        assert  np.max(out.numpy())<=1 and np.min(out.numpy())>=0
        # loss1 = tf.reduce_mean(tf.square(y_train - out))
        loss1 = tf.keras.metrics.categorical_crossentropy(y_train,out,from_logits=False)# y_pred已被softmax设置为False
        loss1 = tf.reduce_mean(loss1)
        #loss2 = tf.reduce_mean(tf.keras.losses.mse(y_train, out)) # 两条计算loss的代码含义完全相
    grads = tape.gradient(loss1, [w1, b1, w2, b2, w3, b3])
    # w1 = w1 - lr * w1_grad 手动更新参数
    w1.assign_sub(lr * grads[0])
    b1.assign_sub(lr * grads[1])
    # print(b1) # 这是为了对照第一次打印b1 检查这里的b1是否被传递到下一次迭代的b1 两个应该相等
    w2.assign_sub(lr * grads[2])
    b2.assign_sub(lr * grads[3])
    w3.assign_sub(lr * grads[4])
    b3.assign_sub(lr * grads[5])
    Loss.append(loss1.numpy())
    Output.append(out)
    # 用于验证的代码
    argmax_out = tf.argmax(out, axis=1)
    # argmax_y_train = tf.argmax(y_train, axis=1)
    # tem_bool = tf.argmax(out, axis=1) == tf.argmax(y_train, axis=1) # 相等为True
    # tem_int32 = tf.cast(tem_bool, dtype=tf.int32).numpy()
    # tem_int32_count1 = list(tem_int32).count(1)
    # print(tem_int32_count1)
    acu = list((tf.cast(tf.argmax(out, axis=1) == tf.argmax(y_train, axis=1), dtype=tf.int32)).numpy()).count(1) / len(y_train)
    # print(f"第{epoch}次迭代： mse={round(loss1.numpy(), 5)}  accuracy={round(acu, 5)}")
    print(f"第{epoch}次迭代： cross_entropy={round(loss1.numpy(), 5)}  accuracy={round(acu, 5)}")
# 将预测标签和实际标签先转为非独热编码用于比较
actual_label = tf.argmax(y_train,axis=1)
# print(actual_label[0:5],actual_label[-6:-1]) # 验证每次程序运行训练集标签是否有变化 : 无变化
pre_label = [tf.argmax(Output[i],axis=1) for i in range(len(Output))]
# 对每个epoch得到的预测标签与实际标签进行比较 利用类型转换变成0-1类型
result = [tf.cast(actual_label == pre_label[i] ,dtype=tf.int32) for i in range(len(pre_label))]
accuracy = [list(result[i].numpy()).count(1) / len(actual_label) for i in range(len(result))]
plt.plot(np.arange(0,len(Loss)),Loss,label='cross_entropy')
plt.legend()
plt.show()
plt.plot(np.arange(0,len(Loss)),accuracy,label='accuracy')
plt.legend()
plt.show()
# 用于验证的代码
# aa = y_train.numpy() # 与argmax_y_train保持一致
ab = Output[-1].numpy() # 通过观察确实与argmax_out一致
# ac = tf.nn.softmax(Output[-1]).numpy() # 证明softmax处理前后不影响概率的大小关系
# 从结果来看准确率虽然上升、误差也确实下降但是准确率很低 故更换loss函数与【4】一致
# 也可以这样计算准确率：使用tf.equal代替== 、使用reduce_sum代替list.count(1)
# acu =[tf.equal(actual_label,pre_label[i]) for i in range(len(pre_label))] # epoch * 60000
# acu = [tf.cast(acu[i],dtype=tf.int32) for i in range(len(acu))] # epoch * 60000
# acu = [tf.reduce_sum(acu[i])/ 60000 for i in range(len(acu))]
#%%
# 【3】使用层搭建前向网络 和直接搭建结果基本相同 P54页
model = tf.keras.Sequential([tf.keras.layers.Dense(256,activation='relu',name='dense_1'),
                            tf.keras.layers.Dense(128,activation='relu',name='dense_2'),
                            tf.keras.layers.Dense(10,name='output',activation='softmax')])
# model.build(input_shape=(len(x_train),28*28))
# model_trainable_variables  = model.trainable_variables
opt = tf.keras.optimizers.SGD(learning_rate=0.1)
# shape=(60000,28,28)--->shape=(60000, 784) 打平二维图片矩阵
x_train = tf.reshape(x_train, (-1, 28 * 28))
epochs = 10 #
# 直接使用model去fit 10代足以 默认使用batch_size=32
model.compile(optimizer=opt ,loss='CategoricalCrossentropy',metrics= tf.keras.metrics.CategoricalAccuracy())
model.fit(x_train,y_train,epochs=epochs)
model.evaluate(x_test,y_test)
#%%
# 每次运算误差都不同 所以可以封装为函数传入迭代周期epochs
def train_epochs(epochs,x_train) :
    Loss = []
    Model_Trainable_Variables = [] # 模型的可训练参数
    Output = []
    Grads = []
    Trainable_weights = []
    for epoch in range(epochs) :
        with tf.GradientTape() as tape:
            output = model(x_train)  # shape=(60000, 10)
            # 断定输出在0-1之间 否则抛出错误
            assert np.max(output.numpy()) <= 1 and np.min(output.numpy()) >= 0
            # loss1 = tf.reduce_mean(tf.keras.losses.mse(y_train, output))
            loss1 = tf.reduce_mean(tf.keras.metrics.categorical_crossentropy(y_train,output,from_logits=False))
            # print(loss1.shape)
        # tf.argmax(output, axis=1) == tf.argmax(y_train, axis=1) 按行依次比对向量 相等为True 否则 False
        # tf.cast(* , dtype=tf.int8).numpy() 转为只有0,1的向量
        # 使用 list转为列表 使用count方法计算0的个数 ,相等时转为0 , 所以0的个数是预测正确的个数
        acu = list((tf.cast(tf.argmax(output, axis=1) == tf.argmax(y_train, axis=1), dtype=tf.int32)).numpy()).count(1) / len(y_train)
        print(f"第{epoch}次迭代： cross_entropy={round(loss1.numpy(),5)}  accuracy={round(acu,5)}")
        Loss.append(loss1.numpy())
        Model_Trainable_Variables.append(model.trainable_variables)
        Output.append(output)
        Trainable_weights.append(model.trainable_weights)
        #  计算三层网络参数的梯度 w1, w2, w3, b1, b2, b3
        grads = tape.gradient(loss1, model.trainable_variables) # grads的确有变化
        Grads.append(grads)
        # 更新网络参数  w' = w - lr * grad
        grads_and_vars = zip(grads, model.trainable_variables)
        opt.apply_gradients(grads_and_vars=grads_and_vars)
        # print(opt.get_weights())
    # 从结果来看Model_Trainable_Variables每次都是一样的  Grads不一样 Trainable_weights不一样
    return Loss ,Model_Trainable_Variables,Trainable_weights, Grads,Output,model
epochs = 50 # 手动需要100代 且没有batch_size的参与 【4】更像模拟compile、fit的过程
Loss ,Model_Trainable_Variables,Grads,Trainable_weights,Output,Model= train_epochs(epochs,x_train)
# 所有周期训练所预测的标签 每个周期的输出标签是60000*10的shape 故 Output实际上是epochs*60000*10(独热编码)
# Output[i]表示取出第i个周期 对第i个周期的60000*10按行取最大值的索引 得到epochs*60000的shape(标签编码)
pre_label = [tf.argmax(Output[i],axis=1) for i in range(len(Output)) ]# 每行最大值的索引为预测的标签编码
actu_label = tf.argmax(y_train.numpy(),axis=1) # 实际标签的独热编码也转换为标签编码
# 与Loss的最后1个对的上
print("最后一次的训练交叉熵为: ",tf.reduce_mean(tf.keras.losses.mse(y_train, Output[-1])).numpy())
result = tf.cast(pre_label[-1] == actu_label,dtype=tf.int32)
print("最后一次的准确率为",list(result.numpy()).count(1) / len(actu_label) )
# 所有周期存放的准确率
accuracy = [ tf.cast(pre_label[i] == actu_label,dtype=tf.int32) for i in range(len(Output))]
accuracy = [list(accuracy[i].numpy()).count(1)/len(actu_label) for i in range(len(accuracy))]
plt.plot(np.arange(0,len(Loss)),Loss,label="CrossEntropy")
plt.legend()
plt.show()
plt.plot(np.arange(0,len(accuracy)),accuracy,label="Accuracy")
plt.legend()
plt.show()
# 使用迭代后的Model再进行fit
Model.compile(optimizer=opt ,loss='CategoricalCrossentropy',metrics= tf.keras.metrics.CategoricalAccuracy())
Model.fit(x_train,y_train,epochs=5)
Model.evaluate(x_test,y_test)
#%%
# 【4】不使用complie、fit自定义训练 使用batch训练集完整定义流程
# 1) 将标签转为独热编码----(独热编码没有梯度！！！？？？？)
# -----> 已解决: 并非独热编码没有梯度,加载数据时已经转换为独热编码
# y_train_onehot = to_categorical(y_train,10) # ---> 多余操作 变成了(60000, 10, 10)是错误的
# y_test_onehot = to_categorical(y_test,10)
# print(y_train_onehot.shape)
# 2) 将加载的x_train/x_test,y_train/y_test四个tensor转换成dataset格式
train_dataset = tf.data.Dataset.from_tensor_slices((x_train,y_train)) # 60000*784和60000*10(已展平和独热编码)
test_dataset = tf.data.Dataset.from_tensor_slices((x_test,y_test)) # 10000*784和10000*10(已展平和独热编码)
# 3) 随机打乱测试集取一半作为验证集 取后一半验证集
val_dataset = test_dataset.shuffle(buffer_size=len(x_test)).skip(len(x_test)//2)# 5000*784和5000*10(已展平和独热编码)
test_dataset = test_dataset.take(len(val_dataset)) # 剩下的前一半为测试集
# 4) 定义batch_size=64 取训练集和验证集块
batch_size = 64 # 一次抓取的样本数 60000/64=937.5 = 938
# 块数据集的形状=(None,784)和(None,10) None是因为有的批不一定是batch_size大小
train_dataset_batch = train_dataset.shuffle(buffer_size=len(train_dataset)).batch(batch_size)
# 5000 // 64 = 79 (None,784)和(None,10)
val_dataset_batch = val_dataset.shuffle(buffer_size=len(val_dataset)).batch(batch_size)
# 5000 // 64 = 79 (None,784)和(None,10)
test_dataset_batch = test_dataset.shuffle(buffer_size=len(test_dataset)).batch(batch_size)
# 5) 定义优化器、损失函数和评价函数
optimizer = tf.keras.optimizers.SGD(learning_rate=0.005)
# 要求传入的为onehot编码 输出模型的预测输出在[0,1]内 故from_logits=False不需要再进行缩放
loss = tf.keras.losses.CategoricalCrossentropy(from_logits=False)
# 准备metrics评价函数
train_acc_metric = tf.keras.metrics.CategoricalAccuracy()
val_acc_metric = tf.keras.metrics.CategoricalAccuracy()
#%%
# 6) 定义模型
model = tf.keras.Sequential([tf.keras.layers.Dense(256,activation='relu',name='dense_1'),
                            tf.keras.layers.Dense(128,activation='relu',name='dense_2'),
                            tf.keras.layers.Dense(10,name='output',activation='softmax')])
# 7) 周期迭代
epochs = 5
epochTrainAcu = [] # shape=(epoch,938)
epochTrainLoss = [] # shape=(epoch,938)
epochValAcu = []# shape=(epoch,79)
for epoch in range(epochs) :
    # 要放在step外边，epoch里边 否则会持续添加
    stepValAcu = []  # shape=(79，)
    stepTrainLoss = []  # shape=(938,)
    stepTrainAcu = []  # shape=(938,)
    print(f"当前迭代到第{epoch+1}周期，请继续等待...")

    for step, (x_batch_train, y_batch_train) in enumerate(train_dataset_batch):
        # y_batch_train.shape=(64,10)或(32,10) x_batch_train = (64,784) 或 (32,784)
        # step = 938 train_dataset_batch有938个x_batch_train 每次验证1个
        # 对每个块数据集的数据进行迭代 带有数据和标签
        # step为块数据集x_batch_train的内部数据编号

        # 验证x_batch_train是否相同 根据60000 = 937 * 64 + 32 最后一个batch形状为(32,784)
        # print(x_batch_train.shape)

        # 直观证明每个块数据集确实是不同的
        # print(np.mean(np.mean(x_batch_train.numpy(),axis=1)))
        # print(tf.norm(x_batch_train, ord=1).numpy()/ len(x_batch_train)) # 也可以通过计算范数验证

        with tf.GradientTape() as tape:
             # output.shape=(64, 10)
             print(f"正在运行：第{epoch+1}周期的第{step+1}步")
             output = model(x_batch_train)
             # print(output.shape,y_batch_train.shape) # 验证输出形状是否相等

             # 预计模型的输出应当满足在[0,1]之间 from_logits=False 否则提前抛出错误
             assert np.max(output.numpy())<=1 and np.min(output.numpy())>=0

             # 根据损失函数计算交叉熵损失
             step_train_loss_value = loss(y_true=y_batch_train, y_pred=output)
             step_train_acu_value = train_acc_metric(y_true=y_batch_train, y_pred=output)
        # print(f"第 %d 步 : loss = %.5f acu = %.5f " % (step,step_train_loss_value.numpy(),step_train_acu_value.numpy()))
        # 当前周期每步的loss和acu变化
        stepTrainLoss.append(step_train_loss_value.numpy())
        stepTrainAcu.append(step_train_acu_value.numpy())
        grads = tape.gradient(step_train_loss_value, model.trainable_variables) # 每一步都计算梯度
        optimizer.apply_gradients(zip(grads, model.trainable_variables)) # 每一步都更新参数

        # 证明梯度和参数确实更新的代码 因为本身过小所以不使用平均而是用求和
        def tensor_sum(tensor):
            array = tensor.numpy()
            if array.ndim > 1 :
               return np.round(np.sum(np.sum(array,axis=1)),5)
            else:
                return np.round(np.sum(array),5)
        variables = [tensor_sum(grads[i]) for i in range(6)]
        # print("w1=%.5f b1=%.5f w2=%.5f b2=%.5f w3=%.5f b3=%.5f"
        #       % (variables[0],variables[1],variables[2],variables[3],variables[4],variables[-1]))

    # 得到所有周期的准确率结果 epoch*step
    epochTrainLoss.append(stepTrainLoss)
    epochTrainAcu.append(stepTrainAcu)
    # 重置训练集指标用于下一epoch使用
    train_acc_metric.reset_states()

    # 使用当前周期该块数据集的训练结果对验证集进行验证

    for x_batch_val, y_batch_val in val_dataset_batch:
        # val_dataset_batch.shape= (None,784)和(None,10)
        # 5000 // 64 = 79  5000 = 64 * 78 + 8
        # x_batch_val.shape=(64,784)或(8,784)
        # y_batch_val.shape=(64,10)或(8,10)
        # 总val_step = 79
        val_output = model(x_batch_val)
        step_val_acu_value = val_acc_metric(y_batch_val, val_output)
        stepValAcu.append(step_val_acu_value.numpy())
    epochValAcu.append(stepValAcu)
    # 重置验证集指标
    val_acc_metric.reset_states()
    if  epoch == epochs - 1 :
        print("迭代结束")
#%%
# 测试集预测
# 1) 整体进行预测 需要对分好的测试集解压得到数据和标签 因为model.predict只有一个输入且要求张量类型
x_test_shuffle,y_test_shuffle = zip(*test_dataset) # 解压得到2个tuple类型
x_test_shuffle = tf.convert_to_tensor(x_test_shuffle)
y_test_shuffle = tf.convert_to_tensor(y_test_shuffle)
test_pred = model.predict(x_test_shuffle)
equal_bool = tf.equal(tf.argmax(test_pred,axis=1),tf.argmax(y_test_shuffle,axis=1))
equal_int = tf.cast(equal_bool,dtype=tf.int64)
print("测试集的准确率为：",tf.reduce_sum(equal_int).numpy()/len(equal_int))
#%%
# 2) 按batch进行预测 仿照验证集得到多迭代的预测率
Test_ACU = []
for step ,(x_batch_test, y_batch_test) in enumerate(test_dataset_batch):
    test_output = model.predict(x_batch_test)
    test_result = tf.cast(tf.equal(tf.argmax(test_output,axis=1),tf.argmax(y_batch_test,axis=1)), dtype=tf.int64)
    test_acu = tf.reduce_sum(test_result).numpy()/len(test_result)
    print(f"正在执行第{step + 1}次预测：acu={test_acu}")
    Test_ACU.append(test_acu)
plt.plot(np.arange(0,len(Test_ACU)),Test_ACU,label="test_acu")
plt.plot([0,len(Test_ACU)],[np.mean(Test_ACU),np.mean(Test_ACU)],label="average_acu")
plt.legend()
plt.show()
#%%
# 绘制每个周期的train_loss、train_acu的步变化趋势
def  plot_epoch_curve(epochAcu,epochs,title,epochLoss=None,lossIsPlot=False) :
    # data =epochTrainAcu
    # plt.rcParams['figure.figsize'] = (10.8, 7.8)
    # plt.figure(figsize=(20, 26))
    fig, ax = plt.subplots()

    for epoch in range(epochs) :
        ax.plot(np.arange(0,len(epochAcu[epoch])),epochAcu[epoch],label=f"epoch={epoch}")
        # if lossIsPlot :
        #     plt.plot(np.arange(0,len(epochLoss[epoch])),epochLoss[epoch],label=f"epoch={epoch}")
    ax.plot(np.arange(0,len(epochAcu[epoch])),np.mean(epochAcu,axis=0),color='k',linewidth=1.5, label="平均准确率")
    ax.set_xlabel('Step')
    ax.set_ylabel('Acu')
    ax.legend(loc="lower right")
    if lossIsPlot :
        ax1 = ax.twinx()
        ax1.set_ylabel('Loss')
        ax1.plot(np.arange(0, len(epochLoss[epoch])), np.mean(epochLoss, axis=0),alpha=0.5,linewidth=0.5, label="平均交叉熵损失")
        ax1.legend(loc='upper left')
    plt.title(title)
    plt.show()
plot_epoch_curve(epochAcu=epochTrainAcu,epochs=epochs,epochLoss=epochTrainLoss,
                 title='训练集：准确率和交叉熵损失的周期步变化',lossIsPlot=True)
# plot_acu_loss_curve(data=epochTrainLoss,epochs=epochs,title="训练误差的周期步变化")
plot_epoch_curve(epochAcu=epochValAcu,epochs=epochs,title='验证集：准确率和交叉熵损失的周期步变化')

#%%










