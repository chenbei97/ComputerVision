#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : December_09_DecisionTreeVisualization.py
@Author : chenbei
@Date : 2022-01-04 11:10
@Email ：chenbei_electric@163.com
@Address : Beijing Jiaotong University
'''
from matplotlib.pylab import mpl
mpl.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
# mpl.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
# mpl.rcParams['savefig.dpi'] = 600  # 图片像素
# mpl.rcParams['figure.dpi'] = 400  # 分辨率
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.datasets import load_iris
from sklearn.tree import DecisionTreeClassifier
from sklearn import tree
import graphviz
# (1)准备数据
data = load_iris()
df = pd.DataFrame(data.data, columns = data.feature_names)
df['Species'] = data.target
target = np.unique(data.target)
target_names = np.unique(data.target_names)
targets = dict(zip(target, target_names))
df['Species'] = df['Species'].replace(targets) # 用实际名称而非数字作为类别
X = df.drop(columns="Species")
y = df["Species"]
X_train, X_test, y_train, y_test = train_test_split(X,y,
                                                 test_size = 0.4,
                                                 random_state = 42)
model = DecisionTreeClassifier(max_depth =3, random_state = 42)
model.fit(X_train, y_train)
# （2）文字可视化
text_representation = tree.export_text(model)
print(text_representation)

# (3)借助plot_tree函数
plt.figure(figsize=(30,10), facecolor ='g') #
a = tree.plot_tree(model,
                   feature_names = X.columns,
                   class_names = y.unique(),
                   rounded = True,
                   filled = True,
                   fontsize=14)
plt.show()

# （4）借助graphviz(这也是HiddenLayer、torchviz、和tf.keras.utils.plot_model的依赖包)
dot_data = tree.export_graphviz(model, out_file=None,
                                feature_names=data.feature_names,
                                class_names=data.target_names,
                                filled=True)
graph = graphviz.Source(dot_data, format="png")
graph.view() # pycharm要使用view函数

