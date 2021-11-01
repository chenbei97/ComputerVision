#include <iostream>
using namespace std;
#include "quote_pointer.h"
// ��python����Ҫֱ�ӷ������˽��������Ҫװ����@property
/*
    # ����ֱ�ӻ�ȡ˽������ ����get����
	@property
	def age(self):   # �������ͱ�����������ͬ
		return self.__age
	# ����ֱ�Ӹı�˽������ ����set���� set������get
	@age.setter
	def age(self , age):
		self.__age = age
*/
// c++����ĳЩ������������� ���˽�����Կ���ʹ����Ԫ friend
/*
1.ȫ�ֺ�������Ԫ
2.������Ԫ
3.��Ա��������Ԫ
*/
class Building1
{
	friend void goodGay(Building1* building); //�ú������Է���˽������
public :
	Building1() // �޲ι���
	{
		_Livingroom = "����";
		_Bedroom = "����";
	}
public:
	string _Livingroom; // ����
private:
	string _Bedroom; // ����

};
// 1. ȫ�ֺ�������Ԫ
void goodGay(Building1* building) // ��ַ����
{ 
	// ȫ�ֺ������ܷ���˽������ ���Ǽ���friend ���Է���
	cout << "�û���ȫ�ֺ������ڷ���˽���������� : " <<building->_Bedroom<< endl;
}

// 2. ������Ԫ
class Building2
{
	friend class Goodgay1;// ĳ����Է��ʸ����˽������ ��ô�����κγ�Ա�����Է��ʸ���
public:
	Building2(); //�޲ι��� ���ǲ�ͬ��Building2�������ڽ��й��� ����Ҳ�������⹹��
public:
	string _Livingroom; // ����
private:
	string _Bedroom; // ����
};
// <2.1>Building2 ����д���캯�� ���޲ι��죩
Building2::Building2()
{
	_Livingroom = "����"; 
	_Bedroom = "����";

}
class Goodgay1
{
public:
	Goodgay1(); // �޲ι��� : ��new�������µ��ڴ��ַ��building2ָ������
	void visit();
	Building2* building2; // ��Goodgay������˽����� ֻ���������ǵ�ַ
};
// <2.2>Goodgay ����д���캯�� (�޲ι���)
Goodgay1::Goodgay1()
{
	// ������������� �������� building2 ָ��һ���¿��ٵ��ڴ��ַ ����building2��ָ�봴��
	building2 = new Building2;  // �����building2 �����������building2����ͬ��
}
// <2.3> Goodgay ����д��Ա����
void Goodgay1::visit()
{
	//cout << "�û��������ڷ���˽���������� : " <<building2->_Livingroom << endl;
	// Ҳ���Է���˽������ 
	cout << "�û��������ڷ���˽���������� : " << building2->_Bedroom << endl;
}


// 3.��Ա��������Ԫ : ֻϣ������ĳ���������ܷ���
class Building3; // ��ȻGoodgay2����Building3���� , ����ǰ���õ��˺��� ���Ի�������������һ����Building3
class Goodgay2 // Goodgay2������Building3֮ǰ���� ����97�в���ʶ�������
{
public:
	Goodgay2();// �޲ι��� : ��new�������µ��ڴ��ַ��building3ָ������
	Building3* building3;
	void visit1(); // ������visit1���������Է��ʽ�����˽������
	void visit2(); // ������visit2�������Է��ʽ�����˽������
};
class Building3
{
	//friend class Goodgay2;
	//friend void Goodgay2:: visit1();
	friend void Goodgay2::visit2();   
public:
	Building3(); //�޲ι���
public:
	string _Livingroom; // ����
private:
	string _Bedroom; // ����
};

// ���⹹�캯��
Goodgay2::Goodgay2()
{
	building3 = new Building3;
}
// �����Ա����
void Goodgay2::visit1()
{
	cout << "�û�����ĳ�Ա����visit1���ڷ��ʹ������� : " << building3->_Livingroom << endl;
}
void Goodgay2::visit2()
{
	cout << "�û�����ĳ�Ա����visit2���ڷ���˽������ : " << building3->_Bedroom << endl;
}
// ���⹹�캯��
Building3::Building3()
{
	_Bedroom = "����";
	_Livingroom = "����";
}
int friend_use()
//int main()
{
	//copy_Construct(); // �������캯������
	// Deep_Shallow_Copy(); // �����ǳ����
	// classMember(); // ����Ϊ���Ա
	//static_member_func(); // ��ľ�̬�����;�̬����
	//this_pointer(); // this ָ���ʹ��
	
	//Building1 building1;
	//goodGay(&building1);
 //  
	//Goodgay1 goodgay1;
	//goodgay1.visit();
	
	Goodgay2 goodgay2;
	goodgay2.visit1();
	goodgay2.visit2();
	system("pause");
	return 0;
}