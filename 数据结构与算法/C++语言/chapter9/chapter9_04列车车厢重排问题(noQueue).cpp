#include <iostream>
using namespace std;
// 本cpp文件基本保留了书原始代码,没有修改函数名,只对全局变量加了C9防止变量名重复
int* whichTrackC9;  // 1≤i≤numberOfCarsC9,whichTrackC9[i]是车厢i去的缓存车道,1≤whichTrackC9[i]≤numberOfTracksC9-1
int* lastCarC9;     // 1≤i≤numberOfTracksC9-1,lastCarC9[i]是缓冲道i存储的最后1个车厢编号,本身是1≤lastCarC9[i]≤numberOfCarsC9
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

    // 初始化每个缓冲道和尾部车厢编号,全部为0
    //每缓存1个车厢c,都要记录它最合适的缓冲道索引whichTrackC9[c]
    // 以及根据c的编号大小更新这个缓冲车道的最后1个车厢编号lastCarC9[whichTrackC9[c]]
    lastCarC9 = new int[numberOfTracksC9 + 1]; // 每个缓冲道都有1个尾部车辆,这个缓存车道可以没有车,那么lastCarC9[i]保持=0
    fill(lastCarC9 + 1, lastCarC9 + numberOfTracksC9 + 1, 0); // 初始化为0,只用到[1,numberOfTracksC9],即缓冲道索引是下标1开始计数的比较方便
    whichTrackC9 = new int[numberOfCarsC9 + 1]; // whichTrackC9[c] 表示c应该去向的车道是whichTrackC9[c]
    fill(whichTrackC9 + 1, whichTrackC9 + numberOfCarsC9 + 1, 0); // 初始化都是0
    int nextCarToOutput = 1;

    for (int i = 1; i <= numberOfCarsC9; i++) // 遍历每个车辆
        if (inputOrder[i] == nextCarToOutput) // 如果输入的车厢就是下一个要输出的
        {
            cout << "Move car " << inputOrder[i] << " from input "
                << "track to output track" << endl;
            nextCarToOutput++;
            while (nextCarToOutput <= numberOfCarsC9 && // 下1个车厢编号不要越界
                whichTrackC9[nextCarToOutput] != 0) // 这个车厢对应的最合适缓冲道不能为0,为0说明没有车移除应该执行下边的缓存操作才对
            {
                outputFromHoldingTrack(nextCarToOutput); // 移除这个车厢
                nextCarToOutput++; // 继续下1辆
            }
        }
        else // 如果不是,给车厢i寻找合适的缓冲道,记录在whichTrackC9[i]
            if (!putInHoldingTrack(inputOrder[i]))
                return false;

    return true;
}

void outputFromHoldingTrack(int c)
{
    // 能进入此函数的前提是车厢c找到了合适的缓冲车道,即whichTrack[i]!=0
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
        if (lastCarC9[i] != 0) // 先从非空的缓冲道寻找合适的,i=1,2,有元素不会等于0
        {   
            if (c > lastCarC9[i] && lastCarC9[i] > bestLast) 
            {
                // c > lastCarC9[i]是第1个要求,至少c得比缓存道的车厢编号大才能被继续缓存
                // lastCarC9[i] > bestLast是第2个要求,可能2个缓存道都合适,那就需要比较这2个缓存道的尾部车厢
                // bestLast用于记录满足条件的缓存道的尾部车厢编号更大的那个,更大的那个更接近车厢c,初始时为0
                bestLast = lastCarC9[i]; // lastCarC9[i]就是个车厢编号,记录它,它目前是最大的车厢编号
                bestTrack = i; // 记录当前最大车厢编号所属的缓冲道
            }
        }
        else // 没有合适的非空缓冲道就用空缓冲道
            if (bestTrack == 0)
                bestTrack = i;

    if (bestTrack == 0) // 空缓冲道也没有则重排失败
        return false; 

    whichTrackC9[c] = bestTrack; // 找到了车厢c最合适的缓存车道,记录在whichTrackC9中
    lastCarC9[bestTrack] = c; // 更新这个车道的尾部车厢编号为c,因为是车厢c被缓存
    // 刚进入时c=3,i=1,bestTrack=1,whichTrack[3]=1,lastCar[1]=3,i=2,3没有运行
    // 再次进入c=6,i=1,lastCar[1]=3不为空,c=6>3 && 3 > 0,所以bestLast=3,bestTrack=1,whichTrack[6]=1,lastCar[1]=6
    // c=9,同理在i=1就成立了, 9>lastCar[1]=6 &&  6>3
    cout << "Move car " << c << " from input track "
        << "to holding track " << bestTrack << endl;
    return true;
}
