#include "primary.h"
using namespace cv;
void image_type_conversion_imwirte()
{
    Mat src = imread("D:/VisualStudioItems/apple.jpg", IMREAD_COLOR);
    Mat gray,hsv;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    cvtColor(src, hsv, COLOR_BGR2HSV);
    namedWindow("gray", WINDOW_FREERATIO);
    namedWindow("hsv", WINDOW_FREERATIO);
    imshow("gray", gray);
    imshow("hsv", hsv);
    waitKey(0);
    //imwrite("D:/VisualStudioItems/apple_gray.jpg", gray);
}