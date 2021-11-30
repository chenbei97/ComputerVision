#include "primary.h"
using namespace cv;
enum ergodic_types { PointerArray, PTr, At, Continuous, Iterator };
void matrix_ergodic_pointer_array(const Mat& src);
void matrix_ergodic_ptr(const Mat& src);
void matrix_ergodic_at(const Mat& src);
void matrix_ergodic_continuous(const Mat& src);
void matrix_ergodic_iterator(const Mat& src);
void matrix_ergodic(const Mat& src, int type);
void image_matrix_ergodic()
{
	ergodic_types types[] = { PointerArray, PTr, At, Continuous, Iterator };
	const std::vector<std::string> typeNames = {"PointerArray","PTr","At","Continuous","Iterator"};
	//Mat src (5, 5, CV_8UC3, Vec3i(1,2,3));
	//Mat src = Mat::ones(3, 3, CV_8UC3);
	Mat src = imread(imgAddr + "lena.jpg");
	//resize(src, src, Size(100, 100));
	std::cout << src.isContinuous() << std::endl; // 1
	std::cout << src.size() << std::endl; 
	std::cout << types[0] << std::endl; // 0 
	std::cout << sizeof(types) << "   "<< sizeof(types[0])<<std::endl; // 20,4
	uchar *p = src.data;
	//std::cout << (uchar*)src.data << std::endl; //是一堆字符乱码数据
	//std::cout << p << std::endl; //是一堆字符乱码数据
	for (int i = 0; i < sizeof(types) / sizeof(types[0]); i++)
	{
		double time0 = static_cast<double>(getTickCount());
		matrix_ergodic(src, types[i]);
		time0 = ((double)getTickCount() - time0) / getTickFrequency();
		std::cout << "use  "+typeNames[i]+"  cost time =  ： " << time0 << "s" << std::endl;  
	}
}

void matrix_ergodic(const Mat &src ,int type)
{
	switch (type)
	{
		case 0: matrix_ergodic_pointer_array(src); break;
		case 1:matrix_ergodic_ptr(src); break;
		case 2:matrix_ergodic_at(src); break;
		case 3:matrix_ergodic_continuous(src); break;
		case 4:matrix_ergodic_iterator(src); break;
	}
}
void matrix_ergodic_pointer_array(const Mat& src)
{
	
	uchar* row_pointer = (uchar*)src.data;//src.data是展平的一维普通数组 
	// row_pointer是一个指向了一维数组的指针罢了,然后逐行逐列访问每个元素
	//uchar* row_pointer = src.data; // 不强制转换也可以,会比强制转换略长
	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			// 把0,1,2,3,4需要映射到0,3,6,9,12的位置上,然后再使用+0,+1,+2访问每个通道
			//std::cout << (int)row_pointer[row * src.cols * src.channels() + 0]<<"  ";
			//std::cout << (int)row_pointer[row * src.cols * src.channels() + 1]<< "  ";
			//std::cout << (int)row_pointer[row * src.cols * src.channels() + 2]<< "  ";
		}
		//std::cout <<std::endl;
	}
	
	// 或者如此也可以
	//for (int row = 0; row < src.rows; row++)
	//{
	//	for (int col = 0; col < src.cols * src.channels(); col++)
	//	{
	//		std::cout << (int)row_pointer[row*src.cols*src.channels()+col] << "  "; 
	//		// 数组的存放方式是BGR交替的,所以一次性打印的列数还要乘通道数
	//	}
	//	std::cout << std::endl;
	//}



}
void matrix_ergodic_ptr(const Mat& src)
{
	for (int row = 0; row < src.rows; row++)
	{
		const uchar* p = src.ptr<uchar>(row); // ptr可以使指针指向每行指针本身(行指针首元素地址),是数组指针
		for (int col = 0; col < src.cols * src.channels(); col++)
		{
			//std::cout << (int)p[col] << "  ";
		}
		//std::cout << std::endl;
	}
}
void matrix_ergodic_at(const Mat& src)
{
	if (src.channels() == 1)
	{
		for (int row = 0; row < src.rows; row++)
		{
			for (int col = 0; col < src.cols; col++)
			{
				//std::cout << (int)src.at<uchar>(row, col)<<"  ";
			}	
		}
		//std::cout << std::endl;
	}
	else if (src.channels() == 3)
	{
		for (int row = 0; row < src.rows; row++)
		{
			for (int col = 0; col < src.cols; col++)
			{
				//std::cout <<(int)src.at<Vec3b>(row, col)[0] << "  "; // 只能使用Vec3b接收,不可使用Vec3i
				//std::cout << (int)src.at<Vec3b>(row, col)[1] << "  ";
				//std::cout << (int)src.at<Vec3b>(row, col)[2] << "  ";
			}
			//std::cout << std::endl;
		}
	}
	else { throw("src.channels() should be 1 or 3"); return; }	
}
void matrix_ergodic_continuous(const Mat& src)
{
	if (src.isContinuous())
	{
		int n_cols = src.rows * src.cols * src.channels();
		const uchar* p = src.ptr<uchar>(0); // 指向首行即可
		for (int col = 0; col < n_cols; col++)
		{
			//std::cout << (int)p[col] << "  ";
		}
		//std::cout << std::endl;
	}
	else
	{
		throw("memory is not continuous");
		return;
	}
}
void matrix_ergodic_iterator(const Mat& src)
{
	Mat_<Vec3b>::const_iterator it = src.begin<Vec3b>();  //初始位置的迭代器
	Mat_<Vec3b>::const_iterator itend = src.end<Vec3b>();  //终止位置的迭代器
	while (it != itend)
	{
		//std::cout << (int)(*it)[0] << "  ";
		//std::cout << (int)(*it)[1] << "  ";
		//std::cout << (int)(*it)[2] << "  ";
		it++;
	}
	//std::cout << std::endl;
}