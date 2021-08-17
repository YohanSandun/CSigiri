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

#include "lexer.h"

Lexer::Lexer(String* code) {
	code_ = code;
	Advance();
}

Lexer::~Lexer() {
	if (error_ != nullptr)
		delete error_;
}

void Lexer::Advance(int amount) {
	index_ += amount;
	if (index_ < code_->length_) {
		current_char_ = code_->ptr_[index_];
		return;
	}
	current_char_ = '\0';
}

char Lexer::Peek(int amount) {
	if (index_ + amount < code_->length_) 
		return code_->ptr_[index_ + amount];;
	return '\0';
}

List<Token*>* Lexer::GenerateTokens() {
	List<Token*>* tokens = new List<Token*>();
	while (current_char_ != '\0') 
	{
		if (current_char_ == ' ' || current_char_ == '\t')
			Advance();
		else if (current_char_ == '+') {
			tokens->Add(new Token(Token::Type::kPlus));
			Advance();
		}
		else if (current_char_ == '-') {
			tokens->Add(new Token(Token::Type::kMinus));
			Advance();
		}
		else if (current_char_ == '*') {
			tokens->Add(new Token(Token::Type::kMultiply));
			Advance();
		}
		else if (current_char_ == '/') {
			tokens->Add(new Token(Token::Type::kDivision));
			Advance();
		}
		else if (current_char_ == '%') {
			tokens->Add(new Token(Token::Type::kModulus));
			Advance();
		}
	}
	tokens->Add(new Token(Token::Type::kEof));
	return tokens;
}