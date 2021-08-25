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
	current_column_++;
	if (index_ < code_->length_) {
		current_char_ = code_->ptr_[index_];
		if (current_char_ == '\n') {
			current_line_++;
			current_column_ = 0;
		}
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
		else if (current_char_ == '\r') {
			if (Peek() == '\n') {
				tokens->Add(new Token(Token::Type::kNewline, current_line_, current_column_));
				Advance(2);
			}
			else {
				tokens->Add(new Token(Token::Type::kNewline, current_line_, current_column_));
				Advance();
			}
		}
		else if (current_char_ == '\n' || current_char_ == ';') {
			tokens->Add(new Token(Token::Type::kNewline, current_line_, current_column_));
			Advance();
		}
		else if (current_char_ == '+') {
			if (Peek() == '=') {
				tokens->Add(new Token(Token::Type::kPlusEq, current_line_, current_column_));
				Advance(2);
			}
			else {
				tokens->Add(new Token(Token::Type::kPlus, current_line_, current_column_));
				Advance();
			}
		}
		else if (current_char_ == '-') {
			if (Peek() == '=') {
				tokens->Add(new Token(Token::Type::kMinusEq, current_line_, current_column_));
				Advance(2);
			}
			else {
				tokens->Add(new Token(Token::Type::kMinus, current_line_, current_column_));
				Advance();
			}
		}
		else if (current_char_ == '*') {
			if (Peek() == '*') {
				if (Peek(2) == '=') {
					tokens->Add(new Token(Token::Type::kPowerEq, current_line_, current_column_));
					Advance(3);
				}
				else {
					tokens->Add(new Token(Token::Type::kPower, current_line_, current_column_));
					Advance(2);
				}
			}
			else if (Peek() == '=') {
				tokens->Add(new Token(Token::Type::kMultiplyEq, current_line_, current_column_));
				Advance(2);
			}
			else {
				tokens->Add(new Token(Token::Type::kMultiply, current_line_, current_column_));
				Advance();
			}
		}
		else if (current_char_ == '/') {
			if (Peek() == '=') {
				tokens->Add(new Token(Token::Type::kDivisionEq, current_line_, current_column_));
				Advance(2);
			}
			else {
				tokens->Add(new Token(Token::Type::kDivision, current_line_, current_column_));
				Advance();
			}
		}
		else if (current_char_ == '%') {
			if (Peek() == '=') {
				tokens->Add(new Token(Token::Type::kModulusEq, current_line_, current_column_));
				Advance(2);
			}
			else {
				tokens->Add(new Token(Token::Type::kModulus, current_line_, current_column_));
				Advance();
			}
		}
		else if (current_char_ == '=') {
			if (Peek() == '=') {
				tokens->Add(new Token(Token::Type::kEqualsEquals, current_line_, current_column_));
				Advance(2);
			}
			else {
				tokens->Add(new Token(Token::Type::kEquals, current_line_, current_column_));
				Advance();
			}
		}
		else if (current_char_ == '!') {
			if (Peek() == '=') {
				tokens->Add(new Token(Token::Type::kNotEquals, current_line_, current_column_));
				Advance(2);
			}
			else {
				tokens->Add(new Token(Token::Type::kBooleanNot, current_line_, current_column_));
				Advance();
			}
		}
		else if (current_char_ == '&') {
			if (Peek() == '=') {
				tokens->Add(new Token(Token::Type::kBitwiseAndEq, current_line_, current_column_));
				Advance(2);
			}
			else if (Peek() == '&') {
				tokens->Add(new Token(Token::Type::kBooleanAnd, current_line_, current_column_));
				Advance(2);
			}
			else {
				tokens->Add(new Token(Token::Type::kBitwiseAnd, current_line_, current_column_));
				Advance();
			}
		}
		else if (current_char_ == '|') {
			if (Peek() == '=') {
				tokens->Add(new Token(Token::Type::kBitwiseOrEq, current_line_, current_column_));
				Advance(2);
			}
			else if (Peek() == '|') {
				tokens->Add(new Token(Token::Type::kBooleanOr, current_line_, current_column_));
				Advance(2);
			}
			else {
				tokens->Add(new Token(Token::Type::kBitwiseOr, current_line_, current_column_));
				Advance();
			}
		}
		else if (current_char_ == '~') {

			if (Peek() == '=') {
				tokens->Add(new Token(Token::Type::kBitwiseComplementEq, current_line_, current_column_));
				Advance(2);
			}
			else {
				tokens->Add(new Token(Token::Type::kBitwiseComplement, current_line_, current_column_));
				Advance();
			}
		}
		else if (current_char_ == '^') {
			if (Peek() == '=') {
				tokens->Add(new Token(Token::Type::kBitwiseXorEquals, current_line_, current_column_));
				Advance(2);
			}
			else {
				tokens->Add(new Token(Token::Type::kBitwiseXor, current_line_, current_column_));
				Advance();
			}
		}
		else if (current_char_ == '<') {
			if (Peek() == '=') {
				tokens->Add(new Token(Token::Type::kLessEquals, current_line_, current_column_));
				Advance(2);
			}
			else if (Peek() == '<') {
				if (Peek(2) == '=') {
					tokens->Add(new Token(Token::Type::kBitwiseLeftShiftEq, current_line_, current_column_));
					Advance(3);
				}
				else {
					tokens->Add(new Token(Token::Type::kBitwiseLeftShift, current_line_, current_column_));
					Advance(2);
				}
			}
			else {
				tokens->Add(new Token(Token::Type::kLess, current_line_, current_column_));
				Advance();
			}
		}
		else if (current_char_ == '>') {
			if (Peek() == '=') {
				tokens->Add(new Token(Token::Type::kGreaterEquals, current_line_, current_column_));
				Advance(2);
			}
			else if (Peek() == '>') {
				if (Peek(2) == '=') {
					tokens->Add(new Token(Token::Type::kBitwiseRightShiftEq, current_line_, current_column_));
					Advance(3);
				}
				else {
					tokens->Add(new Token(Token::Type::kBitwiseRightShift, current_line_, current_column_));
					Advance(2);
				}
			}
			else {
				tokens->Add(new Token(Token::Type::kGreater, current_line_, current_column_));
				Advance();
			}
		}
		else if (current_char_ == ',') {
			tokens->Add(new Token(Token::Type::kComma, current_line_, current_column_));
			Advance();
		}
		else if (current_char_ == '.') {
			tokens->Add(new Token(Token::Type::kDot, current_line_, current_column_));
			Advance();
		}
		else if (current_char_ == ':') {
			tokens->Add(new Token(Token::Type::kColon, current_line_, current_column_));
			Advance();
		}
		else if (current_char_ == '(') {
			tokens->Add(new Token(Token::Type::kLeftParen, current_line_, current_column_));
			Advance();
		}
		else if (current_char_ == ')') {
			tokens->Add(new Token(Token::Type::kRightParen, current_line_, current_column_));
			Advance();
		}
		else if (current_char_ == '[') {
			tokens->Add(new Token(Token::Type::kLeftSquare, current_line_, current_column_));
			Advance();
		}
		else if (current_char_ == ']') {
			tokens->Add(new Token(Token::Type::kRightSquare, current_line_, current_column_));
			Advance();
		}
		else if (current_char_ == '{') {
			tokens->Add(new Token(Token::Type::kLeftBrace, current_line_, current_column_));
			Advance();
		}
		else if (current_char_ == '}') {
			tokens->Add(new Token(Token::Type::kRightBrace, current_line_, current_column_));
			Advance();
		}
		else if (current_char_ >= '0' && current_char_ <= '9')
			tokens->Add(CreateNumber());
		else if ((current_char_ >= 'A' && current_char_ <= 'Z') || (current_char_ >= 'a' && current_char_ <= 'z') || current_char_ == '_') 
			tokens->Add(CreateIdentifier());
	}
	tokens->Add(new Token(Token::Type::kEof, current_line_, current_column_));
	return tokens;
}

Token* Lexer::CreateNumber() {
	int dot_count = 0;
	String* number = new String(5);
	U_INT32 start_column = current_column_;
	while (current_char_ != '\0' && ((current_char_ >= '0' && current_char_ <= '9') || current_char_ == '.')) {
		if (current_char_ == '.')
			dot_count++;
		number->Append(current_char_);
		Advance();
	}
	if (dot_count != 0)
		return new Token(number, Token::Type::kFloat, current_line_, start_column, current_column_);
	return new Token(number, Token::Type::kInteger, current_line_, start_column, current_column_);
	//TODO : Throw an error when dot_count > 1
}

Token* Lexer::CreateIdentifier() {
	U_INT32 start_column = current_column_;
	String* id = new String(5);
	while (current_char_ != '\0' && ((current_char_ >= 'A' && current_char_ <= 'Z') || (current_char_ >= 'a' && current_char_ <= 'z')
		|| ((current_char_ >= '0' && current_char_ <= '9') || current_char_ == '_'))) {
		id->Append(current_char_);
		Advance();
	}
	if (id->Compare(UTF_8 "float")) {
		delete id;
		return new Token(Token::Type::kKwFloat, current_line_, start_column, current_column_);
	}
	else if (id->Compare(UTF_8 "if")) {
		delete id;
		return new Token(Token::Type::kKwIf, current_line_, start_column, current_column_);
	}
	else if (id->Compare(UTF_8 "elif")) {
		delete id;
		return new Token(Token::Type::kKwElif, current_line_, start_column, current_column_);
	}
	else if (id->Compare(UTF_8 "else")) {
		delete id;
		return new Token(Token::Type::kKwElse, current_line_, start_column, current_column_);
	}
	else if (id->Compare(UTF_8 "for")) {
		delete id;
		return new Token(Token::Type::kKwFor, current_line_, start_column, current_column_);
	}
	else if (id->Compare(UTF_8 "to")) {
		delete id;
		return new Token(Token::Type::kKwTo, current_line_, start_column, current_column_);
	}
	else if (id->Compare(UTF_8 "step")) {
		delete id;
		return new Token(Token::Type::kKwStep, current_line_, start_column, current_column_);
	}
	else if (id->Compare(UTF_8 "method")) {
		delete id;
		return new Token(Token::Type::kKwMethod, current_line_, start_column, current_column_);
	}
	else if (id->Compare(UTF_8 "return")) {
		delete id;
		return new Token(Token::Type::kKwReturn, current_line_, start_column, current_column_);
	}
	else if (id->Compare(UTF_8 "while")) {
		delete id;
		return new Token(Token::Type::kKwWhile, current_line_, start_column, current_column_);
	}
	return new Token(id, Token::Type::kIdentifier, current_line_, start_column, current_column_);
}