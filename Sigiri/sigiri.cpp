#include "include/sigiri.h"

Interpreter::~Interpreter() {
	//delete mSymbols;
}

Value* Interpreter::visit(Node* node) {
	if (node->mType == Node::Type::INTEGER)
		return visitInteger((IntegerNode*)node);
	else if (node->mType == Node::Type::BINARY)
		return visitBinary((BinaryNode*)node);
	else if (node->mType == Node::Type::UNARY)
		return visitUnary((UnaryNode*)node);
	else if (node->mType == Node::Type::VAR_ACCESS)
		return visitVarAccess((VarAccess*)node);
	else if (node->mType == Node::Type::VAR_ASSIGN)
		return visitVarAssign((VarAssign*)node);
	else if (node->mType == Node::Type::BLOCK)
		return visitBlock((Block*)node);
}

Value* Interpreter::visitInteger(IntegerNode* node) {
	Value* value = new IntegerValue(node->mValue);
	return value;
}

Value* Interpreter::visitBinary(BinaryNode* node) {
	Value* left = visit(node->mLeft);
	Value* right = visit(node->mRight);

	switch (node->mOpType)
	{
	case Token::Type::PLUS:
		return left->add(right);
	case Token::Type::MINUS:
		return left->sub(right);
	case Token::Type::ASTERIX:
		return left->mul(right);
	case Token::Type::FW_SLASH:
		return left->div(right);
	case Token::Type::POWER:
		return left->s_pow(right);
	default:
		break;
	}
	return nullptr;
}

Value* Interpreter::visitUnary(UnaryNode* node) {
	Value* value = visit(node->mNode);
	if (node->mOpType == Token::Type::MINUS) {
		return value->negate();
	}
	return value;
}

Value* Interpreter::visitVarAccess(VarAccess* node) {
	if (mSymbols->getCount() > node->mId) 
		return mSymbols->get(node->mId)->clone();
}

Value* Interpreter::visitVarAssign(VarAssign* node) {
	Value* value = visit(node->mNode);
	if (mSymbols->getCount() > node->mId)
	{
		delete mSymbols->get(node->mId);
		mSymbols->mPtr[node->mId] = value;
	}
	else 
		mSymbols->add(value);
	return value;
}

Value* Interpreter::visitBlock(Block* node) {
	int count = node->mStatements->getCount();
	for (size_t i = 0; i < count; i++)
	{
		if (i == count-1)
			return visit(node->mStatements->get(i));
		visit(node->mStatements->get(i));
	}
	return nullptr;
}