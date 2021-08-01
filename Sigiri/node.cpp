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

//-------------------------------------------------------------------------------------------------------------

FloatNode::FloatNode(double value) : Node(Type::FLOAT) {
	mValue = value;
}

FloatNode::~FloatNode() {
	
}

void FloatNode::toString() {
	printf("%f", mValue);
}

//-------------------------------------------------------------------------------------------------------------


StringNode::StringNode(String* value) : Node(Type::STRING) {
	mValue = value;
}

StringNode::~StringNode() {
	delete mValue;
}

void StringNode::toString() {
	printf("%s", mValue->mPtr);
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

VarAssign::VarAssign(String* id, Node* node) : Node(Type::VAR_ASSIGN) {
	mId = id;
	mNode = node;
}

VarAssign::~VarAssign() {
	delete mId;
	delete mNode;
}

void VarAssign::toString() {
	printf("%d=", mId);
	mNode->toString();
}

//-------------------------------------------------------------------------------------------------------------

VarAccess::VarAccess(String* id) : Node(Type::VAR_ACCESS) {
	mId = id;
}

VarAccess::~VarAccess() {
	delete mId;
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

//-------------------------------------------------------------------------------------------------------------

ForLoop::ForLoop(String* id, Node* start, Node* to, Node* step, Node* body) : Node(Type::FOR_LOOP) {
	mId = id;
	mStart = start;
	mTo = to;
	mStep = step;
	mBody = body;
}

ForLoop::~ForLoop() {
	delete mStart;
	delete mTo;
	if (mStep != nullptr)
		delete mStep;
	delete mBody;
}

//-------------------------------------------------------------------------------------------------------------

Method::Method(String* id, Node* body, List<String*>* params) : Node(Type::METHOD) {
	mId = id;
	mParams = params;
	mBody = body;
}

Method::~Method() {
	delete mId;
	delete mParams;
	delete mBody;
}

//-------------------------------------------------------------------------------------------------------------


Call::Call(Node* base, List<Node*>* args) : Node(Type::CALL) {
	mBase = base;
	mArgs = args;
}

Call::~Call() {
	delete mBase;
	delete mArgs;
}

//-------------------------------------------------------------------------------------------------------------

Return::Return(Node* node) : Node(Type::RETURN) {
	mNode = node;
}

Return::~Return() {
	delete mNode;
}

//-------------------------------------------------------------------------------------------------------------

IfCase::IfCase(Node* condition, Node* body) {
	mCondition = condition;
	mBody = body;
}

IfCase::~IfCase() {
	delete mCondition;
	delete mBody;
}

If::If(List<IfCase*>* cases, Node* elseCase) : Node(Type::IF) {
	mCases = cases;
	mElseCase = elseCase;
}

If::~If() {
	delete mCases;
	delete mElseCase;
}

//-------------------------------------------------------------------------------------------------------------

ListNode::ListNode(List<Node*>* items) : Node(Type::LIST) {
	mItems = items;
}

ListNode::~ListNode() {
	delete mItems;
}

//-------------------------------------------------------------------------------------------------------------

SubscriptAccessNode::SubscriptAccessNode(Node* base, Node* node) : Node(Type::SUBSCRIPT_ACCESS) {
	mBase = base;
	mNode = node;
}

SubscriptAccessNode::~SubscriptAccessNode() {
	delete mBase;
	delete mNode;
}

//-------------------------------------------------------------------------------------------------------------

SubscriptAssignNode::SubscriptAssignNode(Node* base, Node* node) : Node(Type::SUBSCRIPT_ASSIGN) {
	mNode = node;
	mBase = base;
}

SubscriptAssignNode::~SubscriptAssignNode() {
	delete mNode;
	delete mBase;
}

//-------------------------------------------------------------------------------------------------------------

ClassNode::ClassNode(String* id, Node* body) : Node(Type::CLASS) {
	mId = id;
	mBody = body;
}

ClassNode::~ClassNode() {
	delete mId;
	delete mBody;
}

//-------------------------------------------------------------------------------------------------------------

AttributeNode::AttributeNode(Node* base, Node* node) : Node(Type::ATTRIBUTE) {
	mBase = base;
	mNode = node;
}

AttributeNode::~AttributeNode() {
	delete mBase;
	delete mNode;
}