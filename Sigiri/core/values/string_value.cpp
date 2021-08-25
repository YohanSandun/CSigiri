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

#include "string_value.h"
#include "integer_value.h"
#include "float_value.h"
#include "core/string/string.h"

StringValue::StringValue(String* value, U_INT32 line, U_INT32 column_start, U_INT32 column_end) : Value(Value::Type::kString, line, column_start, column_end) {
	this->value = value;
}

StringValue::~StringValue() {
	delete value;
}

Value* StringValue::CastFrom(Value* value) {
	if (value->type == Value::Type::kString)
		return value;
	else if (value->type == Value::Type::kInteger) {
		String* string_value = IntToString((static_cast<IntegerValue*>(value))->value);
		U_INT32 line = value->line;
		U_INT32 column_start = value->line;
		U_INT32 column_end = value->line;
		delete value;
		return new StringValue(string_value, line, column_start, column_end);
	}
	else if (value->type == Value::Type::kFloat) {
		String* string_value = FloatToString((static_cast<FloatValue*>(value))->value);
		U_INT32 line = value->line;
		U_INT32 column_start = value->line;
		U_INT32 column_end = value->line;
		delete value;
		return new StringValue(string_value, line, column_start, column_end);
	}
	return nullptr;
}

void StringValue::Print() {
	printf("'%s'", value->ptr_);
}

bool StringValue::GetAsBoolean() {
	return value->length_ != 0;
}