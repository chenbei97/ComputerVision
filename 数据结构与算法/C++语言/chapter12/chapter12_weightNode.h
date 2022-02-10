#pragma once
#ifndef chapter12_weightNode_
#define chapter12_weightNode_
#include <ostream>
using namespace std;
template<class T>
struct weightNode
{
	T data; // 数据
	double weight; // 权重
	weightNode() {}
	weightNode(const T& theData, double theWeight)
	{
		data = theData;
		weight = theWeight;
	}
	weightNode(const T& theData)
	{
		data = theData;
		weight = 0; // 默认权重为0,最低优先级
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
