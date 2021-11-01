#pragma once
#include "point.h"
class Circle
{
private:
    int  _R = 1; //半径
    Point _Center; // 圆心
public:
    // 1.设置半径
    void setR(int r);
    // 2.获取半径
    int getR();
    //3.设置圆心
    void setCenter(Point center);
   
    // 4.获取圆心
    Point getCenter();
    void isInCircle_ByClass(Point& p);
};
