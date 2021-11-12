#include "primary.h"
using namespace cv;
void image_assignment_copy_clone()
{
	Mat src = imread("D:/VisualStudioItems/apple.jpg", IMREAD_COLOR);

	Mat src_assign = src; // ��ֵ

	Mat src_copy;
	src.copyTo(src_copy); // ����

	Mat src_clone = src.clone(); // ��¡

	// ���õĴ����հ�ͼ��ķ���
	Mat img1 = Mat::zeros(src.size() , src.type()); // ʹ������ͼ�������
	Mat img2 = Mat::ones(Size(220, 220), CV_8UC3);// 8λ�޷���������ͨ��
	
	img2 = 127; // ʹ��������ֵ
	img2 = Scalar(10, 20, 30); // ʹ��scalar��ֵ��Scalar��һ���ĸ�Ԫ�ص�������
	
	Scalar s1(0,255,255); // ��ɫ
	std::cout << s1 << std::endl;//[0, 255, 255, 0]
	img2 = s1; // ��Scalar����������ͨ���ϵ������з����İ��и���
	// std :: cout << img2 << std::endl; // ����ֱ�Ӵ�ӡ

	Mat img2_assign = img2; // ��ֵ
	img2_assign = Scalar(255, 0, 0);//��ɫ BGR
	imshow("img2_1",img2); // ��ɫ,˵���ı丳ֵ����Ҳ��ı��κ�����ָ��Ķ���

	Mat img2_clone = img2.clone();// �ı��¡���󲻻�ı䱻��¡����
	img2_clone = Scalar(0, 255, 0);
	imshow("img2_clone", img2_clone);// ��ɫ
	imshow("img2_2", img2);// ��ɫ,���ı�
	waitKey();
}