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

#include "node.h"

Node::Node(Node::Type type, uint32 line, uint32 column_start, uint32 column_end) {
	this->type = type;
	this->line = line;
	this->column_start = column_start;
	this->column_end = column_end;
}

LiteralNode::LiteralNode(int value, uint32 line, uint32 column_start, uint32 column_end) : Node(Node::Type::kLiteral, line, column_start, column_end) {
	this->value.int_value = value;
	this->literal_type = LiteralType::kInteger;
}

LiteralNode::LiteralNode(double value, uint32 line, uint32 column_start, uint32 column_end) : Node(Node::Type::kLiteral, line, column_start, column_end) {
	this->value.float_value = value;
	this->literal_type = LiteralType::kFloat;
}

LiteralNode::LiteralNode(String* value, uint32 line, uint32 column_start, uint32 column_end) : Node(Node::Type::kLiteral, line, column_start, column_end) {
	this->value.string_value = value;
	this->literal_type = LiteralType::kString;
}

BinaryNode::BinaryNode(Node* left, OperatorType operator_type, Node* right, uint32 line, uint32 column_start, uint32 column_end) : Node(Node::Type::kBinary, line, column_start, column_end) {
	this->left = left;
	this->right = right;
	this->operator_type = operator_type;
}

UnaryNode::UnaryNode(Node* node, UnaryOperatorType operator_type, uint32 line, uint32 column_start, uint32 column_end) : Node(Node::Type::kUnary, line, column_start, column_end) {
	this->node = node;
	this->operator_type = operator_type;
}

BlockNode::BlockNode(List<Node*>* nodes, uint32 line, uint32 column_start, uint32 column_end) : Node(Node::Type::kBlock, line, column_start, column_end) {
	this->nodes = nodes;
}