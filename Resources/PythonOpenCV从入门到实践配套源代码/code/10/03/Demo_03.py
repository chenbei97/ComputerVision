import cv2
import os
import sys

PIC_PATH = "C:\\Users\\Administrator\\Desktop\\test\\"  # 照片文件夹地址
width, height = 100, 100  # 缩放比例

pic_file = os.listdir(PIC_PATH)  # 所有照片文件列表
same_pic_index = []  # 相同图像的索引列表
imgs = []  # 缩放后的图像对象列表
has_same = set()  # 相同图像的集合
count = len(pic_file)  # 照片数量

if count == 0:  # 如果照片数量为零
    print("没有图像")
    sys.exit(0)  # 停止程序

for file_name in pic_file:  # 遍历照片文件
    pic_name = PIC_PATH + file_name  # 拼接完整文件名
    img = cv2.imread(pic_name)  # 创建文件的图像
    img = cv2.resize(img, (width, height))  # 缩放成统一大小
    imgs.append(img)  # 按文件顺序保存图像对象

for i in range(0, count - 1):  # 遍历所有图像文件，不遍历最后一个图像
    if i in has_same:  # 如果此图像已经找到相同的图像
        continue  # 跳过
    templ = imgs[i]  # 取出模板图像
    same = [i]  # 与templ内容相同的图像索引列表
    for j in range(0 + i + 1, count):  # 从templ的下一个位置开始遍历
        if j in has_same:  # 如果此图像已经找到相同的图像
            continue  # 跳过
        pic = imgs[j]  # 取出对照图像
        results = cv2.matchTemplate(pic, templ, cv2.TM_CCOEFF_NORMED)  # 比较两图像相速度
        if results > 0.9:  # 如果相似度大于90%，认为是同一张照片
            same.append(j)  # 记录对照图像的索引
            has_same.add(i)  # 模板图像已找到相同图像
            has_same.add(j)  # 对照图像已找到相同图像
    if len(same) > 1:  # 如果模板图像找到了至少一张与自己相同的图像
        same_pic_index.append(same)  # 记录相同图像的索引

for same_list in same_pic_index:  # 遍历所有相同图像的索引
    text = "相同的照片："
    for same in same_list:
        text += str(pic_file[same]) + ", "  # 拼接文件名
    print(text)
