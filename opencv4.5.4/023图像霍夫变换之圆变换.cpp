#include "primary.h"
using namespace cv;
void image_hough_transform_circle()
{
	// ԭ��ƽ��������Բ�ĵ�ת�����������C(x0,y0,r)���̴��м���ֵ
	// ���������У���Ҫ����ֵ�˲�
	// �����ڲ��ǻ���ͼ���ݶȵ�ʵ�֣����ȼ���Ե���ֿ��ܵ�Բ��
	// Ȼ��Ӻ�ѡԲ�ļ����Ӧ��Ѱ뾶�ҵ���Բ
	Mat src = imread(imgAddr + "shape.jpg");
	std::cout << imgAddr + "shape.jpg" << std::endl;
	Mat msrc;
	medianBlur(src,msrc,3);
	Mat gray_src;
	cvtColor(msrc, gray_src, COLOR_BGR2GRAY);
	//if (src.empty() != 1)
	//	std::cout << "image load successful..." << std::endl;
	//else
	//{
	//	std::cout << "image null..." << std::endl;
	//	return;
	//}
	
	Mat gray;
	unsigned int threshold = 50 ;
	Canny(gray_src,gray, threshold, (double)threshold * 2);
	std::cout << "gray.empty() = " << gray.empty() << std :: endl; // =0 ��Ϊ��
	int minR = 2, maxR = 200; // Բ���ڵ���С�����뾶
	double minDist = 2; //����Բ��֮�����̾���, ���С��2��Ϊ��ͬ��Բ
	double param1 = (double)threshold * 2, param2 =30; // param1  ��Ե�����edgeʹ�õĸ���ֵparam2 ���ĵ��ۼ�����ֵ-��ѡԲ��
	// Ĭ�϶���100
	int method = HOUGH_GRADIENT; // ��ⷽ�����ݶ����
	// HOUGH_GRADIENT_ALT,HOUGH_MULTI_SCALE,HOUGH_STANDARD
	double dp = 1;
	std::vector<Vec3f> circles; // ����Բ�������R
	HoughCircles(gray, circles,method,dp,minDist ,param1,param2,minR,maxR);
	for (size_t i = 0; i < circles.size(); i++)
	{
		std::cout << circles[i] << std::endl;
		Point center(circles[i][0], circles[i][1]);
		double radius = circles[i][2];
		if ( radius > 120 && radius < 130)
			circle(src, center, radius, Scalar(0, 0, 255), 1);
	}
	imshow("gray", gray);
	imshow("src",src);
	waitKey(0);
	destroyAllWindows();

}