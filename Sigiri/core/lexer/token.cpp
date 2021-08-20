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

#include "token.h"

Token::Token(Type type, uint32 line, uint32 start_column) {
	this->type = type;
	this->line = line;
	this->start_column = start_column;
	this->end_column = start_column;
}

Token::Token(Type type, uint32 line, uint32 start_column, uint32 end_column) {
	this->type = type;
	this->line = line;
	this->start_column = start_column;
	this->end_column = end_column;
}

Token::Token(String* value, Type type, uint32 line, uint32 start_column, uint32 end_column) {
	this->value = value;
	this->type = type;
	this->line = line;
	this->start_column = start_column;
	this->end_column = end_column;
}

Token::~Token() {
	if (value != nullptr)
		delete value;
}

const char* Token::name() {
	return token_names[(int)type];
}