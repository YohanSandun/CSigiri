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
	"Assign",
	"VarAccess",
	"If",
	"Method",
	"Call",
	"For",
	"Return",
	"While",
};

struct Node
{
	enum class Type {
		kEmpty,
		kLiteral,
		kBinary,
		kUnary,
		kBlock,
		kAssign,
		kVarAccess,
		kIfStatement,
		kMethod,
		kCall,
		kFor,
		kReturn,
		kWhile,
	} type;

	U_INT32 line = 0, column_start = 0, column_end = 0;

	Node(Type type, U_INT32 line, U_INT32 column_start, U_INT32 column_end);
	virtual ~Node();
};

struct LiteralNode : public Node
{
	union Value
	{
		int int_value;
		long double float_value;
		String* string_value;
	} value;

	enum class LiteralType {
		kInteger,
		kFloat,
		kString
	} literal_type;

	LiteralNode(int value, U_INT32 line, U_INT32 column_start, U_INT32 column_end);
	LiteralNode(long double value, U_INT32 line, U_INT32 column_start, U_INT32 column_end);
	LiteralNode(String* value, U_INT32 line, U_INT32 column_start, U_INT32 column_end);
	~LiteralNode();
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

	Node* left, * right;

	BinaryNode(Node* left, OperatorType operator_type, Node* right, U_INT32 line, U_INT32 column_start, U_INT32 column_end);
	~BinaryNode();
};

struct UnaryNode : public Node
{
	enum class UnaryOperatorType {
		kPlus,
		kMinus,
		kBooleanNot,
		kBitwiseComplement,
		kFloat,
		kInt,
		kString,
	} operator_type;

	Node* node;

	UnaryNode(Node* node, UnaryOperatorType operator_type, U_INT32 line, U_INT32 column_start, U_INT32 column_end);
	~UnaryNode();
};

struct BlockNode : public Node
{
	List<Node*>* nodes;
	BlockNode(List<Node*>* nodes, U_INT32 line, U_INT32 column_start, U_INT32 column_end);
	~BlockNode();
};

struct AssignNode : public Node
{
	Node* node;
	String* key;
	AssignNode(String* key, Node* node, U_INT32 line, U_INT32 column_start, U_INT32 column_end);
	~AssignNode();
};

struct VarAccessNode : public Node {
	String* key;
	VarAccessNode(String* key, U_INT32 line, U_INT32 column_start, U_INT32 column_end);
	~VarAccessNode();
};

struct IfNode : public Node {
	struct IfCase
	{
		Node* condition, *body;
		IfCase(Node* condition, Node* body) {
			this->condition = condition;
			this->body = body;
		}
		~IfCase() {
			delete condition;
			delete body;
		}
	};
	List<IfCase*>* cases;
	Node* else_case;
	IfNode(List<IfCase*>* cases, Node* else_case, U_INT32 line, U_INT32 column_start, U_INT32 column_end);
	~IfNode();
};

struct MethodNode : public Node {
	struct MethodParameter {
		String* name;
		Node* default_value;
		MethodParameter(String* name, Node* default_value) {
			this->name = name;
			this->default_value = default_value;
		}
		~MethodParameter() {
			// name is destroyed by the token
			delete default_value;
		}
	};
	String* name;
	Node* body;
	List<MethodParameter*>* parameters;
	MethodNode(String* name, Node* body, List<MethodParameter*>* parameters, U_INT32 line, U_INT32 column_start, U_INT32 column_end);
	~MethodNode();
};

struct CallNode : public Node {
	struct MethodArgument {
		String* name;
		Node* value;
		MethodArgument(String* name, Node* value) {
			this->name = name;
			this->value = value;
		}
		~MethodArgument() {
			// name is destroyed by the token
			delete value;
		}
	};
	List<MethodArgument*>* arguments;
	Node* callee;
	CallNode(Node* callee, List<MethodArgument*>* arguments, U_INT32 line, U_INT32 column_start, U_INT32 column_end);
	~CallNode();
};

struct ForNode : public Node {
	String* identifier;
	Node* start, * to, * step, * body;
	ForNode(String* identifier, Node* start, Node* to, Node* step, Node* body, U_INT32 line, U_INT32 column_start, U_INT32 column_end);
	~ForNode();
};

struct ReturnNode : public Node {
	Node* node;
	ReturnNode(Node* node, U_INT32 line, U_INT32 column_start, U_INT32 column_end);
	~ReturnNode();
};

struct WhileNode : public Node {
	Node* condition, * body;
	WhileNode(Node* condition, Node* body, U_INT32 line, U_INT32 column_start, U_INT32 column_end);
	~WhileNode();
};

#endif 