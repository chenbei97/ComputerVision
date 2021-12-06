#include "primary.h"
using namespace cv;
void generate_gauss_blur_kernel(Mat & kernel , Size size , double sigma);
void guass_filter(const Mat & src, Mat & blur , Mat& kernel);
void gauss_dog(const Mat& src , Mat &dst , Size size , double sigma , bool usefunc = true, bool show = false, double k=1.6);
void image_feature_detection_log()
{
	/*
		1.首先对图像f(x,y)平滑滤波,滤波函数位高斯函数G(x,y)
			G(x,y) = 1/2*pi*σ1*σ2 × exp{-[(x-μ1)^2/σ1^2+(y-μ2)^2/σ2^2]/2}
			令σ1=σ2合并,μ1=μ2=0化简得到如下等式
			G(x,y) = 1/2*pi*σ^2 × exp{-(x^2+y^2)/2*σ^2}
		2.G(x,y)是圆对称函数,将G(x,y)和f(x,y)进行卷积得到平滑图像g(x,y)
					g(x,y) = f(x,y) @ G(x,y)
		3.对平滑后的图像进行增强,即使用拉普拉斯核锐化得到h(x,y)
					h(x,y) = ▽^2(f(x,y) @ G(x,y))
		4.检测二阶导数的零交叉点,即h(x,y)=0的像素点,这些点对应一阶导数峰值较大的点
			而局部梯度较大值的这些点就是边缘点,实际应用为了避免检测出非显著边缘应当选择
			一阶导数大于某一阈值的零交叉点作为边缘点
		5.因为对f(x,y)先求与G(x,y)的卷积再求二阶拉普拉斯导数
			等价于先对G(x,y)求拉普拉斯再求其与图像的卷积
				所以 h(x,y) = f(x,y) @ ▽^2(G(x,y))
		6.▽^2(G(x,y))称为log滤波器,表达式为
			▽^2(G(x,y)) = ∂^2G/∂x^2 + ∂^2G/∂y^2 
								= 1/pi*σ^4 ×{(x^2+y^2)/2σ^2 - 1}× exp{-1/2σ^2(x^2+y^2)}
		7.两种方式数学上是等价的,常用的5×5近似高斯-拉普拉斯算子如下所示
			[ -2, -4, -4, -4, -2]
			[ -4,  0,  8,  0,  -4]
			[ -4,  8, 24, 8,  -4]
			[ -4,  0,  8,  0,  -4]
			[ -2, -4, -4, -4, -2] 
	*/
	Mat src = imread(imgAddr + "lena.jpg");
	Mat edge1, edge2;
	double sigma = 2;
	Size kernel_size(7, 7);
	bool show = false;
	double k = 1.6;
	gauss_dog(src,edge1,kernel_size,sigma,true,show,k); // 使用自带的高斯滤波函数
	gauss_dog(src, edge2, kernel_size, sigma, false, show,k);// 使用自定义的高斯滤波函数
	imshow("edge1",edge1);
	imshow("edge2", edge2);
	waitKey(0);
	destroyAllWindows();
}
void generate_gauss_blur_kernel(Mat& kernel, Size size, double sigma)
{
	kernel.create(size, CV_64F);
	int height = size.height;
	int width = size.width;
	int center_h = (height - 1) / 2; //中心行坐标
	int center_w = (width - 1) / 2; // 中心列坐标
	double sum = 0.0; // 计算整个核元素的和用于归一化
	double x, y;
	for (int i = 0; i < height; ++i)
	{
		y = pow(i - center_h, 2); // 中心位置认为是0,从负轴开始到正轴进行平方得到一系列点
		for (int j = 0; j < width; ++j)
		{
			x = pow(i - center_w, 2); // 这是x方向得到一系列点
			double value = exp(-(x + y) / (2 * pow(sigma, 2)));
			// 因为后面还要进行归一化所以不计算常数减少计算量
			kernel.at<double>(i, j) = value;
			sum += value;
		}
	}
	kernel /= sum;
	//std::cout << kernel << std::endl;
}
void guass_filter(const Mat& src, Mat& blur, Mat & kernel)
{
	int rows = (kernel.rows - 1) / 2;
	int cols = (kernel.cols - 1) / 2;
	std ::cout<< "rows = " << rows << "   cols = " << cols << std::endl;
	blur = Mat::zeros(src.size(), src.type());
	Mat newsrc;
	// 填充边界,上下左右填充的长度,边界类型
	int top, bottom, left, right;
	top = bottom = rows;// 填充3
	left = right = cols; // 填充3
	copyMakeBorder(src,newsrc,top,bottom,left,right,BORDER_REPLICATE); // 使用复制像素方法填充
	// 220*220 ----> 226*226
	std::cout <<"src.rows = "<<src.rows<< "   newsrc.rows = "<<newsrc.rows <<
		"\nsrc.cols = "<<src.cols<<"   newsrc.cols = "<< newsrc.cols << std::endl;

	// 开始滤波
	for (int row = rows ; row < src.rows +rows;++row) //步长为1但是起始位置是(3,3)-->(222,222)
		for (int col = cols; col < src.cols + cols; col++)
		{
			//std::cout << "(x,y) = " << "(" << row << "," << col << ")" << std::endl;
			double sum[3] = { 0 }; // 用于统计3个通道的元素和,单通道时只使用sum[0]
			// 外部双for是对图像循环,每移动1行or1列就会计算一次双for内循环,得到元素相乘的累积和值
			// 内部双for是对核循环,但认为kernel的中心为原点,内部for不受外部for影响,永远是从-3到3遍历
			for (int r = -rows ; r <= rows ; ++r) // (-3,3)之间
					for (int c = -cols; c <= cols; ++c)// (-3,3)之间
					{
						if (src.channels() == 1)
						{
							// row∈(rows,src.rows+rows),r∈(-rows,rows) =>(0,rows+2*rows)=(0,226)
							// col∈(cols,src.cols+cols),r∈(-cols,cols) =>(0,cols+2*cols)=(0,226)
							// srcval其实就是遍历了整个newsrc的值
							double srcval = newsrc.at<uchar>(row + r, col + c); // 图像值
							// r+rows∈(0,2*rows),c+cols∈(0,2*cols)=(0,6)
							double kerval = kernel.at<double>(r + rows, c + cols); // 核值
							sum[0] += srcval * kerval;
						}
						else if (src.channels() == 3)
						{
							Vec3b srcvals = newsrc.at<Vec3b>(row + r, col + c); // 坐标不发生变化
							double kerval = kernel.at<double>(r + rows, c + cols); // 核值
							sum[0] += srcvals[0] * kerval;
							sum[1] += srcvals[1] * kerval;
							sum[2] += srcvals[2] * kerval;
						}			
					}
			for (int channel = 0; channel < src.channels(); channel++)
			{
				if (sum[channel] < 0)
					sum[channel] = 0; // 因为像素值不会有负数
				else if (sum[channel] > 255)
					sum[channel] = 255; // 限制范围
			}
			if (src.channels() == 1) // 处于外部双for循环,内部的计算已经完成,直接赋值即可
			{
				// blur没有填充图像,故blur_row∈(0,src.rows) , blur_col∈(0,src.cols)
				blur.at<uchar>(row-rows,col-cols) = static_cast<uchar>(sum[0]); 
			}
			else if (src.channels() == 3)
			{
				Vec3b rgb = { static_cast<uchar>(sum[0]),static_cast<uchar>(sum[1]),static_cast<uchar>(sum[2]) };
				blur.at<Vec3b>(row - rows, col - cols) = rgb;
			}
		}

}
void gauss_dog(const Mat& src, Mat& dst, Size size, double sigma, bool usefunc ,bool show, double k )
{
	Mat kernel1,kernel2,blur1,blur2;
	if (usefunc)
	{
		GaussianBlur(src,blur1,size,k*sigma);
		GaussianBlur(src, blur2, size, sigma);
		dst = blur1 - blur2;
	}
	else
	{
		generate_gauss_blur_kernel(kernel1, size, k * sigma);
		generate_gauss_blur_kernel(kernel2, size, sigma);
		guass_filter(src, blur1, kernel1);
		guass_filter(src, blur2, kernel2);
		// 高斯差分DOG的图像等于不同σ下使用log滤波的结果图像之差
		dst = blur1 - blur2 - 1;
	}
	
	if (show)
	{
		Mat inverse_dst, temp;
		bitwise_not(dst, inverse_dst);
		imshow("blur1", blur1);
		imshow("blur2", blur2);
		imshow("dst1", inverse_dst); // 看不清二值化处理后看得清
		threshold(dst, temp, 0, 255, THRESH_BINARY); // 二值化处理
		imshow("dst2", temp);
		waitKey(0);
		destroyAllWindows();
	}
	threshold(dst, dst, 0, 255, THRESH_BINARY); // 二值化处理
}