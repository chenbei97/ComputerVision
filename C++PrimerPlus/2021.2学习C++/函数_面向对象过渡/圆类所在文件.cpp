#include <iostream>
using namespace std;
#include "circle.h"
//面向对象案例.cpp文件必须注释掉那些类的声明 否则提示重复定义
// 1.设置半径
void Circle :: setR(int r)
{
    _R = r;
}
// 2.获取半径
int  Circle::getR()
{
    return _R;
}
//3.设置圆心
void Circle:: setCenter(Point center)
{
    _Center = center; // 得到一个圆心类作为圆类的私有属性
}
// 4.获取圆心
Point Circle:: getCenter()
{
    return _Center;//这个圆心有许多方法和属性
}
void Circle:: isInCircle_ByClass(Point& p)
{
    // 计算两点距离的平方
    int* center = _Center.get_X_Y_Global();
    int x_center = *center;
    int y_center = *(center + 1); // 要用指针+1再取地址,不能用 ++*center 这样只是解引用再加1
    // 2.得到某个点的坐标 同样在main函数实例化给定
    int* p1 = p.get_X_Y_Global();
    int x = *p1;
    int y = *(p1 + 1);
    int distance = pow(x_center - x, 2) + pow(y_center - y, 2);
    //cout << "距离平方为 : " << distance << endl;
    // 计算半径的平方
    int R2 = pow(getR(), 2);
    // cout << "半径平方为 : " << R2 << endl;
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
