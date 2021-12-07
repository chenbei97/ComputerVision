#include "primary.h"
#include <opencv2/ml/ml.hpp>
using namespace cv;
void machine_learing_bayesian_classifier()
{
	// 贝叶斯分类器是各种分类器中分类错误概率最小或者给定代价下平均风险最小的分类器
	// 常用的分类器有Naive Bayes、TAN、BAN、GBN
	int width = 512, height = 512;
	Mat image = Mat::zeros(height, width, CV_8UC3);
	int labels[10] = { 1,-1,1,1,-1,1,-1,1,-1,-1 };
	float data[10][2] = { {501,150},{255,10},{501,255},{10,501},{25,80},
									{150,300},{77,200},{300,300},{45,250},{200,200} };
	Mat train_x(10, 2, CV_32FC1, data);
	Mat train_y(10, 1, CV_32SC1, labels);
	Ptr<cv::ml::NormalBayesClassifier> model = cv::ml::NormalBayesClassifier::create();
	Ptr<cv::ml::TrainData> Tdata = cv::ml::TrainData::create(train_x, cv::ml::SampleTypes::ROW_SAMPLE, train_y);
	model->train(Tdata);
	Vec3b green(0, 255, 0), blue(255, 0, 0);
	for (int row = 0; row < image.rows; row++)
		for (int col = 0; col < image.cols; col++)
		{
			Mat sampleMat = (Mat_<float>(1, 2) << col, row); // 坐标是(x,y)=(col,row)
			float response = model->predict(sampleMat); // 相当于是每个点都预测一遍
			if (response == 1)
				image.at<Vec3b>(row, col) = green; // 绿色为标签1的结果
			else if (response == -1)
				image.at<Vec3b>(row, col) = blue; // 蓝色为标签2的结果
		}
	// 显示训练数据的所在点(画圆)
	int thickness = 2;
	int lineType = 8;
	int radius = 5;
	Scalar c1 = Scalar::all(0); // 标签1的为黑点
	Scalar c2 = Scalar::all(255); // 标签-1的为白点
	for (int row = 0; row < train_y.rows; row++)
	{
		const float* v = train_x.ptr<float>(row);
		Point pt = Point((int)v[0], (int)v[1]);
		if (labels[row] == 1)
			circle(image, pt, radius, c1, thickness, lineType);
		else
			circle(image, pt, radius, c2, thickness, lineType);
	}
	imshow("result", image);
	waitKey(0);
	destroyAllWindows();
}