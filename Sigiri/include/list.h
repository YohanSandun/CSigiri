#pragma once

#include "declarations.h"

template <class T>
struct List {
public:
    List();
    ~List();
    void add(T item);
    uint getCount();
    T get(uint at);
    uint mSize;
    T* mPtr;

private:
    void ensureMemory();
    const uint mDefaultSize = 2;
    int mCurrentIndex = -1;
};
