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

#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include "core/declarations.h"
#include "core/parser/nodes/node.h"

class CodeGenerator
{
public:
	uint32 current_data_index_ = 0;
	uint32 current_opcode_index_ = 0;

	sbyte data_[4096];
	sbyte opcoeds_[1024];

	void VisitBlockNode(BlockNode* node);
	void VisitLiteralNode(LiteralNode* node);
	void VisitBinaryNode(BinaryNode* node);
	void VisitUnaryNode(UnaryNode* node);
	void Visit(Node* node);
};


#endif
