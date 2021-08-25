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

Value::Value(Type type, U_INT32 line, U_INT32 column_start, U_INT32 column_end) {
	this->type = type;
	this->line = line;
	this->column_start = column_start;
	this->column_end = column_end;
}

Value* Value::IncrementRefCount(int amount) {
	ref_count += amount;
	return this;
}

void Value::Print() {

}

Value::~Value() {

}

Value* Value::Clone() {
	return this;
}

bool Value::GetAsBoolean() {
	return false;
}

// Arithmetic
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

Value* Value::Power(Value* other) {
	return this;
}


// Comparison
Value* Value::Equals(Value* other) {
	return this;
}

Value* Value::NotEquals(Value* other) {
	return this;
}

Value* Value::LessThan(Value* other) {
	return this;
}

Value* Value::LessThanOrEqual(Value* other) {
	return this;
}

Value* Value::GreaterThan(Value* other) {
	return this;
}

Value* Value::GreaterThanOrEqual(Value* other) {
	return this;
}


// Bitwise
Value* Value::BitwiseAnd(Value* other) {
	return this;
}

Value* Value::BitwiseOr(Value* other) {
	return this;
}

Value* Value::BitwiseComplement() {
	return this;
}

Value* Value::BitwiseXor(Value* other) {
	return this;
}

Value* Value::BitwiseLeftShift(Value* other) {
	return this;
}

Value* Value::BitwiseRightShift(Value* other) {
	return this;
}


// Boolean
Value* Value::BooleanAnd(Value* other) {
	return this;
}

Value* Value::BooleanOr(Value* other) {
	return this;
}

Value* Value::BooleanNot() {
	return this;
}
