#include "include/sigiri.h"

Interpreter::~Interpreter() {
	//delete mSymbols;
}

Value* Interpreter::visit(Node* node, SymbolsRuntime* symbols) {
	if (node->mType == Node::Type::INTEGER)
		return visitInteger((IntegerNode*)node, symbols);
	else if (node->mType == Node::Type::BINARY)
		return visitBinary((BinaryNode*)node, symbols);
	else if (node->mType == Node::Type::UNARY)
		return visitUnary((UnaryNode*)node, symbols);
	else if (node->mType == Node::Type::VAR_ACCESS)
		return visitVarAccess((VarAccess*)node, symbols);
	else if (node->mType == Node::Type::VAR_ASSIGN)
		return visitVarAssign((VarAssign*)node, symbols);
	else if (node->mType == Node::Type::BLOCK)
		return visitBlock((Block*)node, symbols);
	else if (node->mType == Node::Type::FOR_LOOP)
		return visitFor((ForLoop*)node, symbols);
	else if (node->mType == Node::Type::METHOD)
		return visitMethod((Method*)node, symbols);
	else if (node->mType == Node::Type::CALL)
		return visitCall((Call*)node, symbols);
}

Value* Interpreter::visitInteger(IntegerNode* node, SymbolsRuntime* symbols) {
	Value* value = new IntegerValue(node->mValue);
	return value;
}

Value* Interpreter::visitBinary(BinaryNode* node, SymbolsRuntime* symbols) {
	Value* left = visit(node->mLeft, symbols);
	Value* right = visit(node->mRight, symbols);

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
	case Token::Type::EQUALS_EQUALS:
		return left->comp_eq_eq(right);
	case Token::Type::NOT_EQUALS:
		return left->comp_not_eq(right);
	case Token::Type::LESS_THAN:
		return left->comp_less(right);
	case Token::Type::GREATER_THAN:
		return left->comp_greater(right);
	case Token::Type::LESS_EQ:
		return left->comp_less_eq(right);
	case Token::Type::GREATER_EQ:
		return left->comp_greater_eq(right);
	case Token::Type::BITWISE_AND:
		return left->bitwise_and(right);
	case Token::Type::BITWISE_OR:
		return left->bitwise_or(right);
	case Token::Type::BITWISE_XOR:
		return left->bitwise_xor(right);
	case Token::Type::LEFT_SHIFT:
		return left->shift_left(right);
	case Token::Type::RIGHT_SHIFT:
		return left->shift_right(right);
	case Token::Type::BOOLEAN_AND:
		return left->boolean_and(right);
	case Token::Type::BOOLEAN_OR:
		return left->boolean_or(right);

	default:
		break;
	}
	return nullptr;
}

Value* Interpreter::visitUnary(UnaryNode* node, SymbolsRuntime* symbols) {
	Value* value = visit(node->mNode, symbols);
	if (node->mOpType == Token::Type::MINUS) {
		return value->negate();
	}
	else if (node->mOpType == Token::Type::BOOLEAN_NOT) {
		return value->boolean_not();
	}
	else if (node->mOpType == Token::Type::BITWISE_COMPLEMENT) {
		return value->bitwise_complement();
	}
	return value;
}

Value* Interpreter::visitVarAccess(VarAccess* node, SymbolsRuntime* symbols) {
	return symbols->getSymbol(node->mId)->clone();
}

Value* Interpreter::visitVarAssign(VarAssign* node, SymbolsRuntime* symbols) {
	Value* value = visit(node->mNode, symbols);
	symbols->setSymbol(node->mId, value);
	return value;
}

Value* Interpreter::visitBlock(Block* node, SymbolsRuntime* symbols) {
	int count = node->mStatements->getCount();
	for (size_t i = 0; i < count; i++)
	{
		if (i == count-1)
			return visit(node->mStatements->get(i), symbols);
		visit(node->mStatements->get(i), symbols);
	}
	return nullptr;
}

Value* Interpreter::visitFor(ForLoop* node, SymbolsRuntime* symbols) {
	int start = 0, to = 0;
	Value* v_start = visit(node->mStart, symbols);
	if (v_start->mType == Value::Type::INTEGER)
		start = ((IntegerValue*)v_start)->mValue;
	//else error
	Value* v_to = visit(node->mTo, symbols);
	if (v_to->mType == Value::Type::INTEGER)
		to = ((IntegerValue*)v_to)->mValue;
	Value* v_step = nullptr;

	int step = 1;
	if (node->mStep != nullptr) {
		Value* v_step = visit(node->mStep, symbols);
		if (v_step->mType == Value::Type::INTEGER)
			step = ((IntegerValue*)v_step)->mValue;
		delete v_step;
	}
		
	symbols->setSymbol(node->mId, v_start);

	IntegerValue* v_start_int = (IntegerValue*)v_start;

	if (start < to) {
		while (start < to)
		{
			visit(node->mBody, symbols);
			start += step;
			v_start_int->mValue = start;
		}
	}
	else {
		while (start > to)
		{
			visit(node->mBody, symbols);
			start += step;
			v_start_int->mValue = start;
		}
	}

	delete v_to;

	return nullptr;
}

Value* Interpreter::visitMethod(Method* node, SymbolsRuntime* symbols) {
	MethodValue* value = new MethodValue(node->mId, node->mBody);
	return value;
}

Value* Interpreter::visitCall(Call* node, SymbolsRuntime* symbols) {
	return nullptr;
}