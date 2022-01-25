#include <iostream>
using namespace std;
// ��cpp�ļ�������������ԭʼ����,û���޸ĺ�����,ֻ��ȫ�ֱ�������C9��ֹ�������ظ�
int* whichTrackC9;  // �������ڵĻ��峵��(ָ��),���Դ������峵��,whichTrackC9[i]��1������,�±�1��ʼ
int* lastCarC9;     // ���峵�����1������ı��(ָ��),whichTrackC9[i]��ӦlastCarC9[i]
int numberOfCarsC9; // �ܵĳ�����
int numberOfTracksC9; // �ܵĻ������
void outputFromHoldingTrack(int);
bool putInHoldingTrack(int);
bool railroad(int*, int, int);
void _chapter9_carriageRearrange_noQueue()
{
    const int nCars = 9; // 9�ڳ���
    const int nTracks = 3; // 3�������
    int permutation[nCars + 1] = { 0, 3,6,9,2,4,7,1,8,5 }; // ����С��0��λ�ò���,��1��ʼ�ȽϷ���
    cout << "Input permutation is 581742963" << endl; // ��ʼ����������
    railroad(permutation, 9, 3);
    cout << "Output permutation is 123456789" << endl; // ��ʼ����������
}

bool railroad(int* inputOrder,int theNumberOfCars, int theNumberOfTracks)
{
    numberOfCarsC9 = theNumberOfCars;
    numberOfTracksC9 = theNumberOfTracks - 1; // ��1���ǲ���Ϊ�������

    // ��ʼ��ÿ���������β��������,ȫ��Ϊ0,ÿ�����ն����Լ��Ļ����(����Ч�ʵ�..)
    lastCarC9 = new int[numberOfTracksC9 + 1]; // ÿ�����������1��β������,����û��,��ôlastCarC9[i]����=0
    fill(lastCarC9 + 1, lastCarC9 + numberOfTracksC9 + 1, 0); // ��ʼ��Ϊ0,ֻ�õ�[1,numberOfTracksC9],����������±�1��ʼ�����ıȽϷ���
    whichTrackC9 = new int[numberOfCarsC9 + 1]; // �����ͬ�����0��ʼ��
    fill(whichTrackC9 + 1, whichTrackC9 + numberOfCarsC9 + 1, 0);
    int nextCarToOutput = 1;

    for (int i = 1; i <= numberOfCarsC9; i++) // ����ÿ������
        if (inputOrder[i] == nextCarToOutput) // �������ĳ��������һ��Ҫ�����
        {
            cout << "Move car " << inputOrder[i] << " from input "
                << "track to output track" << endl;
            nextCarToOutput++;
            while (nextCarToOutput <= numberOfCarsC9 && // ��1�������Ų�ҪԽ��
                whichTrackC9[nextCarToOutput] != 0) // �¸������Ӧ�Ļ������Ϊ0,˵�������������������
            {
                outputFromHoldingTrack(nextCarToOutput); // �Ƴ��������
                nextCarToOutput++; // ������1��
            }
        }
        else // �������,�Ͱ���������͵�������Ӧ���Ǹ������
            // inputOrder[i] to whichTrackC9[i]
            if (!putInHoldingTrack(inputOrder[i]))
                return false;

    return true;
}

void outputFromHoldingTrack(int c)
{
    // ���Կ���,��ʹ��ջ�Ͷ��еķ������,�˺�������һ���β�,��������
    cout << "Move car " << c << " from holding track "
        << whichTrackC9[c] << " to output track" << endl;

    // ���Ҫ�Ƴ��ĳ���c�����ǻ��峵�������1��
    if (c == lastCarC9[whichTrackC9[c]]) // whichTrackC9[c]�õ�����c����ʵĻ����������bestTrack
        // lastCarC9[bestTrack] �õ���Ӧ����������ʵĻ�������Ӧ�ô�ŵĳ���
        lastCarC9[whichTrackC9[c]] = 0; // ������������,�Ϳ����Ƴ�����,����Ϊ0 
}

bool putInHoldingTrack(int c)
{
    int bestTrack = 0,  // ��ʼ������ʵĻ����Ϊ0
        bestLast = 0;  // ��ʼ������ʵĻ������β��������Ϊ0

    for (int i = 1; i <= numberOfTracksC9; i++) // ����ÿ�������
        if (lastCarC9[i] != 0) // �����whichTrack[i]���û��Ԫ����lastCarC9�����0,��֮˵����Ԫ��
        {   
            // ���Ƚ���ǿջ����,ִ���·��ж�,Ѱ������ʵķǿջ����
            if (c > lastCarC9[i] && lastCarC9[i] > bestLast) // Ҫ����ĳ�����Ҫ�ȵ�ǰ�������β�������Ŵ�
            {
                // bestLastһ��ʼ0,���Ż�����ı���,bestLast���ҵ����л������߳����������Ǹ�
                bestLast = lastCarC9[i]; // ������õĻ����β��������
                bestTrack = i; // ��֮��Ӧ�Ļ�������
            }
        }
        else // û�к��ʵķǿջ�������ÿջ����
            if (bestTrack == 0)
                bestTrack = i;

    if (bestTrack == 0) // �ջ����Ҳû��������ʧ��
        return false; 

    whichTrackC9[c] = bestTrack; // ������ʵĻ��������������������Ŷ�Ӧ��λ��
    lastCarC9[bestTrack] = c; // �����������������ʶ�Ӧ�Ļ��������
    // �ս���ʱc=3,i=1,bestTrack=1,whichTrack[3]=1,lastCar[1]=3,i=2,3û������
    // �ٴν���c=6,i=1,lastCar[1]=3��Ϊ��,c=6>3 && 3 > 0,����bestLast=3,bestTrack=1,whichTrack[6]=1,lastCar[1]=6
    // c=9,ͬ����i=1�ͳ�����, 9>lastCar[1]=6 &&  6>3
    cout << "Move car " << c << " from input track "
        << "to holding track " << bestTrack << endl;
    return true;
}