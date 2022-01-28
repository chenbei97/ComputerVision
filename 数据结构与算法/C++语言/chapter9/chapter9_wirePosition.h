#pragma once
#ifndef chapter9_wirePosition_
#define chapter9_wirePosition_
#include <ostream>
struct wirePosition
{
    int row,
        col;
    operator int() const { return row; } // 强转转换,返回所在行
};
std::ostream& operator<<(std::ostream& out, const wirePosition& x)
{
    out << "(" << x.row << "," << x.col << ") =>";
    return out; // 告诉queue如何打印这种数据类型
}
#endif chapter9_wirePosition_