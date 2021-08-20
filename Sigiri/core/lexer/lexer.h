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

#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include "core/declarations.h"
#include "core/string/string.h"
#include "core/list/list.cpp"

class Lexer {
private:
	String* code_;
	int index_ = -1;
	uint32 current_line_ = 1, current_column_ = 0;
	char current_char_ = '\0';

	void Advance(int amount = 1);
	char Peek(int amount = 1);

	Token* CreateNumber();
	Token* CreateIdentifier();

public :
	Lexer(String* code);
	~Lexer();
	List<Token*>* GenerateTokens();
	String* error_ = nullptr;
};

#endif // !LEXER_H
