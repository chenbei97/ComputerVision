#include "primary.h"
using namespace cv;
#include <vector>
void image_geometric_central_moment()
{
	/*
	���ľء����ξ����һ�����ľ�

	Moments moments( InputArray array, bool binaryImage = false );
	binaryImage���Ƿ�Ϊ��ֵͼ��

	double contourArea( InputArray contour, bool oriented = false );
	contour��������������
	oriented��Ĭ�Ϸ��ؾ���ֵ
	���������������

	double arcLength( InputArray curve, bool closed );
	curve��������������
	closed�������Ƿ��Ǳպϵ�
	�����������߻���

	��ȡ��Ե->��������->����ÿ������������(��)�����������
	*/
	Mat src = imread(imgAddr + "shape.jpg"), gray, canny;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	blur(gray, gray, Size(3, 3), Point(-1, -1));
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

	std::vector<Moments> contour_moments(contours.size());
	std::vector<Point2f> centers(contours.size());// �洢ÿ���ؼ������������λ��
	bool binaryImage = false;
	bool oriented = false; // ����������ؾ���ֵ
	bool closed = true;
	int radius = 100;
	for (size_t i = 0; i < contour_moments.size(); i++)
	{
		contour_moments[i] = moments(contours[i],binaryImage);
		float x0 = static_cast<float>(contour_moments[i].m10 / contour_moments[i].m00);
		// m10��һ��x�����,m01��һ��y�����,m00����׾�
		// x0 = m10/m00  ;  y0 = m01 / m00
		float y0 = static_cast<float>(contour_moments[i].m01 / contour_moments[i].m00);
		centers[i] = Point(x0,y0);
		std::cout << "centers[i] = " << centers[i] << std::endl;
		double area = contourArea(contours[i],oriented);
		double _length =arcLength(contours[i],closed);
		circle(src, centers[i], radius, Scalar(0, 0, 255), 2, 21, 0);
		std::cout << "area = " << area << "   length = " << _length << std::endl;
	}
	imshow("src",src);
	waitKey(0);
	destroyAllWindows();


	
}