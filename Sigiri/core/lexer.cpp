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
			tokens->Add(new Token(Token::Type::kNewLine));
			advance();
		}
		else if (mCurrentChar == '+') {
			tokens->Add(new Token(Token::Type::kPlus));
			advance();
		}
		else if (mCurrentChar == '-') {
			tokens->Add(new Token(Token::Type::kMinus));
			advance();
		}
		else if (mCurrentChar == '*') {
			if (peek(1) == '*') {
				tokens->Add(new Token(Token::Type::kPower));
				advance();
				advance();
			}
			else {
				tokens->Add(new Token(Token::Type::kAsterix));
				advance();
			}
		}
		else if (mCurrentChar == '/') {
			tokens->Add(new Token(Token::Type::kFowardSlash));
			advance();
		}
		else if (mCurrentChar == '%') {
			tokens->Add(new Token(Token::Type::kPrecentage));
			advance();
		}
		else if (mCurrentChar == '(') {
			tokens->Add(new Token(Token::Type::kLeftParen));
			advance();
		}
		else if (mCurrentChar == ')') {
			tokens->Add(new Token(Token::Type::kRightParen));
			advance();
		}
		else if (mCurrentChar == '{') {
			tokens->Add(new Token(Token::Type::kLeftBrace));
			advance();
		}
		else if (mCurrentChar == '}') {
			tokens->Add(new Token(Token::Type::kRightBrace));
			advance();
		}
		else if (mCurrentChar == '[') {
			tokens->Add(new Token(Token::Type::kLeftSqare));
			advance();
		}
		else if (mCurrentChar == ']') {
			tokens->Add(new Token(Token::Type::kRightSquare));
			advance();
		}
		else if (mCurrentChar == ':') {
			tokens->Add(new Token(Token::Type::kColon));
			advance();
		}
		else if (mCurrentChar == ';') {
			tokens->Add(new Token(Token::Type::kNewLine));
			advance();
		}
		else if (mCurrentChar == '^') {
			tokens->Add(new Token(Token::Type::kBitwiseXor));
			advance();
		}
		else if (mCurrentChar == '~') {
			tokens->Add(new Token(Token::Type::kBitwiseComplement));
			advance();
		}
		else if (mCurrentChar == ',') {
			tokens->Add(new Token(Token::Type::kComma));
			advance();
		}
		else if (mCurrentChar == '.') {
			tokens->Add(new Token(Token::Type::kDot));
			advance();
		}
		else if (mCurrentChar == '=') {
			if (peek(1) == '=') {
				tokens->Add(new Token(Token::Type::kEqualsEquals));
				advance();
				advance();
			} else {
				tokens->Add(new Token(Token::Type::kEquals));
				advance();
			}
		}
		else if (mCurrentChar == '<') {
			if (peek(1) == '=') {
				tokens->Add(new Token(Token::Type::kLessEquals));
				advance();
				advance();
			}
			else if (peek(1) == '<') {
				tokens->Add(new Token(Token::Type::kLeftShift));
				advance();
				advance();
			}
			else {
				tokens->Add(new Token(Token::Type::kLessThan));
				advance();
			}
		}
		else if (mCurrentChar == '>') {
			if (peek(1) == '=') {
				tokens->Add(new Token(Token::Type::kGreaterEquals));
				advance();
				advance();
			}
			else if (peek(1) == '>') {
				tokens->Add(new Token(Token::Type::kRightShift));
				advance();
				advance();
			}
			else {
				tokens->Add(new Token(Token::Type::kGreaterThan));
				advance();
			}
		}
		else if (mCurrentChar == '!') {
			if (peek(1) == '=') {
				tokens->Add(new Token(Token::Type::kNotEquals));
				advance();
				advance();
			}
			else {
				tokens->Add(new Token(Token::Type::kBooleanNot));
				advance();
			}
		}
		else if (mCurrentChar == '&') {
			if (peek(1) == '&') {
				tokens->Add(new Token(Token::Type::kBooleanAnd));
				advance();
				advance();
			}
			else {
				tokens->Add(new Token(Token::Type::kBitwiseAnd));
				advance();
			}
		}
		else if (mCurrentChar == '|') {
			if (peek(1) == '|') {
				tokens->Add(new Token(Token::Type::kBooleanOr));
				advance();
				advance();
			}
			else {
				tokens->Add(new Token(Token::Type::kBitwiseOr));
				advance();
			}
		}
		else if (mCurrentChar >= '0' && mCurrentChar <= '9') {
			tokens->Add(makeNumber());
		}
		else if (mCurrentChar == '"') {
			tokens->Add(makeString());
		}
		else if ((mCurrentChar >= 'a' && mCurrentChar <= 'z') ||
			(mCurrentChar >= 'A' && mCurrentChar <= 'Z') || mCurrentChar == '_') {
			tokens->Add(makeIdentifier());
		}
	}
	tokens->Add(new Token(Token::Type::kEof));
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
	return new Token(str, Token::Type::kString);
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
		return new Token(number, Token::Type::kIntNumber);
	else
		return new Token(number, Token::Type::kFloatNumber);
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
		return new Token(Token::Type::kKeywordVar);
	}
	else if (id->Compare("int")) {
		delete id;
		return new Token(Token::Type::kKeywordInt);
	}
	else if (id->Compare("for")) {
		delete id;
		return new Token(Token::Type::kKeywordFor);
	}
	else if (id->Compare("to")) {
		delete id;
		return new Token(Token::Type::kKeywordTo);
	}
	else if (id->Compare("step")) {
		delete id;
		return new Token(Token::Type::kKeywordStep);
	}
	else if (id->Compare("method")) {
		delete id;
		return new Token(Token::Type::kKeywordMethod);
	}
	else if (id->Compare("return")) {
		delete id;
		return new Token(Token::Type::kKeywordReturn);
	}
	else if (id->Compare("break")) {
		delete id;
		return new Token(Token::Type::kKeywordBreak);
	}
	else if (id->Compare("continue")) {
		delete id;
		return new Token(Token::Type::kKeywordContinue);
	}
	else if (id->Compare("if")) {
		delete id;
		return new Token(Token::Type::kKeywordIf);
	}
	else if (id->Compare("elif")) {
		delete id;
		return new Token(Token::Type::kKeywordElif);
	}
	else if (id->Compare("else")) {
		delete id;
		return new Token(Token::Type::kKeywordElse);
	}
	else if (id->Compare("class")) {
		delete id;
		return new Token(Token::Type::kKeywordClass);
	}
	return new Token(id, Token::Type::kIdentifier);
}