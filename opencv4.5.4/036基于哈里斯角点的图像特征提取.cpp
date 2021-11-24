#include "primary.h"
using namespace cv;
#include <vector>
Mat harris_src, harris_gray, harris_dst;
int harris_thresh = 245; // �����Ķ��� ��ǰֵ
int harris_count = 255; // ���ֵ
const char* harris_winname = "harris";
const char* harris_barname = "thresh";
void image_feature_extraction__HarrisCorner_callback(int ,void*);
void image_feature_extraction__HarrisCorner()
{
	/*
	ͼ��������ȡ����������SIFT��HOG��SURF��HAAR��LBP��KAZE��AKAZE��BRISK
	Ŀ��DDM��Ŀ����(Detection)��Ŀ������(Description)��Ŀ��ƥ��(Matching)

	void cornerHarris( InputArray src, OutputArray dst, int blockSize,
								int ksize, double k,
								int borderType = BORDER_DEFAULT );
	src��dst������ΪCV_32FC1
	blockSize��blockSize�����С
	ksize��Sobel���㴰�ڴ�С
	k������Ƕ���Ӧ��������С������˹��������ɲ���,0.04~0.06
	borderType�������߽�����
	*/
	namedWindow(harris_winname,WINDOW_FREERATIO); // !!!���������
	harris_src = imread(imgAddr + "tajmahal.jpg");
	cvtColor(harris_src, harris_gray, COLOR_BGR2GRAY);// ����˹ֻ���Ҷ�ͼ
	createTrackbar(harris_barname, harris_winname,&harris_thresh, harris_count, image_feature_extraction__HarrisCorner_callback);
	image_feature_extraction__HarrisCorner_callback(0,0);
	waitKey(0);
	destroyAllWindows();
	return ;
}
void image_feature_extraction__HarrisCorner_callback(int, void*)
{
	harris_dst = Mat::zeros(harris_gray.size(), CV_32FC1);
	int blocksize = 2;
	int ksize = 3;
	double k = 0.04;
	int borderType = BORDER_DEFAULT;
	cornerHarris(harris_gray,harris_dst,blocksize,ksize,k,borderType); // ������
	normalize(harris_dst, harris_dst, 0, 255, NORM_MINMAX,CV_32FC1,Mat());
	//imshow("harris_gray", harris_gray);
	Mat dst;
	convertScaleAbs(harris_dst,dst);// �������ֵ��ת����8bit
	//imshow("dst", dst);
	Mat src = harris_src.clone();
	for (int row = 0; row < src.rows; row++)
	{
		uchar* current_row = src.ptr(row);
		for (int col = 0; col < src.cols; col++)
		{
			int value = (int)*current_row;
			//std::cout << "value = " << value << std::endl;
			if (value > harris_thresh)
			{
				int radius = 1;
				circle(src, Point(row, col), radius, Scalar(0, 0, 255), 1, 8, 0);
			}
			current_row++;
		}
	}
	imshow(harris_winname, src);
}