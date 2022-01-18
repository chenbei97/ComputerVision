#include "charter5_arrayList.h"
#include "charter1_illegalParameterValue.h"
#include<sstream>
//template<class T>
//_charter5_arrayList<T>* _charter5_paL; // ����1��ȫ��ָ��������ⲿcpp�ļ�����
template<class T>
_charter5_arrayList<T>::_charter5_arrayList(int initialCapacity)
{
	// Ĭ�Ϲ���ʵ��
	if (initialCapacity < 1)
	{
		std::ostringstream s; //����1�����ڴ����ַ�������
		s << "Initial Capacity = " << initialCapacity << "  Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	element = new T[arrayLength]; // ��̬�������� �������������Ӧdelete [] element
	listSize = 0; //��ʱ0��Ա
	//_charter5_paL = this; // ȫ��ָ��ָ��this
}

template<class T>
_charter5_arrayList<T> ::_charter5_arrayList(const _charter5_arrayList<T>& theList)
{
	// ���ƹ���ʵ�֣����Բο�charter5_01_���Ա�ĳ�����;�����.cpp�Եı䳤һά����ʵ��
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];
	// element�Ǹ�ָ��,ָ��+�����ǿ��Ե�,��Դ������Ԫ��(��������)��������ǰָ��ָ��ĵ�ַ,�����ַ������������arrayLength
	// ��ʵ���൱����ȫ������
	std::copy(theList.element, theList.element + listSize, element); // copy����Ҫ���뿪ͷ��β��Ŀ��
	//_charter5_paL = this; // ȫ��ָ��ָ��this
}

template<class T>
T& _charter5_arrayList<T>::get(int theIndex) const
{
	checkIndex(theIndex); //�ȼ����û���������
	return element[theIndex];
}

template<class T>
int _charter5_arrayList<T>::indexOf(const T& theElement) const
{
	int theIndex = (int)(std::find(element, element + listSize, theElement) - element);
	if (theIndex == listSize) // listSize��ȡ�����ı߽�[0,listSize-1] or[0,listSize)
		return -1;
	else return theIndex;
}

template<class T>
void _charter5_arrayList<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	// theIndex��Ҫɾ����λ��,theIndex + 1�Ǻ�1��Ԫ��λ��
	// element��һ��ָ��,ָ���˺�1��Ԫ��,��ָ���βԪ�صĺ�1��
	// ��[index+1,listSize)֮���Ԫ�ؿ���theIndex��λ����ʼ,Ҳ���Ǻ����Ԫ��������ǰ�ƶ�1����λ
	std::copy(element + theIndex + 1, element + listSize, element + theIndex);
	// --listSize�Ǹ���������,--��ǰ���ʽ�ȸı�
	element[--listSize].~T(); // ������������,ԭ��ֻ�ǿ���,����listSize-1�����Ԫ�ػ�����Ҫ���
}

template<class T>
void _charter5_arrayList<T>::changeLength1D(T*& pa, int oldLength, int newLength)
{
	if (newLength < 0)
		throw illegalParameterValue("new length must be >=0");
	T* temp = new T[newLength];
	// ����µĳ��ȱ䳤��ิ��ԭ������ô��Ԫ��,�����̾͸��Ƶ�ǰ��ô��Ԫ��
	int number = std::min(oldLength, newLength);//Ҫ���Ƶ�Ԫ�ظ���
	std::copy(pa, pa + number, temp); // a�Ǹ�T���͵�ָ����������� ����+����
	delete[] pa; // ɾ��ԭ��������Ԫ��
	pa = temp; // ָ���µ�����
}

template<class T>
void _charter5_arrayList<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex <0 || theIndex > listSize)
	{
		std::ostringstream s;
		s << "index = " << theIndex << "   size = " << listSize;
		throw illegalParameterValue(s.str());
	}
	if (listSize == arrayLength)
	{
		// ��������,����չ����Ϊ2������
		// ֮����ʹ��2�����ݽṹ���㷨��Ӧ��C++����������P101ҳ�Ķ���5-1����
		// �������1���˷��������������鳤�ȣ���ôʵʩһϵ�����Ա�Ĳ�������Ҫ��ʱ���벻�øı����鳤�ȶԱȣ���������1����������
		// �����ÿ�β��붼������1������β��1��,n�β����������鳤�ȵ�ʱ���Ǧ�(n^2),��ֱ�����ӳ���n,β��n��Ϊ��(n)
		changeLength1D(element, arrayLength, 2 * arrayLength); // element��1��ָ��
		arrayLength *= 2;
	}
	// [theIndex,listSize-1]֮���Ԫ�������ƶ�,��ʼλ���Ǻ�1��Ԫ��λ��listSize + 1
	// copy_backward��copy�Ĳ�ͬ����ǰ���Ǵ����Ҷ˵�Ԫ�ؿ�ʼ�ƶ�,�����Ǵ���˵�Ԫ���ƶ�
	// ��ʡһ��ʱ��
	std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);
	element[theIndex] = theElement; //����λ�ø�ֵҪ�����Ԫ��
	listSize++; //Ԫ�ظ���������
}

template<class T>
void _charter5_arrayList<T>::output(std::ostream& out) const
{
	// ������Ԫ�ظ��Ƶ��������,���������������
	std::copy(element, element + listSize, std::ostream_iterator<T>(std::cout, "   "));
}

template<class T> // ������������ص�Ҳ������������
std::ostream& operator << (std::ostream& out, const _charter5_arrayList<T>& x)
{
	// �������Ϊ����������Ա�ʵ��������,����ʹ��cout
	x.output(out); // ����output��������,�Ϳ���ֱ�Ӵ�ӡ���Ա���
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