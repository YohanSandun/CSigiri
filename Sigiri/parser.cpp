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
	delete mTokens;
	delete mSymbols;
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

void Parser::skipNewLines() {
	while (currentToken->mType == Token::Type::NEWLINE)
		advance();
}

Node* Parser::parse() {
	return block(Token::Type::EOF_TOKEN);
}

Node* Parser::block(Token::Type end) {
	List<Node*>* statements = new List<Node*>();
	while (true) {
		skipNewLines();
		if (currentToken->mType == end)
			break;
		statements->add(expr());
	}
	return new Block(statements);
}

Node* Parser::expr() {
	Node* left = compare();
	while (currentToken->mType == Token::Type::BOOLEAN_AND || currentToken->mType == Token::Type::BOOLEAN_OR)
	{
		Token::Type type = currentToken->mType;
		advance();
		Node* right = compare();
		left = new BinaryNode(left, type, right);
	}
	return left;
}

Node* Parser::compare() {
	if (currentToken->mType == Token::Type::BOOLEAN_NOT) {
		advance();
		return new UnaryNode(Token::Type::BOOLEAN_NOT, compare());
	}
	Node* left = bitwise_or();
	while (currentToken->mType == Token::Type::EQUALS_EQUALS || currentToken->mType == Token::Type::NOT_EQUALS ||
		currentToken->mType == Token::Type::GREATER_THAN || currentToken->mType == Token::Type::LESS_THAN ||
		currentToken->mType == Token::Type::GREATER_EQ || currentToken->mType == Token::Type::LESS_EQ) {
		Token::Type type = currentToken->mType;
		advance();
		Node* right = bitwise_or();
		left = new BinaryNode(left, type, right);
	}
	return left;
}

Node* Parser::bitwise_or() {
	Node* left = bitwise_xor();
	while (currentToken->mType == Token::Type::BITWISE_OR)
	{
		advance();
		Node* right = bitwise_xor();
		left = new BinaryNode(left, Token::Type::BITWISE_OR, right);
	}
	return left;
}

Node* Parser::bitwise_xor() {
	Node* left = bitwise_and();
	while (currentToken->mType == Token::Type::BITWISE_XOR)
	{
		advance();
		Node* right = bitwise_and();
		left = new BinaryNode(left, Token::Type::BITWISE_XOR, right);
	}
	return left;
}

Node* Parser::bitwise_and() {
	Node* left = shift();
	while (currentToken->mType == Token::Type::BITWISE_AND)
	{
		advance();
		Node* right = shift();
		left = new BinaryNode(left, Token::Type::BITWISE_AND, right);
	}
	return left;
}

Node* Parser::shift() {
	Node* left = arithmetic();
	while (currentToken->mType == Token::Type::LEFT_SHIFT || currentToken->mType == Token::Type::RIGHT_SHIFT)
	{
		Token::Type type = currentToken->mType;
		advance();
		Node* right = arithmetic(); 
		left = new BinaryNode(left, type, right);
	}
	return left;
}

Node* Parser::arithmetic() {
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
	Node* left = complement();
	while (currentToken->mType == Token::Type::POWER)
	{
		advance();
		Node* right = factor();
		left = new BinaryNode(left, Token::Type::POWER, right);
	}
	return left;
}

Node* Parser::complement() {
	if (currentToken->mType == Token::Type::BITWISE_COMPLEMENT) {
		advance();
		Node* node = factor();
		return new UnaryNode(Token::Type::BITWISE_COMPLEMENT, node);
	}
	return atom();
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