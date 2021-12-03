#include "primary.h"
using namespace cv;
void image_hist_correct()
{
	Mat src = imread(imgAddr + "me.jpg");

	int nimages = 1; // 从结果来看取1和取3貌似没区别,可能是内部机制原因
	int channels[] = { 0,1,2}; // src的通道0,1,2，依据测试结果0,1,2表示这个图的第几通道
	int* pchannel = channels; // 指向一维普通数组的指针
	Mat mask = Mat();
	std::vector<Mat> hist(src.channels());// 输出的应当是3个图片的直方图 3个1维的 , 3×256
	int dims = 1; //一维的,二维可能会得到256*256
	int bins = 256; // 灰度图的直方图一般是一维的,长度是256
	int histsizes[] = {bins,bins,bins}; // 每个图的直方图尺寸都是1维256长度
	int* histSize = histsizes;
	float range_b[] = { 0,256 };
	float range_g[] = { 0,256 };
	float range_r[] = { 0,256 }; // 每个通道的上下限都是0-256
	const float* range_bgr[] = { range_b ,range_g,range_r}; // 一维指针数组 存放每个通道上下限数组的地址,必须是const型
	const float** ranges = range_bgr; // 指向一维指针数组本身的**指针,ranges++或者ranges[1]访问的都是元素range_g本身
	std::cout << ranges[1] << "   " << range_g << "   " << &range_g[0] << "   " << std :: endl;
	bool uniform = true;
	bool accumulate = false;
	
	for (int i = 0; i < hist.size(); i++)
	{
		calcHist(&src, nimages, pchannel++, mask, hist[i], dims, histSize++, ranges, uniform, accumulate);
		// std::cout << hist[i].size() << std::endl; // [1×256]
		//std::cout << hist[i] << std::endl;
	}
	
	double maxval[3] = {0,0,0}; // 计算一维直方图的最大值 3个通道
	double *pmaxval = maxval;
	for (size_t i = 0; i < 3; i++)
	{
		minMaxLoc(hist[i], NULL, pmaxval++, NULL, NULL,Mat());
		std::cout << "maxval = " << maxval[i] << std::endl;
	}
	int x_step = 2;
	int  dst_rows = 256; //  输出图像的高度
	Mat dst1 = Mat::zeros(dst_rows, x_step * bins, CV_8UC3);
	Mat dst2 = dst1.clone();
	std::vector<Mat> dsts;
	std::vector<Scalar> colors = {Scalar(255,0,0),Scalar(0,255,0),Scalar(0,0,255)};
	for (int i = 0; i < 3; i++)
	{
		dsts.push_back(Mat::zeros(dst_rows, x_step * bins, CV_8UC3));// 256 * 512
		for (int bin = 0; bin < bins; bin++)
		{
			int x1 = bin * x_step; // 每个小矩形的左上角水平x坐标取0,2,4,..
			int x2 = (bin + 1) * x_step - 1; // 每个小矩形的右下角水平x坐标1,3,5,7..
			// 每个灰度级的y坐标需要先归一化到0-1再放缩到图像的尺度,然后取整减1保证不越界 否则255.7可能取256
			int y1 = cvRound(hist[i].at<float>(bin) / maxval[i] * dst_rows);
			int y2 = 255 - 0;// 0的话矩形是基于x轴y=0向下的,视觉上为了更好观看把坐标选在y2>y1上 好似基准线在y=255上
			//std::cout << (i + 1) * (bin + 1) << std::endl;
			//std::cout << "x1 = " << x1 << "  x2 = " << x2 << "   y1 = " << y1 << "  y2 = " << y2<< std::endl;
			rectangle(dsts[i],Point(x1,y1),Point(x2,y2),colors[i]); // 3个窗口分别显示3个通道的直方图
			rectangle(dst1, Point(x1, y1), Point(x2, y2), colors[i]); // 1个窗口同时显示
			imshow("dst"+std::to_string(i), dsts[i]);
		}
		for (int bin = 1; bin < bins; bin++)
		{
			int x1 = (bin - 1) * x_step; // 0,2,4,...
			int x2 = bin * x_step - 1;// 1,3,5..
			int y1 = 255 - cvRound(hist[i].at<float>(bin - 1) / maxval[i] * dst_rows);// 为了视觉效果把y=0基准拉到y=255
			int y2 = 255 - cvRound(hist[i].at<float>(bin) / maxval[i] * dst_rows); // 为了视觉效果把y=0基准拉到y=255
			line(dst2, Point(x1, y1), Point(x2, y2), colors[i], 2, 8, 0);
		}
	}
	imshow("rect", dst1);
	imshow("line1", dst2);
	
	Mat src_hsv;
	cvtColor(src,src_hsv,COLOR_BGR2HSV);
	Mat hsv_h, hsv_s, hsv_v;
	Mat hsvs[] = { hsv_h, hsv_s, hsv_v }; // 不直接用3个彩色图片是因为要求深度类型尺寸保持一致比较麻烦
	split(src_hsv,hsvs);
	Mat* hsv = hsvs;
	nimages = 3;
	int channels_ []= { 0,1,2 }; // 看成3个图片时也要按照顺序0,1,2，只是1是第2个图片的0通道,2是第3个图片的0通道
	int* pchannel_ = channels_;
	int histsizes_[] = { bins,bins,bins }; // 每个图的直方图尺寸都是1维256长度
	int* histSize_ = histsizes_;
	float range_h[] = { 0,180 };
	float range_s[] = { 0,256 };
	float range_v[] = { 0,256 }; 
	const float* range_hsv[] = { range_h,range_s,range_v }; // 一维指针数组
	const float** ranges_ = range_hsv;
	Mat hist_[] = {Mat(),Mat(), Mat()};
	Mat* phist_ = hist_;
	//std::vector<Mat> hist_(src.channels()); //  使用容器和数组都可以,这里使用数组上边使用容器
	
	for (int i = 0; i < 3; i++) // 这里表示对每个图片循环,与上方的含义1个图像的每个通道循环含义完全不同
	{
		calcHist(hsv, nimages, pchannel_++, mask, hist_[i], dims, histSize_++, ranges_, uniform, accumulate);
		std::cout << hist_[i].size() << "  " << hist_[i].channels() << std::endl; // [1 x 256]  1
		//std::cout << hist_[i] << std::endl;
	}
	double maxval_[3] = { 0,0,0 }; // 计算一维直方图的最大值 3个通道
	double* pmaxval_ = maxval_;
	for (size_t i = 0; i < 3; i++)
	{
		minMaxLoc(hist_[i], NULL, pmaxval_++, NULL, NULL, Mat());
		std::cout << "maxval = " << maxval_[i] << std::endl;
	}
	Mat dst_ = Mat::zeros(dst_rows, x_step * bins, CV_8UC3);;
	for (size_t i = 0; i < 3; i++)
	{
		for (int bin = 1; bin < bins; bin++) // 注意不要越界 i =1开始
		{
			int x1 = (bin-1) * x_step; // 0,2,4,...
			int x2 = bin  * x_step - 1;// 1,3,5..
			int y1 = 255 - cvRound(hist_[i].at<float>(bin -1) / maxval_[i] * dst_rows);// 为了视觉效果把y=0基准拉到y=255
			int y2 = 255 - cvRound(hist_[i].at<float>(bin) / maxval_[i] * dst_rows); // 为了视觉效果把y=0基准拉到y=255
			//std::cout << "x1 = " << x1 << "  x2 = " << x2 << "   y1 = " << y1 << "  y2 = " << y2<< std::endl;
			CV_Assert(x1 <= bins*x_step && x2 <= bins * x_step &&y1<=dst_rows && y2 <= dst_rows);
			line(dst_, Point(x1, y1), Point(x2, y2), colors[i], 2, 8, 0);
		}
	}
	imshow("line2",dst_);
	waitKey(0);
	destroyAllWindows();
}