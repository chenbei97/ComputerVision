#include "primary.h"
using namespace cv;
void image_gradient_laplance()
{
	Mat src = imread(imgAddr + "apple.jpg"), dst;
	GaussianBlur(src, src, Size(3, 3), 1.0, 0.0, 4);
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	int ksize = 3;
	Laplacian(gray,dst,-1,ksize);// 二阶导数
	double alpha = 1.0, beta = 0;
	convertScaleAbs(dst, dst, alpha, beta); // 取绝对值
	threshold(dst, dst, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("dst", dst);
	waitKey(0);
	destroyAllWindows();
}
