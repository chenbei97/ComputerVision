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
    //image_functions_using("convertTo");
    //image_blend();
    //image_brightnessand_contrast_adjustment();
    //image_draw_shape_text();
    //image_functions_using("rng_uniform");
    //image_functions_using("createTrackBar");
    //image_functions_using("normalize");
    //image_blur();
    //image_corrosion_expansion();
    //image_open_close();
    //image_white_black_tophat();
    //image_morphology_extract_line();
    image_up_down_sampling();
    image_threshold_calculate();
    image_linear_filtering();
    image_edge_processing();
    image_gradient_sobel();
    image_gradient_laplance();
    image_gradient_canny();
    image_hough_transform_line();
    image_hough_transform_circle();
    image_pixel_remapping();
    image_histogram_equalization();
    image_histogram_calculation_C1();
    image_histogram_calculation_C3();
    image_histogram_calculation_STL3();
    image_histogram_comparison();
    image_histogram_reverse_projection();
    return 0;
}
/*
#pragma once
#include <opencv2/xfeatures2d/nonfree.hpp>//使用SURF、SIFT时需要导入该nonfree.hpp文件
#include <opencv2/core/core.hpp> // 结构和数学运算
#include <opencv2/flann/miniflann.hpp> // 最邻近搜索匹配函数
#include <opencv2/imgproc/imgproc.hpp> // 图像处理函数
#include <opencv2/video/video.hpp> // 视觉追踪以及背景分割
#include <opencv2/features2d/features2d.hpp> // 用于追踪的二维特征
#include <opencv2/objdetect/objdetect.hpp> // 级联人脸分类器、latentSVM分类器、HoGan特征和平面片检测器
#include <opencv2/calib3d/calib3d.hpp> // 校准和双目视觉相关
#include <opencv2/ml/ml.hpp> // 机器学习、聚类和模式识别
#include <opencv2/photo/photo.hpp> // 操作和恢复照片相关算法
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
// 测试，这里以扩展模块中常用的xfeature2D模块为例，调用包含其中的SIFT实现特征检测


