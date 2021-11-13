#include "primary.h"
using namespace cv;
void image_draw_line(Mat& img);
void image_draw_rectangle(Mat& img);
void image_draw_ellipse(Mat& img);
void image_draw_circle(Mat& img);
void image_draw_fillpoly(Mat& img);
void image_draw_shape_text()
{
	// line ellipse circle rectangle fillpoly
	Mat im = imread(imgAddr + "eagle.jpg");
	//image_draw_line(im);
	//image_draw_rectangle(im);
	//image_draw_ellipse(im);
	//image_draw_circle(im);
	//image_draw_fillpoly(im);
	Point org(im.cols / 2, im.rows / 2);
	int fontFace = FONT_HERSHEY_COMPLEX;
	int thickness = 5;
	int lineType = LINE_8;
	double fontScale = FONT_HERSHEY_SCRIPT_COMPLEX;
	Scalar color(0,0,255);
	putText(im,"opencv",org,fontFace,fontScale,color,thickness,lineType);
	namedWindow("im", WINDOW_FREERATIO);
	imshow("im", im);
	waitKey(0);
	destroyAllWindows();
}
void image_draw_line(Mat & img)
{
	Point p1(0, 0);
	Point p2;
	p2.x = img.cols;
	p2.y = img.rows;
	Scalar color(255, 0, 0);
	line(img,p1,p2,color,2,LINE_8);
	namedWindow("im",WINDOW_FREERATIO);
	imshow("im", img);
	waitKey(0);
	destroyAllWindows();
}
void image_draw_rectangle(Mat& img)
{
	// 绘制矩形需要使用矩形数据类型
	Rect rect1(100,100,100,100); // 使用 x,y,w,h构造
	Rect rect2(Point(400, 400), Point(100,100));// 使用p1,p2构造,后面的才是坐标
	Rect rect3(Point(800, 800), Size(100, 100));// 使用p,size构造
	Scalar color1(0,0,255);
	Scalar color2(0, 255, 255);// 黄
	Scalar color3(0, 255, 0);
	rectangle(img,rect1,color1,2,LINE_8);
	rectangle(img, rect2, color2, 2, LINE_8);
	rectangle(img, rect3, color3, 2, LINE_8);
	namedWindow("im", WINDOW_FREERATIO);
	imshow("im", img);
	waitKey(0);
	destroyAllWindows();
}
void image_draw_ellipse(Mat& img)
{
	/*RotatedRect ro(,Point90);*/
	Point center(img.cols / 2, img.rows / 2);
	Size size(300, 500);
	float angle = 90;
	RotatedRect ro1(center,size,angle);

	RotatedRect ro2(Point(0,100),Point(0,0),Point(100,0));//给出三个点从左下、左上、右上顺序
	Scalar color1(0, 0, 255);
	Scalar color2(0, 255, 0);
	ellipse(img,ro1,color1,2);
	ellipse(img, ro2, color2, 2);

	// 使用第2种构造也可以
	ellipse(img,center,size,45,0,180,color1,10,8);// 0-360表示完整的弧
	namedWindow("im", WINDOW_FREERATIO);
	imshow("im", img);
	waitKey(0);
	destroyAllWindows();
}
void image_draw_circle(Mat& img)
{
	Scalar color1(255, 0, 255);
	int radius = 200;
	circle(img, Point(img.cols / 2, img.rows / 2), radius, color1, 2, 8);
	namedWindow("im", WINDOW_FREERATIO);
	imshow("im", img);
	waitKey(0);
	destroyAllWindows();
}
void image_draw_fillpoly(Mat& img)
{
	Scalar color1(255, 0, 255);
	Point pts[1][6]; // 直接构造5个点的数组,每个点是point类型
	pts[0][0] = Point(100,100); // 绘制多边形区域的每个点坐标
	pts[0][1] = Point(100, 200);
	pts[0][2] = Point(200, 100);
	pts[0][3] = Point(200, 200);
	pts[0][4] = Point(100, 100);
	std::cout << pts[0] << "	"<<*pts[0]<<std::endl; // 数组首地址和[100, 100]
	
	const Point* ppts[1] = {pts[0]};// 从下边输出结果来看 ppts 是一个指针数组,只有一个元素,这个元素是指向Point的指针
	std::cout << ppts <<"	"<<*ppts<<"	"<<ppts[0]<< std::endl;// ppts也是地址,但是与pts[0]差了50
	// 解引用后仍然是地址,其实就是第1个元素
	int  num[] = { 5}; //点的数量,也是指针类型(数组)
	int ncontours = 1;//指示绘制的多段线是否闭合,默认闭合=1
	fillPoly(img,ppts,num, ncontours,color1,8);// ppts是Point的二级指针
	namedWindow("im", WINDOW_FREERATIO);
	imshow("im", img);
	waitKey(0);
	destroyAllWindows();
}