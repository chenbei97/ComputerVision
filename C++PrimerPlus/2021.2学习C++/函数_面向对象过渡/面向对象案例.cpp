#include <iostream>
using namespace std;
#include "quote_pointer.h"
/*
<1>��������������������� 
�ֱ���ȫ�ֺ����ͳ�Ա�����ж������������Ƿ����
*/
class Cube
{
    // 1.˽������ �����
private :
    int _Height = 1;
    int _Width = 1;
    int _Length = 1;

    // 2.���� ��ȡ��������
public : 
    int calculateArea() //int length, int width, int height
    {
        return  2 * _Height * _Width + 2 * _Height * _Length + 2 * _Width * _Length;
    }
    int calculateVolume()
    {
        return  _Length * _Width * _Height;
    }
    // 3.�ⲿ�ӿ� ���ó����
public :
    // �߶ȵĶ�дȨ��
    void setHeight(int height)
    {
        _Height = height;
    }
    int getHeight()
    {
        return _Height;
    }
    // ��ȵĶ�дȨ��
    void setWidth(int width)
    {
        _Width = width;
    }
    int getWidth()
    {
        return _Width;
    }
    // ���ȵĶ�дȨ��
    void setLength(int length)
    {
        _Length = length;
    }
    int getLength()
    {
        return _Length;
    }
    // 4.�ж������������Ƿ����
   // 4.1��Ա�����ж�
public :
    bool  isEqual_ByClass(Cube &c) // ֻ��Ҫ����һ���������ڲ��ıȽϼ���
    {
        if (_Height == c.getHeight() && _Length == c.getLength() && _Width == c.getWidth())
        {
            return true;
        }
        return false;
    }
    
};
// 4.2ȫ�ֺ����ж�
 bool isEqual(Cube &c1, Cube &c2 ) 
     // ���ô��� ���Բ����ٿ�������
{
     if (c1.getHeight() == c2.getHeight() && c1.getLength() == c2.getLength() && c1.getWidth() == c2.getWidth())
     {
         return true;
     }
     return false;
 }

 /*
 <2> ���Բ�Ĺ�ϵ
 */
 // ����
 //class Point
 //{
 //private :
 //    int  _X = 0;
 //    int _Y = 0;
 //    int   _XY[2];
 //public :
 //    // ����x,y����
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
 //    //    return XY;// ��Ҫ���ؾֲ����� �ڴ汻�ͷ�
 //    //}
 //    int* get_X_Y_Global()
 //    {
 //        // ��ʹ�þֲ����� XY[2] ����˽�������¶���һ�� �����Ϳ��Է������ַ
 //        _XY[0] = _X;
 //        _XY[1] = _Y;
 //        return _XY;
 //    }
 //};
 //// Բ��
 //class Circle
 //{
 //private : 
 //    int  _R=1; //�뾶
 //    Point _Center; // Բ��
 //public :
 //    // 1.���ð뾶
 //    void setR(int r)
 //    {
 //        _R = r;
 //    }
 //    // 2.��ȡ�뾶
 //    int getR()
 //    {
 //        return _R;
 //    }
 //    //3.����Բ��
 //    void setCenter(Point center)
 //    {
 //        _Center = center; // �õ�һ��Բ������ΪԲ���˽������
 //    }
 //    // 4.��ȡԲ��
 //    Point getCenter()
 //    {
 //        return _Center;//���Բ������෽��������
 //    }
 //    void isInCircle_ByClass(Point & p)
 //    {
 //        // ������������ƽ��
 //        int* center = _Center.get_X_Y_Global();
 //        int x_center = *center; 
 //        int y_center = *(center + 1); // Ҫ��ָ��+1��ȡ��ַ,������ ++*center ����ֻ�ǽ������ټ�1
 //        // 2.�õ�ĳ��������� ͬ����main����ʵ��������
 //        int* p1 = p.get_X_Y_Global();
 //        int x = *p1;
 //        int y = *(p1 + 1);
 //        int distance = pow(x_center - x, 2) + pow(y_center - y, 2);
 //        //cout << "����ƽ��Ϊ : " << distance << endl;
 //        // ����뾶��ƽ��
 //        int R2 = pow(getR(), 2);
 //       // cout << "�뾶ƽ��Ϊ : " << R2 << endl;
 //        // �Ƚ�
 //        if (R2 == distance)
 //        {
 //            cout << "����Բ��" << endl;
 //        }
 //        else if (R2 < distance)
 //        {
 //            cout << "����Բ��" << endl;
 //        }
 //        else
 //        {
 //            cout << "����Բ��" << endl;
 //        }

 //    }
 //};
// // ȫ�ַ��� �жϵ��Բ�Ĺ�ϵ
// void isInCircle(Circle& c, Point& p)
// {
//     // ������������ƽ��
//     //1.�õ�Բ�ĵ����� Բ������main����ʵ����������
//     // Ȼ�����жϺ�����ȡ����Բ������
//     int* center = c.getCenter().get_X_Y_Global();
//     int x_center = *center;
//     int y_center = *(center+1); // Ҫ��ָ��+1��ȡ��ַ,������ ++*center ����ֻ�ǽ������ټ�1
//     //cout << "\n" <<x_center << endl;
//    // cout << y_center << endl;
//     // 2.�õ�ĳ��������� ͬ����main����ʵ��������
//     int  * p1 =p.get_X_Y_Global(); 
//     int x = *p1;
//     int y =  *(p1+1);
//     int distance = pow(x_center - x, 2) + pow(y_center - y, 2);
//     cout << "����ƽ��Ϊ : " << distance << endl;
//     // ����뾶��ƽ��
//     int R2 = pow(c.getR(), 2); 
//     cout << "�뾶ƽ��Ϊ : " << R2 << endl;
//     // �Ƚ�
//     if (R2 == distance)
//     {
//         cout << "����Բ��" << endl;
//     }
//     else if (R2 < distance)
//     {
//         cout << "����Բ��" << endl;
//     }
//     else
//     {
//         cout << "����Բ��" << endl;
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
//    cout << "����������Ϊ : " << c1.calculateArea() <<endl;
//    cout << "����������Ϊ : " << c1.calculateVolume() << endl;
//    
//    Cube c2;
//    c2.setHeight(10);
//    c2.setLength(10);
//    c2.setWidth(10);
//
//    // ȫ�ֺ����ж��Ƿ����
//    cout <<( isEqual(c1, c2) ? "�������������" : "���������岻���" )<< endl;
//    // ��Ա�����ж��Ƿ����
//    cout << (c1.isEqual_ByClass(c2) ? "c2��c1����������������" : "c2��c1������������岻���") << endl;
//    cout << (c2.isEqual_ByClass(c1) ? "c1��c2����������������" : "c1��c2������������岻���") << endl;
//    
//
//    // ����
//    Point  p1;
//    p1.set_X_Y(3,4); //����ĳ����Ϊ(4,5)
//    //int *p = p1.get_X_Y_Local();
//    //cout << "X����Ϊ : " << *p <<endl;
//    //cout << "X����Ϊ : " << *p << endl; //�ڶ��λ�ȡ��ַ�ͻ᲻ͬ �ֲ��������ͷ�
//    //cout << "Y����Ϊ : " << *p++<< endl; /ָ���ƶ�Ҳ���ܻ��
//
//    int* p = p1.get_X_Y_Global();
//    cout << "X����Ϊ : " << *p << endl;
//    cout << "Y����Ϊ : " << ++*p << endl; // *p++ ���ʽ��ֵû�б�
//    cout << "ָ���Ѿ��ƶ� : " <<* p << endl; // ������ʹ��p������ʹ��Ҫע��p�Ѿ������˸ı�
//   
//    // Բ��
//    Circle cc;
//    Point p2;
//    p2.set_X_Y(0, 0);
//    cc.setCenter(p2);
//    cc.setR(5);
//    // ȫ�ֺ����ж�
//    //isInCircle(cc, p1);
//    // �ֲ������ж�
//    cc.isInCircle_ByClass(p1);
//    //system("pause");
//    return 0;
//}