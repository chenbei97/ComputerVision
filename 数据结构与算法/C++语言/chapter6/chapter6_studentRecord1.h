#pragma once
#ifndef chapter6_studentRecord1_
#define chapter6_studentRecord1_
#include <string>
#include <iostream>
// 方式1
struct _chapter6_studentRecord1
{
    int score;
    std::string* name;

    int operator !=(_chapter6_studentRecord1 x) const
    {
        return (score != x.score); // 重载!=运算
    }
};
std::ostream& operator<<(std::ostream& out, const _chapter6_studentRecord1& x)
{
    out << "score = " << x.score << "  name = " << *x.name << std::endl; return out;
}
#endif chapter6_studentRecord1_