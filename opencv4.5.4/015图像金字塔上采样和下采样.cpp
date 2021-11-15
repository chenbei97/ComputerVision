#include "primary.h"
#include <vector>
#include <string>
using namespace cv;
using namespace std;
void image_up_down_sampling()
{
	// ͼ���������Ҫ�ȶԲ�ģ��,Ȼ����в���,������ɾ��ż��������
	// ����ͼƬֻ��ԭ����1/4��С(���)����220��220->110��110
	// ��˹�����һ��ͼ�������ֲ�����֮��Ĳ�ֵͼ�񣬳����ڽǵ���
	// ����˵���ϲ������²���API��ʹ��
	const Mat src = imread(imgAddr + "apple.jpg");
	Mat up, down;
	pyrUp(src,up,Size(src.cols *2 , src.rows * 2));
	pyrDown(src, down, Size(src.cols / 2, src.rows / 2));
	cout << "up = " << up.size() << "	down=" << down.size() << endl;
	bool show_up_down = false;
	if (show_up_down == true)
	{
		imshow("up",up);
		imshow("down", down);
		waitKey(0);
		destroyAllWindows();
	}
	// ͼ�������ĳһ��ĸ�˹���DoG
	Mat gray, temp1, temp2,dst;
	double sigmaX1 = 1.0,  sigmaX2 = 1.5 , sigmaY = 0.0;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	GaussianBlur(gray,temp1,Size(5,5),sigmaX1,sigmaY);
	GaussianBlur(gray, temp2, Size(15, 15), sigmaX2, sigmaY);
	subtract(temp1,temp2,dst);
	bitwise_not(dst,dst);
	//imshow("dst",dst);
	//waitKey(0);
	//destroyAllWindows();

	// ͼ�������
	vector<Mat> image_pyramid;
	double sigmaX = 3.0;
	Mat T = src;
	image_pyramid.push_back(src);
	while (min(T.cols, T.rows) != 1)
	{
		GaussianBlur(T,T,Size(3,3),sigmaX,sigmaY);
		pyrDown(T, T,Size(T.cols/2,T.rows/2));
		cout <<"T.size = " << T.size() <<  endl;
		image_pyramid.push_back(T);
	}
	cout << "guassian_pyramid.size() = "<< image_pyramid.size()<< endl;
	vector<Mat> ::iterator it;
	int i = 1;
	for (it = image_pyramid.begin();it != image_pyramid.end()-6; it++)
	{
		// _itos_s(int _Value, char *_Buffer, size_t _BufferCount, int _Radix);
		//char str[3];
		//_itoa_s(i , str,sizeof(str),10); // ʮ����,�����ֽڲ��ܳ���str
		stringstream str;
		str << i;
		//imshow("img"+str.str(), *(it));
		i++;
	}
	//waitKey(0);
	//destroyAllWindows();
	//��˹������������һ��������,�����кܶ���(Octave)���������ɣ�
	// ����ÿ����������������ɲ�
	// �Ƚ�ԭͼ������һ��֮����Ϊ��˹�������ĵ�1���1��
	// ����1���1��ͼ�񾭸�˹����õ���1���1��
	// �����ң���Sift������ȡ���ǹ̶�ֵ1.6
	// ���ҳ���һ������ϵ��k,�ȵ�һ���µ�ƽ�����Ӧ�=k*�ң�������ƽ����1���2��ͼ��
	// �������ظ������õ�L��ͼ����ͬһ����ÿһ��ͼ��ĳߴ綼��һ����
	// ֻ��ƽ��ϵ����һ�� 0���ң�k�ң�k^2��,k^3�ҡ���k^(L-2)��
	//  ����1�鵹��������ͼ������������Ϊ2�Ľ��������õ���ͼ����Ϊ��2��ĵ�1��
	// �Ե�2��ĵ�1��ͼ����ƽ������Ϊ�ҵĸ�˹ƽ�����õ���2��ĵ�2��,����ִ��,�ڳߴ緽���2���ǵ�1��ͼ���һ��

	waitKey(0);
	destroyAllWindows();
}