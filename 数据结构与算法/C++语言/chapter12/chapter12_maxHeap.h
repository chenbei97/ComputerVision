#pragma once
#ifndef chapter12_maxHeap_
#define chapter12_maxHeap_
#include <sstream>
#include <algorithm>
#include "chapter1_illegalParameterValue.h"
#include "chapter1_changeLength1D.h"
#include "chapter9_queueEmpty.h"
#include "chapter12_abstractMaxPriorityQueue.h"
// �����������ȫ������,�����ɾ��ʱ�临�Ӷ�O(logn),�������ʱ�临�Ӷ�ΪO(nlogn)
using namespace std;
template<class T>
class maxHeap : public abstractMaxPriorityQueue<T>
{
public:
    maxHeap(int initialCapacity = 10);
    ~maxHeap();
    bool empty() const { return heapSize == 0; }
    int size() const{return heapSize;}
    int capacity() const { return arrayLength-1; } // �û���ʼ��������
    const T& top();
    void pop();
    void push(const T&);
    void initialize(T*, int);
    void deactivateArray();
    void output(ostream& out) const;
private:
    int heapSize;       // �ѽڵ�ĸ���
    int arrayLength;    // ������ʵ����=��ʼ������+1,��Ϊheap[0]����
    T* heap;            // ���Ԫ�صĶ�
};
template<class T>
maxHeap<T>::~maxHeap()
{
   //delete[] heap; ��Ҫ���,initial�����ᵼ���ظ��ͷų���
}

template<class T>
maxHeap<T>::maxHeap(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity + 1;
    heap = new T[arrayLength];
    heapSize = 0;
}

template<class T>
void maxHeap<T>::push(const T& theElement)
{
    if (heapSize == arrayLength - 1) // ʵ���õ���������arrayLength - 1
    { 
        
        T* temp = new T[2 * arrayLength-1];
        copy(heap, heap + arrayLength, temp); //heap[0,arrayLength)=>temp
        /*delete[] heap;*/
        heap = temp;
        arrayLength = 2 * arrayLength - 1;
        //changeLength1D(heap, arrayLength, 2 * arrayLength); // ������ն˻����һЩ������Ϣ������ʲôԭ��
        //arrayLength *= 2;
    }

    int currentNode = ++heapSize; // ����Ľڵ��������λ�þ���arr[++heapSize]
    while (currentNode != 1 && heap[currentNode / 2] < theElement) // ���ݹ���
    {
        // �ҵ��������1�����ڵ�Ԫ�ش�����Ԫ�ؼ���
        // ������ڵ�С����Ԫ��heap[currentNode / 2] < theElement
        // �Ҹ��ڵ�û�����1���ڵ�,�ͼ����۰�,ʹ��&&����Ϊ���ڵ㲻������ֹ��Ѱ
        // �Ҹ��ڵ�Ԫ��ҲС����Ԫ��,����û��߼����޷��˳�ѭ����
        heap[currentNode] = heap[currentNode / 2]; // ���ӽڵ���ڸ��ڵ���и���
        currentNode /= 2;                          // ���ڵ�
    }

    heap[currentNode] = theElement; // ѭ�����������˳���Ž��и�ֵ
}

template<class T>
void maxHeap<T>::pop()
{
    if (heapSize == 0)   // heap empty
        throw queueEmpty();
    heap[1].~T(); // ��1��,������ȼ�ֱ������������
    // �������Ĺ����ǽ�ʣ�µ�Ԫ��������֯�õ������
    // �����Ǽ򵥵�����Ԫ��ǰ��1����λ,ӳ���ϵ���б仯
    // ��Ϊ�ֵܽڵ�֮�䲢���������,ֻ�Ǹ��ӽڵ�����
    // ��2��:ɾ��β��Ԫ��,������Ҫ�ñ�����ʱ��¼һ��
    T lastElement = heap[heapSize--];//��ע��heap[heapSize]��û��ɾ��
    heap[heapSize + 1] = NULL; // ɾ����ʵɾ������
    // �Ӹ��ڵ������������ʼ�Ƚ�
    int currentNode = 1,
        child = 2;     // ���ڵ������
    while (child <= heapSize) // ���1�����ӽڵ����µ�heapSize,Ҳ����ԭ����heapSize-1
    {
        // ��3���Ӹ�(��)�ڵ������ѡ������,Ҳ���Ǻ��ӿ���ƽ�Ƶ��ֵܽڵ�
        if (child < heapSize && heap[child] < heap[child + 1]) 
            // heap[2]<heap[3]=>heap[heapSize-1]<heap[heapSize]
            child++; // ����,���heap[2]<heap[3],˵���������ƶ�����(��)�ڵ�

        // ��4��,�ж�ɾ����Ԫ���ܷ���뵽�����ȱchild��λ��
        if (lastElement >= heap[child])
            break;   // yes

         // ��5��,˵����ʱchild��������1�����Բ��뵽child��λ��
        // ɾ����Ԫ�ؿ����ܹ����뵽�µ�child������ȱλ��
        heap[currentNode] = heap[child]; // ���ǵ�ǰchild֮ǰ,��ȡ�����Ԫ�ص����ĸ��ڵ�
        currentNode = child;             // ԭ���ĸ��ڵ���µ���һ�����ڵ�
        child *= 2; // child���µ���һ���ӽڵ�,����++,�ֵܽڵ㲻��
    }
    // ������child=heapSize,û���ֵܽڵ�������if����ִ��
    // ��ʱheap[child]��ɾ����Ԫ��ǰ1��,��һ����lastElement
    // ������,ֱ��ִ��heap[currentNode] = lastElement,��ʱcurrentNode=heapSize/2
    // ʣ�µ�Ԫ�غ�ɾ����Ԫ����ͬ��С,����Ҳ����Ҫ���κβ�����
    // �����ȻlastElement < heap[child],child�����֮ǰ��ȡ��ȥ���Ǹ��ڵ�
    // currentNode��lastElement���ֵܽڵ�����
    // ��ʱcurrentNode�Ѿ�����ΪheapSize,child*2=2*heapSize,�˳�while
    heap[currentNode] = lastElement; // ��ȱ�ĸ��ڵ������Ԫ��
    cout << "after pop heap is  ";
    for (int i = 1; i <= heapSize; i++) {
        cout << heap[i] << " ";
    }
    cout << "\n";
} 

template<class T>
const T& maxHeap<T>::top()
{
    if (heapSize == 0)
        throw queueEmpty();
    return heap[1]; // ������ȼ���Ԫ�������ڵ�1��
}

template<class T>
void maxHeap<T>::initialize(T *theHeap, int theSize)
{
    // push����֪��Ҫ�Ķѵ���״,Ȼ���ӡӳ�������
    // ������������ָ����ĳ�����ȼ�����������
    // �ö�theHeap[1:theSize]��Ԫ��������
    delete[] heap; 
    heap = theHeap;
    heapSize = theSize; // 10
    arrayLength = heapSize + 1; //11
    // �����1�����к��ӽڵ�ĸ���ʼ���
    // ����ڵ��������λ����heapSize/2
    // ֮��������heapSize/2��ǰ�ĸ��ڵ�,ֱ��ȫ�ָ��ڵ�1��λ��
    for (int root = heapSize / 2; root >= 1; root--) // ÿ�����ڵ����µ�����Ԫ�ض����м��
    {
        // ��¼������ڵ��Ԫ��,������������Ƿ�Ϊ�����
        T rootElement = heap[root];  // �ȼ�¼,��������Ǵ���ѾͲ����ٲ���
        int child = 2 * root; // ������ڵ�ĺ���
        // ������Ǵ����,��Ҫ��������ڵ���Ϊ���Ĵ���ѵ���ЩԪ��
        while (child <= heapSize)
        {
            //cout << "before : heap["<<child<<"] = " << heap[child] 
            //    << "  heap["<<child + 1<<"] = " << heap[child + 1] << endl;
            if (child < heapSize && heap[child] < heap[child + 1])
                child++; // �ҵ�2�����Ӹ�����Ǹ�

            if (rootElement >= heap[child])
                break;  // ������������������

             // ����������,����������ӳ�Ϊ���ڵ�,���ڵ�λ����child/2
            heap[child / 2] = heap[child]; // currentNode���ڵ����child / 2
            //cout << "after : heap[" << child << "] = " << heap[child]
            //    << "  heap[" << child + 1 << "] = " << heap[child + 1] << endl;
            child *= 2; 

        }
        heap[child / 2] = rootElement;// currentNode���ڵ����child / 2
        //cout << "root = "<<root<<"\n";
        //for (int i = 1; i <= heapSize; i++) // ��ӡheap�ı仯����
        //    cout << heap[i] <<" ";
        //cout << "\n";
    }
}

template<class T>
void maxHeap<T>::deactivateArray()
{
    heap = NULL; arrayLength = heapSize = 0;
}

template<class T>
void maxHeap<T>::output(ostream& out) const
{
    // heap��[1,heapSize]λ�ö���Ԫ��,���临�Ƶ������
    //copy(heap + 1, heap + heapSize + 1, ostream_iterator<T>(cout, "  "));
    for (int i = 1; i <= heapSize; i++)
        out << heap[i] << "  ";
}

template <class T>
ostream& operator<<(ostream& out, const maxHeap<T>& x)
{
    x.output(out); return out;
}
#endif // !chapter12_maxHeap_
