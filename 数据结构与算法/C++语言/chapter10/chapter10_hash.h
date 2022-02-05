#pragma once
#ifndef chapter10_hash_
#define chapter10_hash_
#include <iostream>
#include <string>
using namespace std;

template <class K>
class hashT; // hashª·÷ÿ√˚

template<>
class hashT<string>
{
public:
    size_t operator()(const string theKey) const
    {// Convert theKey to a nonnegative integer.
        unsigned long hashValue = 0;
        int length = (int)theKey.length();
        for (int i = 0; i < length; i++)
            hashValue = 5 * hashValue + theKey.at(i);
        return size_t(hashValue);
    }
};

template<>
class hashT<int>
{
public:
    size_t operator()(const int theKey) const
    {
        return size_t(theKey);
    }
};

template<>
class hashT<long>
{
public:
    size_t operator()(const long theKey) const
    {
        return size_t(theKey);
    }
};
#endif // !chapter10_hash_
