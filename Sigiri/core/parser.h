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

	Node* block(SymbolsParser* context, Token::Type end = Token::Type::kRightBrace);
	Node* expr(SymbolsParser* context);
	Node* Compare(SymbolsParser* context);
	Node* bitwise_or(SymbolsParser* context);
	Node* bitwise_xor(SymbolsParser* context);
	Node* bitwise_and(SymbolsParser* context);
	Node* shift(SymbolsParser* context);
	Node* arithmetic(SymbolsParser* context, bool byPassDot);
	Node* term(SymbolsParser* context, bool byPassDot);
	Node* power(SymbolsParser* context, bool byPassDot);
	Node* factor(SymbolsParser* context, bool byPassDot);
	Node* complement(SymbolsParser* context, bool byPassDot);
	Node* call(SymbolsParser* context, bool byPassDot);
	Node* atom(SymbolsParser* context, bool byPassDot);

	Node* for_expr(SymbolsParser* context);
	Node* method_expr(SymbolsParser* context);
	Node* return_expr(SymbolsParser* context);
	Node* if_expr(SymbolsParser* context);
	Node* list_expr(SymbolsParser* context);

	Node* subscript(Node* base, SymbolsParser* context);

	Node* class_expr(SymbolsParser* context);
	Node* attribute(Node* base, SymbolsParser* context);

	void skipNewLines();

public:
	//List<String*>* mSymbols;
	String* mError = nullptr;
	Parser();
	~Parser();
	void setTokens(List<Token*>* tokens);
	Node* parse(SymbolsParser* context);
};