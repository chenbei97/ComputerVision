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
    ~matrix() { if (element != NULL) element = NULL; delete[] element; }
    int rows() const { return theRows; }
    int cols() const { return theColumns; }
    matrix<T>  transpose() const; // ȡ������ο�һά����
    void t(); // �ı����ڴ�˳��
    
    T& operator()(int , int ) const;
    
    matrix<T>& operator=(const matrix<T>&); // A=B ; �൱�ڸ��ƹ��� this���
    matrix<T>& operator=(const T&) ; // A = 5 ; ����Ԫ�ض���5 this���
   
    matrix<T> operator+(const T&) const; // B = A+5 
    matrix<T> operator+(const matrix<T>&) const; // C = A+B
    template<class T>
    friend matrix<T> operator+(const T&, const matrix<T>&); // 5+A 
    
    matrix<T> operator-() const; // -A , û��matrix<T> operator+() const��Ϊû��Ҫ�����Լ�
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
    

    //friend ostream& operator<<(ostream&, const matrix<T>&); // ֱ��������ע��Ԫ�����ᱨ��
    // �����Ҫʹ��2������,�Ͳ�Ӧ��ʹ�ó�Ա����,���Ƿǳ�Ա�����ֲ��ܷ���������,����ʹ��friend
    // ���Լ���template<class T1/T>���ɽ��,T��T1������,����<<����ֱ�Ӽ���<>Ҳ����,����ʵ��Ҳ����
    
    // friend ostream& operator<<<>(ostream&, const matrix<T>& ); // �����ټ�<>��� ����ʵ��
    //template<class T>
    // friend ostream& operator<<(ostream&, const matrix<T>&); // �����ڼ�template<class T>ʵ��,����ʵ��
    //template<class T>
    //friend ostream& operator<<<>(ostream&, const matrix<T>&); // ���������ʹ��Ҳ�ǿ��Ե�
    // ���ڢ٢ڢ۷ǳ�Ա��������ʹ��const�޶���,����û��const
    friend ostream& operator<<(ostream&out, const matrix<T>&m) //   ����������ʵ�� ����<>,��������ⲿ���Զ�����double���ٶ���int���;ͻ����
    {     
            int k = 0;  // ����this->element������
            for (int i = 0; i < m.theRows; i++) // ÿ�� ����m.theRows�������˿��Է���˽�г�Ա
            {// ������Ȼ���ܷ���this
                for (int j = 0; j < m.theColumns; j++)
                    out << m.element[k++] << "  "; // ÿ�� ����k++��0��ʼֱ��theColumns*theRows-1
                out << endl;
            }
            return out;
    }

    // ˵������������Ԫ�������ڷ���Ԫ�����ڵ�3����������
    // output1��output3���������Ա����,����ǰ�߿��Է���˽������theRows���߲���
    // output2�����Ա����,��Ȼ���Է���,��Ϊ�Դ�this,��ʵ�ֲ�����Ҫ˵��������
    template<class T1> // ʹ��TҲ�ǿ��Ե�,ʵ���ϻ��Զ�����,���û�д˾�Ҳ�ᱨ��
    friend void output1(const matrix<T1>&); 
    void output2();
private:
    int theRows,    // ����
        theColumns; // ����
    T* element;     // ����ӳ��,���ڴ洢����Ԫ��
    bool empty() const { return theColumns * theRows == 0; };
};

// ��������(i,j)
template<class T>
matrix<T>::matrix(int theRows, int theColumns)
{
    // ��������
    if (theRows < 0 || theColumns < 0)
        throw illegalParameterValue("Rows and columns must be >= 0");
    if ((theRows == 0 || theColumns == 0)
        && (theRows != 0 || theColumns != 0))
        throw illegalParameterValue
        // ����Ϊ0���߶�Ϊ0 ��Ϊ(m,0)��(n,0)�����ܷ����ڴ�
        ("Both rows and columns are 0 or neither is zero");

    // create the matrix
    this->theRows = theRows;
    this->theColumns = theColumns;
    this->element = new T[theRows * theColumns];
}

// ���ƹ���
template<class T>
matrix<T>::matrix(const matrix<T>& m)
{
    theRows = m.theRows;
    theColumns = m.theColumns;
    this->element = new T[theRows * theColumns];

    copy(m.element, // ָ��m�Ĵ洢�׵�ַ
        m.element + theRows * theColumns, // ʵ���������1λ�ĺ�1��
        this->element);
}

// ��������A(i,j)
template<class T>
T&  matrix<T>::operator()(int i, int j) const  // ����()����������
{   // ���ص���Ԫ�ص�����,�����������x(1,1)=2.5��ֵʱ���ǿ��Ըı�ԭ�����ݵ�
    if (this->empty())
    {
        printf("Warning : matrix is empty,it will return nothing. \n");
    }
    else
    {  // ��Ϊ�ռ����ж��Ƿ�Խ��
        if (i < 1 || i > theRows
            || j < 1 || j > theColumns) // �л����г���Խ�������ʾԽ��
            throw matrixIndexOutOfBounds();
    }
    return element[(i - 1) * theColumns + j - 1]; // ��άӳ�乫ʽΪ ����*(i-1)+j-1,��Ϊi,j���Ǵ�1��ʼ������Ҫ-1
}

//  ��ֵ���� A=B
template<class T>
matrix<T>& matrix<T>::operator=(const matrix<T>& m)
{
    // A = B Aû��ʼ��������ֱ����ȣ�A��ʼ������Ҫ�����ж�size�Ƿ�ƥ��
    if (! this->empty())
    {
        if (this->theColumns != m.theColumns || this->theRows != m.theRows)
            throw matrixSizeMismatch(); // ��ֹA=B,����size��ͬ 
    }
    if (this != &m) // ������Լ������Լ�û��Ҫ��ִ��,���ڱ�����ִ�в���
    {
        // ��y=y����ִ��,y=w��ִ��
        delete[] this->element; // �� ��Ҫ���������Լ�ԭ�е�,delete����,�����ǲ���Ԫ��
        // �·��Ĵ���͸��ƹ�����ȫһ��
        theRows = m.theRows;
        theColumns = m.theColumns;
        this->element = new T[theRows * theColumns];
        copy(m.element,
            m.element + theRows * theColumns,
            this->element);
    }
    return *this; // ����Ҫ���ظ��Ǻ������ *thisΪ matrix<T>&���� �� (*this) = m
}

//  ��ֵ���� A=5
template<class T>
matrix<T>& matrix<T>::operator=(const T& k) 
{

    if (theColumns <= 0 || theRows <= 0)
        throw matrixSizeNotInitialized();
    for (int i = 0; i < theColumns*theRows; i++)
        this->element[i] = k;
    return *this;
}

//  �ӷ����� A+5
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

//  �ӷ����� A+B
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

//  �ӷ����� 5+A
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

//  �������� -A
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

//  �������� A-B
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

//  �������� A-5
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

//  �������� 5-A
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

// �˷� A*B
template<class T>
matrix<T> matrix<T>::operator*(const matrix<T>& m) const
{// matrix multiply.  Return w = (*this) * m. // ����˷���΢Ҫע������ǰ����=������
    if (theColumns != m.theRows)
        throw matrixSizeMismatch();

    matrix<T> w(theRows, m.theColumns);  // result matrix ���صľ�����ǰ����*������

    // ����a=5��4 ��b=4��3�Ľ��Ϊc=5��3 
    int arow = 0, bcol = 0, cw = 0; // 3���α�
    for (int i = 1; i <= theRows; i++) // i =1,2,3,4,5
    {
        for (int j = 1; j <= m.theColumns; j++) // j = 1,2,3
        { 
            T sum = element[arow] * m.element[bcol];  // �൱��a[1,1]*b[1,1]
            for (int k = 2; k <= theColumns; k++) // k=2,3,4 ����Ϊ�κ�����,���Ǽ��㼸��
                // ������Ԫ���Ѿ�����,ֻ��Ҫ����theColumns-1��,��ôkӦ�ô�2��ʼ
            {
                arow++;  // a[1,1]=>a[1,2],ÿ�е���һ��Ԫ���ƶ�1��λ�ü���
                bcol += m.theColumns;  // b[1,j]=>b[2,j]=>b[3,j]=>b[4,j] ͬ���ƶ���Ҫ�ƶ�4����λ,��bcol������0��ʼ���ܵ�4
                sum += element[arow] * m.element[bcol]; 
                // a[i,1]*b[1,j]+{a[i,2]*b[2,j]+a[i,3]*b[3,j]+a[i,4]*b[4,j]},{}����k=2,3,4����3��
            }
            w.element[cw++] = sum;  // c[i][j]��cw=0��ʼ��ֱ�� theRows*m.theColumns����,�洢�ô�
            // ���㵱ǰ����ÿ���еĺ�,����arow���Ƿ��ص�ǰ����Ԫ��λ��
            // �����ǵ���1����Ԫ��,��Ӧ����1,2,3��,����bcol��Ӧ����0,1,2,��j��ʾ,j��1��ʼ��
            arow -= theColumns - 1; // ÿ��m���б���,arowҪ���˻ص�ǰ�е���Ԫ�ش�
            bcol = j; // ÿ�е���Ԫ��,������b[1,1],b[1,2],b[1,3],bcol��elementǡ�ö�Ӧ�ľ���0,1,2����
            // ��b[1,1]->b[4,1]��ǰ���Ѿ�ִ�й�(�൱��bcol=0�����),��һ���ص�b[1,2]->b[4,2],�ٻص�b[1,3]->b[4,3]
            // Ҳ����bcolֻ��Ҫ��ȡ1,2����,ǡ����j
            // 0 b[1,1]->b[1,2]->b[1,3]->
            //    b[2,1]->b[2,2]->b[2,3]->
            //    b[3,1]->b[3,2]->b[3,3]->
            //    b[4,1]->b[4,2]->b[4,3]
        }

        // ÿ���и��µ�ʱ��,arowҪ�ƶ�����һ�е���Ԫ��
        arow += theColumns; // a[1,1]=>a[2,1],Ҫ+4����ַ,�������б��������Ǻ���theColumns - 1��Ԫ��
        bcol = 0; // i���º����Ϊ0,bcol += m.theColumns���ܼӵ�ָ������λ��
    }
    return w;
}

// ת�� A^T ����ı�ʵ�ʵ��ڴ�����
template<class T>
matrix<T> matrix<T>::transpose() const
{// �˷��������ı��ڴ������ֻ��������ӳ���λ�÷���
    // ת��Ҫ��ʼ����
    if (this->theColumns <= 0 || this->theRows <= 0)
        throw matrixSizeNotInitialized();
    matrix<T> w(theColumns, theRows);
    /*
        ��������ת����һά��������ôʵ�ֵ�
        �ڴ�λ�õ�Ԫ�� => 0,1,2,3,4,5,6,7,8,9,10,11
        ����ӳ�䣺
        0, 1, 2, 3    A(i,j)=element[theColumns*(i-1)+j-1] = element[4i+j-5]
        4, 5, [6], 7    ����A(2,3)=element[4+2]=6
        8, 9, 10, 11 
        ����ӳ�䣺
        0, 3, 6, 9    A(i,j)=element[theRows*(j-1)+i-1] = element[i+3j-4]
        1, 4, 7, 10  ����A(3,3) = element[6+2]=8
        2, 5, [8], 11
        ת�ú�
        0, 4, 8       �е�����������ӳ��,����������Ϊ����
        1, 5, 9      A.T(i,j)=element[theColumns*(j-1)+i-1] = element[i+4j-5]
        2, 6, 10   ����A.T(4,3) = element 
        3, 7, [11]
    */
    for (int i = 1; i <= theColumns; i++)
        for (int j = 1; j <= theRows; j++)
            w(i,j) = element[theColumns*(j-1)+i-1];
    return w;
}

// ת�ã��ı��ڴ�����
template<class T>
void matrix<T> :: t()
{
    if (this->theColumns <= 0 || this->theRows <= 0)
        throw matrixSizeNotInitialized();
    /*
        ����transpose�ķ���
        �ڴ� : 0,1,2,3,  4,5,6,7,   8,9,10,11  3��4
        ת�ú�:0,4,8,  1,5,9,  2,6,10,  3,7,11 4��3
        ÿ�����������theColumns��Ԫ��
        �ؼ������еĿ�ͷ��ԭ���ĵ�1��λ��
    */
    T* b = new T  [theColumns*theRows];
    int k = 0;
    for (int i = 0; i <= theRows; i++)// i = 0,1,2,3
    {
        for (int j = i; j < theColumns*theRows; j += theColumns) 
        {
            // j =0,4,8<12 or j =1,5,9<12 or j=2,6,10 <12 or j = 3,7,11<12
            //cout << "element[" << j << "] = " << element[j] << endl;
            b[k++] = element[j];  // �������ķ�ʽȡ����
        }
    }
    k = 0;
    for (; k < theColumns * theColumns; k++)
        element[k] = b[k];
    int t = theColumns;
    theColumns = theRows;
    theRows = t; // ת�ú�������Ҫ����
    b = NULL; // ��Ҫdelete b���Զ��ͷ�,ֻ��Ҫ�ÿձ���Ұָ�뼴��
}

// �������ʵ�ִ���һЩ���⣬�ⲿ����ʹ��double���͵�matrixʱ�Ͳ���ʹ��cout<<x<<endl;
//ostream& operator<<(ostream& out, const matrix<int>& m)
//{
//    int k = 0;  // ����this->element������
//    for (int i = 0; i < m.theRows; i++) // ÿ�� =>����m.theRows�������˿��Է���˽�г�Ա
//    { // ���ǲ�����ʾ����this
//        for (int j = 0; j < m.theColumns; j++)
//            out << m.element[k++] << "  "; // ÿ�� ����k++��0��ʼֱ��theColumns*theRows-1
//        out << endl;
//    }
//    return out;
//}

// �����ٻ��ߢڻ��ߢ� ����ʵ��
//template<class T> // �۷����ٻ��Ǣڻ��Ǣ�����ʵ�ֲ��ֱ����
//ostream& operator<<<>(ostream& out, const matrix<T>& m) // <<�����ϱߵ�ǰ����
//// ʹ�÷����ٺ͢�ʱΪ�˱���û�к����������ʾ����ϱ�ʹ��<<<>�±�Ҳʹ��<<<>,���ǲ���Ҳȷʵ�������
//// ʹ�÷�����ʱ ͬ�� �ϱ�ʹ��<<,�±�Ҳ���ʹ��<< ���ǲ�������Ҳ�ǲ�������
//{
//    int k = 0;  // ����this->element������
//    for (int i = 0; i < m.theRows; i++) // ÿ�� =>����m.theRows�������˿��Է���˽�г�Ա
//    {// ���ǲ�����ʾ����this
//        for (int j = 0; j < m.theColumns; j++)
//            out << m.element[k++] << "  "; // ÿ�� ����k++��0��ʼֱ��theColumns*theRows-1
//        out << endl;
//    }
//    return out;
//}
template<class T>
void output3(const matrix<T>& m);
 //output1��output3���������Ա����,����ǰ�߿��Է���˽������theRows���߲���
 //output2�����Ա����,��Ȼ���Է���,��Ϊ�Դ�this,��ʵ�ֲ�����Ҫ˵��������
template<class T1> // ʹ��T1��T��ʵ������,����������Ҳ�����д������������Ӵ���
void output1(const matrix<T1>& m)
{
    int idx = 0;
    for (int i = 0; i < m.theRows; i++) // ���Է���˽������ ��ͨ��this
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
void matrix<T>::output2() // ���Ա����: ��Ҫ˵��������
{
    int idx = 0;
    for (int i = 0; i < this->theRows; i++) // ���Է���˽������ ͨ��this
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
void output3(const matrix<T>&m) //�������Ա����
{
    int idx = 0;
    for (int i = 1; i <= m.rows(); i++) // �����Է���˽������ ֻ�ܼ�ӷ���
    {
        for (int j = 1; j <= m.cols(); j++)
        {
            cout << m(i,j) << "  "; // theRows,theColumns,element�����ܷ���
        }
        cout << endl;
    }
    cout << endl;
}
#endif // !charter7_matrix_
