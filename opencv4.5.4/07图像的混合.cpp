#include "primary.h"
using namespace cv;
void image_blend()
{
	// g(x) = αf(x) +(1-α)h(x)
	Mat im1 = imread(imgAddr+"cascade.jpg");
	Mat im2 = imread(imgAddr + "eagle.jpg");
	Mat temp;
	Mat dst;
	if (im1.rows > im2.rows or im1.cols > im2.cols)
	{
		resize(im1, temp, im2.size());
		// out = saturate(α * im1 + β * im2  + gamma)
		addWeighted(temp, 0.3, im2, 0.7, 0, dst); // 图片大小必须一致
	}
	else
	{
		resize(im2, temp, im1.size());
		addWeighted(im1, 0.3, temp, 0.7, 0, dst); // 图片大小必须一致
	}

	//namedWindow("cascade", WINDOW_AUTOSIZE);
	//namedWindow("eagle", WINDOW_AUTOSIZE);
	//imshow("cascade", im1);
	//imshow("eagle", im2);
	

	imshow("blend",dst);
	waitKey(0);
	destroyAllWindows();


}