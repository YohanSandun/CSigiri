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

#include <cstdio>

#include "parser.h"

Parser::Parser(List<Token*>* tokens) {
	error_ = nullptr;
	tokens_ = tokens;
	token_count_ = tokens_->count();
	Advance();
}

void Parser::Advance(int amount) {
	index_ += amount;
	if (index_ < token_count_) {
		current_token_ = tokens_->Get(index_);
	}
}

void Parser::SkipNewLines() {
	while (current_token_->type == Token::Type::kNewline)
		Advance();
}

void Parser::SetError(const char* error) {
	error_ = new String(UTF_8 error);
	error_line_ = current_token_->line;
	error_column_start_ = current_token_->start_column;
	error_column_end_ = current_token_->end_column;
}

void Parser::PrintError() {
	printf("Parser Error:\n");
	printf("\t%s\n", error_->ptr_);
	printf("\tnear line %d from column %d to %d\n", error_line_, error_column_start_, error_column_end_);
}

bool Parser::HasError() {
	return error_ != nullptr;
}

Node* Parser::Parse() {
	return ParseBlock(Token::Type::kEof);
}

Node* Parser::ParseBlock(Token::Type end_token_type) {
	List<Node*>* statements = new List<Node*>();
	U_INT32 start_line = current_token_->line;
	while (true)
	{
		SkipNewLines();
		if (current_token_->type == end_token_type)
			break;
		Node* node = ParseExpression();
		if (ERROR) {
			delete statements;
			return nullptr;
		}
		statements->Add(node);
	}
	return new BlockNode(statements, start_line, 0, 0);
}

Node* Parser::ParseExpression() {
	U_INT32 start_column = current_token_->start_column;
	U_INT32 start_line = current_token_->line;
	Node* left = ParseCompare();
	if (ERROR)
		return nullptr;
	while (current_token_->type == Token::Type::kBooleanOr || current_token_->type == Token::Type::kBooleanAnd) {
		BinaryNode::OperatorType operaotr_type = current_token_->type == Token::Type::kBooleanOr ?
			BinaryNode::OperatorType::kBooleanOr : BinaryNode::OperatorType::kBooleanAnd;
		Advance();
		Node* right = ParseCompare();
		if (ERROR) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, operaotr_type, right, start_line, start_column, current_token_->start_column);
	}
	return left;
}

Node* Parser::ParseCompare() {
	if (current_token_->type == Token::Type::kBooleanNot) {
		Advance();
		U_INT32 start_line = current_token_->line;
		U_INT32 start_column = current_token_->start_column;
		Node* node = ParseCompare();
		if (ERROR)
			return nullptr;
		return new UnaryNode(node, UnaryNode::UnaryOperatorType::kBooleanNot, start_line, start_column, current_token_->start_column);
	}
	U_INT32 start_line = current_token_->line;
	U_INT32 start_column = current_token_->start_column;
	Node* left = ParseBitwiseOr();
	if (ERROR)
		return nullptr;
	while (current_token_->type == Token::Type::kEqualsEquals || current_token_->type == Token::Type::kNotEquals 
		|| current_token_->type == Token::Type::kLess || current_token_->type == Token::Type::kLessEquals
		|| current_token_->type == Token::Type::kGreater || current_token_->type == Token::Type::kGreaterEquals
		)
	{
		BinaryNode::OperatorType operator_type;
		if (current_token_->type == Token::Type::kEqualsEquals)
			operator_type = BinaryNode::OperatorType::kEqualsEquals;
		else if (current_token_->type == Token::Type::kNotEquals)
			operator_type = BinaryNode::OperatorType::kNotEquals;
		else if (current_token_->type == Token::Type::kLess)
			operator_type = BinaryNode::OperatorType::kLess;
		else if (current_token_->type == Token::Type::kLessEquals)
			operator_type = BinaryNode::OperatorType::kLessEquals;
		else if (current_token_->type == Token::Type::kGreater)
			operator_type = BinaryNode::OperatorType::kGreater;
		else if (current_token_->type == Token::Type::kGreaterEquals)
			operator_type = BinaryNode::OperatorType::kGreaterEquals;
		Advance();
		Node* right = ParseBitwiseOr();
		if (ERROR) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, operator_type, right, start_line, start_column, current_token_->start_column);
	}
	return left;
}


Node* Parser::ParseBitwiseOr() {
	U_INT32 start_line = current_token_->line;
	U_INT32 start_column = current_token_->start_column;
	Node* left = ParseBitwiseXor();
	if (ERROR)
		return nullptr;
	while (current_token_->type == Token::Type::kBitwiseOr) {
		Advance();
		Node* right = ParseBitwiseXor();
		if (ERROR) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, BinaryNode::OperatorType::kBitwiseOr, right, start_line, start_column, current_token_->start_column);
	}
	return left;
}

Node* Parser::ParseBitwiseXor() {
	U_INT32 start_line = current_token_->line;
	U_INT32 start_column = current_token_->start_column;
	Node* left = ParseBitwiseAnd();
	if (ERROR)
		return nullptr;
	while (current_token_->type == Token::Type::kBitwiseXor) {
		Advance();
		Node* right = ParseBitwiseAnd();
		if (ERROR) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, BinaryNode::OperatorType::kBitwiseXor, right, start_line, start_column, current_token_->start_column);
	}
	return left;
}

Node* Parser::ParseBitwiseAnd() {
	U_INT32 start_line = current_token_->line;
	U_INT32 start_column = current_token_->start_column;
	Node* left = ParseBitwiseShift();
	if (ERROR)
		return nullptr;
	while (current_token_->type == Token::Type::kBitwiseAnd) {
		Advance();
		Node* right = ParseBitwiseShift();
		if (ERROR) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, BinaryNode::OperatorType::kBitwiseAnd, right, start_line, start_column, current_token_->start_column);
	}
	return left;
}

Node* Parser::ParseBitwiseShift() {
	U_INT32 start_line = current_token_->line;
	U_INT32 start_column = current_token_->start_column;
	Node* left = ParseArithmetic();
	if (ERROR)
		return nullptr;
	while (current_token_->type == Token::Type::kBitwiseLeftShift || current_token_->type == Token::Type::kBitwiseRightShift) {
		BinaryNode::OperatorType operator_type = current_token_->type == Token::Type::kBitwiseLeftShift ?
			BinaryNode::OperatorType::kBitwiseShiftLeft : BinaryNode::OperatorType::kBitwiseShiftRight;
		Advance();
		Node* right = ParseArithmetic();
		if (ERROR) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, operator_type, right, start_line, start_column, current_token_->start_column);
	}
	return left;
}

Node* Parser::ParseArithmetic() {
	U_INT32 start_line = current_token_->line;
	U_INT32 start_column = current_token_->start_column;
	Node* left = ParseTerm();
	if (ERROR)
		return nullptr;
	while (current_token_->type == Token::Type::kPlus || current_token_->type == Token::Type::kMinus) {
		BinaryNode::OperatorType operator_type = current_token_->type == Token::Type::kPlus ?
			BinaryNode::OperatorType::kAddition : BinaryNode::OperatorType::kSubtraction;
		Advance();
		Node* right = ParseTerm();
		if (ERROR) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, operator_type, right, start_line, start_column, current_token_->start_column);
	}
	return left;
}

Node* Parser::ParseTerm() {
	U_INT32 start_line = current_token_->line;
	U_INT32 start_column = current_token_->start_column;
	Node* left = ParseFactor();
	if (ERROR)
		return nullptr;
	while (current_token_->type == Token::Type::kMultiply || current_token_->type == Token::Type::kDivision || current_token_->type == Token::Type::kModulus) {
		BinaryNode::OperatorType operator_type;
		if (current_token_->type == Token::Type::kMultiply)
			operator_type = BinaryNode::OperatorType::kMultiplication;
		else if (current_token_->type == Token::Type::kDivision)
			operator_type = BinaryNode::OperatorType::kDivision;
		else if (current_token_->type == Token::Type::kModulus)
			operator_type = BinaryNode::OperatorType::kModulus;
		Advance();
		Node* right = ParseFactor();
		if (ERROR) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, operator_type, right, start_line, start_column, current_token_->start_column);
	}
	return left;
}

Node* Parser::ParseFactor() {
	U_INT32 start_line = current_token_->line;
	U_INT32 start_column = current_token_->start_column;
	Token* token = current_token_;
	if (current_token_->type == Token::Type::kPlus || current_token_->type == Token::Type::kMinus) {
		UnaryNode::UnaryOperatorType operator_type = current_token_->type == Token::Type::kPlus ?
			UnaryNode::UnaryOperatorType::kPlus : UnaryNode::UnaryOperatorType::kMinus;
		Advance();
		Node* factor = ParseFactor();
		if (ERROR)
			return nullptr;
		return new UnaryNode(factor, operator_type, start_line, start_column, current_token_->start_column);
	}
	return ParsePower();
}

Node* Parser::ParsePower() {
	U_INT32 start_line = current_token_->line;
	U_INT32 start_column = current_token_->start_column;
	Node* left = ParseComplement();
	if (ERROR)
		return nullptr;
	while (current_token_->type == Token::Type::kPower) 
	{
		Advance();
		Node* right = ParseFactor();
		if (ERROR) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, BinaryNode::OperatorType::kPower, right, start_line, start_column, current_token_->start_column);
	}
	return left;
}

Node* Parser::ParseComplement() {
	if (current_token_->type == Token::Type::kBitwiseComplement) {
		Advance();
		U_INT32 start_line = current_token_->line;
		U_INT32 start_column = current_token_->start_column;
		Node* node = ParseFactor();
		if (ERROR)
			return nullptr;
		return new UnaryNode(node, UnaryNode::UnaryOperatorType::kBitwiseComplement, start_line, start_column, current_token_->start_column);
	}
	return ParseCall();
}

Node* Parser::ParseCall() {
	return ParseAtom();
}

Node* Parser::ParseAtom() {
	U_INT32 start_line = current_token_->line;
	U_INT32 start_column = current_token_->start_column;
	Token* token = current_token_;
	if (token->type == Token::Type::kInteger) {
		Advance();
		return new LiteralNode((int)StringToInt(token->value), start_line, start_column, current_token_->start_column);
	} 
	else if (token->type == Token::Type::kFloat) {
		Advance();
		return new LiteralNode(StringToFloat(token->value), start_line, start_column, current_token_->start_column);
	}
	else if (token->type == Token::Type::kLeftParen) {
		Advance();
		Node* expression = ParseExpression();
		if (ERROR)
			return nullptr;
		if (current_token_->type != Token::Type::kRightParen) {
			SetError("Expect ')'");
			return nullptr;
		}
		Advance();
		return expression;
	}
	SetError("Expect something!");
	return nullptr;
}