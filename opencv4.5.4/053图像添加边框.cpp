#include "primary.h"
using namespace cv;
void image_add_border()
{
	/*
	BORDER_CONSTANT 常数填充
	BORDER_DEFAULT：默认
	BORDER_ISOLATED：
	BORDER_REPLICATE：复制法，复制最边缘的像素
	BORDER_REFLECT101 ：对称法，以最边缘的像素为轴
	BORDER_REFLECT：对称法，但是最边缘的像素也要对称过去
	BORDER_WRAP ：用另一侧像素填充这一侧的扩充边界
	*/
	Mat src, dst;
	int borderType = BORDER_DEFAULT;
	RNG rng;
	src = imread(imgAddr + "12.jpg");
	int top = (int)(0.05 * src.rows);
	int bottom = top;
	int left = (int)(0.05 * src.cols);
	int right = left;
	const char* name = "baby";
	
	for (;;)
	{
		Scalar color(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		char c = (char)waitKey(500);
		if (c == 27) break;
		else if (c == (int)'i') borderType = BORDER_ISOLATED;
		else if (c == (int)'r') borderType = BORDER_REFLECT;
		else if (c == (int)'r') borderType = BORDER_REFLECT;
		else if (c == (int)'c') borderType = BORDER_CONSTANT;
		else if (c == (int)'v')borderType = BORDER_REFLECT101;
		else if (c == (int)'b')borderType = BORDER_REPLICATE;
		else if (c == (int)'t') borderType = BORDER_TRANSPARENT;
		else if (c == (int)'w')borderType = BORDER_WRAP;
		copyMakeBorder(src, dst, top, bottom, left, right, borderType, color);
		namedWindow(name, WINDOW_FREERATIO);
		imshow(name, dst);
	}
	//Scalar color(255,255,0);
	//copyMakeBorder(src, dst, top, bottom, left, right, borderType, color);
	//imshow(name, dst);
	//waitKey(0);
	//destroyAllWindows();
	
}