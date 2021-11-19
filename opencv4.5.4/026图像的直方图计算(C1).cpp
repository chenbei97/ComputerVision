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
void image_histogram_calculation_C1()
{
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
		images ： 输入图像的指针,可以是单个3通道的图片,也可以是多个图像组成的数组
		nimages：输入图像的个数
		channels：需要统计直方图的第几通道，可以是C风格数组也可以是STL Vector
		通道是按照顺序编排的，images[0]的前3个通道编号为0,1,2，images[1]为3,4,5，以此类推
		channels的元素个数就是直方图的维度，即对应于某个输入数组的某个通道
		
		mask ： 掩膜，计算掩膜内像素的直方图 一般Mat()
		mask必须是一个8bit数组且和images的输入数组大小相同

		hist ：输出直方图，要求是数组类型
		dims ：需要统计直方图通道的个数，就是channels中的元素个数

		histSize：指的是直方图分成多少个区间，就是 bin的个数
		可以是C风格数组也可以是STL容器，元素的个数也应该等于dims

		ranges：用于指定每个通道维度的直方图的范围，所以ranges本身的长度等于dims
		①可以使用C风格也可以使用STL，如果是C风格：每个元素ranges[i]应当是另一个数组
		以下参数以具有3个通道的1个图片进行解释，那么 int channels[] = {0,1,2} , dims=3 ,nimages=1
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

	// 《1》使用单通道C风格（使用规范化）

	int  histsize = 256; // 该通道具有256个bin 
	int histsize1[] = { 256 }; // 传入&histsize或者histsize1都是正确的
	int nimages = 1; // 输入图像的个数
	int channels = 0; // 灰度图只有1个通道
	int channels1[] = { 0 }; // 也可以使用数组,0表示第0个通道,传入&channels和channels都可以
	int dims = 1; // 需要统计直方图通道的总个数 这里循环对灰度图处理 所以为1

	float range[] = { 0,256 };// 2个元素的数组,说明像素的范围，只需要传递总体区间的上下界
	std::cout << "range = " << range << std::endl; // range = 000000B4094FF258 *range=0
	const float *ranges = { range }; // 指向数组首地址的指针 去掉大括号也可以
	std::cout <<"ranges[1] = "<< ranges[1] << std::endl; // *histRange = 0 histRange = range

	Mat b_hist, g_hist, r_hist;
	std::vector<Mat> hists = { b_hist, g_hist, r_hist };// 输出直方图
	// 按说只需要传递b_hist一个即可但是希望循环处理3个灰度通道所以使用了容器，后边可以不使用循环直接对3通道处理

	/*
	因为ranges后面还用，所以测试的程序注释掉
	如果复盘想使用这段测试，务必把后续的程序注释掉
	ranges++;
	//ranges++; // 多加一次就溢出
	// range++; 是非法的 这里体现的是数组 无法++
	std::cout << "*ranges++ = " << *ranges << std::endl; // *ranges++ = 256
	// 这说明ranges是一个指向数组的指针,++可以访问数组的元素，但不是指针数组
	
	//1) 验证ranges是否是指针数组
	float range_[] = { 1,2,3 };
	//const float* p = { range ,range_ }; // 非法,p是指向数组的指针
	const float* p[] = { range ,range_ }; // 现在的p才是指针数组
	// p++;  非法,指针数组是不能++的
	std::cout <<"*p = "<< * p << "	*p[0] = "<< * p[0] << std::endl; // 前者是第一个数组的首地址,后者是第一个数组首元素

	// 2) 验证const float *ranges = { range }和 const float *ranges =  range 是否相同
	const float* p1 = range;
	p1++;
	//p1++;// 多加一次就溢出 和上面是一样的
	std::cout << "*p1++ = " << *p1 << std::endl; // *p1++ = 256 结论是完全相同
	*/
	for (int i = 0; i < 3; i++) // 使用单通道的C风格，循环处理3个灰度通道
	{
		std::cout << "images[i].size() = " <<images[i].size() << std::endl; // 确认可以坐标索引
		std::cout << "hists[i].size() = " << hists[i].size() << std::endl; // 确认装载容器没问题[0,0]
		calcHist(&images[i], nimages, channels1, Mat(), hists[i], dims, histsize1, &ranges, true, false); //C风格
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