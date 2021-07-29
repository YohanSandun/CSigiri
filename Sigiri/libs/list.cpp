#pragma once
#include "../include/list.h"

template <class T>
List<T>::List() {
	mPtr = new T[mDefaultSize];
	mSize = mDefaultSize;
}

template <class T>
List<T>::List(int count) {
	mPtr = new T[count];
	mSize = count;
}

template <class T>
List<T>::~List() {
	if (!keepItemsAlive) {
		for (int i = 0; i <= mCurrentIndex; i++)
			if (mPtr[i] != nullptr)
				delete mPtr[i];
	}
	delete[] mPtr;
}

template <class T>
void List<T>::add(T item) {
	ensureMemory();
	mPtr[mCurrentIndex] = item;
}

template <class T>
void List<T>::add(int index, T item) {
	//ensureMemory();
	mPtr[index] = item;
}

template <class T>
uint List<T>::getCount() {
	return mCurrentIndex + 1;
}

template <class T>
T List<T>::get(uint at) {
	return mPtr[at];
}

template <class T>
void List<T>::ensureMemory() {
	if (++mCurrentIndex == mSize) {
		mSize += mDefaultSize;
		T* newPtr = new T[mSize];
		for (int i = 0; i < mCurrentIndex; i++)
			newPtr[i] = mPtr[i];
		delete[] mPtr;
		mPtr = newPtr;
	}
}