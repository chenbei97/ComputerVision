#include <iostream>
using namespace std;
#include "circle.h"
#include "point.h"
//#include "quote_pointer.h"
void isInCircle(Circle& c, Point& p)
{
    // 计算两点距离的平方
    //1.得到圆心的坐标 圆心是在main函数实例化给定的
    // 然后在判断函数中取出来圆心坐标
    int* center = c.getCenter().get_X_Y_Global();
    int x_center = *center;
    int y_center = *(center + 1); // 要用指针+1再取地址,不能用 ++*center 这样只是解引用再加1
    //cout << "\n" <<x_center << endl;
   // cout << y_center << endl;
    // 2.得到某个点的坐标 同样在main函数实例化给定
    int* p1 = p.get_X_Y_Global();
    int x = *p1;
    int y = *(p1 + 1);
    int distance = pow(x_center - x, 2) + pow(y_center - y, 2);
    cout << "距离平方为 : " << distance << endl;
    // 计算半径的平方
    int R2 = pow(c.getR(), 2);
    cout << "半径平方为 : " << R2 << endl;
    // 比较
    if (R2 == distance)
    {
        cout << "点在圆上" << endl;
    }
    else if (R2 < distance)
    {
        cout << "点在圆外" << endl;
    }
    else
    {
        cout << "点在圆内" << endl;
    }

}
int  use_circle_point()
//int main() 

{
    // 点类
    Point  p1;
    p1.set_X_Y(3, 4); //设置某个点为(4,5)
     // 圆类
    Circle cc;
    Point p2;
    p2.set_X_Y(0, 0);
    cc.setCenter(p2);
    cc.setR(5);
    // 全局函数判断
    isInCircle(cc, p1);
    // 局部函数判断
    cc.isInCircle_ByClass(p1); 
    //system("pause");
    return 0;

}