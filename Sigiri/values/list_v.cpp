#include "value.h"

ListValue::ListValue(List<Value*>* value) : Value(Type::LIST) {
	mValues = value;
}

ListValue::~ListValue() {
	delete mValues;
}

Value* ListValue::add(Value* other) {
	return nullptr;
}

Value* ListValue::sub(Value* other) {
	return nullptr;
}

Value* ListValue::mul(Value* other) {
	return nullptr;
}

Value* ListValue::div(Value* other) {
	return nullptr;
}

Value* ListValue::mod(Value* other) {
	return nullptr;
}

Value* ListValue::s_pow(Value* other) {
	return nullptr;
}

Value* ListValue::comp_eq_eq(Value* other) {
	return nullptr;
}

Value* ListValue::comp_not_eq(Value* other) {
	return nullptr;
}

Value* ListValue::comp_greater(Value* other) {
	return nullptr;
}

Value* ListValue::comp_less(Value* other) {
	return nullptr;
}

Value* ListValue::comp_greater_eq(Value* other) {
	return nullptr;
}

Value* ListValue::comp_less_eq(Value* other) {
	return nullptr;
}

Value* ListValue::bitwise_and(Value* other) {
	return nullptr;
}

Value* ListValue::bitwise_or(Value* other) {
	return nullptr;
}

Value* ListValue::bitwise_xor(Value* other) {
	return nullptr;
}

Value* ListValue::shift_left(Value* other) {
	return nullptr;
}

Value* ListValue::shift_right(Value* other) {
	return nullptr;
}

Value* ListValue::boolean_and(Value* other) {
	return nullptr;
}

Value* ListValue::boolean_or(Value* other) {
	return nullptr;
}

Value* ListValue::bitwise_complement() {
	return this;
}

Value* ListValue::negate() {
	return this;
}

Value* ListValue::boolean_not() {
	return this;
}

Value* ListValue::clone() {
	return this;
}

void ListValue::print() {
	int len = mValues->count();
	printf("[");
	for (size_t i = 0; i < len; i++)
	{
		if (i + 1 == len)
			mValues->Get(i)->print();
		else {
			mValues->Get(i)->print();
			printf(", ");
		}
	}
	printf("]");
}

bool ListValue::asBoolean() {
	return mValues->count() == 0 ? false : true;
}

Value* ListValue::subscriptAccess(Value* at) {
	if (at->mType == Value::Type::INTEGER) {
		int index = ((IntegerValue*)at)->mValue;
		return mValues->Get(index)->clone(); // todo check whether correct or not
	}
	return this;
}

Value* ListValue::subscriptAssign(Value* at, Value* value) {
	if (at->mType == Value::Type::INTEGER) {
		int index = ((IntegerValue*)at)->mValue;
		delete mValues->Get(index); // todo dont delete objects
		mValues->Add(index, value);
	}
	return this;
}