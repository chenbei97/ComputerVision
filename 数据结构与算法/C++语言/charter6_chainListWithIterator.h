#pragma once
#include "charter5_linearList.h"
#include "charter6_chainNode.h"
#include "myExceptions.h"
#include <sstream>
#include <ostream>
#include <iterator>
template <class T>
class _charter6_chainListWithIterator : public _charter5_linearList<T>
{
public:
	_charter6_chainListWithIterator(int initialCapacity = 10);
	_charter6_chainListWithIterator(const _charter6_chainListWithIterator<T>& theList);
	~_charter6_chainListWithIterator();
	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(std::ostream& out) const;

	// ����Ϊ��Ա����Ϊ������ʹ�õ�����ʱ��Ҫ��������ʵ��
	class _charter6_iterator;
	// �������2���������ص��ǵ��������ʵ��,�ֱ�ָ����������ʵ���Ŀ�ͷ�ͽ�β
	_charter6_iterator begin() { return _charter6_iterator(firstNode); }
	_charter6_iterator end() { return _charter6_iterator(NULL); }
    class _charter6_iterator
    {
    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;
		_charter6_iterator(_charter6_chainNode<T>* theNode = NULL)
        {
			// ������ֻ��1��ʵ��������,begin/end���ǵ��ô˹���ָ�������������
            node = theNode; 
        }

        // ��Ϊ��������2����Ա,��������Ҫ����
		//  *it = *node = node->element
        T& operator*() const { return node->element; }// node����it , ����*it
		// node����it ,�����pnode = &node,pnode->element<=>&node->element,->��Ҫ����
        T* operator->() const { return &node->element; } //�ȼ���Ϊ &it->element

		_charter6_iterator& operator++()   
        {
            node = node->next; return *this; //���ʽ�Ѿ��ı�,node����it�൱�ڷ���++it
        }
		_charter6_iterator operator++(int) // ���ʽֵû�ı�,���صĻ��Ǿ�ֵ
        {
			_charter6_iterator old = *this;
            node = node->next;
            return old; // ,node����it�൱�ڷ���it++
        }

		// �ڵ�֮���Ƿ���ȱȽϵ������ǵĵ�ַ�Ƿ������Ҫ����
        bool operator!=(const _charter6_iterator right) const
        {
            return node != right.node; // ����it != chain.begin() node����it
        }
        bool operator==(const _charter6_iterator right) const
        {
            return node == right.node; // node����it
        }
    protected:
		_charter6_chainNode<T>* node; // ������ʵ�����Դ��Ľڵ�ָ��
    };  

protected:
	int listSize;
	_charter6_chainNode<T>* firstNode; 
	void checkIndex(int theIndex) const;
};

template<class T>
_charter6_chainListWithIterator<T>::_charter6_chainListWithIterator(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	firstNode = NULL; // ��ʼ��ʱҲ��NULL,��һ��Ԫ����˭����֪��
	listSize = 0;
}

template<class T>
_charter6_chainListWithIterator<T>::_charter6_chainListWithIterator(const _charter6_chainListWithIterator<T>& theList)
{
	listSize = theList.listSize; // ˽������listSize����

	if (listSize == 0) // ������ƹ�������Ǹ�������,��ִ�к������Ƶ���ز���
	{
		firstNode = NULL;
		return;
	}

	// 1��ָ��theListͷ�ڵ��ָ��
	_charter6_chainNode<T>* sourceNode = theList.firstNode;
	// std::cout<<firstNode->element<<"   "<< endl; ��ʱ�����firstNodeʲô��û����,��ӡelement��next�ᱨ��
	firstNode = new _charter6_chainNode<T>(sourceNode->element); // ֻ������theListͷ�ڵ������
	//printf("firstNode->element = %d", firstNode->element);
	//std::cout << firstNode->next << std::endl; // û�и���theListͷ�ڵ��ָ����Ϣ

	// ����Ҳ���Ḵ��theList�����ڵ��ָ����Ϣ,��Ϊ����theList��,�����firstNodeֻ��Ҫ��¼�Լ�����һ���ڵ��ַ����
	// ��firstNodeָ�����ʵ��targetNode,��whileѭ���з�����������ָ����һ��
	// �·�ֻ�������Ϣ,sourceNode����û�и���
	/*
		std::cout << sourceNode->next << "  " << sourceNode->next->next << "  " << sourceNode->next->next->next
		<<"   " << sourceNode->next->next->next->next->element << endl;
		�������û��ʼ���ĵ�ַ
	*/
	sourceNode = sourceNode->next; // ����ָ��theList�ĵ�2���ڵ�
	_charter6_chainNode<T>* targetNode = firstNode; // ָ��theList�ĵ�1���ڵ�
	while (sourceNode != NULL) // ����һ���ڵ㲻Ϊ�վͻ�ִ��
	{
		// new�ǿ��ٵ��½ڵ�,��ǰtargetNode��ָ��ָ������¿��ٵĽڵ��ַ
		// �½ڵ�ĵ�ַ����ú�ֻ��1����ַû�б���ʵ��,�������ƶ�targetNode ֻ��ͨ��targetNode =targetNode ->next������
		// ���ٵ��½ڵ�ֻ��element����������theList�Ľڵ�
		targetNode->next = new _charter6_chainNode<T>(sourceNode->element);
		targetNode = targetNode->next; // 
		sourceNode = sourceNode->next;//����ָ����1���ڵ�
	}
	targetNode->next = NULL;
	/*
	* ��ʱ�ٴ�ӡ���ᱨ��,���ƹ����Ѿ����
	std::cout << "���ƹ�������Ժ��ӡ��" << std::endl;
	std::cout << "firstNode = "<<firstNode << "\n"
		<< "firstNode->element = "<<firstNode->element << "   firstNode->next = " << firstNode->next << "\n"
		<< "firstNode->next->next = "<<firstNode->next->next << "   firstNode->next->next->next = " << firstNode->next->next->next << "\n"
		<< "firstNode->next->next->next->next = "<<firstNode->next->next->next->next << "   firstNode->next->next->next->next->next = " << firstNode->next->next->next->next->next << "\n" << std::endl;
	std::cout << "firstNode��theList.firstNode��2����ͬ�ĵ�ַ��" << std::endl;
	std::cout << "theList.firstNode = " << theList.firstNode << "\n"
		<< "theList.firstNode->element = " << theList.firstNode->element << "   theList.firstNode->next = " << theList.firstNode->next << "\n"
		<< "theList.firstNode->next->next = " << theList.firstNode->next->next << "   theList.firstNode->next->next->next = " << theList.firstNode->next->next->next << "\n"
		<< "theList.firstNode->next->next->next->next = " << theList.firstNode->next->next->next->next << "   theList.firstNode->next->next->next->next->next = " << theList.firstNode->next->next->next->next->next << "\n" << std::endl;
	*/
}

template<class T>
_charter6_chainListWithIterator<T>:: ~_charter6_chainListWithIterator()
{
	// ���ƹ�����߲���Ľڵ㶼��new������,��Ҫ������
	while (firstNode != NULL)
	{
		//��ǰ�ڵ㲻Ϊ�վ�һ��ָ��ָ������������һ���ڵ�
		_charter6_chainNode<T>* nextNode = firstNode->next;
		delete firstNode; // ɾ����ǰ�ڵ�
		firstNode = nextNode; // �ٰѵ�ǰ�ڵ�ָ����һ���ڵ�
		listSize--; // �ڵ�Ԫ��Ҳ��Ϊ0
	}
	//printf("listSize = %d\n", listSize);
}

template<class T>
T& _charter6_chainListWithIterator<T>::get(int theIndex) const
{
	checkIndex(theIndex);
	// 1��ͷָ����нڵ����
	_charter6_chainNode<T>* currentNode = firstNode;
	for (int i = 0; i < theIndex; i++)
		currentNode = currentNode->next; // ִ����theIndex��
	return currentNode->element; // ��ʱp�Ѿ���theIndex�ڵ� ���������򼴿�
}

template<class T>
int _charter6_chainListWithIterator<T>::indexOf(const T& theElement) const
{
	// ����ĳ��Ԫ�ص�����,��Ҫ����ͷָ�����ÿ���ڵ�,�ȽϺ�element����Ϣ����
	_charter6_chainNode<T>* currentNode = firstNode;
	int index = 0;  // ��Ϊ������������û��ʵ��,��Ҫ�Լ���������ֵ
	while (currentNode != NULL &&
		currentNode->element != theElement) // ��Ϊ����û�ҵ�ʱִ��while
	{
		// �ƶ�ͷָ�뵽��1���ڵ�
		currentNode = currentNode->next;
		index++;
	}

	// while����,���û�ҵ��ͷ���-1���򷵻�index
	if (currentNode == NULL)
		return -1;
	else
		return index;

}

template<class T>
void _charter6_chainListWithIterator<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	_charter6_chainNode<T>* deleteNode; // ����1���ֲ�ָ��
	if (theIndex == 0)
	{
		// ɾ��ͷ�ڵ�ֻ��Ҫ��firstNodeָ����1���ڵ�,����ڵ�ĵ�ַ��firstNode->next
		deleteNode = firstNode;// ԭ����ͷ�ڵ��ַ�����ᱻdelete
		firstNode = firstNode->next;//ͷ�ڵ�ָ����Ϣ����Ϊԭ��ͷ�ڵ�ָ�����1����firstNode->next
	}
	else
	{
		_charter6_chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
			p = p->next;
		// ��ʱp����index-1��λ��
		deleteNode = p->next; // ɾ����index�ڵ�ĵ�ַ��Ϣ��index-1,����ʹ��p->next
		p->next = p->next->next; // �ѵ�ǰindex-1��ָ��ָ��index+1,��p->next->next(��¼��index��ָ��)
	}
	listSize--;
	delete deleteNode; // ɾ����ַ��������ɾ��
}

template<class T>
void _charter6_chainListWithIterator<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex < 0 || theIndex > listSize)
	{// invalid index
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}

	if (theIndex == 0)// �����ͷ�ڵ�֮ǰ����ڵ�,���´����Ľڵ�ָ��ԭ����ͷ�ڵ㼴��
	{
		// 1.ʹ��1��ָ��ָ����ԭ��ͷ�ڵ���Ϣ�������½ڵ�
		// newfirstNode������ָ�����,��firstNode����һ��ָ��
		_charter6_chainNode<T>* newfirstNode = new _charter6_chainNode<T>(theElement, firstNode);
		// 2.�����ڵ�ͷ�ڵ�ָ��ԭ����ͷ�ڵ�,�������������Ϣ������
		this->firstNode = newfirstNode;//����ͷ�ڵ�
		// 3.��ǰ��ͷ�ڵ㲻Ӱ��ָ�����һ���ڵ�,�������,����ִ�����
	}
	else // index��Ҫ����Ľڵ�,��Ҫ�ҵ�index-1�Ľڵ�,ֻ�ܽ���һ��ָ��ͷ�ڵ��ָ���������
	{
		_charter6_chainNode<T>* p = firstNode;//һ��ָ������ͷ�ڵ��ָ��
		for (int i = 0; i < theIndex - 1; i++)//�ƶ�index-1�ξ͵���ǰ1���ڵ�ĵ�ַ
			p = p->next; // �ȼ���p->next->next->next->...->next(index-1��next) 

		// ����ִֻ����index-1��,��ʱpָ����ǵ�index-1���ڵ�,��������һ������index�ڵ�
		// 1.����1���½ڵ㱣��index�ڵ����Ϣ(��p->next��),Ҫ��(theElement, p->next)��ʽ����
		_charter6_chainNode<T>* theIndexNode = new _charter6_chainNode<T>(theElement, p->next); // �����ڵ��Ҫʹ��new
		// 2.Ҫ��index-1��ָ����Ϣ(p->next)ָ��ǰ�´����Ľڵ�
		p->next = theIndexNode;
		// 3.theIndexNode����ʱ������ԭ��index�ڵ����Ϣ��,������ĺ���
	}
	listSize++; // ��Ա+1
}

template<class T>
void _charter6_chainListWithIterator<T>::output(std::ostream& out) const
{
	for (_charter6_chainNode<T>* currentNode = firstNode;
		currentNode != NULL;
		currentNode = currentNode->next) // ��Ϊ��ʱ�ͼ������µ�ַ����һ���ڵ�
		out << currentNode->element << "  ";//��ӡԪ��
}

template <class T>
ostream& operator<<(ostream& out, const _charter6_chainListWithIterator<T>& x)
{
	x.output(out); return out;
}

template<class T>
void _charter6_chainListWithIterator<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize)
	{
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}

}