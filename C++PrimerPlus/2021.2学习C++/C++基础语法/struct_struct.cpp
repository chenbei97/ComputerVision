#include <iostream>
#include <string> //2019���ᱨ�� c++20
#include "hello_world.h"
#include <ctime> // ʱ��ͷ�ļ�
using namespace std;
struct student {
	string name="cb";
	int age = 19;
	int score = 100;
};
struct teacher {
	int id = 5;
	string name = "sb";
	int age = 40;
	struct student  std = {
	"chen",100,100}; //ĳ��������ѧ��
};
int struct_struct(){
//int main() {
	//Struct(); 
	// �ṹ��Ƕ�׽ṹ��
	student  s1 = {"123",12,45};
	teacher  t1 = { 000,"wang",200,s1};
	cout << t1.std.age << endl; //���ص���ʵ��s1������
	teacher t2;
	cout << t2.std.age << endl;//��ʼ��������100
	
	
	//system("pause");
	return 0;
}