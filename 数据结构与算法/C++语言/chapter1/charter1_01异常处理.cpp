#include "charter1_illegalParameterValue.h"
int _charter1_abc(int a, int b, int c);
void _charter1_throwError()
{
	try { std::cout << _charter1_abc(2, 0, 4) << std::endl; }
	catch (illegalParameterValue e)
	{
		e.outputMessage();
	}
	printf("abc(1,2,5) = %d", _charter1_abc(1, 2, 5));
}
int _charter1_abc(int a, int b, int c)
{
	if (a <= 0 || b <= 0 || c <= 0)
		throw illegalParameterValue("All parameters should be > 0");
	return a * b * c;
}