#pragma once
#include <string>
#include <iostream>
// 方式1
struct studentRecord1
{
    int score;
    std::string* name;

    int operator !=(studentRecord1 x) const
    {
        return (score != x.score); // 重载!=运算
    }
};
std::ostream& operator<<(std::ostream& out, const studentRecord1& x)
{
    out << "score = "<<x.score << "  name = " << *x.name << std::endl; return out;
}
// 方式2
struct studentRecord2
{
    int score;
    std::string* name;
    operator int() const { return score; }// 重载类型转换
};
std::ostream& operator<<(std::ostream& out, const studentRecord2& x)
{
    out << "score = " << x.score << "  name = " << *x.name << std::endl; return out;
}
// 合并方式1和2
struct studentRecord
{
    int score;
    std::string* name;

    int operator !=(studentRecord x) const
    {
        return (score != x.score || name != x.name); // 名字或者分数不等都是不等
    }
    operator int() const { return score; } // int()只能在操作符!=和<<以外操作中使用
};
std::ostream& operator<<(std::ostream& out, const studentRecord& x)
{
    out << "score = " << x.score << "  name = " << *x.name << std::endl; return out;
}
