//--------------------------------------------------------------------------
// Copyright 2021 Yohan Sandun
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//--------------------------------------------------------------------------

#ifndef TOKEN_H
#define TOKEN_H

#include "core/string/string.h"

static const char* token_names[] = {
		"Empty",

		"Integer",
		"Float",
		"String",
		"Identifier",

		"+",
		"-",
		"*",
		"/",
		"%",
		"**",

		"==",
		"!=",
		"<",
		"<=",
		">",
		">=",

		"&&",
		"||",
		"!",

		"&",
		"|",
		"~",
		"^",
		"<<",
		">>",

		"=",
		"+=",
		"-=",
		"*=",
		"/=",
		"%=",
		"**=",
		"&=",
		"|=",
		"~=",
		"<<=",
		">>=",

		"(",
		")",
		"[",
		"]",
		"{",
		"}",
		",",
		".",
		":",
		"Newline",

		"var",
		"if",
		"else",
		"elif",
		"for",
		"to",
		"step",

		"EOF",
};

struct Token {

	enum class Type {
		kEmpty,

		kInteger,
		kFloat,
		kString,
		kIdentifier,

		kPlus,					// +
		kMinus,					// -
		kMultiply,				// *
		kDivision,				// /
		kModulus,				// %
		kPower,					// **

		kEqualsEquals,			// ==
		kNotEquals,				// !=
		kLess,					// <
		kLessEquals,			// <=
		kGreater,				// >
		kGreaterEquals,			// >=

		kBooleanAnd,			// &&
		kBooleanOr,				// ||
		kBooleanNot,			// !

		kBitwiseAnd,			// &
		kBitwiseOr,				// |
		kBitwiseComplement,		// ~
		kBitwiseXor,			// ^
		kBitwiseLeftShift,		// <<
		kBitwiseRightShift,		// >>

		kEquals,				// =
		kPlusEq,				// +=
		kMinusEq,				// -=
		kMultiplyEq,			// *=
		kDivisionEq,			// /=
		kModulusEq,				// %=
		kPowerEq,				// **=
		kBitwiseAndEq,			// &=
		kBitwiseOrEq,			// |=
		kBitwiseComplementEq,	// ~=
		kBitwiseLeftShiftEq,	// <<=
		kBitwiseRightShiftEq,	// >>=	

		kLeftParen,				// (
		kRightParen,			// )
		kLeftSquare,			// [
		kRightSquare,			// ]
		kLeftBrace,				// {
		kRightBrace,			// }
		kComma,					// ,
		kDot,					// .
		kColon,					// :
		kNewline,				// \n and ;(Semi-colon)

		kKwVar,					// var
		kKwIf,					// if
		kKwElse,				// else
		kKwElif,				// elif
		kKwFor,					// for
		kKwTo,					// to
		kKwStep,				// step

		kEof,
	} type;

	String* value = nullptr;
	uint32 line = 0, start_column = 0, end_column = 0;
	Token(Type type);
	Token(String* value, Type type);
	~Token();
	const char* GetName();
};

#endif 
