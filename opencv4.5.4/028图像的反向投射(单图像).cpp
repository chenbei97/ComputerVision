#include "primary.h"
using namespace cv;
void image_histogram_reverse_projection_single()
{
	// ����ͶӰ�Ƿ�Ӧֱ��ͼģ����Ŀ��ͼ���еķֲ����
	// ����ֱ��ͼģ����Ŀ��ͼ����Ѱ���Ƿ������ƵĶ���
	// ͨ����HSV�ռ��е�H��S����ͨ��ֱ��ͼģ��

	// ����ͼƬ->תΪHSV->����ֱ��ͼ�͹�һ��->���㷴��ͶӰͼ��
	// 

	Mat src = imread(imgAddr + "apple.jpg"), hsv;
	MatND dst;
	cvtColor(src, hsv, COLOR_BGR2HSV);
	dst.create(hsv.size(), hsv.depth());
	const int fromTo[] = { 2,0 }; // ��Ԫ��ȡ0,1,2����ȷ���ڶ���Ԫ��ֻ��ȡ0,ֻ�ܴӵ�һ��ͨ����ʼ
	// ����ľ����ĳЩͨ����ָ��Ƹ���Ӧ����������ĳЩͨ����,���еĶ�Ӧ��ϵ����fromTo����ָ��
	//mixChannels(const Mat* src,int nsrc,Mat* dst ,int ndst,const int* fromTo,size_t npairs);
	// src�����룻nsrcs������ͼ����������Ƶ�dst��ndsts��
	//fromTo����һ����������ͨ����Ƿ�ΧΪ��0 ~ src[0].channels()-1
	// �ڶ�����������ͨ����Ƿ�ΧΪ��src[0].channels() ~ src[0].channels()+src[1].channels()-1 �Դ�����
	// ����fromTo�ĵ�һ��Ԫ�ؼ�fromTo[0]Ӧ��������������ĳ��ͨ�����
	// fromTo�ĵڶ���Ԫ�ؼ�fromTo[1]Ӧ��������������ĳ��ͨ����ǣ����������ͻ����������fromTo[0]ͨ����������ݸ��Ƹ���������fromTo[1]ͨ��
	//��֮����һ����������ͨ����Ǻ��������Ÿ���������ͨ�����
	//npairs������fromTo�е��м����������ͨ����ϵ����ʵ���ǲ���fromTo������Ԫ�ظ�������2
	size_t nsrcs = 1, ndsts = 1, npairs = 1;
	mixChannels(&hsv, nsrcs, &dst, ndsts, fromTo, npairs); // ��Դͼ��ĵ�1��ͨ�����Ƶ�dst��
	std::cout << "dst.channels() = " << dst.channels() << "	dst.size() = " << dst.size() << std::endl; // dst.channels() = 1 dst.size() = [750 x 562]
	std::cout << "dst.dims  = " << dst.dims << std::endl; // dst.dims  = 2
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
	calcHist(&dst, nimages, &chan, Mat(), h_hist, dims, &histsize, ranges, true, false);
	//std::cout << h_hist << std::endl;
	normalize(h_hist, h_hist, 0, 255, NORM_MINMAX, -1, Mat()); // 0-255��һ��
	Mat backImage;
	double scale = 1.0;
	bool uniform = true;
	calcBackProject(&dst, nimages, &chan, h_hist, backImage, ranges, scale, uniform);
	imshow("hsv", hsv);
	imshow("dst", dst);
	imshow("backImage", backImage);
	waitKey(0);
	destroyAllWindows();

}