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

		STRING,

		IDENTIFIER,

		KEYWORD_VAR,
		KEYWORD_INT,
		KEYWORD_FOR,
		KEYWORD_TO,
		KEYWORD_STEP,
		KEYWORD_METHOD,
		KEYWORD_RETURN,
		KEYWORD_BREAK,
		KEYWORD_CONTINUE,

		KEYWORD_IF,
		KEYWORD_ELIF,
		KEYWORD_ELSE,

		KEYWORD_CLASS,

		PLUS,
		MINUS,
		ASTERIX,
		FW_SLASH,
		MODULUS,
		POWER,

		L_PAREN,
		R_PAREN,

		COMMA,
		DOT,

		L_BRACE,
		R_BRACE,

		L_SQ,
		R_SQ,

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