#include "primary.h"
using namespace cv;
void image_morphology_extract_line()
{
	// 彩色->灰色->二值化->定义结构元素->开闭运算
	Mat src = imread(imgAddr+"line.jpg"); 
	Mat gray;
	Mat binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	int max_value = 255;// 二值图像最大值
	int adaptiveMethod = ADAPTIVE_THRESH_GAUSSIAN_C; // 自适应方法
	int thresholdType = THRESH_BINARY;// 阈值类型
	int blocksize = 3;// 块包含的像素个数,用于计算阈值 CV_Assert( blockSize % 2 == 1 && blockSize > 1 );
	double C = 0; // 权重,可以正数、0、负数
	adaptiveThreshold(gray , binary,max_value,adaptiveMethod,thresholdType,blocksize,C);
	Mat hlinekernel = getStructuringElement(MORPH_RECT,Size(src.cols/16,1));//检测水平线的核
	Mat vlinekernel = getStructuringElement(MORPH_RECT, Size(1, src.rows / 16));//检测垂直线的核
	Mat temp ,dst;
	erode(binary,temp,hlinekernel); // 类似的可以检测垂直线
	dilate(temp,dst,hlinekernel);
	morphologyEx(binary, dst, MORPH_OPEN, vlinekernel); // 开运算等价
	bitwise_not(dst,dst); // 负片看得清楚
	blur(dst,dst,Size(11,11));

	Mat output; // 如果只想要文字,使用常规矩形元素即可,这里效果不好
	Mat kernel = getStructuringElement(MORPH_RECT, Size(2, 2));
	morphologyEx(binary, output,MORPH_OPEN, kernel);
	bitwise_not(output, output);
	imshow("binary,", binary);
	imshow("dst,", dst);
	imshow("output", output);
	waitKey(0);
	destroyAllWindows();
}