#include <iostream>
#include <assert.h>
template<class T >
void sequentialSearch_analytic(T a[], int n, const T& x);
template<class T >
void insert_analytic(T a[], int& n, const T& x);
void _chapter2_analytic_best_worst_mean_steps()
{
	const int n = 5;
	int a[n] = { 0,1,2,3,4 };
	int x = 0;
	sequentialSearch_analytic(a, n, x);// �������Ƚ�4��
	x = a[n - 1];
	printf("\n");
	sequentialSearch_analytic(a, n, x); //�������Ƚ�n+3��
	x = 6;
	printf("\n");
	sequentialSearch_analytic(a, n, x); //û�ҵ�Ҳ��n+3��
	// ����֪��,�ٶ�һ���ܲ��ҳɹ�100%ʱ�������ÿ��Ԫ�ز�ͬ����Ϊx���κ�Ԫ����ȵĸ���һ��
	// ��ô�Ϳ�����Ϊƽ�����ҵĳɹ�����Ϊ(n+7)/2
	// ���ǿ��ܴ��ڲ��ɹ����ҵ������ʱִ�в���Ϊn+3,�ٶ��ܹ��ɹ����Ҹ���0.8
	// ����ʵ�ĸ���Ϊ0.8(n+7)/2+0.2(n+3)=0.6n+3.4
	int n1 = 5;
	int b[6] = { 0,1,2,3,4 };
	printf("\n");
	insert_analytic(b, n1, x); // ��õ����ֱ���Ҳ干��4��
	int n2 = 5; // ���µ�n2,n1��1��
	int c[6] = { 0,1,2,3,4 }; // ���µ�����,��Ϊb������+1��
	x = -1;
	printf("\n");
	insert_analytic(c, n2, x);// ��������干��2*5+4��
}
template<class T >
void sequentialSearch_analytic(T a[], int n, const T& x)
{
	int step = 0;
	int i; step++;
	for (i = 0; i < n && a[i] != x; i++)
		step++; // forѭ���Ƚ�1��
	step++; // ��ֹforѭ��1��
	step++;// if���۲��ҳɹ������ж�1��
	if (i == n)   printf("x is not exist");// if�ж�1��,���ִ��ִ�в�Ӱ����1��
	else { step++; printf("x_idx = %d", i); }// ���ҳɹ�ִ��1��ʧ��0��

	printf("\nstep = %d", step);
	if (a[0] == x)
		assert(step == 4); // ��õ��������1��,for�Ƚ�1��,if�ж�1��,�ҵ������ֵ����1��,����4��
	else if (a[n - 1] == x)
		assert(step == n + 3); // �������Ƚ���n�λ�û�ҵ�
}
template<class T >
void insert_analytic(T a[], int& n, const T& x)
{
	int step = 0;
	int i; step++; // 1��
	for (i = n - 1; i >= 0 && x < a[i]; i--)
	{
		step++; // ����forѭ���Ƚ�i+1�� i=0,1,2,...n-1
		a[i + 1] = a[i]; // ��ֵi+1�� i=0,1,2,...n-1
		step++;// ��ֵi+1��
		// һ��forѭ��ִ��2(i+1)��
	}
	step++;// ��ֹforѭ��1��
	a[i + 1] = x; step++;
	n++; step++;
	for (int i = 0; i < n; i++) // ����<n,��Ϊn++��
		printf("a[%d] = %d  ", i, a[i]);
	printf("\nstep = %d", step);
	if (a[0] == x)
		assert(step == 2 * (n - 1) + 4); // ������forѭ���Ƚ�ִ��(n+1)�θ�ֵn��,�ⲿ4�ι������2n+4��,����n++��������Ҫ��һ��
	else if (a[n - 1] == x)
		assert(step == 4); // ��õ�����Ҳ岻����forѭ��������Ҫ��ֹ1�ι�1+1+1+1ִ��4��

	// ����a[n]��Ҫ4��
	// ������1��������ĳ��λ��Ӧ��Ϊforѭ���ڲ��Ƚ�(i+1)�θ�ֵi+1�ι�2i+2��,�ⲿִ��4��
	// ����a[0]ʱȡi=n-1,(2n-2+2)=2n��,�ⲿִ��4��;����a[n-1]ȡi=0,��Ҫ2��,�ⲿִ��4��;
	// ��a[0]��a[n-1]��n�����������ⲿ�ۼ�4n��,�ڲ���2n+2(n-1)+...+2=n(n+1)��
	// �������Ҳ�û��forѭ���Ĵ���4,�ܵĴ���Ϊn^2+5n+4=(n+4)(n+1)��ƽ������=n+4
}