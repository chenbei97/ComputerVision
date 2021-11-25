#include "primary.h"
using namespace cv;
#include <vector>
void image_feature_detection_hog()
{
	/*
	灰度图像转换->梯度计算->分网格的梯度方向直方图->块描述子
	->特征数据与检测窗口->匹配方法
	正向训练200个样本，反向训练600-800个样本
	例如64×128的像素块，可以分为8×16个cell，分为7×15个块(R-HOG)
	总计的直方图向量数为7×15×2×2×9=3780个向量数组
	HOGDescriptor() : winSize(64,128), blockSize(16,16), blockStride(8,8),
        cellSize(8,8), nbins(9), derivAperture(1), winSigma(-1),
        histogramNormType(HOGDescriptor::L2Hys), L2HysThreshold(0.2), gammaCorrection(true),
        free_coef(-1.f), nlevels(HOGDescriptor::DEFAULT_NLEVELS), signedGradient(false)
    {}
	*/
	Mat src = imread(imgAddr + "peoples.jpg"), temp,gray; // ronaldo.png
	resize(src,temp,Size(64,128));
	cvtColor(temp, gray, COLOR_BGR2GRAY);
	Size winSize(64, 128);
	Size blockSize(16, 16);
	Size blockStride(8, 8);
	Size cellSize(8, 8);
	int nbins = 9;
	HOGDescriptor detector(winSize,blockSize,blockStride,cellSize,nbins);
	std::vector<float> descriptors;
	std::vector<Point>locations;
	Size winStride(0,0);
	Size padding(0, 0);
	detector.compute(gray,descriptors,winStride,padding,locations);
	printf_s("描述子的数量为：%d", descriptors.size());
	// virtual void setSVMDetector(InputArray svmdetector)
	
	
	detector.setSVMDetector(detector.getDefaultPeopleDetector()); // 判断是否是人
	std::vector<Rect> peoples;
	double scale = 1.05;
	double histThreshold = 0.0;
	double finalThreshold = 2.0;
	winStride = Size(8, 8);
	padding = Size(32, 32);
	detector.detectMultiScale(src,peoples,histThreshold, winStride,padding,scale,finalThreshold);
	for (size_t i = 0; i < peoples.size(); i++)
	{
		rectangle(src,peoples[i],Scalar(0,0,255),2,8,0);
	}
	imshow("src",src);
	waitKey(0);
	destroyAllWindows();
}