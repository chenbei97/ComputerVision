#pragma once
#pragma once
#ifndef chapter6_studentRecord_
#define chapter6_studentRecord_
#include <string>
#include <iostream>
// �ϲ���ʽ1��2
struct _chapter6_studentRecord
{
    int score;
    std::string* name;
    operator int() const { return score; }// ��������ת��
};
std::ostream& operator<<(std::ostream& out, const _chapter6_studentRecord& x)
{
    out << "score = " << x.score << "  name = " << *x.name << std::endl; return out;
}
#endif chapter6_studentRecord_