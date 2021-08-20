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

// Experimental code

#include "code_generator.h"

void CodeGenerator::Visit(Node* node) {
	if (node->type == Node::Type::kBlock)
		VisitBlockNode((BlockNode*)node);
	else if (node->type == Node::Type::kLiteral)
		VisitLiteralNode((LiteralNode*)node);
	else if (node->type == Node::Type::kBinary)
		VisitBinaryNode((BinaryNode*)node);
	else if (node->type == Node::Type::kUnary)
		VisitUnaryNode((UnaryNode*)node);
}

void CodeGenerator::VisitBlockNode(BlockNode* node) {
	uint32 statement_count = node->nodes->count();
	for (size_t i = 0; i < statement_count; i++)
	{
		Visit(node->nodes->Get(i));
	}
}

void CodeGenerator::VisitLiteralNode(LiteralNode* node) {
	if (node->literal_type == LiteralNode::LiteralType::kInteger) {

	}
}

void CodeGenerator::VisitBinaryNode(BinaryNode* node) {

}

void CodeGenerator::VisitUnaryNode(UnaryNode* node) {

}