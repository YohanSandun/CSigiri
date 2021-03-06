#pragma once

#include "declarations.h"
#include "string.h"

struct Token {
public:
	String* mValue = nullptr;
	enum class Type {
		NEWLINE,

		INT_NUMBER,
		FLOAT_NUMBER,

		IDENTIFIER,
		KEYWORD_INT,

		PLUS,
		MINUS,
		ASTERIX,
		FW_SLASH,
		POWER,

		L_PAREN,
		R_PAREN,

		COMMA,

		L_BRACE,
		R_BRACE,

		COLON,
		SEMI_COLON,

		EQUALS,
		EQUALS_EQUALS,
		NOT_EQUALS,
		GREATER_THAN,
		LESS_THAN,
		GREATER_EQ,
		LESS_EQ,

		BOOLEAN_NOT,
		BOOLEAN_AND,
		BOOLEAN_OR,

		BITWISE_OR,
		BITWISE_AND,
		BITWISE_XOR,
		BITWISE_COMPLEMENT,

		LEFT_SHIFT,
		RIGHT_SHIFT,

		EOF_TOKEN
	} mType;

	uint mLine;
	uint mColStart, mColEnd;

	Token(Type type);
	Token(String* value, Type type);
	~Token();
};