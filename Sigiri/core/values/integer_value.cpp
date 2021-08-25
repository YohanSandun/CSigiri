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
#include "float_value.h"

IntegerValue::IntegerValue(int value, U_INT32 line, U_INT32 column_start, U_INT32 column_end, bool is_boolean) : Value(Value::Type::kInteger, line, column_start, column_end) {
	this->value = value;
	this->is_boolean = is_boolean;
}

IntegerValue::~IntegerValue() {

}

Value* IntegerValue::CastFrom(Value* value) {
	if (value->type == Value::Type::kInteger)
		return value;
	else if (value->type == Value::Type::kFloat) {
		int integer_value = (static_cast<FloatValue*>(value))->value;
		U_INT32 line = value->line;
		U_INT32 column_start = value->line;
		U_INT32 column_end = value->line;
		delete value;
		return new IntegerValue(integer_value, line, column_start, column_end);
	}
	return nullptr;
}

void IntegerValue::Print() {
	if (is_boolean)
		printf("%s", value == 0 ? "false" : "true");
	else
		printf("%d", value);
}

Value* IntegerValue::Clone() {
	return new IntegerValue(value, line, column_start, column_end, is_boolean);
}

bool IntegerValue::GetAsBoolean() {
	return value != 0;
}

Value* IntegerValue::Add(Value* other) {
	if (other->type == Value::Type::kInteger) {
		value += (static_cast<IntegerValue*>(other))->value;
		delete other;
		return this;
	}
}

Value* IntegerValue::Subtract(Value* other) {
	if (other->type == Value::Type::kInteger) {
		value -= (static_cast<IntegerValue*>(other))->value;
		delete other;
		return this;
	}
}

Value* IntegerValue::Multiply(Value* other) {
	if (other->type == Value::Type::kInteger) {
		value *= (static_cast<IntegerValue*>(other))->value;
		delete other;
		return this;
	}
}

Value* IntegerValue::Divide(Value* other) {
	if (other->type == Value::Type::kInteger) {
		value /= (static_cast<IntegerValue*>(other))->value;
		delete other;
		return this;
	}
}

Value* IntegerValue::Mod(Value* other) {
	if (other->type == Value::Type::kInteger) {
		value %= (static_cast<IntegerValue*>(other))->value;
		delete other;
		return this;
	}
}

Value* IntegerValue::Power(Value* other) {
	if (other->type == Value::Type::kInteger) {
		//TODO: implement power
		delete other;
		return this;
	}
}

Value* IntegerValue::Equals(Value* other) {
	if (other->type == Value::Type::kInteger) {
		value = value == (static_cast<IntegerValue*>(other))->value;
		is_boolean = true;
		delete other;
		return this;
	}
}

Value* IntegerValue::NotEquals(Value* other) {
	if (other->type == Value::Type::kInteger) {
		value = value != (static_cast<IntegerValue*>(other))->value;
		is_boolean = true;
		delete other;
		return this;
	}
}

Value* IntegerValue::LessThan(Value* other) {
	if (other->type == Value::Type::kInteger) {
		value = value < (static_cast<IntegerValue*>(other))->value;
		is_boolean = true;
		delete other;
		return this;
	}
}

Value* IntegerValue::LessThanOrEqual(Value* other) {
	if (other->type == Value::Type::kInteger) {
		value = value <= (static_cast<IntegerValue*>(other))->value;
		is_boolean = true;
		delete other;
		return this;
	}
}

Value* IntegerValue::GreaterThan(Value* other) {
	if (other->type == Value::Type::kInteger) {
		value = value > (static_cast<IntegerValue*>(other))->value;
		is_boolean = true;
		delete other;
		return this;
	}
}

Value* IntegerValue::GreaterThanOrEqual(Value* other) {
	if (other->type == Value::Type::kInteger) {
		value = value >= (static_cast<IntegerValue*>(other))->value;
		is_boolean = true;
		delete other;
		return this;
	}
}

Value* IntegerValue::BitwiseAnd(Value* other) {
	if (other->type == Value::Type::kInteger) {
		value &= (static_cast<IntegerValue*>(other))->value;
		delete other;
		return this;
	}
}

Value* IntegerValue::BitwiseOr(Value* other) {
	if (other->type == Value::Type::kInteger) {
		value |= (static_cast<IntegerValue*>(other))->value;
		delete other;
		return this;
	}
}

Value* IntegerValue::BitwiseComplement() {
	value = ~value;
	return this;
}

Value* IntegerValue::BitwiseXor(Value* other) {
	if (other->type == Value::Type::kInteger) {
		value ^= (static_cast<IntegerValue*>(other))->value;
		delete other;
		return this;
	}
}

Value* IntegerValue::BitwiseLeftShift(Value* other) {
	if (other->type == Value::Type::kInteger) {
		value <<= (static_cast<IntegerValue*>(other))->value;
		delete other;
		return this;
	}
}

Value* IntegerValue::BitwiseRightShift(Value* other) {
	if (other->type == Value::Type::kInteger) {
		value >>= (static_cast<IntegerValue*>(other))->value;
		delete other;
		return this;
	}
}

Value* IntegerValue::BooleanAnd(Value* other) {
	if (other->type == Value::Type::kInteger) {
		value = value && (static_cast<IntegerValue*>(other))->value;
		is_boolean = true;
		delete other;
		return this;
	}
}

Value* IntegerValue::BooleanOr(Value* other) {
	if (other->type == Value::Type::kInteger) {
		value = value || (static_cast<IntegerValue*>(other))->value;
		is_boolean = true;
		delete other;
		return this;
	}
}

Value* IntegerValue::BooleanNot() {
	value = !value;
	is_boolean = true;
	return this;
}
