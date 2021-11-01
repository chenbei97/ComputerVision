#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 典型图像分割算法介绍.py
@Author : chenbei
@Date : 2021/9/16 15:26
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
from matplotlib.font_manager import FontProperties
myfont = FontProperties(fname=r"C:\Windows\Fonts\simsun.ttc", size=10.5)
import numpy as np
import os
import skimage.io, skimage.color, skimage.filters, skimage.segmentation
import skimage
from matplotlib.colors import LinearSegmentedColormap
import SimpleITK as sitk
plt.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
mpl.rcParams['font.size'] = 10.5  # 图片字体大小
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
mpl.rcParams['agg.path.chunksize'] = 10000
plt.rcParams['figure.figsize'] = (7.8, 3.8)  # 设置figure_size尺寸
plt.rcParams['savefig.dpi'] = 600  # 图片像素
plt.rcParams['figure.dpi'] = 600  # 分辨率
root = os.path.join(os.getcwd(), "ImageProcessing")
img_dir = os.path.join(root, "images")
horse = skimage.io.imread(img_dir+"\horse.jpg")
grey = skimage.color.rgb2gray(horse)
def plot_im1_im2(im1,im2,title1="original",title2="reconstruction"):
    fig = plt.figure()
    plt.gray()
    ax1 = fig.add_subplot(121)
    ax2 = fig.add_subplot(122)
    ax1.imshow(im1),ax2.imshow(im2)
    ax1.set_title(title1,size=12),ax2.set_title(title2,size=12)
    ax1.set_axis_off(),ax2.set_axis_off()
    fig.show()
#%% （1）基于费尔森茨瓦布高效图
# 计算 Felsenszwalb 基于图形的高效图像分割
# scale - 自由参数。 更高意味着更大的集群
# sigma – 预处理中使用的高斯核的宽度（标准偏差）
# min_size – 最小组件尺寸。 使用后处理强制执行
# multichannel – 图像的最后一个轴是否被解释为多个通道。 当前不支持 3D 图像的 False 值
# 返回指示段标签的整数掩码[0,255]之间 (width, height) ndarray
label_img = skimage.segmentation.felzenszwalb(grey,scale=100,sigma=0.5,min_size=400)
# 返回布尔数组，其中标记区域之间的边界为 True（只返回边界像素为真的掩码）
# Return bool array where boundaries between labeled regions are True
border = skimage.segmentation.find_boundaries(label_img=label_img)
# 利用set或者unique返回强度的分布
pixel_indensity = np.unique(label_img.ravel()) # set(label_img.ravel())也可
label_img[border] = 0 # 边界像素设为0
# 返回带有突出显示标记区域之间边界的图像（边界直接高亮的图像）
# Return image with boundaries between labeled regions highlighted
im_felzenszwalb = skimage.segmentation.mark_boundaries(grey,label_img=label_img)
plot_im1_im2(label_img,im_felzenszwalb)
#%% （2）基于SLIC
# 在 Color-(x,y,z) 空间中使用 k-means 聚类分割图像
# n_segments – 分割输出图像中的（近似）标签数量
# compactness - 平衡颜色接近度和空间接近度。 较高的值赋予空间邻近性更多的权重，使超像素形状更加方形/立方体。
# max_iter – k-means 的最大迭代次数
# sigma – 用于对图像每个维度进行预处理的高斯平滑内核的宽度
# 在标量值的情况下，相同的 sigma 应用于每个维度 零意味着没有平滑
# 返回指示段标签的整数掩码[]不在0-255范围所以不使用find_boundaries 2D or 3D array
label_img = skimage.segmentation.slic(image=horse, compactness=100, n_segments=50)
seg_slic = skimage.segmentation.mark_boundaries(horse,label_img=label_img)
plt.imshow(seg_slic),plt.show()
#%% （3）基于快速移位QuickShift
# 在 Color-(x,y) 空间中使用 quickshift 聚类分割图像
# ratio – 平衡色彩空间接近度和图像空间接近度。 较高的值赋予色彩空间更多的权重
# kernel_size – 用于平滑样本密度的高斯核的宽度。 更高意味着更少的集群
# max_dist – 数据距离的截止点。 更高意味着更少的集群
# return_tree – 是否返回完整的分割层次树和距离
# sigma – 作为预处理的高斯平滑宽度。 零意味着没有平滑
# 返回指示段标签的整数掩码 (width, height) ndarray
i = 1
Label_img = []
for max_dist in [5,500]:
    for ratio in [0.1,0.9] :
        plt.subplot(2,2,i)
        label_img = skimage.segmentation.quickshift(horse,kernel_size=3,
                                                         max_dist=max_dist,ratio=ratio,sigma=1.0)
        seg_quickshift = skimage.segmentation.mark_boundaries(horse,label_img=label_img)
        border = skimage.segmentation.find_boundaries(label_img=label_img)
        label_img[border] = 0
        Label_img.append(label_img)
        plt.imshow(seg_quickshift)
        plt.title('max_dist = '+ str(max_dist)+' ratio = '+ str(ratio))
        i += 1
plt.show()
plot_im1_im2(Label_img[0],Label_img[1])
plot_im1_im2(Label_img[2],Label_img[3])
#%% （4）基于紧凑型分水岭
# 在从给定的标记淹没的图像中查找流域盆地
# markers – 所需的标记数量，或使用要在标签矩阵中分配的值标记盆地的数组
# 零意味着不是标记。 如果无（没有给出标记），图像的局部最小值被用作标记
# connectivity – 与图像具有相同维数的数组，其非零元素表示连接的邻居
# 遵循 scipy 约定，默认是图像维度的单连通数组
# compactness – 使用具有给定紧凑性参数的紧凑分水岭 更高的值会导致更规则形状的流域盆地
# 返回与标记具有相同类型和形状的标记矩阵 ndarray
gradient = skimage.filters.sobel(grey) # 分水岭算法必须使用灰度图求梯度
i = 1
for markers in [200,1000]:
    for compactness in [0.001,0.0001] :
        plt.subplot(2,2,i)
        label_img = skimage.segmentation.watershed(image=gradient,markers=markers,compactness=compactness)
        seg_watershed = skimage.segmentation.mark_boundaries(horse,label_img=label_img)
        plt.imshow(seg_watershed)
        plt.title('markers = '+ str(markers)+' compactness = '+ str(compactness),size=10)
        i += 1
plt.show()
#%% （5）基于SimpleTK的区域生长
# 一个像素的邻域强度与当前像素强度相似，则认为处于同一分割片段
# 用一个固定的种子点启动算法，改变上阈值查看分割效果
# 上阈值越大，得到的分割区域越大
head = skimage.io.imread(img_dir+"\head.png")
head_grey = skimage.color.rgb2gray(head) * 255
head_sitk = sitk.GetImageFromArray(head_grey) # 从 numpy 数组中获取 SimpleITK 图像
head_sitk_cast = sitk.Cast(sitk.RescaleIntensity(head_sitk),sitk.sitkUInt8)
seed = (200,300) # 初始像素集（种子点），根据图片情况需要手动选择
lower_threshold = 20
upper_threshold = [40,55,80]
for upper in upper_threshold:
    plt.figure()
    plt.subplot(131)
    plt.imshow(head)
    plt.scatter(seed[0],seed[1],color='red',s=50,label='initial pixel set')
    plt.title("original image upper = " +str(upper))
    plt.legend()
    seg_connectthreshold = sitk.ConnectedThreshold(head_sitk,
                                                   seedList=[seed],
                                                   lower = lower_threshold,
                                                   upper = upper)
    seg_connected_threshold = sitk.LabelOverlay(head_sitk_cast,seg_connectthreshold)
    plt.subplot(132)
    seg_connectthreshold = sitk.GetArrayFromImage(seg_connectthreshold)
    seg_connected_threshold = sitk.GetArrayFromImage(seg_connected_threshold)
    plt.imshow(seg_connectthreshold)
    plt.title("region growing upper = " + str(upper))
    plt.subplot(133)
    plt.imshow(seg_connected_threshold)
    plt.title("connected threshold upper = " + str(upper))
plt.show()
#%% （6）基于活动轮廓学蛇算法
# snake - 初始蛇坐标。 对于周期性边界条件，端点不得重复
# alpha – 蛇的长度形状参数。 较高的值使蛇收缩更快
# beta – 蛇形平滑度形状参数。 较高的值使蛇更平滑
# w_line – 控制对亮度的吸引力。 使用负值来吸引黑暗区域
# w_edge – 控制对边缘的吸引力。 使用负值从边缘排斥蛇
# gamma – 显式时间步进参数
# max_px_move – 每次迭代移动的最大像素距离
# max_iterations – 优化蛇形的最大迭代次数
# convergence - 收敛标准
im = skimage.data.astronaut()
im_gray = skimage.color.rgb2gray(im)
im_filter = skimage.filters.gaussian(im_gray,3) # 先平滑处理一下
# 生成初始轮廓
center = (220,100)
# # (220,100)是脸部区域的中心点
radius = 100 # 浮动半径100
num = 600 # 轮廓点个数
s = np.linspace(0,2*np.pi,num) # 2pi是为了凑圆
x = center[0] + radius * np.cos(s) # 左右浮动
y = center[1] + radius * np.sin(s) # 上下浮动
init = np.array([x,y]).T
i = 1
for max_iterations in [20,30,50,100]:
    snake = skimage.segmentation.active_contour(image=im_filter,
                                                snake=init,
                                                alpha=0.015,
                                                beta=10,
                                                gamma=0.001,
                                                max_iterations=max_iterations)
    plt.subplot(2,2,i)
    plt.imshow(im_filter)
    plt.plot(init[:,0],init[:,1],color='b',linestyle='--',linewidth=1.5)
    plt.plot(snake[:,0], snake[:,1],color='r',linestyle='-',linewidth=1.)
    i += 1
plt.show()
#%% （7）基于形态学蛇算法
# ① 形态学测地线活动轮廓 MorphGAC
# 要求图像轮廓清晰，所以需要预处理，可以使用高斯梯度反变换
# skimage.segmentation.inverse_gaussian_gradient
# ② 形态学无边缘活动轮廓 MorghACWE
# 不要求图像轮廓清晰，可以直接使用
def store_evolution(lst):
    def store(x):
        lst.append(np.copy(x))
    return store
evolution_acwe = []
evolution_gac = [] # 储存水平集
# MorghACWE算法创建一个带有二进制值的棋盘级别集 ,棋盘的二元水平集
init_level_set = skimage.segmentation.checkerboard_level_set(image_shape=grey.shape, square_size=5)
callback_acwe = store_evolution(evolution_acwe)
callback_gac = store_evolution(evolution_gac)
level_set_acwe = skimage.segmentation.morphological_chan_vese(
                            image=grey, iterations=30, init_level_set=init_level_set,
                            smoothing=1, lambda1=1, lambda2=1,
                            iter_callback=callback_acwe)
# MorphGAC算法需要预处理： 高斯梯度反变换
gimage = skimage.segmentation.inverse_gaussian_gradient(grey)
level_set_gac = skimage.segmentation.morphological_geodesic_active_contour(
                                          gimage=gimage, iterations=30,
                                          init_level_set=init_level_set, smoothing=1,
                                          threshold=0.7, balloon=-1,
                                          iter_callback=callback_gac)
fig , axes = plt.subplots(2,2)
axes = axes.flatten()
# ACWE算法
axes[0].imshow(grey),axes[0].contour(level_set_acwe,[0.5],color='r')
axes[1].imshow(level_set_acwe)
contour = axes[1].contour(evolution_acwe[5],[0.5],colors='g')
contour.collections[0].set_label("Iteration 5")
contour = axes[1].contour(evolution_acwe[10],[0.5],colors='y')
contour.collections[0].set_label("Iteration 10")
contour = axes[1].contour(evolution_acwe[-1],[0.5],colors='b')
contour.collections[0].set_label("Iteration 30")
axes[1].legend(prop=myfont,loc="upper right")
axes[1].set_title("MorghACWE")
# GAC算法
axes[2].imshow(grey),axes[2].contour(level_set_gac,[0.5],colors='r')
axes[3].imshow(level_set_gac)
contour = axes[3].contour(evolution_gac[5],[0.5],colors='g')
contour.collections[0].set_label("Iteration 5")
contour = axes[3].contour(evolution_gac[10],[0.5],colors='y')
contour.collections[0].set_label("Iteration 10")
contour = axes[3].contour(evolution_gac[-1],[0.5],colors='b')
contour.collections[0].set_label("Iteration 30")
axes[3].legend(prop=myfont,loc="upper right")
axes[3].set_title("MorghGAC")
fig.tight_layout()
fig.show()
#%% （8）基于GrabCut(cv2)
# 书P250页不再给出









