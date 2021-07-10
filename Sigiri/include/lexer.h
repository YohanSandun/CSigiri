#pragma once

#include "token.h"
#include "string.h"
#include "../libs/list.cpp" // to satisfy the compiler

struct Lexer
{
private:
	char mCurrentChar;
	int mIndex = -1;
	int mColumn = 0;
	int mLine = 1;
	uint mCodeLen;
	String* mCode;
	void advance();
	char peek(int amount = 1);
	Token* makeNumber();
	Token* makeIdentifier();

public:
	Lexer(String* code);
	~Lexer();
	List<Token*>* generateTokens();
};