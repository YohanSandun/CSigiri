#pragma once

#include "../libs/list.cpp"
#include "token.h"
#include "node.h"

class Parser {
private:
	List<Token*>* mTokens = nullptr;
	List<String*>* mSymbols;
	void advance();
	int mIndex = -1;
	Token* currentToken;

	int getSymbolIndex(String* name);

	Node* expr();
	Node* term();
	Node* power();
	Node* factor();
	Node* atom();

public:
	Parser();
	void setTokens(List<Token*>* tokens);
	~Parser();
	Node* parse();
};