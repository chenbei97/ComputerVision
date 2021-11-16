#include "primary.h"
#include <vector>
using namespace cv;
void image_hough_transform_line()
{
	// ǰ��������Ե����Ѿ���� 
	// ԭ��ƽ��ռ�ת��Ϊ������ռ�
	// ֱ���ϵĵ�任��������ռ���Եõ�һ������R
	// ͬһֱ�ߵĵ�(R,theta)Ⱥ����һ����ǿ���ź�(����ǿ��),���ݴ˷��㵽ƽ������Ӷ��õ�ֱ��
	// HoughLines ������任�����ػ���ռ�(theta,R)
	// HoughLinesP��ֱ�߸��ʣ�������ֱ�ߵ�����
	Mat src = imread(imgAddr + "line.jpg"), dst;
	Mat gray;
	unsigned short int thresh = 100;
	Canny(src,gray, thresh,  2 * thresh );
	std::vector<Vec4f> lines1; // ���ص���2����,Ҳ����4��ֵ
	std::vector<Scalar> lines2;
	double rho = 1; // ���ɼ�����ʱ���ص�ɨ�貽��
	double theta= CV_PI / 180.0; // ���ɼ�����ʱ�ĽǶȲ�����һ��ȡCV_PI/180
	double srn = 0.0 ,stn =0.0; // �Ƿ�Ӧ�ö�߶ȵĻ���任,��������0��ʾ�������任
	double  min_theta=0, max_theta=CV_PI; // Ĭ�ϽǶ�ɨ�跶ΧΪ0-180��
	int threshold = 10; // ������Ŀ��ֵ,ֻ�л���㹻����ļ�������ܿ���ֱ��
	double minLineLength = 0; // ��С�߳�
	double maxLineGap = 0; // �����߼��
	HoughLinesP(gray,lines1,rho,theta,threshold,minLineLength,maxLineGap);// ���������8λ�Ҷ�ͼ��
	HoughLinesP(gray, lines2, rho, theta, threshold, minLineLength, maxLineGap);
	std::vector<Vec4f> ::const_iterator  it; // ���Է�ֹ�޸�ԭ��ֵ
	RNG rng;
	for (it = lines1.begin(); it != lines1.end(); it++)
	{
	   Vec4f T1;
	   T1 = *it;
		std::cout << T1<< "		" << T1[0] <<"	" << T1[1] << std::endl;
		line(src,Point(T1[0],T1[1]),Point(T1[2],T1[3]),Scalar(rng.uniform(0,255),rng.uniform(0,255),255),2); // ���ص���Щ�ߵ�����ȷʵ��ȷ
	}
	Mat src_T;
	bitwise_not(src, src_T);
	std::cout << "T2��" << std::endl;
	Mat src_ = src.clone();
	for (std::vector<Scalar>::const_iterator it1 = lines2.begin(); it1 != lines2.end(); it1++)
	{
		Scalar T2;
		T2 = *it1;
		std::cout << T2[0] << std :: endl; // �ӽ������ ʹ��Scalar����Ҳ�ǿ��Ե�
		line(src_, Point(T2[0], T2[1]), Point(T2[2], T2[3]), Scalar(rng.uniform(0, 255), rng.uniform(0, 255), 255), 2);
	}
	Mat src_TT;
	bitwise_not(src_, src_TT);
	//imshow("src_T", src_T);
	//imshow("src_TT", src_TT); // ��ȫ֤��ʹ��Vec4f��Scalar�����һ����


	Mat input = imread(imgAddr + "line1.jpg");
	Mat canny;
	Canny(input,canny,50,100);
	threshold = 1;
	srn = 0;
	std::vector<Vec2f> lines; 
	HoughLines(canny, lines, theta, threshold, srn, stn, min_theta, max_theta);
	std::cout << "T3��" << lines.size() << std::endl;
	for (size_t i = 0; i < lines.size(); i++) // ��һ�ֱ�����ʽ
	{
		//size_t�Ǳ�׼C���ж���ģ���64λϵͳ��Ϊlong long unsigned int
		Vec2f T3 = lines[i]; // ���ص���theta , r  ����û���ֽ��
		 // r = cos(theta)*x + sin(theta)*y
		std::cout << T3 <<"   "<< T3[0] <<"   " << T3[1] << std::endl;
		/*line()*/
	}
	imshow("canny", canny);
	waitKey(0);
	destroyAllWindows();
}