#include "primary.h"
using namespace cv;

void image_pixel_read_write_operation()
{
	Mat src = imread("D:/VisualStudioItems/apple.jpg",IMREAD_COLOR);//IMREAD_GRAYSCALE
	int width = src.cols;
	int height = src.rows;
	int dims = src.dims;
	int channels = src.channels();
	int i = 0;
	std::cout << "channels = " << channels << "  dims = " << dims << std :: endl; // channel=3 , dim=2（channels = 1  dims = 2）
	bool isPtr = true;
	bool isAt = false;
	if (isPtr == false && isAt == true) 
	{
		double time0 = static_cast<double>(getTickCount());
		// <1> 使用at访问(借助索引)
		for (int row = 0; row < height; row++)
			for (int col = 0; col < width; col++)
			{// 遍历数组
				if (channels == 1)
				{ // 灰度图像
					int uint_value = src.at<uchar>(row, col); // 这个图片是0-255类型的
					src.at<uchar>(row, col) = 255 - uint_value;
					/*float float_value = src.at<float>(row, col);*/
					if (i < 50)
					{
						std::cout << "uint = " << uint_value << std::endl;
						i++;
					}
					else
						break;
				}
				else if (channels == 3)
				{ // 彩色图像
					Vec3b vector_value = src.at<Vec3b>(row, col); // 一次性读取了3个通道的位置上的数值组成了数组
					src.at<Vec3b>(row, col)[0] = 255 - vector_value[0]; // 继续访问每个通道
					src.at<Vec3b>(row, col)(1) = 255 - vector_value(1);
					src.at<Vec3b>(row, col)[2] = 255 - vector_value[2];
					//	if (i < 10) {
					//		std::cout << "(3,3,0),(3,3,1),(3,3,2) = " << vector_value << std::endl;
					//		i++;
					//	}
					//	else
					//		break;
					//}
				}
			}
		time0 = ((double)getTickCount() - time0) / getTickFrequency();
		std::cout << "\t使用at的运行时间为： " << time0 << "秒" << std::endl;  //输出运行时间=0.0330268秒
		// 访问特定坐标元素
		if (channels == 1)
		{
			Point p0(100, 100);
			std::cout << "(100,100) = " << src.at<uchar>(p0) << std::endl; // 单通道时读取的是3
			std::cout << "(100,100) = " << src.at<uchar>(100, 100) << std::endl;// 单通道时读取的是3
		}
		else
		{
			Point p1(100, 100);
			std::cout << "(100,100,0) = " << (int)src.at<Vec3b>(p1)[0] << "  (100,100,1) = " << (int)src.at<Vec3b>(p1)(1) << std::endl; // 多通道时读取的是[3, 72, 27]
		}
		
		imshow("inverse_src", src);
		waitKey(0);
	}
	else if (isPtr == true && isAt == false)
	{
		double time0 = static_cast<double>(getTickCount());
		//<2> 使用ptr访问(借助指针)
		for (int row = 0; row < height; row++) 
		{
			uchar* current_raw = src.ptr<uchar>(row); // ptr只能访问行,每次行循环的行指针
			for (int col = 0; col < width; col++)
			{
				if (channels == 1) {
					int value = *current_raw; // 这是行指针的首元素
					*current_raw = 255 - value;
					current_raw++; // 行指针++ 访问列元素
				}
				else
				{
					//*(current_raw++) = 255 - *current_raw; // 使用三次,这是因为行指针是指向3个通道依次向右平铺的数组列
					//*(current_raw++) = 255 - *current_raw;
					//*(current_raw++) = 255 - *current_raw;
					*(current_raw++) = 255 - *current_raw;
				}
			}
		}
		time0 = ((double)getTickCount() - time0) / getTickFrequency();
		//getTickCount( )函数返回CPU自某个事件以来走过的时钟周期数
		// getTickFrequency()函数返回CPU一秒钟所走的时钟周期数
		std::cout << "\t使用ptr的运行时间为： " << time0 << "秒" << std::endl;  //输出运行时间=0.001702秒
		imshow("inverse_src", src);
		waitKey(0);
	}	
	else // 迭代器方法
	{
		double time0 = static_cast<double>(getTickCount());
		Mat_<Vec3b>::iterator it = src.begin<Vec3b>();  //初始位置的迭代器
		Mat_<Vec3b>::iterator itend = src.end<Vec3b>();  //终止位置的迭代器
		for (; it != itend; ++it)
		{
			(*it)[0] = 255 - (*it)[0];
			(*it)[1] = 255 - (*it)[1];
			(*it)[2] = 255 - (*it)[2];
		}
		time0 = ((double)getTickCount() - time0) / getTickFrequency();
		std::cout << "\t使用iterator的运行时间为： " << time0 << "秒" << std::endl;  //输出运行时间=0.02秒
		imshow("inverse_src", src);
		waitKey(0);
	}
}