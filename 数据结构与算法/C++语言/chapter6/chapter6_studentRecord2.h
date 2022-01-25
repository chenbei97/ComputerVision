#pragma once
#ifndef chapter6_studentRecord2_
#define chapter6_studentRecord2_
#include <string>
#include <iostream>
// 方式2
struct _chapter6_studentRecord2
{
    int score;
    std::string* name;
    operator int() const { return score; }// 重载类型转换
};
std::ostream& operator<<(std::ostream& out, const _chapter6_studentRecord2& x)
{
    out << "score = " << x.score << "  name = " << *x.name << std::endl; return out;
}
#endif chapter6_studentRecord2_