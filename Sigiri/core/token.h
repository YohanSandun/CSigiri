#pragma once

#include "declarations.h"
#include "string/string.h"

struct Token {
public:
	String* value = nullptr;
	enum class Type {
		kIntNumber,
		kFloatNumber,
		kString,
		kIdentifier,

		kKeywordVar,
		kKeywordInt,
		kKeywordFor,
		kKeywordTo,
		kKeywordStep,
		kKeywordMethod,
		kKeywordReturn,
		kKeywordBreak,
		kKeywordContinue,
		kKeywordIf,
		kKeywordElif,
		kKeywordElse,
		kKeywordClass,

		kPlus,
		kMinus,
		kAsterix,
		kFowardSlash,
		kPrecentage,
		kPower,

		kLeftParen,
		kRightParen,
		kLeftBrace,
		kRightBrace,
		kLeftSqare,
		kRightSquare,

		kComma,
		kDot,
		kColon,
		kSemiColon, 
		kNewLine,

		kEquals,
		kEqualsEquals,
		kNotEquals,
		kGreaterThan,
		kLessThan,
		kGreaterEquals,
		kLessEquals,

		kBooleanNot,
		kBooleanAnd,
		kBooleanOr,

		kBitwiseOr,
		kBitwiseAnd,
		kBitwiseXor,
		kBitwiseComplement,
		kLeftShift,
		kRightShift,

		kEof
	} type;

	uint line;
	uint col_start, col_end;

	Token(Type type);
	Token(String* value, Type type);
	~Token();
};