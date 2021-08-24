//-------------------------------------------------------------------------
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

#ifndef PARSER_H
#define PARSER_H

#include "core/list/list.cpp"
#include "core/lexer/token.h"
#include "core/string/string.h"
#include "nodes/node.h"

#define ERROR error_ != nullptr

class Parser {
private:
	List<Token*>* tokens_;
	U_INT32 token_count_;
	int index_ = -1;
	Token* current_token_;
	String* error_;
	U_INT32 error_line_;
	U_INT32 error_column_start_;
	U_INT32 error_column_end_;

	void Advance(int amount = 1);
	Token* Peek(int amount = 1);
	void SkipNewLines();
	void SetError(const char* error);

	Node* ParseBlock(Token::Type end_token_type);
	Node* ParseExpression();
	Node* ParseCompare();
	Node* ParseBitwiseOr();
	Node* ParseBitwiseXor();
	Node* ParseBitwiseAnd();
	Node* ParseBitwiseShift();
	Node* ParseArithmetic();
	Node* ParseTerm();
	Node* ParseFactor();
	Node* ParsePower();
	Node* ParseComplement();
	Node* ParseCall();
	Node* ParseAtom();
	Node* ParseIfStatement();
	Node* ParseBody();
	Node* ParseMethod();
	MethodNode::MethodParameter* ParseMethodParameter();
	CallNode::MethodArgument* ParseMethodArgument();
	Node* ParseFor();
	Node* ParseReturn();

public:
	Parser(List<Token*>* tokens);
	bool HasError();
	void PrintError();
	Node* Parse();
};

#endif
