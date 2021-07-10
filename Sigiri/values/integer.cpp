#include "../include/value.h"

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

Value* IntegerValue::s_pow(Value* other) {
	if (other->mType == Type::INTEGER) {
		int exp = ((IntegerValue*)other)->mValue;
		return new IntegerValue((int)pow(mValue, exp));
	}
}

Value* IntegerValue::negate() {
	return new IntegerValue(-mValue);
}

void IntegerValue::print() {
	printf("%d", mValue);
}