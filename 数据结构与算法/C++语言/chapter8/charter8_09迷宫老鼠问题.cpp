#include "charter8_arrayStack.h"
#include "charter8_mazePosition.h"
#include "charter8_make2dArray.h"
#include <iostream>
using namespace std;
int** maze, mazeSize;
arrayStack<mazePosition>* mazePath;
void welcome(); 
void inputMaze();
bool findPath();
void outputPath();
void _charter8_maze_mouse()
{
    inputMaze();
	welcome(); // ��Ϸ��ʼ��Ҫ��ӭ����
    if (findPath())
        outputPath();
    else
        cout << "No path" << endl;

}
void inputMaze()
{
    // �����û��ֶ�����Ҳ����ֱ�Ӷ���
    //cout << "Enter maze size" << endl;
    //cin >> mazeSize;
    //make2dArray(maze, mazeSize + 2, mazeSize + 2);
    //cout << "Enter maze in row major order" << endl;
    //for (int i = 1; i <= mazeSize; i++)
    //    for (int j = 1; j <= mazeSize; j++)
    //        cin >> maze[i][j];

    // Ϊ�˷�����Դ���,����ֱ�Ӹ�����P199ҳͼ8-15�������Թ�
    mazeSize = 10;
    make2dArray(maze, mazeSize + 2, mazeSize + 2);
    for (int row = 0; row < mazeSize + 2; row++)
        for (int col = 0; col < mazeSize + 2; col++)
            maze[row][col] = 0; //��ʼ��Ϊ0
    // �����Թ��ⲿ�ϰ�(0��,0��,maze+1��,maze+1��Ϊ1)
    for (int col = 0; col < mazeSize + 2; col++)
    {
        maze[0][col] = 1;
        maze[mazeSize+1][col] = 1;
    }
    for (int row = 0; row < mazeSize + 2; row++)
    {
        maze[row][0] = 1;
        maze[row][mazeSize + 1] = 1;
    }
    // �����Թ��ڲ��ϰ�
    maze[1][2] = 1; maze[1][3] = 1; maze[1][4] = 1; maze[1][5] = 1; maze[1][6] = 1;// ��1��
    maze[2][2] = 1; maze[2][6] = 1; maze[2][8] = 1; maze[2][9] = 1;// ��2��
    maze[3][4] = 1; maze[3][6] = 1; maze[3][9] = 1;// ��3��
    maze[4][2] = 1; maze[4][4] = 1; maze[4][6] = 1; maze[4][8] = 1; maze[4][9] = 1;// ��4��
    maze[5][2] = 1;  maze[5][4] = 1; maze[5][6] = 1; maze[5][8] = 1;// ��5��
    maze[6][2] = 1; maze[6][3] = 1; maze[6][4] = 1; maze[6][6] = 1; maze[6][8] = 1; maze[6][10] = 1;// ��6��
    maze[7][2] = 1; maze[7][6] = 1; maze[7][8] = 1; maze[7][10] = 1;// ��7��
    maze[8][2] = 1; maze[8][4] = 1; maze[8][5] = 1; maze[8][6] = 1; maze[8][8] = 1;// ��8��
    maze[9][1] = 1; maze[9][8] = 1; // ��9��
    maze[10][5] = 1; maze[10][6] = 1; maze[10][7] = 1; maze[10][8] = 1;// ��10��
}
void welcome()
{
    cout << "welcome into this maze! The maze shape is as follows " << endl;
    for (int row = -1; row < mazeSize + 2 ; row++)
    {
        for (int col = -1 ; col < mazeSize + 2; col++)
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
                if (row == 0 || row == mazeSize+1 || col == 0 || col == mazeSize+1)
                     cout << maze[row][col] << ".   ";
                else
                    cout << maze[row][col] << "    ";
        }
            
        cout << endl;
    }
    cout << "Start looking for a path? If yes, please hit enter" << endl;
    system("pause");
}
bool findPath()
{
    // ·��Ѱ�ҷ�������(1,1)������(mazeSize,mazeSize),�ҵ�������·������true
    mazePath = new arrayStack<mazePosition>; // ֻ��1��ָ��,�ȿ����ڴ�

    // ��ʼ��ƫ�����������λ������
    mazePosition offset[4];
    offset[0].row = 0; offset[0].col = 1;   // right
    offset[1].row = 1; offset[1].col = 0;   // down
    offset[2].row = 0; offset[2].col = -1;  // left
    offset[3].row = -1; offset[3].col = 0;  // up

    //offset[0].row = 0; offset[0].col = -1;   // left
    //offset[1].row = -1; offset[1].col = 0;   // up
    //offset[2].row = 0; offset[2].col = 1;  // right
    //offset[3].row = 1; offset[3].col = 0;  // down

    mazePosition here;
    here.row = 1;
    here.col = 1;
    maze[1][1] = 1; // �����ϰ���ֹ����
    int option = 0; // ��һ���ƶ��ķ���
    int lastOption = 3; // ���1��ѡ��

    // ��ʼѰ��·��
    while (here.row != mazeSize || here.col != mazeSize) // û������ھͼ����ƶ�
    {
        int r, c;
        while (option <= lastOption) // 4�����򶼻᳢��
        {
            r = here.row + offset[option].row;
            c = here.col + offset[option].col;
            cout << "(" << r << "," << c << ")" << " => ";
            if (maze[r][c] == 0) break;//˵��λ��(r,c)û���ϰ���ǰ��,����֤��2�����ܵķ�����0
            option++;
        }
        if (option <= lastOption) // ˵��ȷʵ�ҵ�1��û���ϰ��ķ���
        {
            mazePath->push(here);//�ƶ���maze[r][c],�Ѹ�λ����Ϣ��ջ
            here.row = r;
            here.col = c;
            maze[r][c] = 1; // �����ϰ���֤���᷵�����λ��
            option = 0; // ѡ������
        }
        else
        { // ��Χ�����ϰ�,Ψһ��ѡ�����˻���һ��,ǰ��������һ��
            if (mazePath->empty())
                return false;   // û�п��˻صķ���ͷ���false
            mazePosition last = mazePath->top(); // �ݴ���һ����λ����Ϣ
            mazePath->pop();// ·��ɾ����һ����λ����Ϣ
            if (last.row == here.row) // �˻ص�λ�ò���ͬ�о���ͬ��
            {
                option = 2 + last.col - here.col; 
                // ���last��here���,last.col - here.col=-1,����last��˵�������������ƶ�,Ҫ��option��0
                // ���last��here�ұ�,last.col - here.col=1,����last��˵�������������ƶ�,Ҫ��option��2
                // �ٶ�option = x + last.col - here.col, ����Ҫ��x-1��0 && x+1��2,��x��1
                // ��ʵ���ѡ1���������,��������˻ص����ʱ�ٳ��������ƶ�,�˻ص��ұ��ٳ��������ƶ�
                // �˵���߻�ȡ��߻����˵��ұ߻�ȡ�ұ��ǿ��Եģ���xȡ3ʱlast.col - here.col=-1,xȡ-1ʱ����1
                // �˵���߻�ȡ��߼�3-1=2(left)���˵��ұ߻�ȡ�ұ�-1+1=0(right)
                // ����ֻ�Ǻõ����,���xȡ3,�����˻ص����ұ߲������,�ǵ���option=4,
                // �ֻ�ɾ��1��Ԫ��,��˷����������³��Կ����ҵ���ȴ��Զ�Ҳ���
                // xȡ-1�˻ص�����߶������ұߣ���option=-2Ҳ�����
                // ������xȡ0,��ôoption���ܵ���-1����1,�����-1����Խ�����,����ֻ��ȡ2
            }
            else
            {
                option = 1 + last.row - here.row;
                // ���last��here�ϱ�,last.col - here.col=-1,����last��˵�������������ƶ�,Ҫ��option��1
               // ���last��here�±�,last.col - here.col=1,����last��˵�������������ƶ�,Ҫ��option��3
               // �ٶ�option = x + last.col - here.col, ����Ҫ��x-1��1 && x+1��3,��x��2
                // ͬ���˵��ϱ߻�����û����,����Ҫ��option=3,����x=4����4-1=3,����x=4ʱ,�ֲ�һ�����ϱ�,��ʱoption=5Խ��
                // �˵��±߻�����Ҫ��option=1,��ʱx+1=1,��x=0,���ǿ������ϱ�,option=-1,Ҳ��Խ��
                // �ٿ�x=3,��ʱoption���ܵ���4����2,option=4��������һ·�����Ҳ���·��,���ÿ������ҳ����ҵ���Ҳ��Զ�Ҳ���
                // x=1,option��ȡ0����2,��������������ٴγ���
            }
            here = last; // �ص���һ��
        }
    }

    return true;
}
void outputPath()
{
    cout << "The path is" << endl;
    // ������ӡ���Ե������Ǵӳ��ڵ���ڵĴ�ӡ��ʽ��������̫���
    //mazePosition here;
    //int idx = 0;
    //while (!mazePath->empty())
    //{
    //    here = mazePath->top();
    //    mazePath->pop();
    //    cout <<"(" <<here.row << ',' << here.col << ") <= ";
    //    idx++;
    //    if ((idx) % 10 == 0)
    //        cout << "\n";
    //}
    cout <<"entrance => "<< * mazePath << "(10,10) => exit" << endl;
}

