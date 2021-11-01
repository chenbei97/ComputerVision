#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : ImageProcessing（PIL）.py
@Author : chenbei
@Date : 2021/8/30 15:23
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
from matplotlib.font_manager import FontProperties
import numpy as np
import pandas as pd
import tensorflow as tf
import os
from tensorflow.keras import layers, Sequential

plt.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
plt.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
plt.rcParams['savefig.dpi'] = 600  # 图片像素
plt.rcParams['figure.dpi'] = 600  # 分辨率
font_set = FontProperties(fname=r"C:\Windows\Fonts\simsun.ttc", size=10.5)
root = os.path.join(os.getcwd(), "ImageProcessing")
img_dir = os.path.join(root, "images")
address = os.path.join(img_dir,"lena.jpg")
address1 = os.path.join(img_dir,"me.jpg")
from PIL import  Image
from PIL import  ImageDraw , ImageFont
from PIL import  ImageStat
from PIL import ImageChops
from PIL import ImageEnhance ,ImageFilter
# PIL (width, height) skimage (height,width, channel) 因为数组习惯先行后列对应的为先高后宽
# PIL得到的是PIL对象且属于Uint8类型而非float类型
# skimage的得到的是Numpy对象 通过np.array(PIL)和skimage.Image.fromarray(skimage)相互转换
# matplotlib读取得到的也是Numpy对象
# （1）Image（2）ImageFilter（3）ImageEnhance（4）ImageDraw、ImageFont
# （5）IamgeStat（6）ImageChops
img = Image.open(address)
#%% （1）Image  : img.width,img.height,img.mode,img.format,img.size
print(img.width,img.height,img.size,type(img))
# 1）裁剪图像 : (left, upper, width, height)-tuple 定义了到左、上的距离和截取区域的宽度和高度
img_crop = img.crop(box=(0,0,350,300))
# 2）缩放图像 : PIL.Image.NEAREST,PIL.Image.BILINEAR,PIL.Image.BOX
img_resize = img.resize(size=(img.width*2,img.height*2),resample=Image.BILINEAR)
# 3）点处理 : point
# ① 反转图像 : 255-r
img_point = img.point(lut = lambda x : 255-x) # lut 是一个单值函数类似于map可应用于所有像素点
# ② 对数变换
img_point_log = img.point(lut = lambda x : 255 * np.log(1 + x / 255))
# ③ 幂律变换
img_point_pow = img.point(lut = lambda x : 255 * (x / 255)**0.06)
# 4）图像格式 : convert
'''
# “1”、“L”、“P”“RGBA”和“RGB” L = R * 299/1000 + G * 587/1000 + B * 114/1000
# mode="1" 二值图像 非0即1 ---->mode="RGB" 3个通道对"1"的拷贝
# mode="L" 灰度图像 0-255 8bit ---->mode="RGB" 3个通道对"L"的拷贝
# mode="RGB"--->mode="P" 像素值为[0,255]之间的某个数值，但它为调色板的索引值，其最终还是彩色图像
# mode="P" 调色板图像 0-255 8bit ---->mode="RGB" 3个通道对"P"的拷贝

# mode="RGB"--->mode="RGBA",增加透明度通道均为255,表示不透明
# mode="RGBA"--->mode="RGB",直接删除透明度通道,其他不变
# mode="RGB"--->mode="CMYK",表示负片，C = 255 - R、M = 255 - G、Y = 255 - B、K = 0
# mode="CMYK"--->mode="RGB",负负得正 无损转换

# mode="RGB"--->mode="YCbCr",一种转换
# Y= 0.257*R+0.564*G+0.098*B+16
# Cb = -0.148*R-0.291*G+0.439*B+128
# Cr = 0.439*R-0.368*G-0.071*B+128
# mode="YCbCr"--->mode="RGB" ，反变换
# R= 1.164*(Y-16)+1.596*(Cr-128)
# G = 1.164*(Y-16)-0.392*(Cb-128)-0.813*(Cr-128)
# B = 1.164*(Y-16)+2.017*(Cb-128)
# PIL图像格式转换网站参考：https://blog.csdn.net/zong596568821xp/article/details/83151743

# 参数dither用于控制颜色抖动。默认是FLOYDSTEINBERG,不使用赋值为NONE
# 参数palette用于控制调色板的产生,默认是WEB，标准216色的“web palette”要使用优化的调色板，则赋值为ADAPTIVE
# 参数colors用于控制调色板颜色数目。当参数palette为ADAPTIVE时，colors数值表示调色板的颜色数目。默认是最大值，即256种颜色
'''
img_gray = img.convert(mode="L",matrix=None, dither=None, palette=Image.WEB, colors=256)
# 5）转置图像
img_transpose_flip_left_right = img.transpose(method = Image.FLIP_LEFT_RIGHT)
# 6) 旋转图像
img_rotate  = img.rotate(angle=45)
# 7）图像形状 : 通过反向映射(扭曲)实现 可以缩放、平移、旋转和剪切
'''
PIL.Image.EXTENT 切出矩形区域 PIL.Image.AFFINE 仿射变换
PIL.Image.PERSPECTIVE 透视变换 PIL.Image.QUAD 四边形映射到矩形
PIL.Image.MESH 一次操作映射多个源四边形
data = (a,b,c,d,e,f) , 对于输出图像像素位置(x,y),取自输入图像的(ax+by+c,dx+ey+f)'''
img_affine = img.transform(size=(int(1.4*img.width),img.height), method=Image.AFFINE, data=(1,-0.5,0,0,1,0))
# 8）更改像素值 :putpixel 类似于point，不过接受的是坐标处理函数
img_putpixel = img.copy()
n = 5000
x , y = np.random.randint(0 , img.width , n) ,np.random.randint(0 , img.height , n)
for (x,y) in zip(x,y):
    # 对(x,y)坐标像素进行更改 添加椒盐噪声
    img_putpixel.putpixel(xy=(x,y),value=( (0,0,0) if np.random.rand() < 0.5 else (255,255,255) ))
# 9）缩略图
img_thumbnail = img.copy()
img_thumbnail.thumbnail(size=(100,100) ,resample=Image.BICUBIC)
img.paste(im=img, box = (250,200))
# 10）绘制RGB通道像素值直方图
img_histogram = img.histogram() # 得到3个通道不同像素值的分布个数的依次平铺
# sum(img_histogram[:256]) # 187500 恰好是每个通道的像素值总个数
# 像素值在0-255范围内的每个值对应有多少个像素点
plt.bar(range(256),img_histogram[:256],color='r',alpha=0.5) # 从结果来看 R通道基本集中为0
plt.bar(range(256),img_histogram[256:512],color='g',alpha=0.5) # G通道基本集中在255
plt.bar(range(256),img_histogram[512:],color='b',alpha=0.5) # B通道基本集中在0
# 那么接近(0,255,0)的分布,所以图像整个呈现绿色
# 11）分离图像的RGB通道 : 展示不同通道的图像 (灰度级)
img_split_r , img_split_g , img_split_b  = img.split() # 分离后依然是PIL对象
# plt.subplot(131);plt.imshow(img_split_r,cmap=plt.cm.Reds);plt.axis('off')
# plt.subplot(132);plt.imshow(img_split_g,cmap=plt.cm.Greens);plt.axis('off')
# plt.subplot(133);plt.imshow(img_split_b,cmap=plt.cm.Blues);plt.axis('off')
# plt.tight_layout()
# plt.show()
# 12）合并图像通道
img_merge = Image.merge(mode='RGB', bands=(img_split_r,img_split_b,img_split_g)) # 交换蓝绿通道
# 13）双图像的α溶解混合 out = (1.0-α)*img1 + α*img2 要求模式相同(同RGB)、大小相同(width,height)
img1 = Image.open(address1)
img1 = img1.resize(size=(img.width,img.height),resample=Image.BILINEAR).convert(mode='RGB')
img_belend = Image.blend(im1=img, im2=img1, alpha=0.5)
# 14）filter
maxfilter = ImageFilter.MaxFilter(3)
im_maxfilter = img.filter(filter=maxfilter)
# im_maxfilter.show()
#%% （2）ImageFilter平滑
guass_blur = ImageFilter.GaussianBlur
n = 3
kernel = np.reshape(np.ones(n*n),(n,n))/ (n*n)
newimg1 = ImageFilter.Kernel((n,n),kernel.flatten())
maxfilter , minfilter ,medianfilter= ImageFilter.MaxFilter(3) ,ImageFilter.MinFilter(3),ImageFilter.MedianFilter(3)
filters = [ImageFilter.FIND_EDGES,ImageFilter.EDGE_ENHANCE,ImageFilter.EDGE_ENHANCE_MORE]
# （3）图像增强
imgContrast = ImageEnhance.Contrast(img)
imgCore = imgContrast.enhance(factor=2).getdata()
img_contrast = np.reshape(np.asarray(imgCore).astype(np.uint8),(imgCore.size[1],imgCore.size[0],imgCore.bands))
#%% （4）图像绘制图形 : 使用ImageDraw模块
# 1）绘制图形
draw_ellipse = ImageDraw.Draw(img) # 生成画布
# xy 的含义与crop一致 后2个表示椭圆宽度直径和高度直径 fill表示颜色
draw_ellipse.ellipse(xy=(0,0,200,300), fill=(0,255,0))
del draw_ellipse # 删除画布
# 2）图像添加文本
draw_text = ImageDraw.Draw(img)
draw_font = ImageFont.truetype(font="arial.ttf", size=23) # 加载 TrueType 或 OpenType 字体，并创建字体对象
draw_text.text(xy = (0,0),text="chenbei",font=draw_font)
#%%
# 3）添加矩形框
draw_rectangle = ImageDraw.Draw(img)
draw_rectangle.rectangle(xy=[100,0,300,100],fill=None,outline="green") # （X，Y，W，H）格式
img.show()
del draw_text ,draw_font
#%%（5）图像的基本信息
img_stat = ImageStat.Stat(img)
# 1） RGB每个通道像素最大和最小值
print("pixel max_min_values : " , img_stat._getextrema())
# 2） 通道像素个数
print("pixel counts : " , img_stat._getcount())
# 3） 像素平均值,中位值,方差
print(f"pixel mean {img_stat._getmean()} \npixel median {img_stat._getmedian} \npixel stddev {img_stat._getstddev()}")
#%%（6）图像叠加
# 像素相乘 要求大小相同 图像叠加到另一个图像的顶部
img_multiply = ImageChops.multiply(img,img1) # out = image1 * image2 / MAX
img_add = ImageChops.add(img,img1) # out = ((image1 + image2) / scale + offset)
img_difference = ImageChops.difference(img,img1) # 检测两张相似图片的差异 out = abs(image1 - image2)
img_subtract = ImageChops.subtract(img,img1) # out = ((image1 - image2) / scale + offset)
img_screen = ImageChops.screen(img,img1) # out = MAX - ((MAX - image1) * (MAX - image2) / MAX) 叠加两个图像负片








