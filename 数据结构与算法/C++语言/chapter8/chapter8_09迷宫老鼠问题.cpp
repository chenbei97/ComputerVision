#include "chapter8_arrayStack.h"
#include "chapter8_mazePosition.h"
#include "chapter8_make2dArray.h"
#include <iostream>
using namespace std;
int** maze, mazeSize;
arrayStack<mazePosition>* mazePath;
void welcome(); 
void inputMaze();
bool findPath();
void outputPath();
void _chapter8_maze_mouse()
{
    inputMaze();
	welcome(); // 游戏开始需要欢迎界面
    if (findPath())
        outputPath();
    else
        cout << "No path" << endl;

}
void inputMaze()
{
    // 可以用户手动输入也可以直接定义
    //cout << "Enter maze size" << endl;
    //cin >> mazeSize;
    //make2dArray(maze, mazeSize + 2, mazeSize + 2);
    //cout << "Enter maze in row major order" << endl;
    //for (int i = 1; i <= mazeSize; i++)
    //    for (int j = 1; j <= mazeSize; j++)
    //        cin >> maze[i][j];

    // 为了方便测试代码,这里直接给出书P199页图8-15那样的迷宫
    mazeSize = 10;
    make2dArray(maze, mazeSize + 2, mazeSize + 2);
    for (int row = 0; row < mazeSize + 2; row++)
        for (int col = 0; col < mazeSize + 2; col++)
            maze[row][col] = 0; //初始化为0
    // 设置迷宫外部障碍(0行,0列,maze+1行,maze+1列为1)
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
    // 设置迷宫内部障碍
    maze[1][2] = 1; maze[1][3] = 1; maze[1][4] = 1; maze[1][5] = 1; maze[1][6] = 1;// 第1行
    maze[2][2] = 1; maze[2][6] = 1; maze[2][8] = 1; maze[2][9] = 1;// 第2行
    maze[3][4] = 1; maze[3][6] = 1; maze[3][9] = 1;// 第3行
    maze[4][2] = 1; maze[4][4] = 1; maze[4][6] = 1; maze[4][8] = 1; maze[4][9] = 1;// 第4行
    maze[5][2] = 1;  maze[5][4] = 1; maze[5][6] = 1; maze[5][8] = 1;// 第5行
    maze[6][2] = 1; maze[6][3] = 1; maze[6][4] = 1; maze[6][6] = 1; maze[6][8] = 1; maze[6][10] = 1;// 第6行
    maze[7][2] = 1; maze[7][6] = 1; maze[7][8] = 1; maze[7][10] = 1;// 第7行
    maze[8][2] = 1; maze[8][4] = 1; maze[8][5] = 1; maze[8][6] = 1; maze[8][8] = 1;// 第8行
    maze[9][1] = 1; maze[9][8] = 1; // 第9行
    maze[10][5] = 1; maze[10][6] = 1; maze[10][7] = 1; maze[10][8] = 1;// 第10行
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
    // 路径寻找方向从入口(1,1)到出口(mazeSize,mazeSize),找到这样的路径返回true
    mazePath = new arrayStack<mazePosition>; // 只是1个指针,先开辟内存

    // 初始化偏置量方便计算位置坐标
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
    maze[1][1] = 1; // 设置障碍阻止返回
    int option = 0; // 下一次移动的方向
    int lastOption = 3; // 最后1个选项

    // 开始寻找路径
    while (here.row != mazeSize || here.col != mazeSize) // 没到达出口就继续移动
    {
        int r, c;
        while (option <= lastOption) // 4个方向都会尝试
        {
            r = here.row + offset[option].row;
            c = here.col + offset[option].col;
            cout << "(" << r << "," << c << ")" << " => ";
            if (maze[r][c] == 0) break;//说明位置(r,c)没有障碍就前进,不保证有2个可能的方向都是0
            option++;
        }
        if (option <= lastOption) // 说明确实找到1个没有障碍的方向
        {
            mazePath->push(here);//移动到maze[r][c],把该位置信息入栈
            here.row = r;
            here.col = c;
            maze[r][c] = 1; // 设置障碍保证不会返回这个位置
            option = 0; // 选项重置
        }
        else
        { // 周围都是障碍,唯一的选择是退回上一步,前提是有上一步
            if (mazePath->empty())
                return false;   // 没有可退回的方向就返回false
            mazePosition last = mazePath->top(); // 暂存上一步的位置信息
            mazePath->pop();// 路径删除上一步的位置信息
            if (last.row == here.row) // 退回的位置不是同行就是同列
            {
                option = 2 + last.col - here.col; 
                // 如果last在here左边,last.col - here.col=-1,对于last来说它无需再向右移动,要求option≠0
                // 如果last在here右边,last.col - here.col=1,对于last来说它无需再向左移动,要求option≠2
                // 假定option = x + last.col - here.col, 根据要求x-1≠0 && x+1≠2,故x≠1
                // 其实随便选1个方向就行,这里就是退回到左边时再尝试向上移动,退回到右边再尝试向下移动
                // 退到左边还取左边或者退到右边还取右边是可以的，即x取3时last.col - here.col=-1,x取-1时等于1
                // 退到左边还取左边即3-1=2(left)和退到右边还取右边-1+1=0(right)
                // 但这只是好的情况,如果x取3,但是退回的是右边不是左边,那等于option=4,
                // 又会删除1个元素,如此反复可能上下尝试可以找到的却永远找不到
                // x取-1退回的是左边而不是右边，则option=-2也会出错
                // 最后就是x取0,那么option可能等于-1或者1,如果是-1立刻越界出错,综上只能取2
            }
            else
            {
                option = 1 + last.row - here.row;
                // 如果last在here上边,last.col - here.col=-1,对于last来说它无需再向下移动,要求option≠1
               // 如果last在here下边,last.col - here.col=1,对于last来说它无需再向上移动,要求option≠3
               // 假定option = x + last.col - here.col, 根据要求x-1≠1 && x+1≠3,故x≠2
                // 同理退到上边还退上没问题,退上要求option=3,所以x=4才能4-1=3,但是x=4时,又不一定在上边,此时option=5越界
                // 退到下边还退下要求option=1,此时x+1=1,即x=0,但是可能在上边,option=-1,也会越界
                // 再看x=3,此时option可能等于4或者2,option=4运气不好一路后退找不到路径,本该可以左右尝试找到的也永远找不到
                // x=1,option可取0或者2,即向左或者向右再次尝试
            }
            here = last; // 回到上一步
        }
    }

    return true;
}
void outputPath()
{
    cout << "The path is" << endl;
    // 这样打印可以但是这是从出口到入口的打印方式看起来不太舒服
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

