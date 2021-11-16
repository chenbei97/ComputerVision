#include "primary.h"
using namespace cv;
Mat src_024 = imread(imgAddr + "apple.jpg"), dst_024;
Mat mapx;
Mat mapy;
void image_pixel_remapping_mapfunction(int index);
void image_pixel_remapping()
{
	// ��ԭͼ������ذ���һ������ӳ�䵽��ͼ��Ķ�Ӧλ����
	// ����ʵ�ַ�ת�����ε�
	// remap�����롢�����ӳ���1��ӳ���2����ֵ����(���Բ�ֵ��������ֵ)
	// �߽��ֵ������
	/*
		INTER_NEAREST - ����ڲ�ֵ
		INTER_LINEAR �C ˫���Բ�ֵ��Ĭ��ֵ��
		INTER_CUBIC �C ˫����������ֵ����4��4���������ڵ�˫���β�ֵ��
		INTER_LANCZOS4 -Lanczos��ֵ����8��8���������Lanczos��ֵ��
	*/
	// const Scalar boaderValue
	mapx.create(src_024.size(), CV_32FC1);// ��������CV_32FC1��CV_32FC2����
	mapy.create(src_024.size(), CV_32FC1);
	
	int interpolation = INTER_LINEAR;   // INTER_NEAREST
	int borderMode = BORDER_CONSTANT;  // �������Բ�ֵ,�߽��ֵ����
	Scalar boardValue(0,255,0);//��ֵ��ֵ
	int index = -1;
	//std::cout << "index = ";
	//std::cin >> index;
	//image_pixel_remapping_mapfunction(index);
	//remap(src_024, dst_024, mapx, mapy, interpolation, borderMode, boardValue);
	//imshow("src", src_024);
	//imshow("dst", dst_024);
	//waitKey(0);
	image_pixel_remapping_mapfunction(index); // ��ִ��һ��
	remap(src_024, dst_024, mapx, mapy, interpolation, borderMode, boardValue);
	while (true)
	{
		index = waitKey(500) ; 
		std::cout << index << std::endl; // esc=27
		if ((char)index == 27)
			break;
		index = index % 3; // ֻ�ܵ���0,1,2
		std::cout << index << std::endl;
		image_pixel_remapping_mapfunction(index);
		//std::cout << "update successful ..." << std::endl;
		remap(src_024, dst_024, mapx, mapy, interpolation, borderMode, boardValue);
		imshow("dst", dst_024);
	}	
	destroyAllWindows();
}
void image_pixel_remapping_mapfunction(int index)
{
	for (int row = 0; row < src_024.rows; row++)
	{
		for (int col = 0; col < src_024.cols; col++) // ӳ���ϵ
		{
			switch (index)
			{
			case 0 : // ���ҷ�ת
				mapx.at<float>(row, col) = src_024.cols  - col; // ��תx static_cast<float>
				mapy.at<float>(row, col) = row; // y����
				// c++������ʹ��c���Ե�ǿ������ת���⣬������������ǿ������ת��
				// static_cast��dynamic_cast��const_cast��reinterpret_cast
				// static_cast�൱�ڴ�ͳ��C�������ǿ��ת�������������expressionת��Ϊnew_type����
				//std::cout << "case 0 running..." << std::endl;
				break;
			case 1: // ���·�ת
				mapx.at<float>(row, col) = col;
				mapy.at<float>(row, col) = src_024.rows - row;
				break;
			case 2: // ����ת
				mapx.at<float>(row, col) = src_024.cols - col;
				mapy.at<float>(row, col) = src_024.rows - row;
				break;
			default: // ʲôҲ����
				mapx.at<float>(row, col) = col;
				mapy.at<float>(row, col) = row;
				break;
			}
		}
	}
}