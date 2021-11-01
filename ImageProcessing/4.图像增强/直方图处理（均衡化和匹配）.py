#%%
# -*- coding UTF-8 -*-
'''
@Project : TensorflowStudy
@File : 直方图处理（均衡化和匹配）.py
@Author : chenbei
@Date : 2021/9/3 16:56
'''
import matplotlib.pyplot as plt
from matplotlib.pylab import mpl
from matplotlib.font_manager import FontProperties
import numpy as np
import os
import numpy
import skimage.io , skimage.color , skimage.exposure ,skimage.data ,\
    skimage.restoration ,skimage.measure,skimage.util
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
font_set = FontProperties(fname=r"C:\Windows\Fonts\simsun.ttc", size=10.5)
root = os.path.join(os.getcwd(),"ImageProcessing")
img_dir = os.path.join(root,"images")
def plot_image(im=None,freq=None,isfreq=False,allplot=False,isre=False):
    if im is None and freq is None:
        print("at least one input")
        return None
    if freq is not None :
        assert type(freq) == numpy.ndarray
        if np.max(freq) > 1 :# 说明是uint8型图像
            freq = np.clip(freq.real, 0, 255)
        else:
            freq = np.clip(freq.real,0,1)
    if im is not None:
        assert type(im) == numpy.ndarray
        if isre : # 如果输入的是重建后的图像,一般是complex128,需要取实部
            im = im.real
        else:
            if np.max(im) > 1 :
                im = np.clip(im,0,255)
            else:
                im = np.clip(im,0,1)
    if allplot :
        fig , (ax1,ax2) = pylab.subplots(1,2)
        ax1.imshow(im, cmap='gray') ,ax1.axis('off'),ax1.set_title("time")
        ax2.imshow((20 * np.log10(np.where(freq <= 0, 0.1, freq))).astype(int), cmap='gray')
        ax2.axis('off'), ax2.set_title("freq")
    else:
        if not isfreq :
            pylab.imshow(im,cmap='gray')
        else:
            pylab.imshow((20*np.log10(np.where(freq<=0 , 0.1 ,freq))).astype(int),cmap='gray')
        pylab.axis('off')
    pylab.show()
def plot_image_hist(ims,axes,fig,bins=256):
    # ① 成对绘制 拆分坐标轴一上一下 分别绘制原图和像素强度图
    def spilit_axes(axes,idx):
          return axes[:,idx]
    # ② 对成对的坐标轴轴解包,并生成双y轴
    def spilit_image_hist(axes,idx) :
        ax_image , ax_hist = spilit_axes(axes,idx)
        ax_percent = ax_hist.twinx()
        return ax_image , ax_hist , ax_percent
    # ③ 对 image设置参数
    def set_image_params(img,ax_image,title) :
        ax_image.imshow(img,cmap=plt.cm.gray),ax_image.set_axis_off()
        ax_image.set_title(title,size=12)
        return ax_image
    # ④ 对 hist设置参数
    def set_hist_params(img,ax_hist) :
        ax_hist.hist(img.ravel(), bins=bins, histtype='step', color='black')
        ax_hist.set_xlim(0, 1)  # 像素分布在[0,1]
        ax_hist.set_xlabel("pixel intensity",size=12)
        ax_hist.set_ylabel("", size=12)
        ax_hist.ticklabel_format(axis='y',style='scientific',scilimits=(0,0)) # 对y轴使用科学计数法,且(0,0)默认使用所有数字
        ax_hist.set_yticks([])# 默认没有刻度,上级函数可以根据idx来调用本函数对不同的坐标轴进行设置,如第5和第8个图才设置
        return ax_hist
    # ⑤ 对 twinx()设置参数
    def set_twinx_params(img,ax_twinx,bins=bins):
        img_cd , bins  = skimage.exposure.cumulative_distribution(img,bins)# 累积分布系数计算
        ax_twinx.plot(bins,img_cd,'r')
        ax_twinx.set_yticks([])
        ax_twinx.set_ylabel("",size=12)
        return ax_twinx
    # ⑥ 对每个上下图进行处理
    def set_params(axes,im,idx) :
        titles = ["Original","Stretch","Globalequ","Adaptequ"]
        img = skimage.img_as_float(im)  # 对每个img归一化到[0,1]
        ax_image , ax_hist , ax_percent = spilit_image_hist(axes,idx) # 对当前img拆分得到4个轴
        ax_image = set_image_params(img,ax_image,titles[idx]) # 对image轴设置参数
        ax_hist = set_hist_params(img,ax_hist) # 对hist轴设置参数
        ax_percent = set_twinx_params(img,ax_percent) # 对twinx轴设置参数
        # 单独设置
        if idx == 0 :
            hist_y_min,hist_y_max = ax_hist.get_ylim()
            ax_hist.set_yticks(np.linspace(0,hist_y_max,5)) # 对左y轴设置5等分显示
            ax_hist.set_ylabel("num of pixs") # 像素频率
        if idx == 3 :
            ax_percent.set_yticks(np.linspace(0,1,5)) # 累积分布系数0-1
            ax_percent.set_ylabel("percent") # 总强度分数
    # ⑦ 主程序绘图
    for im , idx in enumerate(ims):
        set_params(axes,idx,im)
    fig.tight_layout()
    pylab.show()
#%%
# （1）基于skimage的对比度拉伸和直方图均衡化
# 1）核心代码 : 原始+拉伸+全局均衡+自适应均衡
im = skimage.color.rgb2gray(skimage.io.imread(img_dir + r"\chairs.png"))
def return_image_enhance(im,in_range_max=100,clip_limit=0.03):
    im_rescale = skimage.exposure.rescale_intensity(im,in_range=(0,in_range_max),out_range=(0,255)) # 输入和输出图像的最小和最大强度值
    im_eq = skimage.exposure.equalize_hist(im)
    im_adapteq = skimage.exposure.equalize_adapthist(im,clip_limit=clip_limit)# clip_limit 裁剪限制，在 0 和 1 之间归一化
    ims = [im,im_rescale,im_eq,im_adapteq]
    return ims
# 2）生成绘制8个图像的坐标轴 按(2,4)分布
def return_fig_axes():
    fig = pylab.figure()
    axes = []
    for i in range(8):
        if 0 < i < 4 :
            axes.append(fig.add_subplot(2,4,i+1,sharex=axes[0],sharey=axes[0]))
        else:
            axes.append(fig.add_subplot(2, 4, i + 1))
    axes = np.reshape(axes,(2,4))
    return fig,axes
# 3）可视化函数
# ① 比较不同的in_range_max影响
def compare_in_range_max():
    in_range_maxs = [50,100,150,200,250]
    for in_range_max in in_range_maxs :
        fig,axes = return_fig_axes()
        ims = return_image_enhance(im,in_range_max=in_range_max)
        plot_image_hist(ims,axes,fig)
# compare_in_range_max()
# ② 比较不同的clip_limit影响
def compare_clip_limits():
    clip_limits = np.linspace(0,0.01,10)
    for clip_limit in clip_limits :
        fig,axes = return_fig_axes()
        ims = return_image_enhance(im,clip_limit=clip_limit)
        plot_image_hist(ims,axes,fig)
compare_clip_limits()
# （2）直方图匹配
#%%
im = (skimage.color.rgb2gray(skimage.io.imread(img_dir + r"\beans_g.png"))*255).astype(np.uint8)
im_template = (skimage.color.rgb2gray(skimage.io.imread(img_dir + r"\lena_g.png"))*255).astype(np.uint8) # 匹配的模板
ims = [im,im_template]
# 1）计算cdf分数
def return_cdf(ims) :
    im_cdfs = []
    for im in ims :
        im_cdf , bins = skimage.exposure.cumulative_distribution(im)
        # print(len(set(bins))) bins是一段步长1的序列，表示输出像素强度的所处范围
        im_cdf = np.insert(im_cdf,0,[0] * bins[0]) # 开头插入6个0的序列
        im_cdf = np.append(im_cdf,[1] * (255 - bins[-1] )) # 结尾添加255-237=18个1的序列
        im_cdfs.append(im_cdf)
    return im_cdfs
# 2）计算直方图匹配
def hist_matching(ims):
    im_cdfs = return_cdf(ims) # length = 256 = [0,0,0,0,0,0,0.002,...,1,1,1,1,...,1]
    pixels = np.arange(256)
    # x:要插值的x坐标 xp:数据点的x坐标 fp:数据点的y坐标 返回长度与x相同,即插值的y坐标
    # 模板图像存在映射关系(0,1),(0,2),..,(0,6),..,(1,237),(1,238),...(1,255)
    newpixels = np.interp(x=im_cdfs[0],xp=im_cdfs[1],fp=pixels) # 一维线性插值得到一张映射表
    # newpixels[ims[0].ravel()] 对原始图像每个像素点进行匹配，共99540个
    # 每个像素点的大小作为位置去索引,也就是原本6的像素映射为23了
    newim = (np.reshape(newpixels[ims[0].ravel()],ims[0].shape)).astype(np.uint8)
    return newim , newpixels
# 3）验证累计分数的计算过程
def validate():
    im_flatten = list(im.flatten())
    print(len(set(im_flatten))) # 从输出观察发现确实没有0-5,238-255强度的像素点,且只有115个类型取到
    pixel_min , pixel_max = min(set(im_flatten)) , max(set(im_flatten))
    pixel_num = [im_flatten.count(element) for element in np.arange(pixel_min,pixel_max+1)] # 232
    pixel_cdf = np.array(pixel_num).cumsum() / sum(pixel_num) # sum(pixel_num)=99540
    im_cdf , bins = skimage.exposure.cumulative_distribution(im)
    print(len(set(im_cdf))) # 115
    print(len(pixel_cdf),len(im_cdf)) # (232,232)
    assert np.allclose(im_cdf,pixel_cdf) == True # 两个完全相等
# validate()
# 4）累积分数可视化
new_im,newpixels = hist_matching(ims)
ims = [im,im_template,new_im]
im_cdfs = return_cdf(ims)
for im_cdf,arg,label in zip(im_cdfs,['r.-','g.-','b.-'],['input','template','output'] ):
    plt.plot(im_cdf,np.arange(256),arg,label=label)
plt.legend()
plt.show()

#%%















