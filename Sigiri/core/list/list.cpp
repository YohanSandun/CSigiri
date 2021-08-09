#pragma once
#include "list.h"

template <class T>
List<T>::List() {
	ptr = new T[kDefaultSize];
	size = kDefaultSize;
}

template <class T>
List<T>::List(int count) {
	ptr = new T[count];
	size = count;
}

template <class T>
List<T>::~List() {
	if (!keep_items_alive_) {
		for (int i = 0; i <= current_index_; i++)
			if (ptr[i] != nullptr)
				delete ptr[i];
	}
	delete[] ptr;
}

template <class T>
void List<T>::Add(T item) {
	EnsureMemory();
	ptr[current_index_] = item;
}

template <class T>
void List<T>::Add(int index, T item) {
	//EnsureMemory();
	ptr[index] = item;
}

template <class T>
uint List<T>::count() {
	return current_index_ + 1;
}

template <class T>
void List<T>::UnlinkItem(uint index) {
	ptr[index] = nullptr;
}

template <class T>
T List<T>::Get(uint at) {
	return ptr[at];
}

template <class T>
void List<T>::EnsureMemory() {
	if (++current_index_ == size) {
		size += kDefaultSize;
		T* newPtr = new T[size];
		for (int i = 0; i < current_index_; i++)
			newPtr[i] = ptr[i];
		delete[] ptr;
		ptr = newPtr;
	}
}