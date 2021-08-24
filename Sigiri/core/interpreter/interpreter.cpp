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
		
		U_INT32 parameter_count = method_value->parameters != nullptr ? method_value->parameters->count() : 0;
		U_INT32 argument_count = node->arguments != nullptr ? node->arguments->count() : 0;

		if (argument_count > parameter_count) {
			//TODO line
			delete value;
			SetError("Too much arguments passed into method", 0, 0, 0);
			return nullptr;
		}

		Context* new_context = new Context(context);

		if (parameter_count == 0) {
			Value* body_result = Visit(method_value->body, new_context);
			//TODO delete result if we dont need
			return body_result;
		}
		else {
			Value** arguments = new Value*[parameter_count];
			// Assigning default values
			for (size_t i = 0; i < parameter_count; i++)
			{
				if (method_value->parameters->Get(i)->default_value != nullptr) {
					Value* default_value = Visit(method_value->parameters->Get(i)->default_value, context);
					if (ERROR) {
						delete value;
						delete new_context;
						return nullptr;
					}
					arguments[i] = default_value;
				}
				else
					arguments[i] = nullptr;
			}

			for (size_t i = 0; i < argument_count; i++)
			{
				if (node->arguments->Get(i)->name != nullptr) {
					bool found_parameter = false;
					for (size_t j = 0; j < parameter_count; j++)
					{
						if (method_value->parameters->Get(j)->name->Compare(node->arguments->Get(i)->name)) {
							Value* argument_value = Visit(node->arguments->Get(i)->value, context);
							if (ERROR) {
								delete value;
								delete[] arguments;
								delete new_context;
								return nullptr;
							}
							if (arguments[j] != nullptr)
								delete arguments[j];
							arguments[j] = argument_value;
							found_parameter = true;
							break;
						}
					}
					if (!found_parameter) {
						//TODO line
						delete value;
						delete[] arguments;
						delete new_context;
						SetError("Couldn't find parameter for named argument", 0, 0, 0);
						return nullptr;
					}
				}
				else {
					if (i < parameter_count) {
						Value* argument_value = Visit(node->arguments->Get(i)->value, context);
						if (ERROR) {
							delete value;
							delete[] arguments;
							delete new_context;
							return nullptr;
						}
						if (arguments[i] != nullptr)
							delete arguments[i];
						arguments[i] = argument_value;
					}
					else {
						//TODO line
						delete value;
						delete[] arguments;
						delete new_context;
						SetError("Too much arguments passed into method", 0, 0, 0);
						return nullptr;
					}
				}
			}

			for (size_t i = 0; i < parameter_count; i++)
			{
				if (arguments[i] == nullptr) {
					//TODO line
					delete value;
					delete[] arguments;
					delete new_context;
					SetError("Missing argument", 0, 0, 0);
					return nullptr;
				}
				else {
					//TODO Do we want to clone parameter name?
					new_context->symbols_->Put(method_value->parameters->Get(i)->name, arguments[i]);
				}
			}

			delete[] arguments;
			Value* body_result = Visit(method_value->body, new_context);
			//TODO delete result if we dont need
			return body_result;
		}
	}
	return nullptr;
}