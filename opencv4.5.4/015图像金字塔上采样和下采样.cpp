#include "primary.h"
#include <vector>
#include <string>
using namespace cv;
using namespace std;
void image_up_down_sampling()
{
	// 图像金字塔需要先对层模糊,然后进行采样,采样是删除偶数行与列
	// 所以图片只有原来的1/4大小(面积)，如220×220->110×110
	// 高斯差分是一幅图像在两种参数下之间的差值图像，常用于角点检测
	// 首先说明上采样和下采样API的使用
	const Mat src = imread(imgAddr + "apple.jpg");
	Mat up, down;
	pyrUp(src,up,Size(src.cols *2 , src.rows * 2));
	pyrDown(src, down, Size(src.cols / 2, src.rows / 2));
	cout << "up = " << up.size() << "	down=" << down.size() << endl;
	bool show_up_down = false;
	if (show_up_down == true)
	{
		imshow("up",up);
		imshow("down", down);
		waitKey(0);
		destroyAllWindows();
	}
	// 图像金字塔某一层的高斯差分DoG
	Mat gray, temp1, temp2,dst;
	double sigmaX1 = 1.0,  sigmaX2 = 1.5 , sigmaY = 0.0;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	GaussianBlur(gray,temp1,Size(5,5),sigmaX1,sigmaY);
	GaussianBlur(gray, temp2, Size(15, 15), sigmaX2, sigmaY);
	subtract(temp1,temp2,dst);
	bitwise_not(dst,dst);
	//imshow("dst",dst);
	//waitKey(0);
	//destroyAllWindows();

	// 图像金字塔
	vector<Mat> image_pyramid;
	double sigmaX = 3.0;
	Mat T = src;
	image_pyramid.push_back(src);
	while (min(T.cols, T.rows) != 1)
	{
		GaussianBlur(T,T,Size(3,3),sigmaX,sigmaY);
		pyrDown(T, T,Size(T.cols/2,T.rows/2));
		cout <<"T.size = " << T.size() <<  endl;
		image_pyramid.push_back(T);
	}
	cout << "guassian_pyramid.size() = "<< image_pyramid.size()<< endl;
	vector<Mat> ::iterator it;
	int i = 1;
	for (it = image_pyramid.begin();it != image_pyramid.end()-6; it++)
	{
		// _itos_s(int _Value, char *_Buffer, size_t _BufferCount, int _Radix);
		//char str[3];
		//_itoa_s(i , str,sizeof(str),10); // 十进制,缓存字节不能超过str
		stringstream str;
		str << i;
		//imshow("img"+str.str(), *(it));
		i++;
	}
	//waitKey(0);
	//destroyAllWindows();
	//高斯金字塔并不是一个金字塔,而是有很多组(Octave)金字塔构成，
	// 并且每组金字塔都包含若干层
	// 先将原图像扩大一倍之后作为高斯金字塔的第1组第1层
	// 将第1组第1层图像经高斯卷积得到第1组第1层
	// 参数σ，在Sift算子中取的是固定值1.6
	// 将σ乘以一个比例系数k,等到一个新的平滑因子σ=k*σ，用它来平滑第1组第2层图像
	// 如此这般重复，最后得到L层图像，在同一组中每一层图像的尺寸都是一样的
	// 只是平滑系数不一样 0，σ，kσ，k^2σ,k^3σ……k^(L-2)σ
	//  将第1组倒数第三层图像作比例因子为2的降采样，得到的图像作为第2组的第1层
	// 对第2组的第1层图像做平滑因子为σ的高斯平滑，得到第2组的第2层,反复执行,在尺寸方面第2组是第1组图像的一半
	/*
	https://blog.csdn.net/Fishmemory/article/details/51519877
	https://blog.csdn.net/dcrmg/article/details/52561656
	*/
	waitKey(0);
	destroyAllWindows();
}
