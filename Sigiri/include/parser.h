#pragma once

#include "../libs/list.cpp"
#include "token.h"
#include "node.h"

class Parser {
private:
	List<Token*>* mTokens;
	void advance();
	int mIndex = -1;
	Token* currentToken;

	Node* expr();
	Node* term();
	Node* power();
	Node* factor();
	Node* atom();

public:
	Parser(List<Token*>* tokens);
	~Parser();
	Node* parse();
};