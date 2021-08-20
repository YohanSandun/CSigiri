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

#include "value.h"

Value::Value(Type type, uint32 line, uint32 column_start, uint32 column_end) {
	this->type = type;
	this->line = line;
	this->column_start = column_start;
	this->column_end = column_end;
}

void Value::Print() {

}

Value* Value::Add(Value* other) {
	return this;
}

Value* Value::Subtract(Value* other) {
	return this;
}

Value* Value::Multiply(Value* other) {
	return this;
}

Value* Value::Divide(Value* other) {
	return this;
}

Value* Value::Mod(Value* other) {
	return this;
}