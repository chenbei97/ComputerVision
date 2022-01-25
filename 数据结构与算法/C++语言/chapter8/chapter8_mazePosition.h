#pragma once
#ifndef chapter8_mazePosition_
#define chapter8_mazePosition_
struct mazePosition
{
    int row, 
        col;  
    operator int() const { return row; } // 强转转换,返回所在行
};
std::ostream& operator<<(std::ostream& out, const mazePosition& x)
{
    out << "(" << x.row << "," << x.col << ") =>";
    return out; // 告诉stack如何打印这种数据类型
}
#endif chapter8_mazePosition_
