#include"primary.h"
using namespace cv;
void image_mask_operation()
{
	Mat src = imread("D:/VisualStudioItems/apple.jpg", IMREAD_COLOR);//IMREAD_GRAYSCALE
	std::cout << "src.depth() = " << src.depth() << std ::endl; // src.depth()表示位图深度
	int channels = src.channels();
	int cols = (src.cols - 1) * channels; // 宽度,卷积是从图像第1列开始的,不是第0列 2247
	// 乘通道数是因为默认将图像的所有通道依次向右平铺,故有3倍的列数
	int rows = src.rows - 1 ; // 高度,行同理 561

	std::cout << "rows = " << src.rows << "cols = "<< src.cols <<std :: endl; // rows = 562cols = 750
	Mat im1 = Mat :: zeros(src.size(), src.type());
	Mat im3(src.size(), CV_8UC3, Scalar(0, 0, 0)); // 8位无符号3通道,注意Scalar的构造要与通道数一致
	Mat im4(3,3, CV_8UC1, Scalar(1));
	std::cout << im4 << std::endl;
	Mat im5(3, 3, CV_8UC2, Scalar(1)); // 这样其实隐式的调用了Scalar(1,0)
	std::cout << im5 << std::endl;
	Mat im6(3, 3, CV_8UC2, Scalar(1,2,3));// 仍然隐式调用Scalar(1,2,0),3被舍弃
	std::cout << im6 << std::endl;
	/*           [ a , b , c ]                   [ 0 -1 0  ]
	kernel = [ d , e , f ]   本例使用[ -1 5 -1 ]
	              [ g , h , k ]                  [ 0  -1 0 ]
	掩膜后图像中心像素值I(x,y)  = a * I(x-1,y-1) + b * I(x-1,y) + c * I(x-1,y+1)+ ...\
											              d * I(x,y-1) + e * I(x,y) + f * I(x, y+1)+...\
											              g * I(x+1,y-1) + h * I(x+1,y) + k*I(x+1,y+1)
	其中 x, y 均≥1
	*/
	int a = 0, b = -1, c = 0, d = -1, e = 5, f = -1, g = 0, h = -1 , k = 0; // kernel coeff
	Mat image;
	image = src;
	for (int row = 1; row < rows; row++) // 1-561
	{
		// 采用ptr指针访问
		const uchar* previous_row = image.ptr<uchar>(row - 1); // 使用const防止修改原图像
		const uchar* current_row = image.ptr<uchar>(row );
		const uchar* next_row = image.ptr<uchar>(row + 1);
		uchar* output = im3.ptr<uchar>(row); // 输出图像的行指针
		for (int col = channels; col < cols; col++) // (row,col)从(1,1)开始 ,1-2246
		{
			 //以第0行为例,平铺坐标(0,0)(0,1)(0,2)是第0列，以此类推每个通道之间都差3个位置
			 //row应当从第1行开始,col应当从3开始,因为平铺坐标(1,3)(1,4)(1,5)才是坐标系的第1列,
			int result = a * previous_row[col - channels] + b * previous_row[col] + c * previous_row[col + channels] +
				                  d * current_row[col - channels] + e * current_row[col] + f * current_row[col + channels] +
				                  g * next_row[col - channels] + h * next_row[col] + k * next_row[col + channels];
			output[col] = saturate_cast<uchar>(result);

			//int result = e * current_row[col] - (current_row[col-channels]+current_row[col+channels]+previous_row[col]+next_row[col]);
			//output[col] = saturate_cast<uchar>(result); // 限制范围
			
			//std::cout <<"col = " << col <<"	current_row[col] = "<<current_row[col] << std::endl;
			//std::cout << "(row,col) = " << "("<<row << "," << col<<")"<< std::endl;
		}
	}

	// 使用函数实现掩膜
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