#include "token.h"

Token::Token(Type type) {
	type = type;
}

Token::Token(String* value, Type type) {
	value = value;
	type = type;
}

Token::~Token() {
	if (value != nullptr)
		delete value;
}