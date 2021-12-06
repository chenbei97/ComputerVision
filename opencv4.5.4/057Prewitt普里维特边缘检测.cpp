#include "primary.h"
using namespace cv;
void get_prewitt_kernel(Mat & kernel ,int type,bool printkernel );
void image_prewitt_edge_detection()
{
	Mat src = imread(imgAddr + "lena.jpg");
	std::vector<Mat>kernels(4);
	std::vector<Mat>dsts(4);
	int ddepth = CV_32F; // 8λ�޷��Żᵼ������ĸ�����Ϊ0
	for (int i = 0; i < 4; i++)
	{
		get_prewitt_kernel(kernels[i], i, true);
		filter2D(src,dsts[i],ddepth,kernels[i],Point(-1,-1),0,BORDER_DEFAULT);
		convertScaleAbs(dsts[i], dsts[i]);
		imshow("dst"+std::to_string(i),dsts[i]);
	}
	// ��Եǿ��
	Mat dst(src.rows, src.cols, CV_8UC3);
	dst = dsts[0] + dsts[1]; // �����Ǳ�Եǿ��
	imshow("dst",dst);
	waitKey(0);
	destroyAllWindows();

}
void get_prewitt_kernel(Mat& kernel, int type, bool printkernel = false)
{
	switch (type)
	{
	case 0: 
		kernel = (Mat_<float>(3, 3) << -1, -1, -1, 0, 0, 0, 1, 1, 1); // ˮƽ
		flip(kernel, kernel, -1); // ��ʱ�뷭ת180��õ������
		if (printkernel)
			std::cout <<"horizontal = "<< kernel << std::endl;
		break;
	case 1:
		kernel = (Mat_<float>(3, 3) << -1,0,1,-1,0,1,-1,0,1); // ��ֱ
		flip(kernel, kernel, -1); // ��ʱ�뷭ת180��õ������
		if (printkernel)
			std::cout <<"vertical = "<< kernel << std::endl;
		break;
	case 2:
		kernel = (Mat_<float>(3, 3) << 0,1,1,-1,0,1,-1,-1,0);// ���Խ�
		flip(kernel, kernel, -1); // ��ʱ�뷭ת180��õ������
		if (printkernel)
			std::cout <<"diag = "<< kernel << std::endl;
		break;
	case 3:
		kernel = (Mat_<float>(3, 3) <<-1,-1,0,-1,0,1,0,1,1 ); // ���Խ�
		flip(kernel, kernel, -1); // ��ʱ�뷭ת180��õ������
		if (printkernel)
			std::cout <<"inverse diag = "<< kernel << std::endl;
		break;
	default:
		kernel = NULL;
		break;
	}
	/*
	[-1,-1,-1]      [-1,0,1]       [ 0,1,1]        [-1,-1,0]
	[ 0, 0, 0]       [-1,0,1]       [-1,0,1]        [-1, 0,1]
	[ 1, 1, 1]       [-1,0,1]       [-1,0,1]        [0, 1 ,1]
	*/
}