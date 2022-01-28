#include <iostream>
#include "chapter9_arrayQueue.h"
#include "chapter8_make2dArray.h"
#include "chapter9_pixelPosition.h"
using namespace std;
int imageSize;
int** imageGrid; // ��άͼƬ
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
    // ���ڴ洢��here���ڵ�����λ��,Ϊ��˵���Ѿ�û�б��Ϊ1������
    arrayQueue<pixelPosition> q; 
    pixelPosition here, nbr;
    int id = 1; // δ��ǵ����ض���1����0

    for (int r = 1; r <= imageSize; r++)      
        for (int c = 1; c <= imageSize; c++)   
            if (imageGrid[r][c] == 1) // ����ÿ������,����ҵ����1��
            {
                imageGrid[r][c] = ++id; //�ͱ�Ǹ�����Ϊ��1��id=2,3,4...ȡ�������طֲ�
                here.row = r;
                here.col = c;

                while (true)
                {
                    for (int i = 0; i < numOfNbrs; i++) // ����here��Χ����������
                    {
                        nbr.row = here.row + offset[i].row;
                        nbr.col = here.col + offset[i].col;
                        if (imageGrid[nbr.row][nbr.col] == 1) // ����������û��ǵ�
                        {
                            imageGrid[nbr.row][nbr.col] = id; // �����
                            q.push(nbr); // ����¼��,q��¼���Ļ���˵��ǹ������ز����ٴ�����if����
                        }
                    }

                    if (q.empty()) break; // ֱ��q�����б�ǹ�������˵�������������ض��Ѿ���ǹ�
                    here = q.front(); // ��here�ƶ�������ӵ����ڵı�ǹ�������
                    q.pop(); // ԭ����ӹ��������Ѿ���ǹ�,���ܱ����ڵ�Ҳ�Ѿ���ǹ�,pop�����ٴ��ظ�
                }
            } 
}
void outputImage()
{
    cout << "The pixel distribution after the image is marked is as follows~" << endl;
    welcomeImage(); // �ٴ��������
}