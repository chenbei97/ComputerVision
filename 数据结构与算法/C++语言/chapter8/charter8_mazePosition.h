#pragma once
#ifndef charter8_mazePosition_
#define charter8_mazePosition_
struct mazePosition
{
    int row, 
        col;  
    operator int() const { return row; } // 强转转换,返回所在行
};
#endif charter8_mazePosition_
