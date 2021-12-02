#include "primary.h"
using namespace cv;
void gray_points_deal(const Mat& src,Mat& dst, int type);
void gray_line_transform(const Mat& src, Mat& dst, float a , int b);
void gray_subsection_line_transform(const Mat& src, Mat& dst, float x1, float x2, float y1, float y2);
void gray_logarithm_transform(const Mat& src, Mat& dst, int type, float k , double elispon);
void gray_inverse_logarithm_transform(const Mat& src, Mat& dst, double r , int level);
void gray_normalize(const std::vector<double>& srcdata, Mat& dst , int level);
void gray_pow_transform(const Mat& src, Mat& dst, double r, float k);
void image_gray_transformation()
{
	/*
		<1>�㴦��ĻҶȱ任��
		���鹫ʽ��D = 0.299R + 0.587G + 0.114B
		���ֵ�� max(B,G,R)
		ƽ��ֵ�� ava(B,G,R)
		<2>�Ҷ����Ա任�������Աȶ�
		 y = k x + b  xΪ�任ǰ�Ҷ�ֵ,y�任��Ҷ�ֵ
		 <3>�Ҷȷֶ����Ա任�������Աȶ�
		        k1 x + c1  0��x��threshold1
		 y =  k2 x + c2   threshold1��x��threshold2
				k3 x + c3  threshold2��x��255
				x = threshold1  y = y_thresh1
				x = threshold2  y = y_thresh2
		<4>�����任����ǿ����ϸ�ڣ���Ϊ���������ڽӽ�0�ķ�Χб�ʽϴ�
			ͬʱͼ��ĸ���ҶƵ�׽Ͽ�0-10^6�����Զ����任����ѹ���߶�
			y = k * log(1 + x + ��)
		<5>�������任��y = ((r+1)^x - 1) / r �õ��Ĵ󲿷�����Ϊ��ɫ,ֻ��ͻ���������ص�
		<6>���ɱ任��y = c * x^r
	*/
	Mat src = imread(imgAddr+"lena.jpg");
	std::vector<Mat> dsts;
	// <1>�㴦��ĻҶȱ任
	try 
	{
		for (int i = 0; i < 4; i++)
		{
			dsts.push_back(Mat(src.rows, src.cols, CV_8UC1)); // ����Ҫָ�����ͷ��򱨴�
			gray_points_deal(src, dsts[i], i);
			imshow(std::to_string(i), dsts[i]);
		}
	}
	catch (const char* e) { std::cout << e << std::endl; }
	// <2>�Ҷ����Ա任�������Աȶ�
	float k = -1;
	int b = 255; //��Ƭ
	// k = 1.2; b = 50;
	Mat dst1(src.rows,src.cols,src.type());
	gray_line_transform(src,dst1,k,b);
	imshow("dst1",dst1);
	// <3>�Ҷȷֶ����Ա任�������Աȶ�
	Mat dst2(src.rows, src.cols, src.type());
	gray_subsection_line_transform(src, dst2, 72, 100,5,240);
	imshow("dst2", dst2);
	Mat dst3(src.rows, src.cols, src.type());
	int type = 2;
	gray_logarithm_transform(src, dst3, type,1,1e-8);
	imshow("dst3", dst3);
	std::cout << "pow(2, 3) = "<<pow(2, 3) << std::endl;
	Mat dst4(src.rows, src.cols, src.type());
	double r = 3; // �ݱ任
	int level = 255;
	gray_inverse_logarithm_transform(src,dst4,r,level);
	imshow("dst4", dst4);
	r = 0.5;
	k = 1;
	Mat dst5(src.rows, src.cols, src.type());
	gray_pow_transform(src, dst5, r, k);
	imshow("dst5", dst5);
	waitKey(0);
	destroyAllWindows();
}
void gray_pow_transform(const Mat& src, Mat& dst, double r, float k)
{
	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			Vec3b src_value = src.at<Vec3b>(row, col);
			dst.at<Vec3b>(row, col)[0] = k * pow(src_value[0],r);
			dst.at<Vec3b>(row, col)[1] = k * pow(src_value[1], r);
			dst.at<Vec3b>(row, col)[2] = k * pow(src_value[2], r);
		}
	}
	normalize(dst, dst, 0, 255, NORM_MINMAX);
}
void gray_normalize(const std :: vector<double>& srcdata, Mat& dst, int level)
{
	// level ��ʾ�Ҷȼ�,����һ����0-1���������ٻҶȼ�
	// (x - xmin) / ( xmax - xmin) , ��Ҫ���ҵ����ֵ����Сֵ
	// ���������Ҫ��������,Ҳ����ͼ���ÿ��Ԫ�ر����push_back������
	double maxval = 0, minval = 0;
	for (size_t i = 0; i < srcdata.size(); i++)
	{
		if (srcdata[i] > maxval)
			maxval = srcdata[i];
		if (srcdata[i] < minval)
			minval = srcdata[i];
	}
	double delta = maxval - minval;
	std::cout << "maxval - minval = " <<delta<< std::endl;
	int idx = 0;
	double value;
	for (int row = 0; row < dst.rows; row++)
	{
		uchar* p = dst.ptr<uchar>(row);
		for (int col = 0; col < dst.cols * dst.channels(); col++)
		{
			// �����൱���ٰ�����������˳��ֵ��ȥ,��dst��ѭ���ﻹ��Ҫ�õ�������ÿ��Ԫ�� ����Ҫ�������idx
			value = (srcdata[idx++] - minval) * 1.0 / delta;
			//std::cout << value << std::endl;
			p[col] = (uchar)(level * value);// level �ǻҶȼ������
		}
	}
	//std::cout << dst << std::endl;
}
void gray_inverse_logarithm_transform(const Mat& src, Mat& dst, double r ,int level)
{
	std::vector<double> srcdata;
	double value;
	for (int row = 0; row < src.rows ; row++)
	{
		const uchar* p = src.ptr<uchar>(row);// ��ָ��
		for (int col = 0; col < src.cols * src.channels(); col++)
		{
			// y = ((r+1)^x - 1) / r
			value = (pow(r + 1, p[row]) - 1)/ r;
			srcdata.push_back(value);
		}
	}
	CV_Assert (srcdata.size() == src.cols * src.cols * src.channels()) ;
	gray_normalize(srcdata, dst, level);
}
void gray_logarithm_transform(const Mat& src, Mat& dst, int type, float k = 1.0 , double elispon = 1e-8)
{
	// ����Ԫ��+1��y = log ( 1+ x + ��)
	if (type == 0)
	{
		// const ע�� src���ܸı� 
		add(src, Scalar(1.0 + elispon), dst); // �ȼ���1+r��ת�����ݸ�ʽ���򱨴�
		dst.convertTo(dst, CV_32FC3); // תΪ��������ִ��log����,����log�ᱨ��
		log(dst, dst); // Assertion failed (depth == CV_32F || depth == CV_64F) ,CV_32FC3Ҳ����
		// ��ʱ��������Խ�� ��Ҫ��һ��0-255
		dst.convertTo(dst, CV_8UC3); // ������ת����������ֱ�ӹ�һ��������
		normalize(dst, dst, 0,255, NORM_MINMAX);
		//std::cout << dst << std::endl;
		convertScaleAbs(dst,dst,1.0); // ����������ȡ����ֵ
	}
	else if (type == 1)
	{
		double temp = 0;
		for (int row = 0; row < src.rows; row++)
			for (int col = 0; col < src.cols; col++)
			{
				for (int c = 0; c < src.channels(); c++)
				{	
					temp = k * log((double)((double)src.at<Vec3b>(row, col)[c] + 1.0) + elispon);
					//std::cout << temp << std::endl;
					dst.at<Vec3b>(row, col)[c] = saturate_cast<uchar>(temp);
				}
			}
		dst.convertTo(dst, CV_8UC3); // ���Բ���
		normalize(dst, dst, 0, 255, NORM_MINMAX);
		convertScaleAbs(dst, dst, 1.0);
	}
	else
	{
		src.convertTo(dst, CV_32F);
		dst = dst + 1;
		log(dst, dst);
		dst = k * dst;
		dst.convertTo(dst, CV_8UC3); // �����
		normalize(dst, dst, 0, 255, NORM_MINMAX);
		//std::cout << dst << std::endl;
		convertScaleAbs(dst, dst);
	}
}
void gray_subsection_line_transform(const Mat& src, Mat& dst , float x1 , float x2, float y1, float y2)
{
	/*
				 k1 x + c1  0��x��threshold1
		 y =  k2 x + c2   threshold1��x��threshold2
				k3 x + c3  threshold2��x��255
				x = threshold1  y = y_thresh1
				x = threshold2  y = y_thresh2
		k1*x1+c1=y1 => k1 = (y1 - c1)/ x1 = y1 /x1 (c1 = 0)
		k2 = ( y2 - y1 ) / (x2 -x1)
		c2 = y1 - k2 * x1 
	*/
	float k1 = (y1 - 0) / (x1-0);
	float k2 = (y2 - y1) / (x2 - x1);
	float k3 = (255 - y2) / (255 - x2);
	float c1 = y1 - k1 * x1;
	float c2 = y2 - k2 * x2;
	float c3 = 255 - k3 * 255;
	std::vector<unsigned char> loolUpTable(256); // ��ѯ��
	for (size_t x = 0; x < 256; x++)
	{
		if (x < x1)
			loolUpTable[x] = static_cast<unsigned char>(x * k1);
		else if( x > x2)
			loolUpTable[x] = static_cast<unsigned char>(x * k3 + c3);
		else
			loolUpTable[x] = static_cast<unsigned char>(x * k2 + c2);
	}
	for (int row = 0; row < src.rows; row++)
	{
		unsigned char* p_src = src.data + row * src.step[0]; // src.data�Ǹ�һά����,p���Ը��ݲ����õ�ÿ����Ԫ�ش��ڵĵ�ַλ��
		unsigned char* p_dst = dst.data + row * src.step[0];
		for (int col = 0; col < src.cols * src.channels(); col++)
		{
			p_dst[col] = loolUpTable[p_src[col]];
		}
	}
		
}
void gray_line_transform(const Mat& src, Mat& dst , float k, int b)
{
	/*
		k > 1 �Աȶȱ��
		k < 1�Աȶȱ�С
		k = 1 ,b��0,ͼ�����лҶ�ֵƽ��һ����Χ,��ô����ͼ��������߸���
		k =1 , b = 0 , ���������ͬ
		k = -1 ,b =255 , ���ͼ��Ҷȷ�ת
		k<0 ,b >0,���������,������䰵,�������Ч��ͼ��������
	*/
	for (int row = 0; row < src.rows; row++)
		for (int col = 0; col < src.cols; col++)
		{
			for (int channel = 0; channel < src.channels(); channel++)
			{
				dst.at<Vec3b>(row, col)[channel] = saturate_cast<uchar>(k * src.at<Vec3b>(row, col)[channel] + b);
			}
		}
}
void gray_points_deal(const Mat& src, Mat& dst ,int type = 0)
{
	if (type == 0)
	{
		for (int row = 0; row < src.rows; row++)
			for (int col = 0; col < src.cols; col++)
			{
				dst.at<uchar>(row, col) = saturate_cast<uchar>(
					0.114 * src.at<Vec3b>(row, col)[0] +
					0.587 * src.at<Vec3b>(row, col)[1] +
					0.299 * src.at<Vec3b>(row, col)[2]);
			}
	}
	else if (type == 1)
	{
		for (int row = 0; row < src.rows; row++)
			for (int col = 0; col < src.cols; col++)
			{
				dst.at<uchar>(row, col) = saturate_cast<uchar>(
					max( max(src.at<Vec3b>(row, col)[0], src.at<Vec3b>(row, col)[1]),
						src.at<Vec3b>(row, col)[2] )
					);
			}
	}
	else if (type == 2)
	{
		for (int row = 0; row < src.rows; row++)
			for (int col = 0; col < src.cols; col++)
			{
				dst.at<uchar>(row, col) = saturate_cast<uchar>(
							(src.at<Vec3b>(row, col)[0]+
							src.at<Vec3b>(row, col)[1]+
							src.at<Vec3b>(row, col)[2] )/3 );
			}
	}
	else
		throw "type only = 0,1,2";
}