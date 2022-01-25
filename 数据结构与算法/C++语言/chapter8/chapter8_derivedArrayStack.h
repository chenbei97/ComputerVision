#pragma once
#ifndef chapter8_derivedArrayStack_
#define chapter8_derivedArrayStack_
// �������������������������Ա�ľ�����arrayList�ͳ���ջ��abstractStack
// ��Ϊ�����Ĺ�ϵ,�����ִ��Ч�ʱȽϵ�,��ͷ�ļ�<charter8_arrayStack.h>�лᶨ����abstractStackֱ��ʵ�ֵľ�����
// ���̳е�����������ͷ�ļ�Ϊ<charter5_arrayList.h>,��������ļ�������ʷԭ��û�аѶ����ʵ��д��һ��
// ��ʵ�ֲ��ַ�����<charter5_arrayList�ķ��ļ�ʵ��.cpp>���У����ڰѶ��������Ҫ����һ��
// ��ô�̳����ͷ�ļ��������,���԰������Ͷ������һ����������Ա�,������ͷ�ļ�<charter8_arrayList.h>��
#include "chapter8_arrayList.h"
#include "chapter8_abstractStack.h"
#include "chapter8_stackEmpty.h"
template<class T>
class derivedArrayStack : private _chapter8_arrayList<T>, public abstractStack<T>
{
public:
	derivedArrayStack(int initialCapacity = 10) : _chapter8_arrayList<T>(initialCapacity) {} // ���캯��ֱ�Ӽ̳�
	bool empty() const { return _chapter8_arrayList<T> ::empty(); } // emptyֱ�Ӽ̳�
	int size() const { return _chapter8_arrayList<T>::size(); } // sizeֱ�Ӽ̳�
	// ����ջ��ľ���ʵ��
	T& top(); 
	void pop();
	void push(const T&);
	friend ostream& operator<<<>(ostream&, const derivedArrayStack<T>&);
private:
	void output(std::ostream& out) const ; // ��дoutput����
};

template<class T>
T& derivedArrayStack<T> ::top()
{
	// �·���������ȷ��,�����и��ط���Ҫ����,get����������ʱ�׳����쳣��illegalParameterValue
	// ��ô�����ⲿ��ʹ����Ա��˵,������֪������̳е��߼�,����Ӧ�ð����������쳣תΪջ�����͵��쳣
	//if (_charter8_arrayList<T>::empty())
	//	throw stackEmpty();
	//return  _charter8_arrayList<T>::get(_charter8_arrayList<T>::size() - 1); // ��ȡ�Ҷ˵�Ԫ�� ��listSize-1
	try { return _chapter8_arrayList<T>::get(_chapter8_arrayList<T>::size() - 1); }
	catch (illegalParameterValue) { throw stackEmpty(); } // ����try_catch�ṹ����ת��
}

template<class T>
void derivedArrayStack<T> ::pop()
{
	if (_chapter8_arrayList<T>::empty())
		throw stackEmpty();
	  _chapter8_arrayList<T>::erase(_chapter8_arrayList<T>::size() - 1); // ɾ������listSize-1��Ԫ��
}

template<class T>
void derivedArrayStack<T> ::push(const T& theElement)
{
	  _chapter8_arrayList<T>::insert(_chapter8_arrayList<T>::size(), theElement); // �����λ����listSize
}

template<class T>
void derivedArrayStack<T> ::output(std::ostream &out) const
{
	// ԭ����ʵ�ַ���
	/*std::copy(element, element + listSize, std::ostream_iterator<T>(std::cout, "   "));*/
	if (_chapter8_arrayList<T>::size() == 0)
		throw stackEmpty();
	for (int i = 0; i < _chapter8_arrayList<T>::size(); i++)
	{
		cout << _chapter8_arrayList<T>::element[i] << "  ";
		if ((i + 1) % 10 == 0)
			out << endl;
	}
}

template<class T>
ostream& operator<<<>(ostream& out, const derivedArrayStack<T>& theStack)
{
	theStack.output(out);
	return out;
}
#endif // !chapter8_derivedArrayStack_
