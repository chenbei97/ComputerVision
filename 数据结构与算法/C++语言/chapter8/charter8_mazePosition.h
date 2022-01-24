#pragma once
#ifndef charter8_mazePosition_
#define charter8_mazePosition_
struct mazePosition
{
    int row, 
        col;  
    operator int() const { return row; } // Ç¿×ª×ª»»,·µ»ØËùÔÚÐÐ
};
std::ostream& operator<<(std::ostream& out, const mazePosition& x)
{
    out << "(" << x.row << "," << x.col << ") =>";
    return out; // 告诉stack如何打印这种数据类型
}
#endif charter8_mazePosition_
