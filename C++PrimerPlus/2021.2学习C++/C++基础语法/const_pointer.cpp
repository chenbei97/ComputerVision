#include <iostream>
#include <string> //2019���ᱨ�� c++20
#include "hello_world.h"
#include <ctime> // ʱ��ͷ�ļ�
using namespace std;
void const_pointer(){
//int main() {
	//create_pointer();
	//1.const ����ָ��--->����ָ��;
	//2.const���γ���--->ָ�볣����
    //3.const ����ָ�������γ�����

	// 1.����ָ��:ָ���ָ������޸�,��ָ��ָ���ֵ�����޸�
	int a = 10, b = 20;
	const int* p = &a; //����ָ��
	//*p = 20; //*p���ǽ����ü�ԭ����ֵ10,�ǲ��ܸı�͸�ֵ20��
	p = &b; //����p�Ǹ���ַ,ָ���ǿ��Ըĵ�,ָ��b�ĵ�ַ
	
	//2.ָ�볣��:
	int* const p1 = &a;
	* p1 = 20; //ֵ�����޸�
	// p1 = &b; //ָ�����޸�

	//3.const������ָ�������γ���
	const int* const p2 = &a;
	//*p2 = 20; �����޸�ֵ
	//p2 = &b;//Ҳ�����޸�ָ��
	//system("pause");
	//return 0;
}
