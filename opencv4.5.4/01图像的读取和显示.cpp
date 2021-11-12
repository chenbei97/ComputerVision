#include "primary.h"
#include <iostream>
using namespace cv;
void imread_imshow()
{
    Mat src = imread("D:/VisualStudioItems/apple.jpg",IMREAD_GRAYSCALE);
    if (!src.empty())
    {
        std::cout << "src.depth()=" << src.depth() << std::endl;
        namedWindow("input", WINDOW_FREERATIO);//可调的自由比例
        imshow("input", src);
        waitKey(0);
        destroyAllWindows();
    }
    else
        printf("could not load image...");
}

