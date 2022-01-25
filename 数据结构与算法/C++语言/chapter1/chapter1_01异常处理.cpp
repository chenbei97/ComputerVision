#include "chapter1_illegalParameterValue.h"
int _chapter1_abc(int a, int b, int c);
void _chapter1_throwError()
{
	try { std::cout << _chapter1_abc(2, 0, 4) << std::endl; }
	catch (illegalParameterValue e)
	{
		e.outputMessage();
	}
	printf("abc(1,2,5) = %d", _chapter1_abc(1, 2, 5));
}
int _chapter1_abc(int a, int b, int c)
{
	if (a <= 0 || b <= 0 || c <= 0)
		throw illegalParameterValue("All parameters should be > 0");
	return a * b * c;
}