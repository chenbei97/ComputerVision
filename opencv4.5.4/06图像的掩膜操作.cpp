#include"primary.h"
using namespace cv;
void image_mask_operation()
{
	Mat src = imread("D:/VisualStudioItems/apple.jpg", IMREAD_COLOR);//IMREAD_GRAYSCALE
	std::cout << "src.depth() = " << src.depth() << std ::endl; // src.depth()��ʾλͼ���
	int channels = src.channels();
	int cols = (src.cols - 1) * channels; // ���,����Ǵ�ͼ���1�п�ʼ��,���ǵ�0�� 2247
	// ��ͨ��������ΪĬ�Ͻ�ͼ�������ͨ����������ƽ��,����3��������
	int rows = src.rows - 1 ; // �߶�,��ͬ�� 561

	std::cout << "rows = " << src.rows << "cols = "<< src.cols <<std :: endl; // rows = 562cols = 750
	Mat im1 = Mat :: zeros(src.size(), src.type());
	Mat im3(src.size(), CV_8UC3, Scalar(0, 0, 0)); // 8λ�޷���3ͨ��,ע��Scalar�Ĺ���Ҫ��ͨ����һ��
	Mat im4(3,3, CV_8UC1, Scalar(1));
	std::cout << im4 << std::endl;
	Mat im5(3, 3, CV_8UC2, Scalar(1)); // ������ʵ��ʽ�ĵ�����Scalar(1,0)
	std::cout << im5 << std::endl;
	Mat im6(3, 3, CV_8UC2, Scalar(1,2,3));// ��Ȼ��ʽ����Scalar(1,2,0),3������
	std::cout << im6 << std::endl;
	/*           [ a , b , c ]                   [ 0 -1 0  ]
	kernel = [ d , e , f ]   ����ʹ��[ -1 5 -1 ]
	              [ g , h , k ]                  [ 0  -1 0 ]
	��Ĥ��ͼ����������ֵI(x,y)  = a * I(x-1,y-1) + b * I(x-1,y) + c * I(x-1,y+1)+ ...\
											              d * I(x,y-1) + e * I(x,y) + f * I(x, y+1)+...\
											              g * I(x+1,y-1) + h * I(x+1,y) + k*I(x+1,y+1)
	���� x, y ����1
	*/
	int a = 0, b = -1, c = 0, d = -1, e = 5, f = -1, g = 0, h = -1 , k = 0; // kernel coeff
	Mat image;
	image = src;
	for (int row = 1; row < rows; row++) // 1-561
	{
		// ����ptrָ�����
		const uchar* previous_row = image.ptr<uchar>(row - 1); // ʹ��const��ֹ�޸�ԭͼ��
		const uchar* current_row = image.ptr<uchar>(row );
		const uchar* next_row = image.ptr<uchar>(row + 1);
		uchar* output = im3.ptr<uchar>(row); // ���ͼ�����ָ��
		for (int col = channels; col < cols; col++) // (row,col)��(1,1)��ʼ ,1-2246
		{
			 //�Ե�0��Ϊ��,ƽ������(0,0)(0,1)(0,2)�ǵ�0�У��Դ�����ÿ��ͨ��֮�䶼��3��λ��
			 //rowӦ���ӵ�1�п�ʼ,colӦ����3��ʼ,��Ϊƽ������(1,3)(1,4)(1,5)��������ϵ�ĵ�1��,
			int result = a * previous_row[col - channels] + b * previous_row[col] + c * previous_row[col + channels] +
				                  d * current_row[col - channels] + e * current_row[col] + f * current_row[col + channels] +
				                  g * next_row[col - channels] + h * next_row[col] + k * next_row[col + channels];
			output[col] = saturate_cast<uchar>(result);

			//int result = e * current_row[col] - (current_row[col-channels]+current_row[col+channels]+previous_row[col]+next_row[col]);
			//output[col] = saturate_cast<uchar>(result); // ���Ʒ�Χ
			
			//std::cout <<"col = " << col <<"	current_row[col] = "<<current_row[col] << std::endl;
			//std::cout << "(row,col) = " << "("<<row << "," << col<<")"<< std::endl;
		}
	}

	// ʹ�ú���ʵ����Ĥ
	Mat kernel = ( Mat_<float>(3, 3) << 1 , 1 , 1 , 1 , 5, 1 , 1 , 1 , 1 ) ;
	Mat im2 = Mat::zeros(src.size(), src.type());
	filter2D(src,im2,src.depth(),kernel);
	namedWindow("output2", WINDOW_AUTOSIZE);
	imshow("output2", im2);

	namedWindow("input", WINDOW_AUTOSIZE);
	namedWindow("output1", WINDOW_FREERATIO);

	imshow("output1",im3);

	imshow("input", src);
	waitKey(0);
	destroyAllWindows();

}