#include <string>
#include <iostream>
int stringToInt(std::string s);
void _chapter10_int2String()
{
    std::string s = "abc";
    std::cout << s << " = " << stringToInt(s) << std::endl;

    s = "abcde";
    std::cout << s << " = " << stringToInt(s) << std::endl;
}
int stringToInt(std::string s)
{
    int length = (int)s.length();
    int answer = 0;
    if (length % 2 == 1)
    {
        answer = s.at(length - 1);
        length--;
    }

    for (int i = 0; i < length; i += 2)
    {
        answer += s.at(i);
        answer += ((int)s.at(i + 1)) << 8;
    }

    return (answer < 0) ? -answer : answer;
}