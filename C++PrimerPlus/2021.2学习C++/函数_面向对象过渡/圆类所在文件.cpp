#include <iostream>
using namespace std;
#include "circle.h"
//���������.cpp�ļ�����ע�͵���Щ������� ������ʾ�ظ�����
// 1.���ð뾶
void Circle :: setR(int r)
{
    _R = r;
}
// 2.��ȡ�뾶
int  Circle::getR()
{
    return _R;
}
//3.����Բ��
void Circle:: setCenter(Point center)
{
    _Center = center; // �õ�һ��Բ������ΪԲ���˽������
}
// 4.��ȡԲ��
Point Circle:: getCenter()
{
    return _Center;//���Բ������෽��������
}
void Circle:: isInCircle_ByClass(Point& p)
{
    // ������������ƽ��
    int* center = _Center.get_X_Y_Global();
    int x_center = *center;
    int y_center = *(center + 1); // Ҫ��ָ��+1��ȡ��ַ,������ ++*center ����ֻ�ǽ������ټ�1
    // 2.�õ�ĳ��������� ͬ����main����ʵ��������
    int* p1 = p.get_X_Y_Global();
    int x = *p1;
    int y = *(p1 + 1);
    int distance = pow(x_center - x, 2) + pow(y_center - y, 2);
    //cout << "����ƽ��Ϊ : " << distance << endl;
    // ����뾶��ƽ��
    int R2 = pow(getR(), 2);
    // cout << "�뾶ƽ��Ϊ : " << R2 << endl;
        // �Ƚ�
    if (R2 == distance)
    {
        cout << "����Բ��" << endl;
    }
    else if (R2 < distance)
    {
        cout << "����Բ��" << endl;
    }
    else
    {
        cout << "����Բ��" << endl;
    }

}
