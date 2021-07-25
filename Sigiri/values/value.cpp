#include "../include/value.h"

Value::Value(Type type) {
	mType = type;
}

Value::Value() {
	mType = Type::_NULL_;
}

Value* Value::add(Value* other) {
	return this;
}

Value* Value::sub(Value* other) {
	return this;
}

Value* Value::mul(Value* other) {
	return this;
}

Value* Value::div(Value* other) {
	return this;
}

Value* Value::s_pow(Value* other) {
	return this;
}

Value* Value::bitwise_and(Value* other) {
	return this;
}

Value* Value::bitwise_or(Value* other) {
	return this;
}

Value* Value::bitwise_xor(Value* other) {
	return this;
}

Value* Value::shift_left(Value* other) {
	return this;
}

Value* Value::shift_right(Value* other) {
	return this;
}

Value* Value::boolean_and(Value* other) {
	return this;
}

Value* Value::boolean_or(Value* other) {
	return this;
}

Value* Value::comp_eq_eq(Value* other) {
	return this;
}

Value* Value::comp_greater(Value* other) {
	return this;
}

Value* Value::comp_greater_eq(Value* other) {
	return this;
}

Value* Value::comp_less(Value* other) {
	return this;
}

Value* Value::comp_less_eq(Value* other) {
	return this;
}

Value* Value::comp_not_eq(Value* other) {
	return this;
}

Value* Value::bitwise_complement() {
	return this;
}

Value* Value::boolean_not() {
	return this;
}

Value* Value::negate() {
	return this;
}

Value* Value::clone() {
	return this;
}

void Value::print() {
	printf("VALUE");
}