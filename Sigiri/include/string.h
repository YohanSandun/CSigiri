#pragma once

using uint = unsigned int;

uint strLen(const char* ptr);

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
};