#include "string.h"

uint strLen(const char* ptr) {
	uint i = 0;
	while (ptr[i++] != '\0');
	return i-1;
}

bool strCmp(const char* s1, const char* s2) {
	if (strLen(s1) != strLen(s2))
		return false;
	int i = 0;
	while (s1[i] != '\0' && s2[i] != '\0') {
		if (s1[i] != s2[i])
			return false;
		i++;
	}
	return true;
}

String* intToStr(int i) {
	if (i == 0)
		return new String('0');
	String* str = new String(5);
	if (i < 0)
	{
		i *= -1;
		str->append('-');
	}
	while (i > 0) {
		int digit = i % 10;
		str->append(digit + '0');
		i /= 10;
	}
	return str;
}

int strToInt(String* str) {
	int value = 0;
	uint len = str->getLength();
	int i = 0;
	while (i < len) {
		int digit = str->mPtr[i++] - '0';
		value *= 10;
		value += digit;
	}
	return value;
}

double strToFloat(String* str) {
	double value = 0;
	uint len = str->getLength();
	int dotIndex = str->indexOf('.');
	dotIndex = dotIndex >= 0 ? dotIndex : len;

	for (size_t i = 0; i < dotIndex; i++)
	{
		int digit = str->mPtr[i] - '0';
		for (size_t j = 0; j < dotIndex - i - 1; j++)
			digit *= 10;
		value += digit;
	}

	double decimal = 0;
	for (size_t i = dotIndex+1; i < len; i++)
	{
		int digit = str->mPtr[i] - '0';
		uint divide = 1;
		for (size_t j = 0; j < i-dotIndex; j++)
			divide *= 10;
		decimal += (digit/(double)divide);
	}
	return value+decimal;
}

int String::indexOf(char c) {
	uint len = strLen(mPtr);
	for (size_t i = 0; i < len; i++)
	{
		if (mPtr[i] == c)
			return i;
	}
	return -1;
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

//#include <cstdio>

String::~String() {
	if (mPtr == nullptr)
		return;
	//printf("deleted %s\n", mPtr);
	delete[] mPtr;
}

uint String::getLength() {
	return strLen(mPtr);
}

int String::compare(String* other) {
	return strCmp(mPtr, other->mPtr);
}

int String::compare(char* other) {
	return strCmp(mPtr, other);
}

void String::append(const char* ptr) {
	uint len = strLen(ptr);
	uint myLen = strLen(mPtr);
	if (myLen + len  < mSize)
		for (size_t i = 0; i < len + 1; i++)
			mPtr[myLen + i] = ptr[i];
	else {
		// re-alloc memory
		mSize += len + 10; //todo increment amt
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

String* String::clone() {
	return new String(mPtr);
}