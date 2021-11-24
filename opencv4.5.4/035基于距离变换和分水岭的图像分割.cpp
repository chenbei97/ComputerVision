#include "primary.h"
using namespace cv;
#include <vector>
void image_segmentation_of_distance_transformand_watershed()
{
	/*
		����任�����ڲ������͸�ʴ�õ������ڵ��Ǿ���õ�
		void distanceTransform( InputArray src, OutputArray dst,
									 int distanceType, int maskSize, int dstType=CV_32F);
		distanceType��ʹ��DIST_L1��DIST_L12��DIST_L2
		maskSize��֧��3��3��5��5��������С
		dstType�����8λ��32λ�ĸ���������ͨ��
		void distanceTransform( InputArray src, OutputArray dst,
                                     OutputArray labels, int distanceType, int maskSize,
                                     int labelType = DIST_LABEL_CCOMP );
		 labels����ɢάŵͼ���
		 labelType ��DIST_LABEL_PIXEL��DIST_LABEL_CCOMP

		��ˮ�룺���ڽ�������ʵ��
		void watershed( InputArray image, InputOutputArray markers );

		�ٰ�ɫ������Ϊ��ɫ
		��ʹ��filter2D��������˹����ʵ��ͼ��Աȶ����
		��תΪ��ֵͼ��
		�ܾ���任
		�ݶԾ���任�����һ����0-1֮��
		��ʹ����ֵ�ٴζ�ֵ���õ����
		�߸�ʴ�õ�ÿ��peak_erode
		��findContours �� drawContours
		��watershed
		���ÿ��������ɫ������
	
	*/
	Mat src = imread(imgAddr + "pepper.jpg");
	Mat src_white = src.clone();
	// �ٰ�ɫ������Ϊ��ɫ
	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			if (src.at<Vec3b>(row, col) == Vec3b(255, 255, 255))
			{
				src_white.at<Vec3b>(row, col)[0] = 0;
				src_white.at<Vec3b>(row, col)[1] = 0;
				src_white.at<Vec3b>(row, col)[2] = 0;
			}
		}
	}
	
	//��ʹ��filter2D��������˹����ʵ��ͼ��Աȶ����
	Mat sharp;
	Mat kernel = (Mat_<float>(3, 3) << 1, 1, 1,
															1, -8, 1,
															1, 1, 1);
	filter2D(src_white, sharp,  CV_32F, kernel, Point(-1, -1));//ֻ��Ҫ��ȣ�ʹ�� CV_32F
	std::cout << "sharp.channels() = "<<sharp.channels() << std::endl; // Ҳ��3ͨ��
	sharp.convertTo(sharp,CV_8UC3); //CV_8UҲ��
	src_white.convertTo(src_white,CV_8UC3);
	Mat inverse_sharp = sharp - src_white;
	inverse_sharp.convertTo(inverse_sharp, CV_8UC3);
	//imshow("src_white", src_white);
	 //imshow("sharp", sharp);
	//imshow("inverse_sharp", inverse_sharp);

	// ��תΪ��ֵͼ��
	Mat binary,gray;
	cvtColor(inverse_sharp, gray, COLOR_BGR2GRAY);
	//imshow("gray", gray);
	double thresh = 50;
	double maxval = 255;
	int type = THRESH_OTSU | THRESH_BINARY;
	threshold(gray, binary, thresh, maxval, type);
	//imshow("binary", binary);

	// �ܾ���任
	Mat distTransform;
	int distanceType = DIST_L1;
	int maskSize = 3;
	int dstType = CV_32F;
	int labelType = DIST_LABEL_CCOMP;
	distanceTransform(binary, distTransform,distanceType,maskSize,dstType);
	
	//�ݶԾ���任�����һ����0 - 1֮��
	double alpha = 0.0, beta = 1.0;
	int norm_type = NORM_MINMAX;
	normalize(distTransform, distTransform, alpha, beta, norm_type, -1, noArray());
	
	//��ʹ����ֵ�ٴζ�ֵ���õ����
	thresh = 0.2;
	maxval = 1.0;
	threshold(distTransform, distTransform, thresh, maxval, THRESH_BINARY);
	//imshow("distTransform", distTransform);
	
	//�߸�ʴ�õ�ÿ��peak_erode
	Mat kernel1 = Mat::ones(1, 1, CV_8UC1);
	Mat erode_dist;
	erode(distTransform, erode_dist, kernel1);
	erode_dist.convertTo(erode_dist,CV_8U);
	//imshow("erode_dist", erode_dist); // ֱ�ӿ��������
	Mat inverse_erode_dist;
	bitwise_not(erode_dist, inverse_erode_dist);
	//imshow("inverse_erode_dist", inverse_erode_dist);
	
	//��findContours �� drawContours
	std::vector<std::vector<Point>>contours;
	std::vector<Vec4i> hierarchy;
	int mode = RETR_TREE;
	int method = CHAIN_APPROX_SIMPLE;
	findContours(erode_dist, contours, hierarchy, mode, method, Point(0, 0));

	Mat markers = Mat::zeros(src.size(), CV_32SC1); // �������еõ���������,�����Ƕ����͵�
	for (size_t i = 0; i < contours.size(); i++)
	{
		//std::cout << "i = " << i <<"   ��"<<contours[i] << std::endl;
		Scalar color = Scalar::all(static_cast<int>(i)+1);
		/*Scalar color(0,255,0,0);*/
		//std::cout << "color = " << color << std::endl;
		drawContours(markers,contours,static_cast<int>(i),color,2,8,noArray());
		//std::cout << markers << std::endl;
	}
	
	//��watershed
	watershed(src, markers);  // (src.type() == CV_8UC3 && dst.type() == CV_32SC1)
	Mat mask;
	markers.convertTo(mask, CV_8UC1);
	bitwise_not(mask, mask);
	//imshow("mask",mask);
	
	//���ÿ��������ɫ������

	std::vector<Vec3b> colors;

	for (size_t i = 0; i < contours.size(); i++)
	{
		// ��ͬ�������Ƿָ��ߣ�ʹ�ò�ͬ����ɫ
		int b = theRNG().uniform(0, 255);
		int g = theRNG().uniform(0, 255);
		int r = theRNG().uniform(0, 255);
		colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
	}

	// ԭ����markers�ǵ�ͨ��,����3ͨ�������ɫ
	// ���ǲ���ԭͼ���,Ҳ����markers���,ֻ������marker�ṩ��λ����Ϣ
	Mat dst = Mat::zeros(markers.size(), CV_8UC3);  
	for (int row = 0; row < markers.rows; row++) 
	{
		for (int col = 0; col < markers.cols; col++)
		{
			int marker = markers.at<int>(row, col);
			//std::cout << "marker = " << marker << std::endl;
			if (marker > 0 && marker <= static_cast<int>(contours.size())) //��0Ԫ����ǿ��Ҫ��������������
			{
				dst.at<Vec3b>(row, col) = Vec3b(0, 0, 0);
			}
		}
	}
	imshow("dst",dst);
	waitKey(0);
	destroyAllWindows();
}