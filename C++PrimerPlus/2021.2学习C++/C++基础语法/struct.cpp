#include <iostream>
#include <string> //2019���ᱨ�� c++20
#include "hello_world.h"
#include <ctime> // ʱ��ͷ�ļ�
using namespace std;
//������ʽ:
//1.struct �ṹ���� ������
//2. struct �ṹ���� ������ = {��Ա1,��Ա2}
//3. ����ṹ��ʱ˳�㴴������
struct student {
    string name = "cb";
    int age = 24;
    int score = 100;
}s4; //˳�㴴���ṹ�����;
int Struct(){
//int main() {
    //pointer_func();
    // �ṹ�������û��Զ������������,�����û��洢��ͬ����������
    // �������Ĺ��ɣ�����û�к���,�ṹ�岻����
    // struct �ṹ����{�ṹ���Ա�б�};

    // ʵ�����ṹ��
    struct student s1;//1.
    student s2; //������������ʡ��,���Ƕ���ʱ����
    s2.age = 30; //�ṹ���Ա����
    struct student s3 = {"chenbei",24,100 };//2.
    //3.�ڴ���ʱ�͸������ֵ ������
    s4.name = "����";
    s4.age = 20;
    s4.score = 60;
    
    // �ṹ������ : �Ѵ������������忴��һ�������������
    // ÿ����һ����������һ����ȫ������
    struct student arr[3] = {
    {"����",18,80},
    {"����", 39, 45},
    {"����", 95, 22}
    };
    cout << arr[2].name << endl;

    //�ṹ��ָ�� : ���ʽṹ���Ա������
    //int* p = &s3; //����,��Ϊs3ȡ��ַΪ�ṹ��student����ʹ������ָ��
    struct student * p = &s3;
    student* p1 = &s2;// Ҳ����ʡ��

    cout << p->name << endl; //�ṹ��ָ�����������->����

    //system("pause");
    return 0;
}