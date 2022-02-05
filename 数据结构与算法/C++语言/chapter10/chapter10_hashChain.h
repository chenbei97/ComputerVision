#pragma once
#ifndef chapter10_hashChain_
#define chapter10_hashChain_
#include <iostream>
#include "chapter10_hash.h"  // mapping functions from K to nonnegative integer
#include "chapter10_dictionary.h"
#include "chapter10_dictionaryChain.h"
using namespace std;
template<class K, class V>
class hashChain : public dictionary<K, V>
{
public:
    hashChain(int theDivisor = 11)
    {
        divisor = theDivisor;
        dSize = 0;

        // allocate and initialize hash table array
        table = new dictionaryChain<K, V>[divisor];
    }

    ~hashChain() { delete[] table; }

    bool empty() const { return dSize == 0; }
    int size() const { return dSize; }

    pair<const K, V>* find(const K& theKey) const
    {
        return table[hash(theKey) % divisor].find(theKey);
    }

    void insert(const pair<const K, V>& thePair)
    {
        int homeBucket = (int)hash(thePair.first) % divisor;
        int homeSize = table[homeBucket].size();
        table[homeBucket].insert(thePair);
        if (table[homeBucket].size() > homeSize)
            dSize++;
    }

    void erase(const K& theKey)
    {
        table[hash(theKey) % divisor].erase(theKey);
    }

    void output(ostream& out) const
    {
        for (int i = 0; i < divisor; i++)
            if (table[i].size() == 0)
                cout << "NULL" << endl;
            else
                cout << table[i] << endl;
    }

    friend ostream& operator<<<>(ostream& out, const hashChain<K, V>& x);
protected:
    dictionaryChain<K, V>* table;  // hash table
    hashT<K> hash;              // maps type K to nonnegative integer
    int dSize;                 // number of elements in list
    int divisor;               // hash function divisor
};


// overload <<
template <class K, class V>
ostream& operator<<<>(ostream& out, const hashChain<K, V>& x)
{
    x.output(out); return out;
}
#endif // !chapter10_hashChain_
