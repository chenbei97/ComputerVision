#pragma once
#ifndef chapter12_maxHeap_
#define chapter12_maxHeap_
#include <sstream>
#include <algorithm>
#include "chapter1_illegalParameterValue.h"
#include "chapter1_changeLength1D.h"
#include "chapter9_queueEmpty.h"
#include "chapter12_abstractMaxPriorityQueue.h"
// 堆是有序的完全二叉树,插入和删除时间复杂度O(logn),堆排序的时间复杂度为O(nlogn)
using namespace std;
template<class T>
class maxHeap : public abstractMaxPriorityQueue<T>
{
public:
    maxHeap(int initialCapacity = 10);
    ~maxHeap();
    bool empty() const { return heapSize == 0; }
    int size() const{return heapSize;}
    int capacity() const { return arrayLength-1; } // 用户初始化的容量
    const T& top();
    void pop();
    void push(const T&);
    void initialize(T*, int);
    void deactivateArray();
    void output(ostream& out) const;
private:
    int heapSize;       // 堆节点的个数
    int arrayLength;    // 数组真实容量=初始化容量+1,因为heap[0]弃用
    T* heap;            // 存放元素的堆
};
template<class T>
maxHeap<T>::~maxHeap()
{
   //delete[] heap; 不要这句,initial函数会导致重复释放出错
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
    if (heapSize == arrayLength - 1) // 实际用到的容量是arrayLength - 1
    { 
        
        T* temp = new T[2 * arrayLength-1];
        copy(heap, heap + arrayLength, temp); //heap[0,arrayLength)=>temp
        /*delete[] heap;*/
        heap = temp;
        arrayLength = 2 * arrayLength - 1;
        //changeLength1D(heap, arrayLength, 2 * arrayLength); // 用这个终端会输出一些错误信息不明白什么原因
        //arrayLength *= 2;
    }

    int currentNode = ++heapSize; // 插入的节点在数组的位置就是arr[++heapSize]
    while (currentNode != 1 && heap[currentNode / 2] < theElement) // 起泡过程
    {
        // 找到编号最大的1个父节点元素大于新元素即可
        // 如果父节点小于新元素heap[currentNode / 2] < theElement
        // 且父节点没到编号1根节点,就继续折半,使用&&是因为父节点不能无休止上寻
        // 且根节点元素也小于新元素,如果用或逻辑就无法退出循环了
        heap[currentNode] = heap[currentNode / 2]; // 让子节点等于父节点进行覆盖
        currentNode /= 2;                          // 父节点
    }

    heap[currentNode] = theElement; // 循环条件满足退出后才进行赋值
}

template<class T>
void maxHeap<T>::pop()
{
    if (heapSize == 0)   // heap empty
        throw queueEmpty();
    heap[1].~T(); // 第1步,最大优先级直接析构掉即可
    // 接下来的工作是将剩下的元素重新组织得到大根堆
    // 并不是简单的所有元素前移1个单位,映射关系会有变化
    // 因为兄弟节点之间并不是有序的,只是父子节点有序
    // 第2步:删除尾部元素,但是需要用变量临时记录一下
    T lastElement = heap[heapSize--];//但注意heap[heapSize]并没有删除
    heap[heapSize + 1] = NULL; // 删除其实删除不掉
    // 从根节点的左右子树开始比较
    int currentNode = 1,
        child = 2;     // 根节点的左孩子
    while (child <= heapSize) // 最后1个孩子节点是新的heapSize,也就是原来的heapSize-1
    {
        // 第3步从父(根)节点的子树选择更大的,也即是孩子可能平移到兄弟节点
        if (child < heapSize && heap[child] < heap[child + 1]) 
            // heap[2]<heap[3]=>heap[heapSize-1]<heap[heapSize]
            child++; // 例如,如果heap[2]<heap[3],说明右子树移动到父(根)节点

        // 第4步,判断删除的元素能否插入到这个空缺child的位置
        if (lastElement >= heap[child])
            break;   // yes

         // 第5步,说明此时child的子树有1个可以插入到child的位置
        // 删除的元素可能能够插入到新的child子树空缺位置
        heap[currentNode] = heap[child]; // 覆盖当前child之前,先取出这个元素到它的父节点
        currentNode = child;             // 原本的父节点更新到下一级父节点
        child *= 2; // child更新到下一级子节点,不是++,兄弟节点不是
    }
    // 最坏情况是child=heapSize,没有兄弟节点了所以if不会执行
    // 此时heap[child]是删除的元素前1个,它一定≥lastElement
    // 如果相等,直接执行heap[currentNode] = lastElement,此时currentNode=heapSize/2
    // 剩下的元素和删除的元素相同大小,但是也不需要做任何操作了
    // 如果依然lastElement < heap[child],child被填充之前先取出去覆盖父节点
    // currentNode是lastElement的兄弟节点填充的
    // 此时currentNode已经更新为heapSize,child*2=2*heapSize,退出while
    heap[currentNode] = lastElement; // 空缺的父节点插入新元素
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
    return heap[1]; // 最大优先级的元素总是在第1个
}

template<class T>
void maxHeap<T>::initialize(T *theHeap, int theSize)
{
    // push是已知想要的堆的形状,然后打印映射的数组
    // 现在期望给出指定的某种优先级来构造大根堆
    // 用堆theHeap[1:theSize]的元素来构造
    delete[] heap; 
    heap = theHeap;
    heapSize = theSize; // 10
    arrayLength = heapSize + 1; //11
    // 从最后1个具有孩子节点的根开始检查
    // 这个节点在数组的位置是heapSize/2
    // 之后继续检查heapSize/2以前的根节点,直到全局根节点1的位置
    for (int root = heapSize / 2; root >= 1; root--) // 每个根节点以下的所有元素都进行检查
    {
        // 记录这个根节点的元素,检查它的子树是否为大根堆
        T rootElement = heap[root];  // 先记录,如果子树是大根堆就不用再操作
        int child = 2 * root; // 这个父节点的孩子
        // 如果不是大根堆,就要调整这个节点作为根的大根堆的这些元素
        while (child <= heapSize)
        {
            //cout << "before : heap["<<child<<"] = " << heap[child] 
            //    << "  heap["<<child + 1<<"] = " << heap[child + 1] << endl;
            if (child < heapSize && heap[child] < heap[child + 1])
                child++; // 找到2个孩子更大的那个

            if (rootElement >= heap[child])
                break;  // 如果满足大根堆无需操作

             // 不满足大根堆,就让这个孩子成为父节点,父节点位置是child/2
            heap[child / 2] = heap[child]; // currentNode父节点就是child / 2
            //cout << "after : heap[" << child << "] = " << heap[child]
            //    << "  heap[" << child + 1 << "] = " << heap[child + 1] << endl;
            child *= 2; 

        }
        heap[child / 2] = rootElement;// currentNode父节点就是child / 2
        //cout << "root = "<<root<<"\n";
        //for (int i = 1; i <= heapSize; i++) // 打印heap的变化过程
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
    // heap在[1,heapSize]位置都有元素,将其复制到输出流
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
