#include <iostream>
#include <string> //2019���ᱨ�� c++20
#include "hello_world.h"
#include <ctime> // ʱ��ͷ�ļ�
using namespace std;
struct student {
	string name = "cb";
	int age = 24;
	int score = 100;
};
void print_student_value(struct student s) {
     //ֵ���� ��������Ϊһ���ṹ��  (student   s)
	// �˽ṹ����student����İ���
	s.name = "CB";
	cout << "�Ӻ�����ֵ��������" << s.name << endl;
 }
void print_student_addr(const  struct  student * s) {
	//ֵ���� ��������Ϊһ���ṹ��ĵ�ַ  (student*    s)
   // �˽ṹ���ַ��student�İ���
	//student *s ֻռ��4�ӽڣ� student s ��Ҫ�����µ��ڴ�����ֵ����, ��ַ���ݿ��Խ�ʡ�ڴ�
	// ��ַ���ݽ�ʡ�ڴ浫�ǲ���ȫ,����д�����ͻᵼ��ԭ�������ݷ����ı�
	// ����ʹ��const ���Է�ֹĳ������д���� Ҳ�г���ָ�벻�ܸı�ֵ,����ֻ��
	//s->name = "CB";
	cout << "�Ӻ����е�ַ��������" << s->name << endl;
}
int struct_func(){
//int main() {
	//struct_struct(); 
	// �ṹ����Ϊ��������
	//1.ֵ���� 2.��ַ����
	student stu; 
	// 1.ֵ����
	print_student_value(stu); //�Ӻ��������β�
	cout << "main������ֵ��������" << stu.name << endl; //ԭ����û�����ı�
	//2.��ַ����
	student* p = &stu;
	//print_student_addr(&stu);//�Ӻ��������β�
	print_student_addr(p);//����ָ��Ҳ���� p 0r &stu ����ȷ
	cout << "main�����е�ַ��������" << stu.name << endl; //ԭ���������˸ı�,����ʹ��const�󲻻�ı�
	//system("pause");


	return 0;
}