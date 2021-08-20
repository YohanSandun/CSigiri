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

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "core/parser/nodes/node.h"

#include "core/values/value.h"
#include "core/values/integer_value.h"

class Interpreter {
private:
	Value* VisitBlockNode(BlockNode* node);
	Value* VisitLiteralNode(LiteralNode* node);
	Value* VisitBinaryNode(BinaryNode* node);
	Value* VisitUnaryNode(UnaryNode* node);

public:
	Value* Visit(Node* node);
};

#endif 

