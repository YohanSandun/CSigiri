#pragma once

#include <cstdio>
#include <math.h>

class Value {
public:
	enum class Type {
		INTEGER,
		FLOAT
	} mType;
	Value(Type type);

	virtual Value* add(Value* other) = 0;
	virtual Value* sub(Value* other) = 0;
	virtual Value* mul(Value* other) = 0;
	virtual Value* div(Value* other) = 0;
	virtual Value* s_pow(Value* other) = 0;
	virtual Value* comp_eq_eq(Value* other) = 0;
	virtual Value* comp_not_eq(Value* other) = 0;
	virtual Value* comp_less(Value* other) = 0;
	virtual Value* comp_greater(Value* other) = 0;
	virtual Value* comp_less_eq(Value* other) = 0;
	virtual Value* comp_greater_eq(Value* other) = 0;

	virtual Value* bitwise_or(Value* other) = 0;
	virtual Value* bitwise_xor(Value* other) = 0;
	virtual Value* bitwise_and(Value* other) = 0;

	virtual Value* shift_left(Value* other) = 0;
	virtual Value* shift_right(Value* other) = 0;

	virtual Value* boolean_and(Value* other) = 0;
	virtual Value* boolean_or(Value* other) = 0;

	virtual Value* negate() = 0;
	virtual Value* boolean_not() = 0;
	virtual Value* bitwise_complement() = 0;

	virtual Value* clone() = 0;

	virtual void print() = 0;
};

class IntegerValue : public Value {
public:
	int mValue;
	bool isBool = false;
	IntegerValue(int value);

	Value* add(Value* other);
	Value* sub(Value* other);
	Value* mul(Value* other);
	Value* div(Value* other);
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

	void print();
};