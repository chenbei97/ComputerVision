#%%
# -*- coding UTF-8 -*-
'''
@Project : MyPythonProjects
@File : 处理CSV数据.py
@Author : chenbei
@Date : 2021/7/27 8:52
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
import tensorflow_datasets as tfds
import functools
TRAIN_DATA_URL = "https://storage.googleapis.com/tf-datasets/titanic/train.csv"
TEST_DATA_URL = "https://storage.googleapis.com/tf-datasets/titanic/eval.csv"
train_file_path = tf.keras.utils.get_file("train.csv", TRAIN_DATA_URL)
test_file_path = tf.keras.utils.get_file("eval.csv", TEST_DATA_URL)
np.set_printoptions(precision=3, suppress=True)
CSV_COLUMNS = ['survived', 'sex', 'age', 'n_siblings_spouses',
               'parch', 'fare', 'class', 'deck', 'embark_town', 'alone']
# dataset = tf.data.experimental.make_csv_dataset(file_pattern="train.csv",
#                                                 num_epochs=5,
#                                                 shuffle=False,
#                                                 batch_size=2,
#                                                 select_columns=CSV_COLUMNS[0:3])
# iterator = dataset.as_numpy_iterator()
# a = dict(next(iterator))
# print(a)
def get_dataset(file_path):
  dataset = tf.data.experimental.make_csv_dataset(
      file_pattern=file_path,
      batch_size=12, # 为了示例更容易展示，手动设置较小的值
      label_name= 'survived', # 设定标签列
      na_value="?",# 遇到问号识别为NAN
      num_epochs=1, # 指定遍历数据集的次数 否则默认无限循环
      header=True, # 默认导入的CSV文件有标题行
      select_columns=None,# 如果不需要全部列则进行指定
      ignore_errors=True )# 默认遇见有错误的数据或者空行时停止解析 设为True会忽略该行错误转到下一行
  return dataset
raw_train_data = get_dataset(train_file_path)
raw_test_data = get_dataset(test_file_path)
CATEGORIES = {
    'sex': ['male', 'female'],
    'class' : ['First', 'Second', 'Third'],
    'deck' : ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'],
    'embark_town' : ['Cherbourg', 'Southhampton', 'Queenstown'],
    'alone' : ['y', 'n']} # 没有age和survived age更像回归 survived是标签 这些列只能在有限的集合中取值
examples, labels = next(iter(raw_train_data)) # 指定标签列时 标签单独返回
dict(examples) # 从结果来看得到了所有样本的sex、age、n_siblings_spouses等等
# 每个指标都是一行,所以变成了标签数*样本数的以列为主的张量
#%%
# 标签列
categorical_columns = []
for key, value in CATEGORIES.items():
    # 带有内存词汇表的CategoricalColumn
    cat_col = tf.feature_column.categorical_column_with_vocabulary_list(
        key=key, vocabulary_list=value)
    # VocabularyListCategoricalColumn(key='alone', vocabulary_list=('y', 'n'), dtype=tf.string)
    categorical_columns.append(tf.feature_column.indicator_column(cat_col))
#%%

#%%
def process_continuous_data(mean, data):
  # 标准化数据
  data = tf.cast(data, tf.float32) * 1/(2*mean)
  return tf.reshape(data, [-1, 1])

MEANS = {
    'age' : 29.631308,
    'n_siblings_spouses' : 0.545455,
    'parch' : 0.379585,
    'fare' : 34.385399
}

# 数字列
numerical_columns = []

for feature in MEANS.keys():
  num_col = tf.feature_column.numeric_column(feature,
  normalizer_fn=functools.partial(process_continuous_data, MEANS[feature]))
  numerical_columns.append(num_col)
#%%
# 将这两个特征列的集合相加，并且传给 tf.keras.layers.DenseFeatures 从而创建一个进行预处理的输入层
preprocessing_layer = tf.keras.layers.DenseFeatures(categorical_columns+numerical_columns)

# 从 preprocessing_layer 开始构建 tf.keras.Sequential
model = tf.keras.Sequential([
  preprocessing_layer,
  tf.keras.layers.Dense(128, activation='relu'),
  tf.keras.layers.Dense(128, activation='relu'),
  tf.keras.layers.Dense(1, activation='sigmoid'),
])

model.compile(
    loss='binary_crossentropy',
    optimizer='adam',
    metrics=['accuracy'])

train_data = raw_train_data.shuffle(500)
test_data = raw_test_data

model.fit(train_data, epochs=20)

test_loss, test_accuracy = model.evaluate(test_data)
print('\n\nTest Loss {}, Test Accuracy {}'.format(test_loss, test_accuracy))
#%%
predictions = model.predict(test_data)

# 显示部分结果
for prediction, survived in zip(predictions[:10], list(test_data)[0][1][:10]):
    print(prediction,bool(survived),survived.numpy())
    print("Predicted survival: {:.2%}".format(prediction[0]),
        " | Actual outcome: ",
        ("SURVIVED" if bool(survived) else "DIED"))