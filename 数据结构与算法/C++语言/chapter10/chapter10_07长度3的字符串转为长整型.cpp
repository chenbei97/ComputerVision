#include <string>
#include <iostream>
long long2String(std::string s);
void _chapter10_long2String()
{
	std::string s = "abc";
	std::cout<<"answer is "<<long2String(s)<<"\n";
}
long long2String(std::string s)
{
	if (s.length() > 3)
		return -1;
	long answer = s.at(0);
	// ����8λ
	answer = (answer << 8) + s.at(1);
	// ��������8λ
	return (answer << 8) + s.at(2);
}