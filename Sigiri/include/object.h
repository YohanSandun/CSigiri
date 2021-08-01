#pragma once

#include "value.h"
#include "context.h"

class ObjectValue : public Value {
public:
	SymbolsRuntime* mSymbols;
	ObjectValue(SymbolsRuntime* symbols);
	~ObjectValue();

	Value* add(Value* other);
	Value* sub(Value* other);
	Value* mul(Value* other);
	Value* div(Value* other);
	Value* mod(Value* other);
	Value* s_pow(Value* other);
	Value* comp_eq_eq(Value* other);
	Value* comp_not_eq(Value* other);
	Value* comp_less(Value* other);
	Value* comp_greater(Value* other);
	Value* comp_less_eq(Value* other);
	Value* comp_greater_eq(Value* other);

	Value* bitwise_or(Value* other);
	Value* bitwise_xor(Value* other);
	Value* bitwise_and(Value* other);

	Value* shift_left(Value* other);
	Value* shift_right(Value* other);

	Value* boolean_and(Value* other);
	Value* boolean_or(Value* other);

	Value* bitwise_complement();
	Value* negate();
	Value* boolean_not();
	Value* clone();

	bool asBoolean();

	Value* subscriptAccess(Value* at);
	Value* subscriptAssign(Value* at, Value* value);

	void print();
};