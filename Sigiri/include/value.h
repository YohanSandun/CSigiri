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
	virtual Value* negate() = 0;

	virtual Value* clone() = 0;

	virtual void print() = 0;
};

class IntegerValue : public Value {
public:
	int mValue;
	IntegerValue(int value);

	Value* add(Value* other);
	Value* sub(Value* other);
	Value* mul(Value* other);
	Value* div(Value* other);
	Value* s_pow(Value* other);
	Value* negate();
	Value* clone();

	void print();
};