#pragma once
#ifndef chapter12_minHeap_
#define chapter12_minHeap_
#include <sstream>
#include <algorithm>
#include "chapter1_illegalParameterValue.h"
#include "chapter9_queueEmpty.h"
#include "chapter12_abstractMinPriorityQueue.h"
using namespace std;
template<class T>
class minHeap : public abstractMinPriorityQueue<T>
{
public:
    minHeap(int initialCapacity = 10);
    ~minHeap() { delete[] heap; }
    bool empty() const { return heapSize == 0; }
    int size() const{return heapSize;}
    int capacity() const { return arrayLength - 1; } // 用户初始化的容量
    const T& top();
    void pop();
    void push(const T&);
    void initialize(T*, int);
    void deactivateArray();
    void output(ostream& out) const;
private:
    int heapSize;       // number of elements in queue
    int arrayLength;    // queue capacity + 1
    T* heap;            // element array
};

template<class T>
minHeap<T>::minHeap(int initialCapacity)
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
void minHeap<T>::push(const T& theElement)
{
    if (heapSize == arrayLength - 1)
    {
        T* temp = new T[2 * arrayLength - 1];
        copy(heap, heap + arrayLength, temp); //heap[0,arrayLength)=>temp
        heap = temp;
        arrayLength = 2 * arrayLength - 1;
    }

    int currentNode = ++heapSize;
    while (currentNode != 1 && heap[currentNode / 2] > theElement) // 改成大于就可以
    {
        heap[currentNode] = heap[currentNode / 2]; 
        currentNode /= 2;                        
    }
    heap[currentNode] = theElement;
}

template<class T>
void minHeap<T>::pop()
{
    if (heapSize == 0)  
        throw queueEmpty();
    heap[1].~T();
    T lastElement = heap[heapSize--];
    int currentNode = 1,
        child = 2;   
    while (child <= heapSize)
    {
        if (child < heapSize && heap[child] > heap[child + 1]) // 改成大于即可
            child++;
        if (lastElement <= heap[child]) // 改成小于等于
            break;   
        heap[currentNode] = heap[child]; 
        currentNode = child;           
        child *= 2;
    }
    heap[currentNode] = lastElement;
}

template<class T>
const T& minHeap<T>::top()
{
    if (heapSize == 0)
        throw queueEmpty();
    return heap[1]; // 最大优先级的元素总是在第1个
}

template<class T>
void minHeap<T>::initialize(T* theHeap, int theSize)
{
    delete[] heap;
    heap = theHeap;
    heapSize = theSize;
    arrayLength = heapSize + 1;
    for (int root = heapSize / 2; root >= 1; root--)
    {
        T rootElement = heap[root];
        int child = 2 * root; 
        while (child <= heapSize)
        {
            if (child < heapSize && heap[child] > heap[child + 1])//改成大于
                child++;
            if (rootElement <= heap[child]) // 改成小于等于
                break;  
            heap[child / 2] = heap[child]; 
            child *= 2;                   
        }
        heap[child / 2] = rootElement;
    }
}

template<class T>
void minHeap<T>::output(ostream& out) const
{
    copy(heap + 1, heap + heapSize + 1, ostream_iterator<T>(cout, "  "));
}

template<class T>
void minHeap<T>::deactivateArray()
{
    heap = NULL; arrayLength = heapSize = 0;
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const minHeap<T>& x)
{
    x.output(out); return out;
}
#endif // !chapter12_minHeap_
