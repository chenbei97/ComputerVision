#include "primary.h"
using namespace cv;
void image_brightnessand_contrast_adjustment()
// 本质上还是读写操作
{
	Mat src = imread(imgAddr + "eagle.jpg");//IMREAD_GRAYSCALE
	Mat dst(src.size(),src.type());
	float alpha = 0.1;
	float beta = 0.0;
	Mat T;
	src.convertTo(T,CV_32FC3);
	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			if (src.channels() == 1)
			{
				float old_value = src.at<uchar>(row, col);
				float new_value = old_value * alpha + beta;
				src.at<uchar>(row, col) = saturate_cast<uchar>(new_value);
			}
			else
			{
				//float b = T.at<Vec3f>(row, col)[0];// 数值使用Vec3f的话需要先将src转变CV_32FC3
				//float g = T.at<Vec3f>(row, col)[1];
				//float r = T.at<Vec3f>(row, col)[2];
				//dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b * alpha + beta);
				//dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g * alpha + beta);
				//dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r * alpha + beta);
				float b = src.at<Vec3b>(row, col)[0]; // 或者直接使用Vec3b
				float g = src.at<Vec3b>(row, col)[1];
				float r = src.at<Vec3b>(row, col)[2];
				src.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b * alpha + beta);
				src.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g * alpha + beta);
				src.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r * alpha + beta);
			}
		}
	}
	//imshow("dst",dst);
	imshow("src", src);
	waitKey(0);
	destroyAllWindows();

}