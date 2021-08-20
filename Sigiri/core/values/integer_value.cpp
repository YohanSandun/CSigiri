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

#include "integer_value.h"

IntegerValue::IntegerValue(int value, uint32 line, uint32 column_start, uint32 column_end) : Value(Value::Type::kInteger, line, column_start, column_end) {
	this->value = value;
}


void IntegerValue::Print() {
	printf("%d", value);
}

Value* IntegerValue::Add(Value* other) {
	if (other->type == Value::Type::kInteger) {
		value += ((IntegerValue*)other)->value;
		delete other;
		return this;
	}
}

Value* IntegerValue::Subtract(Value* other) {
	if (other->type == Value::Type::kInteger) {
		value -= ((IntegerValue*)other)->value;
		delete other;
		return this;
	}
}

Value* IntegerValue::Multiply(Value* other) {
	if (other->type == Value::Type::kInteger) {
		value *= ((IntegerValue*)other)->value;
		delete other;
		return this;
	}
}

Value* IntegerValue::Divide(Value* other) {
	if (other->type == Value::Type::kInteger) {
		value /= ((IntegerValue*)other)->value;
		delete other;
		return this;
	}
}

Value* IntegerValue::Mod(Value* other) {
	if (other->type == Value::Type::kInteger) {
		value %= ((IntegerValue*)other)->value;
		delete other;
		return this;
	}
}
