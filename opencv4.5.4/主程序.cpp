#include "primary.h"
#include "function.h"
#include <iostream>

using namespace std;
using namespace cv;
int main() 
{
    //imread_imshow();
    //image_type_conversion_imwirte();
   // image_assignment_copy_clone();
   //image_pixel_read_write_operation();
   // image_arithmetic_operation();
    //image_mask_operation();
    //image_functions_using("bitwise");
    image_functions_using("convertTo");
    return 0;
}
/*
#pragma once
#include <opencv2/xfeatures2d/nonfree.hpp>//ʹ��SURF��SIFTʱ��Ҫ�����nonfree.hpp�ļ�
#include <opencv2/core/core.hpp> // �ṹ����ѧ����
#include <opencv2/flann/miniflann.hpp> // ���ڽ�����ƥ�亯��
#include <opencv2/imgproc/imgproc.hpp> // ͼ������
#include <opencv2/video/video.hpp> // �Ӿ�׷���Լ������ָ�
#include <opencv2/features2d/features2d.hpp> // ����׷�ٵĶ�ά����
#include <opencv2/objdetect/objdetect.hpp> // ����������������latentSVM��������HoGan������ƽ��Ƭ�����
#include <opencv2/calib3d/calib3d.hpp> // У׼��˫Ŀ�Ӿ����
#include <opencv2/ml/ml.hpp> // ����ѧϰ�������ģʽʶ��
#include <opencv2/photo/photo.hpp> // �����ͻָ���Ƭ����㷨
#include <iostream>
#include <iostream>
#include <string>
    Mat src = imread("D:/VisualStudioItems/apple.jpg");
    cv::Ptr<cv::xfeatures2d::SURF>
    surf = cv::xfeatures2d::SURF::create();
    std::vector<cv::KeyPoint> kp;
    surf->detect(src, kp);
    Mat res;
    cv::drawKeypoints(src, kp, res);
    cv::Ptr<cv::SIFT>
    sift = cv::SIFT::create();
    imshow("input", src);
    imshow("result", res);
    waitKey(0);
    return 0;
*/
// ���ԣ���������չģ���г��õ�xfeature2Dģ��Ϊ�������ð������е�SIFTʵ���������


