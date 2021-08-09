#pragma once

#include "../values/value.h"
#include "../values/object.h"
#include "node.h"
#include "symbol_table.h"
#include "list/list.cpp"
#include "context.h"

class Interpreter {
public:
	Value* visit(Node* node, SymbolsRuntime* symbols);
	~Interpreter();

private:

	List<Value*>* mSymbols = new List<Value*>();

	Value* visitInteger(IntegerNode* node, SymbolsRuntime* symbols);
	Value* visitFloat(FloatNode* node, SymbolsRuntime* symbols);
	Value* visitString(StringNode* node, SymbolsRuntime* symbols);
	Value* visitBinary(BinaryNode* node, SymbolsRuntime* symbols);
	Value* visitUnary(UnaryNode* node, SymbolsRuntime* symbols);
	Value* visitVarAccess(VarAccess* node, SymbolsRuntime* symbols);
	Value* visitVarAssign(VarAssign* node, SymbolsRuntime* symbols, SymbolsRuntime* baseSymbols = nullptr);
	Value* visitBlock(Block* node, SymbolsRuntime* symbols);
	Value* visitFor(ForLoop* node, SymbolsRuntime* symbols);
	Value* visitMethod(Method* node, SymbolsRuntime* symbols);
	Value* visitCall(Call* node, SymbolsRuntime* symbols, SymbolsRuntime* baseSymbols = nullptr);
	Value* vistiReturn(Return* node, SymbolsRuntime* symbols);
	Value* visitIf(If* node, SymbolsRuntime* symbols);
	Value* visitList(ListNode* node, SymbolsRuntime* symbols);
	Value* visitSubscriptAccess(SubscriptAccessNode* node, SymbolsRuntime* symbols);
	Value* visitSubscriptAssign(SubscriptAssignNode* node, SymbolsRuntime* symbols);
	Value* visitClass(ClassNode* node, SymbolsRuntime* symbols);
	Value* visitAttribute(AttributeNode* node, SymbolsRuntime* symbols);
	Value* visitTuple(TupleNode* node, SymbolsRuntime* symbols);
};