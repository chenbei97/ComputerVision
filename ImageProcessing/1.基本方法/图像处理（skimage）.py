#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : ImageProcessing（skimage）.py
@Author : chenbei
@Date : 2021/8/31 10:51
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
import numpy as np
import scipy.ndimage
import os
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
address = os.path.join(img_dir,"lena.jpg")
address1 = os.path.join(img_dir,"me.jpg")
root = os.path.join(os.getcwd(),"ImageProcessing")
img_dir = os.path.join(root,"images")
# PIL (width, height) skimage (height,width, channel) 因为数组习惯先行后列对应的为先高后宽
# PIL得到的是PIL对象 skimage的得到的是Numpy对象 通过np.array(PIL)和skimage.Image.fromarray(skimage)相互转换
# matplotlib读取得到的也是Numpy对象
import skimage.io ,skimage.transform ,skimage.util,skimage.color,skimage.feature ,\
    skimage.exposure,skimage.restoration,skimage.measure,skimage.metrics,skimage.filters,\
    skimage.morphology,skimage.draw
# （1）io（2）color（3）exposure（4）restoration（5）util
# （6）transform（7）measure (8) metrics (9)filters (10)feature（11）morphology
# （12）draw
#%%
# （1）io : imread , imshow
img = skimage.io.imread(address)
print(f"height {img.shape[0]} width {img.shape[1]}") # 先高度375 再宽度500
#%% （2）color : rgb2gray rgba2rgb
# 1）灰度图
img_gray = skimage.color.rgb2gray(img)
# 2）四通道->三通道
img = skimage.io.imread(img_dir+"\man.png")
img = skimage.color.rgb2gray(skimage.color.rgba2rgb(skimage.img_as_float(img)))
# 3）标签图像转为RGB
# 标签并不是像素强度，还需要根据标签转换，给定参数标签和被转换对象
label , num_features = scipy.ndimage.label(input=img)
label_invert = skimage.color.label2rgb(label=label,image=img)
#%% （3）exposure
# 1）拉伸、全局均衡、自适应均衡、累积分布系数
im_stretch = skimage.exposure.rescale_intensity(img,in_range=(0,100),out_range=(0,255)) # 输入和输出图像的最小和最大强度值
im_eq = skimage.exposure.equalize_hist(img) # 全局均衡
im_adapteq = skimage.exposure.equalize_adapthist(img,clip_limit=0.03) # 自适应均衡
img_cd , bins  = skimage.exposure.cumulative_distribution(img,256) # 累积分布系数
#%% （4）restoration
# 1）维纳滤波器
n2 = 2
filter2 = np.ones((n2,n2)) / n2**2
img_wena = skimage.restoration.unsupervised_wiener(img,psf=filter2)
# 2）双边滤波器
img_bila = skimage.restoration.denoise_bilateral(img)
# 3）（高斯）噪声标准偏差的稳健的基于小波的估计器
img_noise = img +  0.25*np.random.standard_normal(img.shape)
img_noise = np.clip(img,0,1)
sigma_est = np.mean(skimage.restoration.estimate_sigma(img_noise,multichannel=True))
print("噪声标准差：%.5f" % (sigma_est))
# 4）非局部均值去噪
pacth_kw = dict(patch_size=5,patch_distance=6,multichannel=True) # 定义一个打包参数字典，指定斑块的大小和之间的距离
#     ① 慢速算法
img_denoise_slow = skimage.restoration.denoise_nl_means(img_noise,h=1.15*sigma_est,
                                                        fast_mode=False,**pacth_kw)
#     ② 快速算法
img_denoise_fast = skimage.restoration.denoise_nl_means(img_noise,h=0.8*sigma_est,
                                                        fast_mode=True,**pacth_kw)
psnr = skimage.metrics.peak_signal_noise_ratio(img,img_noise)
#%%
# （5）util
# 1）添加随机高斯噪声
img_add_random_noise = skimage.util.random_noise(image=skimage.img_as_float(img), mode='gaussian',
                                                 seed=None, clip=True,var=0.5**2)
skimage.io.imshow(img_add_random_noise),plt.axis('off'),skimage.io.show()
#%%
# （6）transform
# 1）相似变换
SimilarityTransform = skimage.transform.SimilarityTransform(matrix=None, scale=0.9, rotation=np.pi/4,
                 translation=(img.shape[0]/2,-100))
img_wrap = skimage.transform.warp(image=img,inverse_map=SimilarityTransform)
skimage.io.imshow(img_wrap),plt.axis('off'),skimage.io.show()
# 2）旋流变换 swirl transform strength旋流量参数 radius以像素表示旋流程度
img_swirl = skimage.transform.swirl(img, radius=200, rotation=0, strength=15)
skimage.io.imshow(img_swirl),plt.axis('off'),skimage.io.show()
# 3）缩放图像
im_rescale = skimage.transform.rescale(img, scale=0.5,multichannel=True,anti_aliasing=False)
# 4）拉普拉斯金字塔
im_laplace_generator = skimage.transform.pyramid_laplacian(img)
# 5）高斯金字塔
im_guass_generator = skimage.transform.pyramid_gaussian(img)
# 6）平滑向下采样
# skimage.transform.pyramid_reduce()
# 7）向上采样平滑
# skimage.transform.pyramid_expand()
# 8）仿射变换
affine = skimage.transform.AffineTransform()
#%%
# （7）measure
# skimage.measure.ransac RANSAC随机抽样一致性算法对参数鲁棒估计
# （8）metrics
# 1）峰值信噪比 PSNR
# psnr = skimage.metrics.peak_signal_noise_ratio(img,img_noise)
#%%
# （9）filters
# 1）边缘检测器
im_laplace = np.clip(skimage.filters.laplace(img) + img ,0,1) # 拉普拉斯滤波后锐化
im_x = skimage.filters.sobel_h(img) # 使用了水平右掩膜
im_y = skimage.filters.sobel_v(img) # 使用了垂直下掩膜
im_xy = skimage.filters.sobel(img) # 2个方向均使用
im_sobel = skimage.filters.sobel(img)
im_roberts = skimage.filters.roberts(img)
im_prewitt = skimage.filters.prewitt(img)
im_scharr = skimage.filters.scharr(img)
# skimage.filters.roberts_pos_diag() # 水平方向
# skimage.filters.roberts_neg_diag() # 垂直方向
# skimage.filters.scharr_h()
# skimage.filters.scharr_v()
# skimage.filters.prewitt_v() # 乘了1/3
# skimage.filters.prewitt_h()
# 2）形态学对比图提升、中值滤波和计算局部熵
skimage.filters.rank.enhance_contrast(img,skimage.morphology.disk(5))
skimage.filters.rank.median(img,skimage.morphology.disk(5))
skimage.filters.rank.entropy(img,skimage.morphology.disk(5))
# 3）直方图求解二值化阈值
threshold = skimage.filters.threshold_otsu(img)
#%%
# （10）feature
# 1）边缘检测canny
im_canny = skimage.feature.canny(img,sigma=3)
# 2）哈里斯角点检测
# skimage.feature.corner_harris
# skimage.feature.corner_peaks
# skimage.feature.peak_local_max
# skimage.feature.corner_subpix
# 3）BRIEF和ORB匹配器
matcher = skimage.feature.BRIEF()
matcher_ = skimage.feature.ORB(n_keypoints=200)
matcher.detect_and_extract(img)
# matcher.extract(im,kp)
# 4）绘制匹配线plot_matches
# 5）匹配器match_descriptors
kp , des = matcher.keypoints,matcher.descriptors
# 6）计算类Haar特征的坐标
# skimage.feature.haar_like_feature_coord
# 7）类Haar特征的可视化
# skimage.feature.draw_haar_like_feature
#%%
# （11）morphology
# 详细见<基于skimage.morphology.py>文件
#%%（12）draw
# 1）circle_perimeter 绘制圆坐标函数
im = np.zeros((10,10))
radius = 3
rr,cc = skimage.draw.circle_perimeter(r=im.shape[0]//2,c=im.shape[1]//2,radius=radius)
pixels = np.vstack((rr,cc)).T
plt.imshow(im)
for pixel in pixels :
    plt.scatter(pixel[0],pixel[1])
plt.show()
# # 点的密集度测试
# for radius in [1,2,3,4,5,6,7] :
#     a,b = skimage.draw.circle_perimeter(5,5,radius=radius)
#     print(len(a),len(b)) # 8倍关系，这说明每扩大一个半径增加8个采样点
# 2）

# （12）其他
img_uint8 = skimage.img_as_ubyte(img)
img_float = skimage.img_as_float(img)

