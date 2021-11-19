#include "primary.h"
#include <vector>
using namespace cv;
/*
		calcHist( const Mat* images, int nimages,
			const int* channels, InputArray mask,
			OutputArray hist, int dims, const int* histSize,
			const float** ranges, bool uniform = true, bool accumulate = false

		images �� ����ͼ���ָ��,�����ǵ���ͼƬ,Ҳ�����Ƕ��ͼ����ɵ�����
		���е�ͼ�������ͬ������ȣ�CV_8U or CV_32F����ͬʱһ��ͼ������ж��channels

		nimages������ͼ��ĸ���
		channels��ʹ���������ݵĵڼ�ͨ����������C�������Ҳ������STL Vector
		ͨ���ǰ���˳����ŵģ�images[0]��ǰ3��ͨ�����Ϊ0,1,2��images[1]Ϊ3,4,5���Դ�����
		channels��Ԫ�ظ�������ֱ��ͼ��ά�ȣ�����Ӧ��ĳ�����������ĳ��ͨ��

		mask �� ��Ĥ��������Ĥ�����ص�ֱ��ͼ һ��Mat()
		mask������һ��8bit�����Һ�images�����������С��ͬ

		hist �����ֱ��ͼ��Ҫ������������
		dims ����Ҫͳ��ֱ��ͼͨ���ĸ���������channels�е�Ԫ�ظ���

		histSize��ָ����ֱ��ͼ�ֳɶ��ٸ����䣬���� bin�ĸ���,��ÿһά��ֱ��ͼ�ĸ���
		������C�������Ҳ������STL������Ԫ�صĸ���ҲӦ�õ���dims
		����ע�⣺�����ά����ָ����ά�ȣ����ֻͳ�ƻҶ�ֵ��Ƶ�ʣ���ʵ��1ά�ģ�����ж���������ݶȡ�����
		2��������ζ��ֱ��ͼ��3ά�ģ�x��y���ʾ2��������z�����ͬʱ������2�����������ظ���
		����������ζ��2ά��������-Ƶ����ֱ��ͼ

		ranges������ָ��ÿ��ͨ��ά�ȵ�ֱ��ͼ�ķ�Χ������ranges����ĳ��ȵ���dims
		�ٿ���ʹ��C���Ҳ����ʹ��STL�������C���ÿ��Ԫ��ranges[i]Ӧ������һ������
		���²����Ծ���3��ͨ����1��ͼƬ���н��ͣ���ô int channels[] = {0,1,2} , dims=1 ,nimages=1
		int histsize[] = {256,256,256} ÿ��ͨ�����ֳ�256��bins��Ҳ����ʹ�� std :: vector<int> histsize={256,256,256}
		��ranges[i]�Ľ���ȡ����uniform�Ƿ��һ������
		��uniform = true  ����[0,100)����ҿ�
		C���Ӧ��ָ��ÿ��ͨ��
		˵����i��ͨ����100����ֵ���ڵ�����ȳ������԰���ֵ(����ǿ��)����y���꣬����Ҫx���꣬x�ǵȼ��ı��ڻ�ͼ
		���������һ����uniform=false��˵���Զ���ˮƽ��࣬��i��ͨ���ֳ�histsize[i]��bins,��ranges[i]Ҳ������histsize[i]��Ԫ��
		ranges[i]�൱�ڸ������е�ˮƽ���꣬����{{0,2},{3,6},{7,9},{9,12},{17,19},{22,57}...{240,256}}��histsize[i]������Ȼ������ҿ�
		ÿ��Ԫ�ض�ָ���˵�ǰԪ�ص��½�(����)����һ��Ԫ�ص��Ͻ�(������)��˵���˾���bin��ʼ������Ϊ0,3,7,9,17,22,...��ÿ��bin�Ŀ�Ȳ�һ��
		��ranges[i]��STL���������
		����1��ͼƬ��3��ͨ����C���ָ���ķ�Χ����const float* ranges = {{0,256},{0,256},{0,256}}
		uniform=true��ʹ��STL�ʹ���vector<float> ranges = {0,256,0,256,0,256}
		uniform=false�����൱��ƽ̯C��������Ԫ�� �� vector={0,2,3,6,7,9...}��ÿ��ά�ȶ�Ӧ2��Ԫ��


		uniform=true���Ƿ�Եõ���ֱ��ͼ������й�һ������
		accumulate=false���ڶ��ͼ��ʱ���Ƿ��ۼƼ�������ֵ�ø���
		const float** ranges�� ͳ������ֵ������
	*/
void image_histogram_calculation_C3()
{
	Mat src = imread(imgAddr + "apple.jpg"),dst;
	cvtColor(src, src, COLOR_BGR2HSV);
	Mat c1,c2,c3;
	// ��2��ʹ�ö�ͨ��C���ʹ�ù淶������ʵ���ļ�����C1�ļ򻯰汾������֤���˴˺���ֻ�ܼ��㵥��ͨ��
	// ����һ���Լ���һ��ͼ���3��ͨ���õ�1��һάֱ��ͼ��ֻ�ֱܷ�ʹ��1��ͨ������õ�1��ֱ��ͼ����ΪchannelsԪ�صĸ������������ĺ���
	// Ҳ���Ǳ���ʹ��ѭ���������ȣ����Ǹ�һ��3ͨ��ͼ�����ͬʱ����3��ͨ����ֱ��ͼ������
	int histsize[] = { 256 }; //��ÿһά��ֱ��ͼ�ĸ�����ֻ��1��ά��
	int nimages = 1; // ����1��ͼ��
	int channel = 1; // Ԫ�ظ���=ֱ��ͼ��ά��dims1��ͳ������ͼ����ĸ�ͨ��
	// ����붼ͳ�ƣ��ظ����뼴��
	int channels[] = { 0,1,2 };
	int dims = 1;
	float range[] = { 0,256};
	const float* ranges[] = { range  };  // ָ��ֱ��ͼά�ȵķ�Χ
	calcHist(&src, nimages, &channels[0], Mat(), c1, dims, histsize, ranges, true, false);
	calcHist(&src, nimages, &channel, Mat(), c2, dims, histsize, ranges, true, false);
	calcHist(&src, nimages, &channels[2], Mat(), c3, dims, histsize, ranges, true, false);
	std::cout <<"c1.size() = "<< c1.size() << std::endl; // 1 x 256 , channels=1
	
	int hist_h = 400; // ֱ��ͼ���512���߶�800
	int hist_w = 1024;
	int bin_w = hist_w / histsize[0]; // bin�Ŀ�� 
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
	// ��3��ʹ�õ�ͨ��STL���ʹ�ù淶����

	// ��4��ʹ�ö�ͨ��STL���ʹ�ù淶����

		//std::vector<int> histsize2 = { 256,256,256 };
	//calcHist(images, channels1, Mat(), hists, histsize2, Ranges, false);
	//std::vector<int> channels1 = { 0,1,2 };
	//const std::vector<float > Ranges = { 0,256 };

}