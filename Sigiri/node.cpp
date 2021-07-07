#include "include/node.h"
#include <cstdio>

Node::Node(Type type) {
	mType = type;
}

void Node::toString() {

}

IntegerNode::IntegerNode(int value) : Node(Type::INTEGER) {
	mValue = value;
}

void IntegerNode::toString() {
	printf("%d", mValue);
}

FloatNode::FloatNode(double value) : Node(Type::FLOAT) {
	mValue = value;
}

void FloatNode::toString() {
	printf("%f", mValue);
}

BinaryNode::BinaryNode(Node* left, Token::Type type, Node* right) : Node(Type::BINARY) {
	mLeft = left;
	mOpType = type;
	mRight = right;
}

void BinaryNode::toString() {
	printf("(");
	mLeft->toString();
	
	if (mOpType == Token::Type::PLUS)
		printf("+");
	else if (mOpType == Token::Type::MINUS)
		printf("-");
	else if (mOpType == Token::Type::ASTERIX)
		printf("*");
	else if (mOpType == Token::Type::FW_SLASH)
		printf("/");


	mRight->toString();
	printf(")");
}

BinaryNode::~BinaryNode() {
	delete mLeft;
	delete mRight;
}