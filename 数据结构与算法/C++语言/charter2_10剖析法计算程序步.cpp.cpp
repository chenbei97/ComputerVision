#include <iostream>
#include <assert.h>
template<class T>
void accumulate_analytic(T src[], T dst[], int n);
template<class T>
void matrix_transpose_analytic(T ** a ,int n ,bool show =true);
void _charter2_analytic_method_steps()
{
	const int n = 4; // �����Ƿ���
	int a1[n] = { 1,2,3,0 };
	int a2[n] = { 4,5,6,10};
	int a3[n] = { 7,8,9,11 };
	int a4[n] = { 12,13,14,15 };
	// Ԫ����ÿ��������Ԫ�ص��׵�ַ,a1=&a1[0]������ô��ֵҲ����
	
	int* a[n] = { a1,a2,a3,a4 };  // һάָ������
	int** pa = a;
	int step = 0;
	matrix_transpose_analytic(a, n); // a����
	printf("\n");
	matrix_transpose_analytic(pa, n); // paҲ����
	int b[5] = { 1,2,3,4,5 };
	int c[5] = {};
	printf("\n");
	accumulate_analytic(b, c, 5);
}
template<class T>
void matrix_transpose_analytic(T** a, int n,bool show)
{
	// **ָ����ָ��һάָ�����鱾���ָ����Է�������Ԫ��
	int step = 0;
	for (int i = 0; i < n; i++) // ��Ҫn+1�αȽ�,������2��forѭ���Ƚϴ���,i=0,ִ��3��,��Ϊ��ֹѭ����1��
	{
		step += 1; 
		for (int j = i + 1; j < n; j++) // ��Ҫ��(n-i)�αȽ�,n=3ʱ=3+2+1+0=6�αȽ�
		{
			// �ڲ�forѭ������ִֻ����n-i-1��
			step += 2; // ִ��������i��n�ν���,�����Ǽ��㽻�������ͱȽϴ���
			T temp = a[i][j]; // a[0][1],a[0][2],...,a[0][n-1]<=>a[1,0],a[2,0],...,a[n-1,0]ÿ�ν����ͼ�����1��1��
			a[i][j] = a[j][i];// a[1][2],a[1][3],...,a[1][n-1]<=>a[2,1],a[3,1],...,a[n-1,1]
			a[j][i] = temp; // a[i][j]��i����ÿ�в���,�б仯,a[j][i]��j����ÿ�б仯,�в���
		}
		step += 1; // ��ֹ��2��forѭ������1��
	}
	step += 1; // ��ֹ��1��forѭ������1��
	assert(step == n * n + n + 1); // ʱ�临�Ӷ�Ϊn^2+n+1
	if (show)
	{
		for (int row = 0; row < n; row++)
		{
			int* rowp = a[row]; // ��ָ��
			for (int col = 0; col < n; col++)
				printf("a[%d][%d] = %d   ", row, col, rowp[col]);
		}
		printf("\nstep = %d", step);
	}

}
template<class T>
void accumulate_analytic(T src[], T dst[], int n)
{
	int step = 0;
	T res = 0; step++; // 1��
	for (int j = 0; j < n; j++) //ִ��n+1��
	{
		step++; // �Ƚ�j��n�Ĵ�СΪn��
		dst[j] = res += src[j]; step += 2;// 2�θ�ֵ����
		printf("dst[%d] = %d   ", j, dst[j]);
	}
	step++; // ��ֹforѭ����Ҫ1��,�ܼ�1+n+2n+1=3n+2��
	assert(step == 3*n+2);
	printf("\nstep = %d", step);
	// 5->17,4->14
		
}