#include "primary.h"
using namespace cv;
void image_add_border()
{
	/*
	BORDER_CONSTANT �������
	BORDER_DEFAULT��Ĭ��
	BORDER_ISOLATED��
	BORDER_REPLICATE�����Ʒ����������Ե������
	BORDER_REFLECT101 ���ԳƷ��������Ե������Ϊ��
	BORDER_REFLECT���ԳƷ����������Ե������ҲҪ�Գƹ�ȥ
	BORDER_WRAP ������һ�����������һ�������߽�
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