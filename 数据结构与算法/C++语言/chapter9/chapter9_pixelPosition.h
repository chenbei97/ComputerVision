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
    return out; // ����queue/stack��δ�ӡ������������
}
#endif chapter9_pixelPosition_
