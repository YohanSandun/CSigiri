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

#ifndef VALUE_H
#define VALUE_H

#include <cstdio>

#include "core/declarations.h"

struct Value
{
	enum class Type {
		kInteger,
		kFloat,
		kString,
		kMethod,
	} type;

	U_INT32 line, column_start, column_end;
	Value(Type type, U_INT32 line, U_INT32 column_start, U_INT32 column_end);
	virtual ~Value();
	virtual void Print();
	virtual Value* Clone();
	virtual bool GetAsBoolean();

	virtual Value* Add(Value* other);
	virtual Value* Subtract(Value* other);
	virtual Value* Multiply(Value* other);
	virtual Value* Divide(Value* other);
	virtual Value* Mod(Value* other);
	virtual Value* Power(Value* other);

	virtual Value* Equals(Value* other);
	virtual Value* NotEquals(Value* other);
	virtual Value* LessThan(Value* other);
	virtual Value* LessThanOrEqual(Value* other);
	virtual Value* GreaterThan(Value* other);
	virtual Value* GreaterThanOrEqual(Value* other);

	virtual Value* BitwiseAnd(Value* other);
	virtual Value* BitwiseOr(Value* other);
	virtual Value* BitwiseComplement();
	virtual Value* BitwiseXor(Value* other);
	virtual Value* BitwiseLeftShift(Value* other);
	virtual Value* BitwiseRightShift(Value* other);

	virtual Value* BooleanAnd(Value* other);
	virtual Value* BooleanOr(Value* other);
	virtual Value* BooleanNot();

};

#endif 

