#include "value.h"

ClassValue::ClassValue(String* name, Node* body) : Value(Type::CLASS) {
	mBody = body;
	mName = name;
}

ClassValue::~ClassValue() {
	//printf("method '%s' Destroyed!\n", mName->mPtr);
	delete mName;
	delete mBody;
}

Value* ClassValue::add(Value* other) {
	return this;
}

Value* ClassValue::sub(Value* other) {
	return this;
}

Value* ClassValue::mul(Value* other) {
	return this;
}

Value* ClassValue::div(Value* other) {
	return this;
}

Value* ClassValue::mod(Value* other) {
	return this;
}

Value* ClassValue::s_pow(Value* other) {
	return this;
}

Value* ClassValue::bitwise_and(Value* other) {
	return this;
}

Value* ClassValue::bitwise_or(Value* other) {
	return this;
}

Value* ClassValue::bitwise_xor(Value* other) {
	return this;
}

Value* ClassValue::shift_left(Value* other) {
	return this;
}

Value* ClassValue::shift_right(Value* other) {
	return this;
}

Value* ClassValue::boolean_and(Value* other) {
	return this;
}

Value* ClassValue::boolean_or(Value* other) {
	return this;
}

Value* ClassValue::comp_eq_eq(Value* other) {
	return this;
}

Value* ClassValue::comp_greater(Value* other) {
	return this;
}

Value* ClassValue::comp_greater_eq(Value* other) {
	return this;
}

Value* ClassValue::comp_less(Value* other) {
	return this;
}

Value* ClassValue::comp_less_eq(Value* other) {
	return this;
}

Value* ClassValue::comp_not_eq(Value* other) {
	return this;
}

Value* ClassValue::bitwise_complement() {
	return this;
}

Value* ClassValue::boolean_not() {
	return this;
}

Value* ClassValue::negate() {
	return this;
}

Value* ClassValue::clone() {
	return this;
}

void ClassValue::print() {
	printf("Class definition '%s'\n", mName->mPtr);
}

bool ClassValue::asBoolean() {
	return false;
}

Value* ClassValue::subscriptAccess(Value* at) {
	return this;
}

Value* ClassValue::subscriptAssign(Value* at, Value* value) {
	return this;
}