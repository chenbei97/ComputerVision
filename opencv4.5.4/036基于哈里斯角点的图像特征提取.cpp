#include "primary.h"
using namespace cv;
#include <vector>
Mat harris_src, harris_gray, harris_dst;
int harris_thresh = 245; // 滑动的对象 当前值
int harris_count = 255; // 最大值
const char* harris_winname = "harris";
const char* harris_barname = "thresh";
void image_feature_extraction__HarrisCorner_callback(int ,void*);
void image_feature_extraction__HarrisCorner()
{
	/*
	图像特征提取与描述符：SIFT、HOG、SURF、HAAR、LBP、KAZE、AKAZE、BRISK
	目标DDM：目标检测(Detection)、目标描述(Description)、目标匹配(Matching)

	void cornerHarris( InputArray src, OutputArray dst, int blockSize,
								int ksize, double k,
								int borderType = BORDER_DEFAULT );
	src、dst：类型为CV_32FC1
	blockSize：blockSize邻域大小
	ksize：Sobel运算窗口大小
	k：计算角度响应的特征大小，哈里斯检测器自由参数,0.04~0.06
	borderType：参数边界类型
	*/
	namedWindow(harris_winname,WINDOW_FREERATIO); // !!!必须有这句
	harris_src = imread(imgAddr + "tajmahal.jpg");
	cvtColor(harris_src, harris_gray, COLOR_BGR2GRAY);// 哈里斯只检测灰度图
	createTrackbar(harris_barname, harris_winname,&harris_thresh, harris_count, image_feature_extraction__HarrisCorner_callback);
	image_feature_extraction__HarrisCorner_callback(0,0);
	waitKey(0);
	destroyAllWindows();
	return ;
}
void image_feature_extraction__HarrisCorner_callback(int, void*)
{
	harris_dst = Mat::zeros(harris_gray.size(), CV_32FC1);
	int blocksize = 2;
	int ksize = 3;
	double k = 0.04;
	int borderType = BORDER_DEFAULT;
	cornerHarris(harris_gray,harris_dst,blocksize,ksize,k,borderType); // 浮点数
	normalize(harris_dst, harris_dst, 0, 255, NORM_MINMAX,CV_32FC1,Mat());
	//imshow("harris_gray", harris_gray);
	Mat dst;
	convertScaleAbs(harris_dst,dst);// 计算绝对值并转换到8bit
	//imshow("dst", dst);
	Mat src = harris_src.clone();
	for (int row = 0; row < src.rows; row++)
	{
		uchar* current_row = src.ptr(row);
		for (int col = 0; col < src.cols; col++)
		{
			int value = (int)*current_row;
			//std::cout << "value = " << value << std::endl;
			if (value > harris_thresh)
			{
				int radius = 1;
				circle(src, Point(row, col), radius, Scalar(0, 0, 255), 1, 8, 0);
			}
			current_row++;
		}
	}
	imshow(harris_winname, src);
}