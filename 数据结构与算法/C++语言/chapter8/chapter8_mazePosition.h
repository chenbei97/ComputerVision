#pragma once
#ifndef chapter8_mazePosition_
#define chapter8_mazePosition_
struct mazePosition
{
    int row, 
        col;  
    operator int() const { return row; } // ǿתת��,����������
};
std::ostream& operator<<(std::ostream& out, const mazePosition& x)
{
    out << "(" << x.row << "," << x.col << ") =>";
    return out; // ����stack��δ�ӡ������������
}
#endif chapter8_mazePosition_
