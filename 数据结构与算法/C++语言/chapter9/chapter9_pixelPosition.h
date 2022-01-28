#pragma once
#ifndef chapter9_pixelPosition_
#define chapter9_pixelPosition_
struct pixelPosition
{
    int row,
        col;
};
std::ostream& operator<<(std::ostream& out, const pixelPosition& x)
{
    out << "(" << x.row << "," << x.col << ") =>";
    return out; // 告诉queue/stack如何打印这种数据类型
}
#endif chapter9_pixelPosition_
