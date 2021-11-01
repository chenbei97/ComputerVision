#include <iostream>
using namespace std;
#include "quote_pointer.h"
/*
<1>设计立方体类求面积和体积 
分别用全局函数和成员函数判断两个立方体是否相等
*/
class Cube
{
    // 1.私有属性 长宽高
private :
    int _Height = 1;
    int _Width = 1;
    int _Length = 1;

    // 2.方法 获取面积和体积
public : 
    int calculateArea() //int length, int width, int height
    {
        return  2 * _Height * _Width + 2 * _Height * _Length + 2 * _Width * _Length;
    }
    int calculateVolume()
    {
        return  _Length * _Width * _Height;
    }
    // 3.外部接口 设置长宽高
public :
    // 高度的读写权限
    void setHeight(int height)
    {
        _Height = height;
    }
    int getHeight()
    {
        return _Height;
    }
    // 宽度的读写权限
    void setWidth(int width)
    {
        _Width = width;
    }
    int getWidth()
    {
        return _Width;
    }
    // 长度的读写权限
    void setLength(int length)
    {
        _Length = length;
    }
    int getLength()
    {
        return _Length;
    }
    // 4.判断两个立方体是否相等
   // 4.1成员函数判断
public :
    bool  isEqual_ByClass(Cube &c) // 只需要传递一个用来和内部的比较即可
    {
        if (_Height == c.getHeight() && _Length == c.getLength() && _Width == c.getWidth())
        {
            return true;
        }
        return false;
    }
    
};
// 4.2全局函数判断
 bool isEqual(Cube &c1, Cube &c2 ) 
     // 引用传递 可以不必再拷贝数据
{
     if (c1.getHeight() == c2.getHeight() && c1.getLength() == c2.getLength() && c1.getWidth() == c2.getWidth())
     {
         return true;
     }
     return false;
 }

 /*
 <2> 点和圆的关系
 */
 // 点类
 //class Point
 //{
 //private :
 //    int  _X = 0;
 //    int _Y = 0;
 //    int   _XY[2];
 //public :
 //    // 设置x,y坐标
 //    void set_X_Y(int x, int y)
 //    {
 //        _X = x;
 //        _Y = y;
 //    }
 //    //int * get_X_Y_Local()
 //    //{
 //    //    int XY[2];
 //    //    XY[0] = _X;
 //    //    XY[1] = _Y;
 //    //    return XY;// 不要返回局部变量 内存被释放
 //    //}
 //    int* get_X_Y_Global()
 //    {
 //        // 不使用局部变量 XY[2] 而在私有属性新定义一个 这样就可以返回其地址
 //        _XY[0] = _X;
 //        _XY[1] = _Y;
 //        return _XY;
 //    }
 //};
 //// 圆类
 //class Circle
 //{
 //private : 
 //    int  _R=1; //半径
 //    Point _Center; // 圆心
 //public :
 //    // 1.设置半径
 //    void setR(int r)
 //    {
 //        _R = r;
 //    }
 //    // 2.获取半径
 //    int getR()
 //    {
 //        return _R;
 //    }
 //    //3.设置圆心
 //    void setCenter(Point center)
 //    {
 //        _Center = center; // 得到一个圆心类作为圆类的私有属性
 //    }
 //    // 4.获取圆心
 //    Point getCenter()
 //    {
 //        return _Center;//这个圆心有许多方法和属性
 //    }
 //    void isInCircle_ByClass(Point & p)
 //    {
 //        // 计算两点距离的平方
 //        int* center = _Center.get_X_Y_Global();
 //        int x_center = *center; 
 //        int y_center = *(center + 1); // 要用指针+1再取地址,不能用 ++*center 这样只是解引用再加1
 //        // 2.得到某个点的坐标 同样在main函数实例化给定
 //        int* p1 = p.get_X_Y_Global();
 //        int x = *p1;
 //        int y = *(p1 + 1);
 //        int distance = pow(x_center - x, 2) + pow(y_center - y, 2);
 //        //cout << "距离平方为 : " << distance << endl;
 //        // 计算半径的平方
 //        int R2 = pow(getR(), 2);
 //       // cout << "半径平方为 : " << R2 << endl;
 //        // 比较
 //        if (R2 == distance)
 //        {
 //            cout << "点在圆上" << endl;
 //        }
 //        else if (R2 < distance)
 //        {
 //            cout << "点在圆外" << endl;
 //        }
 //        else
 //        {
 //            cout << "点在圆内" << endl;
 //        }

 //    }
 //};
// // 全局方法 判断点和圆的关系
// void isInCircle(Circle& c, Point& p)
// {
//     // 计算两点距离的平方
//     //1.得到圆心的坐标 圆心是在main函数实例化给定的
//     // 然后在判断函数中取出来圆心坐标
//     int* center = c.getCenter().get_X_Y_Global();
//     int x_center = *center;
//     int y_center = *(center+1); // 要用指针+1再取地址,不能用 ++*center 这样只是解引用再加1
//     //cout << "\n" <<x_center << endl;
//    // cout << y_center << endl;
//     // 2.得到某个点的坐标 同样在main函数实例化给定
//     int  * p1 =p.get_X_Y_Global(); 
//     int x = *p1;
//     int y =  *(p1+1);
//     int distance = pow(x_center - x, 2) + pow(y_center - y, 2);
//     cout << "距离平方为 : " << distance << endl;
//     // 计算半径的平方
//     int R2 = pow(c.getR(), 2); 
//     cout << "半径平方为 : " << R2 << endl;
//     // 比较
//     if (R2 == distance)
//     {
//         cout << "点在圆上" << endl;
//     }
//     else if (R2 < distance)
//     {
//         cout << "点在圆外" << endl;
//     }
//     else
//     {
//         cout << "点在圆内" << endl;
//     }
//     
// }
// int  example()
////int main() 
//{
//    //Access_Right();
//    Cube c1;
//    c1.setHeight(10);
//    c1.setLength(10);
//    c1.setWidth(10);
//    cout << "长方体的面积为 : " << c1.calculateArea() <<endl;
//    cout << "长方体的体积为 : " << c1.calculateVolume() << endl;
//    
//    Cube c2;
//    c2.setHeight(10);
//    c2.setLength(10);
//    c2.setWidth(10);
//
//    // 全局函数判断是否相等
//    cout <<( isEqual(c1, c2) ? "两个立方体相等" : "两个立方体不相等" )<< endl;
//    // 成员函数判断是否相等
//    cout << (c1.isEqual_ByClass(c2) ? "c2与c1相比两个立方体相等" : "c2与c1相比两个立方体不相等") << endl;
//    cout << (c2.isEqual_ByClass(c1) ? "c1与c2相比两个立方体相等" : "c1与c2相比两个立方体不相等") << endl;
//    
//
//    // 点类
//    Point  p1;
//    p1.set_X_Y(3,4); //设置某个点为(4,5)
//    //int *p = p1.get_X_Y_Local();
//    //cout << "X坐标为 : " << *p <<endl;
//    //cout << "X坐标为 : " << *p << endl; //第二次获取地址就会不同 局部变量被释放
//    //cout << "Y坐标为 : " << *p++<< endl; /指针移动也不能获得
//
//    int* p = p1.get_X_Y_Global();
//    cout << "X坐标为 : " << *p << endl;
//    cout << "Y坐标为 : " << ++*p << endl; // *p++ 表达式的值没有变
//    cout << "指针已经移动 : " <<* p << endl; // 后续不使用p，但是使用要注意p已经发生了改变
//   
//    // 圆类
//    Circle cc;
//    Point p2;
//    p2.set_X_Y(0, 0);
//    cc.setCenter(p2);
//    cc.setR(5);
//    // 全局函数判断
//    //isInCircle(cc, p1);
//    // 局部函数判断
//    cc.isInCircle_ByClass(p1);
//    //system("pause");
//    return 0;
//}