#pragma once
#ifndef chapter10_dictionaryArray_
#define chapter10_dictionaryArray_
#include <ostream>
#include <sstream>
#include "chapter10_dictionary.h"
#include "chapter1_illegalParameterValue.h"
using namespace std;
template<class K, class V>
class dictionaryArray : public dictionary<K, V>
{
public:
    dictionaryArray(int initiCapacity = 10);
    ~dictionaryArray();
    bool empty() const { return dSize == 0; }
    int size() const { return dSize; }
    pair<const K, V>* find(const K&) const;
    void erase(const K&);
    void insert(const pair<const K, V>&);
    void output(ostream& out) const;
    friend ostream& operator<<<> (ostream&, const dictionaryArray<K, V>&);
protected:
    void changeCapacity(pair<K, V>*& , int , int);
    int checkKey(const K& ) const;
    pair<K, V> *data; // ����ָ��洢����,key��value�����Ըı䲻ʹ�ô���ͼ��
    int dCapacity; // �ֵ���������
    int dSize; // �ֵ��ֵ�Ը���
};

template<class K, class V>
dictionaryArray<K, V>::dictionaryArray(int initCapacity) 
{
    if (initCapacity < 1)
    {
        ostringstream s; 
        s << "Initial Capacity = " << initCapacity << "  Must be > 0";
        throw illegalParameterValue(s.str());
    }
    dCapacity = initCapacity;
    data = new pair<K,V> [dCapacity]; 
    dSize = 0;
}

template<class K, class V>
dictionaryArray<K, V>::~dictionaryArray()
{
    if (data != NULL)
    {
        delete[] data;
        data = NULL;
    }
    delete data;
}

template<class K, class V>
pair<const K, V>* dictionaryArray<K, V>::find(const K& theKey) const
{
    int theIndex = checkKey(theKey);
    if (theIndex >= 0)
    {
        // ֱ��return &data[theIndex]�ǲ�ƥ�䷵�����͵�
        // const K���͵�ָ��һ����ʼ���Ͳ��ɸ���,����ֻ���ڳ�ʼ��ʱ�����
        // ��ô����������ƹ���,����Ϊ��ָ������,��Ҫͨ��new���õ�1����ַ
        pair<const K, V>* newp =
            new pair<const K, V>{ data[theIndex].first,data[theIndex].second };
        return newp;
    } 
    cout << "There is no such keyword " << theKey << endl;
    return NULL;
}

template<class K, class V>
void dictionaryArray<K, V>::erase(const K& theKey) 
{
    int theIndex = checkKey(theKey); // ���ؼ����Ƿ���ڲ����عؼ�������λ��
    if (theIndex < 0)
    {
        cout << "There is no such keyword " << theKey << endl;
        return;
    }
    pair<K, V>* newData = new pair<K, V>[dSize - 1];
    copy(data, data + theIndex, newData);
    copy(data + theIndex + 1, data + dSize, newData + theIndex);
    --dSize;
    delete [] data;
    data = newData;
}

template<class K, class V>
void dictionaryArray<K, V>::changeCapacity(pair<K, V>*& oldData, int oldCapacity, int newCapacity)
{
    if (newCapacity < 0)
        throw illegalParameterValue("new length must be >=0");
    pair<K, V>* newData = new pair<K, V>[newCapacity];
    int number = min(oldCapacity, newCapacity);
    copy(oldData, oldData + number, newData);
    delete[] oldData; 
    oldData = newData;
}

template<class K, class V>
void dictionaryArray<K, V>::insert(const pair<const K, V>& thePair)
{
    if (dSize == dCapacity)
    {
        changeCapacity(data, dCapacity, 2 * dCapacity); 
        dCapacity *= 2;
    }
     //�ȼ�������Ƿ��ظ�,���ظ���¼��λ�ø�д����
    for (int i = 0; i < dSize; i++)
        if (thePair.first == data[i].first)
        {
            data[i].second = thePair.second; 
            cout << "thePair " << thePair.first << " is overwrited in array[" << i << "]" << endl;
            return;
        }
            
    // û���ظ��ٱȽ�key�Ĵ�С��ϵ,�ҵ�Ӧ�������λ��
    int theIndex = 0; 
    while (data[theIndex].first < thePair.first
        && theIndex<dSize)
    {
        theIndex++;
    }
    cout << "thePair "<<thePair.first<<" is inserted in array["<<theIndex <<"]"<< endl;
    copy_backward(data + theIndex, data + dSize, data + dSize + 1);
    data[theIndex] = thePair; 
    dSize++; 
}

template<class K, class V>
void dictionaryArray<K, V>::output(ostream& out) const
{
    if (dSize == 0)
    {
        out << "the dictArray is empty!" << endl;
        return;
    }
    out << "(key,value) as follows\n";
    for (int i = 0; i < dSize; i++)
        out << "(" << data[i].first << "," << data[i].second << ") ";
    out << "\n";
}

template<class K, class V>
ostream& operator<<<> (ostream& out, const dictionaryArray<K, V>& theDict)
{
    if (theDict.dSize == 0)
        out << "the dictArray is empty!" << endl;
    theDict.output(out);
    return out;
}

template<class K, class V>
int dictionaryArray<K,V>::checkKey(const K& theKey) const
{
    int i = 0;
    for (i = 0; i < dSize; i++)
        if (theKey == data[i].first)
        {
            return i; // �����������key������λ��
        }
    return -1; // û��������key
}
#endif // !chapter10_dictionaryArray_
