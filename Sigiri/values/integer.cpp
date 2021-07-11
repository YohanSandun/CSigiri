#include "../include/value.h"

IntegerValue::IntegerValue(int value) : Value(Type::INTEGER) {
	mValue = value;
}

Value* IntegerValue::add(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue += ((IntegerValue*)other)->mValue;
		delete other;
		return this;
	}
}

Value* IntegerValue::sub(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue -= ((IntegerValue*)other)->mValue;
		delete other;
		return this;
	}
}

Value* IntegerValue::mul(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue *= ((IntegerValue*)other)->mValue;
		delete other;
		return this;
	}
}

Value* IntegerValue::div(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue /= ((IntegerValue*)other)->mValue;
		delete other;
		return this;
	}
}

Value* IntegerValue::s_pow(Value* other) {
	if (other->mType == Type::INTEGER) {
		int exp = ((IntegerValue*)other)->mValue;
		mValue = (int)pow(mValue, exp);
		delete other;
		return this;
	}
}

Value* IntegerValue::negate() {
	mValue *= -1;
	return this;
}

Value* IntegerValue::clone() {
	return new IntegerValue(mValue);
}

void IntegerValue::print() {
	printf("%d", mValue);
}