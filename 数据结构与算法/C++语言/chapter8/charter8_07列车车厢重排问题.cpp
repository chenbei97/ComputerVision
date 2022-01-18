#include <iostream>
#include "charter8_arrayStack.h" // 可以使用链栈但是数组栈更快
using namespace std;
arrayStack<int>* trackC8; // 全局栈指针,动态的开辟指定数量的缓冲轨道
arrayStack<int> sortedCarriageC8; // 排序好的车厢存放处
int nCarsC8; // 给定的车厢数
int nTracksC8; // 给定的缓冲轨道数
// nCarsC8和nTracksC8都是主程序自行给定的,不同的车厢数需要的最小缓冲轨道数是不同的
// 如果给错,可能会排列失败,例如1,n,n-1,...,2这个排列的车厢要求最少n-1个缓冲轨道
int smallestNumC8; // 缓冲轨道最小的车厢编号
int belongToTrackC8; // 最小的车厢编号所属的缓冲轨道编号
bool carriageRearrange(int[], int, int);
void moveInOutputTrack();
bool moveInBufferTrack(int);
void _charter8_carriageRearrange()
{
	const int nCars = 9; // 9节车厢
	const int nTracks = 3; // 3个缓冲道
	int permutation[nCars + 1] = { 0, 3,6,9,2,4,7,1,8,5 }; // 数组小标0的位置不用,从1开始比较方便
	cout << "Input permutation is 581742963" << endl; // 初始的输入排列
	if (carriageRearrange(permutation, 9, 3))
	{
		cout << "carriage rearrange is successful, permutation is : " 
			<< sortedCarriageC8<< endl;
	}
	else {cout << "carriage rearrange is failed " << endl;}	
}
bool carriageRearrange(int permutation[], int nCars, int nTracks)
{
	nCarsC8 = nCars;
	nTracksC8 = nTracks;
	const int temp = 10; // 这里是为了说明temp≥1就可以,无关紧要
	// 如果给的9节车厢则初始化最小编号为9+temp,表示缓冲轨道暂时没有车厢
	smallestNumC8 = nCarsC8 + temp; // 因为必须要初始化所以先给定任意1个值,这里取10罢了
	// 下标0不使用,从1开始方便,即trackC8[1]为第1个缓冲轨道
	trackC8 = new arrayStack<int>[nCarsC8 + 1]; 
	int nextNum = 1; // 按顺序下1个进入出轨道的车厢编号,从编号1开始

	for (int i = 1; i <= nCarsC8; i++) // through every permution's num 581742963
	{
		int currentNum = permutation[i]; // actual number 3,6,9,2,4,7,1,8,5
		if (currentNum == nextNum) // currentNum=1,5的时候执行
		{
			cout << "move car(" << currentNum << ") to output track" << endl;
			sortedCarriageC8.push(currentNum);
			cout <<"sortedCarriage is " << sortedCarriageC8 << endl;
			nextNum++; // 下一个应该出去的车厢编号是2
			cout << "nextNum = "<<nextNum << endl;
			// 如果缓冲道最小的车厢编号(一定是最小的先出)是下一个要出的车厢,则移到出轨道
			while (smallestNumC8 == nextNum) // 第1次执行时nextNum=2,smallestNumC8=2
			{
				moveInOutputTrack(); // 车厢2被移出去了,smallestNumC8=3
				nextNum++; // nextNum =3 , 如此反复运行
				cout << "nextNum = " << nextNum << endl;
				if (nextNum == nCarsC8 + 1)
					break;
				// 从(nextNum,smallestNumC8)=(2,2)开始依次执行(3,3),(4,4)共3次,然后(5,6)停止执行
				// 此时缓冲轨道只有6,7,9,而下1个该出去的是5,所以会执行moveInBufferTrack
				// 而当前的currentNum是1,下1个是8和5,8执行moveInBufferTrack,此时缓冲轨道6,7,8,9
				// 然后currentNum=5,在while之前就已经执行出去了,currentNum=6
				// (6,6)=>(7,7)=>(8,8)=>(8,8),缓冲轨道的车厢全部移出完毕
			}
		}
		else
		{
			// 从一开始,如果车厢编号一直不是1,会把不是1的车厢先存入缓冲轨道
			// 这里会把3移入H1,6->H2,9->H3,紧接着2->H1,4->H2,7->H3
			// 直到currentNum=1会执行上方程序,把缓冲轨道的一些车厢移出,然后while在(5,6)也不执行了
			// currentNum = 8,nextNum = 5,移入缓冲轨道 currentNum = 5 执行上方程序
			if (!moveInBufferTrack(currentNum))  // currentNum = 3,6,9,2,4,7,8的时候执行
				return false; // 如果没有缓冲轨道了说明重排失败
		}
	}
	return true;
}
void moveInOutputTrack()
{
	//cout << "belongToTrackC8 = " << belongToTrackC8 << endl; 1,1,2,2,3,1,3
	// belongToTrackC8在moveInBufferTrack已经变成1了
	trackC8[belongToTrackC8].pop(); // 把最小的车厢从相应的缓冲道移出
	cout << "move car(" << smallestNumC8 << ") from bufferTrack(" 
		<< belongToTrackC8 << ") to outputTrack" << endl;
	sortedCarriageC8.push(smallestNumC8);
	cout << "sortedCarriage is " << sortedCarriageC8 << endl;
	smallestNumC8 = nCarsC8 + 1; // 如果下方没找到目前最小的车辆编号说明缓冲道没有车厢
	for (int i = 1; i <= nTracksC8; i++) // through every not empty track
	{
		cout << "smallestNum = " << smallestNumC8 
			<<" belongToTrack "<< belongToTrackC8<< endl;
		if (!trackC8[i].empty() && (trackC8[i].top() < smallestNumC8))
		{ //  如果顶部元素有更小的车辆编号就更新2个全局变量
			smallestNumC8 = trackC8[i].top();
			belongToTrackC8 = i;
		}
	}
}
bool moveInBufferTrack(int currentNum)
{
	// 有可用的缓冲道那么可以移入,返回true;否则说明有限的缓冲道无法进行重排
	const int temp = 10; // 这里是为了说明temp≥1就可以,无关紧要
	int bestTrack = 0; // currentNum最合适移入的Track,应该从1到nTracksC8,0是初始化
	int smallerNum= nCarsC8 + temp; // 如果有比currentNum更小的编号就会更新这个值否则不变
	for (int i = 1; i <= nTracksC8; i++)
		if (!trackC8[i].empty()) // through every not empty track
		{
			// 不为空时当前的Track至少有1个top,取出来和当前的车厢编号比较,更小的被记录用于下一个Track比较
			int topCar = trackC8[i].top(); // 获取不同Track的top和smallerNum比较,找到最小的
			// 且当前的车厢编号还小于smallerNum,说明可以在这个Track存储,记录存储的Track编号
			if (currentNum < topCar && topCar < smallerNum) // smallerNum总是一开始等于10
			{
				// 此时有更小的车厢编号,位置在trackC8[i]的栈顶
				smallerNum = topCar; // 记录更小的车厢编号(如果有的话更新它用于比较下1个Track)
				bestTrack = i; // 记录此时的车厢编号所属的缓冲道
			}
		}
		else
			// 如果还是初始化状态,说明之前的Track不为空但也没有更小的车辆编号
			if (bestTrack == 0) bestTrack = i;  // 移入首个为空的Track,i=1必定执行
	if (bestTrack == 0) return false;// 空Track也没有,说明无法重排
	trackC8[bestTrack].push(currentNum); // i=1,bestTrack=1,currentNum=3
	cout << "move car(" << currentNum << ") from inputTrack to bufferTrack(" 
		<<bestTrack<<")" << endl;

	// 如果有必要需要更新2个全局变量，3,6,9,2,4,7,1,8,5
	if (currentNum < smallestNumC8) // 最开始是3<10,6<3? 均不执行直到1<3才会执行
	{
		smallestNumC8 = currentNum; // =3,=1,
		belongToTrackC8 = bestTrack; // =1,
	}
	return true; 
}