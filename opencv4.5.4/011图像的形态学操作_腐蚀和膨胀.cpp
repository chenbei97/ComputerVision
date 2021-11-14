#include "primary.h"
using namespace cv;
void image_corrosion_expansion()
{
	// ��ʴ�����������= �ṹ���� ������ ����ͼ�����С����ֵ
	// ���ͣ����������= �ṹ���� ������ ����ͼ����������ֵ
	Mat im = imread(imgAddr + "cascade.jpg",IMREAD_GRAYSCALE);
	Mat im_erode, im_dilate;
	Mat kernel1, kernel2;
	int shape = MORPH_RECT; // ���εĺ� 
	//MORPH_CROSS,MORPH_ELLIPSE,MORPH_DILATE,MORPH_ERODE
	// CV_Assert( shape == MORPH_RECT || shape == MORPH_CROSS || shape == MORPH_ELLIPSE );
	Size size(3,3);
	Point center(-1, -1); // �˵�������������ָ��,�Զ�����
	kernel1 = getStructuringElement(shape,size,center);//ȫ1
	kernel2 = getStructuringElement(shape, size, center);//�����ĽǶ���1
	std::cout << "kernel1 = \n" << kernel1 << "\nkernel2 = \n" << kernel2 << std::endl;
	erode(im, im_erode, kernel1);
	dilate(im, im_dilate, kernel2);
	namedWindow("im_erode", WINDOW_FREERATIO);
	imshow("im_erode", im_erode);
	namedWindow("im_dilate", WINDOW_FREERATIO);
	imshow("im_dilate", im_dilate);
	waitKey(0);
	destroyAllWindows();
	system("pause");
}