#pragma once
#ifndef chapter9_arrayQueue_
#define chapter9_arrayQueue_
#include <sstream>
#include "chapter9_abstractQueue.h"
#include "chapter9_queueEmpty.h"
#include "chapter1_illegalParameterValue.h"
using namespace std;
template<class T>
class arrayQueue : public abstractQueue<T>
{
public:
	arrayQueue(int initialCapacity = 10);
	~arrayQueue() { if (queue != NULL) queue = NULL; delete[] queue; }
    bool empty() const { return theFront == theBack; }
    int size() const;
    T& front();
    T& back();
    void pop();
    void push(const T&);
    friend ostream& operator<<<>(ostream&, arrayQueue<T> &);
    void log(bool);
    void output(ostream&) const;
    int getFrontIndex() { return theFront; }
    int getBackIndex() { return theBack; }
private:
    int theFront;       // 队首元素索引的逆时针前1位
    int theBack;        // 队尾元素索引
    int arrayLength;  
    T* queue;
    bool isChangeArrayLength; // 最初没有改变过容量
    bool isPop; // 没有执行过1次pop
    bool isLog;
};

template<class T>
arrayQueue<T> ::arrayQueue(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity; // 还可以改变
    queue = new T[arrayLength];
    theFront = 0; // 初始位置都是0
    theBack = 0;
    isLog = false;
    isChangeArrayLength = false;
    isPop = false;
};

template<class T>
int arrayQueue<T>::size() const
{
    // 1. 0≤theBack < theFront , 说明已经越过0 , 分成2部分计算
    // 第1部分应当计算[theFront+1,arrayLength-1]的元素个数
    // 而[a,b]闭区间的元素个数为b-a+1,所以这部分元素个数为arrayLength-theFront-1
    // 第2部分计算[0,theBack],个数为theBack+1
    // 合并为arrayLength+theBack-theFront
    // 2. 如果theFront<theBack,只需要计算[theFront+1,theBack],即theBack - theFront
    // 3. 现在合并2种情况,theBack-theFront看成整体X,考虑(X+C)%C的情况
    // X不是大于0就是小于0,小于0时相当于不够除1个C,剩下的就是X+C
    // X大于0时,够除1个C,因为X再大也不到1个C,那剩下的余数其实就是X
    // theFront=0,theBack=C-1达到了差值最大,所以余数最大为C-1,也就是arrayLength-1
    // 最小的时候自然是初始theFront=theBack=0,之后theBack开始变化,size=theBack-theFront
    if (theBack > theFront) // 这段程序和下方注释的程序完全等价
        return theBack - theFront;
    else
        return arrayLength + theBack - theFront;
    // return (theBack - theFront + arrayLength) % arrayLength;
}

template<class T>
T& arrayQueue<T> ::front()
{
    if (theFront == theBack)
        throw queueEmpty();
    return queue[(theFront + 1) % arrayLength];
};

template<class T>
T& arrayQueue<T> ::back()
{
    if (theFront == theBack)
        throw queueEmpty();
    return queue[theBack]; // theBack就是尾部元素的实际位置
};

template<class T>
void arrayQueue<T> ::pop()
{
    if (theFront == theBack)
        throw queueEmpty();
    if (isLog == true)
        cout << ">>>>>>>>before pop theBack<old> = " << theBack << " and theFront<old> = " << theFront << endl;
    theFront = (theFront + 1) % arrayLength; // pop后就从31变成0了
    queue[theFront].~T();  // pop删除队首元素
    isPop = true;
    if (isLog == true)
    {
        cout << ">>>>>>>>after pop theBack<new> = " << theBack << " and theFront<new> = " << theFront << endl;
        cout << ">>>>>>>>after pop queue size is " << size()<<" and queue is "<< endl;
        int idx = 0;
        for (int i = theFront; i <= theBack; i++) // 不要用<=size(),用theBack更准确
        {
            if (i == theFront)
                cout << "NULL" << "(" << i << ")" << "  ";
            else
                cout << queue[i] << "(" << i << ")" << "  ";
            if ((idx + 1) % 5 == 0)
                cout << endl;
            idx++;
        }
        cout << "\n--------------------------------------------------------------------" << endl;
    }

};

template<class T>
void arrayQueue<T>::log(bool isLog)
{
    this->isLog = isLog;
}

template<class T>
void arrayQueue<T>::output(ostream & out) const
{
    if (empty())
    {
        for (int i = 0; i < arrayLength; i++)
        {
            out << "queue[" << i << "] = " << "NULL" << "  ";
            if ((i + 1) % 5 == 0)
                out << endl;
        }
        return;
    }

    if (isPop)
    {
        // pop过可能theBack会越过0也可能还没越过0,但是theFront不会等于0
        // 可以使用theBack和theFront的大小关系判断
        if (isLog == true)
        {
            if (theFront > theBack)
                cout << ">>>>>>>>theBack has crossed 0, it will be 0 ≤ theBack < theFront, queue is circular" << endl;
            else
                cout << ">>>>>>>>theBack has not passed 0, it will be thefront < theback, queue not circular " << endl;
        }
        for (int i = 0; i < arrayLength; i++) // 不能用size(),比如3-31都是有元素的,但是0-2没有
            //size=29,那么queue[29],queue[30],queue[31]就没有被打印出来,所以应该用arrayLength
        {
            // 数组环绕：就是theBack能够回到{0,arrayLength-1}且theFront不是0
            // 正常情况没有pop过,theFront总是={0,arrayLength-1}
            // 当theBack要等于arrayLength-1时就立刻变为arrayLength-2,所以总是不会等于theFront
            // 因为theBack=theFront可以是队空也可以是队满的条件,为了避免冲突,即将队满就会扩充容量
            // 但是如果pop过,theBack就可以回到{0,arrayLength-1}了,因为theFront这个时候已经在{0,arrayLength-1}的前边
            // 可能的情形 ①：theBack小于theFront,说明theBack>=0
            // 例如theBack=2,theFront = 4, 此时i = 3, 4都没有元素, 但是0,1,2有元素
            // 所以theBack< i <= theFront , 即3,4被打印出来
            if (theFront > theBack)
            {
                if (theBack < i && i <= theFront)
                    out << "queue[" << i << "] = " << "NULL" << "  ";
                else
                    out << "queue[" << i << "] = " << queue[i] << "  ";
            }
            else
            {
                // 可能的情形 ②：theBack大于theFront,说明theBack没越过0
                // 例如theBack=6,theFront = 2, 此时i = 3, 4,5,6有元素
                //  但是[0,1,2]和(theBack,arrayLength-1]没有元素
                // 所以theBack< i <= theFront , 即3,4被打印出来
                if (i >theBack || i <= theFront)
                    out << "queue[" << i << "] = " << "NULL" << "  ";
                else
                    out << "queue[" << i << "] = " << queue[i] << "  ";
            }
            if ((i + 1) % 5 == 0)
                out << endl;
        }
    }
    else
    {
        // 如果没拓展过容量,例如capacity=4,size()=3,[0,3]在3位置有元素,0没有
        // 只要拓展过容量,例如capacity=8,size()=7,[0,7],0位置有元素,7就没有了
        // 这是因为theFront是没有用到的内存,theFront = {0,2*arrayLength - 1}
        // 但是theBack不会有影响,会自动退1变成2,6或者14
        for (int i = 0; i <= theBack; i++) // 无环绕没有问题
        {
            // 且i==theFront即可,只可能在theFront没有元素
            if (i == theFront)
                out << "queue[" << i << "] = " << "NULL" << "  ";
            else
                out << "queue[" << i << "] = " << queue[i] << "  ";
            if ((i + 1) % 5 == 0)
                out << endl;
        }
    }
}

template<class T>
ostream& operator<<<>(ostream& out, arrayQueue<T> & theQueue)
{
    theQueue.output(out);
    //arrayQueue<T> temp = theQueue;
    //while (!temp.empty())
    //{
    //    out << temp.front() << "  ";
    //    temp.pop();
    //}
    return out;
}

template<class T>
void arrayQueue<T> ::push(const T & theElement)
{
    if (isLog == true)
    {
        cout << ">>>>>>>>now theBack<old> = " << theBack 
            << " and theFront<old> = " << theFront 
            << " arrayLength<old> = "<<arrayLength<<endl;
        if ((theBack + 1) % arrayLength != theFront)
            cout << ">>>>>>>>so (theBack<old> + 1) % arrayLength = " << (theBack + 1) % arrayLength
            << " != " << "theFront<old> = " << theFront << endl;
    }
    if ((theBack + 1) % arrayLength == theFront)
    {
        if (isLog == true)
        {
            cout << ">>>>>>>>so (theBack<old> + 1) % arrayLength = " << (theBack + 1) % arrayLength
                << " == " << "theFront<old> = " << theFront << endl;
            cout << ">>>>>>>>The queue is about to fill up, now queue size is "
                << size() << " capacity is " << arrayLength << endl;
        }
        T* newQueue = new T[2 * arrayLength];
        int start = (theFront + 1) % arrayLength; //真实的队首元素所在位置
        if (isLog == true)
            cout << ">>>>>>>>now start = (theFront<old> + 1) % arrayLength = " << 
                "("<<theFront<<" + 1) % "<<arrayLength<<" = " <<start<< endl;
        if (start < 2) // 数组没有环绕(只在theFront=0时成立,此时start=1)
        {
            // queue[1,arrayLength-1]的内容复制到newQueue[0,arrayLength-2]
            copy(queue + start, queue + start + arrayLength - 1, newQueue);
            if (isLog == true)
                for (int i = 0; i < 2*arrayLength; i++)
                {
                    if (i <=arrayLength-2) // 在这之前才有元素
                        cout << "newQueue[" << i << "] = " << newQueue[i] << "   ";
                    else
                        cout << "newQueue[" << i << "] = " << "NULL" << "   ";
                    if ((i + 1) % 4 == 0)
                        cout << endl;
                }
        }
        else
        { 
            // 能运行这步程序说明已经有环绕,即theFront≥1,start≥2,theBack<theFront
            // ① 将queue(theFront,arrayLength-1]<=>[start,arrayLength-1]复制到newQueue[0,arrayLength-1-start]
            // 因为copy是前闭后开的,取得到start取不到arrayLength
            copy(queue + start, queue + arrayLength, newQueue);
            // ② 再把queue[0,theBack]复制到newQueue的arrayLength-1-start后边,也就是arrayLength - start
            // theBack可能≥0,也可能没有,若≥0说明有元素正好复制过去,若≤0,说明没有元素NULL,复制不影响
            copy(queue, queue + theBack + 1, newQueue + arrayLength - start);
            if (isLog == true)
            {
                cout << ">>>>>>>>now copy oldQueue[" << start << "," << arrayLength - 1 << "] to newQueue[0,"
                    << arrayLength - 1 - start << "]...\n" << ">>>>>>>>and copy oldQueue[0," << theBack
                    << "] to newQueue[" << arrayLength - start << "," << arrayLength - 2 << "]..." << endl;
                for (int i = 0; i < arrayLength-1; i++)
                {
                    cout << "newQueue[" << i << "] = " << newQueue[i] << "  ";
                    if ((i + 1) % 5 == 0)
                        cout << endl;
                }
            }
        }

        // 切换到新队列并设置前面和后面
        theFront = 2 * arrayLength - 1;
        theBack = arrayLength - 1 - 1;   // 队列的实际大小为arrayLength-1,因为不会插满,把back向前移动1位
        arrayLength *= 2;
        isChangeArrayLength = true;
        queue = newQueue;
        if (isLog == true)
        {
            cout << "theFront<new> = " << theFront
                << "  theBack<new> = " << theBack <<
                " arrayLength<new> = " << arrayLength << endl;
            cout << ">>>>>>>>Now queue is newQueue, but the element "
                << theElement << " has not been inserted " << endl;
        }
    }

    // 第1次插入时theBack=1,第arrayLength-1次插入时theBack=arrayLength-1
    // 直到第arrayLength次插入,上一次的theBack还没改变=arrayLength-1
    // 此时满足(theBack + 1) % arrayLength == theFront == 0 就会扩充arrayLength
    // 因为queue[1,arrayLength-1]的内容复制到newQueue[0,arrayLength-2]
    // 所以要把theBack向前挪一位,theBack = arrayLength-1-1
    // 然后theBack继续执行theBack = (theBack + 1) % arrayLength,变成了arrayLength-1
    theBack = (theBack + 1) % arrayLength;
    if (isLog == true)
        cout << ">>>>>>>>now theBack<new> = " << theBack << " and theFront<new> = " << theFront << endl;
    queue[theBack] = theElement; 
    if (isLog == true)
    {
        cout << ">>>>>>>>after queue insert the element " << theElement << " queue is " << endl;
        output(cout);
        cout << "queue[theBack<new>] = " << "queue[" << theBack << "] = " << queue[theBack] << endl;
        cout << "--------------------------------------------------------------------" << endl;
    }
};
#endif // !chapter9_arrayQueue_
