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

void Interpreter::ReleaseMemory(Value* value) {
	if (value == nullptr)
		return;
	if (value->type == Value::Type::kMethod)
		return;
	if (value->type == Value::Type::kString) {
		if (value->ref_count != 0)
			return;
	}
	delete value;
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
	else if (node->type == Node::Type::kReturn)
		return VisitReturnNode((ReturnNode*)node, context);
	else if (node->type == Node::Type::kFor)
		return VisitForNode((ForNode*)node, context);
	else if (node->type == Node::Type::kWhile)
		return VisitWhileNode((WhileNode*)node, context);
	return nullptr;
}

Value* Interpreter::VisitBlockNode(BlockNode* node, Context* context) {
	U_INT32 statement_count = node->nodes->count();
	for (size_t i = 0; i < statement_count; i++)
	{
		if (node->nodes->Get(i)->type != Node::Type::kLiteral) {
			Value* value = Visit(node->nodes->Get(i), context);
			if (ERROR)
				return nullptr;
			ReleaseMemory(value);
			if (context->return_value_ != nullptr)
				return nullptr;
		}
	}
	return nullptr;
}

Value* Interpreter::VisitLiteralNode(LiteralNode* node, Context* context) {
	if (node->literal_type == LiteralNode::LiteralType::kInteger)
		return new IntegerValue(node->value.int_value, node->line, node->column_start, node->column_end);
	else if (node->literal_type == LiteralNode::LiteralType::kFloat)
		return new FloatValue(node->value.float_value, node->line, node->column_start, node->column_end);
	else if (node->literal_type == LiteralNode::LiteralType::kString)
		return new StringValue(node->value.string_value->Clone(), node->line, node->column_start, node->column_end);
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
	else if (node->operator_type == UnaryNode::UnaryOperatorType::kFloat) {
		Value* cast_result = FloatValue::CastFrom(value);
		if (cast_result == nullptr) {
			delete value;
			SetError("Can't cast to float", value->line, value->column_start, value->column_end);
			return nullptr;
		}
		return cast_result;
	}
}

Value* Interpreter::VisitAssignNode(AssignNode* node, Context* context) {
	Value* value = Visit(node->node, context);
	if (ERROR)
		return nullptr;
	context->symbols_->Put(node->key, value->Clone()->IncrementRefCount());
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
			ReleaseMemory(Visit(node->cases->Get(i)->body, context));
		}
		delete condition;
	}

	if (node->else_case != nullptr) 
		ReleaseMemory(Visit(node->else_case, context));
	return nullptr;
}

Value* Interpreter::VisitMethodNode(MethodNode* node, Context* context) {
	MethodValue* value = new MethodValue(node->name == nullptr ? nullptr : node->name, node->body, node->parameters, node->line, node->column_start, node->column_end);
	if (node->name != nullptr)
		context->symbols_->Put(node->name, value);
	return value;
}

Value* Interpreter::VisitCallNode(CallNode* node, Context* context) {

	//TODO move built-in methods to seperate class
	if (node->callee->type == Node::Type::kVarAccess) {
		VarAccessNode* var_access = static_cast<VarAccessNode*>(node->callee);
		if (var_access->key->Compare(UTF_8 "print")) {
			if (node->arguments != nullptr) {
				if (node->arguments->count() == 1) {
					Value* value = Visit(node->arguments->Get(0)->value, context);
					if (value != nullptr) {
						value->Print();
						ReleaseMemory(value);
					}
				}
			}
			printf("\n");
			return nullptr;
		}
	}

	Value* value = Visit(node->callee, context);
	if (ERROR) 
		return nullptr;

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
			ReleaseMemory(Visit(method_value->body, new_context));
			Value* return_value = new_context->return_value_;
			delete new_context;
			return return_value;
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
							if (argument_value != nullptr && argument_value->ref_count > 0)
								argument_value->ref_count++;
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
						if (argument_value != nullptr && argument_value->ref_count > 0)
							argument_value->ref_count++;
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

			ReleaseMemory(Visit(method_value->body, new_context));
			Value* return_value = new_context->return_value_;

			delete new_context;
			for (size_t i = 0; i < parameter_count; i++)
			{
				if (arguments[i] != nullptr) {
					arguments[i]->ref_count--;
					ReleaseMemory(arguments[i]);
				}
			}
			return return_value;
		}
	}
	return nullptr;
}

Value* Interpreter::VisitReturnNode(ReturnNode* node, Context* context) {
	Value* value = Visit(node->node, context);
	if (ERROR)
		return nullptr;
	context->return_value_ = value;
	return nullptr;
}

Value* Interpreter::VisitForNode(ForNode* node, Context* context) {
	int start = 0, to = 0, step = 1;
	Value* start_value = Visit(node->start, context);
	if (ERROR)
		return nullptr;
	if (start_value->type != Value::Type::kInteger) {
		SetError("Start value must be an integer", start_value->line, start_value->column_start, start_value->column_end);
		delete start_value;
		return nullptr;
	}
	start = (static_cast<IntegerValue*>(start_value))->value;

	Value* to_value = Visit(node->to, context);
	if (ERROR) {
		delete start_value;
		return nullptr;
	}
	if (to_value->type != Value::Type::kInteger) {
		SetError("End value must be an integer", to_value->line, to_value->column_start, to_value->column_end);
		delete to_value;
		delete start_value;
		return nullptr;
	}
	to = (static_cast<IntegerValue*>(to_value))->value;

	if (node->step != nullptr) {
		Value* step_value = Visit(node->step, context);
		if (ERROR) {
			delete start_value;
			delete to_value;
			return nullptr;
		}
		if (step_value->type != Value::Type::kInteger) {
			SetError("End value must be an integer", step_value->line, step_value->column_start, step_value->column_end);
			delete to_value;
			delete start_value;
			delete step_value;
			return nullptr;
		}
		step = (static_cast<IntegerValue*>(step_value))->value;
		delete step_value;
	}

	delete to_value;

	context->symbols_->Put(node->identifier, start_value);
	IntegerValue* integer_start = static_cast<IntegerValue*>(start_value);

	if (start < to) {
		while (start < to)
		{
			ReleaseMemory(Visit(node->body, context));
			if (ERROR) {
				delete start_value;
				delete to_value;
				return nullptr;
			}
			if (context->return_value_ != nullptr)
				break;
			start += step;
			integer_start->value = start;
		}
	}
	else {
		while (start > to) {
			ReleaseMemory(Visit(node->body, context));
			if (ERROR) {
				delete start_value;
				delete to_value;
				return nullptr;
			}
			if (context->return_value_ != nullptr)
				break;
			start += step;
			integer_start->value = start;
		}
	}
	return nullptr;
}

Value* Interpreter::VisitWhileNode(WhileNode* node, Context* context) {
	Value* condition = Visit(node->condition, context);
	if (ERROR)
		return nullptr;

	while (condition->GetAsBoolean()) {
		ReleaseMemory(Visit(node->body, context));
		if (ERROR) {
			delete condition;
			return nullptr;
		}
		delete condition;
		condition = Visit(node->condition, context);
		if (ERROR)
			return nullptr;
	}
	return nullptr;
}