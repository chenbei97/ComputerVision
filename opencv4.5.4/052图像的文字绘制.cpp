#include "primary.h"
using namespace cv;
void image_draw_text()
{
	const std::string text = "Hello C++ , Hello OpenCV !";
	int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX; // 手写字体风格
	fontFace = FONT_HERSHEY_COMPLEX; 
	double fontScale = 3.0;
	int thickness = 3;
	Mat img(400, 1500, CV_8UC3, Scalar::all(0));
	int baseline = 0;
	// 获取字符串的高度和宽度，baseline表示文字最底部的y坐标，加上厚度就是视觉上最底部的坐标
	Size textsize = getTextSize(text, fontFace, fontScale, thickness, &baseline);//获取待绘制文字应具备的文本框大小
	baseline += thickness;
	// 这个位置是文字的左下角起点
	Point center((img.cols - textsize.width) / 2, (img.rows - textsize.height) / 2);
	line(img, Point(0, 0), center, Scalar::all(255), 4);
	// 左上角(0,3)，右下角(center+宽度,高度不变)
	Point left_top(center.x,center.y - textsize.height);
	Point right_bottom(center.x+textsize.width , center.y);
	line(img, left_top, right_bottom, Scalar(255, 0, 0), 4);
	rectangle(img, left_top, right_bottom,Scalar(0,0,255),4);
	Mat dst = img(Rect(left_top+Point(-20,-20),right_bottom+Point(20,20)));
	putText(img,text,center,fontFace,fontScale,Scalar::all(255),thickness,8);
	imshow("text",dst);
	waitKey(0);
	destroyAllWindows();
}