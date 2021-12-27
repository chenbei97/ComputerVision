## 1.基本的数据结构

### 1.1概述

​	cv::Vec<>，固定向量类，向量可以承载2,3,4,6个元素，类型有b(unsigned char)、w(unsigned short)、s(short)、i(int)、f(float)、d(double)；所以固定向量类有很多的别名，cv::Vec{2,3,4,6}{b,w,s,i,f,d}，例如cv::Vec2i表示具有2个整型元素的固定向量，访问元素通过下标访问myVec[0]、myVec[1]，也可以通过圆括号访问myVec(0)

​	cv::Point<>，固定点类，只有2-3个元素，用来描述二维、三维坐标，与固定向量类不同在于通过句号运算来访问，即myPoint.x、myPoint.y，常用cv::Point2f

​	cv::Scalar<>，在固定点类基础上实现，本质上是四维Point类，一般使用双精度，继承于cv::Vec<double,4>，但是是通过下标访问的

​	cv::Size<>，和固定点类很像，区别是属性为width、height而不是x、y，因为高度宽度是整数，实际上使用的是cv::Size2i，浮点类型也可以cv::Size2f

​	cv::Rect<>，是处理整数类型的矩形，有坐标和宽高

​	cv::RotateRect<>，用于处理非轴对称的矩形，一个cv::Point2f类型的中心点，一个cv::Size2f的size，还有一个额外的浮点类型的角度

### 1.2 cv::Point坐标类

	#### 1.2.1基本操作

```c++
using namespace cv ;
// 1.默认构造函数
cv :: Point2i p ; // 二维点
cv :: Point3i p ; // 三维点
//2.复制构造函数
cv :: Point3f p2(p1) ;
// 3.值构造函数
cv :: Point2i(x,y) ;
cv :: Point3d(x,y,z) ;
// 4.构造成固定向量类
(cv :: Vec3f) p ;
// 5.成员访问
p.x , p.y 
// 6.常用函数
float x = p1.dot(p2) ;
double x = p1.dot(p2) ; // 点乘
p1.cross(p2) ; // 叉乘
p.inside(r); // 判断一个点p是否在举行r内
```

### 1.3 cv::Scalar四维点类

​	这个类所有成员都是双精度浮点数，有一些常用的函数，注意没有固定向量类的转换操作，因为cv::Scalar类继承于固定向量类，自身也算是固定向量类

​	Scalar是一个四个元素的数组类

#### 1.3.1基本操作

```c++
cv :: Scalar s ; // 默认构造
cv :: Scalar s2(s1) ; // 复制构造
cv :: Scalar s(x) ; // 值构造
cv :: Scalar s(x,y,w,h) ; 
s1.mul(s2) ; // 元素相乘
s.conj(); // 四元数共轭，返回cv :: Scalar(s0,-s1,-s2,-s3)
s.isReal() ; // 返回bool型, 如果s1=s2=s3为真
```

### 1.4 cv::size宽高类

​	类似于cv::Point类，都是组成2个元素，可以互相转化，size和point可以共同被scalar使用

​	具备常用的默认构造函数、值构造和复制构造，句点访问的属性以及特有的成员函数area

​	最后size类不支持转换为vec类，这点和point类不同

```c++
sz.width , sz.height ;
sz.area(); // 矩形面积
Size()
```

### 1.5 cv::Rect矩形类

​	矩形类常用于表示矩形区域的左上角坐标和区域的高度和宽度，可以使用size类和point类

#### 1.5.1基本操作

```c++
cv :: Rect r1 ;
cv :: Rect r2(r1) ;
cv :: Rect r(x,y,w,w) ;
cv :: Rect r(point,size) ; // 通过坐标类和圆类构造
cv :: Rect r(p1,p2) ; // 使用两个对角坐标也可以构造
r.x, r.y, r.height, r.width // 访问成员
r.area() ; // 面积
r.tl(); 左上角坐标
r.br() ; // 右下角坐标
r.contains(p); // 区域是否包含坐标

// 覆写操作符
cv :: Rect r3 = r1 & r2 ; 
r1 &= r2 ; // 交集
r1 |= r2 ; // 并集
cv :: Rect rx = r + x; // 平移矩形x个数量
r += x ; // 平移
cv :: rect rs = r + s ; // 扩大矩形大小
bool eq = (r1 == r2) ; // 矩形是否重叠

```

### 1.6 cv::RotateRect类

​	少数没有使用模板的接口类，包含中心点point、大小size以及角度float

​	Rect类以左上角为原点，RotateRect以原点

#### 1.6.1基本操作

```c++
cv :: RotateRect rr() ;// 默认构造
cv :: RotateRect rr2(r1) ; // 赋值构造
cv :: RotateRect rr(p1,p2) ; // 两点构造
cv :: RotateRect rr(p,,sz,theta) ; // 值构造
rr.center , rr.size , rr.angle ; // 成员
rr.points(pts[4]) ; // 返回4个角的列表
```

### 1.7 cv::Matx固定矩阵类

​	固定矩阵类的子类是固定向量类，适用于实现已知矩阵大小的情况，对于图像和大型数组使用Mat

​	定义格式为 

```
cv :: Matx{1,2,..,6}{1,2..6}{f,d} ; // 数字只能在1-6之间分配
```

#### 1.7.1基本操作

```c++
Matx66f m0; // 默认构造
Matx33d m1 = { 0,1,2,3,4,5,6,7,8 }; // 值构造
Matx33d m2(m1);// 复制构造
double x = 1;
Matx33d m3 = Matx33d::all(x); // 使用相同元素构造
Matx33d m4 = Matx33d::zeros(); // 0矩阵
Matx33d m5 = Matx33d:: ones(); // 全1
Matx33d m6 = Matx33d:: eye(); // 单位阵
//Matx31f  m7 = Matx33f ::diag(); // 对角阵
Matx33d m8 = Matx33d::randu(5, 10); // 均匀分布
Matx33d m9 = Matx33d::randn(0, 1);// 正态分布

cout << "m9(5, 5) = " << m9(2, 2)<<endl; // 注意不要越界,m9为3×3
cout << m9.dot(m9) << m9.ddot(m9) << endl; // 点积
Matx34f m10;
Matx43f m11 = m10.reshape<4, 3>(); // 改变形状


Matx66d m12 = (Matx66d)m0;// 改变类型
auto m13 = m12.get_minor<2, 2>(3, 3); // 提取(3,3)处的2×2子矩阵
auto m14 = m12.row(2);
auto m15 = m12.col(3); // 提取矩阵的行列
auto m16 = m12.diag();
auto m17 = m12.t();
auto m18 = m12.inv(DECOMP_LU);//提取对角线和计算转置以及求逆(指定方法)
auto m19 = m9.mul(m9); // 元素乘法
```

### 1.8 cv::Vec固定向量类

​	该类继承于cv::Matx类，可以看成是Matx列为1的特例，它可以衍生出Scalar类

​	具备常规的拷贝、复制和值构造，成员访问可以使用[]也可以使用()

```c++
Vec8i v1(1,2,3,4,5,6,7,8);
cout << "v1[7]=" << v1[7] <<"  v1(7)="<< v1(7) << endl; // 成员访问
// Vec8i v2 = v1.cross(v1);
```

### 1.9 cv::complex复数类

​	与STL复数类模板不同，可以转换，最大的区别是成员访问，STL通过成员函数real()和imag()获取，opencv是通过句号运算符访问

```c++
Complexd c(5, 10);// 双精度
cout << "real=" << c.re << "   imag=" << c.im << endl; // 成员访问
cout << "共轭虚部="<<c.conj().im << endl;
```

### 1.10 cv::Range类

​	用于确定一个连续的整数序列，有2个元素start和end，范围包括start不包括end，使用size()函数可以得到元素数量

​	还有一个成员函数empty()用于判断是否含有元素；

​	最后all()函数可以用于任何需要获得对象可用范围的时候

### 1.11 cv::TermCriteria类

​	此函数是辅助对象，也有函数需要传递一些条件，这些条件用一个类实现，具体的条件类型在头文件已经用常量定义，只需要将其传入给一些算法函数的实参即可

​	常见的构造函数为

```c++
cv :: TermCriteria(int type , int maxCount , double epsilon)
```

变量type被设置为cv::TermCriteria::COUNT 或者 cv::TermCriteria::EPS，或者使用并运算一起使用，然后传入算法中

### 1.12 cv::ptr类

​	智能指针允许创建一个对象的引用，并传递到各处，这些引用会被计数，引用的实例消失时会自动释放，无需手动释放

​	有一些附加函数addref和release，可以增加和减少指针内部的引用次数，而empty是用于判断指针对象的实例是否存在。

​	最后一个函数是delete_obj，引用计数为0时自动调用的函数

### 1.13 cv::Mat大型数组类

​	所有的Mat实例都带有一些属性

```c++
mat.dims ; // 维度->维度一般是2，是二维图像
mat.channels(); // 通道数，一般是3或者1
mat.flag ; // 数组元素类型
mat.rows ; // 行->height
mat.cols ; // 列->width
mat.depth(); // src.depth()表示位图深度，有32、24、8等
// 还有一个指向数据真正存储位置的指针
// 一个表示该内存区域有多少个引用的refcount元素
```

​	最常见的构造函数是指定行列和数据类型，数据类型也是在头文件已经被定义，例如CV_32FC3表示3通道32位浮点类型

```c++
cv::Mat m1(3, 5, CV_32FC3); // (int rows , int cols ,int type)
cv::Mat m2(3, 5, CV_32FC3,cv :: Scalar(1.0f, 2.0f , 0.0f)); // 赋予初值,每个通道分别使用1,2,0赋值
cv::Size sz(3, 5);
cv::Mat m3(sz, CV_32FC3);//用size类初始化
cv::Mat m4 = cv::Mat::eye(10, 10, CV_32FC3);// 调用方法初始化
```

​	赋值操作的机制：并两个变量m1和m2，将m2=m1，实际上是将m2的内部数据指针指向m1，m2如果是那块内存区域的最后一个引用，则指向的实体(如果存在)将会被释放，相应的当前m2和m1共享的内存区域会多增加一个引用

​	

## 2. OpenCV4 C++ 快速入门

### 2.1 读取和显示图像

```c++
void imread_imshow()
{
    Mat src = imread("D:/VisualStudioItems/apple.jpg",IMREAD_GRAYSCALE);
    if (!src.empty())
    {
        std::cout << "src.depth()=" << src.depth() << std::endl;
        namedWindow("input", WINDOW_FREERATIO);//可调的自由比例
        imshow("input", src);
        waitKey(0);
        destroyAllWindows();
    }
    else
        printf("could not load image...");
}
```

### 2.2图像格式转换并保存

```c++
void image_type_conversion_imwirte()
{
    Mat src = imread("D:/VisualStudioItems/apple.jpg", IMREAD_COLOR);
    Mat gray,hsv;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    cvtColor(src, hsv, COLOR_BGR2HSV);
    namedWindow("gray", WINDOW_FREERATIO);
    namedWindow("hsv", WINDOW_FREERATIO);
    imshow("gray", gray);
    imshow("hsv", hsv);
    waitKey(0);
    //imwrite("D:/VisualStudioItems/apple_gray.jpg", gray);
}
```

### 2.3 图像的赋值和拷贝

​	Mat数据格式使用赋值时用的是指针，并不会创建新的内存块

​	赋值的引用做了操作改变内存数据后，其他引用的也会改变，但是copy和克隆不会

```c++
void image_assignment_copy_clone()
{
	Mat src = imread("D:/VisualStudioItems/apple.jpg", IMREAD_COLOR);

	Mat src_assign = src; // 赋值

	Mat src_copy;
	src.copyTo(src_copy); // 复制

	Mat src_clone = src.clone(); // 克隆

	// 常用的创建空白图像的方法
	Mat img1 = Mat::zeros(src.size() , src.type()); // 使用已有图像的类型
	Mat img2 = Mat::ones(Size(220, 220), CV_8UC3);// 8位无符号整型三通道
	
	img2 = 127; // 使用整数赋值
	img2 = Scalar(10, 20, 30); // 使用scalar赋值，Scalar是一个四个元素的数组类
	
	Scalar s1(0,255,255); // 黄色
	std::cout << s1 << std::endl;//[0, 255, 255, 0]
	img2 = s1; // 把Scalar向量在所有通道上的所有行反复的按列复制
	// std :: cout << img2 << std::endl; // 可以直接打印

	Mat img2_assign = img2; // 赋值
	img2_assign = Scalar(255, 0, 0);//蓝色 BGR
	imshow("img2_1",img2); // 蓝色,说明改变赋值对象也会改变任何引用指向的对象

	Mat img2_clone = img2.clone();// 改变克隆对象不会改变被克隆对象
	img2_clone = Scalar(0, 255, 0);
	imshow("img2_clone", img2_clone);// 绿色
	imshow("img2_2", img2);// 蓝色,不改变
	waitKey();
}
```

### 2.4访问图像数组的方式

#### 2.4.1 使用at访问

##### 2.4.1.1 单通道图像

​	at访问是值访问，如果通过指针访问需要使用 Mat的智能指针模板函数ptr

​	如果图片数据时uint8类型的，或者说uchar类型，使用以下方式

```c++
int uint_value = src.at<uchar>(row, col);// 自动提升位为整型
```

​	若图片数据是0-1的浮点类型，使用

```c++
float float_value = src.at<float>(row, col);
```

##### 2.4.1.2 多通道图像

​	多通道会直接读取每个通道在指定位置坐标的数据的组合，也就是向量Vec，可以使用Vec3b、Vec3i或者Vec3f，这些是比较常用的返回类型。注：不能使用Scalar类接收at的返回值

```c++
Vec3b vector_value = src.at<Vec3b>(row, col);
```

​	对上述返回的向量继续得到具体的通道值，使用[]索引即可，根据[1.8 cv::Vec固定向量类](#1.8 cv::Vec固定向量类)可以知道也可以使用()访问

```c++
src.at<Vec3b>(row, col)[0] = 255 - vector_value[0]; // 继续访问每个通道
src.at<Vec3b>(row, col)(1) = 255 - vector_value(1); // ()访问也可
src.at<Vec3b>(row, col)[2] = 255 - vector_value[2];
```

​	以上所有代码如下所示

```c++
double time0 = static_cast<double>(getTickCount());
// <1> 使用at访问(借助索引)
for (int row = 0; row < height; row++)
    for (int col = 0; col < width; col++)
    {// 遍历数组
        if (channels == 1)
        { // 灰度图像
            int uint_value = src.at<uchar>(row, col); // 这个图片是0-255类型的
            src.at<uchar>(row, col) = 255 - uint_value;+
            /*float float_value = src.at<float>(row, col);*/
            if (i < 50)
            {
                std::cout << "uint = " << uint_value << std::endl;
                i++;
            }
            else
                break;
        }
        else if (channels == 3)
        { // 彩色图像
            Vec3b vector_value = src.at<Vec3b>(row, col); // 一次性读取了3个通道的位置上的数值组成了数组
            src.at<Vec3b>(row, col)[0] = 255 - vector_value[0]; // 继续访问每个通道
            src.at<Vec3b>(row, col)(1) = 255 - vector_value(1);
            src.at<Vec3b>(row, col)[2] = 255 - vector_value[2];
            //	if (i < 10) {
            //		std::cout << "(3,3,0),(3,3,1),(3,3,2) = " << vector_value << std::endl;
            //		i++;
            //	}
            //	else
            //		break;
            //}
        }
    }
time0 = ((double)getTickCount() - time0) / getTickFrequency();
std::cout << "\t使用at的运行时间为： " << time0 << "秒" << std::endl;  //输出运行时间=0.0330268秒
```



#### 2.4.2 使用ptr访问

​	针对多通道，ptr模板函数需要指定类型，返回的是指定行的数组指针

```c++
for (int row = 0; row < height; row++) 
{
    double time0 = static_cast<double>(getTickCount());
    uchar* current_raw = src.ptr<uchar>(row); // ptr只能访问行,每次行循环的行指针
    for (int col = 0; col < width; col++)
    {
        if (channels == 1) {
            int value = *current_raw; // 这是行指针的首元素
            *current_raw = 255 - value;
            current_raw++; // 行指针++ 访问列元素
        }
        else
        {
            *current_raw++ = 255 - *current_raw; // 使用三次,这是因为行指针是指向3个通道依次向右平铺的数组列
            *current_raw++ = 255 - *current_raw; // 但是数据是交替的BGR，3列代表一个实际的列
            *current_raw++ = 255 - *current_raw;
        }
    }
}
time0 = ((double)getTickCount() - time0) / getTickFrequency();
std::cout << "\t使用ptr的运行时间为： " << time0 << "秒" << std::endl;  //输出运行时间=0.001702秒
imshow("inverse_src", src);
waitKey(0);
```

​	计时函数：

```c++
//getTickCount( )函数返回CPU自某个事件以来走过的时钟周期数
// getTickFrequency()函数返回CPU一秒钟所走的时钟周期数
double time0 = static_cast<double>(getTickCount());
...
time0 = ((double)getTickCount() - time0) / getTickFrequency();
```

#### 2.4.3 使用iterator访问

​	it是一个数组指针，强调是一个指针，数组大小为3，指针解引用后是数组， ---> int (*p)[3]

​	这个数组存放的是三个通道相同坐标位置的元素。

```c++
double time0 = static_cast<double>(getTickCount());
Mat_<Vec3b>::iterator it = src.begin<Vec3b>();  //初始位置的迭代器
Mat_<Vec3b>::iterator itend = src.end<Vec3b>();  //终止位置的迭代器
for (; it != itend; ++it)
    {
    (*it)[0] = 255 - (*it)[0];
    (*it)[1] = 255 - (*it)[1];
    (*it)[2] = 255 - (*it)[2];
    }
time0 = ((double)getTickCount() - time0) / getTickFrequency();
std::cout << "\t使用iterator的运行时间为： " << time0 << "秒" << std::endl;  //输出运行时间=0.02秒
imshow("inverse_src", src);
waitKey(0);
```

### 2.5 图像的算术操作

​	输入参数都是，第一个对象为InputArray，第二个对象也为InputArray，第三个为输出对象OutArray

```c++
void image_arithmetic_operation()
{
	Mat src = imread("D:/VisualStudioItems/apple.jpg", IMREAD_COLOR);//IMREAD_GRAYSCALE
	int channels = src.channels();
	Mat newsrc = src - Scalar(50, 50, 50); // 调整亮度
	Mat msrc,dsrc,ssrc;
	multiply(src, Scalar(0.5), msrc);
	divide(src,Scalar(50, 50, 50) , dsrc);
	subtract(src,Scalar(50,50,50),ssrc);
	imshow("orgin", src);
	imshow("decrease", newsrc);
	imshow("multiply", msrc);
	imshow("subtract", ssrc);
	imshow("divide", dsrc);
	waitKey(0);
	destroyAllWindows();
}
```

### 2.6 图像的掩膜操作

#### 2.6.1 像素范围裁剪

​	裁剪像素的范围，类似于numpy的clip函数

```c++
saturate_cast<uchar>(-100) -> 0 
```

	#### 2.6.2 矩阵掩膜

​	手动实现掩膜方式。

​	注意：以第0行为例,平铺坐标(0,0)(0,1)(0,2)是第0列，以此类推每个通道之间都差3个位置；row应当从第1行开始,col应当从3开始,因为平铺坐标(1,3)(1,4)(1,5)才是坐标系的第1列。

​	另外掩膜操作是从第1行1列开始的，所以在平铺坐标来看，列从3开始，行从1开始。

```c++
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
    Mat im3(src.size(), CV_8UC3, Scalar(0, 0, 255)); // 也可以这样构造,8位无符号3通道，
    // 注意Scalar的构造要与通道数一致
    Mat im4(3,3, CV_8UC1, Scalar(1));
	std::cout << im4 << std::endl;
	Mat im5(3, 3, CV_8UC2, Scalar(1)); // 这样其实隐式的调用了Scalar(1,0)
	std::cout << im5 << std::endl;
	Mat im6(3, 3, CV_8UC2, Scalar(1,2,3));// 仍然隐式调用Scalar(1,2,0),3被舍弃
	std::cout << im6 << std::endl;
	/*           [ a , b , c ]                   [ 0 -1 0  ]
	kernel =     [ d , e , f ]             本例使用[ -1 5 -1 ]
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
		uchar* output = im1.ptr<uchar>(row); // 输出图像的行指针
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

	imshow("output1",im1);

	imshow("input", src);
	waitKey(0);
	destroyAllWindows();

}
```

​	还可以使用函数filter2D使用，参数依次是被滤波图像，输出图像，被滤波图像的深度以及卷积核

```c++
Mat kernel = ( Mat_<float>(3, 3) << 1 , 1 , 1 , 1 , 5, 1 , 1 , 1 , 1 ) ;
Mat im2 = Mat::zeros(src.size(), src.type());
filter2D(src,im2,src.depth(),kernel);
namedWindow("output2", WINDOW_AUTOSIZE);
imshow("output2", im2);
```

### 2.7

