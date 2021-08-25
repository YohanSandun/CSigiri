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
#ifndef INTEGER_VALUE_H
#define INTEGER_VALUE_H

#include "value.h"

struct IntegerValue : public Value
{
	bool is_boolean = false;
	int value;
	IntegerValue(int value, U_INT32 line, U_INT32 column_start, U_INT32 column_end, bool is_boolean = false);
	~IntegerValue();
	static Value* CastFrom(Value* value);
	void Print();
	Value* Clone();
	bool GetAsBoolean();

	Value* Add(Value* other);
	Value* Subtract(Value* other);
	Value* Multiply(Value* other);
	Value* Divide(Value* other);
	Value* Mod(Value* other);
	Value* Power(Value* other);

	Value* Equals(Value* other);
	Value* NotEquals(Value* other);
	Value* LessThan(Value* other);
	Value* LessThanOrEqual(Value* other);
	Value* GreaterThan(Value* other);
	Value* GreaterThanOrEqual(Value* other);

	Value* BitwiseAnd(Value* other);
	Value* BitwiseOr(Value* other);
	Value* BitwiseComplement();
	Value* BitwiseXor(Value* other);
	Value* BitwiseLeftShift(Value* other);
	Value* BitwiseRightShift(Value* other);

	Value* BooleanAnd(Value* other);
	Value* BooleanOr(Value* other);
	Value* BooleanNot();
};

#endif 

