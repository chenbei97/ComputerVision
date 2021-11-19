#include "primary.h"
#include <vector>
using namespace cv;
void image_histogram_calculation_STL3()
{
	// ��3��ʹ�õ�ͨ��STL���ʹ�ù淶����
// ��ͨ��������STL��˵�ǿ��Եĵ��Ǵ��С��

// ��4��ʹ�ö�ͨ��STL���ʹ�ù淶����
	// C1��ϱȽ��ң�����ʹ�õ��ǲ�ͬ��Mat�������������ʹ����vector���գ�Դͼ��䣬ͨ����һֱ0
	// C2��C1��ʵһ����ֻ����Դͼ�񲻱䣬ͨ������0��1��2��������û����
	// STL3Դͼ��ֱ��ʹ������
	Mat src = imread(imgAddr + "apple.jpg"); 
	cvtColor(src, src, COLOR_BGR2HSV);
	std::vector<Mat> srcs,dsts;
	split(src, srcs);
	int histsize = 256;
	int nimages = 1;
	int channel = 0; //ʹ������channelֻ��Ϊ0��
	int dims = 1;
	float range[] = { 0,256 };
	const float* ranges[] = { range };
	for (int i = 0; i < 3; i++)
	{
		dsts.push_back(Mat());
		calcHist(&srcs[i], nimages, &channel, Mat(), dsts[i], dims, &histsize, ranges, true, false);
	}
	int hist_h = 300; // ֱ��ͼ���512���߶�300
	int hist_w = histsize * 2;
	int bin_w = hist_w / histsize; // bin�Ŀ�� 
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	double alpha = 0.0;
	double beta = histImage.rows; // 400
	int normType = NORM_MINMAX;
	int dtype = -1;
	Mat mask = {};
	Scalar B(255, 0, 0), G(0, 255, 0), R(0, 0, 255);
	std::vector<Scalar> color = { B,G,R };
	for (int i =0 ; i< dsts.size() ; i++)
	{
		normalize(dsts[i], dsts[i], alpha, beta, normType, dtype, mask);
		for (int j = 1; j < histsize; j++)
		{
			int x1 = (j - 1) * bin_w;
			int x2 = j * bin_w;
			int y1 = cvRound(dsts[i].at<float>(j - 1));
			int y2 = cvRound(dsts[i].at<float>(j));
			line(histImage, Point(x1, y1), Point(x2, y2), color[i], 2, LINE_AA);
		}
	}
	imshow("histImage", histImage);
	waitKey(0);
	destroyAllWindows();



}