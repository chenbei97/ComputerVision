#pragma once
#ifndef charter6_studentRecord2_
#define charter6_studentRecord2_
#include <string>
#include <iostream>
// ��ʽ2
struct _charter6_studentRecord2
{
    int score;
    std::string* name;
    operator int() const { return score; }// ��������ת��
};
std::ostream& operator<<(std::ostream& out, const _charter6_studentRecord2& x)
{
    out << "score = " << x.score << "  name = " << *x.name << std::endl; return out;
}
#endif