#include "primary.h"
using namespace cv;
void image_blur()
{   // �����˲�
	// ��ֵ�˲�����˹�˲�����ֵ�˲� blur and GaussianBlur and medianBlur
	Mat im = imread(imgAddr + "eagle.jpg");
	// blur ����  �����롢��������ں����С�������С����ê������
	// GaussianBlur ���� �����롢��������ڴ�Сsize��sigmax��sigmay
	// medianBlur �Խ����������� , ���롢�����ksize���Ժ��ڵ�Ԫ��ͳ������
	// ���ڴ�СΪ�˱���ѡ�����⣬Ӧ��Ϊ����
	Mat im_blur, im_GaussianBlur, im_medianBlur;
	blur(im,im_blur,Size(11,11),Point(-1,-1),4);// 
	GaussianBlur(im,im_GaussianBlur,Size(11,11),11.0,11.0,4);
	medianBlur(im,im_medianBlur,13); // ksize > 1 and ����
	// ˫���˲����������롢��������ذ뾶d(�ṩ-1��������һ����������)
	//  ���ٲ�ֵ���ڵ����ػᱻ���㡢sigmaSpace(���ذ뾶��0,������ݴ˲����������ذ뾶)
	Mat im_bilateralFilter;
	int d = 15;
	double sigmaColor = 150;
	double sigmaSpace = 5;
	bilateralFilter(im,im_bilateralFilter,d, sigmaColor,sigmaSpace);
	namedWindow("ava", WINDOW_FREERATIO);
	namedWindow("gaussian", WINDOW_FREERATIO);
	namedWindow("median", WINDOW_FREERATIO);
	namedWindow("bilateral", WINDOW_FREERATIO);
	imshow("bilateral", im_bilateralFilter);
	imshow("ava", im_blur);
	imshow("gaussian", im_GaussianBlur);
	imshow("median", im_medianBlur);
	waitKey(0);
	destroyAllWindows();
}