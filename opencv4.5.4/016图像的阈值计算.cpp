#include "primary.h"
using namespace cv;
Mat src=imread(imgAddr + "apple.jpg") , dst;
int maxval = 255;
int currval = 127;
int currtype = 0;
int max_threshold_type = 4;
const std::string barname1 = "thresholdValue";
const std::string barname2 = "thresholdType";
const std::string winname = "win";
void image_threshold_calculate_callback(int, void*);
void image_threshold_calculate()
{
	std::cout << THRESH_BINARY << THRESH_BINARY_INV << THRESH_TRUNC
		<< THRESH_TOZERO << THRESH_TOZERO_INV << std :: endl; // 0,1,2,3,4
	Mat gray;
	cvtColor(src,gray,COLOR_BGR2GRAY); // ����ҶȻ�
	Mat temp = Mat :: zeros(gray.size(), gray.type());
	double best_threshold = threshold(gray,temp,0,255,THRESH_OTSU | THRESH_BINARY); // �Զ����������ֵ
	std::cout << "best_threshold(ostu) = " << best_threshold <<std::endl;// best_threshold = 115
	best_threshold = threshold(gray, temp, 0, 255, THRESH_TRIANGLE | THRESH_BINARY);
	std::cout << "best_threshold(triangle) = " << best_threshold << std::endl;// best_threshold = 172
	// THRESH_BINARY��ֵ��ֵ��������ֵ����255
	// THRESH_BINARY_INV����ֵ��ֵ��������ֵ����0������Ϊ255
	// THRESH_TRUNC�ض���ֵ��������ֵ������ֵ����������
	//THRESH_OTSU��ѡ��ostu�㷨�Զ����������ֵ
	// THRESH_MASK
	//THRESH_TRIANGLE ��ʹ��triangle�㷨�Զ����������ֵ
	//THRESH_TOZERO��ֵ����������ֵ���䣬����Ϊ0
	//THRESH_TOZERO_INV����ֵ����������ֵΪ0�����򲻱�
	int* cval = &currval; // ��ֵ
	int* thresh = &currtype; // ��ֵ����
	namedWindow(winname,WINDOW_FREERATIO);//������Assertion failed (scn == 1 && dcn == 1)
	createTrackbar(barname1,winname,cval,maxval, image_threshold_calculate_callback);
	createTrackbar(barname2, winname, thresh, max_threshold_type, image_threshold_calculate_callback);
	image_threshold_calculate_callback(0, 0);
	waitKey(0);
}
void image_threshold_calculate_callback(int,void*)
{
	Mat gray;
	cvtColor(src,gray,COLOR_BGR2GRAY);
	//threshold(gray,dst,currval,maxval,THRESH_BINARY); // ��ֵ��ǰֵ�����ֵ
	threshold(gray, dst, currval, maxval, currtype);
	std::cout << "current threshold type = " << currtype << "	current threshold value = " <<currval << std::endl;
	imshow(winname,dst);

}