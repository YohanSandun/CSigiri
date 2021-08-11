#include "sigiri_string.h"
#include "string_helper.h"

int String::IndexOf(char c) {
	for (size_t i = 0; i < length; i++)
	{
		if (ptr[i] == c)
			return i;
	}
	return -1;
}

void String::CalculateHash() {
	hash_code_ = 0;
	for (size_t i = 0; i < length; i++)
		hash_code_ = 31 * hash_code_ + ptr[i];
}

String::String(const char* ptr) {
	size = StringLength(ptr) + 1;
	length = size - 1;
	this->ptr = new char[size];
	for (size_t i = 0; i < size; i++)
		this->ptr[i] = ptr[i];
	CalculateHash();
}

String::String(uint size) {
	size = size > 0 ? size : 1;
	length = 0;
	ptr = new char[size];
	*ptr = '\0';
}

String::~String() {
	if (ptr == nullptr)
		return;
	delete[] ptr;
}

int String::Compare(String* other) {
	return StringCompare(this, other);
}

int String::Compare(char* other) {
	return StringCompare(ptr, other);
}

void String::Append(const char* ptr) {
	uint len = length;
	uint myLen = StringLength(this->ptr);
	length += len;
	if (myLen + len < size) {
		for (size_t i = 0; i < len + 1; i++)
			this->ptr[myLen + i] = ptr[i];
	}
	else {
		// re-alloc memory
		size += len + 10; //todo increment amt
		char* newPtr = new char[size];
		for (size_t i = 0; i < myLen; i++)
			newPtr[i] = this->ptr[i];
		for (size_t i = 0; i < len + 1; i++)
			newPtr[myLen + i] = ptr[i];
		delete[] this->ptr;
		this->ptr = newPtr;
	}
	CalculateHash();
}

void String::Append(char c) {
	uint myLen = length;
	if (c != '\0')
		length++;
	if (myLen + 1 < size) {
		ptr[myLen] = c;
		ptr[myLen + 1] = '\0';
	}
	else {
		// re-alloc memory
		size += 10;
		char* newPtr = new char[size];
		for (size_t i = 0; i < myLen; i++)
			newPtr[i] = ptr[i];
		newPtr[myLen] = c;
		newPtr[myLen + 1] = '\0';
		delete[] ptr;
		ptr = newPtr;
	}
	CalculateHash();
}

String* String::Clone() {
	return new String(ptr);
}