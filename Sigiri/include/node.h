#pragma once

#include "token.h"

class Node {
public:
	enum class Type
	{
		INTEGER,
		FLOAT,
		UNARY,
		BINARY
	} mType;
	Node(Type type);
	virtual void toString();
};

class IntegerNode : public Node {
public:
	IntegerNode(int value);
	void toString();
	int mValue;
};

class FloatNode : public Node {
public:
	FloatNode(double value);
	void toString();
	double mValue;
};

class UnaryNode : public Node {
public:
	~UnaryNode();
	UnaryNode(Token::Type type, Node* node);
	Node* mNode;
	Token::Type mOpType;
	void toString();
};

class BinaryNode : public Node {
public:
	~BinaryNode();
	BinaryNode(Node* left, Token::Type type, Node* right);
	Node* mLeft, * mRight;
	Token::Type mOpType;
	void toString();
};
