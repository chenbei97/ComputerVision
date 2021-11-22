#include "primary.h"
using namespace cv;
void image_template_match()
{
	/*
	在源图像找到匹配模板图像的子区域
	匹配算法：计算平方距离、计算相关性、计算相关系数
	计算归一化的平方距离、归一化的相关性、归一化的相关系数
	TM_CCOEFF,TM_CCOEFF_NORMED = 4、5
	TM_CCORR,TM_CCORR_NORMED = 2、3
	TM_SQDIFF,TM_SQDIFF_NORMED = 0、1
	void matchTemplate( InputArray image, InputArray templ,
                                 OutputArray result, int method, InputArray mask = noArray() )
	源图像 是W*H，模板图像w*h，则输出是单通道32位的W-w+1 * H-h+1 的图像
	*/
	Mat src = imread(imgAddr +"alphabet.jpg");  // 必须是8bit or 32bit的图像
	Mat templ = imread(imgAddr + "A.jpg");
	cvtColor(src,src,COLOR_BGR2GRAY);
	cvtColor(templ, templ, COLOR_BGR2GRAY);
	Mat dst(src.cols - templ.cols + 1, src.rows - templ.rows + 1,CV_32FC1);
	int method = TM_CCORR_NORMED;
	matchTemplate(src,templ,dst,method,noArray()); // 得到的dst是匹配矩阵
	normalize(dst, dst, 0, 255,NORM_MINMAX); // 即使归一化了也是浮点数
	dst.convertTo(dst,CV_8UC1); 
	Point maxLoc, minLoc; // 图像最大值和最小值的位置
	double Min, Max;
	minMaxLoc(dst,&Min,&Max,&minLoc,&maxLoc,Mat());
	// 找到数组中的最大值和最小值返回给Min和Max，并给出坐标
	Point RectLoc; // 绘制矩形的坐标
	if (method == TM_SQDIFF_NORMED && method == TM_SQDIFF)
	{
		// 平方法匹配时 dst的元素含义是距离，所以最小的那个地方是匹配最好的位置
		RectLoc = minLoc;
	}
	else
		RectLoc = maxLoc;
	Point RectWH = Point(templ.rows,templ.cols);
	rectangle(src,RectLoc, RectWH ,Scalar(0,0,255),2);
	//std::cout << dst << std::endl;
	imshow("src",src);
	waitKey(0);
	destroyAllWindows();
}