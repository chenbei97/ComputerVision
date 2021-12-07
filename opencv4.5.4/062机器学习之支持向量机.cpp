#include "primary.h"
#include <opencv2/ml/ml.hpp>
using namespace cv;
void machine_learing_svm()
{
	int width = 400, height = 300 ;
	Mat image = Mat::zeros(height, width, CV_8UC3);
	//����ѵ������
	int train_y[5] = { 1,-1,-1,-1 ,1};
	float train_x[5][2] = { {200,100},{120,26},{178,59},{255,60},{105,255} };
	Mat train_x_mat(5, 2, CV_32FC1, train_x); // ���mat��ʽ
	Mat train_y_mat(5, 1, CV_32SC1, train_y);

	// ѵ��SVM
	Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();
	// setType/getType���û�ȡSVM��ʽ����
	// ����C_SVC,NU_SVC,ONE_CLASS,EPS_SVR,NU_SVR
	svm->setType(cv::ml::SVM::C_SVC); 
	svm->setKernel(cv::ml::SVM::LINEAR); // ���Է�����
	svm->setDegree(1.0);//����degree����
	svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100 , 1e-6));// ���õ�������,������������ֹ���
	svm->train(train_x_mat, cv::ml::SampleTypes::ROW_SAMPLE, train_y_mat);

	// ��ʾSVM�����ľ�������
	Vec3b green(0, 255, 0), blue(255, 0, 0);
	for(int row =0 ;row<image.rows;row++)
		for (int col = 0; col < image.cols; col++)
		{
			Mat sampleMat = (Mat_<float>(1, 2) << col, row); // ������(x,y)=(col,row)
			float response = svm->predict(sampleMat); // �൱����ÿ���㶼Ԥ��һ��
			if (response == 1)
				image.at<Vec3b>(row, col) = green; // ��ɫΪ��ǩ1�Ľ��
			else if (response == -1)
				image.at<Vec3b>(row, col) = blue; // ��ɫΪ��ǩ2�Ľ��
		}
	
	// ��ʾѵ�����ݵ����ڵ�(��Բ)
	int thickness = 2;
	int lineType = 8;
	int radius = 5;
	circle(image, Point(train_x[0][0], train_x[0][1]), radius, Scalar(0,0,255),thickness, lineType);
	circle(image, Point(train_x[1][0], train_x[1][1]), radius, Scalar(255, 255, 255), thickness, lineType);
	circle(image, Point(train_x[2][0], train_x[2][1]), radius, Scalar(255, 255, 255), thickness, lineType);
	circle(image, Point(train_x[3][0], train_x[3][1]), radius, Scalar(255, 255, 255), thickness, lineType);
	circle(image, Point(train_x[4][0], train_x[4][1]), radius, Scalar(0, 0, 255), thickness, lineType);

	// ��ȡ���е�֧������
	Mat sv = svm->getSupportVectors();
	std::cout << sv.size() << "    " << sv.channels() << std::endl;// [2 x 1]    1
	for (int row = 0; row < sv.rows; ++row)
	{
		const float* v = sv.ptr<float>(row);
		circle(image, Point((int)v[0], (int)v[1]), radius, CV_RGB(0, 0, 0), thickness, lineType);
	}
	imshow("result", image);
	waitKey(0);
	destroyAllWindows();
}