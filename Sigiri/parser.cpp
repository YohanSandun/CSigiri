#include "include/parser.h"
#include "include/string.h"
#include <cstdio>

Parser::Parser() {
	mSymbols = new List<String*>();
}

void Parser::setTokens(List<Token*>* tokens) {
	mIndex = -1;
	if (mTokens != nullptr)
		delete mTokens;
	mTokens = tokens;
	advance();
}

Parser::~Parser() {
	//delete mTokens;
	//delete mSymbols;
}

int Parser::getSymbolIndex(String* name) {
	int count = mSymbols->getCount();
	for (size_t i = 0; i < count; i++)
	{
		if (mSymbols->get(i)->compare(name) == 1)
			return i;
	}
	mSymbols->add(name->clone());
	return count;
}

void Parser::advance() {
	mIndex++;
	if (mIndex < mTokens->getCount())
		currentToken = mTokens->get(mIndex);
}

Node* Parser::parse() {
	return expr();
}

Node* Parser::expr() {
	Node* left = term();
	while (currentToken->mType == Token::Type::PLUS || currentToken->mType == Token::Type::MINUS)
	{
		Token::Type type = currentToken->mType;
		advance();
		Node* right = term();
		left = new BinaryNode(left, type, right);
	}
	return left;
}

Node* Parser::term() {
	Node* left = factor();
	while (currentToken->mType == Token::Type::ASTERIX || currentToken->mType == Token::Type::FW_SLASH)
	{
		Token::Type type = currentToken->mType;
		advance();
		Node* right = factor();
		left = new BinaryNode(left, type, right);
	}
	return left;
}

Node* Parser::factor() {
	Token* token = currentToken;
	if (token->mType == Token::Type::PLUS || token->mType == Token::Type::MINUS) {
		advance();
		Node* node = factor();
		return new UnaryNode(token->mType, node);
	}
	return power();
}

Node* Parser::power() {
	Node* left = atom();
	while (currentToken->mType == Token::Type::POWER)
	{
		advance();
		Node* right = factor();
		left = new BinaryNode(left, Token::Type::POWER, right);
	}
	return left;
}

Node* Parser::atom() {
	Token* token = currentToken;
	if (token->mType == Token::Type::INT_NUMBER) {
		advance();
		return new IntegerNode(strToInt(token->mValue));
	}
	else if (token->mType == Token::Type::FLOAT_NUMBER) {
		advance();
		return new FloatNode(strToFloat(token->mValue));
	}
	else if (token->mType == Token::Type::IDENTIFIER) {
		advance();
		if (currentToken->mType == Token::Type::EQUALS) {
			advance();
			Node* expression = expr();
			return new VarAssign(getSymbolIndex(token->mValue), expression);
		}
		return new VarAccess(getSymbolIndex(token->mValue));
	}
	else if (token->mType == Token::Type::L_PAREN) {
		advance();
		Node* expression = expr();
		if (currentToken->mType != Token::Type::R_PAREN)
			return nullptr;
		advance();
		return expression;
	}
}