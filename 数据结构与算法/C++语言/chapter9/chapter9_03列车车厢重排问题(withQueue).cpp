#include <iostream>
#include "chapter9_arrayQueue.h"
using namespace std;
arrayQueue<int>* trackC9; // ȫ�ֶ���ָ��,��̬�Ŀ���ָ�������Ļ�����
arrayQueue<int> sortedCarriageC9; // ����õĳ����Ŵ�
int nCarsC9; // �����ĳ�����
int nTracksC9; // �����Ļ�������
int smallestNumC9; // ��������С�ĳ�����
int belongToTrackC9; // ��С�ĳ����������Ļ��������
bool carriageRearrangeC9(int*, int, int);
void moveInOutputTrackC9();
bool moveInBufferTrackC9(int);
void _chapter9_carriageRearrange()
{
    const int nCars = 9; // 9�ڳ���
    const int nTracks = 3; // 3�������
    int permutation[nCars + 1] = { 0, 3,6,9,2,4,7,1,8,5 }; // ����С��0��λ�ò���,��1��ʼ�ȽϷ���
    cout << "Input permutation is 581742963" << endl; // ��ʼ����������
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
	nTracksC9 = nTracks - 1;// ��1��ͨ��������ֱ����������
    trackC9 = new arrayQueue<int>[nTracks]; // Ϊ��Щ����ͨ�������ڴ�
    int nextCarToOutput = 1; // ��ʼ����һ��Ӧ������ĳ�����Ϊ1
    smallestNumC9 = nCarsC9 + 1;  // ����������ʼ��,Ŀǰ����С�����10

    for (int i = 1; i <= nCarsC9; i++) // ��1��������Ϊpermution[0]û��
        if (permutation[i] == nextCarToOutput) // ������þ�����1��ֱ�����
        {
            cout << "move car " << permutation[i] << " to output track" << endl;
            sortedCarriageC9.push(permutation[i]);
            nextCarToOutput++;

            // ��������û����ִ���Ϸ�����ͽ�����
            // ����г���,��ΪnextCarToOutput�Ѿ�++,�����жϻ�����Ƿ������һ��������ĳ���
            while (smallestNumC9 == nextCarToOutput) // �����
            {
                moveInOutputTrackC9(); // �ѳ���ӻ�����Ƴ�
                nextCarToOutput++; // ������һ���ó��ĳ�����
                if (smallestNumC9 == nCarsC9 + 1) // ��ֹsmallestNumC9=10,��nextCarToOutputҲ����10�˲���ѭ��
                    break;
            }
            
        }
        else // �������Ӧ�ó��ĳ�������뻺���
            if (!moveInBufferTrackC9(permutation[i])) // ����ɹ��ͼ�����һ���������ĳ���
                return false; // ����ʧ�ܾ�����ʧ��

    return true;

}
bool moveInBufferTrackC9(int nextCar)
{
    // Ŀ����Ϊ���ҵ�����ʵĻ��������һ�����복��
    // ���복����ȥ�Ļ������2��ѡ��,һ���ǿջ����,һ���Ƿǿջ����������ߵĳ����Ŷ�С��nextCar
    // ��ΪtrackC9[i].back()������,����������nextCar�ȽϾͿ�����
    // ���ȷʵ�������ķǿջ����,Ҳ�пջ����,��ռ��1��������Ȼ����,����Ӧ���ڷǿջ����׷�Ӹó���
    // ���±ߵĴ��벼��,�����Ϊ�վ��Ƚ���ִ��,�ջ����������ѡ����������ϱߵ����ȼ���ϵ
    // ��ʼ��,Ŀǰ��õĻ��������0,��������ٴ�1��ʼ
    int bestTrack = 0,  
        bestBack = 0;  // �����������Ļ����,����back����¼�ڸñ���,��ʼ����0

    // ����ÿ�������
    for (int i = 1; i <= nTracksC9; i++)
        if (!trackC9[i].empty()) // ���жϻ������Ϊ��,�Ƚ�back��nextCar����
        {
            if (nextCar > trackC9[i].back() && trackC9[i].back() > bestBack) 
            {
                // ��ʹ�����i�ܹ���������,���ǿ����кܶ������Ļ����������������
                // ����nextCar=5,����ͨ��1�г���4��2,ͨ��2�г���3,1,��ȻnextCar����ͨ��1����
                // Ҳ���ǱȽ�ÿ�����������Ļ������back,�������׷��nextCar,������Ҫ�����±���bestBack
                // ��1���������back�϶���0��ᱻ�Ž�bestBack,��һ���������back�ͻ�����bestBack�Ƚ�
                // �����һ����back����͸���bestBack,ͬʱ����bestTrack
                bestBack = trackC9[i].back();
                bestTrack = i;
            }
        }
        else // �ӿ���������ѡ��,���û�к��ʵķǿջ�����Ż�ռ��1���µĻ����(����еĻ�)
            if (bestTrack == 0) // ���û�к��ʵķǿջ����,bestTrack����0
                bestTrack = i;// ����ж���ջ����,�����С�Ŀջ�����ȱ�ʹ��

    if (bestTrack == 0) // �ջ����Ҳû�о�gg
        return false; 

     // ȷ��������ʵĻ�����Ժ�Ϳ�����ӳ�����
    trackC9[bestTrack].push(nextCar);
    cout << "move car " << nextCar << " from input track "
        << "to buffer track " << bestTrack << endl;

    if (nextCar < smallestNumC9) // ����Ѿ�����ӵĳ�����ܱ�Ŀǰ����С����С
    {
        smallestNumC9 = nextCar; // ���nextCar�͸���smallestNumC9
        belongToTrackC9 = bestTrack; // ��С�������ڵĻ����Ҳ�ı�
    }
    return true;
}
void moveInOutputTrackC9()
{
    // ��С��ų������ϴν��뱾������֪���������Ǹ������
    // ������복���Ƶ��˻����,��С���ἰ�����ڵĻ����Ҳ�Ѿ�������
    trackC9[belongToTrackC9].pop(); // ɾ�������С��ų���,���еĶ�βɾ����
    cout << "move car " << smallestNumC9 << " from bufferTrack("
        << belongToTrackC9 << ") to output track" << endl;
    sortedCarriageC9.push(smallestNumC9);
    // ���ÿ���������,�ҵ���С�ĳ����ź����ڵĻ����
    smallestNumC9 = nCarsC9 + 1; // ���ܻ����û�г���,��ôӦ������Ϊ��ʼ��״̬ =10�Ϳ�����
    for (int i = 1; i <= nTracksC9; i++) // ����ÿ���������
        if (!trackC9[i].empty() && trackC9[i].front() < smallestNumC9) // �����i��Ϊ��,�Ҷ�����С��Ԫ�ض�����С���С
        {
            // ������ĳ����Ŵ�back��front��Խ��ԽС��,����front��С
            //�����С����ǰ��smallestNumC9,�͸���smallestNumC9
            smallestNumC9 = trackC9[i].front();
            belongToTrackC9 = i; // smallestNumC9��Ӧ�Ļ����
        }
}