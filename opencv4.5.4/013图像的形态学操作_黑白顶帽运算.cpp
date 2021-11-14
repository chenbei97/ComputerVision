#include "primary.h"
using namespace cv;
void image_white_black_tophat()
{
	Mat im = imread(imgAddr + "black_white.jpg");
	 // 白顶帽：原图像与开操作的差值图像，开操作去除小对象，白顶帽就是去除大对象
	// 黑顶帽：闭操作和原图像的差值，结果剩下原图像前景色的小洞
	Mat dst1, dst2;
	int shape = MORPH_RECT;
	int op1 = MORPH_BLACKHAT;
	int op2 = MORPH_TOPHAT;
	Mat kernel1 = getStructuringElement(shape, Size(10, 10));
	Mat kernel2 = getStructuringElement(shape, Size(10, 10));
	morphologyEx(im, dst1, op1, kernel1);
	morphologyEx(im, dst2, op2, kernel2);
	imshow("dst1",dst1);
	imshow("dst2", dst2);
	waitKey(0);
	destroyAllWindows();
}