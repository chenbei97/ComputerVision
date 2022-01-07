#pragma once
#ifndef charter7_matrix_
#define charter7_matrix_
#include "charter1_illegalParameterValue.h"
#include "charter7_matrixSizeMismatch.h"
#include "charter7_matrixIndexOutOfBounds.h"
#include "charter7_matrixSizeNotInitialized.h"
using namespace std;
template<class T>
class matrix
{
public:
    matrix(int theRows = 0, int theColumns = 0);
    matrix(const matrix<T>&);
    ~matrix() { delete[] element; }
    int rows() const { return theRows; }
    int cols() const { return theColumns; }
    matrix<T>  transpose() const; // 取决于如何看一维数组
    void t(); // 改变了内存顺序
    
    T& operator()(int , int ) const;
    
    matrix<T>& operator=(const matrix<T>&); // A=B ; 相当于复制构造 this会变
    matrix<T>& operator=(const T&) ; // A = 5 ; 所有元素都是5 this会变
   
    matrix<T> operator+(const T&) const; // B = A+5 
    matrix<T> operator+(const matrix<T>&) const; // C = A+B
    template<class T>
    friend matrix<T> operator+(const T&, const matrix<T>&); // 5+A 
    
    matrix<T> operator-() const; // -A , 没有matrix<T> operator+() const因为没必要就是自己
    matrix<T> operator-(const matrix<T>&) const; // A-B
    matrix<T> operator-(const T&) const ; // A-5
    template<class T>
    friend matrix<T> operator-(const T&, const matrix<T>&); // 5-A
    
    matrix<T> operator*(const matrix<T>&) const;

    matrix<T>& operator+=(const T&); // A+= 5
    matrix<T>& operator++(int); // A++
    matrix<T>& operator-=(const T&);// A-= 5
    matrix<T>& operator--(int); // A--
    matrix<T>& operator*=(const T&);// A*= 5
    matrix<T>& operator /=(const T&);// A/= 5
    

    //friend ostream& operator<<(ostream&, const matrix<T>&); // 直接这样标注友元函数会报错
    // 如果想要使用2个参数,就不应当使用成员函数,但是非成员函数又不能访问类属性,所以使用friend
    // 可以加上template<class T1/T>即可解决,T和T1都可以,或者<<后面直接加上<>也可以,类内实现也可以
    
    // friend ostream& operator<<<>(ostream&, const matrix<T>& ); // 方案①加<>解决 类外实现
    //template<class T>
    // friend ostream& operator<<(ostream&, const matrix<T>&); // 方案②加template<class T>实现,类外实现
    //template<class T>
    //friend ostream& operator<<<>(ostream&, const matrix<T>&); // 方案③组合使用也是可以的
    // 对于①②③非成员函数不能使用const限定符,后面没有const
    friend ostream& operator<<(ostream&out, const matrix<T>&m) //   方案④类内实现 不加<>,如果加了外部测试定义完double后再定义int类型就会出错
    {     
            int k = 0;  // 遍历this->element的索引
            for (int i = 0; i < m.theRows; i++) // 每行 这里m.theRows就体现了可以访问私有成员
            {// 这里依然不能访问this
                for (int j = 0; j < m.theColumns; j++)
                    out << m.element[k++] << "  "; // 每列 这样k++从0开始直到theColumns*theRows-1
                out << endl;
            }
            return out;
    }

    // 说明非类内是友元、非类内非友元和类内的3个函数性质
    // output1和output3都不是类成员函数,但是前者可以访问私有属性theRows或者不可
    // output2是类成员函数,自然可以访问,因为自带this,且实现部分需要说明作用域
    template<class T1> // 使用T也是可以的,实际上会自动覆盖,如果没有此句也会报错
    friend void output1(const matrix<T1>&); 
    void output2();
private:
    int theRows,    // 行数
        theColumns; // 列数
    T* element;     // 行主映射,用于存储矩阵元素
    bool empty() const { return theColumns * theRows == 0; };
};

// 参数构造(i,j)
template<class T>
matrix<T>::matrix(int theRows, int theColumns)
{
    // 参数构造
    if (theRows < 0 || theColumns < 0)
        throw illegalParameterValue("Rows and columns must be >= 0");
    if ((theRows == 0 || theColumns == 0)
        && (theRows != 0 || theColumns != 0))
        throw illegalParameterValue
        // 都不为0或者都为0 因为(m,0)和(n,0)都不能分配内存
        ("Both rows and columns are 0 or neither is zero");

    // create the matrix
    this->theRows = theRows;
    this->theColumns = theColumns;
    this->element = new T[theRows * theColumns];
}

// 复制构造
template<class T>
matrix<T>::matrix(const matrix<T>& m)
{
    theRows = m.theRows;
    theColumns = m.theColumns;
    this->element = new T[theRows * theColumns];

    copy(m.element, // 指向m的存储首地址
        m.element + theRows * theColumns, // 实际上是最后1位的后1个
        this->element);
}

// 索引重载A(i,j)
template<class T>
T&  matrix<T>::operator()(int i, int j) const  // 用于()索引的重载
{   // 返回的是元素的引用,而这个数例如x(1,1)=2.5赋值时候是可以改变原有数据的
    if (this->empty())
    {
        printf("Warning : matrix is empty,it will return nothing. \n");
    }
    else
    {  // 不为空继续判断是否越界
        if (i < 1 || i > theRows
            || j < 1 || j > theColumns) // 行或者列出现越界错误提示越界
            throw matrixIndexOutOfBounds();
    }
    return element[(i - 1) * theColumns + j - 1]; // 二维映射公式为 列数*(i-1)+j-1,因为i,j都是从1开始的所以要-1
}

//  赋值重载 A=B
template<class T>
matrix<T>& matrix<T>::operator=(const matrix<T>& m)
{
    // A = B A没初始化过可以直接相等，A初始化过需要继续判断size是否匹配
    if (! this->empty())
    {
        if (this->theColumns != m.theColumns || this->theRows != m.theRows)
            throw matrixSizeMismatch(); // 防止A=B,两个size不同 
    }
    if (this != &m) // 如果是自己等于自己没必要在执行,等于别人则执行操作
    {
        // 即y=y不会执行,y=w会执行
        delete[] this->element; // ① 需要先析构掉自己原有的,delete最快捷,而不是擦除元素
        // 下方的代码和复制构造完全一样
        theRows = m.theRows;
        theColumns = m.theColumns;
        this->element = new T[theRows * theColumns];
        copy(m.element,
            m.element + theRows * theColumns,
            this->element);
    }
    return *this; // ②需要返回覆盖后的数据 *this为 matrix<T>&类型 且 (*this) = m
}

//  赋值重载 A=5
template<class T>
matrix<T>& matrix<T>::operator=(const T& k) 
{

    if (theColumns <= 0 || theRows <= 0)
        throw matrixSizeNotInitialized();
    for (int i = 0; i < theColumns*theRows; i++)
        this->element[i] = k;
    return *this;
}

//  加法重载 A+5
template<class T>
matrix<T> matrix<T>::operator+(const T& k) const
{
    if (theColumns <= 0 || theRows <= 0)
        throw matrixSizeNotInitialized();
    matrix<T> w(theRows, theColumns);
    for (int i = 0; i < theColumns * theRows; i++)
        w.element[i] = k + this->element[i];
    return w;
}

//  加法重载 A+B
template<class T>
matrix<T> matrix<T>::operator+(const matrix<T>& m) const
{// Return w = (*this) + m.
    if (theRows != m.theRows
        || theColumns != m.theColumns)
        throw matrixSizeMismatch();
    // create result matrix w
    matrix<T> w(theRows, theColumns);
    for (int i = 0; i < theRows * theColumns; i++)
        w.element[i] = element[i] + m.element[i];
    return w;
}

//  加法重载 5+A
template<class T>
matrix<T> operator+(const T& k, const matrix<T>& m)
{
    if (m.theColumns <= 0 || m.theRows <= 0)
        throw matrixSizeNotInitialized();
    matrix<T> w(m.theRows, m.theColumns);
    for (int i = 0; i < m.theColumns * m.theRows; i++)
        w.element[i] = k + m.element[i];
    return w;
}

//  减法重载 -A
template<class T>
matrix<T> matrix<T>::operator-() const
{// Return w = -(*this).
    if (this->theColumns <= 0 || this->theRows <= 0)
        throw matrixSizeNotInitialized();
   // create result matrix w
    matrix<T> w(theRows, theColumns);
    for (int i = 0; i < theRows * theColumns; i++)
        w.element[i] = -element[i];
    return w;
}

//  减法重载 A-B
template<class T>
matrix<T> matrix<T>::operator-(const matrix<T>& m) const
{// Return (*this) - m.
    if (theRows != m.theRows
        || theColumns != m.theColumns)
        throw matrixSizeMismatch();
    // create result matrix w
    matrix<T> w(theRows, theColumns);
    for (int i = 0; i < theRows * theColumns; i++)
        w.element[i] = element[i] - m.element[i];
    return w;
}

//  减法重载 A-5
template<class T>
matrix<T> matrix<T>::operator-(const T&k) const
{
    if (theColumns <= 0 || theRows <= 0)
        throw matrixSizeNotInitialized();
    // create result matrix w
    matrix<T> w(theRows, theColumns);
    for (int i = 0; i < theRows * theColumns; i++)
        w.element[i] = element[i] - k;
    return w;
}

//  减法重载 5-A
template<class T>
matrix<T> operator-(const T& k, const matrix<T>&m)
{
    if (m.theColumns <= 0 || m.theRows <= 0)
        throw matrixSizeNotInitialized();
    matrix<T> w(m.theRows, m.theColumns);
    for (int i = 0; i < m.theColumns * m.theRows; i++)
        w.element[i] = k - m.element[i];
    return w;
}

//  A+=5
template<class T>
matrix<T>& matrix<T>::operator+=(const T& k)
{
    if (this->theColumns <= 0 || this->theRows <= 0)
        throw matrixSizeNotInitialized();
    for (int i = 0; i < theRows * theColumns; i++)
        element[i] += k;
    return *this;
}

// A-=5
template<class T>
matrix<T>& matrix<T>::operator-=(const T& k)
{
    if (this->theColumns <= 0 || this->theRows <= 0)
        throw matrixSizeNotInitialized();
    for (int i = 0; i < theRows * theColumns; i++)
        element[i] -= k;
    return *this;
}

// A*=5
template<class T>
matrix<T>& matrix<T>::operator*=(const T& k)
{
    if (this->theColumns <= 0 || this->theRows <= 0)
        throw matrixSizeNotInitialized();
    for (int i = 0; i < theRows * theColumns; i++)
        element[i] *= k;
    return *this;
}

// A/=5
template<class T>
matrix<T>& matrix<T>::operator/=(const T& k)
{
    if (this->theColumns <= 0 || this->theRows <= 0)
        throw matrixSizeNotInitialized();
    for (int i = 0; i < theRows * theColumns; i++)
        element[i] /= k;
    return *this;
}

// A++
template<class T>
matrix<T>& matrix<T>::operator++(int)
{
    if (this->theColumns <= 0 || this->theRows <= 0)
        throw matrixSizeNotInitialized();
    for (int i = 0; i < theRows * theColumns; i++)
        element[i] ++;
    return *this;
}

// A--
template<class T>
matrix<T>& matrix<T>::operator--(int)
{
    if (this->theColumns <= 0 || this->theRows <= 0)
        throw matrixSizeNotInitialized();
    for (int i = 0; i < theRows * theColumns; i++)
        element[i] --;
    return *this;
}

// 乘法 A*B
template<class T>
matrix<T> matrix<T>::operator*(const matrix<T>& m) const
{// matrix multiply.  Return w = (*this) * m. // 矩阵乘法稍微要注意以下前列数=后行数
    if (theColumns != m.theRows)
        throw matrixSizeMismatch();

    matrix<T> w(theRows, m.theColumns);  // result matrix 返回的矩阵是前行数*后列数

    // 假设a=5×4 和b=4×3的结果为c=5×3 
    int arow = 0, bcol = 0, cw = 0; // 3个游标
    for (int i = 1; i <= theRows; i++) // i =1,2,3,4,5
    {
        for (int j = 1; j <= m.theColumns; j++) // j = 1,2,3
        { 
            T sum = element[arow] * m.element[bcol];  // 相当于a[1,1]*b[1,1]
            for (int k = 2; k <= theColumns; k++) // k=2,3,4 不作为任何索引,就是计算几次
                // 由于首元素已经计算,只需要运行theColumns-1次,那么k应该从2开始
            {
                arow++;  // a[1,1]=>a[1,2],每行的下一个元素移动1个位置即可
                bcol += m.theColumns;  // b[1,j]=>b[2,j]=>b[3,j]=>b[4,j] 同列移动需要移动4个单位,且bcol必须是0开始才能到4
                sum += element[arow] * m.element[bcol]; 
                // a[i,1]*b[1,j]+{a[i,2]*b[2,j]+a[i,3]*b[3,j]+a[i,4]*b[4,j]},{}内是k=2,3,4运行3次
            }
            w.element[cw++] = sum;  // c[i][j]从cw=0开始的直到 theRows*m.theColumns结束,存储好存
            // 计算当前行与每个列的和,所以arow总是返回当前行首元素位置
            // 列总是到下1列首元素,列应该是1,2,3列,但是bcol对应的是0,1,2,用j表示,j从1开始的
            arow -= theColumns - 1; // 每个m的列遍历,arow要后退回当前行的首元素处
            bcol = j; // 每列的首元素,即总是b[1,1],b[1,2],b[1,3],bcol在element恰好对应的就是0,1,2索引
            // 而b[1,1]->b[4,1]在前边已经执行过(相当于bcol=0的情况),下一步回到b[1,2]->b[4,2],再回到b[1,3]->b[4,3]
            // 也就是bcol只需要再取1,2即可,恰好是j
            // 0 b[1,1]->b[1,2]->b[1,3]->
            //    b[2,1]->b[2,2]->b[2,3]->
            //    b[3,1]->b[3,2]->b[3,3]->
            //    b[4,1]->b[4,2]->b[4,3]
        }

        // 每次行更新的时候,arow要移动到下一行的首元素
        arow += theColumns; // a[1,1]=>a[2,1],要+4个地址,所以在列遍历中总是后退theColumns - 1个元素
        bcol = 0; // i更新后必须为0,bcol += m.theColumns才能加到指定的列位置
    }
    return w;
}

// 转置 A^T 不会改变实际的内存排列
template<class T>
matrix<T> matrix<T>::transpose() const
{// 此方法并不改变内存的排序只是以列主映射的位置返回
    // 转置要初始化过
    if (this->theColumns <= 0 || this->theRows <= 0)
        throw matrixSizeNotInitialized();
    matrix<T> w(theColumns, theRows);
    /*
        举例分析转置在一维数组是怎么实现的
        内存位置的元素 => 0,1,2,3,4,5,6,7,8,9,10,11
        行主映射：
        0, 1, 2, 3    A(i,j)=element[theColumns*(i-1)+j-1] = element[4i+j-5]
        4, 5, [6], 7    例如A(2,3)=element[4+2]=6
        8, 9, 10, 11 
        列主映射：
        0, 3, 6, 9    A(i,j)=element[theRows*(j-1)+i-1] = element[i+3j-4]
        1, 4, 7, 10  例如A(3,3) = element[6+2]=8
        2, 5, [8], 11
        转置后
        0, 4, 8       有点类似于列主映射,但是行数变为列数
        1, 5, 9      A.T(i,j)=element[theColumns*(j-1)+i-1] = element[i+4j-5]
        2, 6, 10   例如A.T(4,3) = element 
        3, 7, [11]
    */
    for (int i = 1; i <= theColumns; i++)
        for (int j = 1; j <= theRows; j++)
            w(i,j) = element[theColumns*(j-1)+i-1];
    return w;
}

// 转置：改变内存排序
template<class T>
void matrix<T> :: t()
{
    if (this->theColumns <= 0 || this->theRows <= 0)
        throw matrixSizeNotInitialized();
    /*
        接上transpose的分析
        内存 : 0,1,2,3,  4,5,6,7,   8,9,10,11  3×4
        转置后:0,4,8,  1,5,9,  2,6,10,  3,7,11 4×3
        每个行总是相差theColumns个元素
        关键在于行的开头是原来的第1列位置
    */
    T* b = new T  [theColumns*theRows];
    int k = 0;
    for (int i = 0; i <= theRows; i++)// i = 0,1,2,3
    {
        for (int j = i; j < theColumns*theRows; j += theColumns) 
        {
            // j =0,4,8<12 or j =1,5,9<12 or j=2,6,10 <12 or j = 3,7,11<12
            //cout << "element[" << j << "] = " << element[j] << endl;
            b[k++] = element[j];  // 按这样的方式取出来
        }
    }
    k = 0;
    for (; k < theColumns * theColumns; k++)
        element[k] = b[k];
    int t = theColumns;
    theColumns = theRows;
    theRows = t; // 转置后行与列要交换
    b = NULL; // 不要delete b会自动释放,只需要置空避免野指针即可
}

// 这个类内实现存在一些问题，外部测试使用double类型的matrix时就不能使用cout<<x<<endl;
//ostream& operator<<(ostream& out, const matrix<int>& m)
//{
//    int k = 0;  // 遍历this->element的索引
//    for (int i = 0; i < m.theRows; i++) // 每行 =>这里m.theRows就体现了可以访问私有成员
//    { // 但是不能显示访问this
//        for (int j = 0; j < m.theColumns; j++)
//            out << m.element[k++] << "  "; // 每列 这样k++从0开始直到theColumns*theRows-1
//        out << endl;
//    }
//    return out;
//}

// 方案①或者②或者③ 类外实现
//template<class T> // 论方案①还是②还是③这里实现部分必须加
//ostream& operator<<<>(ostream& out, const matrix<T>& m) // <<在有上边的前提下
//// 使用方案①和③时为了避免没有函数定义的提示最好上边使用<<<>下边也使用<<<>,但是不加也确实不会出错
//// 使用方案②时 同理 上边使用<<,下边也最好使用<< 但是不这样做也是不会出错的
//{
//    int k = 0;  // 遍历this->element的索引
//    for (int i = 0; i < m.theRows; i++) // 每行 =>这里m.theRows就体现了可以访问私有成员
//    {// 但是不能显示访问this
//        for (int j = 0; j < m.theColumns; j++)
//            out << m.element[k++] << "  "; // 每列 这样k++从0开始直到theColumns*theRows-1
//        out << endl;
//    }
//    return out;
//}
template<class T>
void output3(const matrix<T>& m);
 //output1和output3都不是类成员函数,但是前者可以访问私有属性theRows或者不可
 //output2是类成员函数,自然可以访问,因为自带this,且实现部分需要说明作用域
template<class T1> // 使用T1和T其实都可以,但是声明中也必须有此条语句否则报链接错误
void output1(const matrix<T1>& m)
{
    int idx = 0;
    for (int i = 0; i < m.theRows; i++) // 可以访问私有属性 不通过this
    {
        for (int j = 0; j < m.theColumns; j++)
        {
            cout << m.element[idx++] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}
template<class T>
void matrix<T>::output2() // 类成员函数: 需要说明作用域
{
    int idx = 0;
    for (int i = 0; i < this->theRows; i++) // 可以访问私有属性 通过this
    {
        for (int j = 0; j < this->theColumns; j++)
        {
            cout << this->element[idx++] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}
template<class T>
void output3(const matrix<T>&m) //不是类成员函数
{
    int idx = 0;
    for (int i = 1; i <= m.rows(); i++) // 不可以访问私有属性 只能间接访问
    {
        for (int j = 1; j <= m.cols(); j++)
        {
            cout << m(i,j) << "  "; // theRows,theColumns,element都不能访问
        }
        cout << endl;
    }
    cout << endl;
}
#endif // !charter7_matrix_
