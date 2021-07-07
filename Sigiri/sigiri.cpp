#include "include/sigiri.h"


Value* Interpreter::visit(Node* node) {
	if (node->mType == Node::Type::INTEGER)
		return visitInteger((IntegerNode*)node);
	else if (node->mType == Node::Type::BINARY)
		return visitBinary((BinaryNode*)node);
}

Value* Interpreter::visitInteger(IntegerNode* node) {
	return new IntegerValue(node->mValue);
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
	default:
		break;
	}

	return nullptr;
}