#include "primary.h"
#include <vector>
using namespace cv;
//for (int row = 0; row < gray.rows; row++)
//{
//	uchar *current_row = gray.ptr<uchar>(row);
//	for (int col = 0; col < gray.cols; col++)
//	{
//		std::cout << "(" << col << ","<<row<<") = " << (int)*current_row << std::endl;
//	}
//}
void image_histogram_calculation_C1()
{
	Mat src = imread(imgAddr + "apple.jpg"), dst;
	std ::vector<Mat> images; 
	split(src, images); // �����һ��Mat������ָ��,��������ʵ��
	std::vector<std::string> strs = {"blue","green","red"};

	// 3ͨ��ͼ��չʾ
	for (int i = 0; i < images.size(); i++)
	{
		std::cout << "images[i].size() = " << images[i].size() << std::endl;
		imshow(strs[i], images[i]);
	}
	waitKey(0);
	destroyAllWindows();
	
	/*
		calcHist( const Mat* images, int nimages,
			const int* channels, InputArray mask,
			OutputArray hist, int dims, const int* histSize,
			const float** ranges, bool uniform = true, bool accumulate = false
		images �� ����ͼ���ָ��,�����ǵ���3ͨ����ͼƬ,Ҳ�����Ƕ��ͼ����ɵ�����
		nimages������ͼ��ĸ���
		channels����Ҫͳ��ֱ��ͼ�ĵڼ�ͨ����������C�������Ҳ������STL Vector
		ͨ���ǰ���˳����ŵģ�images[0]��ǰ3��ͨ�����Ϊ0,1,2��images[1]Ϊ3,4,5���Դ�����
		channels��Ԫ�ظ�������ֱ��ͼ��ά�ȣ�����Ӧ��ĳ�����������ĳ��ͨ��
		
		mask �� ��Ĥ��������Ĥ�����ص�ֱ��ͼ һ��Mat()
		mask������һ��8bit�����Һ�images�����������С��ͬ

		hist �����ֱ��ͼ��Ҫ������������
		dims ����Ҫͳ��ֱ��ͼͨ���ĸ���������channels�е�Ԫ�ظ���

		histSize��ָ����ֱ��ͼ�ֳɶ��ٸ����䣬���� bin�ĸ���
		������C�������Ҳ������STL������Ԫ�صĸ���ҲӦ�õ���dims

		ranges������ָ��ÿ��ͨ��ά�ȵ�ֱ��ͼ�ķ�Χ������ranges����ĳ��ȵ���dims
		�ٿ���ʹ��C���Ҳ����ʹ��STL�������C���ÿ��Ԫ��ranges[i]Ӧ������һ������
		���²����Ծ���3��ͨ����1��ͼƬ���н��ͣ���ô int channels[] = {0,1,2} , dims=3 ,nimages=1
		int histsize[] = {256,256,256} ÿ��ͨ�����ֳ�256��bins��Ҳ����ʹ�� std :: vector<int> histsize={256,256,256}
		��ranges[i]�Ľ���ȡ����uniform�Ƿ��һ������
		��uniform = true  ����[0,100)����ҿ�
		C���Ӧ��ָ��ÿ��ͨ��
		˵����i��ͨ����100����ֵ���ڵ�����ȳ������԰���ֵ(����ǿ��)����y���꣬����Ҫx���꣬x�ǵȼ��ı��ڻ�ͼ
		���������һ����uniform=false��˵���Զ���ˮƽ��࣬��i��ͨ���ֳ�histsize[i]��bins,��ranges[i]Ҳ������histsize[i]��Ԫ��
		ranges[i]�൱�ڸ������е�ˮƽ���꣬����{{0,2},{3,6},{7,9},{9,12},{17,19},{22,57}...{240,256}}��histsize[i]������Ȼ������ҿ�
		ÿ��Ԫ�ض�ָ���˵�ǰԪ�ص��½�(����)����һ��Ԫ�ص��Ͻ�(������)��˵���˾���bin��ʼ������Ϊ0,3,7,9,17,22,...��ÿ��bin�Ŀ�Ȳ�һ��
		��ranges[i]��STL���������
		����1��ͼƬ��3��ͨ����C���ָ���ķ�Χ����const float* ranges = {{0,256},{0,256},{0,256}}
		uniform=true��ʹ��STL�ʹ���vector<float> ranges = {0,256,0,256,0,256}
		uniform=false�����൱��ƽ̯C��������Ԫ�� �� vector={0,2,3,6,7,9...}��ÿ��ά�ȶ�Ӧ2��Ԫ��


		uniform=true���Ƿ�Եõ���ֱ��ͼ������й�һ������
		accumulate=false���ڶ��ͼ��ʱ���Ƿ��ۼƼ�������ֵ�ø���
		const float** ranges�� ͳ������ֵ������
	*/

	// ��1��ʹ�õ�ͨ��C���ʹ�ù淶����

	int  histsize = 256; // ��ͨ������256��bin 
	int histsize1[] = { 256 }; // ����&histsize����histsize1������ȷ��
	int nimages = 1; // ����ͼ��ĸ���
	int channels = 0; // �Ҷ�ͼֻ��1��ͨ��
	int channels1[] = { 0 }; // Ҳ����ʹ������,0��ʾ��0��ͨ��,����&channels��channels������
	int dims = 1; // ��Ҫͳ��ֱ��ͼͨ�����ܸ��� ����ѭ���ԻҶ�ͼ���� ����Ϊ1

	float range[] = { 0,256 };// 2��Ԫ�ص�����,˵�����صķ�Χ��ֻ��Ҫ����������������½�
	std::cout << "range = " << range << std::endl; // range = 000000B4094FF258 *range=0
	const float *ranges = { range }; // ָ�������׵�ַ��ָ�� ȥ��������Ҳ����
	std::cout <<"ranges[1] = "<< ranges[1] << std::endl; // *histRange = 0 histRange = range

	Mat b_hist, g_hist, r_hist;
	std::vector<Mat> hists = { b_hist, g_hist, r_hist };// ���ֱ��ͼ
	// ��˵ֻ��Ҫ����b_histһ�����ɵ���ϣ��ѭ������3���Ҷ�ͨ������ʹ������������߿��Բ�ʹ��ѭ��ֱ�Ӷ�3ͨ������

	/*
	��Ϊranges���滹�ã����Բ��Եĳ���ע�͵�
	���������ʹ����β��ԣ���ذѺ����ĳ���ע�͵�
	ranges++;
	//ranges++; // ���һ�ξ����
	// range++; �ǷǷ��� �������ֵ������� �޷�++
	std::cout << "*ranges++ = " << *ranges << std::endl; // *ranges++ = 256
	// ��˵��ranges��һ��ָ�������ָ��,++���Է��������Ԫ�أ�������ָ������
	
	//1) ��֤ranges�Ƿ���ָ������
	float range_[] = { 1,2,3 };
	//const float* p = { range ,range_ }; // �Ƿ�,p��ָ�������ָ��
	const float* p[] = { range ,range_ }; // ���ڵ�p����ָ������
	// p++;  �Ƿ�,ָ�������ǲ���++��
	std::cout <<"*p = "<< * p << "	*p[0] = "<< * p[0] << std::endl; // ǰ���ǵ�һ��������׵�ַ,�����ǵ�һ��������Ԫ��

	// 2) ��֤const float *ranges = { range }�� const float *ranges =  range �Ƿ���ͬ
	const float* p1 = range;
	p1++;
	//p1++;// ���һ�ξ���� ��������һ����
	std::cout << "*p1++ = " << *p1 << std::endl; // *p1++ = 256 ��������ȫ��ͬ
	*/
	for (int i = 0; i < 3; i++) // ʹ�õ�ͨ����C���ѭ������3���Ҷ�ͨ��
	{
		std::cout << "images[i].size() = " <<images[i].size() << std::endl; // ȷ�Ͽ�����������
		std::cout << "hists[i].size() = " << hists[i].size() << std::endl; // ȷ��װ������û����[0,0]
		calcHist(&images[i], nimages, channels1, Mat(), hists[i], dims, histsize1, &ranges, true, false); //C���
		std::cout << "hists[i].size() = " << hists[i].size() << std::endl; // ȷ��װ�������洢������[1,256]
	}
	
	// ���b_hist, g_hist, r_hist �Ƿ�Ҳ�����˱仯
	std::cout << "b_hist.size() = " << b_hist.size() << std::endl; 
	// b_hist.size() = [0 x 0] û�б仯 ˵�����������ã�����ʹ��hists[ ]
	// ��һ��
	int hist_h = 400; // ֱ��ͼ���512���߶�400
	int hist_w = 512;
	int bin_w = hist_w / histsize; // bin�Ŀ�� ���ܿ��/ bin�ĸ��� 512/256 = 2
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0)); // rows ,cols ���ڻ���ֱ��ͼ��ͼ�� 3ͨ�� 
	std::cout << "histImage.size() = " << histImage.size() <<std::endl;//histImage.size() = [512 x 400]
	 

	double alpha = 0.0; //  ���norm_typeΪNORM_MINMAX �Ƿ�Χ��һ������alphaΪ��Сֵ
	// ���norm_typeΪ�������ͣ���Ϊ��һ��Ҫ�˵�ϵ��
	double beta = histImage.rows; // ���norm_typeΪNORM_MINMAX ����betaΪ���ֵ 
	// ���norm_typeΪ�������ͣ�beta�����ԣ��˴����ᱻ�õ���һ�㴫��0
	std::cout << "beta = " << beta <<std::endl; // beta = 400
	int normType = NORM_MINMAX;
	int dtype = -1; // ���ȡ��ֵʱ��dst��srcͬ��������,����dst��src��ͬ����ͨ����,�Ҵ�ʱͼ�����ΪCV_MAT_DEPTH(dtype)
	//��һ�����ͣ���������NORM_L1, NORM_L2, NORM_INF, NORM_MINMAX
	Mat mask = {}; // ��ѡ������Ĥ
	//std::cout << hists[0] << std::endl; // û��һ��ǰ�õ��Ķ�������,����ͬǿ�ȵ�Ƶ�ʸ������򵽼�ʮ
	
	for (int i = 0; i < 3; i++)
	{
		// �������᲻����ʾ����������Ҫ�������һ��������߶�400
		// alpha =0 , beta = 512 ��ֱ��ͼ[3,256]��ÿ��ͨ��256��Ԫ�ع�һ����0-512֮��
		// ����2�������ʾ1��ֵ
		normalize(hists[i], hists[i],alpha,beta, normType,dtype,mask);
		//std::cout <<"hists["<<i<<"].size() = "<< hists[i].size() << std::endl;//hists[i].size() = [1 x 256]
	}
	// std::cout << hists[0] << std::endl; // �鿴��һ������� ֵ��0-400֮�� ������ʾ
	// ���Ǹ�������������Ҫȡ������


	int j = 0;
	Scalar color;
	for (std::vector<Mat> ::const_iterator it = hists.begin(); it != hists.end(); it++)
	{

		Mat T = *it; // ÿ��ͨ����ֱ��ͼѭ���������ȿ�ʼb_hist , ��256��Ԫ�� ���δ���0,1,2,,,255�ĸ���
		// ��ʱ�Ѿ���һ���õ�0-400֮��ɽ�����ʾ�����Ǽǵ���ȡ��
		std::cout << "j = " << j << std::endl;
		//if (j == 0)
		//	color = { 255, 0, 0 };
		//else if (j == 1)
		//	color = {0, 255, 0};
		//else 
		//	color = { 0, 0, 255 };
		switch (j)
		{
			case 0:
				color = { 255, 0, 0 }; // �����û�����,������Բ����
				break;
			case 1:
				color = { 0, 255, 0 };
				break;
			case 2:
				color = { 0, 0, 255 };
				break;
		}
		j++;

		for (int i = 1; i < histsize; i++) // ÿ��ͨ��������binѭ�� 1,2,..,255
		{
			int y1 = cvRound(T.at<float>(i - 1)); // ��1����ǡ����400
			int y2 = cvRound(T.at<float>(i));
			int x1 = (i - 1) * bin_w;
			int x2 = i * bin_w;
			//std::cout << "(x1,y1) = " << "(" << x1 << "," << y1 << ")"
			//	<< "   (x2,y2) = " << "(" << x2 << "," << y2 << ")" << std::endl; // ÿ��������껭��
			line(histImage,
				Point(x1, y1),
				Point(x2, y2),
				color, 2, LINE_AA);
		}
	}
	imshow("histImage", histImage);
	waitKey(0);
	destroyAllWindows();
}