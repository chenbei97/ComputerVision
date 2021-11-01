#%%
# -*- coding UTF-8 -*-
'''
@Project : MyPythonProjects
@File : 6.汽车效能数据集回归预测.py
@Author : chenbei
@Date : 2021/8/9 16:41
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
from tensorflow import keras
from tensorflow.keras import layers
# 一、读取数据并处理
dataset_path = tf.keras.utils.get_file("auto-mpg.data",
"http://archive.ics.uci.edu/ml/machine-learning-databases/auto-mpg/autompg.data")
column_names = ['MPG','Cylinders','Displacement','Horsepower','Weight',
 'Acceleration','Model Year','Origin']
raw_dataset = pd.read_csv(dataset_path,
                          names=column_names,#指定列名，如果数据文件中没有列标题行，就需要执行header=None
                           na_values="?", # 一组用于替换NA/NaN的值
                           comment='\t', # 如果该字符出现在行首，这一行将被全部忽略
                           sep=" ", # 指定分割符，默认是"，"
                          skipinitialspace=True )# 忽略分隔符后的空格
dataset = raw_dataset.copy()
print(dataset.isna().sum())# 统计空白数据
dataset = dataset.dropna() # 删除空白数据
origin = dataset.pop('Origin') # pop方法可以将所选列从原数据块中弹出，原数据块不再保留该列
print((origin == 1)*1)
dataset['USA'] = (origin == 1)*1.0 # USA列的取值取决于origin是否为1,为1时=1否则为0
dataset['Europe'] = (origin == 2)*1.0 # 其它同理转为独热编码(×1.0可以自动将bool型变为浮点型)
dataset['Japan'] = (origin == 3)*1.0 # 广播效应可以自动遍历origin的每个元素并映射到dataset的3个列上
#%% 二、拆分数据集为测试集和训练集并归一化
train_dataset = dataset.sample(frac=0.8,random_state=0) # 不放回抽样80%
print(train_dataset.index) # 行索引
test_dataset = dataset.drop(index=train_dataset.index) # 删除index指定的行,也可以按labels进行删除,但这里用index删更方便
# sns.pairplot(train_dataset[["MPG", "Cylinders", "Displacement", "Weight"]], diag_kind="kde")
# plt.show() # 矩阵图
train_labels = train_dataset.pop('MPG')
test_labels = test_dataset.pop('MPG') # 把MPG每加仑英里当成预测值,因为不是分类问题
# 给出训练集的描述信息并转置
train_stats = train_dataset.describe()
# 转置方便后边调用可以直接取每列的平均值和方差用于归一化
train_stats = train_stats.transpose()
# 归一化数据 全局变量train_stats可以在函数内部使用
def norm(x):
    # 输入 x.shape=314*9或78*9 - (9,) 广播效应自动变为(b,9) 每个样本的一行参数减去对应的一行参数均值
    return (x - train_stats['mean']) / train_stats['std']
normed_train_data = norm(train_dataset)
normed_test_data = norm(test_dataset)
#%% 三、构建和编译模型
# units = 正整数，输出空间的维数
def build_model():
  model = keras.Sequential([
      # 包含两个紧密相连的隐藏层
    layers.Dense(64, activation='relu', input_shape=(9,)), # 输入的样本向量个数b=314 特征长度din=9
    layers.Dense(64, activation='relu'),
    layers.Dense(1)]) # 返回单个节点、连续值的输出层
  optimizer = tf.keras.optimizers.RMSprop(0.001)
  model.compile(loss='mse',
                optimizer=optimizer,
                metrics=['mae', 'mse']) # 平均绝对误差 和 均方误差
  return model
model = build_model()
# model.summary()
EPOCHS = 1000
history = model.fit(
  normed_train_data, train_labels,
  epochs=EPOCHS, validation_split = 0.2)
#%% 四、绘制两种误差随着epoch的变化曲线
def plot_history(history):
  hist = pd.DataFrame(history.history) # loss、mae、mse、val_loss、val_mae、val_mse (dict*6 list*1000)
  hist['epoch'] = history.epoch # list * 1000 添加周期到hist的列 命名为epoch
  fig, ax = plt.subplots()
  ax.set_xlabel('Epoch')
  ax.set_ylabel('MAE')
  ax.plot(hist['epoch'], hist['mae'],color='g',
           label='train_mae')
  ax.plot(hist['epoch'], hist['val_mae'],color='c',
           label = 'val_mae')
  # print(hist['mae'].max())
  ax.set_ylim([0, max(hist['mae'].max(), hist['val_mae'].max())])
  ax.legend(loc='upper left')
  ax1 = ax.twinx()
  ax1.plot(hist['epoch'], hist['mse'],color='r',
           label='train_mse')
  ax1.plot(hist['epoch'], hist['val_mse'],color='b',
           label = 'val_mse')
  ax1.set_ylim([0,max(np.max(hist['mse']),np.max(hist['val_mse']))])
  ax1.set_xlabel('Epoch')
  ax1.set_ylabel('MSE')
  ax1.legend(loc='upper right')
  plt.show()
plot_history(history)
#%% 五、使用早期停止技术防止过拟合 训练误差没有提高时自动停止训练 结果显示第50代停止了训练
model = build_model()
# patience : 超过patience个周期没有满足最小改善条件即停止
# monitor : 监控的指标
# min_delta :　最小改善条件 当训练集上的loss不在减小(即减小的程度小于某个阈值)则停止训练
early_stop = keras.callbacks.EarlyStopping(monitor='val_loss', patience=10,min_delta=0)
history = model.fit(normed_train_data, train_labels, epochs=EPOCHS,
                    validation_split = 0.2, verbose=0, callbacks=[early_stop])
plot_history(history)
#%% 六、测试模型的泛化能力 评估测试集
loss, mae, mse = model.evaluate(normed_test_data, test_labels, verbose=2)# 返回标量损失
print("测试集的绝对误差: {:5.3f} MPG".format(mae))
test_pred = model.predict(normed_test_data).flatten() # (78,1).flatten ----> (78,)
point_loss = [np.square(test_labels.array[i]-test_pred[i]) for i in range(test_pred.shape[0])]
plt.scatter(test_labels, test_pred) # 测试集的实际绝对误差和预测绝对误差
plt.plot(point_loss,label='mse_loss')
plt.xlabel('真实值 [Actual Value]')
plt.ylabel('预测值 [Pred Value]')
plt.axis('equal')
plt.axis('square')
plt.xlim([0,max(max(test_labels),max(test_pred))+5])
plt.ylim([0,max(max(test_labels),max(test_pred))+5])
plt.plot([0, 50], [0, 50],label='y=x') # 正比例直线 点的分布接近于y=x,即平均绝对误差很小
plt.legend()
plt.show()
# 还可以观察mse误差分布(直方图)
plt.hist(point_loss, bins = 25)
plt.xlabel("MSE")
plt.ylabel("Num")
plt.show()
# 主要结论
# 均方误差（MSE）是用于回归问题的常见损失函数（分类问题中使用不同的损失函数）
# 类似的，用于回归的评估指标与分类不同。 常见的回归指标是平均绝对误差（MAE）
# 当数字输入数据特征的值存在不同范围时，每个特征应独立缩放到相同范围
# 如果训练数据不多，一种方法是选择隐藏层较少的小网络，以避免过度拟合
# 早期停止是一种防止过度拟合的有效技术
#%% 七、通过创建类来实现回归预测
class Network(keras.Model):
     # 回归网络
     def __init__(self):
        super(Network, self).__init__()
        # 创建 3 个全连接层
        self.fc1 = layers.Dense(64, activation='relu')
        self.fc2 = layers.Dense(64, activation='relu')
        self.fc3 = layers.Dense(1)
     def call(self, inputs, training=None, mask=None):
     # 依次通过 3 个全连接层
         x = self.fc1(inputs)
         x = self.fc2(x)
         x = self.fc3(x)
         return x
model = Network() # 创建网络类实例
# 通过 build 函数完成内部张量的创建，其中 4 为任意的 batch 数量，9 为输入特征长度
model.build(input_shape=(4, 9))
model.summary()
# 打印网络信息 (b * din) * (din * dout1) + b * (1 * dou1) 广播 = 9 * 64 + 1 * 64 = 640
# (b * dout1) * (dout1 * dout2) + b * (1 * dout2) = 64 * 64 + 1 * 64 = 4160
# (b * dout2) * (dout2 * dout) + b * (1 * dout) = 64 + 1 = 65
optimizer = tf.keras.optimizers.RMSprop(0.01) # 创建优化器，指定学习率
train_dataset = tf.data.Dataset.from_tensor_slices((normed_train_data.values, train_labels.values)) # 构建 Dataset 对象
train_dataset = train_dataset.shuffle(len(train_dataset)).batch(32) # 随机打散，批量化
epoch_mae = []
epoch_mse = []
for epoch in range(100): # 400 个 Epoch
    for step, (x,y) in enumerate(train_dataset): # 遍历一次训练集
        # 梯度记录器 step = 314 // 32 + 1 = 10
        with tf.GradientTape() as tape:
            out = model(x) # 通过网络获得输出
            mse_loss = tf.reduce_mean(tf.losses.MSE(y, out)) # 计算 MSE
            mae_loss = tf.reduce_mean(tf.losses.MAE(y, out)) # 计算 MAE
            print(f"第 {epoch+1} epoch的第 {step+1} step : mae = {mae_loss} mse = {mse_loss}")
            # 计算梯度，并更新
        grads = tape.gradient(mse_loss, model.trainable_variables)
        optimizer.apply_gradients(zip(grads, model.trainable_variables))
    epoch_mse.append(mse_loss) # 只记录最后一次
    epoch_mae.append(mae_loss)
plt.plot(epoch_mae,label='mse_loss')
# plt.plot(epoch_mse,label='mae_loss')
plt.legend()
plt.show()
