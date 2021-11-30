#include "primary.h"
using namespace cv;
void image_draw_text()
{
	const std::string text = "Hello C++ , Hello OpenCV !";
	int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX; // ��д������
	fontFace = FONT_HERSHEY_COMPLEX; 
	double fontScale = 3.0;
	int thickness = 3;
	Mat img(400, 1500, CV_8UC3, Scalar::all(0));
	int baseline = 0;
	// ��ȡ�ַ����ĸ߶ȺͿ�ȣ�baseline��ʾ������ײ���y���꣬���Ϻ�Ⱦ����Ӿ�����ײ�������
	Size textsize = getTextSize(text, fontFace, fontScale, thickness, &baseline);//��ȡ����������Ӧ�߱����ı����С
	baseline += thickness;
	// ���λ�������ֵ����½����
	Point center((img.cols - textsize.width) / 2, (img.rows - textsize.height) / 2);
	line(img, Point(0, 0), center, Scalar::all(255), 4);
	// ���Ͻ�(0,3)�����½�(center+���,�߶Ȳ���)
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