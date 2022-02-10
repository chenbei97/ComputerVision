#pragma once
#ifndef chapter12_weightNode_
#define chapter12_weightNode_
#include <ostream>
using namespace std;
template<class T>
struct weightNode
{
	T data; // ����
	double weight; // Ȩ��
	weightNode() {}
	weightNode(const T& theData, double theWeight)
	{
		data = theData;
		weight = theWeight;
	}
	weightNode(const T& theData)
	{
		data = theData;
		weight = 0; // Ĭ��Ȩ��Ϊ0,������ȼ�
	}
	void output(ostream& out) const
	{
		out << "(" << data << "," << weight << ")  ";
	}
};
template<class T>
inline ostream& operator<<(ostream& out, const weightNode<T>& x)
{
	x.output(out);
	return out;
}
#endif // !chapter12_weightNode_
