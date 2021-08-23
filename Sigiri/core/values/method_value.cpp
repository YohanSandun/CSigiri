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

#include "method_value.h"

MethodValue::MethodValue(String* name, Node* body, List<MethodNode::MethodParameter*>* parameters, U_INT32 line, U_INT32 column_start, U_INT32 column_end) : Value(Value::Type::kMethod, line, column_start, column_end) {
	this->name = name;
	this->body = body;
	this->parameters = parameters;
}

MethodValue::~MethodValue() {
	// body is deleted by the parser
	if (name != nullptr)
		delete name;
	if (parameters != nullptr)
		delete parameters;
}

void MethodValue::Print() {
	if (name != nullptr)
		printf("method <%s>", name->ptr_);
	else
		printf("method <anonymous>");
}

bool MethodValue::GetAsBoolean() {
	return true;
}