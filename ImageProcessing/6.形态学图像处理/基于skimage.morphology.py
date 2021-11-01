#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 基于skimage.morphology.py
@Author : chenbei
@Date : 2021/9/10 14:19
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
import os
import skimage.io , skimage.color  ,skimage.morphology
import skimage
plt.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
plt.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
plt.rcParams['savefig.dpi'] = 600  # 图片像素
plt.rcParams['figure.dpi'] = 600  # 分辨率
# font_set = FontProperties(fname=r"C:\Windows\Fonts\simsun.ttc", size=10.5)
root = os.path.join(os.getcwd(),"ImageProcessing")
img_dir = os.path.join(root,"images")
def plot_im1_im2(im1,im2,title1="original",title2="reconstruction"):
    fig = plt.figure()
    plt.gray()
    ax1 = fig.add_subplot(121)
    ax2 = fig.add_subplot(122)
    ax1.imshow(im1),ax2.imshow(im2)
    ax1.set_title(title1,size=12),ax2.set_title(title2,size=12)
    ax1.set_axis_off(),ax2.set_axis_off()
    fig.show()
#%% （1）二值图像
im = skimage.color.rgb2gray(skimage.io.imread(img_dir+"\circleflower.jpg"))
im[im < 0.5] = 0
im[im>0.5] = 1
# 1） 腐蚀和膨胀
# ① 腐蚀
selem = skimage.morphology.rectangle(nrows=2,ncols=5) # 生成扁平的矩形结构元素
im_erosion = skimage.morphology.binary_erosion(im,selem=selem)
# plot_im1_im2(im,im_erosion,title2="erosioned")#可以删除时钟的小刻度对象
# ② 膨胀
selem = skimage.morphology.disk(radius=4) # 生成扁平的盘状结构元素
im_dilation = skimage.morphology.binary_dilation(im,selem=selem)
# plot_im1_im2(im,im_dilation)
# 2） 开闭运算
im_opening = skimage.morphology.binary_opening(im,selem=skimage.morphology.disk(12))
im_closing = skimage.morphology.binary_closing(im,selem=skimage.morphology.disk(6))
# plot_im1_im2(im_opening,im_closing)
# eg：使用开闭运算进行指纹清洗 : 先开后闭运算
# 3） 骨架化和凸包运算
im_skeleton = skimage.morphology.skeletonize(im)
im_convex_hull = skimage.morphology.convex_hull_image(im)
# plot_im1_im2(im_convex_hull,im_skeleton)
convex_hull_diff = skimage.img_as_float(im_convex_hull)
convex_hull_diff[im] = 2
# plot_im1_im2(im,convex_hull_diff)
# 4） 删除小对象和提取边界
# ① 删除小对象
for min_size in [50,200,500]:
    im_remove_small_obeject = skimage.morphology.remove_small_objects(im,min_size)
    # plot_im1_im2(im,im_remove_small_obeject)
# ② 提取边界
im_boundary = im - im_erosion
# 5） 白顶帽和黑顶帽运算
selem = skimage.morphology.square(5)# 生成扁平的方形结构元素
im_white = skimage.morphology.white_tophat(im,selem)
im_black = skimage.morphology.black_tophat(im,selem)
# （2）灰度图像 : 和二值函数相同
# 1） 腐蚀和膨胀
# 2） 开闭运算










