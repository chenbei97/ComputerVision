#include "all.h"
void Study_Fill_Array(array<double, 4>* p);
void Study_Show_Array(array<double, 4>  p);
void Study_compare_arr_vector_array()
{
	double arr1[4] = { 1.2,2.4,4.8,9.6 };
	double arr1_[4];
	vector<double> arr2(4);
	vector<double> arr2_(4);
	array<double, 4> arr3 = { 1.1,1.2,1.3,1.4 };// ���Գ�ʼ��Ҳ���Բ���ʼ��
	array<double, 4> arr3_;
	// vector�ı��뵥����ʼ��
	arr2[0] = 1.0 / 3; arr2[1] = 1.0 / 5; arr2[2] = 1.0 / 7; arr2[3] = 1.0 / 9;

	// ��ͬ�㶼����ʹ���������з���
	cout << "arr1[0]=" << arr1[0] << "  arr2[0]=" << arr2[0] << "  arr3[0]=" << arr3[0] << endl;

	// ������ͨ���鲻��ֱ�Ӹ�ֵ��array/vector�������
	// arr1_ = arr1; �Ƿ�
	arr2_ = arr2;
	arr3_ = arr3;

	// ��ͨ���鲻����Խ�����.vector/array����ʹ��at������ֹԽ��
	arr1[-2] = 20.1; // ʵ���Ͼ���*(arr1-2),����ڴ治����arr1
	cout << "&arr1[-2]=" << &arr1[-2] << "  !=  &arr1=" << &arr1 << endl;
	//arr2.at(-2) = 20.1; at��⵽�Ƿ�����֮���ж�
	arr2.at(2) = 20.1; arr3.at(2) = 20.3;// �Ϸ�
	cout << "arr2[2]=" << arr2[2] << "arr3[2]=" << arr3[2] << endl;

	int x1 = 5, x2 = 5, y;
	y = x1++;
	cout << "�ȼ�����ʽx1++=" << y << "��Ȼ������x1=" << x1 << endl;
	//�ȼ�����ʽx1++ = 5��Ȼ������x1 = 6
	y = ++x2;
	cout << "������Ȼ�������ʽx2++=" << y << "����ʱx2=" << x2 << endl;
	//������Ȼ�������ʽx2++ = 6����ʱx2 = 6

	// ������array����
	array<double, 4> arr;
	Study_Fill_Array(&arr); // �����ַ
	Study_Show_Array(arr);// �������

}
void Study_Fill_Array(array<double, 4>* p)
{
	for (int i = 0; i < 4; i++)
	{
		(*p)[i] = i; // p��ָ��,�����ú��������
	}
}
void Study_Show_Array(array<double, 4>  p)
{
	for (int i = 0; i < 4; i++)
	{
		cout << p[i] << endl;
	}
}