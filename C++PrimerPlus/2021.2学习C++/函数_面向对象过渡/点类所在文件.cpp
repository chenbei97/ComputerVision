#include <iostream>
using namespace std;
#include "point.h"
//���������.cpp�ļ�����ע�͵���Щ������� ������ʾ�ظ�����
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
