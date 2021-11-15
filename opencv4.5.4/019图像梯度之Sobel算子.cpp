#include "primary.h"
using namespace cv;
void image_gradient_sobel()
{
	// һ�׵����ݶ�
	// �Ľ��汾ΪScharr����
	// APT�����롢�����ͼ����ȡ�x����������dx��y����������dy�����Ӻ˴�Сksize(����������)
	// scale��delta��boardType
	int dx=1, dy = 1;
	int ksize = 5;
	int depth = -1;
	Mat src = imread(imgAddr + "apple.jpg"), dst;
	GaussianBlur(src, src, Size(3, 3), 1.0, 0.0, 4); // sigmaX
	Mat gray;
	cvtColor(src,gray,COLOR_BGR2GRAY);
	/*
	 �����ȣ�
	 ����ΪCV_8U,���Ϊ-1/CV_16S/CV_32F/CV_64F
	 CV_16U/CV_16S  --- > -1/CV_32F/CV_64F
	 CV_32F  --> -1/CV_32F/CV_64F
	 CV_64F --> -1/CV_64F
	*/
	int ddepth = CV_16S;//-1,CV_32F ͼ�������ָ�洢ÿ���������õ�λ��,Ҳ��������ͼ���ɫ�ʷֱ���
	// ��ddepth = -1ʱ�����ͼ�񽫾�����Դ��ͬ�����
	double scale = 1.0;
	double delta = 3.0;
	Mat temp, dst2;
	Sobel(gray,dst,ddepth,dx,0,ksize,scale,delta);
	Sobel(dst, dst, ddepth, 0, dy, ksize, scale, delta);
	// ����ʵ�ֶ�����ͼ�������е�ÿһ��Ԫ�� ʵ��saturate(alpha*x+beta)
	double alpha = 1.0, beta = 0;
	temp = dst.clone();
	convertScaleAbs(dst,dst,alpha,beta);
	// ���Ƶ�out = saturate(�� * im1 + �� * im2 + gamma)
	
	addWeighted(temp, 1.0, temp, 0, 0, dst2,ddepth); // ͼƬ��С����һ��

	Mat ddst;
	Scharr(gray, ddst, ddepth, dx, 0, scale, delta,4);//dx >= 0 && dy >= 0 && dx+dy == 1
	Scharr(ddst, ddst, ddepth, 0, dy, scale, delta,4);// û��ksize����
	convertScaleAbs(ddst, ddst, alpha, beta);
	imshow("dst",dst);
	imshow("dst2", dst2);
	imshow("ddst", ddst);
	waitKey(0);
	destroyAllWindows();
}