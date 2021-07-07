#pragma once

#include "declarations.h"

uint strLen(const char* ptr);
int strCmp(const char* s1, const char* s2);

struct String
{
public:
	char* mPtr;
	uint mSize;
	String(const char* ptr);
	String(uint size);
	~String();
	uint getLength();
	void append(const char* ptr);
	void append(char c);
	int compare(String* other);
	int compare(char* other);
	int indexOf(char c);
};

int strToInt(String* str);
double strToFloat(String* str);