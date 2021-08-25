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

#include "float_value.h"
#include "integer_value.h"

Value* FloatValue::CastFrom(Value* value) {
	if (value->type == Value::Type::kFloat) 
		return value;
	else if (value->type == Value::Type::kInteger) {
		long double double_value = (static_cast<IntegerValue*>(value))->value;
		delete value;
		return new FloatValue(double_value, value->line, value->column_start, value->column_end);
	}
	return nullptr;
}

FloatValue::FloatValue(long double value, U_INT32 line, U_INT32 column_start, U_INT32 column_end) : Value(Value::Type::kFloat, line, column_start, column_end) {
	this->value = value;
}

FloatValue::~FloatValue() {

}

void FloatValue::Print() {
	printf("%f", value);
}

Value* FloatValue::Clone() {
	return new FloatValue(value, line, column_start, column_end);
}

bool FloatValue::GetAsBoolean() {
	return value != 0;
}