#pragma once

#include "value.h"
#include "node.h"
#include "symbol_table.h"
#include "../libs/list.cpp"
#include "context.h"

class Interpreter {
public:
	Value* visit(Node* node, SymbolsRuntime* symbols);
	~Interpreter();

private:

	List<Value*>* mSymbols = new List<Value*>();

	Value* visitInteger(IntegerNode* node, SymbolsRuntime* symbols);
	Value* visitBinary(BinaryNode* node, SymbolsRuntime* symbols);
	Value* visitUnary(UnaryNode* node, SymbolsRuntime* symbols);
	Value* visitVarAccess(VarAccess* node, SymbolsRuntime* symbols);
	Value* visitVarAssign(VarAssign* node, SymbolsRuntime* symbols);
	Value* visitBlock(Block* node, SymbolsRuntime* symbols);
	Value* visitFor(ForLoop* node, SymbolsRuntime* symbols);
	Value* visitMethod(Method* node, SymbolsRuntime* symbols);
	Value* visitCall(Call* node, SymbolsRuntime* symbols);
	Value* vistiReturn(Return* node, SymbolsRuntime* symbols);
	Value* visitIf(If* node, SymbolsRuntime* symbols);
};