#include "primary.h"
using namespace cv;
void image_morphology_extract_line()
{
	// ��ɫ->��ɫ->��ֵ��->����ṹԪ��->��������
	Mat src = imread(imgAddr+"line.jpg"); 
	Mat gray;
	Mat binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	int max_value = 255;// ��ֵͼ�����ֵ
	int adaptiveMethod = ADAPTIVE_THRESH_GAUSSIAN_C; // ����Ӧ����
	int thresholdType = THRESH_BINARY;// ��ֵ����
	int blocksize = 3;// ����������ظ���,���ڼ�����ֵ CV_Assert( blockSize % 2 == 1 && blockSize > 1 );
	double C = 0; // Ȩ��,����������0������
	adaptiveThreshold(gray , binary,max_value,adaptiveMethod,thresholdType,blocksize,C);
	Mat hlinekernel = getStructuringElement(MORPH_RECT,Size(src.cols/16,1));//���ˮƽ�ߵĺ�
	Mat vlinekernel = getStructuringElement(MORPH_RECT, Size(1, src.rows / 16));//��ⴹֱ�ߵĺ�
	Mat temp ,dst;
	erode(binary,temp,hlinekernel); // ���ƵĿ��Լ�ⴹֱ��
	dilate(temp,dst,hlinekernel);
	morphologyEx(binary, dst, MORPH_OPEN, vlinekernel); // ������ȼ�
	bitwise_not(dst,dst); // ��Ƭ�������
	blur(dst,dst,Size(11,11));

	Mat output; // ���ֻ��Ҫ����,ʹ�ó������Ԫ�ؼ���,����Ч������
	Mat kernel = getStructuringElement(MORPH_RECT, Size(2, 2));
	morphologyEx(binary, output,MORPH_OPEN, kernel);
	bitwise_not(output, output);
	imshow("binary,", binary);
	imshow("dst,", dst);
	imshow("output", output);
	waitKey(0);
	destroyAllWindows();
}