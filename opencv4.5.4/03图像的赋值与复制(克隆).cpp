#include "primary.h"
using namespace cv;
void image_assignment_copy_clone()
{
	Mat src = imread("D:/VisualStudioItems/apple.jpg", IMREAD_COLOR);

	Mat src_assign = src; // 赋值
	// clone是完全的深拷贝,复制矩阵头和数据空间到申请的新空间
	// copyTo根据dst与src是否一致决定是否申请内存空间,如果矩阵头大小一致则只进行深拷贝不申请空间
	Mat src_copy;
	src.copyTo(src_copy); // 复制

	Mat src_clone = src.clone(); // 克隆

	// 常用的创建空白图像的方法
	Mat img1 = Mat::zeros(src.size() , src.type()); // 使用已有图像的类型
	Mat img2 = Mat::ones(Size(220, 220), CV_8UC3);// 8位无符号整型三通道
	
	img2 = 127; // 使用整数赋值
	img2 = Scalar(10, 20, 30); // 使用scalar赋值，Scalar是一个四个元素的数组类
	
	Scalar s1(0,255,255); // 黄色
	std::cout << s1 << std::endl;//[0, 255, 255, 0]
	img2 = s1; // 把Scalar向量在所有通道上的所有行反复的按列复制
	// std :: cout << img2 << std::endl; // 可以直接打印

	Mat img2_assign = img2; // 赋值
	img2_assign = Scalar(255, 0, 0);//蓝色 BGR
	imshow("img2_1",img2); // 蓝色,说明改变赋值对象也会改变任何引用指向的对象

	Mat img2_clone = img2.clone();// 改变克隆对象不会改变被克隆对象
	img2_clone = Scalar(0, 255, 0);
	imshow("img2_clone", img2_clone);// 绿色
	imshow("img2_2", img2);// 蓝色,不改变
	waitKey();
}
