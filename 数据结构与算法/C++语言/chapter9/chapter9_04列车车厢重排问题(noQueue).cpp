#include <iostream>
using namespace std;
// 本cpp文件基本保留了书原始代码,没有修改函数名,只对全局变量加了C9防止变量名重复
int* whichTrackC9;  // 车厢属于的缓冲车道(指针),可以存多个缓冲车道,whichTrackC9[i]是1个车道,下标1开始
int* lastCarC9;     // 缓冲车道最后1个车厢的编号(指针),whichTrackC9[i]对应lastCarC9[i]
int numberOfCarsC9; // 总的车辆数
int numberOfTracksC9; // 总的缓冲道数
void outputFromHoldingTrack(int);
bool putInHoldingTrack(int);
bool railroad(int*, int, int);
void _chapter9_carriageRearrange_noQueue()
{
    const int nCars = 9; // 9节车厢
    const int nTracks = 3; // 3个缓冲道
    int permutation[nCars + 1] = { 0, 3,6,9,2,4,7,1,8,5 }; // 数组小标0的位置不用,从1开始比较方便
    cout << "Input permutation is 581742963" << endl; // 初始的输入排列
    railroad(permutation, 9, 3);
    cout << "Output permutation is 123456789" << endl; // 初始的输入排列
}

bool railroad(int* inputOrder,int theNumberOfCars, int theNumberOfTracks)
{
    numberOfCarsC9 = theNumberOfCars;
    numberOfTracksC9 = theNumberOfTracks - 1; // 有1个是不作为缓冲道的

    // 初始化每个缓冲道和尾部车厢编号,全部为0,每个车险都有自己的缓冲道(所以效率低..)
    lastCarC9 = new int[numberOfTracksC9 + 1]; // 每个缓冲道都有1个尾部车辆,可以没有,那么lastCarC9[i]保持=0
    fill(lastCarC9 + 1, lastCarC9 + numberOfTracksC9 + 1, 0); // 初始化为0,只用到[1,numberOfTracksC9],即缓冲道是下标1开始计数的比较方便
    whichTrackC9 = new int[numberOfCarsC9 + 1]; // 缓冲道同理进行0初始化
    fill(whichTrackC9 + 1, whichTrackC9 + numberOfCarsC9 + 1, 0);
    int nextCarToOutput = 1;

    for (int i = 1; i <= numberOfCarsC9; i++) // 遍历每个车辆
        if (inputOrder[i] == nextCarToOutput) // 如果输入的车厢就是下一个要输出的
        {
            cout << "Move car " << inputOrder[i] << " from input "
                << "track to output track" << endl;
            nextCarToOutput++;
            while (nextCarToOutput <= numberOfCarsC9 && // 下1个车厢编号不要越界
                whichTrackC9[nextCarToOutput] != 0) // 下个车厢对应的缓冲道不为0,说明这个缓冲道有这个车厢
            {
                outputFromHoldingTrack(nextCarToOutput); // 移除这个车厢
                nextCarToOutput++; // 继续下1辆
            }
        }
        else // 如果不是,就把这个车厢送到和它对应的那个缓冲道
            // inputOrder[i] to whichTrackC9[i]
            if (!putInHoldingTrack(inputOrder[i]))
                return false;

    return true;
}

void outputFromHoldingTrack(int c)
{
    // 可以看出,与使用栈和队列的方法相比,此函数多了一个形参,即车厢编号
    cout << "Move car " << c << " from holding track "
        << whichTrackC9[c] << " to output track" << endl;

    // 如果要移出的车厢c现在是缓冲车道的最后1个
    if (c == lastCarC9[whichTrackC9[c]]) // whichTrackC9[c]得到的是c最合适的缓冲道索引即bestTrack
        // lastCarC9[bestTrack] 得到的应该是这个合适的缓冲索引应该存放的车厢
        lastCarC9[whichTrackC9[c]] = 0; // 如果两者相等了,就可以移除车厢,重置为0 
}

bool putInHoldingTrack(int c)
{
    int bestTrack = 0,  // 初始化最合适的缓冲道为0
        bestLast = 0;  // 初始化最合适的缓冲道的尾部车厢编号为0

    for (int i = 1; i <= numberOfTracksC9; i++) // 遍历每个缓冲道
        if (lastCarC9[i] != 0) // 缓冲道whichTrack[i]如果没有元素则lastCarC9会等于0,反之说明有元素
        {   
            // 优先进入非空缓冲道,执行下方判断,寻找最合适的非空缓冲道
            if (c > lastCarC9[i] && lastCarC9[i] > bestLast) // 要输出的车厢编号要比当前缓冲道的尾部车厢编号大
            {
                // bestLast一开始0,随着缓冲道的遍历,bestLast会找到所有缓冲道里边车厢编号最大的那个
                bestLast = lastCarC9[i]; // 更新最好的缓冲道尾部车厢编号
                bestTrack = i; // 与之对应的缓冲道编号
            }
        }
        else // 没有合适的非空缓冲道就用空缓冲道
            if (bestTrack == 0)
                bestTrack = i;

    if (bestTrack == 0) // 空缓冲道也没有则重排失败
        return false; 

    whichTrackC9[c] = bestTrack; // 把最合适的缓冲道索引存入这个车厢编号对应的位置
    lastCarC9[bestTrack] = c; // 车厢编号则存入它最合适对应的缓冲道索引
    // 刚进入时c=3,i=1,bestTrack=1,whichTrack[3]=1,lastCar[1]=3,i=2,3没有运行
    // 再次进入c=6,i=1,lastCar[1]=3不为空,c=6>3 && 3 > 0,所以bestLast=3,bestTrack=1,whichTrack[6]=1,lastCar[1]=6
    // c=9,同理在i=1就成立了, 9>lastCar[1]=6 &&  6>3
    cout << "Move car " << c << " from input track "
        << "to holding track " << bestTrack << endl;
    return true;
}