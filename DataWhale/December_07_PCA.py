#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : December_07_PCA.py
@Author : chenbei
@Date : 2021-12-21 9:14
@Email ：chenbei_electric@163.com
@Address : Beijing Jiaotong University
'''
from matplotlib.pylab import mpl
mpl.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
mpl.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
mpl.rcParams['savefig.dpi'] = 600  # 图片像素
mpl.rcParams['figure.dpi'] = 600  # 分辨率
import matplotlib.pyplot as plt
import numpy as np
# 1.准备数据
import tensorflow as tf
from tensorflow.keras.datasets import fashion_mnist
(x_train, y_train), (x_test, y_test) = fashion_mnist.load_data()
def process(X,y=None):
    X = X.reshape(-1,X.shape[1]*X.shape[2])
    X = tf.convert_to_tensor(X,dtype=tf.float32)/255.
    if y is not None :
        y = tf.one_hot(y,dtype=tf.int64,depth=10)
        # 10分类独热编码(对应后续的非稀疏类型交叉熵损失函数CategoricalCrossentropy而非SparseCategoricalCrossentropy)
        return X,y
    return X
X_train,y_train = process(x_train,y_train)# (60000,784),(60000,10)
X_test,y_test = process(x_test,y_test) # (10000,784),(10000,10)

# 2.比较降维后恢复的图片与原始图片 fit_transform->inverse_transform
from sklearn.decomposition import PCA
pca = PCA(n_components=180)
X_train_pca = pca.fit_transform(X_train.numpy())
X_train_pca_inverse =pca.inverse_transform(X_train_pca).reshape(-1,x_train.shape[1],x_train.shape[2])
X_test_pca = pca.fit_transform(X_test.numpy())
plt.figure(dpi=600,figsize=(8,4))
fig,axes = plt.subplots(2,5,sharex="row")
axes = axes.flatten()
for idx,axe in enumerate(axes) :
    pack_params = dict(cmap=plt.cm.Greys,norm=None,aspect=None,interpolation='nearest',clim=(0,1.))
    axe.set_xticks([])
    axe.set_yticks([])
    if idx < 5 :
        axe.imshow(x_train[idx,:],**pack_params)
        axe.set_xlabel(f"n_components = {X_train.shape[1]}")
    else:
        axe.imshow(X_train_pca_inverse[idx-5, :], **pack_params)
        axe.set_xlabel(f"n_components = {pca.n_components_}")
plt.show()

# 3.搭建前向网络
n_classes = 10 # 10分类问题
def generate_net(input_shape):
    model = tf.keras.Sequential([tf.keras.layers.Dense(256,activation='relu',name='dense_1'),
                                tf.keras.layers.Dense(128,activation='relu',name='dense_2'),
                                tf.keras.layers.Dense(n_classes,name='output',activation='softmax')])
    model.build(input_shape=input_shape)
    # 参数如何计算？输入(-1,784),首先进入全连接层1,有(784+1)*256=200960,其中偏置参数与输出节点个数有关为256
    # 全连接层1和2之间继续为(256+1)*128=32896个参数
    # 全连接层2与输出层之间为(128+1)*10=1290个参数
    print(model.summary())
    return model
# 4.设置训练参数
epochs = 30 # 训练30代
lr = 0.1 # 学习率0.1
batch_size = 32 # 批样本数
n_samples = X_train.shape[0] # 训练样本数60000

iters = n_samples // batch_size  # 单周期的迭代次数 = 1875
n_iters = epochs * iters # 整个epoch内总的迭代轮询数=10*60000//32=18760
# 引入学习率曲线initial_learning_rate * decay_rate ^ (step / decay_steps)
# step为全局下目前所在的迭代步数,step=0,1,2...n_iters
lr_sch = tf.keras.optimizers.schedules.ExponentialDecay(
            initial_learning_rate=lr, # 初始学习率
            decay_rate=0.98, # 0.1*0.98^(step*iters)
            decay_steps=iters, # 学习率每个周期/iter步下降1次
            staircase = True) # 如果为真step/decay_steps为整数除法,那么学习率曲线类似于阶梯型
opt = tf.keras.optimizers.SGD(lr_sch) # 使用梯度下降法优化
loss_fn = tf.keras.losses.CategoricalCrossentropy(from_logits=False) # 使用交叉熵损失,model定义的尾部已经使用softmax缩放

#观察指数下降曲线
global_steps = np.arange(0,n_iters,iters) # 总的迭代步划分为epochs个区间,自然每个区间的长度是iters
lr_arr = lr_sch(global_steps) # 返回每个epoch对应使用的学习率
plt.figure(figsize = (8,6))
plt.plot(global_steps/n_iters, lr_arr) # 绘制当前进度step/n_iters和学习率的曲线
plt.ylim([0,max(plt.ylim())])
plt.xlabel('speed of progress')
plt.ylabel('learning rate')
plt.show()
# 5.设置训练过程
def train(X_train,y_train,X_test,y_test,batch_size=32,epochs=10,isplot=True,verbose=False):
    X_valid, y_valid = X_test[0:5000], y_test[:5000]  # 分出一半作为验证集
    dataset_train = tf.data.Dataset.from_tensor_slices((X_train, y_train))  # 数据量过大需要分批迭代
    # 准备好数据分批启动器,包括训练和验证,不重复,先打乱再取批次
    dataset_train_batch = dataset_train.shuffle(n_samples).batch(batch_size).prefetch(1)
    global_step = 0 # 全局步数 =0,1,..,1875(1 epoch),....1875*epoch
    global_acu = [] # 全局批准确率
    global_loss = [] # 全局批损失
    epoch_acu = [] # 周期验证准确率
    epoch_loss = [] # 周期验证损失
    from tqdm import tqdm
    for epoch in tqdm(range(epochs)):
        # print(f"The current iteration has reached the {epoch + 1} cycle, please continue to wait...")
        with tf.GradientTape() as tape:
            for step, (batch_x_train, batch_y_train) in enumerate(dataset_train_batch):
                # print(f"Running: step {step + 1} of cycle {epoch + 1}")
                # 1)每个批为(batch_size,784)的shape作为输入,输出为(batch_size,10)
                out_train = model(batch_x_train)
                loss_train = loss_fn(y_pred=out_train,y_true=batch_y_train)
                # 或者直接使用categorical_crossentropy计算也可以,但是需要使用reduce_mean进行批的交叉熵损失平均
                # loss_train = tf.reduce_mean(tf.keras.metrics.categorical_crossentropy(batch_y_train, out_train, from_logits=False)).numpy()
                acu_train = np.sum((tf.argmax(out_train,axis=1) == tf.argmax(batch_y_train,axis=1)).numpy())/batch_size
                if verbose :
                    print(f"epoch = {epoch+1} global_step = {global_step}:  loss=%.5f  acu=%.5f" % (loss_train.numpy(),acu_train))
                global_step += 1
                global_acu.append(acu_train)
                global_loss.append(loss_train.numpy())
            grads = tape.gradient(loss_train, model.trainable_variables)
            grads_and_vars = zip(grads, model.trainable_variables)
            opt.apply_gradients(grads_and_vars=grads_and_vars)
            # 每周期执行1次验证
            out_valid = model(X_valid)
            loss_valid = tf.reduce_mean(tf.keras.metrics.categorical_crossentropy(y_valid, out_valid, from_logits=False)).numpy()
            acu_valid = tf.reduce_mean(tf.keras.metrics.categorical_accuracy(y_valid,out_valid)).numpy()
            epoch_acu.append(acu_valid)
            epoch_loss.append(loss_valid)
            # print("epoch = {:d} valid_loss = {:.5f} valid acu = {:.5f}".format(epoch+1,loss_valid,acu_valid))
    def plot_acu_loss():
        idx_arr = np.arange(0, n_iters, iters)  # 索引数组
        plt.figure(figsize=(7.8, 5))
        plt.subplot(211)
        # plt.plot(np.arange(0,n_iters),global_loss,label="train_loss") # 太密集不画
        # plt.plot(np.arange(0,n_iters),global_acu,label="train_acu")
        plt.plot(np.arange(0,n_iters,iters), np.array(global_loss)[idx_arr], "r-o", label="train_loss")  # 索引数组切片不能是列表
        plt.plot(np.arange(0,n_iters,iters), epoch_loss, "b-o", label="valid_loss")
        plt.xlabel(f"global_step")
        plt.ylabel("loss")
        plt.title(f"loss and acu curve")
        plt.legend()
        plt.subplot(212)
        plt.plot(np.arange(1, epochs + 1), np.array(global_acu)[idx_arr], "r-*", label="train_acu")
        plt.plot(np.arange(1, epochs + 1), epoch_acu, "b-*", label="valid_acu")
        plt.xlabel(f"epoch")
        plt.ylabel("acu")
        plt.xticks(np.arange(1, epochs + 1, 1))
        plt.title(f"per epoch = {iters} steps")
        plt.legend()
        plt.show()
    if isplot :
        plot_acu_loss()
# 6.可视化训练/验证过程
model = generate_net(X_train.shape)
train(X_train,y_train,X_test,y_test,batch_size,epochs,True,True) # 打印日志
# 总体来看验证和训练的损失/准确率是交替上升的不够稳定
# 7.比较降维前后预测的结果
# 降维后的数据X_train_pca和X_test_pca在2.小节已经准备好,只需要先转换为TF张量,y_train,y_test无需改变
X_train_pca = tf.convert_to_tensor(X_train_pca,dtype=tf.float32)
X_test_pca = tf.convert_to_tensor(X_test_pca,dtype=tf.float32)
model = generate_net(input_shape=X_train_pca.shape) # 网络输入shape更改要重新编译
train(X_train_pca,y_train,X_test_pca,y_test,batch_size,epochs,True,False) # 不打印日志
# 主成分降维之后可以验证损失一直高于训练损失,准确率也几乎一直低于训练准确率,看起来降维反而导致效果变差
# 这提示我们降维可能丢失大量信息导致效果变差



