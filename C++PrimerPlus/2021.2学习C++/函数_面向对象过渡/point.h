#pragma once
// Ҳ����ͷ�ļ�ֱ��д������� �����������������
class Point
{
private:
    int  _X = 0;
    int _Y = 0;
    int   _XY[2];
public:
    // ����x,y����
    void set_X_Y(int x, int y);
    int* get_X_Y_Global();
};
