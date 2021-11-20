#include "primary.h"
using namespace cv;
void image_histogram_reverse_projection()
{
	// 反向投影是反应直方图模型在目标图像中的分布情况
	// 即用直方图模型在目标图像中寻找是否有相似的对象
	// 通常用HSV空间中的H、S两个通道直方图模型
	
	// 加载图片->转为HSV->计算直方图和归一化->计算反向投影图像
	// 
	
	Mat src = imread(imgAddr + "apple.jpg"), hsv;
	MatND dst;
	cvtColor(src, hsv, COLOR_BGR2HSV);
	dst.create(hsv.size(),hsv.depth());
	const int fromTo[] = { 2,0 }; // 首元素取0,1,2均正确，第二个元素只能取0,只能从第一个通道开始
	// 输入的矩阵的某些通道拆分复制给对应的输出矩阵的某些通道中,其中的对应关系就由fromTo参数指定
	//mixChannels(const Mat* src,int nsrc,Mat* dst ,int ndst,const int* fromTo,size_t npairs);
	// src：输入；nsrcs：输入图像个数，类似的dst和ndsts；
	//fromTo：第一个输入矩阵的通道标记范围为：0 ~ src[0].channels()-1
	// 第二个输入矩阵的通道标记范围为：src[0].channels() ~ src[0].channels()+src[1].channels()-1 以此类推
	// 数组fromTo的第一个元素即fromTo[0]应该填入输入矩阵的某个通道标记
	// fromTo的第二个元素即fromTo[1]应该填入输出矩阵的某个通道标记，这样函数就会把输入矩阵的fromTo[0]通道里面的数据复制给输出矩阵的fromTo[1]通道
	//总之就是一个输入矩阵的通道标记后面必须跟着个输出矩阵的通道标记
	//npairs：参数fromTo中的有几组输入输出通道关系，其实就是参数fromTo的数组元素个数除以2
	size_t nsrcs=1 ,ndsts=1,npairs = 1;
	mixChannels(&hsv, nsrcs,&dst, ndsts, fromTo, npairs); // 把源图像的第1个通道复制到dst上
	std::cout << "dst.channels() = "<<dst.channels() <<"	dst.size() = "<< dst.size() << std::endl; // dst.channels() = 1 dst.size() = [750 x 562]
	std::cout <<"dst.dims  = "<< dst.dims << std::endl; // dst.dims  = 2
	float range[] = { 0,256 };
	const float* ranges[] = { range };
	int histsize = 256;
	Mat h_hist;
	int nimages = 1;
	int chan = 0;
	int dims = 1;
	/*
	CV_EXPORTS void calcHist( const Mat* images, int nimages,
                          const int* channels, InputArray mask,
                          OutputArray hist, int dims, const int* histSize,
                          const float** ranges, bool uniform = true, bool accumulate = false );
	*/
	calcHist(&dst,nimages,&chan,Mat(),h_hist,dims, &histsize,ranges,true,false);
	//std::cout << h_hist << std::endl;
	normalize(h_hist,h_hist,0,255,NORM_MINMAX,-1,Mat()); // 0-255归一化
	Mat backImage;
	double scale = 1.0;
	bool uniform = true;
	calcBackProject(&dst,nimages,&chan,h_hist,backImage,ranges,scale, uniform);
	imshow("hsv", hsv);
	imshow("dst", dst);
	imshow("backImage", backImage);
	waitKey(0);
	destroyAllWindows();

}