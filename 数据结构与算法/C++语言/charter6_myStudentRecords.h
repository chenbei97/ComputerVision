#pragma once
#include <string>
#include <iostream>
// ��ʽ1
struct studentRecord1
{
    int score;
    std::string* name;

    int operator !=(studentRecord1 x) const
    {
        return (score != x.score); // ����!=����
    }
};
std::ostream& operator<<(std::ostream& out, const studentRecord1& x)
{
    out << "score = "<<x.score << "  name = " << *x.name << std::endl; return out;
}
// ��ʽ2
struct studentRecord2
{
    int score;
    std::string* name;
    operator int() const { return score; }// ��������ת��
};
std::ostream& operator<<(std::ostream& out, const studentRecord2& x)
{
    out << "score = " << x.score << "  name = " << *x.name << std::endl; return out;
}
// �ϲ���ʽ1��2
struct studentRecord
{
    int score;
    std::string* name;

    int operator !=(studentRecord x) const
    {
        return (score != x.score || name != x.name); // ���ֻ��߷������ȶ��ǲ���
    }
    operator int() const { return score; } // int()ֻ���ڲ�����!=��<<���������ʹ��
};
std::ostream& operator<<(std::ostream& out, const studentRecord& x)
{
    out << "score = " << x.score << "  name = " << *x.name << std::endl; return out;
}
