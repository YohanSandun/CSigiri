#include "include/value.h"
#include <cstdio>

Value::Value(Type type) {
	mType = type;
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

void Value::print() {

}

IntegerValue::IntegerValue(int value) : Value(Type::INTEGER) {
	mValue = value;
}

Value* IntegerValue::add(Value* other) {
	if (other->mType == Type::INTEGER) {
		return new IntegerValue(mValue + ((IntegerValue*)other)->mValue);
	}
}

Value* IntegerValue::sub(Value* other) {
	if (other->mType == Type::INTEGER) {
		return new IntegerValue(mValue - ((IntegerValue*)other)->mValue);
	}
}

Value* IntegerValue::mul(Value* other) {
	if (other->mType == Type::INTEGER) {
		return new IntegerValue(mValue * ((IntegerValue*)other)->mValue);
	}
}

Value* IntegerValue::div(Value* other) {
	if (other->mType == Type::INTEGER) {
		return new IntegerValue(mValue / ((IntegerValue*)other)->mValue);
	}
}

void IntegerValue::print() {
	printf("%d", mValue);
}