#include <iostream>
template<class T>
void _charter4_insert_sort(T a[], int n);
void _charter4_ppm1();
void _charter4_ppm2();
void _charter4_program_performance_measurement()
{
	_charter4_ppm1(); // ��ʽ1��ʱ
	std::cout << "\n" << std::endl;
	_charter4_ppm2();// ��ʽ2��ʱ
	system("pause");
}
void _charter4_ppm2()
{
	const int num = 10000;
	int a[num], step = 10;
	double clockPerMill = double(CLOCKS_PER_SEC) / 1000; // 1�δ�=1ms ԭ��1�δ�=1s
	for (int n = 0; n <= num; n += step)
	{
		long numOfRepeat = 0; // ��¼ִ��whileѭ���Ĵ���,�뵱ǰʱ�䵽t1�ľ���Զ���й�
		// Խ��,clock()-t1<160�жϵĴ���Խ��,ԽԶ��Խ��,while����ʱ���ѵ�ʱ���while�Ĵ�������1��while������ʱ��
		clock_t t1 = clock(); // ��ǰʱ����
		do 
		{//����ʱ����Ƶ�ѭ��,ÿ��n��ʱ�����г���160ms���ǲ������
			numOfRepeat++;
			for (int i = 0; i < n; i++)
				a[i] = n - i; // ��ʼ��
			_charter4_insert_sort(a, n);
			//printf("n = %d numOfRepeat = %long\n", n,numOfRepeat);
		} while (clock() - t1 < 160); //�����_charter4_ppm1�Ľ������n=num�Ż���150ms,����Ҫ�󲻳���160ms
		// n��Сʱclock���Ȳ�����¼������ôС��ʱ���,�����Ҳ��160ms,����ʵ������ʱ����0-160ms���ɳ�����beak

		double cost_time = ((double)clock() - t1) / clockPerMill; // ��ʼ������+�����ʱ�侭���ĵδ��� ��ÿ���δ������ѵ�ms����ms
		// Ȼ��ע�͵������ʱ��������һ��,����ʱ�������������ʱ��
		printf("numOfRepeat = %d  length(a) = %d  cost time = %f ms\n", numOfRepeat, n, cost_time / numOfRepeat);
		if (n == 100) step = 50; 
		if (n == 5000) step = 100;
	}
}
void _charter4_ppm1()
{
	const int num = 10000;
	int a[num], step = 10;
	double clockPerMill = double(CLOCKS_PER_SEC) / 1000; //ת��Ϊ1ms��ʱ����
	printf("clockPerMill = %lf\n", clockPerMill);// ÿs�ĵδ�����1000,ÿ1ms�ĵδ���1��
	for (int n = 0; n <= num; n += step)
	{ // n=0,10,20,...,1000
		for (int i = 0; i < n; i++)
		{ // i=0,1,2,..n-1
			a[i] = n - i; // ��ʼ������,i���0ȡ�鵽999,�ҳ�ʼ����������n-i�൱�ڽ���,�������������
		}
		clock_t start_time = clock(); // t1
		_charter4_insert_sort(a, n); // ��[0,n-1]�������������,����n�����Ӳ��������Ӷ�Խ��Խ��
		double cost_time = ((double)clock() - start_time) / clockPerMill; // ��1ms��ʱ�����õ�ms
		printf("length(a) = %d , cost time = %f ms\n", n, cost_time);

		if (n == 100) step = 100; // ��n��100ʱ,����ʱ�������ĺܿ�,��Ҫȷ���Ľ����ߵ���ϡ�輴��
		if (n == 5000) step = 500;
	}
}
template<class T>
void _charter4_insert_sort(T a[], int n)
{
	for (int i = 1; i < n; i++) //ִ��i=1,2,..n-1,n(������ѭ��)
	{
		T t = a[i]; // +1
		int j; // +1
		for (j = i - 1; j >= 0 && t < a[j]; j--)//for����һ���ж�,j=0,1,..n-2����ִ�бȽ�2,..n��
			a[j + 1] = a[j]; // j=0,1,2,...,n-2��ִ��1��,�ڲ���乲ִ��n-1��
		a[j + 1] = t; // +1
	}
	// +1�ϼ�3(n-1)
// ��õ������2��for��ִ���ڲ�����൱��ִֻ�бȽ�,Ҳ��n-1�Σ��ϼ�4(n-1)��
// ��������2��forÿ�ζ�ִ�е�ͷ��
// i=1,j=0,ִ��1�αȽϺ��ٱȽ��ж��Ƿ�������a[j+1] = a[j],�൱��ִ��2��for���,1���ڲ����
// i=n-1,j=n-2Ҳ�ǣ�ִ��n��for���,n-1���ڲ����
// for���ִ����2+3+..+n�Σ��ڲ����ִ����1+1..+1��n-2+1=n-1��,�ϼ�n(n+1)/2-1+(n-1)+3(n-1)=(n^2+9n-10)/2��
}
