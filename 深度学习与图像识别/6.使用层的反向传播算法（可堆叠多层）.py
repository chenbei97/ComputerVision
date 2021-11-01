#%%
# -*- coding UTF-8 -*-
'''
@Project : MyPythonProjects
@File : 6.使用层的反向传播算法（可堆叠多层）.py
@Author : chenbei
@Date : 2021/8/10 14:50
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
import seaborn as sns
from sklearn.datasets import make_moons
from sklearn.model_selection import train_test_split
X, y = make_moons(n_samples = 2000, noise=0.2, random_state=100) # shape=2000*2
X_train, X_test, y_train, y_test = train_test_split(X, y,test_size=0.3, random_state=42)
#%%
def make_plot(X, y, plot_name,dark=False):
    if (dark):
        plt.style.use('dark_background') # 使用黑色背景
    else:
        sns.set_style("whitegrid") # 默认白色背景
    axes = plt.gca()
    axes.set(xlabel="$x_1$", ylabel="$x_2$")
    plt.title(plot_name, fontsize=30)
    plt.subplots_adjust(left=0.20)
    plt.subplots_adjust(right=0.80)
    # 绘制散点图，根据标签区分颜色 数据点分为了0和1映射为2种颜色
    plt.scatter(X[:, 0], X[:, 1], c=y.ravel(), s=40, cmap=plt.cm.Spectral,edgecolors='none')
    plt.show()
# 调用 make_plot 函数绘制数据的分布，其中 X 为 2D 坐标，y 为标签
make_plot(X, y, "Classification Dataset Visualization ",dark=False)
#%% ∑γΩφσωθλδ∂ εŋ ɑ γ μ β
class MyLayer:
    # 定义网络层
    def __init__(self, n_input, n_neurons, activation=None, weights=None,
                 bias=None):
        '''
        :param n_input: 层的输入特征数
        :param n_neurons: 层的输出特征数
        :param activation: 激活函数 外部指定
        :param weights: 权值 内部生成
        :param bias: 偏置 内部生成
        反向传播算法说明：
        （1）考虑无隐含层的多神经元输出节点OK1,OK2,...,OKk 实际标签对应为t1,t2,..,tk 输出节点的含义为第K层的第k个节点
        损失函数 L = 1/2 Σ(OKi-ti)^2   (i=1,2,..k) 表示 第K输出层的k个节点输出与预测的累计方差
        每层网络单元都由3个小环节组成 ： 上一层的输入self.last_output、本层未激活的输出z=wx+b 、激活输出o=σ(z)
        输出层为最后一层时，可以忽略输出节点OK1,OK2,...,OKk的大标K，简化为O1,O2,...,Ok 损失函数 L = 1/2 Σ(Oi-ti)^2 (i=1,2,..k)
        上一层的输出self.last_output也就是输入层数据X，设输入层有j个节点，输入数据为x1,x2,..,xj，输入层第j个节点到输出层第k个节点的权值为Wjk
            ① 开始计算损失函数L对权值Wjk的偏导数 ： ∂L/∂Wjk = 1/2  *  ∂Σ(Oi-ti)^2 / ∂Wjk
            ② L对Wjk的偏导数转为先对输出Ok的偏导数和Ok对Wjk的偏导数乘积 ： ∂L/∂Wjk = ∂L/∂Ok * ∂Ok/∂Wjk
            ③ 输出Ok对Wjk的导数继续转为Ok对Zk的偏导数和Zk对Wjk的偏导数乘积 ：∂Ok/∂Wjk = ∂Ok/∂Zk * ∂Zk/∂Wjk
            ④ 综合①②③可以得到L对输出层权值Wjk的偏导数为 ： ∂L/∂Wjk = ∂L/∂Ok * ∂Ok/∂Zk * ∂Zk/∂Wjk
            ⑤ ∂L/∂Ok = 损失函数的偏导数 = (Ok-tk) 注：Wjk只与Ok有关，与O1,O2,..Ok-1无关可以去掉Σ
            ⑥ ∂Ok/∂Zk = 激活函数的偏导数  以sigmoid(Zk)为例有sig'(Zk) = sig(Zk)*(1-sig(Zk))= Ok(1-Ok)
            ⑦ ∂Zk/∂Wjk = 本层网络输入/上层网络输出 = ∂(xj*Wjk+bj)/∂Wjk = xj  特别的对于无隐含层上层网络输出也就是xj
            ⑧ 结合⑤⑥⑦可以得到L的最终结果为：∂L/∂Wjk = (Ok-tk)Ok(1-Ok)xj  = δk * xj
        （2）多隐含层的情况，考虑输入层N，隐含层I、J，以及输出层K，层输出分别对应Xn、Oi、Oj和Ok
            1） 计算L对倒数第2层也就是J层的权值参数Wij的偏导数 ： ∂L/∂Wij = 1/2  *  ∂Σ(Oi-ti)^2 / ∂Wij
                ① 首先计算L对K层输出Ok的偏导和Ok对Wij的偏导 ： ∂L/∂Wij = Σ∂L/∂Ok * ∂Oi/∂Wij (i=1,2,3,..k)
                ② 计算k层输出Ok对未激活输出Zk的偏导和Zk对Wij的偏导 ： ∂Ok/∂Wij = ∂Ok/∂Zk * ∂Zk/∂Wij (i=1,2,3,..k)
                ③ 计算k层未激活输出Zk对J层输出Oj的偏导 ：∂Zk/∂Wij = ∂Zk/∂Oj * ∂Oj/∂Wij  注：Zk = Oj * Wjk + bj
                ④ 结合①②③可以得到 ∂L/∂Wij = ∂L/∂Ok * ∂Ok/∂Zk * ∂Zk/∂Wij = Σ(Ok-tk)Ok(1-Ok) * ∂Zk/∂Wij
                注 ： 第①步对∂L/∂Wij求导时不能去掉Σ符号，对Wjk求导只与第k个输出Ok有关故可以去掉Σ，但Wij与每个Ok都有关不可以去掉Σ
                ⑤ 计算 ∂Zk/∂Wij = ∂(Oj * Wjk + bj)/∂Wij = Wjk * ∂Oj/∂Wij  注：Wij在输出Oj当中 故Wjk作为常数
                ⑥ 结合④⑤此时得到 ∂L/∂Wij = Σ(Ok-tk)Ok(1-Ok)Wjk * ∂Oj/∂Wij = Σδk * Wjk * ∂Oj/∂Wij
                ⑦ 计算J层输出Oj对未激活输出Zj的偏导和Zj对Wij的偏导 ： ∂Oj/∂Wij = ∂Oj/∂Zj * ∂Zj/∂Wij
                ⑧ 计算J层输出Oj对未激活输出Zj的偏导 ： ∂Oj/∂Zj = σ(Zj) * (1-σ(Zj)) = Oj * (1-Oj)
                ⑨ 计算J层未激活输出Zj对Wij的偏导 ：∂Zj/∂Wij = ∂(Oi * Wij + bi)/∂Wij  = Oi  注：Zj = Oi * Wij + bi
                ⑩ 结合⑥⑦⑧可得 ∂L/∂Wij = [ Σδk * Wjk * (Oj * (1-Oj) ]* Oi = δi * Oi 其中δi = (Oj * (1-Oj) * Σδk * Wjk
            2） 计算L对倒数第3层也就是I层的权值参数Wni的偏导数 ： ∂L/∂Wni= 1/2  *  ∂Σ(Oi-ti)^2 / ∂Wni
                ① 从（1）和（2）的1）可以看出损失函数对权值参数的偏导具有规律
                   ∂L/∂Wjk = (Ok-tk)Ok(1-Ok) * Oj  = δk * Oj
                   ∂L/∂Wij = Oj(1-Oj)ΣδkWjk * Oi = δj * Oi
                   可以得到相似的规律
                   ∂L/∂Wni = Oi(1-Oi)ΣδjWij * On = δi * On
                   ...
                   由此只要依次反向计算当前层的δ参数和上层的输出O即可计算损失函数对当前层的权值变化率
                ② 使用self.last_output指代输出O,不同层对应的依次为Ok、Oj、Oi、On...
                ③ 当为输出层时：使用self.error指代δk的一部分，即误差函数的导数(Ok-tk)
                   layer.error = y - output
                   否则其他层时：指代Σδk*Wjk、Σδj*Wij ...
                   layer.error = np.dot(next_layer.weights, next_layer.delta)
                ④ 使用self.apply_activation_derivative(layer.last_output)指代Ok(1-Ok)、Oj(1-Oj)、Oi(1-Oi)...(sogmoid函数,其他函数具有其他形式)
                ⑤ 使用self.delta指代δ,不同层对应的依次为δk、δj、δi...
                   layer.delta = layer.error * layer.apply_activation_derivative(output)  or
                   layer.delta = layer.error * layer.apply_activation_derivative(layer.last_output)

        '''
        # 正态分布初始化网络权值 shape = din * dout np.random.randn=正态分布
        self.weights = weights if weights is not None else np.random.randn(n_input, n_neurons)
        # shape = (dout,) np.random.rand=均匀分布
        self.bias = bias if bias is not None else np.random.rand(n_neurons)
        self.activation = activation  # 激活函数类型，如sigmoid
        self.last_output = None  # 激活函数的上一层网络输出值 o
        self.error = None  # 用于计算当前层的 delta 变量的中间变量
        self.delta = None  # 记录当前层的 delta 变量，用于计算梯度
    def activate(self, x):
        # 前向传播
        z = np.dot(x, self.weights) + self.bias  # (b,n) --> z=x@w+b = (b,n)*(n,i)+ (i,)-->(b,i)*(i,j)+(j,)-->(b,j)*(j,k)+(k,)-->(b,k)
        # 通过激活函数，得到全连接层的输出 o 并将输出赋予self.last_output 用于反向传播的计算
        self.last_output = self._apply_activation(z) # 应用激活函数
        return self.last_output
    def _apply_activation(self, z):
        # 计算激活函数的输出
        if self.activation is None:
            return z  # 无激活函数，直接返回
        # ReLU 激活函数
        elif self.activation == 'relu':
            return np.maximum(z, 0)
        # tanh
        elif self.activation == 'tanh':
            return np.tanh(z)
        # sigmoid
        elif self.activation == 'sigmoid':
            return 1 / (1 + np.exp(-z))
        elif self.activation == 'softmax':
            def softmax():
                if z.ndim == 2:
                    c = np.max(z, axis=1)
                    exp_x = np.exp(z.T - c)
                    return (exp_x / np.sum(exp_x, axis=0)).T
                c = np.max(z)
                exp_z = np.exp(z - c)
                return exp_z / np.sum(exp_z)
            return softmax()
        return z
    def apply_activation_derivative(self, z):
        # 计算激活函数的导数
        # 无激活函数，导数为 1
        if self.activation is None:
            return np.ones_like(z) # 返回一个用0、1填充的跟输入数组形状和类型一样的数组
        # ReLU 函数的导数实现
        elif self.activation == 'relu':
            grad = np.array(z, copy=True)
            grad[z > 0] = 1.
            grad[z <= 0] = 0.
            return grad
        # tanh 函数的导数实现
        elif self.activation == 'tanh':
            return 1 - z ** 2 # tanh'(x) = 1-tanh^2(x)
        # Sigmoid 函数的导数实现
        elif self.activation == 'sigmoid':
            return z * (1 - z) # sigmoid'(x)=sigmoid(x)(1-sigmoid(x))
        return z
class MyNeuralNetwork:
    # 定义网络
    def __init__(self,learning_rate=0.01,epochs=100):
        self._layers = []  # 网络层对象列表
        self.learning_rate = learning_rate
        self.epochs = epochs
        self.history = {'acu':[],'mse':[]}
    def add_layer(self, layer):
        # 追加网络层
        self._layers.append(layer)
    def fit(self,X_train, y_train):
        self.X = X_train
        self.y = y_train
    def forward(self, X):
        # 前向传播
        for layer in self._layers:
        # 依次通过各个网络层
            X = layer.activate(X)
        return X
    def backward(self, X, y):
        output = self.forward(X) # (1,2)
        # 反向计算每层的𝛿变量
        for i in reversed(range(len(self._layers))):  # 反向循环 len(self._layers)=0,1,2,3-->3,2,1,0=-1,-2,-3,-4
            layer = self._layers[i]  # 得到当前层对象
            # 如果是输出层 i = 3
            if layer == self._layers[-1]:  # 对于输出层
                layer.error = y - output  # 计算 2 分类任务的均方差的导数
                # 关键步骤：计算输出层的 delta，参考输出层的梯度公式 ∂L/∂Wjk = (Ok-tk) * Ok(1-Ok) * Oj  = δk * Oj
                # 其中layer.error=(Ok-tk) layer.apply_activation_derivative(output)=Ok(1-Ok)
                layer.delta = layer.error * layer.apply_activation_derivative(output)
            else:
                # i = 2、1、0
                # i = 2 此时next_layer为输出层 next_layer.delta=(Ok-tk) * Ok(1-Ok) 在i=3时已经传入可以使用
                # 计算layer.error=ΣδkWjk layer.delta=Oj(1-Oj)ΣδkWjk
                # i = 1 此时next_layer为倒数2层 此时也已传入 同理计算得到layer.delta=Oi(1-Oi)ΣδjWij
                # i = 0 layer.delta=On(1-On)ΣδiWni
                next_layer = self._layers[i + 1]  # 得到下一层对象
                # 关键步骤：计算隐藏层的 delta，参考隐藏层的梯度公式 ∂L/∂Wij = Oj(1-Oj) * ΣδkWjk * Oi = δj * Oi
                # 其中layer.error=ΣδkWjk  layer.apply_activation_derivative(layer.last_output)=Oj(1-Oj)

                layer.error = np.dot(next_layer.weights, next_layer.delta)
                layer.delta = layer.error * layer.apply_activation_derivative(layer.last_output)
        # 循环更新权值
        for i in range(len(self._layers)):
            # layer.weights.shape = n_input * n_neurons + (n_input ,) delta是标量
            # i = 0 输入形状(2,) wni=(2,25)  可以实现(2,25)+= (2,25) + (2,)
            # i = 1 输入形状(25,) wij=(25,50) 可以实现(25,50)+= (25,50) +(25,)
            # i = 2 输入形状(50,) wjk=(50,25) 可以实现(50,25)+= (50,25) +(50,)
            # i = 3 输入形状(25,) wko=(25,2) 可以实现(25,2)+= (25,2) +(25,)
            layer = self._layers[i]
            # np.atleast_2d 表示将输入数组转换为至少2维的数组
            last_output = np.atleast_2d(X if i == 0 else self._layers[i - 1].last_output)
            # 梯度下降算法，delta 是公式中的负数，故这里用加号
            layer.weights += layer.delta * last_output.T * self.learning_rate
        return output
    def train(self):
        # 网络训练函数
        # one-hot 编码
        self.y_onehot = np.zeros((self.y.shape[0], 2)) # 存放[0,1]或者[1,0] 1600*2
        self.y_onehot[np.arange(self.y.shape[0]), self.y] = 1 # 利用坐标进行赋值
        for i in range(self.epochs):  # 训练 1000 个 epoch
            self.epoch_output = []
            for j in range(len(self.X)):  # 一次训练一个样本
                output = self.backward(self.X[j], self.y_onehot[j])
                # print("result= %s"%(self.result(output,self.y_onehot[j])))
                self.epoch_output.append(np.argmax(output))
            # 打印出 MSE Loss
            score = self.score()
            mse = self.loss() # 每个周期整体验证
            print('epoch: %s, mse = %.5f acu = %.5f' % (i+1, float(mse),float(score)))
            self.history['mse'].append(mse)
            self.history['acu'].append(score)
    def loss(self):
        return np.mean(np.square(self.y_onehot - self.forward(self.X)))
    def score(self):
        return np.sum(self.epoch_output == self.y)/len(y)
    def predict_proba(self,X_test):
        return self.forward(X_test)
    def predict_label(self,X_test):
        return np.argmax(self.predict_proba(X_test))
    def result(self,y_pred,y_true):
        y_pred = np.argmax(y_pred)
        y_true = np.argmax(y_true)
        return 'yes' if y_pred == y_true else 'no'
nn = MyNeuralNetwork(learning_rate=0.005,epochs=1000) # 实例化网络类
nn.add_layer(MyLayer(2, 10, 'relu')) # 隐藏层 1, 2 * 25
# nn.add_layer(MyLayer(5, 10, 'relu')) # 隐藏层 2, 25 * 50
# nn.add_layer(MyLayer(50, 25, 'relu')) # 隐藏层 3, 50 * 25
nn.add_layer(MyLayer(10, 2, 'softmax')) # 输出层 4, 25 * 2
nn.fit(X_train,y_train)
nn.train()





