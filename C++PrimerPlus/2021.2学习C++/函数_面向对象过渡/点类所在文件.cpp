#include <iostream>
using namespace std;
#include "point.h"
//面向对象案例.cpp文件必须注释掉那些类的声明 否则提示重复定义
void Point ::set_X_Y(int x, int y) 
{
    _X = x;
    _Y = y;
}

int* Point :: get_X_Y_Global()
{
     
    _XY[0] = _X;
    _XY[1] = _Y;
    return _XY;
}
