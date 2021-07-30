#include "../include/value.h"

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
	int len = mValues->getCount();
	printf("[");
	for (size_t i = 0; i < len; i++)
	{
		if (i + 1 == len)
			mValues->get(i)->print();
		else {
			mValues->get(i)->print();
			printf(", ");
		}
	}
	printf("]");
}

bool ListValue::asBoolean() {
	return mValues->getCount() == 0 ? false : true;
}