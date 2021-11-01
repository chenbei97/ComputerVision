#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 哈里斯角点检测器.py
@Author : chenbei
@Date : 2021/9/10 16:13
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
import numpy as np
import os
import skimage.io, skimage.color, skimage.exposure, skimage.transform, \
    skimage.restoration, skimage.measure, skimage.util, skimage.metrics, \
    skimage.filters, skimage.feature, skimage.transform, skimage.morphology
import skimage
import matplotlib.pylab as pylab
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
def plot_im1_im2(im1,im2,title1="original",title2="reconstruction"):
    fig = plt.figure()
    plt.gray()
    ax1 = fig.add_subplot(121)
    ax2 = fig.add_subplot(122)
    ax1.imshow(im1),ax2.imshow(im2)
    ax1.set_title(title1,size=12),ax2.set_title(title2,size=12)
    ax1.set_axis_off(),ax2.set_axis_off()
    fig.show()
def plot_ax(im,ax,title):
    ax.imshow(im),ax.set_title(title,size=12),ax.set_axis_off()
#%% 计算角测量响应图像
im = skimage.io.imread(img_dir+r"\playfootball.jpg")
im_grey = skimage.color.rgb2gray(im)
# method : 从自相关矩阵计算响应图像的方法 ,'k' or 'eps'
# k : 将角与边缘分开的灵敏度因子 [0,0.2] 较小的 k 值会导致检测到尖角
corner = skimage.feature.corner_harris(im_grey,k=0.001,method='k')# 返回角测量响应图像
# plot_im1_im2(im,corner)  # cornor角点像素不为0
im_re = im.copy()
im_re[corner>0.01*corner.max()]= [255,0,0] # 角点像素变为红色 corner.max()=8.787
corner[corner>0.01*corner.max()] = 1.
plot_im1_im2(im,im_re)
peaks = skimage.feature.corner_peaks(corner, min_distance=1) # 算角测量响应图像的峰值
# peaks_local = skimage.feature.peak_local_max(corner,min_distance=1) # 坐标全部找到
subpix = skimage.feature.corner_subpix(im_grey,peaks,window_size=11) # 以子像素准确率决定是否细化角点
# 绘制细分前后的角点
fig ,axes = pylab.subplots(1,2)
axes = axes.flatten()
titles = ['cornor','image']
for img ,axe,title,line,label,marker in zip([corner,im],axes,titles,[subpix,peaks],["细分角点","非细分角点"],['v','+']):
    plot_ax(img,axe,title)
    plt.scatter(line[:,1],line[:,0],label=label,marker=marker)
plt.legend()
fig.show()
#%% 基于RANSAC算法的哈里斯角点特征鲁棒图像匹配
im = skimage.io.imread(img_dir+r"\playfootball.jpg")
im_grey = skimage.color.rgb2gray(im)
# 定义一个二维仿射变换(逆变换)
affine = skimage.transform.AffineTransform(scale=(0.8,0.9),rotation=0.1,translation=(120,-20))
im_warped = skimage.transform.warp(im,affine.inverse,output_shape=im.shape)
# plot_im1_im2(im,im_warped)
im_warped_grey = skimage.color.rgb2gray(im_warped)
# 1）提取原始图像角点和仿射变换后的角点位置
def extract_cornor(im_grey):
    # 传入原始或者仿射变换后的灰度图
    cornor = skimage.feature.corner_harris(im_grey)
    cornor[cornor>0.01*cornor.max()] = 1. # 角图像
    cornor_xy = skimage.feature.corner_peaks(cornor,threshold_rel=0.0001,min_distance=5)#角点坐标
    cornor_subpix = skimage.feature.corner_subpix(im_grey,cornor_xy,window_size=9)# 细分角点
    return cornor_xy,cornor_subpix
cornor_origin_peaks,cornor_origin_subpixs = extract_cornor(im_grey) # 角点坐标 和 细分角点 前者不会出现nan值
cornor_warp_peaks,cornor_warp_subpixs = extract_cornor(im_warped_grey)
def gaussian_weight(window_ext,sigma=1):
    # 对指定窗口大小生成对应的二维高斯权重
    y , x = np.mgrid[-window_ext:window_ext+1,-window_ext:window_ext+1] # 默认步长1
    guassianWeight = np.zeros(y.shape,dtype=np.double)
    guassianWeight[:] = np.exp(-0.5*(x**2/sigma**2+y**2/sigma**2))
    constant = np.sqrt(2 * np.pi * sigma * sigma)
    return guassianWeight/constant
def match_cornor(cornor_origin_subpix , window_ext=3):
    # 输入的cornor_origin_subpix为元组对象(x1,y1)...(x_645,y_645)，原始图像的细分角点坐标对
    x , y = np.round(cornor_origin_subpix).astype(np.intp) # 取整,cornor可能为nan
    # print(f'x={x} y={y}')
    window = im[ x - window_ext : x + window_ext + 1 , y - window_ext : y + window_ext + 1 , :] # 窗口图像
    weight = gaussian_weight(window_ext,sigma=3)
    weights = np.dstack((weight,weight,weight)) # 新维度堆叠成为处理彩色图像的三维高斯权重(每个通道都是二维高斯)
    SSDS = []
    for warp_x , warp_y in cornor_warp_peaks : # 仿射图像的非细分坐标对(没有NAN)(u1,v1)...(u_513,v_513)
        window_warp = im_warped[warp_x - window_ext : warp_x + window_ext + 1 ,
                      warp_y - window_ext : warp_y + window_ext + 1 ,:]
        # cornor为(nan,nan)时，window.shape为0，所以需要去判断
        # print(f"window_shape{window.shape},window_warp_shape{window_warp.shape}")
        if window.shape == window_warp.shape :
            SSD = np.sum(weights*(window - window_warp)**2) # 两组空间对应的高斯加权平方和 [(x1,y1,z1)-(x2,y2,z2)]^2
            SSDS.append(SSD/ window_ext**2 / 3)
    # print(len(SSDS)) 每个原始图像细分坐标对都会得到1个SSDS，长度为仿射图像的非细分坐标对个数
    min_idx = np.argmin(SSDS) if len(SSDS) > 0 else - 1 # 如果能找到SSDS的话再计算否则返回-1
    # 找到SSDS最小值的位置，也就是距离高斯加权最小
    # 也就是原始图像每个细分角点得到的区域与仿射图像非细分角点得到的区域进行比对
    # 两个区域内的点距离综合最近，可以认为这两个点最近
    # 例如第1个原始图像细分点(x1,y1)=(nan,nan)故返回idx=-1
    # 第2个点(x2,y2)=(357.746,386.269)，不是nan开始计算，根据计算结果返回idx=487
    # 含义是(x2,y2)和仿射变换后的图像角点坐标(u_487,v_487)更接近
    if min_idx >=0 :
        return cornor_warp_subpixs[min_idx] # 此时返回细分角点后的坐标,可能是(nan,nan)
    else :
        return [None] # idx=-1返回[None]
# 2）误差平方加权和 匹配原始图像和仿射图像的细分角点后
# 匹配上返回坐标，否则返回[None]
source,destination = [],[] # 变换前后图像的关键点
def match(source,destination):
    for cornor_origin_subpix in cornor_origin_subpixs : # 每个原始的细分坐标对执行循环
        tem = match_cornor(cornor_origin_subpix)
        if any(tem) and not all(np.isnan(tem)):
            # print(tem, any(tem), all(np.isnan(tem)))  # any(tem)判断不是None,all(np.isnan(tem))都不是nan
            source.append(cornor_origin_subpix) # 原始图像细分角点
            destination.append(tem) # 仿射图像细分角点
    source,destination = np.array(source),np.array(destination)
    return source,destination
source,destination = match(source,destination)
# 3）RANSAC对仿射模型进行鲁棒估计
model = skimage.transform.AffineTransform()
print("鲁棒估计前的评估结果：",model.estimate(source,destination))
# 使用RANSAC（随机样本一致性）算法使模型拟合数据
# 返回具有最大共识集的最佳模型，归类为“True”的内联线的布尔掩码
# inliers = [False,False,,,..,]
model_robust,inliers = skimage.measure.ransac((source,destination),
                                              skimage.transform.AffineTransform,
                                              min_samples=3,# 适拟合模型的最小数据点数
                                              residual_threshold=2,# 将数据点分类为输入点的最大距离
                                              max_trials=70) # 随机样本选择的最大迭代次数
# print("鲁棒估计后的评估结果：",model_robust.estimate(source,destination))
def print_info(model,info):
    print(info+f"：scale={model.scale} translation={model.translation} rotation={model.rotation}")
for m,info in zip ([affine,model,model_robust],['实际的仿射模型',"估计的仿射模型",'RANSAC稳健仿射模型']):
    print_info(m,info)
# 4）可视化正确与错误的对应点
outliers = inliers == False # 取反
inliers_idx = np.nonzero(inliers)[0] # 返回为True的索引位置,返回元组对象的第[0]
outliers_idx = np.nonzero(outliers)[0]
# np.column_stack((inliers_idx,inliers_idx)) 添加新列，还是1行
fig ,axes = plt.subplots(1,2)
skimage.feature.plot_matches(ax=axes[0],
                             image1=im_grey,image2=im_warped_grey,
                             keypoints1=source,keypoints2=destination,
                             matches=np.column_stack((inliers_idx,inliers_idx)),keypoints_color='y',matches_color=None)
skimage.feature.plot_matches(ax=axes[1],
                             image1=im_grey,image2=im_warped_grey,
                             keypoints1=source,keypoints2=destination,
                             matches=np.column_stack((outliers_idx,outliers_idx)),keypoints_color='y',matches_color=None)
axes[0].set_title('Correct'),axes[1].set_title('Wrong')
axes[0].set_axis_off(),axes[1].set_axis_off()
fig.show()
