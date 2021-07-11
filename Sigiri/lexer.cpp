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
		else if (mCurrentChar == '\n' || mCurrentChar == '\r') {
			mLine++;
			mColumn = 0;
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
		else if (mCurrentChar == '(') {
			tokens->add(new Token(Token::Type::L_PAREN));
			advance();
		}
		else if (mCurrentChar == ')') {
			tokens->add(new Token(Token::Type::R_PAREN));
			advance();
		}
		else if (mCurrentChar == ':') {
			tokens->add(new Token(Token::Type::COLON));
			advance();
		}
		else if (mCurrentChar == ';') {
			tokens->add(new Token(Token::Type::SEMI_COLON));
			advance();
		}
		else if (mCurrentChar == '=') {
			tokens->add(new Token(Token::Type::EQUALS));
			advance();
		}
		else if (mCurrentChar >= '0' && mCurrentChar <= '9') {
			tokens->add(makeNumber());
		}
		else if ((mCurrentChar >= 'a' && mCurrentChar <= 'z') ||
			(mCurrentChar >= 'A' && mCurrentChar <= 'Z') || mCurrentChar == '_') {
			tokens->add(makeIdentifier());
		}
	}
	return tokens;
}

Token* Lexer::makeNumber() {
	String* number = new String(2);
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
	if (id->compare("int")) {
		return new Token(Token::Type::KEYWORD_INT);
		delete id;
	}
	return new Token(id, Token::Type::IDENTIFIER);
}