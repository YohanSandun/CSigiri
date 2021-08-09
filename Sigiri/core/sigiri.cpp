#include "sigiri.h"

Interpreter::~Interpreter() {
	//delete mSymbols;
}

Value* Interpreter::visit(Node* node, SymbolsRuntime* symbols) {
	if (node->mType == Node::Type::INTEGER)
		return visitInteger((IntegerNode*)node, symbols);
	else if (node->mType == Node::Type::FLOAT)
		return visitFloat((FloatNode*)node, symbols);
	else if (node->mType == Node::Type::STRING)
		return visitString((StringNode*)node, symbols);
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
	else if (node->mType == Node::Type::RETURN)
		return vistiReturn((Return*)node, symbols);
	else if (node->mType == Node::Type::IF)
		return visitIf((If*)node, symbols);
	else if (node->mType == Node::Type::LIST)
		return visitList((ListNode*)node, symbols);
	else if (node->mType == Node::Type::SUBSCRIPT_ACCESS)
		return visitSubscriptAccess((SubscriptAccessNode*)node, symbols);
	else if (node->mType == Node::Type::SUBSCRIPT_ASSIGN)
		return visitSubscriptAssign((SubscriptAssignNode*)node, symbols);
	else if (node->mType == Node::Type::CLASS)
		return visitClass((ClassNode*)node, symbols);
	else if (node->mType == Node::Type::ATTRIBUTE)
		return visitAttribute((AttributeNode*)node, symbols);
	else if (node->mType == Node::Type::TUPLE)
		return visitTuple((TupleNode*)node, symbols);
	else if (node->mType == Node::Type::BREAK) {
		symbols->mBreak = true;
		return nullptr;
	}
	else if (node->mType == Node::Type::CONTINUE) {
		symbols->mContinue = true;
		return nullptr;
	}	
}

Value* Interpreter::visitInteger(IntegerNode* node, SymbolsRuntime* symbols) {
	Value* value = new IntegerValue(node->mValue);
	return value;
}

Value* Interpreter::visitFloat(FloatNode* node, SymbolsRuntime* symbols) {
	Value* value = new FloatValue(node->mValue);
	return value;
}

Value* Interpreter::visitString(StringNode* node, SymbolsRuntime* symbols) {
	Value* value = new StringValue(new String(node->mValue->ptr));
	return value;
}

Value* Interpreter::visitBinary(BinaryNode* node, SymbolsRuntime* symbols) {
	Value* left = visit(node->mLeft, symbols);
	Value* right = visit(node->mRight, symbols);

	switch (node->mOpType)
	{
	case Token::Type::kPlus:
		return left->add(right);
	case Token::Type::kMinus:
		return left->sub(right);
	case Token::Type::kAsterix:
		return left->mul(right);
	case Token::Type::kFowardSlash:
		return left->div(right);
	case Token::Type::kPrecentage:
		return left->mod(right);
	case Token::Type::kPower:
		return left->s_pow(right);
	case Token::Type::kEqualsEquals:
		return left->comp_eq_eq(right);
	case Token::Type::kNotEquals:
		return left->comp_not_eq(right);
	case Token::Type::kLessThan:
		return left->comp_less(right);
	case Token::Type::kGreaterThan:
		return left->comp_greater(right);
	case Token::Type::kLessEquals:
		return left->comp_less_eq(right);
	case Token::Type::kGreaterEquals:
		return left->comp_greater_eq(right);
	case Token::Type::kBitwiseAnd:
		return left->bitwise_and(right);
	case Token::Type::kBitwiseOr:
		return left->bitwise_or(right);
	case Token::Type::kBitwiseXor:
		return left->bitwise_xor(right);
	case Token::Type::kLeftShift:
		return left->shift_left(right);
	case Token::Type::kRightShift:
		return left->shift_right(right);
	case Token::Type::kBooleanAnd:
		return left->boolean_and(right);
	case Token::Type::kBooleanOr:
		return left->boolean_or(right);

	default:
		break;
	}
	return nullptr;
}

Value* Interpreter::visitUnary(UnaryNode* node, SymbolsRuntime* symbols) {
	Value* value = visit(node->mNode, symbols);
	if (node->mOpType == Token::Type::kMinus) {
		return value->negate();
	}
	else if (node->mOpType == Token::Type::kBooleanNot) {
		return value->boolean_not();
	}
	else if (node->mOpType == Token::Type::kBitwiseComplement) {
		return value->bitwise_complement();
	}
	return value;
}

Value* Interpreter::visitVarAccess(VarAccess* node, SymbolsRuntime* symbols) {
	//printf("reading %s\n", node->mId->ptr);

	/*printf("----------------------------\n");

	for (size_t i = 0; i < symbols->mSymbolCount; i++)
	{
		printf("%s\n", symbols->mSymbolNames->Get(i)->ptr);
	}

	printf("----------------------------\n");*/

	return symbols->getSymbol(node->mId)->clone();
}

Value* Interpreter::visitVarAssign(VarAssign* node, SymbolsRuntime* symbols, SymbolsRuntime* baseSymbols) {
	//printf("setting %s\n", node->mId->ptr);
	Value* value = visit(node->mNode, baseSymbols != nullptr ? baseSymbols : symbols);
	symbols->setSymbol(node->mId, value);
	return value->clone();
}

Value* Interpreter::visitBlock(Block* node, SymbolsRuntime* symbols) {
	int count = node->mStatements->count();
	for (size_t i = 0; i < count; i++)
	{
		if (node->mStatements->Get(i)->mType != Node::Type::INTEGER 
			&& node->mStatements->Get(i)->mType != Node::Type::FLOAT
			&& node->mStatements->Get(i)->mType != Node::Type::STRING
			&& node->mStatements->Get(i)->mType != Node::Type::BINARY
			&& node->mStatements->Get(i)->mType != Node::Type::UNARY
			&& node->mStatements->Get(i)->mType != Node::Type::LIST
			&& node->mStatements->Get(i)->mType != Node::Type::TUPLE
			){
			Value* value = visit(node->mStatements->Get(i), symbols);
			if (value != NULL)
				if (node->mStatements->Get(i)->mType != Node::Type::METHOD && node->mStatements->Get(i)->mType != Node::Type::CLASS)
					if (value->mType != Value::Type::LIST && value->mType != Value::Type::METHOD && value->mType != Value::Type::OBJECT
						&& value->mType != Value::Type::TUPLE)
						delete value;
		}
		if (symbols->mReturn || symbols->mBreak || symbols->mContinue)
			return nullptr;
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
			symbols->mContinue = false;
			if (symbols->mReturn || symbols->mBreak) {
				symbols->mBreak = false;
				break;
			}
			start += step;
			v_start_int->mValue = start;
		}
	}
	else {
		while (start > to)
		{
			visit(node->mBody, symbols);
			symbols->mContinue = false;
			if (symbols->mReturn || symbols->mBreak) {
				symbols->mBreak = false;
				break;
			}
			start += step;
			v_start_int->mValue = start;
		}
	}

	delete v_to;

	return nullptr;
}

Value* Interpreter::visitMethod(Method* node, SymbolsRuntime* symbols) {
	MethodValue* value = new MethodValue(node->mId, node->mBody, node->mParams);
	if (node->mId != nullptr)
		symbols->setSymbol(node->mId, value);
	return value;
}

Value* Interpreter::visitCall(Call* node, SymbolsRuntime* symbols, SymbolsRuntime* baseSymbols) {

	if (node->mBase->mType == Node::Type::VAR_ACCESS) {
		VarAccess* var = (VarAccess*)node->mBase;
		if (var->mId->Compare("print")) {
			Value* value = visit(node->mArgs->Get(0), baseSymbols != nullptr ? baseSymbols : symbols);
			if (value != NULL) {
				value->print();
				//delete value; // dont delete objects
			}
			printf("\n");
			return nullptr;
		}
	}

	Value* methodValue = visit(node->mBase, symbols);
	if (methodValue->mType == Value::Type::METHOD) {
		MethodValue* method = (MethodValue*)methodValue;
		int paramCount = method->mParams->count();
		if ((paramCount == 0 && node->mArgs == nullptr) || paramCount == node->mArgs->count()) {
			SymbolsRuntime* newSymbols = new SymbolsRuntime(symbols);
			for (size_t i = 0; i < paramCount; i++)
				newSymbols->setSymbol(method->mParams->Get(i), visit(node->mArgs->Get(i), baseSymbols != nullptr ? baseSymbols : symbols));
			visit(method->mBody, newSymbols);
			Value* retVal = nullptr;
			if (newSymbols->returnValue != nullptr) {
				retVal = newSymbols->returnValue->clone();
				if (retVal->mType == Value::Type::LIST || retVal->mType == Value::Type::OBJECT || retVal->mType == Value::Type::TUPLE)
					newSymbols->keepReturnValue = true;
			}
			delete newSymbols;
			return retVal;
		}
		else {
			// argument count mismatch error
		}
	}
	else if (methodValue->mType == Value::Type::CLASS) {
		ClassValue* cls = (ClassValue*)methodValue;
		SymbolsRuntime* newSymbols = new SymbolsRuntime(symbols);
		visit(cls->mBody, newSymbols);
		ObjectValue* obj = new ObjectValue(newSymbols);
		return obj;
	}
	else {
		// method not found error
	}
	return nullptr;
}

Value* Interpreter::vistiReturn(Return* node, SymbolsRuntime* symbols) {
	Value* value = visit(node->mNode, symbols);
	symbols->mReturn = true;
	symbols->returnValue = value;
	return nullptr;
}

Value* Interpreter::visitIf(If* node, SymbolsRuntime* symbols) {
	int caseCount = node->mCases->count();
	for (size_t i = 0; i < caseCount; i++)
	{
		Value* condition = visit(node->mCases->Get(i)->mCondition, symbols);
		if (condition->asBoolean()) {
			delete condition;
			Value* result = visit(node->mCases->Get(i)->mBody, symbols);
			if (result != nullptr)
				delete result;
			return nullptr;
		}
		delete condition;
	}

	if (node->mElseCase != nullptr) {
		Value* result = visit(node->mElseCase, symbols);
		if (result != nullptr)
			delete result;
	}
	return nullptr;
}

Value* Interpreter::visitList(ListNode* node, SymbolsRuntime* symbols) {
	if (node->mItems == nullptr) 
		return new ListValue(new List<Value*>());
	int count = node->mItems->count();
	List<Value*>* values = new List<Value*>(count + 5); // +5 spaces
	for (size_t i = 0; i < count; i++)
		values->Add(visit(node->mItems->Get(i), symbols));
	return new ListValue(values);
}

Value* Interpreter::visitSubscriptAccess(SubscriptAccessNode* node, SymbolsRuntime* symbols) {
	Value* base = visit(node->mBase, symbols);
	return base->subscriptAccess(visit(node->mNode, symbols));
}

Value* Interpreter::visitSubscriptAssign(SubscriptAssignNode* node, SymbolsRuntime* symbols) {
	SubscriptAccessNode* accessNode = (SubscriptAccessNode*)node->mBase;
	Value* base = visit(accessNode->mBase, symbols);
	return base->subscriptAssign(visit(accessNode->mNode, symbols), visit(node->mNode, symbols));
}

Value* Interpreter::visitClass(ClassNode* node, SymbolsRuntime* symbols) {
	ClassValue* value = new ClassValue(node->mId, node->mBody);
	symbols->setSymbol(node->mId, value);
	return value;
}

Value* Interpreter::visitAttribute(AttributeNode* node, SymbolsRuntime* symbols) {
	Value* base = visit(node->mBase, symbols);
	if (base->mType == Value::Type::OBJECT) {
		if (node->mNode->mType == Node::Type::VAR_ASSIGN)
			return visitVarAssign((VarAssign*)node->mNode, ((ObjectValue*)base)->mSymbols, symbols);
		else if (node->mNode->mType == Node::Type::CALL)
			return visitCall((Call*)node->mNode, ((ObjectValue*)base)->mSymbols, symbols);
		return visit(node->mNode, ((ObjectValue*)base)->mSymbols);
	}
	return nullptr;
}

Value* Interpreter::visitTuple(TupleNode* node, SymbolsRuntime* symbols) {
	if (node->mItems == nullptr)
		return new TupleValue(new List<Value*>(1)); //todo only one space
	int count = node->mItems->count();
	List<Value*>* values = new List<Value*>(count + 5); // +5 spaces
	for (size_t i = 0; i < count; i++)
		values->Add(visit(node->mItems->Get(i), symbols));
	return new TupleValue(values);
}