#include "include/lexer.h"

Lexer::Lexer(String* code) {
	mCode = code;
	mCodeLen = code->getLength();
	advance();
}

Lexer::~Lexer() {
	delete mCode;
}

void Lexer::advance() {
	mIndex++;
	if (mIndex < mCodeLen)
		mCurrentChar = mCode->mPtr[mIndex];
	else
		mCurrentChar = '\0';
}

char Lexer::peek(int amount) {
	if (mIndex + amount < mCodeLen)
		return mCode->mPtr[mIndex + amount];
	return '\0';
}

List<Token*>* Lexer::generateTokens() {
	List<Token*>* tokens = new List<Token*>();
	while (mCurrentChar != '\0') {
		mColumn++;
		if (mCurrentChar == ' ' || mCurrentChar == '\t')
			advance();
		else if (mCurrentChar == '\n' || mCurrentChar == '\r') { // todo
			mLine++;
			mColumn = 0;
			tokens->add(new Token(Token::Type::NEWLINE));
			advance();
		}
		else if (mCurrentChar == '+') {
			tokens->add(new Token(Token::Type::PLUS));
			advance();
		}
		else if (mCurrentChar == '-') {
			tokens->add(new Token(Token::Type::MINUS));
			advance();
		}
		else if (mCurrentChar == '*') {
			if (peek(1) == '*') {
				tokens->add(new Token(Token::Type::POWER));
				advance();
				advance();
			}
			else {
				tokens->add(new Token(Token::Type::ASTERIX));
				advance();
			}
		}
		else if (mCurrentChar == '/') {
			tokens->add(new Token(Token::Type::FW_SLASH));
			advance();
		}
		else if (mCurrentChar == '%') {
			tokens->add(new Token(Token::Type::MODULUS)); // todo
			advance();
		}
		else if (mCurrentChar == '(') {
			tokens->add(new Token(Token::Type::L_PAREN));
			advance();
		}
		else if (mCurrentChar == ')') {
			tokens->add(new Token(Token::Type::R_PAREN));
			advance();
		}
		else if (mCurrentChar == '{') {
			tokens->add(new Token(Token::Type::L_BRACE));
			advance();
		}
		else if (mCurrentChar == '}') {
			tokens->add(new Token(Token::Type::R_BRACE));
			advance();
		}
		else if (mCurrentChar == ':') {
			tokens->add(new Token(Token::Type::COLON));
			advance();
		}
		else if (mCurrentChar == ';') {
			tokens->add(new Token(Token::Type::NEWLINE));
			advance();
		}
		else if (mCurrentChar == '^') {
			tokens->add(new Token(Token::Type::BITWISE_XOR));
			advance();
		}
		else if (mCurrentChar == '~') {
			tokens->add(new Token(Token::Type::BITWISE_COMPLEMENT));
			advance();
		}
		else if (mCurrentChar == ',') {
			tokens->add(new Token(Token::Type::COMMA));
			advance();
		}
		else if (mCurrentChar == '=') {
			if (peek(1) == '=') {
				tokens->add(new Token(Token::Type::EQUALS_EQUALS));
				advance();
				advance();
			} else {
				tokens->add(new Token(Token::Type::EQUALS));
				advance();
			}
		}
		else if (mCurrentChar == '<') {
			if (peek(1) == '=') {
				tokens->add(new Token(Token::Type::LESS_EQ));
				advance();
				advance();
			}
			else if (peek(1) == '<') {
				tokens->add(new Token(Token::Type::LEFT_SHIFT));
				advance();
				advance();
			}
			else {
				tokens->add(new Token(Token::Type::LESS_THAN));
				advance();
			}
		}
		else if (mCurrentChar == '>') {
			if (peek(1) == '=') {
				tokens->add(new Token(Token::Type::GREATER_EQ));
				advance();
				advance();
			}
			else if (peek(1) == '>') {
				tokens->add(new Token(Token::Type::RIGHT_SHIFT));
				advance();
				advance();
			}
			else {
				tokens->add(new Token(Token::Type::GREATER_THAN));
				advance();
			}
		}
		else if (mCurrentChar == '!') {
			if (peek(1) == '=') {
				tokens->add(new Token(Token::Type::NOT_EQUALS));
				advance();
				advance();
			}
			else {
				tokens->add(new Token(Token::Type::BOOLEAN_NOT));
				advance();
			}
		}
		else if (mCurrentChar == '&') {
			if (peek(1) == '&') {
				tokens->add(new Token(Token::Type::BOOLEAN_AND));
				advance();
				advance();
			}
			else {
				tokens->add(new Token(Token::Type::BITWISE_AND));
				advance();
			}
		}
		else if (mCurrentChar == '|') {
			if (peek(1) == '|') {
				tokens->add(new Token(Token::Type::BOOLEAN_OR));
				advance();
				advance();
			}
			else {
				tokens->add(new Token(Token::Type::BITWISE_OR));
				advance();
			}
		}
		else if (mCurrentChar >= '0' && mCurrentChar <= '9') {
			tokens->add(makeNumber());
		}
		else if (mCurrentChar == '"') {
			tokens->add(makeString());
		}
		else if ((mCurrentChar >= 'a' && mCurrentChar <= 'z') ||
			(mCurrentChar >= 'A' && mCurrentChar <= 'Z') || mCurrentChar == '_') {
			tokens->add(makeIdentifier());
		}
	}
	tokens->add(new Token(Token::Type::EOF_TOKEN));
	return tokens;
}

Token* Lexer::makeString() {
	advance();
	String* str = new String(10);
	while (mCurrentChar != '\0') {
		if (mCurrentChar == '\\') {
			advance();
			if (mCurrentChar == 'n')
				str->append('\n');
			else if (mCurrentChar == 't')
				str->append('\t');
			else if (mCurrentChar == 'b')
				str->append('\b');
			else
				str->append(mCurrentChar);
			advance();
			continue;
		}
		if (mCurrentChar == '\"') {
			advance();
			break;
		}
		str->append(mCurrentChar);
		advance();
	}
	return new Token(str, Token::Type::STRING);
}

Token* Lexer::makeNumber() {
	String* number = new String(5);
	int dotCount = 0;
	while (mCurrentChar != '\0' && ((mCurrentChar >= '0' && mCurrentChar <= '9') || mCurrentChar == '.')) {
		if (mCurrentChar == '.')
			dotCount++;
		number->append(mCurrentChar);
		advance();
	}
	if (dotCount == 0)
		return new Token(number, Token::Type::INT_NUMBER);
	else
		return new Token(number, Token::Type::FLOAT_NUMBER);
}

Token* Lexer::makeIdentifier() {
	String* id = new String(5);
	while (mCurrentChar != '\0' && 
		  ((mCurrentChar >= '0' && mCurrentChar <= '9') || 
		  ((mCurrentChar >= 'a' && mCurrentChar <= 'z') ||
		  (mCurrentChar >= 'A' && mCurrentChar <= 'Z') || mCurrentChar == '_'))) {
		id->append(mCurrentChar);
		advance();
	}

	if (id->compare("var")) {
		delete id;
		return new Token(Token::Type::KEYWORD_VAR);
	}
	else if (id->compare("int")) {
		delete id;
		return new Token(Token::Type::KEYWORD_INT);
	}
	else if (id->compare("for")) {
		delete id;
		return new Token(Token::Type::KEYWORD_FOR);
	}
	else if (id->compare("to")) {
		delete id;
		return new Token(Token::Type::KEYWORD_TO);
	}
	else if (id->compare("step")) {
		delete id;
		return new Token(Token::Type::KEYWORD_STEP);
	}
	else if (id->compare("method")) {
		delete id;
		return new Token(Token::Type::KEYWORD_METHOD);
	}
	else if (id->compare("return")) {
		delete id;
		return new Token(Token::Type::KEYWORD_RETURN);
	}
	else if (id->compare("break")) {
		delete id;
		return new Token(Token::Type::KEYWORD_BREAK);
	}
	else if (id->compare("continue")) {
		delete id;
		return new Token(Token::Type::KEYWORD_CONTINUE);
	}
	else if (id->compare("if")) {
		delete id;
		return new Token(Token::Type::KEYWORD_IF);
	}
	else if (id->compare("elif")) {
		delete id;
		return new Token(Token::Type::KEYWORD_ELIF);
	}
	else if (id->compare("else")) {
		delete id;
		return new Token(Token::Type::KEYWORD_ELSE);
	}
	else if (id->compare("class")) {
		delete id;
		return new Token(Token::Type::KEYWORD_CLASS);
	}
	return new Token(id, Token::Type::IDENTIFIER);
}