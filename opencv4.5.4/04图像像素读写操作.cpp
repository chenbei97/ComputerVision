#include "primary.h"
using namespace cv;

void image_pixel_read_write_operation()
{
	Mat src = imread("D:/VisualStudioItems/apple.jpg",IMREAD_COLOR);//IMREAD_GRAYSCALE
	int width = src.cols;
	int height = src.rows;
	int dims = src.dims;
	int channels = src.channels();
	int i = 0;
	std::cout << "channels = " << channels << "  dims = " << dims << std :: endl; // channel=3 , dim=2��channels = 1  dims = 2��
	bool isPtr = true;
	bool isAt = false;
	if (isPtr == false && isAt == true) 
	{
		double time0 = static_cast<double>(getTickCount());
		// <1> ʹ��at����(��������)
		for (int row = 0; row < height; row++)
			for (int col = 0; col < width; col++)
			{// ��������
				if (channels == 1)
				{ // �Ҷ�ͼ��
					int uint_value = src.at<uchar>(row, col); // ���ͼƬ��0-255���͵�
					src.at<uchar>(row, col) = 255 - uint_value;
					/*float float_value = src.at<float>(row, col);*/
					if (i < 50)
					{
						std::cout << "uint = " << uint_value << std::endl;
						i++;
					}
					else
						break;
				}
				else if (channels == 3)
				{ // ��ɫͼ��
					Vec3b vector_value = src.at<Vec3b>(row, col); // һ���Զ�ȡ��3��ͨ����λ���ϵ���ֵ���������
					src.at<Vec3b>(row, col)[0] = 255 - vector_value[0]; // ��������ÿ��ͨ��
					src.at<Vec3b>(row, col)(1) = 255 - vector_value(1);
					src.at<Vec3b>(row, col)[2] = 255 - vector_value[2];
					//	if (i < 10) {
					//		std::cout << "(3,3,0),(3,3,1),(3,3,2) = " << vector_value << std::endl;
					//		i++;
					//	}
					//	else
					//		break;
					//}
				}
			}
		time0 = ((double)getTickCount() - time0) / getTickFrequency();
		std::cout << "\tʹ��at������ʱ��Ϊ�� " << time0 << "��" << std::endl;  //�������ʱ��=0.0330268��
		// �����ض�����Ԫ��
		if (channels == 1)
		{
			Point p0(100, 100);
			std::cout << "(100,100) = " << src.at<uchar>(p0) << std::endl; // ��ͨ��ʱ��ȡ����3
			std::cout << "(100,100) = " << src.at<uchar>(100, 100) << std::endl;// ��ͨ��ʱ��ȡ����3
		}
		else
		{
			Point p1(100, 100);
			std::cout << "(100,100,0) = " << (int)src.at<Vec3b>(p1)[0] << "  (100,100,1) = " << (int)src.at<Vec3b>(p1)(1) << std::endl; // ��ͨ��ʱ��ȡ����[3, 72, 27]
		}
		
		imshow("inverse_src", src);
		waitKey(0);
	}
	else if (isPtr == true && isAt == false)
	{
		double time0 = static_cast<double>(getTickCount());
		//<2> ʹ��ptr����(����ָ��)
		for (int row = 0; row < height; row++) 
		{
			uchar* current_raw = src.ptr<uchar>(row); // ptrֻ�ܷ�����,ÿ����ѭ������ָ��
			for (int col = 0; col < width; col++)
			{
				if (channels == 1) {
					int value = *current_raw; // ������ָ�����Ԫ��
					*current_raw = 255 - value;
					current_raw++; // ��ָ��++ ������Ԫ��
				}
				else
				{
					//*(current_raw++) = 255 - *current_raw; // ʹ������,������Ϊ��ָ����ָ��3��ͨ����������ƽ�̵�������
					//*(current_raw++) = 255 - *current_raw;
					//*(current_raw++) = 255 - *current_raw;
					*(current_raw++) = 255 - *current_raw;
				}
			}
		}
		time0 = ((double)getTickCount() - time0) / getTickFrequency();
		//getTickCount( )��������CPU��ĳ���¼������߹���ʱ��������
		// getTickFrequency()��������CPUһ�������ߵ�ʱ��������
		std::cout << "\tʹ��ptr������ʱ��Ϊ�� " << time0 << "��" << std::endl;  //�������ʱ��=0.001702��
		imshow("inverse_src", src);
		waitKey(0);
	}	
	else // ����������
	{
		double time0 = static_cast<double>(getTickCount());
		Mat_<Vec3b>::iterator it = src.begin<Vec3b>();  //��ʼλ�õĵ�����
		Mat_<Vec3b>::iterator itend = src.end<Vec3b>();  //��ֹλ�õĵ�����
		for (; it != itend; ++it)
		{
			(*it)[0] = 255 - (*it)[0];
			(*it)[1] = 255 - (*it)[1];
			(*it)[2] = 255 - (*it)[2];
		}
		time0 = ((double)getTickCount() - time0) / getTickFrequency();
		std::cout << "\tʹ��iterator������ʱ��Ϊ�� " << time0 << "��" << std::endl;  //�������ʱ��=0.02��
		imshow("inverse_src", src);
		waitKey(0);
	}
}