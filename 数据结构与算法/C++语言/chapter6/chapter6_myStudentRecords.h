#ifndef chapter6_myStudentRecords_
#define chapter6_myStudentRecords_
#include <string>
#include <iostream>
// ��ʽ1
struct _chapter6_studentRecord1
{
    int score;
    std::string* name;

    int operator !=(_chapter6_studentRecord1 x) const
    {
        return (score != x.score); // ����!=����
    }
};
std::ostream& operator<<(std::ostream& out, const _chapter6_studentRecord1& x)
{
    out << "score = "<<x.score << "  name = " << *x.name << std::endl; return out;
}
// ��ʽ2
struct _chapter6_studentRecord2
{
    int score;
    std::string* name;
    operator int() const { return score; }// ��������ת��
};
std::ostream& operator<<(std::ostream& out, const _chapter6_studentRecord2& x)
{
    out << "score = " << x.score << "  name = " << *x.name << std::endl; return out;
}
// �ϲ���ʽ1��2
struct _chapter6_studentRecord
{
    int score;
    std::string* name;

    int operator !=(_chapter6_studentRecord x) const
    {
        return (score != x.score || name != x.name); // ���ֻ��߷������ȶ��ǲ���
    }
    operator int() const { return score; } // int()ֻ���ڲ�����!=��<<���������ʹ��
};
std::ostream& operator<<(std::ostream& out, const _chapter6_studentRecord& x)
{
    out << "score = " << x.score << "  name = " << *x.name << std::endl; return out;
}
#endif chapter6_myStudentRecords_