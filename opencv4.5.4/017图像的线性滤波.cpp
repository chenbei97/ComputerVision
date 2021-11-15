#include "primary.h"
using namespace cv;
void image_linear_filtering()
{
	// ��������
	// robert����[1,0][0,-1]��[0,1][-1,0]
	// sobel����[-1,0,1][-2,0,2][-1,0,1] �� [-1,-2,-1][0,0,0][1,2,1]
	// ������˹���� [0,-1,0][-1,4,-1][0,-1,0]
	Mat src = imread(imgAddr + "apple.jpg"), dst1,dst2;
	Mat kernel1 = (Mat_<float>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
	Mat kernel2 = Mat::ones(Size(3, 3), CV_32F) / 9; 
	//Mat_< double > ( 3,3 )ֻ�ǹ�����ʽMat��һ�ַ���
	double delta = 0;
	filter2D(src, dst1, -1, kernel1,Point(-1,-1),delta,4); // delta�����Ǽ������������+delta
	filter2D(src, dst2, -1, kernel2, Point(-1, -1), delta, 4);
	bitwise_not(dst1,dst1);
	//bitwise_not(dst2, dst2);
	imshow("dst1",dst1);
	imshow("dst2", dst2);
	waitKey(0);
	destroyAllWindows();
}