#include "primary.h"
#include <vector>
#include <iostream>
using namespace cv;
std :: string  convertToString(double d);
void image_histogram_comparison()
{
	// �������2��ͼ�����ֱ��ͼH1��H2����һ������ͬ�ĳ߶ȿռ�
	// ����H1��H2�ľ���Ƚ����Ƴ̶ȣ������Ƚ�ͼ������Ƴ̶�
	// �ȽϷ�����
	/*
	   Correlation ������ԱȽ� HISTCMP_CORREL
	   Chi-Square�������Ƚ� HISTCMP_CHISQR,HISTCMP_CHISQR_ALT
	   Intersection��ʮ�ֽ��� HISTCMP_INTERSECT
	   Bhattacharyya distance �� ���Ͼ��� HISTCMP_BHATTACHARYYA
	*/
	/*
	BGR->HSV
	����ֱ��ͼ ��һ����0-1֮��(y����.Ҳ���ǲ�ͬǿ�ȵ�Ƶ��)
	ʹ��4�ַ������бȽ�compareHist
	*/
	const std :: string imgName1 = "goal1.png";
	const std::string imgName2 = "goal2.png";
	Mat src1 = imread(imgAddr + "basketball1.jpg");
	Mat src2 = imread(imgAddr + "basketball2.jpg");
	//selectROI("win",src2,true,true);
	resize(src2,src2,src1.size());
	//cvtColor(src1, src1,COLOR_BGRA2RGB);
	//cvtColor(src2, src2, COLOR_BGRA2RGB);
	cvtColor(src1, src1, COLOR_BGR2HSV);
	cvtColor(src2, src2, COLOR_BGR2HSV);
	
	
	int channels[] = {2,1}; // ָ��2��ͼ������ļ���ͨ��,ͼ��1��3ͨ��,ͼ��2��2ͨ��
	int* chan = channels;
	int dims = 1; // ֱ��ͼͨ���� 
	int nimages = 1; // 1��ͼ��
	int histsize[] = {256,128}; // 256��bin 
	float range1[] = { 0,256 }; // ͨ����Χ
	float range2[] = { 0,128 };
	const float* ranges[] = { range1 , range2 }; // һ������ָ��,�����ڵ�Ԫ����3������

	// ���ڴ洢ֱ��ͼ�ľ���
	MatND dst1,dst1_, dst2;
	calcHist(&src1,nimages,&channels[0],Mat(),dst1,dims,histsize,ranges,true,false); 
	calcHist(&src1, nimages, channels, Mat(), dst1_, dims, histsize, ranges, true, false);
	//std::cout << dst1 << std::endl; // [1 x 256] ���벻ͬ��ͨ�����Էֱ�õ���Ԫ��Ϊ6678��3177��1
	// std::cout << dst1_ << std::endl; // ���һ����֤������channels�ʹ���&channels[0]��һ����
	// ��һ��˵��һ��ֻ�ܴ���1��ͨ��������������ĺ����ڲ����channels++ͬʱ������ͨ��
	double alpha = 0, beta = 1; // ��׼��һ��
	// dst = (src - min(src)) * (beta - alpha) / [ max(src) - min(src)] + alpha
	normalize(dst1,dst1,alpha,beta,NORM_MINMAX,-1,Mat()); // ��һ����0-1
	calcHist(&src2, nimages, &channels[1], Mat(), dst2, dims, histsize, ranges, true, false);
	normalize(dst2, dst2, alpha, beta, NORM_MINMAX, -1, Mat());
	int method = HISTCMP_CORREL;
	double match_coeff = compareHist(dst1,dst2,HISTCMP_CORREL);
	std::cout << "match_coeff = " << match_coeff << std::endl;
	
	std::vector<int> methods = { HISTCMP_BHATTACHARYYA,HISTCMP_CHISQR,
		HISTCMP_CHISQR_ALT,HISTCMP_HELLINGER,HISTCMP_INTERSECT,HISTCMP_KL_DIV };
	for (std::vector<int> ::const_iterator it = methods.begin(); it != methods.end(); it++)
	{
		std::cout << compareHist(dst1, dst2, *it) << std::endl;
	}
	putText(src2, convertToString(match_coeff),Point(50,50),FONT_HERSHEY_SCRIPT_COMPLEX,1.5,Scalar(0,255,0),2,8);
	imshow("src1", src1);
	imshow("src2", src2);
	waitKey(0);
	destroyAllWindows();
}
std::string  convertToString(double d)
{
	std::ostringstream os;
	if (os << d)
		return os.str();
	else
		return "input is null";
}