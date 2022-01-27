#include <iostream>
#include <assert.h>
#include "chapter9_arrayQueue.h"
#include "chapter8_make2dArray.h"
#include "chapter9_wirePosition.h"
using namespace std;
// 目的寻找最短路径
int** wireGrid;       // 电路棋盘的二维数组(方阵)
int wireSize;         // 棋盘长度
wirePosition wireStart,   // 路径起点
wireFinish;  // 路径终点
arrayQueue<wirePosition> wirePath; // 用队列存储路径
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
    // 为了方便测试代码,这里直接设计1个电路布局,形状在welcome()会打印
    wireSize = 10;
    make2dArray(wireGrid, wireSize + 2, wireSize + 2);
    for (int row = 0; row < wireSize + 2; row++)
        for (int col = 0; col < wireSize + 2; col++)
            wireGrid[row][col] = 1; //初始化为1
    // 设置电路棋盘内部通道
    wireGrid[1][1] = 0; wireGrid[1][5] = 0; wireGrid[1][6] = 0; wireGrid[1][7] = 0; // 第1行
    wireGrid[2][1] = 0; wireGrid[2][2] = 0; wireGrid[2][3] = 0; wireGrid[2][4] = 0; wireGrid[2][5] = 0; wireGrid[2][7] = 0; wireGrid[2][8] = 0;// 第2行
    wireGrid[3][2] = 0; wireGrid[3][3] = 0; wireGrid[3][8] = 0;// 第3行
    wireGrid[4][3] = 0; wireGrid[4][4] = 0; wireGrid[4][8] = 0; wireGrid[4][9] = 0; wireGrid[4][10] = 0;// 第4行
    wireGrid[5][4] = 0; wireGrid[5][5] = 0; wireGrid[5][10] = 0; // 第5行
    wireGrid[6][5] = 0; wireGrid[6][6] = 0; wireGrid[6][9] = 0; wireGrid[6][10] = 0;// 第6行
    wireGrid[7][6] = 0; wireGrid[7][7] = 0; wireGrid[7][7] = 0; wireGrid[7][9] = 0; // 第7行
    wireGrid[8][7] = 0; wireGrid[8][8] = 0; wireGrid[8][9] = 0; wireGrid[8][10] = 0; // 第8行
    wireGrid[9][8] = 0; wireGrid[9][9] = 0; wireGrid[9][10] = 0;// 第9行
    wireGrid[10][9] = 0; wireGrid[10][10] = 0; // 第10行

    wireStart.col = wireStart.row = 1;
    wireFinish.col = wireFinish.row = wireSize;
    cout << "welcome into this wireGrid! The wireGrid shape is as follows " << endl;
}
bool findWirePath()
{
    cout << "Start looking for a path? If yes, please hit enter" << endl;
    system("pause");
    // 与迷宫老鼠找到一条路径不同，还要找到最短的路径
    if ((wireStart.row == wireFinish.row) && (wireStart.col == wireFinish.col))
        return true;
    wirePosition offset[4];
    offset[0].row = 0; offset[0].col = 1;   // right
    offset[1].row = 1; offset[1].col = 0;   // down
    offset[2].row = 0; offset[2].col = -1;  // left
    offset[3].row = -1; offset[3].col = 0;  // up
    

    // 寻找最短路径需要2个过程,1个是距离标记,1个是路径标记
    // 距离标记是以起点开始记为0,它相邻的方格标记为1,1相邻的方格都标注为2
    // 以此类推,直到重点,那么终点的距离标记就是从起点到终点的距离
    // 路径标记可以使用队列wireQueue存储
    // 距离标记可以使用另外1个二维数组存储距离,但是会耗费较大的内存
    // 所以可以考虑重用wireGrid来存储,但是编号1会有冲突,1可以看成是1个障碍也可以看成是距离标记1
    // 为了表面冲突,障碍用1表示,但是起点不从0开始而是从2开始,那么wireGrid[i][j]>1表示1个位置
    // 这个位置到起点的距离是wireGrid[i][j]-2,例如起点相邻的位置路径标记为3,它到起点的距离就是1
    // 非障碍且没有到达的位置是0,障碍位置为1,非障碍已到达位置为路径距离标记
    wirePosition here = wireStart; // 目前的位置在起点处
    wireGrid[wireStart.row][wireStart.col] = 2; // 标记起点距离标志为2
    int numOfNbrs = 4; // here的位置相邻有4个方格
    arrayQueue<wirePosition> wireQueue;//用于存储到达每个位置时相邻位置的路径标记
    wirePosition nbr; // 相邻的位置
    do
    {  // 每到1个位置就标记周边的4个方格
        for (int i = 0; i < numOfNbrs; i++) // 遍历每个邻居来进行路径距离标记
        {
            nbr.row = here.row + offset[i].row; // 依次使用4个偏置(→↓←↑)
            nbr.col = here.col + offset[i].col;
            if (wireGrid[nbr.row][nbr.col] == 0) // 非障碍且未到达位置才能进行路径标记
            {
                wireGrid[nbr.row][nbr.col]
                    = wireGrid[here.row][here.col] + 1; // 相邻位置的距离只需+1
                if ((nbr.row == wireFinish.row) &&
                    (nbr.col == wireFinish.col)) break; // 标记1个位置就要判断这个位置是不是终点
                wireQueue.push(nbr); // 标记过的位置都会被存储
            }
        }
        // 为什么多加1步终点判断?
        // 假设here就是wireFinsh,它能到达这里,说明它的相邻位置不是>1的就距离标记就是障碍1
        // 那么上边的for循环中,第1个if判断都不成立,所以也不会有后面的终点判断
        // 到达终点但do-while循环没有退出,再执行后面的程序会出错
        if ((nbr.row == wireFinish.row) &&
            (nbr.col == wireFinish.col)) break;  

        // wireQueue能是空的说明没有位置被距离标记过,只有障碍1,没有路径
        if (wireQueue.empty())
            return false; 
        // 因为邻居是右下左上方向遍历的,最好的情况是有4个方向都可以走,那么wireQueue最多会存4个位置
        // 优先级也是优先向右移动(如果右边可以移动的话)
        here = wireQueue.front(); // 每个可以移动的方向都尝试,here一旦更改wireQueue又会更改
        wireQueue.pop(); // 尝试1个就删除1个,最后所有可能的方向都会遍历过且会到达终点
    } while (true);

    // 如果这样的路径存在的话,here已经到达了wireFinsh
    // do-while循环中已经改变了wireGrid[10][10]的距离标记
    int wirePathLength = wireGrid[wireFinish.row][wireFinish.col] - 2; // 获取路径长度

    here = wireFinish; // 从终点开始回溯路径
    // 根据距离标记来找路径,最短路径是连续的距离标记
    for (int j = wirePathLength - 1; j >= 0; j--) // 本例预计wirePathLength=18,数组从17-0记录
    {
        wirePath.push(here);
        for (int i = 0; i < numOfNbrs; i++) // 终点周边的4个位置
        {
            nbr.row = here.row + offset[i].row;
            nbr.col = here.col + offset[i].col;
            // 在do-while找到路径的前提下,如观察P217图9-13
            // 回溯过程比当前位置距离标记小的且相同的最多有2个位置
            // 这个情况说明有2条最短路径,但是都一样短为18步,对于距离而言没有区别
            // 本例设计的也有2条最短路径,位置(9,9)->(9,10)->(10,10)或者(9,9)->(10,9)->(10,10)
            // do-while过程已经对(9,9)的相邻位置都标注为19,即(9,10)和(9,10)的距离标记都是19
            if (wireGrid[nbr.row][nbr.col] == j + 2) break; 
            // 最多有2个等于19,但是因为遍历的方向优先级左>上,所以最短路径选择了(9,9)<-(10,9)<-(10,10)
        }
        here = nbr;  // 找到标记19后就让here移动到它这里
    }
    assert(wirePathLength == wirePath.size()); // 路径长度必然等于size()
    return true;
}
void outputWirePath()
{
    cout << "The wire path is" << endl;
    cout << "wireFinsh => " << wirePath << "(1,1) => wireStart" << endl;
    cout << "wireGrid has changed! The wireGrid shape is as follows " << endl;
    welcomeWire(); // 再次调用观察wireGrid的真实布局
}