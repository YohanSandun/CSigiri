#include "lexer.h"

Lexer::Lexer(String* code) {
	mCode = code;
	mCodeLen = code->length;
	advance();
}

Lexer::~Lexer() {
	delete mCode;
}

void Lexer::advance() {
	mIndex++;
	if (mIndex < mCodeLen)
		mCurrentChar = mCode->ptr[mIndex];
	else
		mCurrentChar = '\0';
}

char Lexer::peek(int amount) {
	if (mIndex + amount < mCodeLen)
		return mCode->ptr[mIndex + amount];
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
			tokens->add(new Token(Token::Type::MODULUS));
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
		else if (mCurrentChar == '[') {
			tokens->add(new Token(Token::Type::L_SQ));
			advance();
		}
		else if (mCurrentChar == ']') {
			tokens->add(new Token(Token::Type::R_SQ));
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
		else if (mCurrentChar == '.') {
			tokens->add(new Token(Token::Type::DOT));
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
				str->Append('\n');
			else if (mCurrentChar == 't')
				str->Append('\t');
			else if (mCurrentChar == 'b')
				str->Append('\b');
			else
				str->Append(mCurrentChar);
			advance();
			continue;
		}
		if (mCurrentChar == '\"') {
			advance();
			break;
		}
		str->Append(mCurrentChar);
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
		number->Append(mCurrentChar);
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
		id->Append(mCurrentChar);
		advance();
	}

	if (id->Compare("var")) {
		delete id;
		return new Token(Token::Type::KEYWORD_VAR);
	}
	else if (id->Compare("int")) {
		delete id;
		return new Token(Token::Type::KEYWORD_INT);
	}
	else if (id->Compare("for")) {
		delete id;
		return new Token(Token::Type::KEYWORD_FOR);
	}
	else if (id->Compare("to")) {
		delete id;
		return new Token(Token::Type::KEYWORD_TO);
	}
	else if (id->Compare("step")) {
		delete id;
		return new Token(Token::Type::KEYWORD_STEP);
	}
	else if (id->Compare("method")) {
		delete id;
		return new Token(Token::Type::KEYWORD_METHOD);
	}
	else if (id->Compare("return")) {
		delete id;
		return new Token(Token::Type::KEYWORD_RETURN);
	}
	else if (id->Compare("break")) {
		delete id;
		return new Token(Token::Type::KEYWORD_BREAK);
	}
	else if (id->Compare("continue")) {
		delete id;
		return new Token(Token::Type::KEYWORD_CONTINUE);
	}
	else if (id->Compare("if")) {
		delete id;
		return new Token(Token::Type::KEYWORD_IF);
	}
	else if (id->Compare("elif")) {
		delete id;
		return new Token(Token::Type::KEYWORD_ELIF);
	}
	else if (id->Compare("else")) {
		delete id;
		return new Token(Token::Type::KEYWORD_ELSE);
	}
	else if (id->Compare("class")) {
		delete id;
		return new Token(Token::Type::KEYWORD_CLASS);
	}
	return new Token(id, Token::Type::IDENTIFIER);
}