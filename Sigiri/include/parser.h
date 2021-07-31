#pragma once

#include "token.h"
#include "node.h"
#include "symbol_table.h"

class Parser {
private:
	List<Token*>* mTokens = nullptr;
	void advance();
	int mIndex = -1;
	Token* currentToken;

	Node* block(SymbolsParser* symbols, Token::Type end = Token::Type::R_BRACE);
	Node* expr(SymbolsParser* symbols);
	Node* compare(SymbolsParser* symbols);
	Node* bitwise_or(SymbolsParser* symbols);
	Node* bitwise_xor(SymbolsParser* symbols);
	Node* bitwise_and(SymbolsParser* symbols);
	Node* shift(SymbolsParser* symbols);
	Node* arithmetic(SymbolsParser* symbols);
	Node* term(SymbolsParser* symbols);
	Node* power(SymbolsParser* symbols);
	Node* factor(SymbolsParser* symbols);
	Node* complement(SymbolsParser* symbols);
	Node* call(SymbolsParser* symbols);
	Node* atom(SymbolsParser* symbols);

	Node* for_expr(SymbolsParser* symbols);
	Node* method_expr(SymbolsParser* symbols);
	Node* return_expr(SymbolsParser* symbols);
	Node* if_expr(SymbolsParser* symbols);
	Node* list_expr(SymbolsParser* symbols);

	Node* subscript(Node* base, SymbolsParser* symbols);

	void skipNewLines();

public:
	//List<String*>* mSymbols;
	String* mError = nullptr;
	Parser();
	~Parser();
	void setTokens(List<Token*>* tokens);
	Node* parse(SymbolsParser* symbols);
};