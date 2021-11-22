#include "primary.h"
using namespace cv;
void image_template_match()
{
	/*
	��Դͼ���ҵ�ƥ��ģ��ͼ���������
	ƥ���㷨������ƽ�����롢��������ԡ��������ϵ��
	�����һ����ƽ�����롢��һ��������ԡ���һ�������ϵ��
	TM_CCOEFF,TM_CCOEFF_NORMED = 4��5
	TM_CCORR,TM_CCORR_NORMED = 2��3
	TM_SQDIFF,TM_SQDIFF_NORMED = 0��1
	void matchTemplate( InputArray image, InputArray templ,
                                 OutputArray result, int method, InputArray mask = noArray() )
	Դͼ�� ��W*H��ģ��ͼ��w*h��������ǵ�ͨ��32λ��W-w+1 * H-h+1 ��ͼ��
	*/
	Mat src = imread(imgAddr +"alphabet.jpg");  // ������8bit or 32bit��ͼ��
	Mat templ = imread(imgAddr + "A.jpg");
	cvtColor(src,src,COLOR_BGR2GRAY);
	cvtColor(templ, templ, COLOR_BGR2GRAY);
	Mat dst(src.cols - templ.cols + 1, src.rows - templ.rows + 1,CV_32FC1);
	int method = TM_CCORR_NORMED;
	matchTemplate(src,templ,dst,method,noArray()); // �õ���dst��ƥ�����
	normalize(dst, dst, 0, 255,NORM_MINMAX); // ��ʹ��һ����Ҳ�Ǹ�����
	dst.convertTo(dst,CV_8UC1); 
	Point maxLoc, minLoc; // ͼ�����ֵ����Сֵ��λ��
	double Min, Max;
	minMaxLoc(dst,&Min,&Max,&minLoc,&maxLoc,Mat());
	// �ҵ������е����ֵ����Сֵ���ظ�Min��Max������������
	Point RectLoc; // ���ƾ��ε�����
	if (method == TM_SQDIFF_NORMED && method == TM_SQDIFF)
	{
		// ƽ����ƥ��ʱ dst��Ԫ�غ����Ǿ��룬������С���Ǹ��ط���ƥ����õ�λ��
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