#include <iostream>
#include <assert.h>
#include "chapter9_arrayQueue.h"
#include "chapter8_make2dArray.h"
#include "chapter9_wirePosition.h"
using namespace std;
// Ŀ��Ѱ�����·��
int** wireGrid;       // ��·���̵Ķ�ά����(����)
int wireSize;         // ���̳���
wirePosition wireStart,   // ·�����
wireFinish;  // ·���յ�
arrayQueue<wirePosition> wirePath; // �ö��д洢·��
void welcomeWire();
void inputWireGrid();
bool findWirePath();
void outputWirePath();
void _chapter9_circuit_wiring()
{
    inputWireGrid();
    welcomeWire();
    if (findWirePath())
        outputWirePath();
    else
        cout << "There is no wire path" << endl;
}
void welcomeWire()
{
    for (int row = -1; row < wireSize + 2; row++)
    {
        for (int col = -1; col < wireSize + 2; col++)
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
                if (row == 0 || row == wireSize + 1 || col == 0 || col == wireSize + 1)
                    cout << wireGrid[row][col] << ".   ";
                else
                    cout << wireGrid[row][col] << "    ";
        }

        cout << endl;
    }
}
void inputWireGrid()
{
    //cout << "Enter grid size" << endl;
    //cin >> wireSize;
    //cout << "Enter the start position" << endl;
    //cin >> wireStart.row >> wireStart.col;
    //cout << "Enter the finish position" << endl;
    //cin >> wireFinish.row >> wireFinish.col;
    //make2dArray(wireGrid, wireSize + 2, wireSize + 2);
    //cout << "Enter the wiring grid in row-major order" << endl;
    //for (int i = 1; i <= wireSize; i++)
    //    for (int j = 1; j <= wireSize; j++)
    //        cin >> wireGrid[i][j];
    // Ϊ�˷�����Դ���,����ֱ�����1����·����,��״��welcome()���ӡ
    wireSize = 10;
    make2dArray(wireGrid, wireSize + 2, wireSize + 2);
    for (int row = 0; row < wireSize + 2; row++)
        for (int col = 0; col < wireSize + 2; col++)
            wireGrid[row][col] = 1; //��ʼ��Ϊ1
    // ���õ�·�����ڲ�ͨ��
    wireGrid[1][1] = 0; wireGrid[1][5] = 0; wireGrid[1][6] = 0; wireGrid[1][7] = 0; // ��1��
    wireGrid[2][1] = 0; wireGrid[2][2] = 0; wireGrid[2][3] = 0; wireGrid[2][4] = 0; wireGrid[2][5] = 0; wireGrid[2][7] = 0; wireGrid[2][8] = 0;// ��2��
    wireGrid[3][2] = 0; wireGrid[3][3] = 0; wireGrid[3][8] = 0;// ��3��
    wireGrid[4][3] = 0; wireGrid[4][4] = 0; wireGrid[4][8] = 0; wireGrid[4][9] = 0; wireGrid[4][10] = 0;// ��4��
    wireGrid[5][4] = 0; wireGrid[5][5] = 0; wireGrid[5][10] = 0; // ��5��
    wireGrid[6][5] = 0; wireGrid[6][6] = 0; wireGrid[6][9] = 0; wireGrid[6][10] = 0;// ��6��
    wireGrid[7][6] = 0; wireGrid[7][7] = 0; wireGrid[7][7] = 0; wireGrid[7][9] = 0; // ��7��
    wireGrid[8][7] = 0; wireGrid[8][8] = 0; wireGrid[8][9] = 0; wireGrid[8][10] = 0; // ��8��
    wireGrid[9][8] = 0; wireGrid[9][9] = 0; wireGrid[9][10] = 0;// ��9��
    wireGrid[10][9] = 0; wireGrid[10][10] = 0; // ��10��

    wireStart.col = wireStart.row = 1;
    wireFinish.col = wireFinish.row = wireSize;
    cout << "welcome into this wireGrid! The wireGrid shape is as follows " << endl;
}
bool findWirePath()
{
    cout << "Start looking for a path? If yes, please hit enter" << endl;
    system("pause");
    // ���Թ������ҵ�һ��·����ͬ����Ҫ�ҵ���̵�·��
    if ((wireStart.row == wireFinish.row) && (wireStart.col == wireFinish.col))
        return true;
    wirePosition offset[4];
    offset[0].row = 0; offset[0].col = 1;   // right
    offset[1].row = 1; offset[1].col = 0;   // down
    offset[2].row = 0; offset[2].col = -1;  // left
    offset[3].row = -1; offset[3].col = 0;  // up
    

    // Ѱ�����·����Ҫ2������,1���Ǿ�����,1����·�����
    // ������������㿪ʼ��Ϊ0,�����ڵķ�����Ϊ1,1���ڵķ��񶼱�עΪ2
    // �Դ�����,ֱ���ص�,��ô�յ�ľ����Ǿ��Ǵ���㵽�յ�ľ���
    // ·����ǿ���ʹ�ö���wireQueue�洢
    // �����ǿ���ʹ������1����ά����洢����,���ǻ�ķѽϴ���ڴ�
    // ���Կ��Կ�������wireGrid���洢,���Ǳ��1���г�ͻ,1���Կ�����1���ϰ�Ҳ���Կ����Ǿ�����1
    // Ϊ�˱����ͻ,�ϰ���1��ʾ,������㲻��0��ʼ���Ǵ�2��ʼ,��ôwireGrid[i][j]>1��ʾ1��λ��
    // ���λ�õ����ľ�����wireGrid[i][j]-2,����������ڵ�λ��·�����Ϊ3,�������ľ������1
    // ���ϰ���û�е����λ����0,�ϰ�λ��Ϊ1,���ϰ��ѵ���λ��Ϊ·��������
    wirePosition here = wireStart; // Ŀǰ��λ������㴦
    wireGrid[wireStart.row][wireStart.col] = 2; // ����������־Ϊ2
    int numOfNbrs = 4; // here��λ��������4������
    arrayQueue<wirePosition> wireQueue;//���ڴ洢����ÿ��λ��ʱ����λ�õ�·�����
    wirePosition nbr; // ���ڵ�λ��
    do
    {  // ÿ��1��λ�þͱ���ܱߵ�4������
        for (int i = 0; i < numOfNbrs; i++) // ����ÿ���ھ�������·��������
        {
            nbr.row = here.row + offset[i].row; // ����ʹ��4��ƫ��(��������)
            nbr.col = here.col + offset[i].col;
            if (wireGrid[nbr.row][nbr.col] == 0) // ���ϰ���δ����λ�ò��ܽ���·�����
            {
                wireGrid[nbr.row][nbr.col]
                    = wireGrid[here.row][here.col] + 1; // ����λ�õľ���ֻ��+1
                if ((nbr.row == wireFinish.row) &&
                    (nbr.col == wireFinish.col)) break; // ���1��λ�þ�Ҫ�ж����λ���ǲ����յ�
                wireQueue.push(nbr); // ��ǹ���λ�ö��ᱻ�洢
            }
        }
        // Ϊʲô���1���յ��ж�?
        // ����here����wireFinsh,���ܵ�������,˵����������λ�ò���>1�ľ;����Ǿ����ϰ�1
        // ��ô�ϱߵ�forѭ����,��1��if�ж϶�������,����Ҳ�����к�����յ��ж�
        // �����յ㵫do-whileѭ��û���˳�,��ִ�к���ĳ�������
        if ((nbr.row == wireFinish.row) &&
            (nbr.col == wireFinish.col)) break;  

        // wireQueue���ǿյ�˵��û��λ�ñ������ǹ�,ֻ���ϰ�1,û��·��
        if (wireQueue.empty())
            return false; 
        // ��Ϊ�ھ����������Ϸ��������,��õ��������4�����򶼿�����,��ôwireQueue�����4��λ��
        // ���ȼ�Ҳ�����������ƶ�(����ұ߿����ƶ��Ļ�)
        here = wireQueue.front(); // ÿ�������ƶ��ķ��򶼳���,hereһ������wireQueue�ֻ����
        wireQueue.pop(); // ����1����ɾ��1��,������п��ܵķ��򶼻�������һᵽ���յ�
    } while (true);

    // ���������·�����ڵĻ�,here�Ѿ�������wireFinsh
    // do-whileѭ�����Ѿ��ı���wireGrid[10][10]�ľ�����
    int wirePathLength = wireGrid[wireFinish.row][wireFinish.col] - 2; // ��ȡ·������

    here = wireFinish; // ���յ㿪ʼ����·��
    // ���ݾ���������·��,���·���������ľ�����
    for (int j = wirePathLength - 1; j >= 0; j--) // ����Ԥ��wirePathLength=18,�����17-0��¼
    {
        wirePath.push(here);
        for (int i = 0; i < numOfNbrs; i++) // �յ��ܱߵ�4��λ��
        {
            nbr.row = here.row + offset[i].row;
            nbr.col = here.col + offset[i].col;
            // ��do-while�ҵ�·����ǰ����,��۲�P217ͼ9-13
            // ���ݹ��̱ȵ�ǰλ�þ�����С������ͬ�������2��λ��
            // ������˵����2�����·��,���Ƕ�һ����Ϊ18��,���ھ������û������
            // ������Ƶ�Ҳ��2�����·��,λ��(9,9)->(9,10)->(10,10)����(9,9)->(10,9)->(10,10)
            // do-while�����Ѿ���(9,9)������λ�ö���עΪ19,��(9,10)��(9,10)�ľ����Ƕ���19
            if (wireGrid[nbr.row][nbr.col] == j + 2) break; 
            // �����2������19,������Ϊ�����ķ������ȼ���>��,�������·��ѡ����(9,9)<-(10,9)<-(10,10)
        }
        here = nbr;  // �ҵ����19�����here�ƶ���������
    }
    assert(wirePathLength == wirePath.size()); // ·�����ȱ�Ȼ����size()
    return true;
}
void outputWirePath()
{
    cout << "The wire path is" << endl;
    cout << "wireFinsh => " << wirePath << "(1,1) => wireStart" << endl;
    cout << "wireGrid has changed! The wireGrid shape is as follows " << endl;
    welcomeWire(); // �ٴε��ù۲�wireGrid����ʵ����
}