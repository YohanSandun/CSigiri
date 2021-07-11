#pragma once

#include "value.h"
#include "node.h"
#include "../libs/list.cpp"

class Interpreter {
public:
	Value* visit(Node* node);
	~Interpreter();

private:

	List<Value*>* mSymbols = new List<Value*>();

	Value* visitInteger(IntegerNode* node);
	Value* visitBinary(BinaryNode* node);
	Value* visitUnary(UnaryNode* node);
	Value* visitVarAccess(VarAccess* node);
	Value* visitVarAssign(VarAssign* node);
};