#pragma once

#include "declarations.h"

template <class T>
struct List {
public:
    List();
    List(int count);
    ~List();
    void add(T item);
    void add(int index, T item);
    uint getCount();
    T get(uint at);
    uint mSize;
    T* mPtr;
    bool keepItemsAlive = false;
    void unlinkItem(uint index);

private:
    void ensureMemory();
    const uint mDefaultSize = 10;
    int mCurrentIndex = -1;
};
