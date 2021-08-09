#pragma once

#include "../declarations.h"

template <class T>
struct List {
public:
    List();
    List(int count);
    ~List();
    void Add(T item);
    void Add(int index, T item);
    uint count();
    T Get(uint at);
    uint size;
    T* ptr;
    bool keep_items_alive_ = false;
    void UnlinkItem(uint index);

private:
    void EnsureMemory();
    const uint kDefaultSize = 10;
    int current_index_ = -1;
};
