#include "primary.h"
using namespace cv;
void image_white_black_tophat()
{
	Mat im = imread(imgAddr + "black_white.jpg");
	 // �׶�ñ��ԭͼ���뿪�����Ĳ�ֵͼ�񣬿�����ȥ��С���󣬰׶�ñ����ȥ�������
	// �ڶ�ñ���ղ�����ԭͼ��Ĳ�ֵ�����ʣ��ԭͼ��ǰ��ɫ��С��
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