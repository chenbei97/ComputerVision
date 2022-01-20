#pragma once
#ifndef charter9_arrayQueue_
#define charter9_arrayQueue_
#include <sstream>
#include "charter9_abstractQueue.h"
#include "charter9_queueEmpty.h"
#include "charter1_illegalParameterValue.h"
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
    int theFront;       // ����Ԫ����������ʱ��ǰ1λ
    int theBack;        // ��βԪ������
    int arrayLength;  
    T* queue;
    bool isChangeArrayLength; // ���û�иı������
    bool isPop; // û��ִ�й�1��pop
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
    arrayLength = initialCapacity; // �����Ըı�
    queue = new T[arrayLength];
    theFront = 0; // ��ʼλ�ö���0
    theBack = 0;
    isLog = false;
    isChangeArrayLength = false;
    isPop = false;
};

template<class T>
int arrayQueue<T>::size() const
{
    // 1. 0��theBack < theFront , ˵���Ѿ�Խ��0 , �ֳ�2���ּ���
    // ��1����Ӧ������[theFront+1,arrayLength-1]��Ԫ�ظ���
    // ��[a,b]�������Ԫ�ظ���Ϊb-a+1,�����ⲿ��Ԫ�ظ���ΪarrayLength-theFront-1
    // ��2���ּ���[0,theBack],����ΪtheBack+1
    // �ϲ�ΪarrayLength+theBack-theFront
    // 2. ���theFront<theBack,ֻ��Ҫ����[theFront+1,theBack],��theBack - theFront
    // 3. ���ںϲ�2�����,theBack-theFront��������X,����(X+C)%C�����
    // X���Ǵ���0����С��0,С��0ʱ�൱�ڲ�����1��C,ʣ�µľ���X+C
    // X����0ʱ,����1��C,��ΪX�ٴ�Ҳ����1��C,��ʣ�µ�������ʵ����X
    // theFront=0,theBack=C-1�ﵽ�˲�ֵ���,�����������ΪC-1,Ҳ����arrayLength-1
    // ��С��ʱ����Ȼ�ǳ�ʼtheFront=theBack=0,֮��theBack��ʼ�仯,size=theBack-theFront
    if (theBack > theFront) // ��γ�����·�ע�͵ĳ�����ȫ�ȼ�
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
    return queue[theBack]; // theBack����β��Ԫ�ص�ʵ��λ��
};

template<class T>
void arrayQueue<T> ::pop()
{
    if (theFront == theBack)
        throw queueEmpty();
    if (isLog == true)
        cout << ">>>>>>>>before pop theBack<old> = " << theBack << " and theFront<old> = " << theFront << endl;
    theFront = (theFront + 1) % arrayLength; // pop��ʹ�31���0��
    queue[theFront].~T();  // popɾ������Ԫ��
    isPop = true;
    if (isLog == true)
    {
        cout << ">>>>>>>>after pop theBack<new> = " << theBack << " and theFront<new> = " << theFront << endl;
        cout << ">>>>>>>>after pop queue size is " << size()<<" and queue is "<< endl;
        int idx = 0;
        for (int i = theFront; i <= theBack; i++) // ��Ҫ��<=size(),��theBack��׼ȷ
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
        // pop������theBack��Խ��0Ҳ���ܻ�ûԽ��0,����theFront�������0
        // ����ʹ��theBack��theFront�Ĵ�С��ϵ�ж�
        if (isLog == true)
        {
            if (theFront > theBack)
                cout << ">>>>>>>>theBack has crossed 0, it will be 0 �� theBack < theFront, queue is circular" << endl;
            else
                cout << ">>>>>>>>theBack has not passed 0, it will be thefront < theback, queue not circular " << endl;
        }
        for (int i = 0; i < arrayLength; i++) // ������size(),����3-31������Ԫ�ص�,����0-2û��
            //size=29,��ôqueue[29],queue[30],queue[31]��û�б���ӡ����,����Ӧ����arrayLength
        {
            // ���黷�ƣ�����theBack�ܹ��ص�{0,arrayLength-1}��theFront����0
            // �������û��pop��,theFront����={0,arrayLength-1}
            // ��theBackҪ����arrayLength-1ʱ�����̱�ΪarrayLength-2,�������ǲ������theFront
            // ��ΪtheBack=theFront�����Ƕӿ�Ҳ�����Ƕ���������,Ϊ�˱����ͻ,���������ͻ���������
            // �������pop��,theBack�Ϳ��Իص�{0,arrayLength-1}��,��ΪtheFront���ʱ���Ѿ���{0,arrayLength-1}��ǰ��
            // ���ܵ����� �٣�theBackС��theFront,˵��theBack>=0
            // ����theBack=2,theFront = 4, ��ʱi = 3, 4��û��Ԫ��, ����0,1,2��Ԫ��
            // ����theBack< i <= theFront , ��3,4����ӡ����
            if (theFront > theBack)
            {
                if (theBack < i && i <= theFront)
                    out << "queue[" << i << "] = " << "NULL" << "  ";
                else
                    out << "queue[" << i << "] = " << queue[i] << "  ";
            }
            else
            {
                // ���ܵ����� �ڣ�theBack����theFront,˵��theBackûԽ��0
                // ����theBack=6,theFront = 2, ��ʱi = 3, 4,5,6��Ԫ��
                //  ����[0,1,2]��(theBack,arrayLength-1]û��Ԫ��
                // ����theBack< i <= theFront , ��3,4����ӡ����
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
        // ���û��չ������,����capacity=4,size()=3,[0,3]��3λ����Ԫ��,0û��
        // ֻҪ��չ������,����capacity=8,size()=7,[0,7],0λ����Ԫ��,7��û����
        // ������ΪtheFront��û���õ����ڴ�,theFront = {0,2*arrayLength - 1}
        // ����theBack������Ӱ��,���Զ���1���2,6����14
        for (int i = 0; i <= theBack; i++) // �޻���û������
        {
            // ��i==theFront����,ֻ������theFrontû��Ԫ��
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
        int start = (theFront + 1) % arrayLength; //��ʵ�Ķ���Ԫ������λ��
        if (isLog == true)
            cout << ">>>>>>>>now start = (theFront<old> + 1) % arrayLength = " << 
                "("<<theFront<<" + 1) % "<<arrayLength<<" = " <<start<< endl;
        if (start < 2) // ����û�л���(ֻ��theFront=0ʱ����,��ʱstart=1)
        {
            // queue[1,arrayLength-1]�����ݸ��Ƶ�newQueue[0,arrayLength-2]
            copy(queue + start, queue + start + arrayLength - 1, newQueue);
            if (isLog == true)
                for (int i = 0; i < 2*arrayLength; i++)
                {
                    if (i <=arrayLength-2) // ����֮ǰ����Ԫ��
                        cout << "newQueue[" << i << "] = " << newQueue[i] << "   ";
                    else
                        cout << "newQueue[" << i << "] = " << "NULL" << "   ";
                    if ((i + 1) % 4 == 0)
                        cout << endl;
                }
        }
        else
        { 
            // �������ⲽ����˵���Ѿ��л���,��theFront��1,start��2,theBack<theFront
            // �� ��queue(theFront,arrayLength-1]<=>[start,arrayLength-1]���Ƶ�newQueue[0,arrayLength-1-start]
            // ��Ϊcopy��ǰ�պ󿪵�,ȡ�õ�startȡ����arrayLength
            copy(queue + start, queue + arrayLength, newQueue);
            // �� �ٰ�queue[0,theBack]���Ƶ�newQueue��arrayLength-1-start���,Ҳ����arrayLength - start
            // theBack���ܡ�0,Ҳ����û��,����0˵����Ԫ�����ø��ƹ�ȥ,����0,˵��û��Ԫ��NULL,���Ʋ�Ӱ��
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

        // �л����¶��в�����ǰ��ͺ���
        theFront = 2 * arrayLength - 1;
        theBack = arrayLength - 1 - 1;   // ���е�ʵ�ʴ�СΪarrayLength-1,��Ϊ�������,��back��ǰ�ƶ�1λ
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

    // ��1�β���ʱtheBack=1,��arrayLength-1�β���ʱtheBack=arrayLength-1
    // ֱ����arrayLength�β���,��һ�ε�theBack��û�ı�=arrayLength-1
    // ��ʱ����(theBack + 1) % arrayLength == theFront == 0 �ͻ�����arrayLength
    // ��Ϊqueue[1,arrayLength-1]�����ݸ��Ƶ�newQueue[0,arrayLength-2]
    // ����Ҫ��theBack��ǰŲһλ,theBack = arrayLength-1-1
    // Ȼ��theBack����ִ��theBack = (theBack + 1) % arrayLength,�����arrayLength-1
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
#endif // !charter9_arrayQueue_
