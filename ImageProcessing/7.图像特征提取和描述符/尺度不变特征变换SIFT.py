#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 尺度不变特征变换SIFT.py
@Author : chenbei
@Date : 2021/9/10 16:16
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
import os
import skimage.io, skimage.color, skimage.exposure, skimage.data, \
    skimage.restoration, skimage.measure, skimage.util, skimage.metrics, \
    skimage.filters, skimage.feature, skimage.transform, skimage.morphology
import  cv2
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
def load_image(addr):
    im_ori = skimage.color.rgb2gray(skimage.io.imread(img_dir+addr))
    affine = skimage.transform.AffineTransform(scale=(1.2,1.2),translation=(0,-100))
    im_warp = skimage.transform.warp(im_ori,affine)
    im_rotate = skimage.transform.rotate(im_ori,25)
    return im_ori,im_warp,im_rotate
def compute_kp_des(im,n_keypoints,mode):
    assert type(mode) == str
    if mode == 'BRIEF' :
        matcher = skimage.feature.BRIEF()  # BRIEF匹配器
        cornor = skimage.feature.corner_harris(im)
        cornor[cornor > 0.01*cornor.max()] = 1. # 提高对比度
        kp = skimage.feature.corner_peaks(cornor,min_distance=5)
        matcher.extract(im,kp) # 提取关键点
        kp, des = kp[matcher.mask], matcher.descriptors
    elif mode == 'ORB' :
        matcher = skimage.feature.ORB(n_keypoints=n_keypoints) # ORB匹配器
        matcher.detect_and_extract(im)
        kp , des = matcher.keypoints,matcher.descriptors
    else:
        kp , des = [None],[None]
    return kp,des
def plot_image_kp_des(addr,mode='BRIEF',n_keypoints=200):
    # 1）加载三个图像
    im_ori, im_warp, im_rotate = load_image(addr)
    # 2）分别计算三个图像的描述符和关键点
    kp_ori , des_ori = compute_kp_des(im_ori,n_keypoints,mode)
    kp_warp , des_warp = compute_kp_des(im_warp,n_keypoints,mode)
    kp_rotate , des_rotate = compute_kp_des(im_rotate,n_keypoints,mode)
    # 3）匹配原图与仿射、旋转的描述符
    match12 = skimage.feature.match_descriptors(des_ori,des_warp,cross_check=True)
    match13 = skimage.feature.match_descriptors(des_ori,des_rotate,cross_check=True)
    fig ,axes = plt.subplots(1,2)
    skimage.feature.plot_matches(ax=axes[0],
                                 image1=im_ori,image2=im_warp,
                                 keypoints1=kp_ori,keypoints2=kp_warp,
                                 matches=match12[:10],keypoints_color='y',matches_color=None)
    skimage.feature.plot_matches(ax=axes[1],
                                 image1=im_ori,image2=im_rotate,
                                 keypoints1=kp_ori,keypoints2=kp_rotate,
                                 matches=match13[:10],keypoints_color='y',matches_color=None)
    axes[0].set_title('Warp'),axes[1].set_title('Rotate')
    axes[0].set_axis_off(),axes[1].set_axis_off()
    fig.show()
def plot_match_cv2(addr1="\elephant.jpg",addr2="\elephant.png",mode="ORB",isRatio=False,ratio=0.8,k=2):
    im1 = cv2.imread(img_dir+addr1)
    im2 = cv2.imread(img_dir+addr2)
    if mode == "ORB" :
        Matcher = cv2.ORB_create()
        matcher = cv2.BFMatcher(cv2.NORM_HAMMING, crossCheck=True)# 汉明距离适用于ORB、BRIEF
    elif mode == "SIFT":
        Matcher = cv2.SIFT_create()
        matcher = cv2.BFMatcher() # 默认情使用cv2.NORM_L2.适用于SIFT，SURF
    else:
        print("mode only in [ORB,SIFT]")
    kp1 , des1 = Matcher.detectAndCompute(im1,None)
    kp2 , des2 = Matcher.detectAndCompute(im2,None)
    if isRatio:
        matches = matcher.knnMatch(des1,des2,k=k) # 返回k个最佳匹配
        good_matches = []  # 使用比率检验正确的匹配
        for match in matches : # 返回的是列表，列表的每个元素是2个子列表组成
            m1 , m2 = match[0],match[1]
            if m1.distance < ratio * m2.distance: # 计算最近距离和第二最近距离的比率，如果大于给定比率则拒绝
                good_matches.append([m1,m2])
                im_match = cv2.drawMatchesKnn(im1,kp1,im2,kp2,good_matches,None,flags=2)
    else:
        matches = matcher.match(des1,des2) # 返回最佳匹配
        matches = sorted(matches, key=lambda x: x.distance)  # 使用距离指标对匹配线进行排序
        im_match = cv2.drawMatches(im1, kp1, im2, kp2, matches, None, flags=2)
    plt.figure()
    plt.imshow(im_match)
#%%（0）简单了解cv2的sift函数使用
im = cv2.imread(img_dir+"\monalisa.jpg")
gray = cv2.cvtColor(im,cv2.COLOR_BGR2GRAY)
sift = cv2.SIFT_create() # 新版本改动
key_points = sift.detect(gray,None) # 计算关键点
im_key_points = cv2.drawKeypoints(im,key_points,None,flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)#绘制小圆圈及其方向
kp , des = sift.detectAndCompute(gray,None) # 返回关键点和描述符
print(kp == key_points)
cv2.imshow("img",im_key_points)
cv2.waitKey()
#%%（1）基于cv2实现SIFT图像匹配
plot_match_cv2(mode='SIFT')
plt.title("SIFT不使用比率检验")
plt.show()
plot_match_cv2(mode='SIFT',isRatio=True)
plt.title("SIFT使用比率检验")
plt.show()
#%% （2）基于cv2实现ORB图像匹配
plot_match_cv2(mode='ORB')
plt.title("ORB")
plt.show()
#%% （3）基于skimage实现BRIEF匹配
plot_image_kp_des(r"\playfootball.jpg")
#%% （4）基于skimage实现ORB图像匹配
plot_image_kp_des(r"\playfootball.jpg",mode='ORB')











