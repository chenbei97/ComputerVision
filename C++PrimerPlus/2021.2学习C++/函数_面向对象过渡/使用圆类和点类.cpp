#include <iostream>
using namespace std;
#include "circle.h"
#include "point.h"
//#include "quote_pointer.h"
void isInCircle(Circle& c, Point& p)
{
    // ������������ƽ��
    //1.�õ�Բ�ĵ����� Բ������main����ʵ����������
    // Ȼ�����жϺ�����ȡ����Բ������
    int* center = c.getCenter().get_X_Y_Global();
    int x_center = *center;
    int y_center = *(center + 1); // Ҫ��ָ��+1��ȡ��ַ,������ ++*center ����ֻ�ǽ������ټ�1
    //cout << "\n" <<x_center << endl;
   // cout << y_center << endl;
    // 2.�õ�ĳ��������� ͬ����main����ʵ��������
    int* p1 = p.get_X_Y_Global();
    int x = *p1;
    int y = *(p1 + 1);
    int distance = pow(x_center - x, 2) + pow(y_center - y, 2);
    cout << "����ƽ��Ϊ : " << distance << endl;
    // ����뾶��ƽ��
    int R2 = pow(c.getR(), 2);
    cout << "�뾶ƽ��Ϊ : " << R2 << endl;
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
int  use_circle_point()
//int main() 

{
    // ����
    Point  p1;
    p1.set_X_Y(3, 4); //����ĳ����Ϊ(4,5)
     // Բ��
    Circle cc;
    Point p2;
    p2.set_X_Y(0, 0);
    cc.setCenter(p2);
    cc.setR(5);
    // ȫ�ֺ����ж�
    isInCircle(cc, p1);
    // �ֲ������ж�
    cc.isInCircle_ByClass(p1); 
    //system("pause");
    return 0;

}