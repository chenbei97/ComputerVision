#pragma once
#include "charter1_illegalParameterValue.h"
// �˺��������Ա�ľ�����ʵ�����и��ƹ��캯����ʵ�ֵ�ǰ�����charter5_arrayList.cpp
template<class T>
void changeLength1D(T*& pa, int oldLength, int newLength)
{
	if (newLength < 0)
		throw illegalParameterValue("new length must be >=0");
	std::cout << "before change :  " << std::endl;
	for (int i = 0; i < oldLength; i++)
		std::cout << pa[i] << std::endl; // ����ִ��
	T* temp = new T[newLength];
	// ����µĳ��ȱ䳤��ิ��ԭ������ô��Ԫ��,�����̾͸��Ƶ�ǰ��ô��Ԫ��
	int number = std::min(oldLength, newLength);//Ҫ���Ƶ�Ԫ�ظ���
	printf("number = %d\n", number);
	std::copy(pa, pa + number, temp); // a�Ǹ�T���͵�ָ����������� ����+����
	for (int i = number; i < newLength; i++)
		temp[i] = 0;
	delete[] pa; // ɾ��ԭ��������Ԫ��
	//for (int i = 0 ;i<oldLength; i++) //->��պ󲻿���ִ�лᱨ��
	//	std::cout << pa[i] << std::endl;
	pa = temp; // ָ���µ�����
}
void _charter5_changeLength1D()
{
	const int n = 5;
	int* pa = new int[n];
	for (int i = 0; i < n; i++)
		pa[i] = i + 1;
	//for (int i = 0; i < n; i++)
	//	std::cout << pa[i] << std::endl;
	int oldlength = n;
	int newlength = 10;
	//printf("%d\n", std::min(5,10));
	changeLength1D(pa, oldlength, newlength);
	std::cout << "after change :  " << std::endl;
	for (int i = 0; i < newlength; i++)
		std::cout << pa[i] << std::endl;
}
