#%%
# -*- coding UTF-8 -*-
'''
@Project : MyProjects
@File : 处理图像（from_tensor_slices）.py
@Author : chenbei
@Date : 2021/7/22 11:25
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
import os
font_set = FontProperties(fname=r"C:\Windows\Fonts\simsun.ttc", size=10.5)
import numpy as np
import pandas as pd
from IPython.display import display, Image
import pathlib
import random
import tensorflow as tf
from tensorflow  import keras
#%% 一 下载数据 在缓存中则跳过下载
# 本例中使用的数据集分布在图片文件夹中，一个文件夹含有一类图片
# fname的意思为下载后文件的命名，而untar=True的意思为对下载完后的文件压缩包直接进行解压
# 返回下载的文件绝对路径字符串,默认在.keras\\datasets文件夹下
path_to_downloaded_file = tf.keras.utils.get_file(
    "flower_photos",
    "https://storage.googleapis.com/download.tensorflow.org/example_images/flower_photos.tgz",
    untar=True) # {str}'C:\\Users\\chenbei\\.keras\\datasets\\flower_photos'
data_root = pathlib.Path(path_to_downloaded_file) # WindowsPath对象:C:\Users\chenbei\.keras\datasets\flower_photos
# iterdir() 遍历此目录中的文件 五个文件夹和一个txt文件
for item in data_root.iterdir():
  print(item)


#%%  二 获取所有图片对象的地址、查看license文件对象和随机查看图片对象 给所有图片赋予标签
# 1) 得到WindowPath对象
# all_image_paths = list(data_root.glob('*')) # 返回当前文件夹下的6个目录地址
# all_image_paths = list(data_root.glob('**')) # * 和 ** 没有区别
# all_image_paths = list(data_root.glob('*/')) # 返回当前文件夹下的6个目录地址
all_image_paths = list(data_root.glob('*/*')) # 和*/*.jpg 相同 都是子目录下的地址3670
# all_image_paths = list(data_root.glob('**/*')) # 返回父目录和子目录所有的地址 3676
# all_image_paths = list(data_root.glob('**/**')) # 5个文件夹地址和C:\Users\chenbei\.keras\datasets\flower_photos
# all_image_paths = list(data_root.glob('*/**')) # 5个文件夹地址
# 2) 转换成str字符串对象
all_image_paths = [str(path) for path in all_image_paths]
# 列表的所有元素随机排序
random.shuffle(all_image_paths)

# 从license.txt文件的第5行开始读 也就是索引4开始 注:索引规则是包含头部不包含尾部
# 得到的是字符串列表
attributions = (data_root/"LICENSE.txt").open(encoding='utf-8').readlines()[4:]
#　循环对字符串列表的每个元素进行处理,在' CC-BY'之前和之后进行分割得到2个字符串
attributions = [line.split(' CC-BY') for line in attributions]
# 转换成字典 形如'daisy/7568630428_8cf0fc16ff_n.jpg' 相对路径作为关键字 网址为值
attributions = dict(attributions)

# 打印图片和作者信息
def print_image_author(image_path):
    # 输入的是字符串对象 图片的绝对路径
    # pathlib.Path(image_path) 功能是转回WindowsPath对象
    # 计算此路径相对 other 表示路径的版本 也就是计算图片绝对路径相对于图片文件夹flower_photos地址的相对路径
    # 可以得到形如包含一些信息 : {str}name='2996573407_5e473b9359.jpg'   {tuple}parts={str}{str}
    # {WindowsPath}sunflowers 的一个地址类对象
    image_rel = pathlib.Path(image_path).relative_to(data_root)
    #　str(image_rel)得到相对路径的字符串sunflowers\\2996573407_5e473b9359.jpg
    image_rel  = image_rel.parts[0]+'/'+image_rel.parts[1] # 取出相对路径 不能直接用str(image_rel) 在字典中找不到
    # by David Hepworth - https://www.flickr.com/photos/medhead/2521811279/
    # split(' - ')是将' _ '去除得到2个字符串 [:-1]的效果是去除最后一个字符串 实际上就是第一个字符串
    return "Image (CC BY 2.0) " + ' - '.join(attributions[image_rel].split(' - ')[:-1])
for n in range(3):
  image_path = random.choice(all_image_paths)
  # display(Image(filename= image_path))  此代码只能在jupyter notebook运行
  img = plt.imread(image_path) # 在pycharm中使用plt.imread读取图片二进制数据
  plt.imshow(img) # 显示图像
  plt.show() # 显示
  print(print_image_author(image_path))
  print()

# 生成图片标签 all_image_labels
# 取出6个WindowsPath对象的name也就是父目录名称 如果item是文件夹的话 返回升序后的字符串对象
label_names = sorted(item.name for item in data_root.glob('*/') if item.is_dir())
# 利用enumerate循环得到可迭代对象label_names的索引和元素 组成字典 这样将字符标签对应到整数编号 比较优雅
label_dict = dict((name, index) for index, name in enumerate(label_names))
# 创建图片标签 对所有图片取出字符串路径转成WindowsPath对象再取出parent.namey也就是父目录名称 带入字典关键字
# 自动生成与图片all_image_paths一一对应的整数标签
all_image_labels = [label_dict[pathlib.Path(path).parent.name]
                    for path in all_image_paths]
#%% 三 处理图片数据为张量并归一化
# 1) 使用tf.io.read_file读取图片地址 返回类型 : tf.Tensor(shape=(), dtype=string)
# 2) 使用tf.image.decode_img或tf.image.decode_jpeg 将输入字节'string'转换为tf.dtypes.uint8类型的Tensor shape=(240, 240, 3), dtype=uint8
# 3) 使用tf.img.resize 调整图片 shape=(192, 192, 3), dtype=float32
img_path = all_image_paths[0] # 1) 图片路径
img_raw = tf.io.read_file(filename = img_path) # 2)读取文件的内容，此操作返回一个包含输入文件名全部内容的张量
# 它不做任何解析，它只是按原样返回内容。 通常，这是输入管道的第一步
print(repr(img_raw)[:100]+"...") # repr返回对象的规范字符串表示形式
print(str(img_raw)[:100]+"...")
# 解码为图像 tensor（张量）
img_tensor = tf.image.decode_image(img_raw) # shape=(229, 320, 3)
img_final = tf.image.resize(img_tensor, [192, 192]) # shape=(192, 192, 3)
#%%
img_final = img_final / 255.0
print(img_final.shape)
print(img_final.numpy().min())
print(img_final.numpy().max())
# 4) 查看resize的影响
# ①原图
img_example = plt.imread(img_path) # 原始图片大小 240 * 240 (高度 * 宽度)
img_example_label = all_image_labels[0]
plt.imshow(img_example)
plt.xlabel(print_image_author(img_path))
plt.title(label_names[img_example_label].title()) # .title 只有开头字母大小写的区别 (加了大写)
plt.show()
# ②调整后的图对比: 即resize是调整图片大小的 且可以用plt.imshow显示解码后的图像张量
plt.imshow(img_final)
plt.show()
#%%
# 以上代码变成函数封装 用于后续循环对图片处理
def load_process_image(path):
  image_raw = tf.io.read_file(path) # 读取绝对路径的图片地址并编码为字符串张量
  # tf.image.decode_image 更加通用，而tf.image.decode_jpeg则只适用于对jpg图片的处理
  image = tf.image.decode_jpeg(image_raw, channels=3) # 解码为无符号整型Uint图像张量
  # 关于channels
  # *0：使用JPEG编码图像中的通道数
  # *1：输出灰度图像
  # *3：输出RGB图像
  image = tf.image.resize(image, [192, 192]) # 调整大小
  image /= 255.0  # normalize to [0,1] range 变为Float32图像张量
  return image  # 此类型的image可以被plt.imshow()直接显示


#%% 四、利用函数load_process_image 构建图片数据集Datasets
# 1) 将字符串数组切片，得到一个字符串数据集
path_ds = tf.data.Dataset.from_tensor_slices(all_image_paths)
# 2) 创建一个新的图片数据集，通过在路径数据集上映射 preprocess_image 来动态加载和格式化图片
# map(function, iterable, ...)function -- 函数 iterable -- 一个或多个序列
# 当需要对序列进行某些操作或者处理，将其转换为新的列表时，用map函数
# 以参数序列中的每一个元素调用 function 函数，返回包含每次 function 函数返回值的新列表或者迭代器
AUTOTUNE = tf.data.experimental.AUTOTUNE # AUTOTUNE=-1
image_ds = path_ds.map(load_process_image, num_parallel_calls=AUTOTUNE) # TensorSliceDataset类型
# plt.figure(figsize=(8,8))
# for n, image in enumerate(image_ds.take(4)):
#     # n 索引 image表示经过load_process_image得到的图片张量
#     plt.subplot(2,2,n+1) # 0,1,2,3
#     plt.imshow(image)
#     plt.grid(False)
#     plt.xticks([])
#     plt.yticks([])
#     plt.xlabel(print_image_author(all_image_paths[n]))
# plt.show()
# 3) 使用同样的 from_tensor_slices 方法你可以创建一个标签数据集
# tf.cast等同于tf.dtypes.cast,将张量转换为新类型 这里是将all_image_labels列表类型转换车EagerTensor类型
label_ds = tf.data.Dataset.from_tensor_slices(tf.cast(all_image_labels, tf.int64))# TensorSliceDataset类型
for label in label_ds.take(10):
    #　类似于图片数据集,标签数据集label也是一个EagerTensor对象
    print(label.numpy())
    print(label_names[label.numpy()]) # 整数编号对应的英文名
# 4) 打包在一起得到一个(图片, 标签)数据集对
image_label_ds = tf.data.Dataset.zip((image_ds, label_ds))
print(image_label_ds) # <ZipDataset shapes: ((192, 192, 3), ()), types: (tf.float32, tf.int64)>
# 5) 如果不打包可以直接使用from_tensor_slices,也就是5)的步骤等价于1)~4)
# 有了整个图片和标签的数据集后,即存储地址和标签的两个列表all_image_labels和all_image_paths
# 可以直接对数据集对进行操作,返回的也是TensorSliceDataset类型
ds = tf.data.Dataset.from_tensor_slices((all_image_paths, all_image_labels)) # TensorSliceDataset类型
# 定义双参迭代器函数用于数据集对进行处理
def load_process_from_image_label(path, label):
    # 此函数区别是把label传递了出来
    return load_process_image(path), label
# 数据集队迭代需要双参的迭代函数
# 实际上image_label_ds包含了image_ds和label_ds
# 返回的区别在于1)~4)得到的ZipDataset,第5)步得到的是MapDataset,但数据格式一致
image_label_ds = ds.map(load_process_from_image_label)
print(image_label_ds) # <MapDataset shapes: ((192, 192, 3), ()), types: (tf.float32, tf.int32)>

#%% 五、对得到的 image_label_ds 数据集对 构建随机数据流(tf.data)
# 数据处理的需求 : 被充分打乱; 被分割为 batch;永远重复;尽快提供 batch 使用tf.data方法即可
# 在 .repeat 之后 .shuffle，会在 epoch 之间打乱数据 有些数据出现两次的时候，其他数据还没有出现过
# 在 .batch 之后 .shuffle，会打乱 batch 的顺序，但是不会在 batch 之间打乱数据
# @ https://blog.csdn.net/lichaobxd/article/details/106476115
# 例如np.arange(20)有20个元素　
# ① shuffle->batch(3)->repeat(2)
# 如生成[ [0,1,2,3,4],[5,6,7,8,9],[15,16,17,18,19] ] 和 [ [10,11,12,13,14] ]
# 所有数据先打乱，然后打包成batch输出，整体数据重复2个epoch
# 先打包3个,再重复打包只能找剩下的,1.一个batch中的数据不会重复；2.每个epoch的最后一个batch的尺寸小于等于batch_size

# ② shuffle->repeat(3)->batch
# 如生成 [ [0,1,2,3,4],[10,11,12,13,14],[5,6,7,8,9] ] 和 [ [15,16,17,18,19],[15,16,17,18,19],[10,11,12,13,14] ]
# 把所有数据先打乱，再把所有数据重复两个epoch, 这些数据进行打包

# ③ batch(3)->repeat(2)->shuffle
# 如生成[ [0,1,2,3,4],[5,6,7,8,9],[10,11,12,13,14] ] ; [ [0,1,2,3,4],[5,6,7,8,9],[10,11,12,13,14] ]
# 以及 [ [15,16,17,18,19] ] ; [ [15,16,17,18,19] ]
# 相当于把所有数据先打包成batch，然后把打包成batch的数据重复两遍，最后再将所有batch打乱进行输出
# 1.打乱的是batch；2.某些batch的尺寸小于等于batch_size，因为是对batch进行打乱，所以这些batch不一定是最后一个

BATCH_SIZE = 32
# 1) 设置一个和数据集大小一致的 shuffle buffer size（随机缓冲区大小）以保证数据被充分打乱
# 程序会维持一个buffer_size大小的缓存，每次都会随机在这个缓存区抽取一定数量的数据
image_count = len(all_image_paths)
ds = image_label_ds.shuffle(buffer_size=image_count) # 随机
# 2) dataset.repeat作用就是将数据重复使用多少epoch
ds = ds.repeat(count=None) # 重复 count=None或-1表示无限重复
# 3) dataset.batch作用是将数据打包成batch_size
ds = ds.batch(BATCH_SIZE) # 抓取样本数
# 4) 当模型在训练的时候 prefetch 使数据集在后台取得batch
# 创建一个从该数据集中预取元素的数据集   大多数数据集输入管道应该以调用prefetch结束
# 这允许在处理当前元素时准备后面的元素这通常会提高延迟和吞吐量，但代价是使用额外的内存来存储预取元素
ds = ds.prefetch(buffer_size=AUTOTUNE)
print(ds)# <PrefetchDataset shapes: ((None, 192, 192, 3), (None,)), types: (tf.float32, tf.int32)>

# 5) 为了解决以下三个问题,可以使用步骤 5) 代替 1) ~ 4)
# 使用 tf.data.Dataset.apply 方法和融合过的 tf.data.experimental.shuffle_and_repeat 函数来解决
# ① 完全打乱中使用和数据集大小一样的 buffer_size。较大的缓冲区大小提供更好的随机化，但使用更多的内存
# ② 从随机缓冲区中拉取任何元素前，要先填满它。所以 Dataset 启动的时候一个大的 buffer_size可能会引起延迟
# ③ 在随机缓冲区完全为空之前，被打乱的数据集不会报告数据集的结尾。Dataset由 .repeat 重新启动，导致需要再次等待随机缓冲区被填满
ds = image_label_ds.apply(
  tf.data.experimental.shuffle_and_repeat(buffer_size=image_count))
ds = ds.batch(BATCH_SIZE)
ds = ds.prefetch(buffer_size=AUTOTUNE)
print(ds) # <PrefetchDataset shapes: ((None, 192, 192, 3), (None,)), types: (tf.float32, tf.int32)>

#%% # 六、传递数据集到模型(迁移学习模型tf.keras.applications.MobileNetV2)
# <tensorflow.python.keras.engine.functional.Functional object at 0x000001ED06AF90F0>
# 1) 此函数返回一个 Keras 图像分类模型
mobile_net = tf.keras.applications.MobileNetV2(input_shape=(192, 192, 3), include_top=False)
# 2) 设置 MobileNet 的权重为不可训练
mobile_net.trainable=False
# 该模型期望它的输出被标准化至 [-1,1] 范围内 help(keras_applications.mobilenet_v2.preprocess_input)
# 3) 将输出传递给 MobilNet 模型之前，需要将其范围从 [0,1] 转化为 [-1,1] ds.map(function)---->keras_ds
def change_range(image,label):
  return 2*image-1, label # ds模型的image在[0,1]之间
keras_ds = ds.map(change_range)
# 4) MobileNet 为每张图片的特征返回一个 6x6 的空间网格
# 数据集可能需要几秒来启动，因为要填满其随机缓冲区
# iter(iterable) -> iterator 将可迭代对象变成迭代器
# next(iterator[,default]) default为可选参数，用于设置在没有下一个元素时返回该默认值，如果不设置又没有下一个元素则会出发StopIteration异常
image_batch, label_batch = next(iter(keras_ds)) # next(iter())传1个包
# image_batch : shape=(32, 192, 192, 3), dtype=float32  label_batch : tf.Tensor shape=(32,), dtype=int32
feature_map_batch = mobile_net(image_batch)
print(feature_map_batch.shape) # 这个包生成的特征张量形状(32, 6, 6, 1280)

#%% # 七、建立模型和编译模型并训练数据集ds
model = tf.keras.Sequential([
    mobile_net,
    # 构建一个包装了 MobileNet 的模型并在 tf.keras.layers.Dense
    # 输出层之前使用 tf.keras.layers.GlobalAveragePooling2D 来平均那些空间向量
    # 空间数据的全局平均池化操作 默认channels_last 为形如（samples，rows, cols，channels）的4D张量
    # channels_first模式下，为形如（samples，channels, rows，cols）的4D张量
    tf.keras.layers.GlobalAveragePooling2D(),
    tf.keras.layers.Dense(len(label_names), activation = 'softmax')]) # 输出层是5个标签
logit_batch = model(image_batch).numpy() # EagerTensor shape=(32, 5), dtype=float32 --->(.numpy) ndarray(32,5)
model.compile(optimizer=tf.keras.optimizers.Adam(),
              loss='sparse_categorical_crossentropy',
              metrics=["accuracy"])
model.summary()
steps_per_epoch=tf.math.ceil(len(all_image_paths)/BATCH_SIZE).numpy() # 3670/32≈115
model.fit(ds, epochs=10, steps_per_epoch=30) # 演示的目的只给定三次，一般采用真实的也就是115
# 使用的简单 pipeline（管道）在每个 epoch 中单独读取每个文件。
# 在本地使用 CPU 训练时这个方法是可行的，但是可能不足以进行 GPU 训练并且完全不适合任何形式的分布式训练

#%% 八、分析数据集和模型的性能
# 1) 构建一个简单的函数来检查数据集的性能
import time
default_timeit_steps = 2*steps_per_epoch+1
def timeit(ds, steps=default_timeit_steps):
  overall_start = time.time()
  # 在开始计时之前
  # 取得单个 batch 来填充 pipeline（管道）（填充随机缓冲区）
  it = iter(ds.take(steps+1)) # 231 steps
  next(it) # 开始进行迭代

  start = time.time()
  for i,(images,labels) in enumerate(it): # 每10个迭代输出一个点用于观察
    if i%10 == 0:
      print('.',end='')
  print()
  end = time.time()

  duration = end-start
  print("{} batches: {} s".format(steps, duration)) # 231 steps 花费多少时间
  print("{:0.5f} Images/s".format(BATCH_SIZE*steps/duration)) # 每s 处理多少个图片
  print("Total time: {}s".format(end-overall_start)) # 总的花费时间
timeit(ds)
# 231.0 batches: 12.158760786056519 s
# 607.95669 Images/s
# Total time: 18.287363052368164s
#%%
# 2) 使用 tf.data.Dataset.cache 在 epoch 之间轻松缓存计算结果
# 使用内存缓存的一个缺点是必须在每次运行时重建缓存，这使得每次启动数据集时有相同的启动延迟
ds = image_label_ds.cache()
ds = ds.apply(
  tf.data.experimental.shuffle_and_repeat(buffer_size=image_count))
ds = ds.batch(BATCH_SIZE).prefetch(buffer_size=AUTOTUNE)
timeit(ds)
# 第一次的结果
# 231.0 batches: 2.624976873397827 s
# 2816.02481 Images/s
# Total time: 8.43742847442627s
timeit(ds)
# 第二次的结果 存在缓存会比较快
# 231.0 batches: 1.310492753982544 s
# 5640.62638 Images/s
# Total time: 1.3424053192138672s
#%%
# 3) 如果内存不够容纳数据，使用一个缓存文件
ds = image_label_ds.cache(filename='./_tensorflow/加载和预处理数据/cache.tf-data')
ds = ds.apply(
  tf.data.experimental.shuffle_and_repeat(buffer_size=image_count))
ds = ds.batch(BATCH_SIZE).prefetch(1)
timeit(ds)
# 第一次的结果
# 231.0 batches: 20.672455310821533 s
# 357.57726 Images/s
# Total time: 27.304778337478638s
timeit(ds)
# 第二次的结果 存在缓存会比较快
# 231.0 batches: 12.121948719024658 s
# 609.80294 Images/s
# Total time: 18.30056881904602s
#%% 4) 原始图片数据中构建出一个 TFRecord 文件
# TFRecord 文件是一种用来存储一串二进制 blob 的简单格式通过将多个示例打包进同一个文件内
# TensorFlow 能够一次性读取多个示例，当使用一个远程存储服务，如 GCS 时，这对性能来说尤其重要
# 从原始图片数据中构建出一个 TFRecord 文件
image_ds = tf.data.Dataset.from_tensor_slices(all_image_paths).map(tf.io.read_file)
tfrec = tf.data.experimental.TFRecordWriter('images.tfrec')
tfrec.write(image_ds)
# 构建一个从 TFRecord 文件读取的数据集，并使用你之前定义的 preprocess_image 函数对图像进行解码/重新格式化
image_ds = tf.data.TFRecordDataset('images.tfrec').map(load_process_image)
# 压缩该数据集和你之前定义的标签数据集以得到期望的 (图片,标签) 对
ds = tf.data.Dataset.zip((image_ds, label_ds))
ds = ds.apply(
  tf.data.experimental.shuffle_and_repeat(buffer_size=image_count))
ds=ds.batch(BATCH_SIZE).prefetch(AUTOTUNE)
timeit(ds)
# 这比 缓存 版本慢，因为你还没有缓存预处理







