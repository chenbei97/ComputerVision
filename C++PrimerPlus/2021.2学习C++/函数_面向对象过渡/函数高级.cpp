#include <iostream>
using namespace std;
// 1.����������ʵ��ֻ����һ������Ĭ�ϲ���
// 2.ռλ��  ����ֵ���� ������ (��������)
void func1(int a, int)
{
    cout << a << endl;
}
// 3.���غ��� : ����������ͬ���ǲ�����ͬ  ��Qt�еĹ��غ���@Pyqt_Slot
// �����ķ������Ͳ�����Ϊ�������ص����� int func() �� void func() �ǲ��е�
//3.1 ������Ϊ��������
void func1(int& a)
// �̶���ַ���̶�ֵ ����10�Ƿ� int&a �ȼ���int * const a = &c ָ�볣��
// int & a =10 �ȼ���int * const a = &10; �ǷǷ���,���Գ���10���ܽ���ú���
// ���ñ�����һ���Ϸ����ڴ�ռ�
{
    cout << "���ô��ݡ������غ���" << endl;
}
void func1(const int& a)
// �̶�ֵ���̶���ַ ����10�ǿ��Ե� ����ָ��
 // �ȼ��� const int* p = &a 
// const int &a = 10 ; <----->  const int * p = &10�ǺϷ���  
// �����ǳ��� ָ�� ��������ͬ  ֵ�����޸� ָ�����
{
    cout << "�������á������غ���" << endl;
}
//3.2���������뺯��Ĭ�ϲ���
void func2(int a, int b = 10);
void func2(int a);  // ��main��func2(10) ������ֶ�����Ҫ����
void super()
//int main()
{
    func1(10, 10); // ռλ�����������



    int a = 10;
    //const int* p = &a;  // �̶������̶���ַ
    //cout << "p�ĵ�ַΪ : " << p << endl;
    //p++;
    //cout << "p++�ĵ�ַΪ : " << p << endl;

    func1(a);  // ���ó���
    func1(10); // ��������



    //system("pause");
   // return 0;
}



