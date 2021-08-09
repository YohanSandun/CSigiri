#pragma once

#include "../declarations.h"

struct String
{
public:
	char* ptr;
	uint  size;
	uint  length;

	String(const char* ptr);
	String(uint size);
	~String();
	void Append(const char* ptr);
	void Append(char c);
	int Compare(String* other);
	int Compare(char* other);
	int IndexOf(char c);
	String* Clone();
};