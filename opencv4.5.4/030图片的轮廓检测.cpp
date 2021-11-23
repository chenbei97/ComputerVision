#include "primary.h"
using namespace cv;
#include <vector>
void image_contour_detection()
{
	/*
	 void findContours( InputArray image, OutputArrayOfArrays contours,
                              OutputArray hierarchy, int mode,
                              int method, Point offset = Point());
	void findContours( InputArray image, OutputArrayOfArrays contours,
                              int mode, int method, Point offset = Point());
	image������Ķ�ֵͼ��
	contours�����ص�����
	hierarchy����ͼ�����˽ṹ����ѡ���������㷨����ͼ������˽ṹʵ��
	method ��Ѱ�������ķ�����CHAIN_APPROX_NONE��CHAIN_APPROX_SIMPLE��
	CHAIN_APPROX_TC89_KCOS��CHAIN_APPROX_TC89_L1
	mode���������ص�ģʽ��RETR_CCOMP��RETR_FLOODFILL��RETR_LIST
	RETR_TREE ��RETR_EXTERNAL
	offset���������ص�λ��(Ĭ����λ��)

	void drawContours( InputOutputArray image, InputArrayOfArrays contours,
						int contourIdx, const Scalar& color,
						int thickness = 1, int lineType = LINE_8,
						InputArray hierarchy = noArray(),
						int maxLevel = INT_MAX, Point offset = Point() );
	image�����Ƶ�ͼ��
	contours��findContours���ص�ȫ����������
	contourIdx������������
	color����ɫ
	thickness��lineType ����ȡ�����
	hierarchy��ͼ�����˽ṹ
	maxLevel����������0��ʾֻ���Ƶ�ǰ��1��ʾ���Ƶ�ǰ������Ƕ������
	offset��ƫ��
	*/
	// �Ҷ�ͼ->canny��Ե���->Ѱ������->��������
	Mat src = imread(imgAddr + "shape.jpg"),gray,canny;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	double threshold1 = 50;
	double threshold2 = 2 * threshold1;
	int  apertureSize = 3;
	bool L2gradient = true;
	Canny(gray,canny,threshold1,threshold2,apertureSize,L2gradient);
	std :: vector<std :: vector<Point>>contours; // ���������ж�����ÿ�������ж����
	std::vector<Vec4i> hierarchy; // ���˽ṹ4��ֵ����ȷ������Ҫ����4ֵ����
	int mode = RETR_TREE;
	int method = CHAIN_APPROX_SIMPLE;
	findContours(gray,contours,hierarchy,mode,method,Point(0,0));
	RNG rng;
	// ����ʹ����ȡ��������
	for (std::vector<std::vector<Point>>::const_iterator it = contours.begin(); it != contours.end(); it++)
	{
		std::vector<Point> contour = *it;
		//Scalar color = Scalar(rng.uniform(0,255) ,rng.uniform(0,255) ,rng.uniform(0,255) );
		Scalar color(0, 0, 255);
		for (size_t it1 =1 ; it1 < contour.size() ; it1++)
		{
			Point point1 = contour[it1-1];
			Point point2 = contour[it1];
			line(src,point1,point2,color,2);
			std::cout << "point1 = " << point1 << "	point2 = " <<point2 << std::endl;
		}
	}

	 //Ҳ�������û�������������������contourIdx����
	Mat src_ = src.clone();
	for (size_t i = 0; i < contours.size(); i++)
	{
		//Scalar color (rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		Scalar color(0, 255, 0);
		int contourIdx = i;
		drawContours(src_,contours, contourIdx,color,2,8,hierarchy,0,Point(0,0));
	}
	
	imshow("line",src);
	imshow("drawContours", src_);
	waitKey(0);
	destroyAllWindows();
	
}