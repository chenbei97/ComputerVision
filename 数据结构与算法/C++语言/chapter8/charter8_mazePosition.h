#pragma once
#ifndef charter8_mazePosition_
#define charter8_mazePosition_
struct mazePosition
{
    int row, 
        col;  
    operator int() const { return row; } // ǿתת��,����������
};
#endif charter8_mazePosition_
