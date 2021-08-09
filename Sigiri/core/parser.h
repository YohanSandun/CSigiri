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

	Node* block(SymbolsParser* symbols, Token::Type end = Token::Type::kRightBrace);
	Node* expr(SymbolsParser* symbols);
	Node* Compare(SymbolsParser* symbols);
	Node* bitwise_or(SymbolsParser* symbols);
	Node* bitwise_xor(SymbolsParser* symbols);
	Node* bitwise_and(SymbolsParser* symbols);
	Node* shift(SymbolsParser* symbols);
	Node* arithmetic(SymbolsParser* symbols, bool byPassDot);
	Node* term(SymbolsParser* symbols, bool byPassDot);
	Node* power(SymbolsParser* symbols, bool byPassDot);
	Node* factor(SymbolsParser* symbols, bool byPassDot);
	Node* complement(SymbolsParser* symbols, bool byPassDot);
	Node* call(SymbolsParser* symbols, bool byPassDot);
	Node* atom(SymbolsParser* symbols, bool byPassDot);

	Node* for_expr(SymbolsParser* symbols);
	Node* method_expr(SymbolsParser* symbols);
	Node* return_expr(SymbolsParser* symbols);
	Node* if_expr(SymbolsParser* symbols);
	Node* list_expr(SymbolsParser* symbols);

	Node* subscript(Node* base, SymbolsParser* symbols);

	Node* class_expr(SymbolsParser* symbols);
	Node* attribute(Node* base, SymbolsParser* symbols);

	void skipNewLines();

public:
	//List<String*>* mSymbols;
	String* mError = nullptr;
	Parser();
	~Parser();
	void setTokens(List<Token*>* tokens);
	Node* parse(SymbolsParser* symbols);
};