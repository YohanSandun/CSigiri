#pragma once

class Value {
public:
	enum class Type {
		INTEGER,
		FLOAT
	} mType;
	Value(Type type);

	virtual Value* add(Value* other);
	virtual Value* sub(Value* other);
	virtual Value* mul(Value* other);
	virtual Value* div(Value* other);

	virtual void print();
};

class IntegerValue : public Value {
public:
	int mValue;
	IntegerValue(int value);

	Value* add(Value* other);
	Value* sub(Value* other);
	Value* mul(Value* other);
	Value* div(Value* other);

	void print();
};