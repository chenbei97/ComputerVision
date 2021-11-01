# %%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 5.不使用层手动实现神经网络（3层）.py
@Author : chenbei
@Date : 2021/10/12 15:39
'''
from matplotlib.pylab import mpl
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.datasets import load_digits, load_boston, load_iris, make_moons
from sklearn.model_selection import train_test_split, KFold, cross_val_score, cross_validate
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import confusion_matrix, accuracy_score, classification_report
from sklearn.svm import SVC
from sklearn.naive_bayes import GaussianNB
import seaborn as sns
from collections import defaultdict
import os
import operator
from tensorflow.keras.datasets import mnist
from tensorflow.keras.datasets import mnist
import tensorflow as tf
from tensorflow.keras.utils import to_categorical, plot_model
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Conv2D, Dense, Flatten, MaxPooling2D
from tensorflow.keras.callbacks import TensorBoard
import time
import torch
import torchvision
import hiddenlayer

plt.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
plt.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
plt.rcParams['savefig.dpi'] = 600  # 图片像素
# np.set_printoptions(precision=16)
# plt.rcParams['figure.dpi'] = 600  # 分辨率
root = os.path.join(os.getcwd(), "ImageProcessing")
img_dir = os.path.join(root, "images")
(train_x, train_y), (test_x, test_y) = mnist.load_data()
print(train_x.shape, train_y.shape, train_x.dtype, type(train_x))
def process(x, y=None):
    x = x.reshape((x.shape[0], x.shape[1], x.shape[2], 1))  # np.squeeze() 移除维度 没有unsqueeze
    x = x.astype(np.float32) / 255
    y = to_categorical(y)
    return x, y
train_x, train_y = process(train_x, train_y)
test_x, test_y = process(test_x, test_y)
# %% （1）手动实现三层网络
X_train, X_test = train_x.reshape((train_x.shape[0], -1)), test_x.reshape((test_x.shape[0], -1))
class MyNet():
    def __init__(self, input_shape, neuron_nums=None, h=1e-4, epochs=5, lr=0.2, batch_size=128,weight_scale=1.0):
        self.params = {}
        if neuron_nums is None:
            neuron_nums = [50, 100, 10]
        self.input_shape = input_shape
        self.neuron_nums = neuron_nums
        self.eps = 1e-7  # 数值稳定用,log中
        self.h = h  # 数值差分的最小delta
        self.epochs = epochs
        self.lr = lr
        self.batch_size = batch_size
        self.weight_scale = weight_scale
        self.history = {'acu':{},'loss':{}}
        assert len(input_shape) == 2
    def init_net(self):
        n1, n2, n3 = self.neuron_nums
        w1 = np.random.randn(self.input_shape[1], n1) * self.weight_scale
        b1 = np.ones(n1)
        w2 = np.random.randn(n1, n2) * self.weight_scale
        b2 = np.ones(n2)
        w3 = np.random.randn(n2, n3) * self.weight_scale
        b3 = np.ones(n3)
        keys = ["w1", "w2", "w3", "b1", "b2", "b3"]
        params = [w1, w2, w3, b1, b2, b3]
        for key, param in zip(keys, params):
            self.params[key] = param
    def fit(self, X_train, y_train):
        self.X = X_train
        self.y = y_train
        self.init_net()
        print("initialize net sucessful..")
        print("gradient_descent starting..")
        self.gradient_descent()
        print("gradient_descent finished..")
    def gradient_descent(self):
        index_list = np.arange(self.X.shape[0])
        np.random.shuffle(index_list)
        if self.X.shape[0] % self.batch_size == 0:
            self.iterations = self.X.shape[0] // self.batch_size
        else:
            self.iterations = self.X.shape[0] // self.batch_size + 1
        for epoch in range(self.epochs):
            self.history['acu'][epoch + 1] = []
            self.history['loss'][epoch + 1] = []
            for iter in range(self.iterations):
                if iter != self.iterations - 1:
                    X_batch = self.X[iter * self.batch_size:iter * self.batch_size + self.batch_size]
                    y_batch = self.y[iter * self.batch_size:iter * self.batch_size + self.batch_size]
                else:
                    # 处理边界 最后1步为了不越界使用
                    X_batch = self.X[iter * self.batch_size:]
                    y_batch = self.y[iter * self.batch_size:]
                #print(epoch + 1, iter + 1, X_batch.shape, y_batch.shape)
                train_batch_acu = self.train_batch_score(X_batch, y_batch)
                train_batch_loss = self.train_batch_loss(X_batch, y_batch)
                grads = self.backward(X_batch,y_batch) # 数值微分
                # grads = self.layer_params_gradient(X_batch, y_batch)  # 数值梯度
                for key in self.params.keys():  # 执行梯度下降
                    #print("[%s] = [%s] - lr * grads[%s] starting.." % (key, key, key))
                    #if grads[key].ndim == 2:
                        #print("[%s]_grad_0_0=[%.5f]" % (key, grads[key][0, 0]))
                    #else:
                        #print("[%s]_grad_0_0=[%.5f]" % (key, grads[key][0]))
                    self.params[key] -= self.lr * grads[key]
                    #print("[%s] = [%s] - lr * grads[%s] finished.." % (key, key, key))
                self.history['acu'][epoch + 1].append(train_batch_acu)
                self.history['loss'][epoch + 1].append(train_batch_loss)
                print("epoch：%s iter：%s train_acu=%.5f train_loss=%.5f" % (
                epoch + 1, iter + 1, train_batch_acu, train_batch_loss))
    def forward(self, X):
        self.layer1 = X.dot(self.params["w1"]) + self.params["b1"] # (N,784)*(784,50)+(50,)
        self.z1 = self.relu(self.layer1) # (N,50)
        self.layer2 = self.z1.dot(self.params["w2"]) + self.params["b2"]# (N,50)*(50,100)+(100,)
        self.z2 = self.relu(self.layer2) #(N,100)
        self.out = self.z2.dot(self.params["w3"]) + self.params["b3"] # (N,100)*(100,10)+(10,)
        # 输出10个节点，说明每个样本输出10个值，也就是要求标签为独热编码
        self.out_proba = self.softmax(self.out) # (N,10)
        return self.out_proba
    def backward(self,X,y):
        '''
        :param X: 当前批次
        :param y: 当前批次
        :return:  当前批次损失对w1,w2,w3,b1,b2,b3的梯度
        （1）初始化类成为对象后，调用fit函数
             fit函数先执行init_net函数初始化网络生成6个参数，其次执行gradient_descent函数执行梯度下降
        （2）gradient_descent函数设定epoch和iter双循环，执行前向传播和反向传播，计算梯度并更新参数
        （3）执行backward反向传播之前先执行前向传播forward
             gradient_descent函数中调用train_batch_score
             train_batch_score函数中调用forward
             forward中就依次计算了不同层的输出作为类属性self.layer1,self.layer2,self.out,self.z1,self.z2,self.out_proba
        （4）backward函数从输出层开始依次执行节点函数的反向梯度计算直到输入层
             1）loss<-out_proba、out_proba(softmax)<-out
                一般直接合并计算即可，即直接计算loss对out的梯度，记out_proba=p,out=z,y_batch=y
                首先：loss = -y1*log(p1)-y2*log(p2)-y3*log(p3)
                其次：pi = exp(zi)/[exp(z1)+exp(z2)+exp(z3)] i = 1,2,3
                loss对zi的偏导=loss对pi的偏导 * pi对zi的偏导
                根据数学计算可得结论为 ∂loss/∂zi = pi - yi，即dloss_dout，作为下层的上游梯度
             2）out<-w3@z2+b3
                全连接层涉及矩阵的求导运算 ：
                    当 Y = W @ X + b时 dY/dX=W'
                    当 Y = X @ W + b 时 dY/dX=W' dY/dW=X'@上游梯度 dY/db=上游梯度在轴0的求和
                故 dout_dz2 = w3'
                   dloss_dw3 = z2.T @ dloss_dout
                   dloss_db3 = np.sum(dloss_dout,axis=0)
                此时dloss_dz2 = dloss_dout @ dout_dz2 作为下层的上游梯度
             3）z2<-relu(layer2)
                前向传送时layer2小于等于0的数全置为0，故反向传播也是只需要对上游梯度置零即可
                此时 dloss_dlayer2 = dloss_dz2[self.layer2 <= 0] = 0 作为下层的上游梯度
            4）layer2<-w2@z1+b2
               和步骤2）类似，区别在于当前的上游梯度是dloss_dlayer2，数值导数为z1.T
               dlayer2_dz1 = w2'
               dloss_dw2 = z1.T @ dloss_dlayer2
               dloss_db2 = np.sum(dloss_dlayer2,axis=0)
               此时dloss_dz1 = dloss_dlayer2 @ dlayer2_dz1 作为下层的上游梯度
            5） z1<-relu(layer1)
               和步骤3）类似
               此时 dloss_dlayer1 = dloss_dz1[self.layer1 <= 0] = 0 作为下层的上游梯度
            6）layer1<-w1@X+b1
               和步骤2）类似，区别在于当前的上游梯度是dloss_dlayer1，数值导数为X.T
               dlayer1_dz1 = w1'
               dloss_dw1 = X.T @ dloss_dlayer1
               dloss_db1 = np.sum(dloss_dlayer1,axis=0)
               此时dloss_dX = dloss_dlayer1 @ dlayer1_dX 作为最终梯度
        （5）backward运行结束后，此时参数达到最佳，结束程序，dloss_dX没有什么用
        '''
        grads = {}
        # softmax层的反向传播 ：节点左侧是self.out(Z)，节点右侧是self.out_proba(P) <- loss_W，跳过了对P求导，直接对Z求导
        # loss = -y1*log(p1)-y2*log(p2)-y3*log(p3)
        # p1 = exp(z1)/[exp(z1)+exp(z2)+exp(z3)],p2 = exp(z2)/[exp(z1)+exp(z2)+exp(z3)],p3 = exp(z3)/[exp(z1)+exp(z2)+exp(z3)]
        # loss对z1的导数也就是loss_W对self.out_proba的10个节点的导数
        # 每个节点都可以写为loss对p1导数和p1对z1的导数的乘积，为p1(y1+y2+y3)-y1,p2(y1+y2+y3)-y2,p3(y1+y2+y3)-y3
        # 因为y1+y2+y3=E（矩阵形式），所以所有节点可以统一成 p-y，这里y对应self.y
        self.dloss_dout = (self.out_proba - y) / self.y.shape[0] # (N,10)

        # 第二层w3、b3的反向传播：节点两侧是self.z2和self.out
        # self.out = self.z2 * w3 + b3        (N,10)=(N,100)*(100,10)+(10,)
        # 矩阵求导公式 ：① Y = W * X --> dY/dX = W' ② Y = X' * W --> dY/dX = W
        # 假设 Y = X * W ，同时转置有 Y'= W'*X'，那么根据公式①dY'/dX' = W，同时转置dY/dX = W'
        self.dout_dz2 = self.params['w3'].T  # (10,100) 当前层对X求偏导为参数W的转置
        self.dloss_dw3 = np.dot(self.z2.T,self.dloss_dout)  # 对当前层参数W求偏导为X的转置，区别还需要乘上游导数值
        self.dloss_db3 = np.sum(self.dloss_dout,axis=0) # 偏置量求和即可
        dloss_dz2 = self.dloss_dout.dot(self.dout_dz2)

        # 第二层激活层relu的反向传播：节点两侧是self.layer2和self.z2
        dloss_dz2[self.layer2 <= 0] = 0
        dloss_dlayer2 = dloss_dz2

        # 类似的
        self.dlayer2_dz1 = self.params['w2'].T
        self.dloss_dw2 = np.dot(self.z1.T,dloss_dlayer2)
        self.dloss_db2 = np.sum(dloss_dlayer2, axis=0)
        dloss_dz1 = dloss_dlayer2.dot(self.dlayer2_dz1)

        dloss_dz1[self.layer1<=0] = 0
        dloss_dlayer1 = dloss_dz1

        self.dlayer1_dX = self.params['w1'].T
        self.dloss_dw1 = np.dot(X.T,dloss_dlayer1)
        self.dloss_db1 = np.sum(dloss_dlayer1, axis=0)

        self.dloss_dX = dloss_dlayer1.dot(self.dlayer1_dX)
        # print(self.dloss_dw3.shape,self.dloss_dw2.shape,self.dloss_dw1.shape)
        # print(self.dloss_db3.shape,self.dloss_db2.shape,self.dloss_db1.shape)
        # (100, 10) (50, 100) (784, 50)
        # (10,)(100, )(50, )
        grads['w3'] = self.dloss_dw3
        grads['w2'] = self.dloss_dw2
        grads['w1'] = self.dloss_dw1
        grads['b3'] = self.dloss_db3
        grads['b2'] = self.dloss_db2
        grads['b1'] = self.dloss_db1
        return grads
    def train_score(self):
        y_pred = self.forward(self.X)
        y_pred = np.argmax(y_pred, axis=1)
        y_true = np.argmax(self.y, axis=1)
        return np.sum(y_true == y_pred) / len(y_true)
    def train_batch_score(self, X_batch, y_batch):
        y_pred = self.forward(X_batch)
        y_pred = np.argmax(y_pred, axis=1)
        y_true = np.argmax(y_batch, axis=1)
        return np.sum(y_true == y_pred) / len(y_true)
    def train_loss(self):
        # print(self.out_proba.shape) # (60000, 10)
        # 直接计算所有样本的前向损失：对应元素相乘求和取平均
        y_pred = self.forward(self.X)
        return self.cross_entropy_error(y_pred=y_pred, y_true=self.y)
    def train_batch_loss(self, X_batch, y_batch):
        y_pred = self.forward(X_batch)
        return self.cross_entropy_error(y_pred=y_pred, y_true=y_batch)
    def layer_param_gradient(self,key,X_batch,y_batch):
        grad = np.zeros_like(self.params[key])
        index_genegrator = np.nditer(self.params[key], flags=['multi_index'], op_flags=['readwrite'])
        while not index_genegrator.finished:
            index = index_genegrator.multi_index  # 每个参数的所有元素索引
            # 如对W1的W11参数更新，类似的W1的其他参数也是如此
            # 计算W11的差分时其他参数不动，[ f(W11+h,W12,W13...Wnn)-f(W11-h,W12,W12,..,Wnn) ] / 2h
            # print("w1没前向：", self.params['w1'][0][0],index)
            temp = self.params[key][index]
            self.params[key][index] = float(temp) + self.h  # 前向更新
            loss_forward = self.train_batch_loss(X_batch,y_batch)
            self.params[key][index] = float(temp) - self.h  # 反向更新
            loss_backward = self.train_batch_loss(X_batch,y_batch)
            grad[index] = (loss_forward - loss_backward) / 2 * self.h
            self.params[key][index] = temp # 还原实际值
            # print(f"{key} temp=[{temp}] grad={grad[index]} gradient finished...")
            index_genegrator.iternext()
        return grad
    def layer_params_gradient(self, X_batch, y_batch):
        grads ={}
        print("layer_params_gradient starting...")
        # 数值梯度
        for key in self.params.keys():
            print(f"{key} layer_param_gradient starting...")
            grads[key] = self.layer_param_gradient(key,X_batch,y_batch)
            print(f"{key} layer_param_gradient finished...grads[w1][0][0]={grads['w1'][0][0]}")
        print("params_gradient finished...")
        return grads
    def predict(self, X_test):
        # 预测时使用的是此时最好的参数
        layer1 = X_test.dot(self.params["w1"]) + self.params["b1"]
        z1 = self.relu(layer1)
        layer2 = z1.dot(self.params["w2"]) + self.params["b2"]
        z2 = self.relu(layer2)
        out = z2.dot(self.params["w3"]) + self.params["b3"]
        y_pred = self.softmax(out)
        return y_pred
    def cross_entropy_error(self, y_pred, y_true):
        return -np.sum(y_true * np.log(y_pred + self.eps)) / y_pred.shape[0]
    def softmax(self, x):
        if x.ndim == 2:
            # 传入的是矩阵时 如(4,6)必须修改，否则矩阵的所有元素和为1了
            # 注：对于sigmoid和relu函数没有影响
            # 现在要求x的每列和为1，故找到每列的最大值
            c = np.max(x, axis=1)  # (4,)
            exp_x = np.exp(x.T - c)  # (4,6)-(4,)是不能广播的，需要转置为(6,4)-(4,)-->(6,4),需要后缘维度相同
            return (exp_x / np.sum(exp_x, axis=0)).T  # np.sum(exp_x,axis=0) =(4,) 每列除对应值
        c = np.max(x)
        exp_x = np.exp(x - c)
        return exp_x / np.sum(exp_x)
    def relu(self, x):
        # return np.array(list(map(lambda a: 0 if a < 0 else a, x))) 只适合向量
        return np.maximum(0, x)
mynet = MyNet(input_shape=X_train.shape, neuron_nums=[512,128,10],epochs=10)
mynet.fit(X_train, train_y)
epoch_loss = [np.mean(epoch_iter_loss) for epoch_iter_loss in mynet.history['loss'].values() ]
epoch_acu = [np.mean(epoch_iter_acu) for epoch_iter_acu in mynet.history['acu'].values() ]
fig , ax = plt.subplots()
axx = ax.twinx()
ax.plot(epoch_loss,label='loss',color='b')
axx.plot(epoch_acu,label='acu',color='r')
ax.legend()
axx.legend()
fig.show()
print(mynet.train_score(), mynet.train_loss())
print(np.sum((np.argmax(mynet.predict(X_test),axis=1)==np.argmax(test_y,axis=1)))/len(test_y))
# %% （2）使用tensorfow实现
cnn = Sequential()
cnn.add(Conv2D(filters=64, kernel_size=(3, 3), activation='relu', input_shape=(28, 28, 1)))
cnn.add(MaxPooling2D(pool_size=(2, 2)))
cnn.add(Flatten())
cnn.add(Dense(units=128, activation='relu'))
cnn.add(Dense(units=10, activation='softmax'))
cnn.summary()
# 卷积：28-3++1 =26 总数为 64*9+64 偏置64个，核64个，每个有9个参数
# 池化：26//2=13 参数=0
# 展平：0
# 全连接 ： 输入=13*13*64=10186 输出 128 总：10186*128+128=1384576
# 输出：128*10+10=1290

# plot_model(cnn,to_file='cnn_mnist_helloWorld.png',show_shapes=True,show_layer_names=True)

callbacks = TensorBoard(log_dir="logs/mnist", histogram_freq=1, write_graph=True)
cnn.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])
# cd C:\Users\chenb\jupyterLab   tensorboard --logdir="logs/mnist"  http://localhost:6006/
history = cnn.fit(train_x, train_y, epochs=5, batch_size=64, validation_split=0.1, callbacks=[callbacks])
# https://keras.io/zh/losses/
test_pred = cnn.predict(test_x)
test_pred_label = tf.argmax(test_pred, axis=1).numpy()
test_true_label = tf.argmax(test_y, axis=1).numpy()
acu = sum(test_pred_label == test_true_label) / len(test_true_label)
print(acu)
# %% （3）使用pytorch实现
# 参考  Pytorch深度学习入门与实战\一个提升的例子（图像分类）.py
