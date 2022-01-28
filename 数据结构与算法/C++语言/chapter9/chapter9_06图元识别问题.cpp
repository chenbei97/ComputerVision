#include <iostream>
#include "chapter9_arrayQueue.h"
#include "chapter8_make2dArray.h"
#include "chapter9_pixelPosition.h"
using namespace std;
int imageSize;
int** imageGrid; // 二维图片
void welcomeImage();
void inputImage();
void labelImage();
void outputImage();
void _chapter9_element_recognition()
{
    inputImage();
    welcomeImage();
    labelImage();
    outputImage();
}
void welcomeImage()
{
    for (int row = -1; row < imageSize + 2; row++)
    {
        for (int col = -1; col < imageSize + 2; col++)
        {
            if (row == -1 && col == -1)
                cout << "    ";
            else if (row == -1 && col > -1)
            {
                if (col > 9)
                    cout << col << "   ";
                else
                    cout << col << "    ";
            }
            else if (col == -1 && row > -1)
            {
                if (row > 9)
                    cout << row << "  ";
                else
                    cout << row << "   ";
            }
            else
                if (row == 0 || row == imageSize + 1 || col == 0 || col == imageSize + 1)
                    cout << imageGrid[row][col] << ".   ";
                else
                    cout << imageGrid[row][col] << "    ";
        }
        cout << endl;
    }
}
void inputImage()
{
    imageSize = 10;
    make2dArray(imageGrid, imageSize + 2, imageSize + 2);
    for (int row = 0; row < imageSize + 2; row++)
        for (int col = 0; col < imageSize + 2; col++)
            imageGrid[row][col] = 0; 
    imageGrid[1][1] = 1; imageGrid[1][2] = 1; imageGrid[1][3] = 1; imageGrid[1][4] = 1; 
    imageGrid[1][7] = 1; imageGrid[1][8] = 1; imageGrid[1][9] = 1; imageGrid[1][10] = 1;
    imageGrid[2][4] = 1; imageGrid[2][8] = 1; imageGrid[2][9] = 1; imageGrid[2][10] = 1;
    imageGrid[3][1] = 1; imageGrid[3][2] = 1; imageGrid[3][4] = 1; imageGrid[3][9] = 1; imageGrid[3][10] = 1;
    imageGrid[4][3] = 1; imageGrid[4][2] = 1; imageGrid[4][4] = 1; imageGrid[4][6] = 1; imageGrid[4][10] = 1;
    imageGrid[5][2] = 1; imageGrid[5][3] = 1; imageGrid[5][5] = 1; imageGrid[5][6] = 1; imageGrid[5][7] = 1;
    imageGrid[6][4] = 1; imageGrid[6][5] = 1; imageGrid[6][6] = 1; imageGrid[6][7] = 1; imageGrid[6][8] = 1;
    imageGrid[7][5] = 1; imageGrid[7][6] = 1; imageGrid[7][7] = 1; imageGrid[7][9] = 1; imageGrid[7][10] = 1;
    imageGrid[8][1] = 1; imageGrid[8][2] = 1; imageGrid[8][3] = 1; imageGrid[8][6] = 1; imageGrid[8][10] = 1;
    imageGrid[9][1] = 1; imageGrid[9][2] = 1; imageGrid[9][3] = 1; imageGrid[9][8] = 1; imageGrid[9][10] = 1;
    imageGrid[10][1] = 1; imageGrid[10][2] = 1; imageGrid[10][3] = 1; imageGrid[10][8] = 1; imageGrid[10][9] = 1; imageGrid[10][10] = 1;
    cout << "test image's pixel distribution as follows~" << endl;
}
void labelImage()
{
    cout << "Start marking the pixel distribution of the image~" << endl;
    pixelPosition offset[4];
    offset[0].row = 0; offset[0].col = 1;   // right
    offset[1].row = 1; offset[1].col = 0;   // down
    offset[2].row = 0; offset[2].col = -1;  // left
    offset[3].row = -1; offset[3].col = 0;  // up

    int numOfNbrs = 4;
    // 用于存储与here相邻的任意位置,为空说明已经没有标记为1的像素
    arrayQueue<pixelPosition> q; 
    pixelPosition here, nbr;
    int id = 1; // 未标记的像素都是1或者0

    for (int r = 1; r <= imageSize; r++)      
        for (int c = 1; c <= imageSize; c++)   
            if (imageGrid[r][c] == 1) // 遍历每个像素,如果找到标记1的
            {
                imageGrid[r][c] = ++id; //就标记该像素为下1个id=2,3,4...取决于像素分布
                here.row = r;
                here.col = c;

                while (true)
                {
                    for (int i = 0; i < numOfNbrs; i++) // 遍历here周围的相邻像素
                    {
                        nbr.row = here.row + offset[i].row;
                        nbr.col = here.col + offset[i].col;
                        if (imageGrid[nbr.row][nbr.col] == 1) // 相邻像素有没标记的
                        {
                            imageGrid[nbr.row][nbr.col] = id; // 标记它
                            q.push(nbr); // 并记录它,q记录过的或者说标记过的像素不会再次满足if条件
                        }
                    }

                    if (q.empty()) break; // 直到q不再有标记过的像素说明所有相邻像素都已经标记过
                    here = q.front(); // 让here移动到新添加的相邻的标记过的像素
                    q.pop(); // 原来添加过的像素已经标记过,它周边相邻的也已经标记过,pop无需再次重复
                }
            } 
}
void outputImage()
{
    cout << "The pixel distribution after the image is marked is as follows~" << endl;
    welcomeImage(); // 再次输出即可
}