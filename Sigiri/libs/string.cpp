#include "../include/string.h"

uint strLen(const char* ptr) {
	uint i = 0;
	while (ptr[i++] != '\0');
	return i-1;
}

String::String(const char* ptr) {
	mSize = strLen(ptr)+1;
	mPtr = new char[mSize];
	for (size_t i = 0; i < mSize; i++)
		mPtr[i] = ptr[i];
}

String::String(uint size) {
	mSize = size > 0 ? size : 1;
	mPtr = new char[mSize];
	*mPtr = '\0';
}

String::~String() {
	delete[] mPtr;
}

uint String::getLength() {
	return strLen(mPtr);
}

void String::append(const char* ptr) {
	uint len = strLen(ptr);
	uint myLen = strLen(mPtr);
	if (myLen + len  < mSize)
		for (size_t i = 0; i < len + 1; i++)
			mPtr[myLen + i] = ptr[i];
	else {
		// re-alloc memory
		mSize += len + 10;
		char* newPtr = new char[mSize];
		for (size_t i = 0; i < myLen; i++)
			newPtr[i] = mPtr[i];
		for (size_t i = 0; i < len + 1; i++)
			newPtr[myLen + i] = ptr[i];
		delete[] mPtr;
		mPtr = newPtr;
	}
}

void String::append(char c) {
	uint myLen = strLen(mPtr);
	if (myLen + 1 < mSize) {
		mPtr[myLen] = c;
		mPtr[myLen+1] = '\0';
	}
	else {
		// re-alloc memory
		mSize += 10;
		char* newPtr = new char[mSize];
		for (size_t i = 0; i < myLen; i++)
			newPtr[i] = mPtr[i];
		newPtr[myLen] = c;
		newPtr[myLen+1] = '\0';
		delete[] mPtr;
		mPtr = newPtr;
	}
}