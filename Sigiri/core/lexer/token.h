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

static const char* token_names_[] = {
		"Empty",

		"Integer",
		"Float",

		"Plus",
		"Minus",
		"Asterix",
		"FowardShlash",

		"EOF",
};

struct Token {

	enum class Type {
		kEmpty,

		kInteger,
		kFloat,

		kPlus,			// +
		kMinus,			// -
		kAsterix,		// *
		kFowardShlash,	// /

		kEof,
	} type_;

	String* value_ = nullptr;
	uint32 line_ = 0, start_column_ = 0, end_column = 0;
	Token(Type type);
	Token(String* value, Type type);
	~Token();
};

#endif 
