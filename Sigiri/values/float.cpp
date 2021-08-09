#include "value.h"

FloatValue::FloatValue(double value) : Value(Type::FLOAT) {
	mValue = value;
}

FloatValue::~FloatValue() {
	//printf("int %d Destroyed!\n", mValue);
}

Value* FloatValue::add(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue += ((IntegerValue*)other)->mValue;
		delete other;
		return this;
	}
	else if (other->mType == Type::FLOAT) {
		mValue += ((FloatValue*)other)->mValue;
		delete other;
		return this;
	}
}

Value* FloatValue::sub(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue -= ((IntegerValue*)other)->mValue;
		delete other;
		return this;
	}
	else if (other->mType == Type::FLOAT) {
		mValue -= ((FloatValue*)other)->mValue;
		delete other;
		return this;
	}
}

Value* FloatValue::mul(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue *= ((IntegerValue*)other)->mValue;
		delete other;
		return this;
	}
	else if (other->mType == Type::FLOAT) {
		mValue *= ((FloatValue*)other)->mValue;
		delete other;
		return this;
	}
}

Value* FloatValue::div(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue /= ((IntegerValue*)other)->mValue;
		delete other;
		return this;
	}
	else if (other->mType == Type::FLOAT) {
		mValue /= ((FloatValue*)other)->mValue;
		delete other;
		return this;
	}
}

Value* FloatValue::mod(Value* other) {
	return nullptr;
}

Value* FloatValue::s_pow(Value* other) {
	if (other->mType == Type::INTEGER) {
		int exp = ((IntegerValue*)other)->mValue;
		mValue = (int)pow(mValue, exp);
		delete other;
		return this;
	}
	else if (other->mType == Type::FLOAT) {
		double exp = ((FloatValue*)other)->mValue;
		mValue = pow(mValue, exp);
		delete other;
		return this;
	}
}

Value* FloatValue::comp_eq_eq(Value* other) {
	if (other->mType == Type::INTEGER) {
		IntegerValue* intValue = (IntegerValue*)other;
		intValue->mValue = mValue == intValue->mValue;
		delete this;
		return other;
	}
	else if (other->mType == Type::FLOAT) {
		int result = mValue == ((FloatValue*)other)->mValue;
		delete other;
		delete this;
		return new IntegerValue(result, true);
	}
}

Value* FloatValue::comp_not_eq(Value* other) {
	if (other->mType == Type::INTEGER) {
		IntegerValue* intValue = (IntegerValue*)other;
		intValue->mValue = mValue != intValue->mValue;
		delete this;
		return other;
	}
	else if (other->mType == Type::FLOAT) {
		int result = mValue != ((FloatValue*)other)->mValue;
		delete other;
		delete this;
		return new IntegerValue(result, true);
	}
}

Value* FloatValue::comp_greater(Value* other) {
	if (other->mType == Type::INTEGER) {
		IntegerValue* intValue = (IntegerValue*)other;
		intValue->mValue = mValue > intValue->mValue;
		delete this;
		return other;
	}
	else if (other->mType == Type::FLOAT) {
		int result = mValue > ((FloatValue*)other)->mValue;
		delete other;
		delete this;
		return new IntegerValue(result, true);
	}
}

Value* FloatValue::comp_less(Value* other) {
	if (other->mType == Type::INTEGER) {
		IntegerValue* intValue = (IntegerValue*)other;
		intValue->mValue = mValue < intValue->mValue;
		delete this;
		return other;
	}
	else if (other->mType == Type::FLOAT) {
		int result = mValue < ((FloatValue*)other)->mValue;
		delete other;
		delete this;
		return new IntegerValue(result, true);
	}
}

Value* FloatValue::comp_greater_eq(Value* other) {
	if (other->mType == Type::INTEGER) {
		IntegerValue* intValue = (IntegerValue*)other;
		intValue->mValue = mValue >= intValue->mValue;
		delete this;
		return other;
	}
	else if (other->mType == Type::FLOAT) {
		int result = mValue >= ((FloatValue*)other)->mValue;
		delete other;
		delete this;
		return new IntegerValue(result, true);
	}
}

Value* FloatValue::comp_less_eq(Value* other) {
	if (other->mType == Type::INTEGER) {
		IntegerValue* intValue = (IntegerValue*)other;
		intValue->mValue = mValue <= intValue->mValue;
		delete this;
		return other;
	}
	else if (other->mType == Type::FLOAT) {
		int result = mValue <= ((FloatValue*)other)->mValue;
		delete other;
		delete this;
		return new IntegerValue(result, true);
	}
}

Value* FloatValue::bitwise_and(Value* other) {
	if (other->mType == Type::INTEGER) {
		// impossible
		delete other;
		return this;
	}
}

Value* FloatValue::bitwise_or(Value* other) {
	if (other->mType == Type::INTEGER) {
		// impossible
		delete other;
		return this;
	}
}

Value* FloatValue::bitwise_xor(Value* other) {
	if (other->mType == Type::INTEGER) {
		// impossible
		delete other;
		return this;
	}
}

Value* FloatValue::shift_left(Value* other) {
	if (other->mType == Type::INTEGER) {
		// impossible
		delete other;
		return this;
	}
}

Value* FloatValue::shift_right(Value* other) {
	if (other->mType == Type::INTEGER) {
		// impossible
		delete other;
		return this;
	}
}

Value* FloatValue::boolean_and(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue = mValue && ((IntegerValue*)other)->mValue;
		delete other;
		return this;
	}
}

Value* FloatValue::boolean_or(Value* other) {
	if (other->mType == Type::INTEGER) {
		mValue = mValue || ((IntegerValue*)other)->mValue;
		delete other;
		return this;
	}
}

Value* FloatValue::bitwise_complement() {
	// impossible
	return this;
}

Value* FloatValue::negate() {
	mValue *= -1;
	return this;
}

Value* FloatValue::boolean_not() {
	mValue = !mValue;
	return this;
}

Value* FloatValue::clone() {
	return new FloatValue(mValue);
}

void FloatValue::print() {
	printf("%f", mValue);
}

bool FloatValue::asBoolean() {
	return mValue == 0 ? false : true;
}

Value* FloatValue::subscriptAccess(Value* at) {
	return this;
}

Value* FloatValue::subscriptAssign(Value* at, Value* value) {
	return this;
}