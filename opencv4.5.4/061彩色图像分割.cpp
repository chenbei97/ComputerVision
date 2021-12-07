#include "primary.h"
using namespace cv;
Mat ics_src , ics_bgr, ics_hsv, ics_dst,ics_mask;;
// ɫ��
int ics_hmin = 0, ics_hmin_Max = 360, ics_hmax = 180, ics_hmax_Max = 180;
// ���Ͷ�
int ics_smin = 0, ics_smin_Max = 255, ics_smax = 255, ics_smax_Max = 255;
// ����
int ics_vmin = 106, ics_vmin_Max = 255, ics_vmax = 255, ics_vmax_Max = 255;
const char* ics_dstname = "dst";
const char* ics_maskname = "mask";
void image_color_segmentation_callback(int, void*);
void image_color_segmentation()
{
	ics_src = imread(imgAddr + "lena.jpg");
	ics_bgr = ics_src.clone();
	cvtColor(ics_bgr, ics_hsv, COLOR_BGR2HSV);
	namedWindow(ics_dstname, WINDOW_FREERATIO);
	namedWindow(ics_maskname, WINDOW_FREERATIO);
	// ����ɫ�� H
	createTrackbar("hmin",ics_dstname,&ics_hmin,ics_hmin_Max, image_color_segmentation_callback);
	createTrackbar("hmax", ics_dstname, &ics_hmax, ics_hmax_Max, image_color_segmentation_callback);
	// ���ڱ��Ͷ� S
	createTrackbar("smin", ics_dstname, &ics_smin, ics_smin_Max, image_color_segmentation_callback);
	createTrackbar("smax", ics_dstname, &ics_smax, ics_smax_Max, image_color_segmentation_callback);
	// �������� V
	createTrackbar("vmin", ics_dstname, &ics_vmin, ics_vmin_Max, image_color_segmentation_callback);
	createTrackbar("vmax", ics_dstname, &ics_vmax, ics_vmax_Max, image_color_segmentation_callback);
	image_color_segmentation_callback(0, 0);
	waitKey(0);
	destroyAllWindows();
	return;
}
void image_color_segmentation_callback(int, void*)
{
	ics_dst = Mat::zeros(ics_src.size(), ics_src.type());
	
	// 0-180 , 0-255 ,0-255 ֮��ı�������Ϊ0
	inRange(ics_hsv, Scalar(ics_hmin, ics_smin, ics_vmin), Scalar(ics_hmax, ics_smax, ics_vmax), ics_mask);//3��ͨ���ڷ�Χ֮�ڵı�������Ϊ0,����mask
	for (int row = 0; row < ics_src.rows; row++)
		for (int col = 0; col < ics_src.cols; col++)
			if (ics_mask.at<uchar>(row, col) == 255) // λ������Ϊ255�ı���������Ϊ0
				ics_dst.at<Vec3b>(row, col) = ics_bgr.at<Vec3b>(row, col);
	imshow(ics_dstname, ics_dst);
	imshow(ics_maskname, ics_mask);
}