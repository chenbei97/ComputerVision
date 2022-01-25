#include <iostream>
#include <complex>
typedef std::complex<double>dcomplex; // ��double�����ʹ�ñ���
void quadratic_equation_find_root(const double & a , const double &b ,const double &c, dcomplex& x1, dcomplex& x2);
template<class T>
int find_maxval_loc_in_array(T a[], int n);
void _chapter2_test_and_debug()
{
	double a = 1, b = -5, c = 6;
	dcomplex x1, x2;
	quadratic_equation_find_root(a, b, c, x1, x2);
	a = 1, b = 2, c = 5;
	quadratic_equation_find_root(a, b, c, x1, x2);

	int d[6] = { 0,9,20,44,3,17 };
	int loc;
	loc = find_maxval_loc_in_array(d, sizeof(d) / sizeof(d[0]));
}
void quadratic_equation_find_root(const double& a, const double& b, const double& c , dcomplex & x1, dcomplex & x2 )
{
	if (a == 0)
		throw("a should be �� 0");
	double delta = b * b - 4 * a * c; // b^2-4ac
	double k = -b / (2 * a);
	if (delta > 0) // ������ͬʵ����
	{
		double d = sqrt(delta) / (2*a);
		x1 = k + d;
		x2 = k - d;
	}
	else if (delta == 0)
	{
		// ������ͬʵ����
		x1 = x2 = k;
	}
	else
	{
		// �����
		dcomplex d(0, sqrt(-delta) / (2 * a));
		x1 = k+d;
		x2 = k-d;
	}
	std:: cout << "x1 = " << x1.real()<<" + " <<x1.imag()<<"i"<< 
		"   x2 = " << x2.real()<<" + "<<x2.imag()<<"i" << std::endl;
}
template<class T>
int find_maxval_loc_in_array(T a[], int n)
{
	if (n <= 0)
		throw("n must be > 0");
	int loc = 0; // ���λ�ó�ʼ��Ϊ��1��Ԫ�ص�����0
	for (int i = 1; i < n; i++)
	{
		if (a[loc] < a[i])
			loc = i; // �������ֵ����λ��
	}
	std::cout << "maxval index = " << loc << std::endl;
	return loc;
}