#include "primary.h"
#include <iostream>
using namespace cv;
void imread_imshow()
{
    // 对于InputArray和OutputArray支持的类型为
    // Mat , Mat_<T>,Mat_<T,m,n>,vector<T>,vector<vector<T>>,vector<Mat>
    Mat src = imread("D:/VisualStudioItems/apple.jpg",IMREAD_GRAYSCALE);
    if (!src.empty())
    {
        std::cout << "src.depth()=" << src.depth() << std::endl;
        namedWindow("input", WINDOW_FREERATIO);//¿Éµ÷µÄ×ÔÓÉ±ÈÀý
        imshow("input", src);
        waitKey(0);
        destroyAllWindows();
    }
    else
        printf("could not load image...");
    Scalar a = Scalar::all(1); // [1,1,1,1]
    std::cout << a << std::endl;
    // 直接赋值法
    Mat m = (Mat_<double>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    std::cout << m << std :: endl; 
    // 数组构造法
    int b[3][2] = { 0,1,2,3,4,5 };
    Mat m1(2, 3, CV_32S, b);
    // create法
    Mat m2;
    m2.create(4,4,CV_8UC1);
    std::cout << m2 << std::endl;
}

