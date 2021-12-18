#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : December_05_KNN.py
@Author : chenbei
@Date : 2021-12-16 8:11
@Email ：chenbei_electric@163.com
'''
from matplotlib.pylab import mpl
import matplotlib.pyplot as plt

import pandas as pd
import os
from sklearn.datasets import load_digits, load_boston, load_iris, make_moons
from sklearn.model_selection import train_test_split, KFold, cross_val_score, cross_validate
from sklearn.neighbors import KNeighborsClassifier

from sklearn.metrics import confusion_matrix, accuracy_score, classification_report
mpl.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
mpl.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
mpl.rcParams['savefig.dpi'] = 600  # 图片像素
mpl.rcParams['figure.dpi'] = 600  # 分辨率
#%%
# <1>顺序实现KNN：使用割裂的小函数依次实现功能，<2>中把这些小函数合并成类,<3>使用sklearn定义的方法进行比较
# (1)数据集准备：使用mnist数据集,对其维度调整且标准化(均匀标准化或者正态标准化)
import numpy as np
from tensorflow.keras.datasets import mnist
(train_x,train_y),(test_x,test_y)=mnist.load_data() # (10000,28,28),(10000,)
def minmaxium(X,norm_range):
    # 不涉及距离度量、协方差计算、数据不符合正太分布的时候，可以使用本方法
    # 例如图片处理可以归一化到0-255或0-1
    assert X.ndim == 1 or X.ndim == 2
    if X.ndim == 1 :
        # 归一化到(a,b)的公式为y=(x-min)/(max-min)+a,x=min=>a,x=max=>b b=norm_range[1],a=norm_range[0]
        minval, maxval = np.min(X), np.max(X)
        X = np.array([(x-minval)*(norm_range[1]-norm_range[0])/(maxval-minval)+norm_range[0] for x in X])
    else: # X.ndim=2
        # 样本的特征之间可能差距较大所以是每个样本的特征之间归一化
        # 1)使用循环：效率很低
        """
        for i in range(X.shape[0]): # 每个样本循环,对行向量归一化
            minval, maxval = np.min(X[i,:]),np.max(X[i,:])
            X[i,:] = np.array([(x-minval)*(norm_range[1]-norm_range[0])/(maxval-minval)+norm_range[0] for x in X[i,:]])
        """
        # 2)使用广播：效率较高
        """
        测试程序：
        (train_x,train_y),(test_x,test_y)=mnist.load_data()
        a = train_x.reshape(-1,784)
        min_a,max_a= np.min(a,axis=-1),np.max(a,axis=-1)
        min_max_a = max_a - min_a
        b = (a - min_a.reshape(-1,1))/min_max_a.reshape(-1,1)*2 -1
        ! 特别要注意，单独乘一个数2(推广为b-a)要放在后边乘才有广播效应
        (X_train == train_x.reshape(-1,784)).all()
        如果b=255,a=0，实际上 X_train == train_x.reshape(-1,784)，返回False是个别数有除数误差取整即可
        """
        minval ,max_val = np.min(X,axis=-1),np.max(X,axis=-1) # 注意axis=-1表示最后1个维度,也就是Y维度,在numpy中Y维度是行方向(样本方向)
        X = (X-minval.reshape(-1,1))/(max_val.reshape(-1,1)-minval.reshape(-1,1))*(norm_range[1]-norm_range[0])+norm_range[0]# 广播效应之前必须形状相同,按行广播先使用reshape改变minval,maxval为单列
    return X
def meanstdium(X):
    # 需要使用距离来度量相似性的分类、聚类算法或使用PCA进行降维时适用于本方法
    # # 标准差=方差的算术平方根 std * std = var
    assert X.ndim == 1 or X.ndim == 2
    if X.ndim == 1 :
        return (X-np.mean(X))/np.std(X)
    else:
        # 利用广播效应参考minmaxium的实现
        mean, std = np.mean(X,axis=1), np.std(X,axis=1)
        return (X-mean.reshape(-1,1)) / std.reshape(-1,1)
def normalize(X,norm_mode,norm_range):
    if norm_mode == "zScore":
        return meanstdium(X)
    else :
        return minmaxium(X,norm_range)
def process(X,y,norm=True,norm_mode=None,norm_range=None):
    """
    :param X: [Array] 输入的数据集对,(X_train,y_train)或者(X_test,y_test),X只能是2维或者3维
    :param y: [Array] 输入的数据集对,(X_train,y_train)或者(X_test,y_test),y必须是向量
    :param norm: bool 是否归一化，默认True
    :param norm_mode: str 归一化模式有min-max标准化和z-score标准化方法,可选"minMax"or"zScore",如果为None默认"minMax"
    :param norm_range: tuple 只在norm_mode="minMax"模式有效,如果为None默认归一化到(0,1),或者指定(-1,1)归一化
    :return: 预处理后的数据
    """
    try :
        assert X.ndim == 2 or X.ndim == 3
        assert y.ndim == 1
    except AssertionError:
        print("X,y must be satisfied 2 ≤ X.ndim ≤ 3 and y.nidm = 1!")

    if norm_mode is None :
        norm_mode = "minMax"
    if not isinstance(norm_mode,str):
        raise TypeError("norm_mode must be string or None!if None,default 'minMax'")
    if norm_mode not in ["minMax", "zScore"]:
        raise ValueError("'norm_mode' only support 'minMax' or 'zScore'")
    if norm_mode == "minMax":
        if norm_range is None :
            norm_range = (0, 1)
        if not isinstance(norm_range, tuple):
            raise TypeError("norm_range must be tuple like (a,b) or None!if None,default (0,1)")

    if norm_mode == "zScore" and norm_range is not None :
        raise  Warning("when norm_mode is 'zScore',param norm_range is invalid")
    if X.ndim == 3 :
        X = X.reshape(-1,X.shape[1]*X.shape[2])
    if norm :
        X = normalize(X,norm_mode,norm_range)
    return X,y
X_train,y_train = process(train_x,train_y,True,"zScore")
X_test,y_test = process(test_x,test_y,True,"zScore")
#%% (2)计算距离矩阵：计算每一个测试集的样本与所有训练集样本的距离总和,可使用L1或L2距离
train_num = 10000  # 因为一次性训练时间过长,所以选择有限个训练样本去计算
test_num = 1000 # 测试样本同理,原本的train_num=60000,test_num=10000
def calculate_dist(train_x,test_x,dist,return_time):
    if dist not in ["L1","L2"]:
        raise ValueError("dist only support 'L1' or 'L2',default 'L2'!")
    from time import time # 引入时间
    from tqdm import tqdm # 引入进度条
    distances = []
    t1 = time()
    for every_test_sample in tqdm(test_x,colour='green'):
    #for every_test_sample in (test_x):
        """
        默认情况下np.tile(A,2)表示对A在X轴(axis=0 or -1)方向平铺2倍,或者说对A按列堆叠
        a = np.array([[1],[2]]) # (2,1)
        b = np.tile(a,3)
        out: (2,3)的array([[1, 1, 1],
                            [2, 2, 2]])
        b = np.tile(a,(2,3))表示在Y轴方向(axis=1)对a平铺2次，X轴(axis=0 or -1)方向平铺3次
        out: array([[1, 1, 1],
                   [2, 2, 2],
                   [1, 1, 1],
                   [2, 2, 2]])
        注意：reps元素最后1个数才是轴0(X轴列方向)的平铺倍数,与np.mean/np.min/np.max/np.sum等的参数axis=0含义类似
              axis=-1表示最后1个维度,也就是Y维度,在numpy中Y维度是行方向(样本方向),这点在maxminium函数说明过
              因为这里输入的X_train维度已经被处理为2,所以axis=-1和axis=1是相同的
        对当前遍历的测试集样本按Y方向(行)堆叠以后shape就和X_train相同了,此时直接作差就是L1距离,取平方为L2距离
        然后按照样本方向(Y方向=axis=1)对距离进行求和(X轴/列元素求和)得到总距离向量(shape=(X_train.shape[0],)),对于L2再取根方即可
        """
        current_sample = np.tile(A=every_test_sample, reps=(train_x.shape[0], 1)) # X轴方向不堆叠,Y方向(行)堆叠60000次
        assert current_sample.shape == train_x.shape  # 堆叠后的shape必定相同均为(60000,784)
        if dist == "L2":
            distance = np.sqrt(np.sum(np.abs(train_x - current_sample)**2,axis=1))
        else :
            distance = np.sum(np.abs((train_x - current_sample)),axis=1)
        assert distance.shape == (current_sample.shape[0],)
        distances.append(distance) # 10000 * 60000 每行表示1个测试样本到60000个训练样本的距离向量
    t2 = time()
    if return_time :
        return np.array(distances),t2-t1 #  dtype="object"
    else:
        return np.array(distances) # dtype="object"
dists,cost_time = calculate_dist(X_train[:train_num],X_test[:test_num],"L2",True)
print("cost time = ",cost_time," s")
#%% (3)得到距离矩阵以后计算K个最近距离对应的类别数目,然后进行投票
# 对所有测试样本的每个样本所属的类别投票结果进行可视化和置信度分析
# 例如在K=100的情况下,某个样本预测为0类,其中支持0类的投票数为80,支持其它类合计20次
# 下一个样本也预测为0类,但是可能支持0类的投票只有20个,其它类合计80,只是0类的20个比其它的任何一类都要多所以还是预测为0类
# 投票80和投票20都预测为0类的置信度肯定是不同的,所以需要计算所有预测为0类的实际投票数和除总的投票数就是平均置信度
# 所以对所有预测为0类的样本里统计支持0类的实际投票数,再除总的投票数(每次是K=100票,总票数为K*预测为0类的样本数),就可以得到平均置信度
K = 100 # K个最近邻
def vote(dists,train_y,k=100):
    assert dists.shape[1] == len(train_y) # 1个距离向量有60000个距离元素
    from tqdm import tqdm
    y_pred = [[],[]] # 用于存储每个测试集样本预测的真实标签和投票数目(k个最近邻中的支持率)
    for dist in tqdm(dists): # 每个测试样本的距离向量遍历
        """
        argsort函数的作用是首先对序列升序,再遍历每个元素得到原来序列的实际索引位置
        例子：
        np.argsort([3,1,2,4])
        array([1, 2, 0, 3], dtype=int64)
        [3,1,2,4]升序后是[1,2,3,4],开始遍历1的实际位置是1,2的实际位置是2,3的实际位置是0,4的实际位置是3
        所以输出为[1, 2, 0, 3]
        这里的目的是为了得到最近的k个距离在距离向量的实际位置
        """
        nidx = np.argsort(dist,kind="mergesort") # 冒泡排序得到升序后每个距离在原距离向量所处的实际位置
        kidx = nidx[:k] # 前k个距离的实际位置,idx是升序的实际位置
        from collections import defaultdict
        """
        a = dict(a=1, b=2, c=3)
        a["a"] += 1 # 已经存在的键可以作+=
        # a["d"] += 1 # 会报错不存在的键KeyError: 'd'
        # a[0] += 1
        b = defaultdict(int)
        b["a"] += 1 # defaultdict可以在键不存在的时候+=,即根据需要动态添加键并赋值
        使用defaultdict 可以动态添加关键字label,dict必须事先指定关键字,而label又是不可知的,所以不要使用dict
        """
        label_num = defaultdict(int) # 用于统计不同类别的数目,指定value为int类型
        for idx in kidx : # idx是最近的k个图片实际的索引位置,也是标签的位置
            label = y_train[idx] # 用实际的位置得到对应的类别
            label_num[label] += 1 # 动态的把label作为关键字并赋值
        import operator
        # 字典是无序的,先按照value排序然后取出对应的key就是投票后产生的结果,也就是当前X_test[i]的判断类别
        """
        a = {"a":2,"c":3,"e":1}
        # b = sorted(a.items(),reverse=True,key=a.values()) # 想要按照字典的value排序,单数a.values()是不可迭代的会报错
        如果给定item就会自动抓取返回可迭代元组对象
        operator.itemgetter()可以理解为可迭代的(key、value)的操作对 常用于对字典排序
        b = sorted(a.items(),reverse=True,key=operator.itemgetter(0)) # 0表示按照key排序,返回元组对的列表
        c = sorted(a.items(),reverse=True,key=operator.itemgetter(1)) # 1表示按照value排序,返回元组对的列表
        output :
            b = [('e', 1), ('c', 3), ('a', 2)] # 按key排序
            c = [('c', 3), ('a', 2), ('e', 1)] # 按value排序
            c[0][0]表示排序后的第1个item对的key值,c[0][1]为value值
        """
        sorted_label_num = sorted(label_num.items(), reverse=True, key=operator.itemgetter(1))# reverse表示降序
        y_pred[0].append(sorted_label_num[0][0]) # k个最近邻投票预测的类别
        y_pred[1].append(sorted_label_num[0][1]) # k个最近邻中支持该类别的数目(支持率)

    return np.array(y_pred).T
y_pred = vote(dists,y_train[:train_num],k=K)
def plot_vote_result():
    Votes = {} # 10个类别0-9作为key,value是列表,存储每次支持该类别的所有票数
    for key in [x for x in range(10)]:
        Votes.update({key: []}) # 声明键值和value类型
    # 开始存储每个测试样本预测类别的支持票数
    for key,n_votes in y_pred: # 每个投票结果有1个预测标签和支持该预测的投票数
        Votes[key].append(n_votes) # 使用defaultdict就无需实现声明键值了,这里是给出用dict时的写法

    # idx,maxVotes,minVotes,confidence=key作为横坐标,支持当前类别的最大最小投票数,平均置信度(总的支持投票数/总投票数)
    maxminVotes = [[],[],[],[]]
    for key ,value in Votes.items():
        maxminVotes[0].append(int(key)) # 计算横坐标
        maxminVotes[1].append(np.max(value)) # 计算最大投票数
        maxminVotes[2].append(np.min(value)) # 计算最小投票数
        # 计算平均置信度
        maxminVotes[3].append(np.round(np.sum(value)/(K*len(value)),4)) # len(value)表示总的投票次数,每次有K=100票

    plt.figure(figsize=(10,3),dpi=600)
    plt.subplot(121)
    plt.plot(maxminVotes[0],maxminVotes[1],label="maxVote")
    plt.plot(maxminVotes[0], maxminVotes[2], label="minVote")
    plt.scatter(y_pred[:,0],y_pred[:,1],c=y_pred[:,0].ravel())
    plt.title("vote for k_dists")
    plt.legend(loc="upper right")
    plt.xlabel("label")
    plt.xticks(ticks=np.arange(0,len(maxminVotes[0]))) # 改变X轴刻度为0,1,2,..,9,不然默认是0,2,4,..8
    plt.yticks(ticks=np.arange(0,K+10,10)) # Y同理改变轴刻度为0,10,20,...,100
    plt.ylabel("n_votes")
    plt.subplot(122) # 平均置信度
    # 可选颜色,标记,线型见 https://blog.csdn.net/syyyy712/article/details/87426927
    # 颜色类型见 https://stackoverflow.com/questions/22408237/named-colors-in-matplotlib
    color = ['red','green','blue', 'pink', 'orange', 'yellow','gold','skyblue','cyan','brown']
    reats = plt.bar(maxminVotes[0], maxminVotes[3], width=0.35, align='center', color=color, alpha=0.8)
    for reat in reats:  # 每一个柱子循环标注数值大小
        reat_height = reat.get_height()  # 获取柱子高度
        plt.text(reat.get_x() + reat.get_width() / 2, reat_height, str(reat_height), size=10.5, ha='center',
                 va='bottom')
    plt.tight_layout()
    plt.xticks(ticks=np.arange(0, len(maxminVotes[0])))
    plt.title("avarage confidence for vote results")
    plt.yticks(ticks=np.arange(0,1.1,0.1))  # Y同理改变轴刻度为0,0.1,0.2,...,1.0
    plt.xlabel("label")
    plt.ylabel("avarage confidence")
    plt.show()
plot_vote_result()
#%%(4)对预测结果进行准确率分析
def score(y_true,y_pred):
    return np.sum(y_pred == y_true)/len(y_pred)
score = score(y_test[:test_num],y_pred[:,0])
print(f"test score = {score}") # 0.883
#%%<2>将以上函数合并写成KNN类：
class myKnn:
    def __init__(self,k=100,dist="L2",norm=False,norm_mode=None,norm_range=None):
        """
        :param k: int K个近邻,default=100
        :param dist: str 计算距离矩阵的模式,支持"L1"或"L2"距离
        :param norm: bool 是否标准化
        :param norm_mode: str 标准化模式,支持范围标准化"minMax"和正态标准化"zScore",如果为None默认"minMax"
        :param norm_range: tuple 当norm_mode="minMax"时有效,指定归一化的上下界,如果为None默认为(0,1)

        attribute ：
            ① distances : 计算得到的距离矩阵,shape=(X_test.shape[0],X_train.shape[0])
                每个测试样本都要和训练样本的每一个计算距离,生成一个行向量(X_train.shape[0],)
                所有测试样本计算完毕会生成行向量矩阵,行数为测试样本数,列数为训练样本数
            ② cost_time : 计算距离矩阵花费的时间,单位 秒/s
            ③ __isfit : 私有属性,判断外部是否执行了方法fit
            ④ vote_result : np.array([[], []])存储投票后的结果,其形状为 (X_test.shape[0],2), 用于存储每个测试集样本预测的真实标签和投票数目(k个最近邻中的支持率)
                            所谓支持率是: 例如在K=100的情况下,某个样本预测为0类,其中支持0类的投票数为80,支持其它类合计20次
                            下一个样本也预测为0类,但是可能支持0类的投票只有20个,其它类合计80,只是0类的20个比其它的任何一类都要多所以还是预测为0类,投票80和投票20都预测为0类的置信度肯定是不同的
                            为了计算置信度,可以对所有预测为0类的样本里统计支持0类的实际投票数之和,再除总的投票数(每次是K=100票,总票数为K*预测为0类的样本数),就可以得到平均置信度
            ⑤ avarage_confidence : 平均置信度,是长度为类别数的向量
            ⑥ y_pred : 预测的结果,长度与y_test相同
        method :
            ① fit : 拟合函数
            ② predict : 预测函数
            ③ __normalize : 归一化函数
            ④ minmaxium : 范围归一化函数
            ⑤ meanstdium : 正态标准化函数
            ⑥ __process : 数据预处理函数
            ⑦ __calculate_dist : 计算距离矩阵函数
            ⑧ __vote : 投票函数
            ⑨ score : 计算得分函数
            ⑩ plot_vote_result : 可视化投票结果和平均置信度
        其它 :
             __str__ : 打印当前实例化模型的输入参数

        """
        self.k = k
        self.norm = norm
        self.dist = dist
        self.norm_mode = norm_mode
        self.norm_range = norm_range
        self.__isfit = False
        self.distances = None
        self.cost_time = None
        self.vote_result = None
        self.avarage_confidence = None
        self.y_pred = None

    def fit(self,X_train,y_train):
        self.__isfit = True
        self.X_train = X_train
        self.y_train = y_train
        self.__process(X_train,y_train)

    def predict(self,X_test,y_test):
        self.X_test = X_test
        self.y_test = y_test
        self.__process(X_train, y_train)
        print("start calculating dist matrix ...")
        self.__calculate_dist()
        print(f"compute finished, cost time = {self.cost_time} s")
        print("start voting for dist matrix ...")
        self.__vote()
        print("vote finished")
        # self.vote_result 第1列是预测的类别，第2列是支持这个类别的投票数≤self.k
        self.y_pred = self.vote_result[:,0]
        return self.y_pred

    # 两个归一化方法也可以作为静态方法外部使用
    @staticmethod
    def minmaxium(X, norm_range):
        # 不涉及距离度量、协方差计算、数据不符合正太分布的时候，可以使用本方法
        # 例如图片处理可以归一化到0-255或0-1
        assert X.ndim == 1 or X.ndim == 2
        if X.ndim == 1:
            # 归一化到(a,b)的公式为y=(x-min)/(max-min)+a,x=min=>a,x=max=>b b=norm_range[1],a=norm_range[0]
            minval, maxval = np.min(X), np.max(X)
            X = np.array(
                [(x - minval) * (norm_range[1] - norm_range[0]) / (maxval - minval) + norm_range[0] for x in X])
        else:  # X.ndim=2
            # 样本的特征之间可能差距较大所以是每个样本的特征之间归一化
            # 1)使用循环：效率很低
            """
            for i in range(X.shape[0]): # 每个样本循环,对行向量归一化
                minval, maxval = np.min(X[i,:]),np.max(X[i,:])
                X[i,:] = np.array([(x-minval)*(norm_range[1]-norm_range[0])/(maxval-minval)+norm_range[0] for x in X[i,:]])
            """
            # 2)使用广播：效率较高
            """
            测试程序：
            (train_x,train_y),(test_x,test_y)=mnist.load_data()
            a = train_x.reshape(-1,784)
            min_a,max_a= np.min(a,axis=-1),np.max(a,axis=-1)
            min_max_a = max_a - min_a
            b = (a - min_a.reshape(-1,1))/min_max_a.reshape(-1,1)*2 -1
            ! 特别要注意，单独乘一个数2(推广为b-a)要放在后边乘才有广播效应
            (X_train == train_x.reshape(-1,784)).all()
            如果b=255,a=0，实际上 X_train == train_x.reshape(-1,784)，返回False是个别数有除数误差取整即可
            """
            minval, max_val = np.min(X, axis=-1), np.max(X, axis=-1)  # 注意axis=-1表示最后1个维度,也就是Y维度,在numpy中Y维度是行方向(样本方向)
            X = (X - minval.reshape(-1, 1)) / (max_val.reshape(-1, 1) - minval.reshape(-1, 1)) * (
                        norm_range[1] - norm_range[0]) + norm_range[0]  # 广播效应之前必须形状相同,按行广播先使用reshape改变minval,maxval为单列
        return X

    @staticmethod
    def meanstdium(X):
        # 需要使用距离来度量相似性的分类、聚类算法或使用PCA进行降维时适用于本方法
        # # 标准差=方差的算术平方根 std * std = var
        assert X.ndim == 1 or X.ndim == 2
        if X.ndim == 1:
            return (X - np.mean(X)) / np.std(X)
        else:
            # 利用广播效应参考minmaxium的实现
            mean, std = np.mean(X, axis=1), np.std(X, axis=1)
            return (X - mean.reshape(-1, 1)) / std.reshape(-1, 1)

    def __normalize(self,X):
        if self.norm_mode == "zScore":
            return self.meanstdium(X)
        else:
            return self.minmaxium(X, self.norm_range)

    def __process(self,X, y):
        try:
            assert X.ndim == 2 or X.ndim == 3
            assert y.ndim == 1
        except AssertionError:
            print("X,y must be satisfied 2 ≤ X.ndim ≤ 3 and y.nidm = 1!")

        if self.norm_mode is None:
            self.norm_mode = "minMax"
        if not isinstance(self.norm_mode, str):
            raise TypeError("norm_mode must be string or None!if None,default 'minMax'")
        if self.norm_mode not in ["minMax", "zScore"]:
            raise ValueError("'norm_mode' only support 'minMax' or 'zScore'")
        if self.norm_mode == "minMax":
            if self.norm_range is None:
                self.norm_range = (0, 1)
            if not isinstance(self.norm_range, tuple):
                raise TypeError("norm_range must be tuple like (a,b) or None!if None,default (0,1)")

        if self.norm_mode == "zScore" and self.norm_range is not None:
            raise Warning("when norm_mode is 'zScore',param norm_range is invalid")
        if X.ndim == 3:
            X = X.reshape(-1, X.shape[1] * X.shape[2])
        if self.norm:
            X = self.__normalize(X)
        return X, y

    def __calculate_dist(self):
        if self.dist not in ["L1", "L2"]:
            raise ValueError("dist only support 'L1' or 'L2',default 'L2'!")
        from time import time  # 引入时间
        from tqdm import tqdm  # 引入进度条
        distances = []
        t1 = time()
        for every_test_sample in tqdm(self.X_test, colour='green'):
            # for every_test_sample in (test_x):
            """
            默认情况下np.tile(A,2)表示对A在X轴(axis=0 or -1)方向平铺2倍,或者说对A按列堆叠
            a = np.array([[1],[2]]) # (2,1)
            b = np.tile(a,3)
            out: (2,3)的array([[1, 1, 1],
                                [2, 2, 2]])
            b = np.tile(a,(2,3))表示在Y轴方向(axis=1)对a平铺2次，X轴(axis=0 or -1)方向平铺3次
            out: array([[1, 1, 1],
                       [2, 2, 2],
                       [1, 1, 1],
                       [2, 2, 2]])
            注意：reps元素最后1个数才是轴0(X轴列方向)的平铺倍数,与np.mean/np.min/np.max/np.sum等的参数axis=0含义类似
                  axis=-1表示最后1个维度,也就是Y维度,在numpy中Y维度是行方向(样本方向),这点在maxminium函数说明过
                  因为这里输入的X_train维度已经被处理为2,所以axis=-1和axis=1是相同的
            对当前遍历的测试集样本按Y方向(行)堆叠以后shape就和X_train相同了,此时直接作差就是L1距离,取平方为L2距离
            然后按照样本方向(Y方向=axis=1)对距离进行求和(X轴/列元素求和)得到总距离向量(shape=(X_train.shape[0],)),对于L2再取根方即可
            """
            current_sample = np.tile(A=every_test_sample, reps=(self.X_train.shape[0], 1))  # X轴方向不堆叠,Y方向(行)堆叠60000次
            assert current_sample.shape == self.X_train.shape  # 堆叠后的shape必定相同均为(60000,784)
            if self.dist == "L2":
                distance = np.sqrt(np.sum(np.abs(self.X_train - current_sample) ** 2, axis=1))
            else:
                distance = np.sum(np.abs((self.X_train - current_sample)), axis=1)
            assert distance.shape == (current_sample.shape[0],)
            distances.append(distance)  # 10000 * 60000 每行表示1个测试样本到60000个训练样本的距离向量
        t2 = time()
        self.distances = np.array(distances)
        self.cost_time = t2 - t1

    def __vote(self):
        assert self.distances.shape[1] == len(self.y_train)  # 1个距离向量有60000个距离元素
        from tqdm import tqdm
        y_pred = [[], []]  # 用于存储每个测试集样本预测的真实标签和投票数目(k个最近邻中的支持率)
        for dist in tqdm(self.distances):  # 每个测试样本的距离向量遍历
            """
            argsort函数的作用是首先对序列升序,再遍历每个元素得到原来序列的实际索引位置
            例子：
            np.argsort([3,1,2,4])
            array([1, 2, 0, 3], dtype=int64)
            [3,1,2,4]升序后是[1,2,3,4],开始遍历1的实际位置是1,2的实际位置是2,3的实际位置是0,4的实际位置是3
            所以输出为[1, 2, 0, 3]
            这里的目的是为了得到最近的k个距离在距离向量的实际位置
            """
            nidx = np.argsort(dist, kind="mergesort")  # 冒泡排序得到升序后每个距离在原距离向量所处的实际位置
            kidx = nidx[:self.k]  # 前k个距离的实际位置,idx是升序的实际位置
            from collections import defaultdict
            """
            a = dict(a=1, b=2, c=3)
            a["a"] += 1 # 已经存在的键可以作+=
            # a["d"] += 1 # 会报错不存在的键KeyError: 'd'
            # a[0] += 1
            b = defaultdict(int)
            b["a"] += 1 # defaultdict可以在键不存在的时候+=,即根据需要动态添加键并赋值
            使用defaultdict 可以动态添加关键字label,dict必须事先指定关键字,而label又是不可知的,所以不要使用dict
            """
            label_num = defaultdict(int)  # 用于统计不同类别的数目,指定value为int类型
            for idx in kidx:  # idx是最近的k个图片实际的索引位置,也是标签的位置
                label = self.y_train[idx]  # 用实际的位置得到对应的类别
                label_num[label] += 1  # 动态的把label作为关键字并赋值
            import operator
            # 字典是无序的,先按照value排序然后取出对应的key就是投票后产生的结果,也就是当前X_test[i]的判断类别
            """
            a = {"a":2,"c":3,"e":1}
            # b = sorted(a.items(),reverse=True,key=a.values()) # 想要按照字典的value排序,单数a.values()是不可迭代的会报错
            如果给定item就会自动抓取返回可迭代元组对象
            operator.itemgetter()可以理解为可迭代的(key、value)的操作对 常用于对字典排序
            b = sorted(a.items(),reverse=True,key=operator.itemgetter(0)) # 0表示按照key排序,返回元组对的列表
            c = sorted(a.items(),reverse=True,key=operator.itemgetter(1)) # 1表示按照value排序,返回元组对的列表
            output :
                b = [('e', 1), ('c', 3), ('a', 2)] # 按key排序
                c = [('c', 3), ('a', 2), ('e', 1)] # 按value排序
                c[0][0]表示排序后的第1个item对的key值,c[0][1]为value值
            """
            sorted_label_num = sorted(label_num.items(), reverse=True, key=operator.itemgetter(1))  # reverse表示降序
            y_pred[0].append(sorted_label_num[0][0])  # k个最近邻投票预测的类别
            y_pred[1].append(sorted_label_num[0][1])  # k个最近邻中支持该类别的数目(支持率)
        self.vote_result = np.array(y_pred).T

    def plot_vote_result(self,gap):
        # gap用于设置Y轴的单位刻度,如果K=100,gap=10,则以0,10,20,..,100的刻度进行显示
        Votes = {}  # 10个类别0-9作为key,value是列表,存储每次支持该类别的所有票数
        for key in [x for x in range(10)]:
            Votes.update({key: []})  # 声明键值和value类型
        # 开始存储每个测试样本预测类别的支持票数
        for key, n_votes in self.vote_result:  # 每个投票结果有1个预测标签和支持该预测的投票数
            Votes[key].append(n_votes)  # 使用defaultdict就无需实现声明键值了,这里是给出用dict时的写法

        # idx,maxVotes,minVotes,confidence=key作为横坐标,支持当前类别的最大最小投票数,平均置信度(总的支持投票数/总投票数)
        maxminVotes = [[], [], [], []]
        for key, value in Votes.items(): # 每个类别进行循环判断
            maxminVotes[0].append(int(key)) # 计算横坐标
            maxminVotes[1].append(np.max(value)) # 计算最大投票数
            maxminVotes[2].append(np.min(value)) # 计算最小投票数
            # 计算平均置信度
            maxminVotes[3].append(np.round(np.sum(value) / (self.k * len(value)), 4))  # len(value)表示总的投票次数,每次有K=100票
        self.avarage_confidence = np.array(maxminVotes[3])
        plt.figure(figsize=(10, 3), dpi=600)
        plt.subplot(121)
        plt.plot(maxminVotes[0], maxminVotes[1], label="maxVote")
        plt.plot(maxminVotes[0], maxminVotes[2], label="minVote")
        plt.scatter(self.vote_result[:, 0], self.vote_result[:, 1], c=self.vote_result[:, 0].ravel())
        plt.title("vote for k_dists")
        plt.legend(loc="upper right")
        plt.xlabel("label")
        plt.xticks(ticks=np.arange(0, len(maxminVotes[0])))  # 改变X轴刻度为0,1,2,..,9,不然默认是0,2,4,..8
        plt.yticks(ticks=np.arange(0, self.k + gap, gap))  # Y同理改变轴刻度为0,10,20,...,100
        plt.ylabel("n_votes")
        plt.subplot(122)  # 平均置信度
        # 可选颜色,标记,线型见 https://blog.csdn.net/syyyy712/article/details/87426927
        # 颜色类型见 https://stackoverflow.com/questions/22408237/named-colors-in-matplotlib
        color = ['red', 'green', 'blue', 'pink', 'orange', 'yellow', 'gold', 'skyblue', 'cyan', 'brown']
        reats = plt.bar(maxminVotes[0], maxminVotes[3], width=0.35, align='center', color=color, alpha=0.8)
        for reat in reats:  # 每一个柱子循环标注数值大小
            reat_height = reat.get_height()  # 获取柱子高度
            plt.text(reat.get_x() + reat.get_width() / 2, reat_height, str(reat_height), size=10.5, ha='center',
                     va='bottom')
        plt.xticks(ticks=np.arange(0, len(maxminVotes[0])))
        plt.title("avarage confidence for vote results")
        plt.yticks(ticks=np.arange(0, 1.1, 0.1))  # Y同理改变轴刻度为0,0.1,0.2,...,1.0
        plt.xlabel("label")
        plt.ylabel("avarage confidence")
        plt.tight_layout()
        plt.show()

    def score(self,y_true, y_pred):
        return np.sum(y_pred == y_true) / len(y_pred)

    def __str__(self):
        # print("model param : ")
        # print(f"k_neighbors = {self.k}")
        # print(f"norm = {self.norm}")
        if self.norm :
            if self.__isfit :
                if self.norm_mode is None :
                    norm_mode = "minMax"
                else:
                    norm_mode = self.norm_mode
                if self.norm_mode == "minMax" or self.norm_mode is None:
                    if self.norm_range is None :
                        norm_range = (0,1)
                    else:
                        norm_range = self.norm_range
                else :
                    norm_range = "invalid"
                return f"model param : \nk_neighbors = {self.k}\nnorm = {self.norm}" \
                       f"\nnorm_mode = {norm_mode}\nnorm_range = {norm_range}" \
                       f"\nX_train y_train shape = {self.X_train.shape} {self.y_train.shape}"
            else:
                return f"model param : \nk_neighbors = {self.k}\nnorm = {self.norm}" \
                       f"\nnorm_mode = minMax\nnorm_range = (0,1)" \
                       f"\nX_train,y_train is None,you should fit(X_train,y_train) first!"
        else:
            return f"model param : \nk_neighbors = {self.k}\nnorm = {self.norm}"
train_num = 10000  # 因为一次性训练时间过长,所以选择有10000个训练样本去计算
test_num = 1000 # 测试样本同理,原本的train_num=60000,test_num=10000
TX_train,Ty_train = X_train[:train_num],y_train[:train_num] # 临时数据集
TX_test,Ty_test = X_test[:test_num],y_test[:test_num]# 临时数据集
#%%(1) 默认参数:不归一化比较L1和L2距离
for dist in ["L1","L2"]:
    model = myKnn(dist=dist)
    print(model)
    model.fit(TX_train,Ty_train)
    y_pred = model.predict(TX_test,Ty_test)
    print("test score = ",model.score(Ty_test,y_pred))
# L1=0.858,L2=0.883 结论是L2好于L1
#%%(2) 归一化：使用范围归一化minMax,归一化范围为(0,1)和(-1,1)进行比较,根据上述结果L2优于L1,L2固定
for norm_range in [(-1,1),(0,1)]:
    model = myKnn(norm=True,norm_mode="minMax",norm_range=norm_range)
    model.fit(TX_train,Ty_train)
    y_pred = model.predict(TX_test,Ty_test) #
    print("test score = ",model.score(Ty_test,y_pred))
# (-1,1)= 0.883,(0,1)=0.883 norm=False时本质上就是归一化到(0,255)也是0.883,所以似乎这里范围归一化没有效果
#%% (3)再来看看正态标准化：使用zScore,不使用minMax
model = myKnn(norm=True, norm_mode="zScore")
model.fit(TX_train, Ty_train)
y_pred = model.predict(TX_test, Ty_test)
print("test score = ", model.score(Ty_test, y_pred))  # test score =  0.883 不变
model.plot_vote_result(gap=10) # 调整Y轴刻度,单位长度为10,由于Y轴最大为K=100,注意K与gap的比例协调关系
#%% (4)最后1个比较的是超参数k
# 鉴于以上的讨论,norm_mode不影响结果,所以固定norm=True,norm_mode="minMax",norm_range=(0,1)
for k in [5,10,20,50,200]:
    model = myKnn(k=k,norm=True)
    model.fit(TX_train, Ty_train)
    y_pred = model.predict(TX_test, Ty_test)
    print("test score = ", model.score(Ty_test, y_pred))
# 0.937,0.933,0.931,0.908,0.851
#%% (5)最后使用完整的数据集而不是临时数据集计算花费的时间和准确率，根据上述结果进一步确定k=3
model = myKnn(k=3,norm=True)
model.fit(X_train, y_train)
y_pred = model.predict(X_test, y_test)
print("test score = ", model.score(y_test, y_pred))
model.plot_vote_result(gap=0.5) # k=3时取gap=0.5比较合适
# cost time = 4038.709842443466 s
# test score =  0.9751
#%%<3>使用sklearn的KNN实现
from sklearn.neighbors import  KNeighborsClassifier
from time import time
clf = KNeighborsClassifier(n_neighbors=3)
clf.fit(X_train,y_train)
t1 = time()
test_score = clf.score(X_test,y_test)
t2 = time()
print("test score = ",test_score)# 0.9745
print("cost time = ",t2-t1," s") # cost time =  663.0321996212006  s
# 可以看出准确率上区别不大,时间上花费较少,自定义的KNN有待优化
