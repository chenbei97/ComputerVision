#include "primary.h"
using namespace cv;
void image_hist_correct()
{
	Mat src = imread(imgAddr + "me.jpg");

	int nimages = 1; // �ӽ������ȡ1��ȡ3ò��û����,�������ڲ�����ԭ��
	int channels[] = { 0,1,2}; // src��ͨ��0,1,2�����ݲ��Խ��0,1,2��ʾ���ͼ�ĵڼ�ͨ��
	int* pchannel = channels; // ָ��һά��ͨ�����ָ��
	Mat mask = Mat();
	std::vector<Mat> hist(src.channels());// �����Ӧ����3��ͼƬ��ֱ��ͼ 3��1ά�� , 3��256
	int dims = 1; //һά��,��ά���ܻ�õ�256*256
	int bins = 256; // �Ҷ�ͼ��ֱ��ͼһ����һά��,������256
	int histsizes[] = {bins,bins,bins}; // ÿ��ͼ��ֱ��ͼ�ߴ綼��1ά256����
	int* histSize = histsizes;
	float range_b[] = { 0,256 };
	float range_g[] = { 0,256 };
	float range_r[] = { 0,256 }; // ÿ��ͨ���������޶���0-256
	const float* range_bgr[] = { range_b ,range_g,range_r}; // һάָ������ ���ÿ��ͨ������������ĵ�ַ,������const��
	const float** ranges = range_bgr; // ָ��һάָ�����鱾���**ָ��,ranges++����ranges[1]���ʵĶ���Ԫ��range_g����
	std::cout << ranges[1] << "   " << range_g << "   " << &range_g[0] << "   " << std :: endl;
	bool uniform = true;
	bool accumulate = false;
	
	for (int i = 0; i < hist.size(); i++)
	{
		calcHist(&src, nimages, pchannel++, mask, hist[i], dims, histSize++, ranges, uniform, accumulate);
		// std::cout << hist[i].size() << std::endl; // [1��256]
		//std::cout << hist[i] << std::endl;
	}
	
	double maxval[3] = {0,0,0}; // ����һάֱ��ͼ�����ֵ 3��ͨ��
	double *pmaxval = maxval;
	for (size_t i = 0; i < 3; i++)
	{
		minMaxLoc(hist[i], NULL, pmaxval++, NULL, NULL,Mat());
		std::cout << "maxval = " << maxval[i] << std::endl;
	}
	int x_step = 2;
	int  dst_rows = 256; //  ���ͼ��ĸ߶�
	Mat dst1 = Mat::zeros(dst_rows, x_step * bins, CV_8UC3);
	Mat dst2 = dst1.clone();
	std::vector<Mat> dsts;
	std::vector<Scalar> colors = {Scalar(255,0,0),Scalar(0,255,0),Scalar(0,0,255)};
	for (int i = 0; i < 3; i++)
	{
		dsts.push_back(Mat::zeros(dst_rows, x_step * bins, CV_8UC3));// 256 * 512
		for (int bin = 0; bin < bins; bin++)
		{
			int x1 = bin * x_step; // ÿ��С���ε����Ͻ�ˮƽx����ȡ0,2,4,..
			int x2 = (bin + 1) * x_step - 1; // ÿ��С���ε����½�ˮƽx����1,3,5,7..
			// ÿ���Ҷȼ���y������Ҫ�ȹ�һ����0-1�ٷ�����ͼ��ĳ߶�,Ȼ��ȡ����1��֤��Խ�� ����255.7����ȡ256
			int y1 = cvRound(hist[i].at<float>(bin) / maxval[i] * dst_rows);
			int y2 = 255 - 0;// 0�Ļ������ǻ���x��y=0���µ�,�Ӿ���Ϊ�˸��ùۿ�������ѡ��y2>y1�� ���ƻ�׼����y=255��
			//std::cout << (i + 1) * (bin + 1) << std::endl;
			//std::cout << "x1 = " << x1 << "  x2 = " << x2 << "   y1 = " << y1 << "  y2 = " << y2<< std::endl;
			rectangle(dsts[i],Point(x1,y1),Point(x2,y2),colors[i]); // 3�����ڷֱ���ʾ3��ͨ����ֱ��ͼ
			rectangle(dst1, Point(x1, y1), Point(x2, y2), colors[i]); // 1������ͬʱ��ʾ
			imshow("dst"+std::to_string(i), dsts[i]);
		}
		for (int bin = 1; bin < bins; bin++)
		{
			int x1 = (bin - 1) * x_step; // 0,2,4,...
			int x2 = bin * x_step - 1;// 1,3,5..
			int y1 = 255 - cvRound(hist[i].at<float>(bin - 1) / maxval[i] * dst_rows);// Ϊ���Ӿ�Ч����y=0��׼����y=255
			int y2 = 255 - cvRound(hist[i].at<float>(bin) / maxval[i] * dst_rows); // Ϊ���Ӿ�Ч����y=0��׼����y=255
			line(dst2, Point(x1, y1), Point(x2, y2), colors[i], 2, 8, 0);
		}
	}
	imshow("rect", dst1);
	imshow("line1", dst2);
	
	Mat src_hsv;
	cvtColor(src,src_hsv,COLOR_BGR2HSV);
	Mat hsv_h, hsv_s, hsv_v;
	Mat hsvs[] = { hsv_h, hsv_s, hsv_v }; // ��ֱ����3����ɫͼƬ����ΪҪ��������ͳߴ籣��һ�±Ƚ��鷳
	split(src_hsv,hsvs);
	Mat* hsv = hsvs;
	nimages = 3;
	int channels_ []= { 0,1,2 }; // ����3��ͼƬʱҲҪ����˳��0,1,2��ֻ��1�ǵ�2��ͼƬ��0ͨ��,2�ǵ�3��ͼƬ��0ͨ��
	int* pchannel_ = channels_;
	int histsizes_[] = { bins,bins,bins }; // ÿ��ͼ��ֱ��ͼ�ߴ綼��1ά256����
	int* histSize_ = histsizes_;
	float range_h[] = { 0,180 };
	float range_s[] = { 0,256 };
	float range_v[] = { 0,256 }; 
	const float* range_hsv[] = { range_h,range_s,range_v }; // һάָ������
	const float** ranges_ = range_hsv;
	Mat hist_[] = {Mat(),Mat(), Mat()};
	Mat* phist_ = hist_;
	//std::vector<Mat> hist_(src.channels()); //  ʹ�����������鶼����,����ʹ�������ϱ�ʹ������
	
	for (int i = 0; i < 3; i++) // �����ʾ��ÿ��ͼƬѭ��,���Ϸ��ĺ���1��ͼ���ÿ��ͨ��ѭ��������ȫ��ͬ
	{
		calcHist(hsv, nimages, pchannel_++, mask, hist_[i], dims, histSize_++, ranges_, uniform, accumulate);
		std::cout << hist_[i].size() << "  " << hist_[i].channels() << std::endl; // [1 x 256]  1
		//std::cout << hist_[i] << std::endl;
	}
	double maxval_[3] = { 0,0,0 }; // ����һάֱ��ͼ�����ֵ 3��ͨ��
	double* pmaxval_ = maxval_;
	for (size_t i = 0; i < 3; i++)
	{
		minMaxLoc(hist_[i], NULL, pmaxval_++, NULL, NULL, Mat());
		std::cout << "maxval = " << maxval_[i] << std::endl;
	}
	Mat dst_ = Mat::zeros(dst_rows, x_step * bins, CV_8UC3);;
	for (size_t i = 0; i < 3; i++)
	{
		for (int bin = 1; bin < bins; bin++) // ע�ⲻҪԽ�� i =1��ʼ
		{
			int x1 = (bin-1) * x_step; // 0,2,4,...
			int x2 = bin  * x_step - 1;// 1,3,5..
			int y1 = 255 - cvRound(hist_[i].at<float>(bin -1) / maxval_[i] * dst_rows);// Ϊ���Ӿ�Ч����y=0��׼����y=255
			int y2 = 255 - cvRound(hist_[i].at<float>(bin) / maxval_[i] * dst_rows); // Ϊ���Ӿ�Ч����y=0��׼����y=255
			//std::cout << "x1 = " << x1 << "  x2 = " << x2 << "   y1 = " << y1 << "  y2 = " << y2<< std::endl;
			CV_Assert(x1 <= bins*x_step && x2 <= bins * x_step &&y1<=dst_rows && y2 <= dst_rows);
			line(dst_, Point(x1, y1), Point(x2, y2), colors[i], 2, 8, 0);
		}
	}
	imshow("line2",dst_);
	waitKey(0);
	destroyAllWindows();
}