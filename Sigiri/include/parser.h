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

	Node* block(Token::Type end = Token::Type::R_BRACE);
	Node* expr();
	Node* compare();
	Node* bitwise_or();
	Node* bitwise_xor();
	Node* bitwise_and();
	Node* shift();
	Node* arithmetic();
	Node* term();
	Node* power();
	Node* factor();
	Node* complement();
	Node* atom();
	
	void skipNewLines();

public:
	Parser();
	void setTokens(List<Token*>* tokens);
	~Parser();
	Node* parse();
};