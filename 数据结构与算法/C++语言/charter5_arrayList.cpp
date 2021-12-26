#include "charter5_arrayList.h"
#include "charter1_illegalParameterValue.h"
#include<sstream>
//template<class T>
//_charter5_arrayList<T>* _charter5_paL; // 声明1个全局指针可用于外部cpp文件调用
template<class T>
_charter5_arrayList<T>::_charter5_arrayList(int initialCapacity)
{
	// 默认构造实现
	if (initialCapacity < 1)
	{
		std::ostringstream s; //创建1个用于传递字符串的流
		s << "Initial Capacity = " << initialCapacity << "  Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	element = new T[arrayLength]; // 动态开辟数组 析构函数必须对应delete [] element
	listSize = 0; //暂时0成员
	//_charter5_paL = this; // 全局指针指向this
}

template<class T>
_charter5_arrayList<T> ::_charter5_arrayList(const _charter5_arrayList<T>& theList)
{
	// 复制构造实现：可以参考charter5_01_线性表的抽象类和具体类.cpp对的变长一维数组实现
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];
	// element是个指针,指针+操作是可以的,把源的所有元素(不是容量)拷贝到当前指针指向的地址,这个地址的连续容量是arrayLength
	// 其实就相当于完全复制了
	std::copy(theList.element, theList.element + listSize, element); // copy函数要求传入开头结尾和目标
	//_charter5_paL = this; // 全局指针指向this
}

template<class T>
T& _charter5_arrayList<T>::get(int theIndex) const
{
	checkIndex(theIndex); //先检查有没有这个索引
	return element[theIndex];
}

template<class T>
int _charter5_arrayList<T>:: indexOf(const T& theElement) const
{
	int theIndex = (int)(std::find(element, element + listSize, theElement) - element);
	if (theIndex == listSize) // listSize是取不到的边界[0,listSize-1] or[0,listSize)
		return -1;
	else return theIndex;
}

template<class T>
void _charter5_arrayList<T>:: erase(int theIndex)
{
	checkIndex(theIndex);
	// theIndex是要删除的位置,theIndex + 1是后1个元素位置
	// element是一个指针,指向了后1个元素,并指向结尾元素的后1个
	// 把[index+1,listSize)之间的元素拷贝theIndex的位置起始,也就是后面的元素整体向前移动1个单位
	std::copy(element + theIndex + 1, element + listSize, element + theIndex);
	// --listSize是个数减少了,--在前表达式先改变
	element[--listSize].~T(); // 调用析构函数,原来只是拷贝,但是listSize-1的这个元素还在需要清除
}

template<class T>
void _charter5_arrayList<T>::changeLength1D(T*& pa, int oldLength, int newLength)
{
	if (newLength < 0)
		throw illegalParameterValue("new length must be >=0");
	T* temp = new T[newLength];
	// 如果新的长度变长最多复制原来的那么多元素,如果变短就复制当前这么多元素
	int number = std::min(oldLength, newLength);//要复制的元素个数
	std::copy(pa, pa + number, temp); // a是个T类型的指针的引用类型 可以+操作
	delete[] pa; // 删除原来的容器元素
	pa = temp; // 指向新的容器
}

template<class T>
void _charter5_arrayList<T>::  insert(int theIndex, const T& theElement)
{
	if (theIndex <0 || theIndex > listSize)
	{
		std::ostringstream s;
		s << "index = " << theIndex << "   size = " << listSize;
		throw illegalParameterValue(s.str());
	}
	if (listSize == arrayLength)
	{
		// 数组已满,则拓展数组为2倍长度
		// 之所以使用2《数据结构、算法与应用C++语言描述》P101页的定理5-1决定
		// 如果按照1个乘法因子来增加数组长度，那么实施一系列线性表的操作所需要的时间与不用改变数组长度对比，至多增加1个常数因子
		// 如果表每次插入都是增加1个长度尾插1个,n次插入增加数组长度的时间是Θ(n^2),而直接增加长度n,尾插n次为Θ(n)
		changeLength1D(element, arrayLength, 2 * arrayLength); // element是1个指针
		arrayLength *= 2;
	}
	// [theIndex,listSize-1]之间的元素向右移动,初始位置是后1个元素位置listSize + 1
	// copy_backward和copy的不同在于前者是从最右端的元素开始移动,后者是从左端的元素移动
	// 节省一定时间
	std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);
	element[theIndex] = theElement; //插入位置赋值要插入的元素
	listSize++; //元素个数增加了
}

template<class T>
void _charter5_arrayList<T>:: output( std::ostream& out) const
{
	// 把所有元素复制到输出流中,利用输出流迭代器
	std::copy(element, element + listSize, std::ostream_iterator<T>(std::cout, "   "));
}

template<class T> // 重载运算符返回的也必须是流对象
std::ostream operator << (std::ostream out, const _charter5_arrayList<T>& x)
{
	// 输入参数为流对象和线性表实例的引
	x.output(out); // 利用output函数重载,就可以直接打印线性表了
	return out;
}

template<class T>
void _charter5_arrayList<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize)
	{
		std::ostringstream s;
		s << "index = " << theIndex << "   size - " << listSize;
		throw illegalParameterValue(s.str());
	}
}

