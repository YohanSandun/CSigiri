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

#ifndef NODE_H
#define NODE_H

#include "core/string/string.h"
#include "core/list/list.cpp"

static char* node_names[] = {
	"Empty",
	"Literal",
	"Binary",
	"Unary",
	"Block",
};

struct Node
{
	enum class Type {
		kEmpty,
		kLiteral,
		kBinary,
		kUnary,
		kBlock,
	} type;

	Node(Type type, uint32 line, uint32 column_start, uint32 column_end);
	uint32 line = 0, column_start = 0, column_end = 0;
};

struct LiteralNode : public Node
{
	union Value
	{
		int int_value;
		double float_value;
		String* string_value;
	} value;

	enum class LiteralType {
		kInteger,
		kFloat,
		kString
	} literal_type;

	LiteralNode(int value, uint32 line, uint32 column_start, uint32 column_end);
	LiteralNode(double value, uint32 line, uint32 column_start, uint32 column_end);
	LiteralNode(String* value, uint32 line, uint32 column_start, uint32 column_end);
};

struct BinaryNode : public Node
{
	enum class OperatorType {
		kAddition,
		kSubtraction,
		kMultiplication,
		kDivision,
		kModulus,
		kPower,

		kBooleanAnd,
		kBooleanOr,

		kEqualsEquals,			
		kNotEquals,				
		kLess,					
		kLessEquals,			
		kGreater,				
		kGreaterEquals,

		kBitwiseOr,
		kBitwiseAnd,
		kBitwiseXor,
		kBitwiseShiftLeft,
		kBitwiseShiftRight,

	} operator_type;

	BinaryNode(Node* left, OperatorType operator_type, Node* right, uint32 line, uint32 column_start, uint32 column_end);
	Node* left, * right;
};

struct UnaryNode : public Node
{
	enum class UnaryOperatorType {
		kPlus,
		kMinus,
		kBooleanNot,
		kBitwiseComplement,
	} operator_type;

	UnaryNode(Node* node, UnaryOperatorType operator_type, uint32 line, uint32 column_start, uint32 column_end);
	Node* node;
};

struct BlockNode : public Node
{
	List<Node*>* nodes;
	BlockNode(List<Node*>* nodes, uint32 line, uint32 column_start, uint32 column_end);
};
#endif 

