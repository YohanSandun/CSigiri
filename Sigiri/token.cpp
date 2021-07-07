#include "include/token.h"

Token::Token(Type type) {
	mType = type;
}

Token::Token(String* value, Type type) {
	mValue = value;
	mType = type;
}

Token::~Token() {
	if (mValue != nullptr)
		delete mValue;
}