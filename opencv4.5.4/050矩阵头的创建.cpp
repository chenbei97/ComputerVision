#include "primary.h"
using namespace cv;
void image_matrix_head_create()
{
	Mat kernel = (Mat_<double>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
	// 矩阵头表示访问矩阵的某一行列或者范围,复制矩阵头不会不会复制数据
	// 利用成员函数去访问
	Mat row_n = kernel.row(2);
	Mat col_n = kernel.col(1);
	Mat row_range = kernel.rowRange(1, 2);
	Mat col_range = kernel.colRange(0, 2);
	std::cout << row_n << "\n" << col_n << std::endl;
	std::cout << row_range << "\n" << col_range << std::endl;
}