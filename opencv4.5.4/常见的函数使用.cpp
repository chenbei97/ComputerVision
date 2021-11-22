#include "function.h"
#include "vector"
using namespace cv;
const std::string imgAddr = "D:/VisualStudioItems/Opencv4/Opencv4/Opencv4/images/";
// <1>bitwise系列函数
void image_bitwise();
void image_convertTo();
void image_createTrackBar();
void image_rng_uniform();
void image_createTrackBar_callback(int, void*);
void image_normalize();
void image_functions_using(const std :: string str)
{
	if (str == "bitwise")
	{
		image_bitwise();
	}
	else if (str == "convertTo")
	{
		image_convertTo();
	}
	else if (str == "rng_uniform")
	{
		image_rng_uniform();
	}
	else if (str == "createTrackBar")
	{
		image_createTrackBar();
	}
	else if (str == "normalize")
	{
		image_normalize();
	}

}
void image_normalize()
{
	/*
	normalize( InputArray src, InputOutputArray dst, double alpha = 1, double beta = 0,
                             int norm_type = NORM_L2, int dtype = -1, InputArray mask = noArray());
    mask：选择感兴趣区域，选定后只能对该区域进行操作
	此函数用的范围归一化,beta用来控制缩放的尺度, A/max(A) * beta
	normalize( const SparseMat& src, SparseMat& dst, double alpha, int normType );
	此函数不适用多通道,需要展平多通道或者spilit单独使用
	此函数要求传入的参数是稀疏矩阵,如果没有使用Mat类型其实调用的第1种
	此函数用的是值归一化,A/max(A)
	*/
	Vec4d src1 = {1,2,3,4}, dst1,dst2;
	std::cout << "sum(src1) = " << sum(src1) << std::endl;//sum(src1) = [10, 0, 0, 0]
	
	std::vector<double> src2 = {1,2,3,4},dst3,dst4;
	std::cout << "sum(src2) = " << sum(src2) << std::endl;//sum(src2) = [10, 0, 0, 0]
	
	Mat src3(2, 2, CV_32FC1),dst5,dst6;
	src3.at<float>(0, 0) = 1.0; src3.at<float>(0, 1) = 2.0; src3.at<float>(1, 0) = 3.0; src3.at<float>(1, 1) = 4.0;
	std::cout << "sum(src3) = " << sum(src3) << std::endl;//sum(src3) = [10, 0, 0, 0]
	double alpha = 1.0;
	double beta = 10.0;
	int normtype = 32;// NORM_L1=2; NORM_L2=4;NORM_INF=1;NORM_MINMAX=32;
	if (normtype == NORM_L1)
	{
		std::cout << " L1...." << std::endl;
		alpha = 2;
		normalize(src1, dst1, alpha, normtype); // 以为调用的是第2种,实际上就是用的第1种。。。
		std::cout << "dst1 = " <<dst1 << std::endl; // normtype：被当成beta参数了为0,所以使用了默认的L2
		normalize(src1, dst2, alpha, beta, normtype); // 指定正确的第1种使用方法
		std::cout << "dst2 = " <<dst2 << std::endl;  // dst2 = [0.1, 0.2, 0.3, 0.4]
		

		normalize(src2, dst3, alpha, normtype);// 以为调用的是第2种,实际上就是用的第1种。。。
		std::cout << "dst3 = "; 
		for (int i = 0; i < dst3.size(); i++)
		{
			std::cout  << dst3[i] << "  "; // 错误原因相同,normtype被当成beta参数了为0,所以使用了默认的L2
			// dst3 = 0.182574  0.365148  0.547723  0.730297
		}
		std::cout << std::endl;
		normalize(src2, dst4, alpha, beta, normtype);// 指定正确的第1种使用方法
		std::cout << "dst4 = ";
		for (int i = 0; i < dst4.size(); i++)
		{
			std::cout  << dst4[i] << "  "; // dst4 = 0.1  0.2  0.3  0.4
		}
		std::cout << std::endl;


		normalize(src3, dst5, alpha, normtype);// 错误原因仍然是相同的,Mat不是SparseMat类型,依然自动选择第1种
		std::cout << "dst5 = " << dst5 << std::endl; // L1没起作用
		normalize(src3, dst6, alpha, beta, normtype);// 指定正确的第1种使用方法
		std::cout << "dst6 = " << dst6 << std::endl;

		// 1) NORM_L1
       // L1是求所有元素之和然后分别除，每个元素再单乘系数alpha
		// 也就是第2种函数自始至终没用

	}
	else if (normtype == NORM_L2)
	{
		std::cout << " L2...." << std::endl;
		normalize(src1, dst1, alpha, normtype);
		std::cout << "dst1 = " << dst1 << std::endl;
		normalize(src1, dst2, alpha, beta, normtype);
		std::cout << "dst2 = " << dst2 << std::endl;


		normalize(src2, dst3, alpha, normtype);
		std::cout << "dst3 = ";
		for (int i = 0; i < dst3.size(); i++)
		{
			std::cout << dst3[i] << "  "; 
		}
		std::cout << std::endl;
		normalize(src2, dst4, alpha, beta, normtype);
		std::cout << "dst4 = ";
		for (int i = 0; i < dst4.size(); i++)
		{
			std::cout << dst4[i] << "  "; // dst4 = 0.1  0.2  0.3  0.4
		}
		std::cout << std::endl;

		normalize(src3, dst5, alpha, normtype);
		std::cout << "dst5 = " << dst5 << std::endl;
		normalize(src3, dst6, alpha, beta, normtype);
		std::cout << "dst6 = " << dst6 << std::endl;
		// 从结果来看 dst1=dst2=..=dst6 = [0.182574, 0.365148, 0.547723, 0.730297] 
		// 全部使用的第1种函数 且是L2
	}
	else if (normtype == NORM_INF)
	{
		std::cout << " L∞...." << std::endl;
		normalize(src1, dst1, alpha, beta, normtype);
		std::cout << "dst1 = " << dst1 << std::endl;//dst1 = [0.25, 0.5, 0.75, 1]

		normalize(src2, dst3, alpha, beta, normtype);
		std::cout << "dst3 = ";
		for (int i = 0; i < dst3.size(); i++)
		{
			std::cout << dst3[i] << "  ";//dst3 = 0.25  0.5  0.75  1
		}
		std::cout << std::endl;
		
		normalize(src3, dst5, alpha, beta, normtype);
		std::cout << "dst5 = " << dst5 << std::endl; // dst5 = [0.25, 0.5, 0.75, 1]
		
	}
	else if (normtype == NORM_MINMAX)
	{
		// 范围归一化beta起作用,alpah不再是系数的乘积作用
		// alpha为范围最小值,beta为范围最大值
		// dst = (src - min(src)) * (beta - alpha) / [ max(src) - min(src)] + alpha
		// 如指定下限为alpha=2,上限为beta=100,则
		// (1 - 1) * (100-2) / (4-1) + 2 = 2
		// (2- 1) * (100-2) / (4-1) + 2 = 2
		// (3- 1) * (100-2) / (4-1) + 2 = 2
		// (4 - 1) * (100-2) / (4-1) + 2 = 100
		
		alpha = 2.0;
		beta = 100;
		std::cout << " minmax...." << std::endl;
		normalize(src1, dst1, alpha, beta, normtype);
		std::cout << "dst1 = " << dst1 << std::endl;//dst1 = [[2, 34.6667, 67.3333, 100]

		normalize(src2, dst3, alpha, beta, normtype);
		std::cout << "dst3 = ";
		for (int i = 0; i < dst3.size(); i++)
		{
			std::cout << dst3[i] << "  ";//dst3 = [2, 34.6667, 67.3333, 100]
		}
		std::cout << std::endl;

		normalize(src3, dst5, alpha, beta, normtype);
		std::cout << "dst5 = " << dst5 << std::endl; // dst5 = [2, 34.6667, 67.3333, 100]

	}

}
void image_rng_uniform()
{
	// 随机数的使用
	Mat im = imread(imgAddr + "eagle.jpg");
	RNG rng(123);

	int line_num = 1000;
	for (int i = 0; i < line_num; i++)
	{
		Scalar color(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		Point p1(rng.uniform(0, im.cols), rng.uniform(0, im.rows));// 随机点坐标
		Point p2(rng.uniform(0, im.cols), rng.uniform(0, im.rows));// 随机点坐标
		if (waitKey(10) > 0)
			break;
		line(im, p1, p2, color, 2, 8);
		namedWindow("random_line", WINDOW_FREERATIO);
		imshow("random_line", im);
	}
	destroyAllWindows();
}
void image_bitwise()
{
	Mat src = imread("D:/VisualStudioItems/apple.jpg", IMREAD_COLOR);
	Mat dst;
	bitwise_not(src, dst);
	//bitwise_and 
	//bitwise_or
	//bitwise_xor
	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
	destroyAllWindows();
}
void image_convertTo()
{
	Mat src = imread("D:/VisualStudioItems/apple.jpg", IMREAD_COLOR);
	Mat dst;
	double alpha = 1.0, beta = 0.0; //尺度变换因子 和 附加到尺度变换后的值上的偏移量
	src.convertTo(dst , CV_32FC3,alpha,beta); // rtype=-1说明和源图像数据类型一样
	//std::cout << src << std::endl;
	// std::cout << dst << std::endl;
}
// 回调函数需要全局变量
Mat src_trackbar, dst_trackbar;
int value_trackbar = 10;
int* val_trackbar = &value_trackbar;
const std::string trackbarname_trackbar = "bar";
const std::string winname_trackbar = "win";
void image_createTrackBar()
{
	src_trackbar = imread(imgAddr + "eagle.jpg");
	int max_value_trackbar = 100;
	namedWindow(winname_trackbar, WINDOW_FREERATIO);
	createTrackbar(trackbarname_trackbar, winname_trackbar,
		val_trackbar, max_value_trackbar, image_createTrackBar_callback);
	image_createTrackBar_callback(0, 0);
	waitKey(0);
}
void image_createTrackBar_callback(int, void*)
{
	int ksize = 2 * value_trackbar + 1;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(ksize, ksize));
	erode(src_trackbar, dst_trackbar, kernel);
	imshow(winname_trackbar, dst_trackbar);
	return;
}
