#pragma once
#ifndef chapter9_wirePosition_
#define chapter9_wirePosition_
#include <ostream>
struct wirePosition
{
    int row,
        col;
    operator int() const { return row; } // ǿתת��,����������
};
std::ostream& operator<<(std::ostream& out, const wirePosition& x)
{
    out << "(" << x.row << "," << x.col << ") =>";
    return out; // ����queue��δ�ӡ������������
}
#endif chapter9_wirePosition_