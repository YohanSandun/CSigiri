//--------------------------------------------------------------------------
// Copyright 2021 Yohan Sandun
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//--------------------------------------------------------------------------

#include "interpreter.h"

#define ERROR error_ != nullptr

void Interpreter::SetError(const char* error, U_INT32 line, U_INT32 column_start, U_INT32 column_end) {
	error_ = new String(UTF_8 error);
	error_line = line;
	error_column_start = column_start;
	error_column_end = column_end;
}

void Interpreter::PrintError() {
	printf("Rutime Error: %s\n\t", error_->ptr_);
	printf("near line %d column %d to %d\n", error_line, error_column_start, error_column_end);
}

void Interpreter::ClearError() {
	delete error_;
	error_ = nullptr;
	error_line = 0;
	error_column_start = 0;
	error_column_end = 0;
}

Value* Interpreter::Visit(Node* node, Context* context) {
	if (node->type == Node::Type::kBlock)
		return VisitBlockNode((BlockNode*)node, context);
	else if (node->type == Node::Type::kLiteral)
		return VisitLiteralNode((LiteralNode*)node, context);
	else if (node->type == Node::Type::kBinary)
		return VisitBinaryNode((BinaryNode*)node, context);
	else if (node->type == Node::Type::kUnary)
		return VisitUnaryNode((UnaryNode*)node, context);
	else if (node->type == Node::Type::kAssign)
		return VisitAssignNode((AssignNode*)node, context);
	else if (node->type == Node::Type::kVarAccess)
		return VisitVarAccessNode((VarAccessNode*)node, context);
	else if (node->type == Node::Type::kIfStatement)
		return VisitIfNode((IfNode*)node, context);
	else if (node->type == Node::Type::kMethod)
		return VisitMethodNode((MethodNode*)node, context);
	else if (node->type == Node::Type::kCall)
		return VisitCallNode((CallNode*)node, context);

	return nullptr;
}

Value* Interpreter::VisitBlockNode(BlockNode* node, Context* context) {
	U_INT32 statement_count = node->nodes->count();
	for (size_t i = 0; i < statement_count; i++)
	{
		if (i+1 == statement_count)
			return Visit(node->nodes->Get(i), context);
		Visit(node->nodes->Get(i), context);
		if (ERROR)
			return nullptr;
	}
}

Value* Interpreter::VisitLiteralNode(LiteralNode* node, Context* context) {
	if (node->literal_type == LiteralNode::LiteralType::kInteger)
		return new IntegerValue(node->value.int_value, node->line, node->column_start, node->column_end);
}

Value* Interpreter::VisitBinaryNode(BinaryNode* node, Context* context) {
	Value* left = Visit(node->left, context);
	if (ERROR)
		return nullptr;

	Value* right = Visit(node->right, context);
	if (ERROR)
		return nullptr;

	switch (node->operator_type)
	{
	case BinaryNode::OperatorType::kAddition:
		return left->Add(right);
	case BinaryNode::OperatorType::kSubtraction:
		return left->Subtract(right);
	case BinaryNode::OperatorType::kMultiplication:
		return left->Multiply(right);
	case BinaryNode::OperatorType::kDivision:
		return left->Divide(right);
	case BinaryNode::OperatorType::kModulus:
		return left->Mod(right);
	case BinaryNode::OperatorType::kPower:
		return left->Power(right);

	case BinaryNode::OperatorType::kEqualsEquals:
		return left->Equals(right);
	case BinaryNode::OperatorType::kNotEquals:
		return left->NotEquals(right);
	case BinaryNode::OperatorType::kLess:
		return left->LessThan(right);
	case BinaryNode::OperatorType::kLessEquals:
		return left->LessThanOrEqual(right);
	case BinaryNode::OperatorType::kGreater:
		return left->GreaterThan(right);
	case BinaryNode::OperatorType::kGreaterEquals:
		return left->GreaterThanOrEqual(right);

	case BinaryNode::OperatorType::kBitwiseAnd:
		return left->BitwiseAnd(right);
	case BinaryNode::OperatorType::kBitwiseOr:
		return left->BitwiseOr(right);
	case BinaryNode::OperatorType::kBitwiseXor:
		return left->BitwiseXor(right);
	case BinaryNode::OperatorType::kBitwiseShiftLeft:
		return left->BitwiseLeftShift(right);
	case BinaryNode::OperatorType::kBitwiseShiftRight:
		return left->BitwiseRightShift(right);

	case BinaryNode::OperatorType::kBooleanAnd:
		return left->BooleanAnd(right);
	case BinaryNode::OperatorType::kBooleanOr:
		return left->BooleanOr(right);
	default:
		break;
	}
}

Value* Interpreter::VisitUnaryNode(UnaryNode* node, Context* context) {
	Value* value = Visit(node->node,  context);
	if (ERROR)
		return nullptr;
	if (node->operator_type == UnaryNode::UnaryOperatorType::kMinus)
		return value->Multiply(new IntegerValue(-1, 0, 0, 0));
	else if (node->operator_type == UnaryNode::UnaryOperatorType::kBitwiseComplement)
		return value->BitwiseComplement();
	else if (node->operator_type == UnaryNode::UnaryOperatorType::kBooleanNot)
		return value->BooleanNot();
}

Value* Interpreter::VisitAssignNode(AssignNode* node, Context* context) {
	Value* value = Visit(node->node, context);
	if (ERROR)
		return nullptr;
	context->symbols_->Put(node->key->Clone(), value->Clone());
	return value;
}

Value* Interpreter::VisitVarAccessNode(VarAccessNode* node, Context* context) {
	Value* value = context->GetSymbol(node->key);
	if (value == nullptr) {
		SetError("Undefined variable!", node->line, node->column_start, node->column_end);
		return nullptr;
	}
	return value->Clone();
}

Value* Interpreter::VisitIfNode(IfNode* node, Context* context) {
	int case_count = node->cases->count();
	for (size_t i = 0; i < case_count; i++)
	{
		Value* condition = Visit(node->cases->Get(i)->condition, context);
		if (condition->GetAsBoolean()) {
			delete condition;
			Value* result = Visit(node->cases->Get(i)->body, context);
			// TODO deleting the result if its not a ref type
			return result;
		}
		delete condition;
	}

	if (node->else_case != nullptr) {
		Value* result = Visit(node->else_case, context);
		// TODO deleting the result if its not a ref type
		return result;
	}
	return nullptr;
}

Value* Interpreter::VisitMethodNode(MethodNode* node, Context* context) {
	MethodValue* value = new MethodValue(node->name == nullptr ? nullptr : node->name->Clone(), node->body, node->parameters, node->line, node->column_start, node->column_end);
	if (node->name != nullptr)
		context->symbols_->Put(node->name->Clone(), value);
	return value;
}

Value* Interpreter::VisitCallNode(CallNode* node, Context* context) {
	Value* value = Visit(node->callee, context);
	if (value->type == Value::Type::kMethod) {
		MethodValue* method_value = static_cast<MethodValue*>(value);

	}
	return nullptr;
}