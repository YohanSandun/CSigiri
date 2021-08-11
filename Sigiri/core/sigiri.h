#pragma once

#include "../values/value.h"
#include "../values/object.h"
#include "node.h"
#include "symbol_table.h"
#include "list/list.cpp"
#include "context.h"

class Interpreter {
public:
	Value* visit(Node* node, Context* context);
	~Interpreter();

private:

	List<Value*>* mSymbols = new List<Value*>();

	Value* visitInteger(IntegerNode* node, Context* context);
	Value* visitFloat(FloatNode* node, Context* context);
	Value* visitString(StringNode* node, Context* context);
	Value* visitBinary(BinaryNode* node, Context* context);
	Value* visitUnary(UnaryNode* node, Context* context);
	Value* visitVarAccess(VarAccess* node, Context* context);
	Value* visitVarAssign(VarAssign* node, Context* context, Context* baseSymbols = nullptr);
	Value* visitBlock(Block* node, Context* context);
	Value* visitFor(ForLoop* node, Context* context);
	Value* visitMethod(Method* node, Context* context);
	Value* visitCall(Call* node, Context* context, Context* baseSymbols = nullptr);
	Value* vistiReturn(Return* node, Context* context);
	Value* visitIf(If* node, Context* context);
	Value* visitList(ListNode* node, Context* context);
	Value* visitSubscriptAccess(SubscriptAccessNode* node, Context* context);
	Value* visitSubscriptAssign(SubscriptAssignNode* node, Context* context);
	Value* visitClass(ClassNode* node, Context* context);
	Value* visitAttribute(AttributeNode* node, Context* context);
	Value* visitTuple(TupleNode* node, Context* context);
};