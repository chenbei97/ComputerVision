#include "primary.h"
using namespace cv;
void image_convex_hull()
{
	/*
	һЩ�㼯��, ϣ���ҵ��������ϵ���С͹����Σ���͹����graham�㷨
	ѡ��Y�������͵���Ϊ��ʼ�㣬��ΪP0����ʼ������ɨ�裬�������P1��..Pn
	����˳�����ݼ�����ǶȵĴ�С����ʱ�뷽��
	��ÿ����Pi��˵����Ӹõ㵼��͹����ת��ʱ(��ʱ��)�������ӣ���������ת����ɾ���õ�
	
	void convexHull( InputArray points, OutputArray hull,
                              bool clockwise = false, bool returnPoints = true );
	points�������ѡ�㣬����findContours
	clockwise��Ĭ��˳ʱ�뷽��
	returnPoints��true��ʾ���ص����
	*/
	// �Ҷ�ͼ->canny��Ե���->Ѱ������->͹�����
	Mat src = imread(imgAddr + "shape.jpg"), gray, canny; 
	cvtColor(src, gray, COLOR_BGR2GRAY);
	blur(gray,gray,Size(3,3),Point(-1,-1));
	double threshold1 = 50;
	double threshold2 = 2 * threshold1;
	int  apertureSize = 3;
	bool L2gradient = true;
	Canny(gray, canny, threshold1, threshold2, apertureSize, L2gradient);
	std::vector<std::vector<Point>>contours;
	std::vector<Vec4i> hierarchy;
	int mode = RETR_TREE;
	int method = CHAIN_APPROX_SIMPLE;
	findContours(gray, contours, hierarchy, mode, method, Point(0, 0));
	for (size_t i = 0; i < hierarchy.size(); i++)
	{
		std::cout << hierarchy[i] << std::endl;
	}
	bool clockwise=false, returnPoints=true;
	std::vector<std::vector<Point>>hull(contours.size());
	for (size_t  i = 0; i < hull.size(); i++)
	{
		convexHull(contours[i], hull[i], clockwise, returnPoints);
	}
	
	Scalar color1(0, 0, 255);
	Scalar color2(0, 255, 0);
	int contourIdx;
	Mat src_ = src.clone();
	for (size_t i = 0; i < hull.size(); i++)
	{
		contourIdx = i;
		drawContours(src, hull, contourIdx, color1, 2, 8, hierarchy, 0, Point(0, 0));
		drawContours(src_, contours, contourIdx, color2, 2, 8, hierarchy, 0, Point(0, 0));
	}
	imshow("hull", src);
	imshow("contours", src_);
	waitKey(0);
	destroyAllWindows();
}