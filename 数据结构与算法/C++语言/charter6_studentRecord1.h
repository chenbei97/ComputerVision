#pragma once
#ifndef charter6_studentRecord1_
#define charter6_studentRecord1_
#include <string>
#include <iostream>
// ��ʽ1
struct _charter6_studentRecord1
{
    int score;
    std::string* name;

    int operator !=(_charter6_studentRecord1 x) const
    {
        return (score != x.score); // ����!=����
    }
};
std::ostream& operator<<(std::ostream& out, const _charter6_studentRecord1& x)
{
    out << "score = " << x.score << "  name = " << *x.name << std::endl; return out;
}
#endif