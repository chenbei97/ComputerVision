#pragma once
#ifndef chapter12_maxPriorityQueue_
#define chapter12_maxPriorityQueue_
using namespace std;
#include <iostream>
#include "chapter12_abstractMaxPriorityQueue.h"
#include "chapter12_weightNode.h"
#include "chapter9_queueEmpty.h"
// ������ȼ�����ʹ����������ʵ��
template<class T>
class maxPriorityQueue :public abstractMaxPriorityQueue<weightNode<T>>
{
public:
	maxPriorityQueue(int theCapacity);
	~maxPriorityQueue();
	bool empty() const { return queueSize == 0; }
	int size() const { return queueSize; }
	int getCapacity() const { return capacity; }
	const weightNode<T>& top();
	void pop();
	void push(const weightNode<T>& theElement);
	void outputByWeight(ostream&) const;
	friend ostream& operator<<<>(ostream& out, const maxPriorityQueue<T>&);
protected:
	int queueSize;
	int capacity;
	int getMaxWeightIndex();
	weightNode<T> * data;
};
template<class T>
maxPriorityQueue<T>::maxPriorityQueue(int theCapacity)
{
	capacity = theCapacity;
	data = new weightNode<T>[capacity];
	queueSize = 0;
}

template<class T>
maxPriorityQueue<T>::~maxPriorityQueue()
{
	if (data != NULL)
	{
		delete[] data;
		data = NULL;
		delete data;
	}
}

template<class T>
void maxPriorityQueue<T> ::push(const weightNode<T>& theElement)
{
	if (queueSize == capacity)
	{
		weightNode<T>* temp = new weightNode<T>[capacity * 2];
		copy(data, data + queueSize, temp);
		delete[] data;
		capacity *= 2;
		data = temp;
	}
	data[queueSize] = theElement;
	queueSize++;
}

template<class T>
void  maxPriorityQueue<T> ::pop()
{
	if (queueSize == 0)
		throw queueEmpty();
	weightNode<T>* temp = new weightNode<T> [capacity]; // ����������Ҫ��
	int index = getMaxWeightIndex();
	copy(data, data + index, temp);
	copy(data + index + 1, data + queueSize, temp + index);
	delete[] data;
	data = temp;
	queueSize--;
}

template<class T>
const weightNode<T>& maxPriorityQueue<T> ::top()
{
	if (queueSize == 0)
		throw queueEmpty();
	return data[getMaxWeightIndex()];
}

template<class T>
int maxPriorityQueue<T> ::getMaxWeightIndex()
{
	double maxWeight = data[0].weight;
	int index = 0;
	for (int i = 1; i < queueSize; i++)
	{
		if (data[i].weight > maxWeight)
		{
			maxWeight = data[i].weight; // ���Ȩ��һ��,���ص���������е��Ǹ�Ԫ��
			index = i;
		}
	}
	//cout << "the index is " << index << endl;
	return index; // �������Ȩ��Ԫ������λ��
}

template<class T>
void maxPriorityQueue<T> ::outputByWeight(ostream& out) const
{
	if (queueSize == 0)
	{
		out << "the queue is empty!" ;
		return;
	}
	int count = 0;
	int* rank = new int[queueSize]; // rank���ڵõ�����
	for (int i = 0; i < queueSize; i++)
		rank[i] = 0; // ������ȫ����ʼ��Ϊ0
	for (int i = 1; i < queueSize; i++)
		for (int j = 0; j < i; j++)
		{
			count++;
			if (data[j].weight <= data[i].weight) rank[i]++;
			else rank[j]++;
		} // ��������õ�����Ȩ�ص�����
	cout << "size is " << queueSize << endl;
	weightNode<T>* temp = new weightNode<T>[queueSize]; // temp���ڴ��������data
	for (int i = 0; i < queueSize; i++)
	{
		temp[rank[i]] = data[i]; // rank[i]��a[i]���ƶ�����λ��
	}
	// �����������
	for (int i = queueSize-1; i >= 0; i--)
		out << temp[i]; // �Ӵ�С���
	delete[] temp;
}

template<class T>
ostream& operator<<<>(ostream& out, const maxPriorityQueue<T>& x)
{
	x.outputByWeight(out);
	return out;
}
#endif // !chapter12_maxPriorityQueue_
