#include <iostream>
#include "chapter8_arrayStack.h" // ����ʹ����ջ��������ջ����
using namespace std;
arrayStack<int>* trackC8; // ȫ��ջָ��,��̬�Ŀ���ָ�������Ļ�����
arrayStack<int> sortedCarriageC8; // ����õĳ����Ŵ�
int nCarsC8; // �����ĳ�����
int nTracksC8; // �����Ļ�������
// nCarsC8��nTracksC8�������������и�����,��ͬ�ĳ�������Ҫ����С���������ǲ�ͬ��
// �������,���ܻ�����ʧ��,����1,n,n-1,...,2������еĳ���Ҫ������n-1��������
int smallestNumC8; // ��������С�ĳ�����
int belongToTrackC8; // ��С�ĳ����������Ļ��������
bool carriageRearrangeC8(int[], int, int);
void moveInOutputTrackC8();
bool moveInBufferTrackC8(int);
void _chapter8_carriageRearrange()
{
	const int nCars = 9; // 9�ڳ���
	const int nTracks = 3; // 3�������
	int permutation[nCars + 1] = { 0, 3,6,9,2,4,7,1,8,5 }; // ����С��0��λ�ò���,��1��ʼ�ȽϷ���
	cout << "Input permutation is 581742963" << endl; // ��ʼ����������
	if (carriageRearrangeC8(permutation, 9, 3))
	{
		cout << "carriage rearrange is successful, permutation is : " 
			<< sortedCarriageC8<< endl;
	}
	else {cout << "carriage rearrange is failed " << endl;}	
}
bool carriageRearrangeC8(int permutation[], int nCars, int nTracks)
{
	nCarsC8 = nCars;
	nTracksC8 = nTracks;
	const int temp = 10; // ������Ϊ��˵��temp��1�Ϳ���,�޹ؽ�Ҫ
	// �������9�ڳ������ʼ����С���Ϊ9+temp,��ʾ��������ʱû�г���
	smallestNumC8 = nCarsC8 + temp; // ��Ϊ����Ҫ��ʼ�������ȸ�������1��ֵ,����ȡ10����
	// �±�0��ʹ��,��1��ʼ����,��trackC8[1]Ϊ��1��������
	trackC8 = new arrayStack<int>[nTracks + 1]; 
	int nextNum = 1; // ��˳����1�����������ĳ�����,�ӱ��1��ʼ

	for (int i = 1; i <= nCarsC8; i++) // through every permution's num 581742963
	{
		int currentNum = permutation[i]; // actual number 3,6,9,2,4,7,1,8,5
		if (currentNum == nextNum) // currentNum=1,5��ʱ��ִ��
		{
			cout << "move car(" << currentNum << ") to output track" << endl;
			sortedCarriageC8.push(currentNum);
			cout <<"sortedCarriage is " << sortedCarriageC8 << endl;
			nextNum++; // ��һ��Ӧ�ó�ȥ�ĳ�������2
			cout << "nextNum = "<<nextNum << endl;
			// ����������С�ĳ�����(һ������С���ȳ�)����һ��Ҫ���ĳ���,���Ƶ������
			while (smallestNumC8 == nextNum) // ��1��ִ��ʱnextNum=2,smallestNumC8=2
			{
				moveInOutputTrackC8(); // ����2���Ƴ�ȥ��,smallestNumC8=3
				nextNum++; // nextNum =3 , ��˷�������
				cout << "nextNum = " << nextNum << endl;
				if (nextNum == nCarsC8 + 1)
					break;
				// ��(nextNum,smallestNumC8)=(2,2)��ʼ����ִ��(3,3),(4,4)��3��,Ȼ��(5,6)ִֹͣ��
				// ��ʱ������ֻ��6,7,9,����1���ó�ȥ����5,���Ի�ִ��moveInBufferTrack
				// ����ǰ��currentNum��1,��1����8��5,8ִ��moveInBufferTrack,��ʱ������6,7,8,9
				// Ȼ��currentNum=5,��while֮ǰ���Ѿ�ִ�г�ȥ��,currentNum=6
				// (6,6)=>(7,7)=>(8,8)=>(8,8),�������ĳ���ȫ���Ƴ����
			}
		}
		else
		{
			// ��һ��ʼ,���������һֱ����1,��Ѳ���1�ĳ����ȴ��뻺����
			// ������3����H1,6->H2,9->H3,������2->H1,4->H2,7->H3
			// ֱ��currentNum=1��ִ���Ϸ�����,�ѻ�������һЩ�����Ƴ�,Ȼ��while��(5,6)Ҳ��ִ����
			// currentNum = 8,nextNum = 5,���뻺���� currentNum = 5 ִ���Ϸ�����
			if (!moveInBufferTrackC8(currentNum))  // currentNum = 3,6,9,2,4,7,8��ʱ��ִ��
				return false; // ���û�л�������˵������ʧ��
		}
	}
	return true;
}
void moveInOutputTrackC8()
{
	//cout << "belongToTrackC8 = " << belongToTrackC8 << endl; 1,1,2,2,3,1,3
	// belongToTrackC8��moveInBufferTrack�Ѿ����1��
	trackC8[belongToTrackC8].pop(); // ����С�ĳ������Ӧ�Ļ�����Ƴ�
	cout << "move car(" << smallestNumC8 << ") from bufferTrack(" 
		<< belongToTrackC8 << ") to outputTrack" << endl;
	sortedCarriageC8.push(smallestNumC8);
	cout << "sortedCarriage is " << sortedCarriageC8 << endl;
	smallestNumC8 = nCarsC8 + 1; // ����·�û�ҵ�Ŀǰ��С�ĳ������˵�������û�г���
	for (int i = 1; i <= nTracksC8; i++) // through every not empty track
	{
		cout << "smallestNum = " << smallestNumC8 
			<<" belongToTrack "<< belongToTrackC8<< endl;
		if (!trackC8[i].empty() && (trackC8[i].top() < smallestNumC8))
		{ //  �������Ԫ���и�С�ĳ�����ž͸���2��ȫ�ֱ���
			smallestNumC8 = trackC8[i].top();
			belongToTrackC8 = i;
		}
	}
}
bool moveInBufferTrackC8(int currentNum)
{
	// �п��õĻ������ô��������,����true;����˵�����޵Ļ�����޷���������
	const int temp = 10; // ������Ϊ��˵��temp��1�Ϳ���,�޹ؽ�Ҫ
	int bestTrack = 0; // currentNum����������Track,Ӧ�ô�1��nTracksC8,0�ǳ�ʼ��
	int bestTop= nCarsC8 + temp; // ����б�currentNum��С�ı�žͻ�������ֵ���򲻱�
	for (int i = 1; i <= nTracksC8; i++)
		if (!trackC8[i].empty()) // through every not empty track
		{
			// ��Ϊ��ʱ��ǰ��Track������1��top,ȡ�����͵�ǰ�ĳ����űȽ�,��С�ı���¼������һ��Track�Ƚ�
			// �ҵ�ǰ�ĳ����Ż�С��smallerNum,˵�����������Track�洢,��¼�洢��Track���
			if (currentNum < trackC8[i].top() && trackC8[i].top() < bestTop) // smallerNum����һ��ʼ����10
			{
				// ��ʱ�и�С�ĳ�����,λ����trackC8[i]��ջ��
				bestTop = trackC8[i].top(); // ��¼��С�ĳ�����(����еĻ����������ڱȽ���1��Track)
				bestTrack = i; // ��¼��ʱ�ĳ����������Ļ����
			}
		}
		else
			// ������ǳ�ʼ��״̬,˵��֮ǰ��Track��Ϊ�յ�Ҳû�и�С�ĳ������
			if (bestTrack == 0) bestTrack = i;  // �����׸�Ϊ�յ�Track,i=1�ض�ִ��
	if (bestTrack == 0) return false;// ��TrackҲû��,˵���޷�����
	trackC8[bestTrack].push(currentNum); // i=1,bestTrack=1,currentNum=3
	cout << "move car(" << currentNum << ") from inputTrack to bufferTrack(" 
		<<bestTrack<<")" << endl;

	// ����б�Ҫ��Ҫ����2��ȫ�ֱ�����3,6,9,2,4,7,1,8,5
	if (currentNum < smallestNumC8) // �ʼ��3<10,6<3? ����ִ��ֱ��1<3�Ż�ִ��
	{
		smallestNumC8 = currentNum; // =3,=1,
		belongToTrackC8 = bestTrack; // =1,
	}
	return true; 
}