#include "primary.h"
#include <opencv2/ml/ml.hpp>
using namespace cv;
void machine_learing_bayesian_classifier()
{
	// ��Ҷ˹�������Ǹ��ַ������з�����������С���߸���������ƽ��������С�ķ�����
	// ���õķ�������Naive Bayes��TAN��BAN��GBN
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
			Mat sampleMat = (Mat_<float>(1, 2) << col, row); // ������(x,y)=(col,row)
			float response = model->predict(sampleMat); // �൱����ÿ���㶼Ԥ��һ��
			if (response == 1)
				image.at<Vec3b>(row, col) = green; // ��ɫΪ��ǩ1�Ľ��
			else if (response == -1)
				image.at<Vec3b>(row, col) = blue; // ��ɫΪ��ǩ2�Ľ��
		}
	// ��ʾѵ�����ݵ����ڵ�(��Բ)
	int thickness = 2;
	int lineType = 8;
	int radius = 5;
	Scalar c1 = Scalar::all(0); // ��ǩ1��Ϊ�ڵ�
	Scalar c2 = Scalar::all(255); // ��ǩ-1��Ϊ�׵�
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