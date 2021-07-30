#include "../include/value.h"

MethodValue::MethodValue(String* name, Node* body, List<String*>* params) : Value(Type::METHOD) {
	mBody = body;
	mName = name;
	mParams = params;
}

MethodValue::~MethodValue() {
	printf("method '%s' Destroyed!\n", mName->mPtr);
	delete mName;
	delete mBody;
}

Value* MethodValue::add(Value* other) {
	return this;
}

Value* MethodValue::sub(Value* other) {
	return this;
}

Value* MethodValue::mul(Value* other) {
	return this;
}

Value* MethodValue::div(Value* other) {
	return this;
}

Value* MethodValue::s_pow(Value* other) {
	return this;
}

Value* MethodValue::bitwise_and(Value* other) {
	return this;
}

Value* MethodValue::bitwise_or(Value* other) {
	return this;
}

Value* MethodValue::bitwise_xor(Value* other) {
	return this;
}

Value* MethodValue::shift_left(Value* other) {
	return this;
}

Value* MethodValue::shift_right(Value* other) {
	return this;
}

Value* MethodValue::boolean_and(Value* other) {
	return this;
}

Value* MethodValue::boolean_or(Value* other) {
	return this;
}

Value* MethodValue::comp_eq_eq(Value* other) {
	return this;
}

Value* MethodValue::comp_greater(Value* other) {
	return this;
}

Value* MethodValue::comp_greater_eq(Value* other) {
	return this;
}

Value* MethodValue::comp_less(Value* other) {
	return this;
}

Value* MethodValue::comp_less_eq(Value* other) {
	return this;
}

Value* MethodValue::comp_not_eq(Value* other) {
	return this;
}

Value* MethodValue::bitwise_complement() {
	return this;
}

Value* MethodValue::boolean_not() {
	return this;
}

Value* MethodValue::negate() {
	return this;
}

Value* MethodValue::clone() {
	return this;
}

void MethodValue::print() {
	printf("Method '%s'", mName->mPtr);
}

bool MethodValue::asBoolean() {
	return false;
}