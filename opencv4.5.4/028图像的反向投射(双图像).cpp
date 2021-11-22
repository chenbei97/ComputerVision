#include "primary.h"
using namespace cv;
void image_histogram_reverse_projection_double()
{
	/*
	����ͶӰ�Ƿ�Ӧֱ��ͼģ����Ŀ��ͼ���еķֲ����
	 ����ֱ��ͼģ����Ŀ��ͼ����Ѱ���Ƿ������ƵĶ���
	1��������ͼ������Ͻ�(0,0)��ʼ���и�һ��(0,0)��(10,10)����ʱͼ��
��2��������ʱͼ���ֱ��ͼ��
��3������ʱͼ���ֱ��ͼ��ģ��ͼ���ֱ��ͼ�Աȣ��ԱȽ����Ϊc��
��4��ֱ��ͼ�ԱȽ��c�����ǽ��ͼ��(0,0)��������ֵ��
��5���и�����ͼ���(0,1)��(10,11)����ʱͼ�񣬶Ա�ֱ��ͼ������¼�����ͼ��
��6���ظ���1������5����ֱ������ͼ������½ǡ�
	 ����ͼƬ->תΪHSV->����ֱ��ͼ�͹�һ��->���㷴��ͶӰͼ��

	CV_EXPORTS void calcHist( const Mat* images, int nimages,
						const int* channels, InputArray mask,
						OutputArray hist, int dims, const int* histSize,
						const float** ranges, bool uniform = true, bool accumulate = false );
	*/
	
	
	Mat src = imread(imgAddr + "starry_sky_src.jpg"), templ_hsv,src_hsv;
	Mat templ = imread(imgAddr + "starry_sky_template.jpg");
	cvtColor(templ, templ_hsv, COLOR_BGR2HSV);
	cvtColor(src, src_hsv, COLOR_BGR2HSV);
	int h_bins = 5; int s_bins = 5;
	int histSize[] = { h_bins, s_bins }; // ֱ��ͼ�Ƕ�ά����,ʹ����H��S����ͨ��
	Mat templ_hist;// ģ��ͼ���ֱ��ͼ

	//ȡֵ��Χ��hΪ0-180��sȡֵΪ0-255��vȡֵ��0-255
	float h_ranges[] = { 0, 180 }; // hue��ɫ�ı仯
	float s_ranges[] = { 0, 256 }; // saturation���Ͷȵı仯
	const float* ranges[] = { h_ranges, s_ranges };
	int channels[] = { 0, 1 }; // ͬʱ��2��ͨ����Ϊ��ͬ����м���
	calcHist(&templ_hsv, 1, channels, Mat(), templ_hist, 2, histSize, ranges, true, false);
	std::cout <<"templ_hist.size() = "<< templ_hist.size() << std::endl; // 32��32 �����Լ�ѡ�������ֱ��ͼ��С
	// ����Ǹ������鲻��������ʾ,�ȹ�һ����255
	normalize(templ_hist, templ_hist, 0, 255, NORM_MINMAX, -1, Mat()); // 0-255��һ��

	int nimages = 1;
	int dims = 1;
	double scale = 1.0;
	bool uniform = true;
	Mat backImage; // ʹ��ģ��ֱ��ͼ����Ͷ��Դͼ��õ��µ�ͼ��
	calcBackProject(&src_hsv,nimages,channels, templ_hist,backImage,ranges,scale, uniform);
	std::cout << "src_hsv.size() = " << src_hsv.size() << "   backImage.size() = "<<backImage.size() << std::endl;
	// src_hsv.size() = [1200 x 900]   backImage.size() = [1200 x 900]
	
	imshow("src_hsv", src_hsv);
	imshow("templ_hsv", templ_hsv);
	imshow("backImage", backImage);
	waitKey(0);
	destroyAllWindows();

}