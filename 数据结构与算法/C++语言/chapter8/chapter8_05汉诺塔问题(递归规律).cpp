#include <iostream>
using namespace std;
void towerOfHanoi_byRecursion(int, int, int, int);
void _chapter8_towerOfHanoi_byRecursion()
{
	towerOfHanoi_byRecursion(4, 1, 2, 3);//���Կ�����ӡ����Ϣ����Ϊ15��
}
void towerOfHanoi_byRecursion(int n , int towerx, int towery, int towerz)
{
	// �˳��򲢲����ƶ�Ԫ�صĳ���ֻ��һ�����Գ��򲽵ĳ���
	// ��n�����Ӵ�xת�Ƶ�y
	if (n > 0)
	{
		// �Ȱ�ǰn-1������ת�Ƶ�z,���ĵ��ӾͿ��Է���y
		// towerx,towery,towerz����������,���Կ���arrayStack�����1��Ԫ��
		// ���·�������˳��Բ�ͬ��������pop��push�����Ϳ�����ɵ���
		cout << "n = " << n << " x = " << towerx << "  y = " << towery <<endl;
		towerOfHanoi_byRecursion(n-1,towerx, towerz, towery); 
		cout <<"tower "<< towerx << " is popping " << "and pushed in tower " << towery << endl;
		//cout << "mov top disk from tower " << towerx << " to top of tower " << towery << endl;
		// ֮��Ϳ��԰�z�ϵ�n-1�������ƶ���y
		towerOfHanoi_byRecursion(n - 1, towerz, towery, towerx);
		//cout << "mov top disk from tower " << towerz << " to top of tower " << towerx << endl;
	}
}
