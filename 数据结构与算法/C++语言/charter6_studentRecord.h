#pragma once
#pragma once
#ifndef charter6_studentRecord_
#define charter6_studentRecord_
#include <string>
#include <iostream>
// 合并方式1和2
struct _charter6_studentRecord
{
    int score;
    std::string* name;
    operator int() const { return score; }// 重载类型转换
};
std::ostream& operator<<(std::ostream& out, const _charter6_studentRecord& x)
{
    out << "score = " << x.score << "  name = " << *x.name << std::endl; return out;
}
#endif