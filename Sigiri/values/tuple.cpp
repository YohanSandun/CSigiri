#include "value.h"

TupleValue::TupleValue(List<Value*>* value) : Value(Type::TUPLE) {
	mValues = value;
}

TupleValue::~TupleValue() {
	delete mValues;
}

Value* TupleValue::add(Value* other) {
	return nullptr;
}

Value* TupleValue::sub(Value* other) {
	return nullptr;
}

Value* TupleValue::mul(Value* other) {
	return nullptr;
}

Value* TupleValue::div(Value* other) {
	return nullptr;
}

Value* TupleValue::mod(Value* other) {
	return nullptr;
}

Value* TupleValue::s_pow(Value* other) {
	return nullptr;
}

Value* TupleValue::comp_eq_eq(Value* other) {
	return nullptr;
}

Value* TupleValue::comp_not_eq(Value* other) {
	return nullptr;
}

Value* TupleValue::comp_greater(Value* other) {
	return nullptr;
}

Value* TupleValue::comp_less(Value* other) {
	return nullptr;
}

Value* TupleValue::comp_greater_eq(Value* other) {
	return nullptr;
}

Value* TupleValue::comp_less_eq(Value* other) {
	return nullptr;
}

Value* TupleValue::bitwise_and(Value* other) {
	return nullptr;
}

Value* TupleValue::bitwise_or(Value* other) {
	return nullptr;
}

Value* TupleValue::bitwise_xor(Value* other) {
	return nullptr;
}

Value* TupleValue::shift_left(Value* other) {
	return nullptr;
}

Value* TupleValue::shift_right(Value* other) {
	return nullptr;
}

Value* TupleValue::boolean_and(Value* other) {
	return nullptr;
}

Value* TupleValue::boolean_or(Value* other) {
	return nullptr;
}

Value* TupleValue::bitwise_complement() {
	return this;
}

Value* TupleValue::negate() {
	return this;
}

Value* TupleValue::boolean_not() {
	return this;
}

Value* TupleValue::clone() {
	return this;
}

void TupleValue::print() {
	int len = mValues->count();
	printf("(");
	for (size_t i = 0; i < len; i++)
	{
		if (i + 1 == len)
			mValues->Get(i)->print();
		else {
			mValues->Get(i)->print();
			printf(", ");
		}
	}
	printf(")");
}

bool TupleValue::asBoolean() {
	return mValues->count() == 0 ? false : true;
}

Value* TupleValue::subscriptAccess(Value* at) {
	if (at->mType == Value::Type::INTEGER) {
		int index = ((IntegerValue*)at)->mValue;
		return mValues->Get(index)->clone(); // todo check whether correct or not
	}
	return this;
}

Value* TupleValue::subscriptAssign(Value* at, Value* value) {
	if (at->mType == Value::Type::INTEGER) {
		int index = ((IntegerValue*)at)->mValue;
		delete mValues->Get(index); // todo dont delete objects
		mValues->Add(index, value);
	}
	return this;
}