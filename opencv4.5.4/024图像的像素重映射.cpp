#include "primary.h"
using namespace cv;
Mat src_024 = imread(imgAddr + "apple.jpg"), dst_024;
Mat mapx;
Mat mapy;
void image_pixel_remapping_mapfunction(int index);
void image_pixel_remapping()
{
	// 把原图像的像素按照一定规则映射到新图像的对应位置上
	// 可以实现翻转、变形等
	// remap：输入、输出、映射表1、映射表2、插值方法(线性插值、立方插值)
	// 边界差值方法：
	/*
		INTER_NEAREST - 最近邻插值
		INTER_LINEAR – 双线性插值（默认值）
		INTER_CUBIC – 双三次样条插值（逾4×4像素邻域内的双三次插值）
		INTER_LANCZOS4 -Lanczos插值（逾8×8像素邻域的Lanczos插值）
	*/
	// const Scalar boaderValue
	mapx.create(src_024.size(), CV_32FC1);// 常用类型CV_32FC1或CV_32FC2类型
	mapy.create(src_024.size(), CV_32FC1);
	
	int interpolation = INTER_LINEAR;   // INTER_NEAREST
	int borderMode = BORDER_CONSTANT;  // 常数线性插值,边界插值类型
	Scalar boardValue(0,255,0);//插值数值
	int index = -1;
	//std::cout << "index = ";
	//std::cin >> index;
	//image_pixel_remapping_mapfunction(index);
	//remap(src_024, dst_024, mapx, mapy, interpolation, borderMode, boardValue);
	//imshow("src", src_024);
	//imshow("dst", dst_024);
	//waitKey(0);
	image_pixel_remapping_mapfunction(index); // 先执行一次
	remap(src_024, dst_024, mapx, mapy, interpolation, borderMode, boardValue);
	while (true)
	{
		index = waitKey(500) ; 
		std::cout << index << std::endl; // esc=27
		if ((char)index == 27)
			break;
		index = index % 3; // 只能等于0,1,2
		std::cout << index << std::endl;
		image_pixel_remapping_mapfunction(index);
		//std::cout << "update successful ..." << std::endl;
		remap(src_024, dst_024, mapx, mapy, interpolation, borderMode, boardValue);
		imshow("dst", dst_024);
	}	
	destroyAllWindows();
}
void image_pixel_remapping_mapfunction(int index)
{
	for (int row = 0; row < src_024.rows; row++)
	{
		for (int col = 0; col < src_024.cols; col++) // 映射关系
		{
			switch (index)
			{
			case 0 : // 左右翻转
				mapx.at<float>(row, col) = src_024.cols  - col; // 翻转x static_cast<float>
				mapy.at<float>(row, col) = row; // y不变
				// c++除了能使用c语言的强制类型转换外，还新增了四种强制类型转换
				// static_cast、dynamic_cast、const_cast、reinterpret_cast
				// static_cast相当于传统的C语言里的强制转换，该运算符把expression转换为new_type类型
				//std::cout << "case 0 running..." << std::endl;
				break;
			case 1: // 上下翻转
				mapx.at<float>(row, col) = col;
				mapy.at<float>(row, col) = src_024.rows - row;
				break;
			case 2: // 镜像翻转
				mapx.at<float>(row, col) = src_024.cols - col;
				mapy.at<float>(row, col) = src_024.rows - row;
				break;
			default: // 什么也不做
				mapx.at<float>(row, col) = col;
				mapy.at<float>(row, col) = row;
				break;
			}
		}
	}
}