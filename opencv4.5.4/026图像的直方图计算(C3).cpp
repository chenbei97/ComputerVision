#include "primary.h"
#include <vector>
using namespace cv;
/*
		calcHist( const Mat* images, int nimages,
			const int* channels, InputArray mask,
			OutputArray hist, int dims, const int* histSize,
			const float** ranges, bool uniform = true, bool accumulate = false

		images ： 输入图像的指针,可以是单个图片,也可以是多个图像组成的数组
		所有的图像必须有同样的深度（CV_8U or CV_32F），同时一副图像可以有多个channels

		nimages：输入图像的个数
		channels：使用输入数据的第几通道，可以是C风格数组也可以是STL Vector
		通道是按照顺序编排的，images[0]的前3个通道编号为0,1,2，images[1]为3,4,5，以此类推
		channels的元素个数就是直方图的维度，即对应于某个输入数组的某个通道

		mask ： 掩膜，计算掩膜内像素的直方图 一般Mat()
		mask必须是一个8bit数组且和images的输入数组大小相同

		hist ：输出直方图，要求是数组类型
		dims ：需要统计直方图通道的个数，就是channels中的元素个数

		histSize：指的是直方图分成多少个区间，就是 bin的个数,在每一维上直方图的个数
		可以是C风格数组也可以是STL容器，元素的个数也应该等于dims
		但是注意：这里的维度是指特征维度，如果只统计灰度值的频率，其实是1维的，如果有多个特征如梯度、方向
		2个特征意味着直方图是3维的，x、y轴表示2个特征，z轴表明同时满足这2个特征的像素个数
		单个特征意味着2维，即亮度-频数的直方图

		ranges：用于指定每个通道维度的直方图的范围，所以ranges本身的长度等于dims
		①可以使用C风格也可以使用STL，如果是C风格：每个元素ranges[i]应当是另一个数组
		以下参数以具有3个通道的1个图片进行解释，那么 int channels[] = {0,1,2} , dims=1 ,nimages=1
		int histsize[] = {256,256,256} 每个通道都分成256个bins，也可以使用 std :: vector<int> histsize={256,256,256}
		②ranges[i]的解释取决于uniform是否归一化处理
		③uniform = true  例如[0,100)左闭右开
		C风格：应当指定每个通道
		说明第i个通道的100个数值所在的区间等长，可以把数值(像素强度)看成y坐标，还需要x坐标，x是等间距的便于绘图
		③如果不归一化，uniform=false，说明自定义水平间距，第i个通道分成histsize[i]个bins,则ranges[i]也必须是histsize[i]个元素
		ranges[i]相当于给了所有的水平坐标，例如{{0,2},{3,6},{7,9},{9,12},{17,19},{22,57}...{240,256}}共histsize[i]个，依然是左闭右开
		每个元素都指定了当前元素的下界(包含)和上一个元素的上界(不包含)，说白了就是bin开始的坐标为0,3,7,9,17,22,...且每个bin的宽度不一样
		④ranges[i]是STL容器的情况
		假如1个图片有3个通道，C风格指定的范围都是const float* ranges = {{0,256},{0,256},{0,256}}
		uniform=true：使用STL就传入vector<float> ranges = {0,256,0,256,0,256}
		uniform=false：则相当于平摊C风格数组的元素 即 vector={0,2,3,6,7,9...}，每个维度对应2个元素


		uniform=true：是否对得到的直方图数组进行归一化处理
		accumulate=false：在多个图像时，是否累计计算像素值得个数
		const float** ranges： 统计像素值的区间
	*/
void image_histogram_calculation_C3()
{
	Mat src = imread(imgAddr + "apple.jpg"),dst;
	cvtColor(src, src, COLOR_BGR2HSV);
	Mat c1,c2,c3;
	// 《2》使用多通道C风格（使用规范化）其实本文件就是C1的简化版本，变相证明了此函数只能计算单个通道
	// 不能一次性计算一个图像的3个通道得到1个一维直方图，只能分别使用1个通道计算得到1个直方图，因为channels元素的个数代表特征的含义
	// 也就是必须使用循环、容器等，不是给一个3通道图像就能同时计算3个通道的直方图。。。
	int histsize[] = { 256 }; //在每一维上直方图的个数，只有1个维度
	int nimages = 1; // 包含1个图像
	int channel = 1; // 元素个数=直方图的维度dims1，统计输入图像的哪个通道
	// 如果想都统计，重复塞入即可
	int channels[] = { 0,1,2 };
	int dims = 1;
	float range[] = { 0,256};
	const float* ranges[] = { range  };  // 指定直方图维度的范围
	//calcHist(&src, nimages, &channels[0], Mat(), c1, dims, histsize, ranges, true, false);
	//calcHist(&src, nimages, &channel, Mat(), c2, dims, histsize, ranges, true, false);
	//calcHist(&src, nimages, &channels[2], Mat(), c3, dims, histsize, ranges, true, false);
	int* chan = channels;
	calcHist(&src, nimages, chan++, Mat(), c1, dims, histsize, ranges, true, false);
	calcHist(&src, nimages, chan++, Mat(), c2, dims, histsize, ranges, true, false);
	calcHist(&src, nimages, chan++, Mat(), c3, dims, histsize, ranges, true, false);
	std::cout <<"c1.size() = "<< c1.size() << std::endl; // 1 x 256 , channels=1
	
	int hist_h = 400; // 直方图宽度512，高度800
	int hist_w = 1024;
	int bin_w = hist_w / histsize[0]; // bin的宽度 
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	double alpha = 0.0;
	double beta = histImage.rows; // 400
	int normType = NORM_MINMAX;
	int dtype = -1;
	Mat mask = {};
	normalize(c1, c1, alpha, beta, normType, dtype, mask);
	normalize(c2, c2, alpha, beta, normType, dtype, mask);
	normalize(c3, c3, alpha, beta, normType, dtype, mask); 
	Scalar B(255,0,0),G(0,255,0),R(0,0,255);

	for (int i = 1; i < *histsize; i++)
	{
		int x1 = (i - 1) * bin_w;
		int x2 = i * bin_w;
		int y1_c1 = cvRound(c1.at<float>(i - 1)); 
		int y2_c1 = cvRound(c1.at<float>(i));
		int y1_c2 = cvRound(c2.at<float>(i - 1));
		int y2_c2 = cvRound(c2.at<float>(i));
		int y1_c3 = cvRound(c3.at<float>(i - 1));
		int y2_c3 = cvRound(c3.at<float>(i));
		line(histImage,Point(x1, y1_c1),Point(x2, y2_c1),B, 2, LINE_AA);
		line(histImage, Point(x1, y1_c2), Point(x2, y2_c2), G, 2, LINE_AA);
		line(histImage, Point(x1, y1_c3), Point(x2, y2_c3), R, 2, LINE_AA);
	}
	imshow("histImage", histImage);
	waitKey(0);
	destroyAllWindows();
	// 《3》使用单通道STL风格（使用规范化）

	// 《4》使用多通道STL风格（使用规范化）

		//std::vector<int> histsize2 = { 256,256,256 };
	//calcHist(images, channels1, Mat(), hists, histsize2, Ranges, false);
	//std::vector<int> channels1 = { 0,1,2 };
	//const std::vector<float > Ranges = { 0,256 };

}
