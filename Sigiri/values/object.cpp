#include "object.h"

ObjectValue::ObjectValue(SymbolsRuntime* symbols) : Value(Type::OBJECT) {
	mSymbols = symbols;
}

ObjectValue::~ObjectValue() {
	//printf("method '%s' Destroyed!\n", mName->mPtr);
}

Value* ObjectValue::add(Value* other) {
	return this;
}

Value* ObjectValue::sub(Value* other) {
	return this;
}

Value* ObjectValue::mul(Value* other) {
	return this;
}

Value* ObjectValue::div(Value* other) {
	return this;
}

Value* ObjectValue::mod(Value* other) {
	return this;
}

Value* ObjectValue::s_pow(Value* other) {
	return this;
}

Value* ObjectValue::bitwise_and(Value* other) {
	return this;
}

Value* ObjectValue::bitwise_or(Value* other) {
	return this;
}

Value* ObjectValue::bitwise_xor(Value* other) {
	return this;
}

Value* ObjectValue::shift_left(Value* other) {
	return this;
}

Value* ObjectValue::shift_right(Value* other) {
	return this;
}

Value* ObjectValue::boolean_and(Value* other) {
	return this;
}

Value* ObjectValue::boolean_or(Value* other) {
	return this;
}

Value* ObjectValue::comp_eq_eq(Value* other) {
	return this;
}

Value* ObjectValue::comp_greater(Value* other) {
	return this;
}

Value* ObjectValue::comp_greater_eq(Value* other) {
	return this;
}

Value* ObjectValue::comp_less(Value* other) {
	return this;
}

Value* ObjectValue::comp_less_eq(Value* other) {
	return this;
}

Value* ObjectValue::comp_not_eq(Value* other) {
	return this;
}

Value* ObjectValue::bitwise_complement() {
	return this;
}

Value* ObjectValue::boolean_not() {
	return this;
}

Value* ObjectValue::negate() {
	return this;
}

Value* ObjectValue::clone() {
	return this;
}

void ObjectValue::print() {
	printf("Object");
}

bool ObjectValue::asBoolean() {
	return false;
}

Value* ObjectValue::subscriptAccess(Value* at) {
	return this;
}

Value* ObjectValue::subscriptAssign(Value* at, Value* value) {
	return this;
}