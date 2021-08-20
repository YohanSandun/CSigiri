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

#include "interpreter.h"

Value* Interpreter::Visit(Node* node) {
	if (node->type == Node::Type::kBlock)
		return VisitBlockNode((BlockNode*)node);
	else if (node->type == Node::Type::kLiteral)
		return VisitLiteralNode((LiteralNode*)node);
	else if (node->type == Node::Type::kBinary)
		return VisitBinaryNode((BinaryNode*)node);
	else if (node->type == Node::Type::kUnary)
		return VisitUnaryNode((UnaryNode*)node);
}

Value* Interpreter::VisitBlockNode(BlockNode* node) {
	uint32 statement_count = node->nodes->count();
	for (size_t i = 0; i < statement_count; i++)
	{
		if (i+1 == statement_count)
			return Visit(node->nodes->Get(i));
		Visit(node->nodes->Get(i));
	}
}

Value* Interpreter::VisitLiteralNode(LiteralNode* node) {
	if (node->literal_type == LiteralNode::LiteralType::kInteger)
		return new IntegerValue(node->value.int_value, node->line, node->column_start, node->column_end);
}

Value* Interpreter::VisitBinaryNode(BinaryNode* node) {
	Value* left = Visit(node->left);
	Value* right = Visit(node->right);

	switch (node->operator_type)
	{
	case BinaryNode::OperatorType::kAddition:
		return left->Add(right);
	case BinaryNode::OperatorType::kSubtraction:
		return left->Subtract(right);
	case BinaryNode::OperatorType::kMultiplication:
		return left->Multiply(right);
	case BinaryNode::OperatorType::kDivision:
		return left->Divide(right);
	case BinaryNode::OperatorType::kModulus:
		return left->Mod(right);
	default:
		break;
	}
}

Value* Interpreter::VisitUnaryNode(UnaryNode* node) {
	Value* value = Visit(node->node);
	if (node->operator_type == UnaryNode::UnaryOperatorType::kMinus)
		return value->Multiply(new IntegerValue(-1, 0, 0, 0));
}