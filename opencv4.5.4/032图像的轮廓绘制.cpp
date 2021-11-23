#include "primary.h"
using namespace cv;
#include <vector>
void image_rectangularand_circular_boxes()
{
	/*
	������Χ���ƾ���
	����RDP�㷨ʵ�֣�Ŀ���Ǽ��ٶ������������
	void approxPolyDP( InputArray curve,
								OutputArray approxCurve,
								double epsilon, bool closed );
	curve��������findContours��ĳһ�������ĵ㼯��
	approxCurve��RFP�㷨����ĵ㼯��,��������ͬ
	epsilon��ָ��ԭʼ�����������ֵ֮���������
	closed���Ƿ�պ�

	Rect boundingRect( InputArray array );
	�ú������㲢����ָ���㼯��Ҷ�ͼ��������ص���С���ϱ߽����
	���������findContours�õ��ĵ㼯��,Ҳ������RDP��һ��ɸѡ��ĵ㼯�ϣ���֮��1������

	void minEnclosingCircle( InputArray points,
									  CV_OUT Point2f& center, CV_OUT float& radius );
	points������ĵ㼯��
	center��Բ������洢����
	radius���뾶�洢����
	�ú���ʹ�õ����㷨���Ҷ�ά�㼯����С���Բ

	RotatedRect minAreaRect( InputArray points );
	����һ����ת�ľ������ġ��Ƕȵ�

	RotatedRect fitEllipse( InputArray points );
	������С��Բ�����ǵ㼯������5����

	double minEnclosingTriangle( InputArray points, CV_OUT OutputArray triangle );
	�����ҵ�һ����С����������Σ��������ΰ�Χ������2D�㼯�������������
	��ά����*��ɫ*��ʾ�������������*��ɫ��ʾ*
	Output vector of three 2D points defining the vertices of the triangle. The depth
	of the OutputArray must be CV_32F.
	*/
	Mat src = imread(imgAddr + "shape.jpg"),gray,canny; //balloon.jpg
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

	// ʹ��RDP�㷨����������
	std::vector<std::vector<Point>>contours_approxPoly(contours.size());
	double epsilon = 3; //ԭʼ�����������ֵ֮���������
	bool closed = true;
	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(contours[i] , contours_approxPoly[i],epsilon,closed);
		//std::cout << "contours��" << contours[i] << std::endl;
		//std :: cout << "contours_approxPoly��" <<contours_approxPoly[i] << std::endl;
	}
	std::vector<Rect> rects(contours_approxPoly.size()); // ��������
	std::vector<Point2f> centers(contours_approxPoly.size()); //  ���Բ�����Բ��
	std::vector<float> radiuses(contours_approxPoly.size()); // ע�����Ҫָ������������
	std::vector<RotatedRect> ellipses(contours_approxPoly.size());// ��Բ����

	std::vector<RotatedRect> minRects(contours_approxPoly.size()); // ��С��������
	Point2f pts[4]; // 4���㣺����+���
	
	std::vector<std::vector<Point2f>> triangles(contours_approxPoly.size());// ����������,һ���������3��������
	for (int i = 0; i < contours_approxPoly.size(); i++)
	{
		for (int j = 0 ; j < 3 ; j++)
			triangles[i].push_back(Point2f(CV_32F));
	}

	for (int i = 0; i < contours_approxPoly.size(); i++)
	{
		rects[i] = boundingRect(contours_approxPoly[i]);// ��ɸѡ��ĵ㼯�ϸ�ֵ������
		// std::cout << "i = " << i << "   rect = "<< rects[i] << std::endl; // ÿ����������1��������Ϳ�߶���
		// [669 x 521 from (0, 0)]
		minEnclosingCircle(contours_approxPoly[i],centers[i],radiuses[i]);
		
		//ellipses[i] = fitEllipse(contours_approxPoly[i]);
		// There should be at least 5 points to fit the ellipse
		//std::cout << "i = " << i << "    ellipses[i].center = "<<ellipses[i].center <<"   ellipses[i].angle = " << ellipses[i].angle << std::endl;
		
		minRects[i] = minAreaRect(contours_approxPoly[i]);
		//std::cout << "i = " << i << "    minRects[i].center = " << minRects[i].center << "   ellipses[i].angle = " << minRects[i].center << std::endl;
		minRects[i].points(pts);
		std::cout << "i = " << i << "   pts = " << *pts << std::endl;


		//minEnclosingTriangle(contours_approxPoly[i], triangles[i]);
		//std::cout << "i = " << i << "    triangles[i]= " << triangles[i]<< std::endl;
		
	}

	// ���ݷ��صı�Ҫ�������ƾ��κ�Բ��
	for (int i = 0; i < contours_approxPoly.size(); i++)
	{
		rectangle(src,rects[i],Scalar(0,0,255),2,8,0);
		circle(src,centers[i],radiuses[i],Scalar(0,255,0),2,8,0);
		for (int r = 0; r < 4; r++)
		{
			line(src,pts[r],pts[(r+1)%4],Scalar(255,0,0),2,8,0);
		}
	}
	imshow("src",src);
	waitKey(0);
	destroyAllWindows();
}