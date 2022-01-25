#include <iostream>
#include "chapter9_arrayQueue.h"
using namespace std;
arrayQueue<int>* trackC9; // 全局队列指针,动态的开辟指定数量的缓冲轨道
arrayQueue<int> sortedCarriageC9; // 排序好的车厢存放处
int nCarsC9; // 给定的车厢数
int nTracksC9; // 给定的缓冲轨道数
int smallestNumC9; // 缓冲轨道最小的车厢编号
int belongToTrackC9; // 最小的车厢编号所属的缓冲轨道编号
bool carriageRearrangeC9(int*, int, int);
void moveInOutputTrackC9();
bool moveInBufferTrackC9(int);
void _chapter9_carriageRearrange()
{
    const int nCars = 9; // 9节车厢
    const int nTracks = 3; // 3个缓冲道
    int permutation[nCars + 1] = { 0, 3,6,9,2,4,7,1,8,5 }; // 数组小标0的位置不用,从1开始比较方便
    cout << "Input permutation is 581742963" << endl; // 初始的输入排列
    if (carriageRearrangeC9(permutation, 9, 3))
    {
        cout << "carriage rearrange is successful, permutation is : \n"
            << sortedCarriageC9 << endl;
    }
    else { cout << "carriage rearrange is failed " << endl; }
}
bool carriageRearrangeC9(int* permutation, int nCars, int nTracks)
{
	nCarsC9 = nCars;
	nTracksC9 = nTracks - 1;// 有1个通道是用于直接输出车厢的
    trackC9 = new arrayQueue<int>[nTracks]; // 为这些缓冲通道开辟内存
    int nextCarToOutput = 1; // 初始化下一个应该输出的车厢编号为1
    smallestNumC9 = nCarsC9 + 1;  // 随便给个数初始化,目前的最小编号是10

    for (int i = 1; i <= nCarsC9; i++) // 从1遍历是因为permution[0]没用
        if (permutation[i] == nextCarToOutput) // 如果正好就是下1个直接输出
        {
            cout << "move car " << permutation[i] << " to output track" << endl;
            sortedCarriageC9.push(permutation[i]);
            nextCarToOutput++;

            // 如果缓冲道没车厢执行上方程序就结束了
            // 如果有车厢,因为nextCarToOutput已经++,继续判断缓冲道是否存在下一个该输出的车厢
            while (smallestNumC9 == nextCarToOutput) // 如果有
            {
                moveInOutputTrackC9(); // 把车厢从缓冲道移出
                nextCarToOutput++; // 更新下一个该出的车厢编号
                if (smallestNumC9 == nCarsC9 + 1) // 防止smallestNumC9=10,且nextCarToOutput也等于10退不出循环
                    break;
            }
            
        }
        else // 如果不是应该出的车厢就移入缓冲道
            if (!moveInBufferTrackC9(permutation[i])) // 移入成功就继续下一个输入轨道的车厢
                return false; // 移入失败就重排失败

    return true;

}
bool moveInBufferTrackC9(int nextCar)
{
    // 目的是为了找到最合适的缓冲道给下一个输入车厢
    // 输入车厢能去的缓冲道有2个选择,一个是空缓冲道,一个是非空缓冲道但是里边的车厢编号都小于nextCar
    // 因为trackC9[i].back()是最大的,所以让它和nextCar比较就可以了
    // 如果确实有这样的非空缓冲道,也有空缓冲道,少占用1个车厢显然更好,所以应该在非空缓冲道追加该车厢
    // 而下边的代码布局,如果不为空就先进入执行,空缓冲道是最后的选择就满足了上边的优先级关系
    // 初始化,目前最好的缓冲道还是0,但编号至少从1开始
    int bestTrack = 0,  
        bestBack = 0;  // 多个可以输入的缓冲道,最大的back被记录在该变量,初始化是0

    // 遍历每个缓冲道
    for (int i = 1; i <= nTracksC9; i++)
        if (!trackC9[i].empty()) // 先判断缓冲道不为空,比较back和nextCar即可
        {
            if (nextCar > trackC9[i].back() && trackC9[i].back() > bestBack) 
            {
                // 即使缓冲道i能够满足条件,但是可能有很多这样的缓冲道都能满足条件
                // 例如nextCar=5,现在通道1有车厢4和2,通道2有车厢3,1,显然nextCar进入通道1更好
                // 也就是比较每个满足条件的缓冲道的back,更大的来追加nextCar,所以需要引入新变量bestBack
                // 第1个缓冲道的back肯定比0大会被放进bestBack,下一个缓冲道的back就会和这个bestBack比较
                // 如果下一个的back更大就更新bestBack,同时更新bestTrack
                bestBack = trackC9[i].back();
                bestTrack = i;
            }
        }
        else // 队空总是最后的选择,如果没有合适的非空缓冲道才会占用1个新的缓冲道(如果有的话)
            if (bestTrack == 0) // 如果没有合适的非空缓冲道,bestTrack还是0
                bestTrack = i;// 如果有多个空缓冲道,编号最小的空缓冲道先被使用

    if (bestTrack == 0) // 空缓冲道也没有就gg
        return false; 

     // 确定了最合适的缓冲道以后就可以添加车厢了
    trackC9[bestTrack].push(nextCar);
    cout << "move car " << nextCar << " from input track "
        << "to buffer track " << bestTrack << endl;

    if (nextCar < smallestNumC9) // 这个已经被添加的车厢可能比目前的最小车厢小
    {
        smallestNumC9 = nextCar; // 如果nextCar就更新smallestNumC9
        belongToTrackC9 = bestTrack; // 最小车厢属于的缓冲道也改变
    }
    return true;
}
void moveInOutputTrackC9()
{
    // 最小编号车厢在上次进入本函数就知道了属于那个缓冲道
    // 如果输入车厢移到了缓冲道,最小车厢及其属于的缓冲道也已经调整过
    trackC9[belongToTrackC9].pop(); // 删除这个最小编号车厢,队列的队尾删除法
    cout << "move car " << smallestNumC9 << " from bufferTrack("
        << belongToTrackC9 << ") to output track" << endl;
    sortedCarriageC9.push(smallestNumC9);
    // 检查每个缓冲队列,找到最小的车厢编号和属于的缓冲道
    smallestNumC9 = nCarsC9 + 1; // 可能缓冲道没有车厢,那么应当保持为初始化状态 =10就可以了
    for (int i = 1; i <= nTracksC9; i++) // 遍历每个缓冲队列
        if (!trackC9[i].empty() && trackC9[i].front() < smallestNumC9) // 缓冲道i不为空,且队列最小的元素都比最小编号小
        {
            // 缓冲道的车厢编号从back到front是越来越小的,所以front最小
            //如果它小于以前的smallestNumC9,就更新smallestNumC9
            smallestNumC9 = trackC9[i].front();
            belongToTrackC9 = i; // smallestNumC9对应的缓冲道
        }
}