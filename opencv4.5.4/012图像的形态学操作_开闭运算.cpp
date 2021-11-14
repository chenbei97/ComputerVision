#include "primary.h"
using namespace cv;
void image_open_close()
{
	Mat im = imread(imgAddr + "black_white.jpg");
	Mat dst1,dst2;
	int shape = MORPH_RECT;
	int op1 = MORPH_OPEN;
	int op2 = MORPH_CLOSE ;
	Mat kernel1 = getStructuringElement(shape,Size(10,10));
	Mat kernel2 = getStructuringElement(shape, Size(10, 10));
	//  开运算：去除小对象，背景色黑色，前景色的小对象可以去除
	// 等价于先腐蚀后膨胀，白色小对象腐蚀掉，使用小对象周边的像素膨胀也就是黑色
	// 类似的 闭运算：先膨胀后腐蚀，可填充小洞，可以将白色对象的内部黑色小洞膨胀为暗色，再腐蚀掉为黑色
	morphologyEx(im,dst1,op1,kernel1);
	morphologyEx(im, dst2, op2, kernel2);

	// 形态学梯度 ： 膨胀减去腐蚀，又称为基本梯度，其他还有方向梯度、内部梯度
	int op = MORPH_GRADIENT;
	
	Mat dst;
	Mat src = imread(imgAddr + "eagle.jpg");
	Mat kernel = getStructuringElement(shape, Size(10, 10));
	morphologyEx(src, dst, op, kernel);
	//imshow("im", im);
	//imshow("dst1",dst1);
	//imshow("dst2", dst2);
	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
	destroyAllWindows();

}