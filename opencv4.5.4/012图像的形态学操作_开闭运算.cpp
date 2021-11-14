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
	//  �����㣺ȥ��С���󣬱���ɫ��ɫ��ǰ��ɫ��С�������ȥ��
	// �ȼ����ȸ�ʴ�����ͣ���ɫС����ʴ����ʹ��С�����ܱߵ���������Ҳ���Ǻ�ɫ
	// ���Ƶ� �����㣺�����ͺ�ʴ�������С�������Խ���ɫ������ڲ���ɫС������Ϊ��ɫ���ٸ�ʴ��Ϊ��ɫ
	morphologyEx(im,dst1,op1,kernel1);
	morphologyEx(im, dst2, op2, kernel2);

	// ��̬ѧ�ݶ� �� ���ͼ�ȥ��ʴ���ֳ�Ϊ�����ݶȣ��������з����ݶȡ��ڲ��ݶ�
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