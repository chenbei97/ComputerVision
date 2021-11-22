#include "primary.h"
using namespace cv;
void image_histogram_reverse_projection_double()
{
	/*
	反向投影是反应直方图模型在目标图像中的分布情况
	 即用直方图模型在目标图像中寻找是否有相似的对象
	1）从输入图像的左上角(0,0)开始，切割一块(0,0)至(10,10)的临时图像；
（2）生成临时图像的直方图；
（3）用临时图像的直方图和模板图像的直方图对比，对比结果记为c；
（4）直方图对比结果c，就是结果图像(0,0)处的像素值；
（5）切割输入图像从(0,1)至(10,11)的临时图像，对比直方图，并记录到结果图像；
（6）重复（1）～（5）步直到输入图像的右下角。
	 加载图片->转为HSV->计算直方图和归一化->计算反向投影图像

	CV_EXPORTS void calcHist( const Mat* images, int nimages,
						const int* channels, InputArray mask,
						OutputArray hist, int dims, const int* histSize,
						const float** ranges, bool uniform = true, bool accumulate = false );
	*/
	
	
	Mat src = imread(imgAddr + "starry_sky_src.jpg"), templ_hsv,src_hsv;
	Mat templ = imread(imgAddr + "starry_sky_template.jpg");
	cvtColor(templ, templ_hsv, COLOR_BGR2HSV);
	cvtColor(src, src_hsv, COLOR_BGR2HSV);
	int h_bins = 5; int s_bins = 5;
	int histSize[] = { h_bins, s_bins }; // 直方图是二维特征,使用了H、S两个通道
	Mat templ_hist;// 模板图像的直方图

	//取值范围：h为0-180、s取值为0-255、v取值是0-255
	float h_ranges[] = { 0, 180 }; // hue颜色的变化
	float s_ranges[] = { 0, 256 }; // saturation饱和度的变化
	const float* ranges[] = { h_ranges, s_ranges };
	int channels[] = { 0, 1 }; // 同时将2个通道作为共同体进行计算
	calcHist(&templ_hsv, 1, channels, Mat(), templ_hist, 2, histSize, ranges, true, false);
	std::cout <<"templ_hist.size() = "<< templ_hist.size() << std::endl; // 32×32 可以自己选择输出的直方图大小
	// 输出是浮点数组不能用于显示,先归一化到255
	normalize(templ_hist, templ_hist, 0, 255, NORM_MINMAX, -1, Mat()); // 0-255归一化

	int nimages = 1;
	int dims = 1;
	double scale = 1.0;
	bool uniform = true;
	Mat backImage; // 使用模板直方图反向投射源图像得到新的图像
	calcBackProject(&src_hsv,nimages,channels, templ_hist,backImage,ranges,scale, uniform);
	std::cout << "src_hsv.size() = " << src_hsv.size() << "   backImage.size() = "<<backImage.size() << std::endl;
	// src_hsv.size() = [1200 x 900]   backImage.size() = [1200 x 900]
	
	imshow("src_hsv", src_hsv);
	imshow("templ_hsv", templ_hsv);
	imshow("backImage", backImage);
	waitKey(0);
	destroyAllWindows();

}