#pragma once

#include "declarations.h"
#include "string.h"

struct Token {
public:
	String* mValue = nullptr;
	enum class Type {
		INT_NUMBER,
		FLOAT_NUMBER,
		IDENTIFIER,
		KEYWORD_INT,
		PLUS,
		MINUS,
		ASTERIX,
		FW_SLASH,
		L_PAREN,
		R_PAREN,
		COMMA,
		L_BRACE,
		R_BRACE
	} mType;

	uint mLine;
	uint mColStart, mColEnd;

	Token(Type type);
	Token(String* value, Type type);
	~Token();
};