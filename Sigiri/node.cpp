#include "include/node.h"
#include <cstdio>

Node::Node(Type type) {
	mType = type;
}

Node::~Node() {

}

void Node::toString() {

}

//-------------------------------------------------------------------------------------------------------------

IntegerNode::IntegerNode(int value) : Node(Type::INTEGER) {
	mValue = value;
}

IntegerNode::~IntegerNode() {
	
}

void IntegerNode::toString() {
	printf("%d", mValue);
}

FloatNode::FloatNode(double value) : Node(Type::FLOAT) {
	mValue = value;
}

FloatNode::~FloatNode() {
	
}

void FloatNode::toString() {
	printf("%f", mValue);
}

//-------------------------------------------------------------------------------------------------------------

UnaryNode::UnaryNode(Token::Type type, Node* node) : Node(Type::UNARY) {
	mOpType = type;
	mNode = node;
}

UnaryNode::~UnaryNode() {
	delete mNode;
}

void UnaryNode::toString() {
	if (mOpType == Token::Type::PLUS)
		printf("(+");
	else if (mOpType == Token::Type::MINUS)
		printf("(-");
	mNode->toString();
	printf(")");
}

//-------------------------------------------------------------------------------------------------------------

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
	else if (mOpType == Token::Type::POWER)
		printf("**");

	mRight->toString();
	printf(")");
}

BinaryNode::~BinaryNode() {
	delete mLeft;
	delete mRight;
}

//-------------------------------------------------------------------------------------------------------------

VarAssign::VarAssign(int id, Node* node) : Node(Type::VAR_ASSIGN) {
	mId = id;
	mNode = node;
}

VarAssign::~VarAssign() {
	delete mNode;
}

void VarAssign::toString() {
	printf("%d=", mId);
	mNode->toString();
}

//-------------------------------------------------------------------------------------------------------------

VarAccess::VarAccess(int id) : Node(Type::VAR_ACCESS) {
	mId = id;
}

VarAccess::~VarAccess() {
}

void VarAccess::toString() {
	printf("%d", mId);
}

//-------------------------------------------------------------------------------------------------------------

Block::Block(List<Node*>* statements) : Node(Type::BLOCK) {
	this->mStatements = statements;
}

Block::~Block() {
	delete mStatements;
}

void Block::toString() {
	int count = mStatements->getCount();
	printf("{\n");
	for (size_t i = 0; i < count; i++)
	{
		printf("\t");
		mStatements->get(i)->toString();
	}
	printf("}\n");
}