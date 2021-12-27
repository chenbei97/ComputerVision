#pragma once
/*
��ͷ�ļ��������_charter5_vectorList��charter5_arrayList.h����_charter5_arrayList����ͬ��Ҳ�в�ͬ��
_charter5_arrayList�����鳤����Ҫ��̬����,_charter5_vectorList���ư���ԭ������50%-100%����
_charter5_vectorListû��һ�����캯����_charter5_arrayList�Ĺ��캯���ȼ�
���߶���empty��size��output������<<����,�ǵȼ۵�
_charter5_vectorList��erase��insert�������в�ͬ,��Ҫ�����ڴ��ַ,����˵������λ��,���������������
��������׳����쳣�����ǲ�ͬ��,checkIndex������

arrayList��������ʵ��,��Ҫ˽�б���arrayLength,��Ĭ�Ϲ��캯���д���
����Ҫ˽�б���listSize,��ʼ��Ϊ0,ͨ��insert�����н���++
element��һ��T���͵Ķ�̬�����ָ��
�Ӷ�empy������ͨ��listSize�Ƿ�Ϊ0���ж�,sizeҲ��ͨ��listSize
get�������ľ���return element[theIndex];�������������ķ�ʽ,����ָ��Ҳ����ʹ��[]����
indexOf��������theElementԪ���ǽ���element���������˵�ָ��,ʹ��find��������
insert������Ҫ����changeLength1Dʵ��,���и�������
erase��Ҫ����copyʵ��,Ȼ�����Ԫ�ظ�������
checkIndex�����׳�����ΪillegalParameterValue

vectorList����vectorʵ��,����˽�б���,element��һ��vector<T>��ָ��
empy,sizeֱ��ʹ��vector�����÷���empy��size,������Ϊ����û������������
get�����������return (*element)[theIndex];��Ϊvector֧��[]����,������Ҫ������,����ָ�벻֧��ֱ��[]����
indexOf��������theElementԪ��Ҳ�ǽ���element,��������element���������͵�ָ��,��ô���Դ�����������,ʹ�ü�ͷ���������ʹ��
insert��������vector�Դ��ķ���inser(iterator,val) or inser(iterator,n,val)=>����n��val  �����Լ���д��̬��չ��ȵĺ���
erase������insert����ͬ��,����vector�Դ����� erase
checkIndex�����׳�����ΪillegalIndex

output��<<���ص�ʵ��2������ȫһ��

*/#include "charter5_linearList.h"
#include "charter1_illegalIndex.h"
#include "charter1_illegalParameterValue.h"
#include <vector>
#include <ostream>
#include <iostream>
#include <sstream>
// statement
template<class T>
class _charter5_vectorList : public _charter5_linearList<T>
{
public:
	_charter5_vectorList(int initialCapacity = 10);
	_charter5_vectorList(const _charter5_vectorList<T>& theList);
	~_charter5_vectorList() { delete element; }
	bool empty() const { return element->empty(); }// ����vector�ķ���empty
	int size() const { return (int)element->size(); }// ����vector�ķ���size
	int indexOf(const T& theElement) const; // theElement��vector����,Ԫ����T����
	T& get(int theIndex) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);// �������T���͵�Ԫ��
	void output(std::ostream& out) const;
	int capacity() const { return (int)element->capacity(); };// ����vector�ķ���capacity

	typedef typename std::vector<T> ::iterator iterator; // ��std::vector<T> ::iterator����Ϊiterator
	iterator begin() { return element->begin(); }// ���صľ���vector�ĵ���������
	iterator end() { return element->end(); } // ��Ĺ��к���begin��end���ʹ�õ���vector�����ķ���begin��end

private:
	void checkIndex(int theIndex) const;
	std::vector<T>* element; // ��vector���͵�ָ��,��������,����ʹ��delete����delete []
};

// constructed
template<class T>
_charter5_vectorList<T> ::_charter5_vectorList(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		std::ostringstream s;
		s << "initial capcaity = " << initialCapacity << "  must be > 0";
		throw illegalParameterValue(s.str());
	}
	element = new std::vector<T>; // ��̬������ָ��,��vector���͵�ָ��
}

template<class T>
_charter5_vectorList<T> ::_charter5_vectorList(const _charter5_vectorList<T>& theList)
{
	element = new std::vector<T>(*theList.element); // ���ƹ����ǰ�vectorList��ʵ����˽������element(1������)��ָ������ô���
	// �����Ͼ���һ����������������,vector�������Ĺ��캯��
	//vector<int> arrint1(10);
	//vector<int>arrint2(arrint1);
	//cout << arrint2.capacity() << endl;
	// �����൱�ڰ�*theList.element��������element,����������ΪtheList.element��ָ��
}

template<class T>
void _charter5_vectorList<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= size())
	{
		ostringstream s;
		s << "index = " << theIndex << " size = " << size();
		throw illegalIndex(s.str());
	}
}

template<class T>
T& _charter5_vectorList<T>::get(int theIndex) const
{
	checkIndex(theIndex);
	return (*element)[theIndex];
}

template<class T>
int _charter5_vectorList<T>::indexOf(const T& theElement) const
{
	// �����������Ԫ��theElement��������λ��
	// element��һ��vector������ָ��,Ҳ�߱����÷���begin��end,����Ҫʹ�ü�ͷ->�����
	int theIndex = (int)(find(element->begin(), element->end(),
		theElement)
		- element->begin());//��������Ҫ��ȥelement,����Ҳ��,find���ص��ǵ�1��Ԫ��

	// check if theElement was found
	if (theIndex == size())
		// not found
		return -1;
	else return theIndex;
}

template<class T>
void _charter5_vectorList<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	element->erase(begin() + theIndex);// ����vector�Դ��ķ���erase
}

template<class T>
void _charter5_vectorList<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex < 0 || theIndex > size())
	{// invalid index
		ostringstream s;
		s << "index = " << theIndex << " size = " << size();
		throw illegalIndex(s.str());
	}
	element->insert(element->begin() + theIndex, theElement);//����vector�Դ��ķ���insert ָ�������λ�ú�Ԫ��
}

template<class T>
void _charter5_vectorList<T>::output(ostream& out) const
{
	copy(element->begin(), element->end(), ostream_iterator<T>(cout, "  "));
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const _charter5_vectorList<T>& x)
{
	x.output(out); return out;
}





