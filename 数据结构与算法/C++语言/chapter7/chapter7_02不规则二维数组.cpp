#include <iostream>
using namespace std;
void _chapter7_irregular_array2d()
{
	int rows = 5;
	int lengths[5] = { 6,3,4,2,7 }; // ÿһ�еĳ���
	// ����1����ά���鲢��������Ҫ������
	// ���������ά��������ָ����������Ӷ����
	int** arr = new int* [rows]; // ָ��ָ�������ָ��Ϊ**����
	//  ָ���������ô����ȥ�����ּ���,��int**����
	// ָ��ָ�������?����ȥ�����ֻ�Ҫȥ��������ߵ�1��*,��int *����
	// int * ���Ϳ����ǵ�ַҲ�����ǵ�ַ����
	// int *[rows] ���� int *[] ��ַ��������,Ҳ�����׳Ƶ�ָ������

	for (int i = 0; i < rows; i++)
		arr[i] = new int[lengths[i]]; // arr[i]Ҳ�Ǹ�ָ��,ָ��һά���鱾��
	
	// ����������ı���
	for (int i = 0; i < rows; i++) 
	{
		for (int j = 0; j < lengths[i]; j++)
		{
			arr[i][j] = i * rows + j + 1;
		}
	}
	for (int i = 0; i < rows; i++)
	{
		int* t = arr[i];
		for (int j = 0; j < lengths[i]; j++)
			cout << *t++ << "  ";
	}
	cout << endl;
}