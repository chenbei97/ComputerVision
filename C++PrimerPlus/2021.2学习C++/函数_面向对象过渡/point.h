#pragma once
// 也可以头文件直接写类的声明 类的体在其他函数中
class Point
{
private:
    int  _X = 0;
    int _Y = 0;
    int   _XY[2];
public:
    // 设置x,y坐标
    void set_X_Y(int x, int y);
    int* get_X_Y_Global();
};
