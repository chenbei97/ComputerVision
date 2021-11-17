#include "primary.h"
#include <vector>
using namespace cv;
//for (int row = 0; row < gray.rows; row++)
//{
//	uchar *current_row = gray.ptr<uchar>(row);
//	for (int col = 0; col < gray.cols; col++)
//	{
//		std::cout << "(" << col << ","<<row<<") = " << (int)*current_row << std::endl;
//	}
//}
void image_histogram_calculation()
{
	// 直方图属性：dims=1，灰度图
	// bins：维度子区域的大小划分 bins=256，划分为256个级别
	// range：值得范围，灰度值在[0,255]
	Mat src = imread(imgAddr + "apple.jpg"), dst;
	std ::vector<Mat> images; 
	split(src, images); // 输出是一个Mat的数组指针,可用容器实现
	std::vector<std::string> strs = {"blue","green","red"};

	// 3通道图像展示
	for (int i = 0; i < images.size(); i++)
	{
		std::cout << "images[i].size() = " << images[i].size() << std::endl;
		imshow(strs[i], images[i]);
	}
	waitKey(0);
	destroyAllWindows();
	
	/*
		calcHist( const Mat* images, int nimages,
			const int* channels, InputArray mask,
			OutputArray hist, int dims, const int* histSize,
			const float** ranges, bool uniform = true, bool accumulate = false
		images ： 输入图像的指针
		nimages：输入图像的个数
		channels：需要统计直方图的第几通道
		dims ：需要统计直方图通道的个数
		mask ： 掩膜，计算掩膜内的直方图 一般Mat()
		hist ：输出直方图，要求是数组类型
		histSize：指的是直方图分成多少个区间，就是 bin的个数
		uniform=true：是否对得到的直方图数组进行归一化处理
		accumulate=false：在多个图像时，是否累计计算像素值得个数
		const float** ranges： 统计像素值的区间
	*/
	// 输入图像指针,图像数目、通道数、输入mask(可选)、输出的直方图、维数
	// 直方图级数、值域范围、uniform(true)、accumulate(false)
	int  histsize = 256; // 256个bin
	float range[] = { 0,256 };// 2个元素的数组,说明像素的范围
	std::cout << "range = " << range << std::endl; // range = 000000B4094FF258 *range=0
	const float *histRange = { range }; // 指向数组首地址的指针 去掉大括号也可以
	std::cout <<"histRange[1] = "<<  histRange[1] << std::endl; // *histRange = 0 histRange = range
	Mat b_hist, g_hist, r_hist;
	std::vector<Mat> hists = { b_hist, g_hist, r_hist };// 输出直方图
	int nimages = 1; // 输入图像的个数
	int current_channel = 0;  // 
	int* channels = &current_channel; // 灰度图只有1个通道
	int dims = 1; // 需要统计直方图通道的个数 这里循环对灰度图处理 所以为1
	
	/*
	因为histRange后面还用，所以测试的程序注释掉
	如果复盘想使用这段测试，务必把后续的程序注释掉
	histRange++;
	//histRange++; // 多加一次就溢出
	// range++; 是非法的 这里体现的是数组 无法++
	std::cout << "*histRange++ = " << *histRange << std::endl; // *histRange++ = 256
	// 这说明histRange是一个指向数组的指针,++可以访问数组的元素，但不是指针数组
	
	//1) 验证histRange是否是指针数组
	float range_[] = { 1,2,3 };
	//const float* p = { range ,range_ }; // 非法,p是指向数组的指针
	const float* p[] = { range ,range_ }; // 现在的p才是指针数组
	// p++;  非法,指针数组是不能++的
	std::cout <<"*p = "<< * p << "	*p[0] = "<< * p[0] << std::endl; // 前者是第一个数组的首地址,后者是第一个数组首元素

	// 2) 验证const float *histRange = { range }和 const float *histRange =  range 是否相同
	const float* p1 = range;
	p1++;
	//p1++;// 多加一次就溢出 和上面是一样的
	std::cout << "*p1++ = " << *p1 << std::endl; // *p1++ = 256 结论是完全相同
	*/

	// 后续的程序
	// 计算直方图
	for (int i = 0; i < 3; i++)
	{
		std::cout << "images[i].size() = " <<images[i].size() << std::endl; // 确认可以坐标索引
		std::cout << "hists[i].size() = " << hists[i].size() << std::endl; // 确认装载容器没问题[0,0]
		calcHist(&images[i], nimages, channels, Mat(), hists[i], dims, &histsize, &histRange, true, false);
		std::cout << "hists[i].size() = " << hists[i].size() << std::endl; // 确认装载容器存储了内容[1,256]
	}
	// 检测b_hist, g_hist, r_hist 是否也发生了变化
	std::cout << "b_hist.size() = " << b_hist.size() << std::endl; 
	// b_hist.size() = [0 x 0] 没有变化 说明并不是引用，必须使用hists[ ]

	// 归一化
	int hist_h = 400; // 直方图宽度512，高度400
	int hist_w = 512;
	int bin_w = hist_w / histsize; // bin的宽度 是总宽度/ bin的个数 512/256 = 2
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0)); // rows ,cols 用于绘制直方图的图像 3通道 
	std::cout << "histImage.size() = " << histImage.size() <<std::endl;//histImage.size() = [512 x 400]
	 

	double alpha = 0.0; //  如果norm_type为NORM_MINMAX 是范围归一化，则alpha为最小值
	// 如果norm_type为其他类型，则为归一化要乘的系数
	double beta = histImage.rows; // 如果norm_type为NORM_MINMAX ，则beta为最大值 
	// 如果norm_type为其他类型，beta被忽略，此处不会被用到，一般传入0
	std::cout << "beta = " << beta <<std::endl; // beta = 400
	int normType = NORM_MINMAX;
	int dtype = -1; // 如果取负值时，dst与src同样的类型,否则dst和src有同样的通道数,且此时图像深度为CV_MAT_DEPTH(dtype)
	//归一化类型，常见的有NORM_L1, NORM_L2, NORM_INF, NORM_MINMAX
	Mat mask = {}; // 可选操作掩膜
	//std::cout << hists[0] << std::endl; // 没归一化前得到的都是整数,代表不同强度的频率个数几万到几十
	
	for (int i = 0; i < 3; i++)
	{
		// 但是纵轴不能显示几万，所以需要对纵轴归一化，纵轴高度400
		// alpha =0 , beta = 512 对直方图[3,256]的每个通道256个元素归一化到0-512之间
		// 但是2个宽度显示1个值
		normalize(hists[i], hists[i],alpha,beta, normType,dtype,mask);
		//std::cout <<"hists["<<i<<"].size() = "<< hists[i].size() << std::endl;//hists[i].size() = [1 x 256]
	}
	// std::cout << hists[0] << std::endl; // 查看归一化的情况 值在0-400之间 便于显示
	// 都是浮点数后续还需要取整处理


	int j = 0;
	Scalar color;
	for (std::vector<Mat> ::const_iterator it = hists.begin(); it != hists.end(); it++)
	{

		Mat T = *it; // 每个通道的直方图循环：例如先开始b_hist , 有256个元素 依次代表0,1,2,,,255的个数
		// 此时已经归一化好到0-400之间可进行显示，但是记得先取整
		std::cout << "j = " << j << std::endl;
		//if (j == 0)
		//	color = { 255, 0, 0 };
		//else if (j == 1)
		//	color = {0, 255, 0};
		//else 
		//	color = { 0, 0, 255 };
		switch (j)
		{
			case 0:
				color = { 255, 0, 0 }; // 必须用花括号,不能用圆括号
				break;
			case 1:
				color = { 0, 255, 0 };
				break;
			case 2:
				color = { 0, 0, 255 };
				break;
		}
		j++;

		for (int i = 1; i < histsize; i++) // 每个通道的所有bin循环 1,2,..,255
		{
			int y1 = cvRound(T.at<float>(i - 1)); // 第1个点恰好是400
			int y2 = cvRound(T.at<float>(i));
			int x1 = (i - 1) * bin_w;
			int x2 = i * bin_w;
			//std::cout << "(x1,y1) = " << "(" << x1 << "," << y1 << ")"
			//	<< "   (x2,y2) = " << "(" << x2 << "," << y2 << ")" << std::endl; // 每个点的坐标画线
			line(histImage,
				Point(x1, y1),
				Point(x2, y2),
				color, 2, LINE_AA);
		}
	}

	imshow("histImage", histImage);
	waitKey(0);
	destroyAllWindows();
}