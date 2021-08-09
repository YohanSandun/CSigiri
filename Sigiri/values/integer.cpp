#include "value.h"

IntegerValue::IntegerValue(int value) : Value(Type::INTEGER) {
	mValue = value;
}

IntegerValue::IntegerValue(int value, bool isBool) : Value(Type::INTEGER) {
	mValue = value;
	this->isBool = isBool;
}

IntegerValue::~IntegerValue() {
	//printf("int %d Destroyed!\n", mValue);
}

Value* IntegerValue::add(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue += ((IntegerValue*)other)->mValue;
		delete other;
		return this;
	}
	else if (other->mType == Type::FLOAT) {
		((FloatValue*)other)->mValue += mValue;
		delete this;
		return other;
	}
}

Value* IntegerValue::sub(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue -= ((IntegerValue*)other)->mValue;
		delete other;
		return this;
	}
	else if (other->mType == Type::FLOAT) {
		FloatValue* floatValue = (FloatValue*)other;
		double result = mValue - floatValue->mValue;
		floatValue->mValue = result;
		delete this;
		return other;
	}
}

Value* IntegerValue::mul(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue *= ((IntegerValue*)other)->mValue;
		delete other;
		return this;
	}
	else if (other->mType == Type::FLOAT) {
		((FloatValue*)other)->mValue *= mValue;
		delete this;
		return other;
	}
}

Value* IntegerValue::mod(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue %= ((IntegerValue*)other)->mValue;
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
	else if (other->mType == Type::FLOAT) {
		FloatValue* floatValue = (FloatValue*)other;
		double result = mValue / floatValue->mValue;
		floatValue->mValue = result;
		delete this;
		return other;
	}
}

Value* IntegerValue::s_pow(Value* other) {
	if (other->mType == Type::INTEGER) {
		int exp = ((IntegerValue*)other)->mValue;
		mValue = (int)pow(mValue, exp);
		delete other;
		return this;
	}
	else if (other->mType == Type::FLOAT) {
		FloatValue* floatValue = (FloatValue*)other;
		double exp = floatValue->mValue;
		floatValue->mValue = pow(mValue, exp);
		delete this;
		return other;
	}
}

Value* IntegerValue::comp_eq_eq(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue = mValue == ((IntegerValue*)other)->mValue;
		isBool = true;
		delete other;
		return this;
	}
	else if (other->mType == Type::FLOAT) {
		mValue = mValue == ((FloatValue*)other)->mValue;
		delete other;
		isBool = true;
		return this;
	}
}

Value* IntegerValue::comp_not_eq(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue = mValue != ((IntegerValue*)other)->mValue;
		isBool = true;
		delete other;
		return this;
	}
	else if (other->mType == Type::FLOAT) {
		mValue = mValue != ((FloatValue*)other)->mValue;
		delete other;
		isBool = true;
		return this;
	}
}

Value* IntegerValue::comp_greater(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue = mValue > ((IntegerValue*)other)->mValue;
		isBool = true;
		delete other;
		return this;
	}
	else if (other->mType == Type::FLOAT) {
		mValue = mValue > ((FloatValue*)other)->mValue;
		delete other;
		isBool = true;
		return this;
	}
}

Value* IntegerValue::comp_less(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue = mValue < ((IntegerValue*)other)->mValue;
		isBool = true;
		delete other;
		return this;
	}
	else if (other->mType == Type::FLOAT) {
		mValue = mValue < ((FloatValue*)other)->mValue;
		delete other;
		isBool = true;
		return this;
	}
}

Value* IntegerValue::comp_greater_eq(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue = mValue >= ((IntegerValue*)other)->mValue;
		isBool = true;
		delete other;
		return this;
	}
	else if (other->mType == Type::FLOAT) {
		mValue = mValue >= ((FloatValue*)other)->mValue;
		delete other;
		isBool = true;
		return this;
	}
}

Value* IntegerValue::comp_less_eq(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue = mValue <= ((IntegerValue*)other)->mValue;
		isBool = true;
		delete other;
		return this;
	}
	else if (other->mType == Type::FLOAT) {
		mValue = mValue <= ((FloatValue*)other)->mValue;
		delete other;
		isBool = true;
		return this;
	}
}

Value* IntegerValue::bitwise_and(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue &= ((IntegerValue*)other)->mValue;
		delete other;
		return this;
	}
}

Value* IntegerValue::bitwise_or(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue |= ((IntegerValue*)other)->mValue;
		delete other;
		return this;
	}
}

Value* IntegerValue::bitwise_xor(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue ^= ((IntegerValue*)other)->mValue;
		delete other;
		return this;
	}
}

Value* IntegerValue::shift_left(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue <<= ((IntegerValue*)other)->mValue;
		delete other;
		return this;
	}
}

Value* IntegerValue::shift_right(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue >>= ((IntegerValue*)other)->mValue;
		delete other;
		return this;
	}
}

Value* IntegerValue::boolean_and(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue = mValue && ((IntegerValue*)other)->mValue;
		delete other;
		return this;
	}
	else if (other->mType == Type::FLOAT) {
		mValue = mValue && ((FloatValue*)other)->mValue;
		delete other;
		return this;
	}
}

Value* IntegerValue::boolean_or(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue = mValue || ((IntegerValue*)other)->mValue;
		delete other;
		return this;
	}
	else if (other->mType == Type::FLOAT) {
		mValue = mValue || ((FloatValue*)other)->mValue;
		delete other;
		return this;
	}
}

Value* IntegerValue::bitwise_complement() {
	mValue = ~mValue;
	return this;
}

Value* IntegerValue::negate() {
	mValue *= -1;
	return this;
}

Value* IntegerValue::boolean_not() {
	isBool = true;
	mValue = !mValue;
	return this;
}

Value* IntegerValue::clone() {
	return new IntegerValue(mValue);
}

void IntegerValue::print() {
	if (isBool)
		printf("%s", mValue == 0 ? "false" : "true");
	else
		printf("%d", mValue);
}

bool IntegerValue::asBoolean() {
	return mValue == 0 ? false : true;
}

Value* IntegerValue::subscriptAccess(Value* at) {
	return this;
}

Value* IntegerValue::subscriptAssign(Value* at, Value* value) {
	return this;
}