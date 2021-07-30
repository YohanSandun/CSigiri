#pragma once

#include <cstdio>
#include <math.h>
#include "node.h"
#include "string.h"

class Value {
public:
	enum class Type {
		_NULL_,
		INTEGER,
		FLOAT,
		STRING,
		METHOD
	} mType;
	Value(Type type);
	Value();
	virtual ~Value();
	virtual Value* add(Value* other);
	virtual Value* sub(Value* other);
	virtual Value* mul(Value* other);
	virtual Value* div(Value* other) ;
	virtual Value* s_pow(Value* other) ;
	virtual Value* comp_eq_eq(Value* other) ;
	virtual Value* comp_not_eq(Value* other) ;
	virtual Value* comp_less(Value* other) ;
	virtual Value* comp_greater(Value* other) ;
	virtual Value* comp_less_eq(Value* other) ;
	virtual Value* comp_greater_eq(Value* other) ;

	virtual Value* bitwise_or(Value* other);
	virtual Value* bitwise_xor(Value* other);
	virtual Value* bitwise_and(Value* other) ;

	virtual Value* shift_left(Value* other);
	virtual Value* shift_right(Value* other);

	virtual Value* boolean_and(Value* other);
	virtual Value* boolean_or(Value* other);

	virtual Value* negate();
	virtual Value* boolean_not();
	virtual Value* bitwise_complement();

	virtual Value* clone();

	virtual void print();

	int mRefCount = 1;
	void incRefCount();
	void decRefCount();

	virtual bool asBoolean();
};

class IntegerValue : public Value {
public:
	int mValue;
	bool isBool = false;
	IntegerValue(int value);
	IntegerValue(int value, bool isBool);
	~IntegerValue();

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

	bool asBoolean();

	void print();
};

class FloatValue : public Value {
public:
	double mValue;
	FloatValue(double value);
	~FloatValue();

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

	bool asBoolean();

	void print();
};

class StringValue : public Value {
public:
	String* mValue;
	StringValue(String* value);
	~StringValue();

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

	bool asBoolean();

	void print();
};

class MethodValue : public Value {
public:
	String* mName;
	Node* mBody;
	List<String*>* mParams;
	MethodValue(String* name, Node* body, List<String*>* params);
	~MethodValue();

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

	bool asBoolean();

	void print();
};