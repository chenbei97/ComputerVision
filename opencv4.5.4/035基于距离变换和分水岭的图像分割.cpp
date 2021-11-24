#include "primary.h"
using namespace cv;
#include <vector>
void image_segmentation_of_distance_transformand_watershed()
{
	/*
		距离变换：基于不断膨胀腐蚀得到、基于倒角距离得到
		void distanceTransform( InputArray src, OutputArray dst,
									 int distanceType, int maskSize, int dstType=CV_32F);
		distanceType：使用DIST_L1、DIST_L12、DIST_L2
		maskSize：支持3×3或5×5，滑窗大小
		dstType：输出8位或32位的浮点数，单通道
		void distanceTransform( InputArray src, OutputArray dst,
                                     OutputArray labels, int distanceType, int maskSize,
                                     int labelType = DIST_LABEL_CCOMP );
		 labels：离散维诺图输出
		 labelType ：DIST_LABEL_PIXEL或DIST_LABEL_CCOMP

		分水岭：基于浸泡理论实现
		void watershed( InputArray image, InputOutputArray markers );

		①白色背景变为黑色
		②使用filter2D与拉普拉斯算子实现图像对比度提高
		③转为二值图像
		④距离变换
		⑤对距离变换结果归一化到0-1之间
		⑥使用阈值再次二值化得到标记
		⑦腐蚀得到每个peak_erode
		⑧findContours 和 drawContours
		⑨watershed
		⑩对每个区域着色输出结果
	
	*/
	Mat src = imread(imgAddr + "pepper.jpg");
	Mat src_white = src.clone();
	// ①白色背景变为黑色
	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			if (src.at<Vec3b>(row, col) == Vec3b(255, 255, 255))
			{
				src_white.at<Vec3b>(row, col)[0] = 0;
				src_white.at<Vec3b>(row, col)[1] = 0;
				src_white.at<Vec3b>(row, col)[2] = 0;
			}
		}
	}
	
	//②使用filter2D与拉普拉斯算子实现图像对比度提高
	Mat sharp;
	Mat kernel = (Mat_<float>(3, 3) << 1, 1, 1,
															1, -8, 1,
															1, 1, 1);
	filter2D(src_white, sharp,  CV_32F, kernel, Point(-1, -1));//只需要深度，使用 CV_32F
	std::cout << "sharp.channels() = "<<sharp.channels() << std::endl; // 也是3通道
	sharp.convertTo(sharp,CV_8UC3); //CV_8U也可
	src_white.convertTo(src_white,CV_8UC3);
	Mat inverse_sharp = sharp - src_white;
	inverse_sharp.convertTo(inverse_sharp, CV_8UC3);
	//imshow("src_white", src_white);
	 //imshow("sharp", sharp);
	//imshow("inverse_sharp", inverse_sharp);

	// ③转为二值图像
	Mat binary,gray;
	cvtColor(inverse_sharp, gray, COLOR_BGR2GRAY);
	//imshow("gray", gray);
	double thresh = 50;
	double maxval = 255;
	int type = THRESH_OTSU | THRESH_BINARY;
	threshold(gray, binary, thresh, maxval, type);
	//imshow("binary", binary);

	// ④距离变换
	Mat distTransform;
	int distanceType = DIST_L1;
	int maskSize = 3;
	int dstType = CV_32F;
	int labelType = DIST_LABEL_CCOMP;
	distanceTransform(binary, distTransform,distanceType,maskSize,dstType);
	
	//⑤对距离变换结果归一化到0 - 1之间
	double alpha = 0.0, beta = 1.0;
	int norm_type = NORM_MINMAX;
	normalize(distTransform, distTransform, alpha, beta, norm_type, -1, noArray());
	
	//⑥使用阈值再次二值化得到标记
	thresh = 0.2;
	maxval = 1.0;
	threshold(distTransform, distTransform, thresh, maxval, THRESH_BINARY);
	//imshow("distTransform", distTransform);
	
	//⑦腐蚀得到每个peak_erode
	Mat kernel1 = Mat::ones(1, 1, CV_8UC1);
	Mat erode_dist;
	erode(distTransform, erode_dist, kernel1);
	erode_dist.convertTo(erode_dist,CV_8U);
	//imshow("erode_dist", erode_dist); // 直接看看不清楚
	Mat inverse_erode_dist;
	bitwise_not(erode_dist, inverse_erode_dist);
	//imshow("inverse_erode_dist", inverse_erode_dist);
	
	//⑧findContours 和 drawContours
	std::vector<std::vector<Point>>contours;
	std::vector<Vec4i> hierarchy;
	int mode = RETR_TREE;
	int method = CHAIN_APPROX_SIMPLE;
	findContours(erode_dist, contours, hierarchy, mode, method, Point(0, 0));

	Mat markers = Mat::zeros(src.size(), CV_32SC1); // 储存所有得到的轮廓点,必须是短整型的
	for (size_t i = 0; i < contours.size(); i++)
	{
		//std::cout << "i = " << i <<"   ："<<contours[i] << std::endl;
		Scalar color = Scalar::all(static_cast<int>(i)+1);
		/*Scalar color(0,255,0,0);*/
		//std::cout << "color = " << color << std::endl;
		drawContours(markers,contours,static_cast<int>(i),color,2,8,noArray());
		//std::cout << markers << std::endl;
	}
	
	//⑨watershed
	watershed(src, markers);  // (src.type() == CV_8UC3 && dst.type() == CV_32SC1)
	Mat mask;
	markers.convertTo(mask, CV_8UC1);
	bitwise_not(mask, mask);
	//imshow("mask",mask);
	
	//⑩对每个区域着色输出结果

	std::vector<Vec3b> colors;

	for (size_t i = 0; i < contours.size(); i++)
	{
		// 不同的轮廓是分割线，使用不同的颜色
		int b = theRNG().uniform(0, 255);
		int g = theRNG().uniform(0, 255);
		int r = theRNG().uniform(0, 255);
		colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
	}

	// 原来的markers是单通道,现在3通道填充颜色
	// 但是不在原图填充,也不在markers填充,只是利用marker提供的位置信息
	Mat dst = Mat::zeros(markers.size(), CV_8UC3);  
	for (int row = 0; row < markers.rows; row++) 
	{
		for (int col = 0; col < markers.cols; col++)
		{
			int marker = markers.at<int>(row, col);
			//std::cout << "marker = " << marker << std::endl;
			if (marker > 0 && marker <= static_cast<int>(contours.size())) //非0元素且强度要大于轮廓的容量
			{
				dst.at<Vec3b>(row, col) = Vec3b(0, 0, 0);
			}
		}
	}
	imshow("dst",dst);
	waitKey(0);
	destroyAllWindows();
}