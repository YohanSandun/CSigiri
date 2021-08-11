#include <cstdio>

#include "parser.h"
#include "string/string.h"

char* tokenNames[] = {
		"NEWLINE",
		"INT_NUMBER",
		"FLOAT_NUMBER",
		"STRING",
		"IDENTIFIER",
		"KEYWORD_VAR",
		"KEYWORD_INT",
		"KEYWORD_FOR",
		"KEYWORD_TO",
		"KEYWORD_STEP",
		"KEYWORD_METHOD",
		"KEYWORD_RETURN",
		"KEYWORD_BREAK",
		"KEYWORD_CONTINUE",
		"KEYWORD_IF",
		"KEYWORD_ELIF",
		"KEYWORD_ELSE",
		"KEYWORD_CLASS",
		"PLUS",
		"MINUS",
		"ASTERIX",
		"FW_SLASH",
		"MODULUS",
		"POWER",
		"L_PAREN",
		"R_PAREN",
		"COMMA",
		"DOT",
		"L_BRACE",
		"R_BRACE",
		"L_SQ",
		"R_SQ",
		"COLON",
		"SEMI_COLON",
		"EQUALS",
		"EQUALS_EQUALS",
		"NOT_EQUALS",
		"GREATER_THAN",
		"LESS_THAN",
		"GREATER_EQ",
		"LESS_EQ",
		"BOOLEAN_NOT",
		"BOOLEAN_AND",
		"BOOLEAN_OR",
		"BITWISE_OR",
		"BITWISE_AND",
		"BITWISE_XOR",
		"BITWISE_COMPLEMENT",
		"LEFT_SHIFT",
		"RIGHT_SHIFT",
		"EOF_TOKEN"
};

Parser::Parser() {
	//mSymbols = new List<String*>();
}

void Parser::setTokens(List<Token*>* tokens) {
	mIndex = -1;
	if (mTokens != nullptr)
		delete mTokens;
	mTokens = tokens;
	advance();
}

Parser::~Parser() {
	delete mTokens;
	//delete mSymbols;
}

void Parser::advance() {
	mIndex++;
	if (mIndex < mTokens->count())
		currentToken = mTokens->Get(mIndex);
}

void Parser::skipNewLines() {
	while (currentToken->type == Token::Type::kNewLine)
		advance();
}

Node* Parser::parse(SymbolsParser* context) {
	return block(context, Token::Type::kEof);
}

Node* Parser::block(SymbolsParser* context, Token::Type end) {
	List<Node*>* statements = new List<Node*>();
	while (true) {
		skipNewLines();
		if (currentToken->type == end)
			break;
		Node* node = expr(context);
		if (mError != nullptr) {
			delete statements;
			return nullptr;
		}
		statements->Add(node);
	}
	return new Block(statements);
}

Node* Parser::expr(SymbolsParser* context) {
	Node* left = Compare(context);
	if (mError != nullptr)
		return nullptr;
	while (currentToken->type == Token::Type::kBooleanAnd || currentToken->type == Token::Type::kBooleanOr)
	{
		Token::Type type = currentToken->type;
		advance();
		Node* right = Compare(context);
		if (mError != nullptr) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, type, right);
	}
	return left;
}

Node* Parser::Compare(SymbolsParser* context) {
	if (currentToken->type == Token::Type::kBooleanNot) {
		advance();
		return new UnaryNode(Token::Type::kBooleanNot, Compare(context));
	}
	Node* left = bitwise_or(context);
	if (mError != nullptr)
		return nullptr;
	while (currentToken->type == Token::Type::kEqualsEquals || currentToken->type == Token::Type::kNotEquals ||
		currentToken->type == Token::Type::kGreaterThan || currentToken->type == Token::Type::kLessThan ||
		currentToken->type == Token::Type::kGreaterEquals || currentToken->type == Token::Type::kLessEquals) {
		Token::Type type = currentToken->type;
		advance();
		Node* right = bitwise_or(context);
		if (mError != nullptr) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, type, right);
	}
	return left;
}

Node* Parser::bitwise_or(SymbolsParser* context) {
	Node* left = bitwise_xor(context);
	if (mError != nullptr)
		return nullptr;
	while (currentToken->type == Token::Type::kBitwiseOr)
	{
		advance();
		Node* right = bitwise_xor(context);
		if (mError != nullptr) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, Token::Type::kBitwiseOr, right);
	}
	return left;
}

Node* Parser::bitwise_xor(SymbolsParser* context) {
	Node* left = bitwise_and(context);
	if (mError != nullptr)
		return nullptr;
	while (currentToken->type == Token::Type::kBitwiseXor)
	{
		advance();
		Node* right = bitwise_and(context);
		if (mError != nullptr) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, Token::Type::kBitwiseXor, right);
	}
	return left;
}

Node* Parser::bitwise_and(SymbolsParser* context) {
	Node* left = shift(context);
	if (mError != nullptr)
		return nullptr;
	while (currentToken->type == Token::Type::kBitwiseAnd)
	{
		advance();
		Node* right = shift(context);
		if (mError != nullptr) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, Token::Type::kBitwiseAnd, right);
	}
	return left;
}

Node* Parser::shift(SymbolsParser* context) {
	Node* left = arithmetic(context, false);
	if (mError != nullptr)
		return nullptr;
	while (currentToken->type == Token::Type::kLeftShift || currentToken->type == Token::Type::kRightShift)
	{
		Token::Type type = currentToken->type;
		advance();
		Node* right = arithmetic(context, false);
		if (mError != nullptr) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, type, right);
	}
	return left;
}

Node* Parser::arithmetic(SymbolsParser* context, bool byPassDot=false) {
	Node* left = term(context, byPassDot);
	if (mError != nullptr)
		return nullptr;
	while (currentToken->type == Token::Type::kPlus || currentToken->type == Token::Type::kMinus)
	{
		Token::Type type = currentToken->type;
		advance();
		Node* right = term(context, byPassDot);
		if (mError != nullptr) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, type, right);
	}
	return left;
}

Node* Parser::term(SymbolsParser* context, bool byPassDot=false) {
	Node* left = factor(context, byPassDot);
	if (mError != nullptr) 
		return nullptr;
	while (currentToken->type == Token::Type::kAsterix || currentToken->type == Token::Type::kFowardSlash || currentToken->type == Token::Type::kPrecentage)
	{
		Token::Type type = currentToken->type;
		advance();
		Node* right = factor(context, byPassDot);
		if (mError != nullptr) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, type, right);
	}
	return left;
}

Node* Parser::factor(SymbolsParser* context, bool byPassDot=false) {
	Token* token = currentToken;
	if (token->type == Token::Type::kPlus || token->type == Token::Type::kMinus) {
		advance();
		Node* node = factor(context, byPassDot);
		if (mError != nullptr) 
			return nullptr;
		return new UnaryNode(token->type, node);
	}
	return power(context, byPassDot);
}

Node* Parser::power(SymbolsParser* context, bool byPassDot=false) {
	Node* left = complement(context, byPassDot);
	if (mError != nullptr) 
		return nullptr;
	
	while (currentToken->type == Token::Type::kPower)
	{
		advance();
		Node* right = factor(context, byPassDot);
		if (mError != nullptr) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, Token::Type::kPower, right);
	}
	return left;
}

Node* Parser::complement(SymbolsParser* context, bool byPassDot=false) {
	if (currentToken->type == Token::Type::kBitwiseComplement) {
		advance();
		Node* node = factor(context, byPassDot);
		if (mError != nullptr)
			return nullptr;
		return new UnaryNode(Token::Type::kBitwiseComplement, node);
	}
	return call(context, byPassDot);
}

Node* Parser::call(SymbolsParser* context, bool byPassDot= false) {
	Node* node = atom(context, byPassDot);
	if (mError != nullptr)
		return nullptr;
	if (currentToken->type == Token::Type::kLeftParen) {
		advance();
		List<Node*>* arguments = nullptr;
		if (currentToken->type == Token::Type::kRightParen) {
			advance();
		}
		else {
			arguments = new List<Node*>();
			skipNewLines();
			Node* expression = expr(context);
			if (mError != nullptr) {
				delete node;
				return nullptr;
			}
			arguments->Add(expression);
			skipNewLines();
			while (currentToken->type == Token::Type::kComma) {
				advance();
				skipNewLines();
				if (currentToken->type == Token::Type::kRightParen)
					break;
				Node* expression = expr(context);
				if (mError != nullptr) {
					delete node;
					delete arguments;
					return nullptr;
				}
				arguments->Add(expression);
				skipNewLines();
			}
			if (currentToken->type != Token::Type::kRightParen) {
				delete node;
				delete arguments;
				mError = new String("Expected ')'");
				return nullptr;
			}
			advance();
		}
		if (currentToken->type == Token::Type::kLeftSqare)
			return subscript(new Call(node, arguments), context);
		else if (currentToken->type == Token::Type::kDot)
			return attribute(new Call(node, arguments), context);
		return new Call(node, arguments);
	}
	return node;
}
 
Node* Parser::atom(SymbolsParser* context, bool byPassDot = false) {
	Token* token = currentToken;
	if (token->type == Token::Type::kIntNumber) {
		advance();
		return new IntegerNode(StringToInt(token->value));
	}
	else if (token->type == Token::Type::kFloatNumber) {
		advance();
		return new FloatNode(StringToFloat(token->value));
	}
	else if (token->type == Token::Type::kString) {
		advance();
		if (currentToken->type == Token::Type::kLeftSqare)
			return subscript(new StringNode(new String(token->value->ptr)), context);
		return new StringNode(new String(token->value->ptr));
	}
	else if (token->type == Token::Type::kIdentifier) {
		advance();
		if (currentToken->type == Token::Type::kEquals) {
			advance();
			Node* expression = expr(context);
			if (mError != nullptr)
				return nullptr;
			return new VarAssign(new String(token->value->ptr), expression);
		}
		if (currentToken->type == Token::Type::kLeftSqare)
			return subscript(new VarAccess(new String(token->value->ptr)), context);
		else if (!byPassDot && currentToken->type == Token::Type::kDot) {
			return attribute(new VarAccess(new String(token->value->ptr)), context);
		}
		return new VarAccess(new String(token->value->ptr));
	}
	else if (token->type == Token::Type::kLeftParen) {
		advance();
		if (currentToken->type == Token::Type::kRightParen) {
			advance();
			return new TupleNode(nullptr);
		}
		Node* expression = expr(context);
		if (mError != nullptr)
			return nullptr;

		if (currentToken->type == Token::Type::kRightParen) {
			advance();
			return expression;
		}
		else if (currentToken->type == Token::Type::kComma) {
			List<Node*>* items = new List<Node*>();
			items->Add(expression);
			while (currentToken->type == Token::Type::kComma) {
				advance();
				if (currentToken->type == Token::Type::kRightParen)
					break;
				Node* item = expr(context);
				if (mError != nullptr) {
					delete items;
					return nullptr;
				}
				items->Add(item);
			}
			if (currentToken->type != Token::Type::kRightParen) {
				mError = new String("Expected ',' or ')'");
				delete items;
				return nullptr;
			}
			advance();
			return new TupleNode(items);
		}
		mError = new String("Expected ')'");
		delete expression;
		return nullptr;
	}
	else if (token->type == Token::Type::kKeywordVar) {

		advance();
		token = currentToken;
		if (token->type == Token::Type::kIdentifier) {
			advance();
			if (currentToken->type != Token::Type::kEquals) {
				mError = new String("Expected '='");
				return nullptr;
			}
			advance();
			Node* expression = expr(context);
			if (mError != nullptr)
				return nullptr;

			return new VarAssign(new String(token->value->ptr), expression);
		}
		else {
			mError = new String("Expected an identifier");
			return nullptr;
		}
	}
	else if (token->type == Token::Type::kKeywordFor)
		return for_expr(context);
	else if (token->type == Token::Type::kKeywordMethod)
		return method_expr(context);
	else if (token->type == Token::Type::kKeywordReturn)
		return return_expr(context);
	else if (token->type == Token::Type::kKeywordClass)
		return class_expr(context);
	else if (token->type == Token::Type::kKeywordBreak) {
		advance();
		return new Node(Node::Type::BREAK);
	}
	else if (token->type == Token::Type::kKeywordContinue) {
		advance();
		return new Node(Node::Type::CONTINUE);
	}
	else if (token->type == Token::Type::kKeywordIf)
		return if_expr(context);
	else if (token->type == Token::Type::kLeftSqare)
		return list_expr(context);

	mError = new String("Expected something!");
	return nullptr;
}

Node* Parser::method_expr(SymbolsParser* context) {

	advance(); // method keyword
	Token* identifier = currentToken;
	if (currentToken->type != Token::Type::kIdentifier) {
		identifier = nullptr;
	} else
		advance();
	if (currentToken->type != Token::Type::kLeftParen) {
		mError = new String("Expected '('");
		return nullptr;
	}
	advance();
	List<String*>* ids = new List<String*>();
	SymbolsParser* newSymbols = new SymbolsParser(context);
	if (currentToken->type == Token::Type::kIdentifier) {
		
		ids->Add(new String(currentToken->value->ptr));
		advance();
		while (currentToken->type == Token::Type::kComma) {
			advance();
			if (currentToken->type == Token::Type::kIdentifier) {
			
				ids->Add(new String(currentToken->value->ptr));
				advance();
			}
		}
	}

	if (currentToken->type != Token::Type::kRightParen) {
		mError = new String("Expected ')'");
		return nullptr;
	}
	advance();
	
	if (currentToken->type == Token::Type::kColon) {
		advance();
		skipNewLines();
		//int id = context->setSymbolIndex(identifier->mValue);
		Node* body = expr(newSymbols);
		if (mError != nullptr)
			return nullptr;
		return new Method(identifier == nullptr ? nullptr : new String(identifier->value->ptr), body, ids);
	}
	else {
		skipNewLines();
		if (currentToken->type == Token::Type::kLeftBrace) {
			advance();
			skipNewLines();
			//int id = context->setSymbolIndex(identifier->mValue);
			Node* node = block(newSymbols, Token::Type::kRightBrace);
			advance(); //closing brace
			if (mError != nullptr)
				return nullptr;
			return new Method(identifier == nullptr ? nullptr : new String(identifier->value->ptr), node, ids);
		}
		mError = new String("Expected ':' or '{'");
		return nullptr;
	}
	return nullptr;
}

Node* Parser::for_expr(SymbolsParser* context) {
	Node* start, * to, * step = nullptr;
	advance(); // for keyword
	Token* identifier = currentToken;
	if (currentToken->type != Token::Type::kIdentifier)
	{
		mError = new String("Expected an identifier (for loop)");
		printf("%d\n", currentToken->type);
		return nullptr;
	}
	advance();

	if (currentToken->type != Token::Type::kEquals)
	{
		mError = new String("Expected '='");
		return nullptr;
	}
	advance();

	start = bitwise_or(context);
	if (mError != nullptr)
		return nullptr;
	if (currentToken->type != Token::Type::kKeywordTo)
	{
		mError = new String("Expected 'to'");
		delete start;
		return nullptr;
	}
	advance();

	to = bitwise_or(context);
	if (mError != nullptr) {
		delete start;
		return nullptr;
	}

	if (currentToken->type == Token::Type::kKeywordStep) {
		advance();
		step = bitwise_or(context);
		if (mError != nullptr) {
			delete start;
			delete to;
			return nullptr;
		}
	}
	
	if (currentToken->type == Token::Type::kColon) {
		advance();
		skipNewLines();
		//int id = context->setSymbolIndex(identifier->mValue);
		Node* body = expr(context);
		if (mError != nullptr)
		{
			delete start;
			delete to;
			if (step != nullptr)
				delete step;
			return nullptr;
		}
		return new ForLoop(new String(identifier->value->ptr), start, to, step, body);
	}
	else {
		skipNewLines();
		if (currentToken->type == Token::Type::kLeftBrace) {
			advance();
			skipNewLines();
			//int id = context->setSymbolIndex(identifier->mValue);
			Node* node = block(context, Token::Type::kRightBrace);
			advance(); //closing brace
			if (mError != nullptr)
			{
				delete start;
				delete to;
				if (step != nullptr)
					delete step;
				return nullptr;
			}
			return new ForLoop(new String(identifier->value->ptr), start, to, step, node);
		}
		mError = new String("Expected ':' or '{'");
		delete start;
		delete to;
		if (step != nullptr)
			delete step;
		return nullptr;
	}

	return nullptr;
}

Node* Parser::return_expr(SymbolsParser* context) {
	advance();
	Node* body = expr(context);
	if (mError != nullptr)
		return nullptr;
	return new Return(body);
}

Node* Parser::if_expr(SymbolsParser* context) {
	advance();
	List<IfCase*>* cases = new List<IfCase*>();
	Node* condition = expr(context);
	if (mError != nullptr)
		return nullptr;

	skipNewLines();
	if (currentToken->type == Token::Type::kColon) {
		advance();
		skipNewLines();
		Node* body = expr(context);
		if (mError != nullptr) {
			delete condition;
			return nullptr;
		}
		cases->Add(new IfCase(condition, body));
		skipNewLines();
	}
	else if (currentToken->type == Token::Type::kLeftBrace) {
		advance();
		skipNewLines();
		Node* body = block(context, Token::Type::kRightBrace);
		advance(); //closing brace
		if (mError != nullptr) {
			delete condition;
			return nullptr;
		}
		cases->Add(new IfCase(condition, body));
		skipNewLines();
	}

	while (currentToken->type == Token::Type::kKeywordElif) {
		advance();
		Node* elifCondition = expr(context);
		if (mError != nullptr) {
			delete cases;
			return nullptr;
		}

		skipNewLines();
		if (currentToken->type == Token::Type::kColon) {
			advance();
			skipNewLines();
			Node* elifBody = expr(context);
			if (mError != nullptr) {
				delete elifCondition;
				delete cases;
				return nullptr;
			}
			cases->Add(new IfCase(elifCondition, elifBody));
			skipNewLines();
		}
		else if (currentToken->type == Token::Type::kLeftBrace) {
			advance();
			skipNewLines();
			Node* elifBody = block(context, Token::Type::kRightBrace);
			advance(); //closing brace
			if (mError != nullptr) {
				delete elifCondition;
				delete cases;
				return nullptr;
			}
			cases->Add(new IfCase(elifCondition, elifBody));
			skipNewLines();
		}
	}

	if (currentToken->type == Token::Type::kKeywordElse) {
		advance();
		skipNewLines();
		if (currentToken->type == Token::Type::kColon) {
			advance();
			skipNewLines();
			Node* elseBody = expr(context);
			if (mError != nullptr) {
				delete cases;
				return nullptr;
			}
			skipNewLines();
			return new If(cases, elseBody);
		}
		else if (currentToken->type == Token::Type::kLeftBrace) {
			advance();
			skipNewLines();
			Node* elseBody = block(context, Token::Type::kRightBrace);
			advance(); //closing brace
			if (mError != nullptr) {
				delete cases;
				return nullptr;
			}
			skipNewLines();
			return new If(cases, elseBody);
		}
	}
	return new If(cases, nullptr);
}

Node* Parser::list_expr(SymbolsParser* context) {
	advance();
	if (currentToken->type == Token::Type::kRightSquare) {
		advance();
		return new ListNode(nullptr);
	}
	Node* expression = expr(context);
	if (mError != nullptr)
		return nullptr;
	List<Node*>* items = new List<Node*>();
	items->Add(expression);

	while (currentToken->type == Token::Type::kComma) {
		advance();
		if (currentToken->type == Token::Type::kRightSquare)
			break;
		Node* expression = expr(context);
		if (mError != nullptr) {
			delete items;
			return nullptr;
		}
		items->Add(expression);
	}

	if (currentToken->type == Token::Type::kRightSquare) {
		advance();
		return new ListNode(items);
	}
	if (currentToken->type == Token::Type::kLeftSqare)
		return subscript(new ListNode(items), context);
	mError = new String("Expected ']'");
	delete items;
	return nullptr;
}

Node* Parser::subscript(Node* base, SymbolsParser* context) {
	advance();
	Node* expression = expr(context);
	if (mError != nullptr)
		return nullptr;

	if (currentToken->type != Token::Type::kRightSquare) {
		advance();
		mError = new String("Expected ']'");
		delete expression;
		return nullptr;
	}
	advance();

	if (currentToken->type == Token::Type::kLeftSqare) 
		return subscript(new SubscriptAccessNode(base, expression), context);
		
	if (currentToken->type == Token::Type::kEquals) {
		advance();
		Node* node = expr(context);
		if (mError != nullptr) {
			delete expression;
			return nullptr;
		}
		return new SubscriptAssignNode(new SubscriptAccessNode(base, expression), node);
	}
	return new SubscriptAccessNode(base, expression);
}

Node* Parser::class_expr(SymbolsParser* context) {
	advance();
	Token* identifier = currentToken;
	if (identifier->type != Token::Type::kIdentifier) {
		mError = new String("Expected an identifier");
		return nullptr;
	}
	advance();
	skipNewLines();
	if (currentToken->type == Token::Type::kLeftBrace) {
		advance();
		skipNewLines();
		//int id = context->setSymbolIndex(identifier->mValue);
		Node* node = block(context, Token::Type::kRightBrace);
		advance(); //closing brace
		if (mError != nullptr)
			return nullptr;
		return new ClassNode(new String(identifier->value->ptr), node);
	}
	mError = new String("Expected '{'");
	return nullptr;
}

Node* Parser::attribute(Node* base, SymbolsParser* context) {
	advance();
	
	Node* node = call(context, true);
	if (mError != nullptr)
		return nullptr;
	if (currentToken->type == Token::Type::kDot)
		return attribute(new AttributeNode(base, node), context);
	return new AttributeNode(base, node);
}