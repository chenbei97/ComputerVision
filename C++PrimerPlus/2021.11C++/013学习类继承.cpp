#include "��̳�.h"
void func_q(Person& q) { q.show_person_v(); };
void func_p(Person* p) { p->show_person_v(); };
void func_v(Person v) { v.show_person_v(); };
void Study_Class_inheritance() // �˺���Ҫ��������һ���ļ�����������쳣
{
	Person p0(); // valid but meanless
	// p0().show_person(); invalid
	Person p1; // Ĭ�Ϲ���,����ʹ����ʽ��Person p1����
	p1.show_person();
	Person p2("xixi","chaoyang",27); // �б���
	p2.show_person();
	CB cb0(); // valid but meanless
	// cb0().show_cb(); invalid
	
	CB cb1;// Ĭ�Ϲ���,����ʹ����ʽ��CB cb1����
	CB cb2("banana", "basketball", 1.80, 0, true, "chenbei", "shunyi", 18);// �б���&�вι���
	CB cb3("apple", "football", 1.85, 1, true, cb2); // ���ƹ���

	std :: cout << "cb1��Ĭ�Ϲ���" << std :: endl;
	std :: cout << "	"  ;
	cb1.show_cb();// �ڲ�ʹ����show_person()����

	std::cout << "cb2��" << std::endl;
	std::cout << "	"  ;
	cb2.show_cb();// �ڲ�ʹ����show_person()����

	std::cout << "cb3��" << std::endl;
	std::cout << "	"  ;
	cb3.show_cb();// �ڲ�ʹ����show_person()����

	Person& qp1 = p1; // ������������
	Person* pp2 = &p2;// ��������ָ��
	qp1 = cb2; // �����������ÿ���ָ�����������
	pp2 = &cb3;// ��������ָ�����ָ�����������
	qp1.show_person(); // valid 
	// qp1.show_person(); invalid ����ָ����ζ����������ķ���
	pp2->show_person(); // valid
	// pp2->show_cb(); invalid ����ָ����ζ����������ķ���

	CB &qcb3  = cb3;// ��������������
	CB* pcb3 = &cb3;// ����������ָ��
	// qcb2 = p1; ���ܰѻ���Ķ��󸳸������������
	// qvb2 = qp1;Ҳ���ܰѻ�������ø��������������
	// pcb3 = &p2; ���ܰѻ���Ķ����ַ�����������ָ��
	// pcb3 = pp2; Ҳ���ܰѻ����ָ�븳���������ָ��

	// ����virtual������
	std::cout << "�麯��������" << std::endl;
	Person& qp2 = p2; // ָ��������Ļ�������
	Person& qcb2 = cb2; // ָ�����������Ļ�������
	qp2.show_person(); // ���õ��Ǹ����show_person
	qcb2.show_person();// ��Ȼ��ָ��������ģ������õĻ��Ǹ����show_person
	qp2.show_person_v();// ���õ��Ǹ����show_person_v
	qcb2.show_person_v();// ����virtual�Ժ󣬵��õ����������show_person_v

	pp2 = &p2;
	pcb3 = &cb3;
	pp2->show_person();
	pcb3->show_person();
	pp2->show_person_v();
	pcb3->show_person_v();
	// �����ǣ�û��ʹ��virtual���������û�ָ������ѡ���������ķ���
	// ʹ��virtual������ָ������û�ָ������ѡ���������ķ���

	std::cout << std::endl;
	// �����ж��崦���������á�ָ���ʵ��3�����
	// ���뺯����ʵ�ʲ���Ϊ�������������
	func_q(p2); // �������ô������ʵ��->���û��෽��
	func_q(cb2);// �������ô�������ʵ��->���������෽��
	func_p(&p2);// ����ָ�봫�����ʵ��->���û��෽��
	func_p(&cb2);// ����ָ�봫������ʵ��->���������෽��
	func_v(p2);// ����ʵ���������ʵ��->���û��෽��
	func_v(cb2);// ����ʵ������������ʵ��->���û��෽��
	system("pause");
}