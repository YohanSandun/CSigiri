#pragma once

#include "value.h"
#include "node.h"

class Interpreter {
public:
	Value* visit(Node* node);

private:
	Value* visitInteger(IntegerNode* node);
	Value* visitBinary(BinaryNode* node);
	Value* visitUnary(UnaryNode* node);
};