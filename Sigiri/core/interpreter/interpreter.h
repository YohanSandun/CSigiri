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
#include "core/values/method_value.h"

#include "context.h"

class Interpreter {
private:
	U_INT32 error_line, error_column_start, error_column_end;
	String* error_ = nullptr;

	void SetError(const char* error, U_INT32 line, U_INT32 column_start, U_INT32 column_end);

	Value* VisitBlockNode(BlockNode* node, Context* context);
	Value* VisitLiteralNode(LiteralNode* node, Context* context);
	Value* VisitBinaryNode(BinaryNode* node, Context* context);
	Value* VisitUnaryNode(UnaryNode* node, Context* context);
	Value* VisitAssignNode(AssignNode* node, Context* context);
	Value* VisitVarAccessNode(VarAccessNode* node, Context* context);
	Value* VisitIfNode(IfNode* node, Context* context);
	Value* VisitMethodNode(MethodNode* node, Context* context);
	Value* VisitCallNode(CallNode*node, Context* context);

public:
	void PrintError();
	void ClearError();
	Value* Visit(Node* node, Context* context);
	inline bool HasError() { return error_ != nullptr; }
};

#endif 

