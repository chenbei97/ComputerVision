#pragma once
#include"GlobalFile.h"
#include <map>
// ��student��showMyOrder()ȥ����
class OrderFile
{
public:
	// ���캯��
	OrderFile();

	// ����ԤԼ��¼
	void updateOrder();

	// ��¼������ key --- ��¼������  value --- �����¼�ļ�ֵ����Ϣ
	map<int, map<string, string>> mapOrderFile;
	// key ԤԼ���� value ��һ map<string ,string>
	// Ȼ��Ƕ��  ��ͬ������ԤԼ��Ϣ
	// ԤԼ��¼����
	int OrderNum;
};