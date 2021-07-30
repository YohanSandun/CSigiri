#include "../include/value.h"

StringValue::StringValue(String* value) : Value(Type::STRING) {
	mValue = value;
}

StringValue::~StringValue() {
	delete mValue;
}

Value* StringValue::add(Value* other) {
	return nullptr;
}

Value* StringValue::sub(Value* other) {
	return nullptr;
}

Value* StringValue::mul(Value* other) {
	return nullptr;
}

Value* StringValue::div(Value* other) {
	return nullptr;
}

Value* StringValue::s_pow(Value* other) {
	return nullptr;
}

Value* StringValue::comp_eq_eq(Value* other) {
	return nullptr;
}

Value* StringValue::comp_not_eq(Value* other) {
	return nullptr;
}

Value* StringValue::comp_greater(Value* other) {
	return nullptr;
}

Value* StringValue::comp_less(Value* other) {
	return nullptr;
}

Value* StringValue::comp_greater_eq(Value* other) {
	return nullptr;
}

Value* StringValue::comp_less_eq(Value* other) {
	return nullptr;
}

Value* StringValue::bitwise_and(Value* other) {
	return nullptr;
}

Value* StringValue::bitwise_or(Value* other) {
	return nullptr;
}

Value* StringValue::bitwise_xor(Value* other) {
	return nullptr;
}

Value* StringValue::shift_left(Value* other) {
	return nullptr;
}

Value* StringValue::shift_right(Value* other) {
	return nullptr;
}

Value* StringValue::boolean_and(Value* other) {
	return nullptr;
}

Value* StringValue::boolean_or(Value* other) {
	return nullptr;
}

Value* StringValue::bitwise_complement() {
	return this;
}

Value* StringValue::negate() {
	return this;
}

Value* StringValue::boolean_not() {
	return this;
}

Value* StringValue::clone() {
	return new StringValue(new String(mValue->mPtr));
}

void StringValue::print() {
	printf("%s", mValue->mPtr);
}

bool StringValue::asBoolean() {
	return mValue->getLength() == 0 ? false : true;
}