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
	if (mIndex < mTokens->getCount())
		currentToken = mTokens->get(mIndex);
}

void Parser::skipNewLines() {
	while (currentToken->mType == Token::Type::NEWLINE)
		advance();
}

Node* Parser::parse(SymbolsParser* symbols) {
	return block(symbols, Token::Type::EOF_TOKEN);
}

Node* Parser::block(SymbolsParser* symbols, Token::Type end) {
	List<Node*>* statements = new List<Node*>();
	while (true) {
		skipNewLines();
		if (currentToken->mType == end)
			break;
		Node* node = expr(symbols);
		if (mError != nullptr) {
			delete statements;
			return nullptr;
		}
		statements->add(node);
	}
	return new Block(statements);
}

Node* Parser::expr(SymbolsParser* symbols) {
	Node* left = Compare(symbols);
	if (mError != nullptr)
		return nullptr;
	while (currentToken->mType == Token::Type::BOOLEAN_AND || currentToken->mType == Token::Type::BOOLEAN_OR)
	{
		Token::Type type = currentToken->mType;
		advance();
		Node* right = Compare(symbols);
		if (mError != nullptr) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, type, right);
	}
	return left;
}

Node* Parser::Compare(SymbolsParser* symbols) {
	if (currentToken->mType == Token::Type::BOOLEAN_NOT) {
		advance();
		return new UnaryNode(Token::Type::BOOLEAN_NOT, Compare(symbols));
	}
	Node* left = bitwise_or(symbols);
	if (mError != nullptr)
		return nullptr;
	while (currentToken->mType == Token::Type::EQUALS_EQUALS || currentToken->mType == Token::Type::NOT_EQUALS ||
		currentToken->mType == Token::Type::GREATER_THAN || currentToken->mType == Token::Type::LESS_THAN ||
		currentToken->mType == Token::Type::GREATER_EQ || currentToken->mType == Token::Type::LESS_EQ) {
		Token::Type type = currentToken->mType;
		advance();
		Node* right = bitwise_or(symbols);
		if (mError != nullptr) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, type, right);
	}
	return left;
}

Node* Parser::bitwise_or(SymbolsParser* symbols) {
	Node* left = bitwise_xor(symbols);
	if (mError != nullptr)
		return nullptr;
	while (currentToken->mType == Token::Type::BITWISE_OR)
	{
		advance();
		Node* right = bitwise_xor(symbols);
		if (mError != nullptr) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, Token::Type::BITWISE_OR, right);
	}
	return left;
}

Node* Parser::bitwise_xor(SymbolsParser* symbols) {
	Node* left = bitwise_and(symbols);
	if (mError != nullptr)
		return nullptr;
	while (currentToken->mType == Token::Type::BITWISE_XOR)
	{
		advance();
		Node* right = bitwise_and(symbols);
		if (mError != nullptr) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, Token::Type::BITWISE_XOR, right);
	}
	return left;
}

Node* Parser::bitwise_and(SymbolsParser* symbols) {
	Node* left = shift(symbols);
	if (mError != nullptr)
		return nullptr;
	while (currentToken->mType == Token::Type::BITWISE_AND)
	{
		advance();
		Node* right = shift(symbols);
		if (mError != nullptr) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, Token::Type::BITWISE_AND, right);
	}
	return left;
}

Node* Parser::shift(SymbolsParser* symbols) {
	Node* left = arithmetic(symbols, false);
	if (mError != nullptr)
		return nullptr;
	while (currentToken->mType == Token::Type::LEFT_SHIFT || currentToken->mType == Token::Type::RIGHT_SHIFT)
	{
		Token::Type type = currentToken->mType;
		advance();
		Node* right = arithmetic(symbols, false);
		if (mError != nullptr) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, type, right);
	}
	return left;
}

Node* Parser::arithmetic(SymbolsParser* symbols, bool byPassDot=false) {
	Node* left = term(symbols, byPassDot);
	if (mError != nullptr)
		return nullptr;
	while (currentToken->mType == Token::Type::PLUS || currentToken->mType == Token::Type::MINUS)
	{
		Token::Type type = currentToken->mType;
		advance();
		Node* right = term(symbols, byPassDot);
		if (mError != nullptr) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, type, right);
	}
	return left;
}

Node* Parser::term(SymbolsParser* symbols, bool byPassDot=false) {
	Node* left = factor(symbols, byPassDot);
	if (mError != nullptr) 
		return nullptr;
	while (currentToken->mType == Token::Type::ASTERIX || currentToken->mType == Token::Type::FW_SLASH || currentToken->mType == Token::Type::MODULUS)
	{
		Token::Type type = currentToken->mType;
		advance();
		Node* right = factor(symbols, byPassDot);
		if (mError != nullptr) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, type, right);
	}
	return left;
}

Node* Parser::factor(SymbolsParser* symbols, bool byPassDot=false) {
	Token* token = currentToken;
	if (token->mType == Token::Type::PLUS || token->mType == Token::Type::MINUS) {
		advance();
		Node* node = factor(symbols, byPassDot);
		if (mError != nullptr) 
			return nullptr;
		return new UnaryNode(token->mType, node);
	}
	return power(symbols, byPassDot);
}

Node* Parser::power(SymbolsParser* symbols, bool byPassDot=false) {
	Node* left = complement(symbols, byPassDot);
	if (mError != nullptr) 
		return nullptr;
	
	while (currentToken->mType == Token::Type::POWER)
	{
		advance();
		Node* right = factor(symbols, byPassDot);
		if (mError != nullptr) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, Token::Type::POWER, right);
	}
	return left;
}

Node* Parser::complement(SymbolsParser* symbols, bool byPassDot=false) {
	if (currentToken->mType == Token::Type::BITWISE_COMPLEMENT) {
		advance();
		Node* node = factor(symbols, byPassDot);
		if (mError != nullptr)
			return nullptr;
		return new UnaryNode(Token::Type::BITWISE_COMPLEMENT, node);
	}
	return call(symbols, byPassDot);
}

Node* Parser::call(SymbolsParser* symbols, bool byPassDot= false) {
	Node* node = atom(symbols, byPassDot);
	if (mError != nullptr)
		return nullptr;
	if (currentToken->mType == Token::Type::L_PAREN) {
		advance();
		List<Node*>* arguments = nullptr;
		if (currentToken->mType == Token::Type::R_PAREN) {
			advance();
		}
		else {
			arguments = new List<Node*>();
			skipNewLines();
			Node* expression = expr(symbols);
			if (mError != nullptr) {
				delete node;
				return nullptr;
			}
			arguments->add(expression);
			skipNewLines();
			while (currentToken->mType == Token::Type::COMMA) {
				advance();
				skipNewLines();
				if (currentToken->mType == Token::Type::R_PAREN)
					break;
				Node* expression = expr(symbols);
				if (mError != nullptr) {
					delete node;
					delete arguments;
					return nullptr;
				}
				arguments->add(expression);
				skipNewLines();
			}
			if (currentToken->mType != Token::Type::R_PAREN) {
				delete node;
				delete arguments;
				mError = new String("Expected ')'");
				return nullptr;
			}
			advance();
		}
		if (currentToken->mType == Token::Type::L_SQ)
			return subscript(new Call(node, arguments), symbols);
		else if (currentToken->mType == Token::Type::DOT)
			return attribute(new Call(node, arguments), symbols);
		return new Call(node, arguments);
	}
	return node;
}
 
Node* Parser::atom(SymbolsParser* symbols, bool byPassDot = false) {
	Token* token = currentToken;
	if (token->mType == Token::Type::INT_NUMBER) {
		advance();
		return new IntegerNode(StringToInt(token->mValue));
	}
	else if (token->mType == Token::Type::FLOAT_NUMBER) {
		advance();
		return new FloatNode(StringToFloat(token->mValue));
	}
	else if (token->mType == Token::Type::STRING) {
		advance();
		if (currentToken->mType == Token::Type::L_SQ)
			return subscript(new StringNode(new String(token->mValue->ptr)), symbols);
		return new StringNode(new String(token->mValue->ptr));
	}
	else if (token->mType == Token::Type::IDENTIFIER) {
		advance();
		if (currentToken->mType == Token::Type::EQUALS) {
			advance();
			Node* expression = expr(symbols);
			if (mError != nullptr)
				return nullptr;
			return new VarAssign(new String(token->mValue->ptr), expression);
		}
		if (currentToken->mType == Token::Type::L_SQ)
			return subscript(new VarAccess(new String(token->mValue->ptr)), symbols);
		else if (!byPassDot && currentToken->mType == Token::Type::DOT) {
			return attribute(new VarAccess(new String(token->mValue->ptr)), symbols);
		}
		return new VarAccess(new String(token->mValue->ptr));
	}
	else if (token->mType == Token::Type::L_PAREN) {
		advance();
		if (currentToken->mType == Token::Type::R_PAREN) {
			advance();
			return new TupleNode(nullptr);
		}
		Node* expression = expr(symbols);
		if (mError != nullptr)
			return nullptr;

		if (currentToken->mType == Token::Type::R_PAREN) {
			advance();
			return expression;
		}
		else if (currentToken->mType == Token::Type::COMMA) {
			List<Node*>* items = new List<Node*>();
			items->add(expression);
			while (currentToken->mType == Token::Type::COMMA) {
				advance();
				if (currentToken->mType == Token::Type::R_PAREN)
					break;
				Node* item = expr(symbols);
				if (mError != nullptr) {
					delete items;
					return nullptr;
				}
				items->add(item);
			}
			if (currentToken->mType != Token::Type::R_PAREN) {
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
	else if (token->mType == Token::Type::KEYWORD_VAR) {

		advance();
		token = currentToken;
		if (token->mType == Token::Type::IDENTIFIER) {
			advance();
			if (currentToken->mType != Token::Type::EQUALS) {
				mError = new String("Expected '='");
				return nullptr;
			}
			advance();
			Node* expression = expr(symbols);
			if (mError != nullptr)
				return nullptr;

			return new VarAssign(new String(token->mValue->ptr), expression);
		}
		else {
			mError = new String("Expected an identifier");
			return nullptr;
		}
	}
	else if (token->mType == Token::Type::KEYWORD_FOR)
		return for_expr(symbols);
	else if (token->mType == Token::Type::KEYWORD_METHOD)
		return method_expr(symbols);
	else if (token->mType == Token::Type::KEYWORD_RETURN)
		return return_expr(symbols);
	else if (token->mType == Token::Type::KEYWORD_CLASS)
		return class_expr(symbols);
	else if (token->mType == Token::Type::KEYWORD_BREAK) {
		advance();
		return new Node(Node::Type::BREAK);
	}
	else if (token->mType == Token::Type::KEYWORD_CONTINUE) {
		advance();
		return new Node(Node::Type::CONTINUE);
	}
	else if (token->mType == Token::Type::KEYWORD_IF)
		return if_expr(symbols);
	else if (token->mType == Token::Type::L_SQ)
		return list_expr(symbols);

	mError = new String("Expected something!");
	return nullptr;
}

Node* Parser::method_expr(SymbolsParser* symbols) {

	advance(); // method keyword
	Token* identifier = currentToken;
	if (currentToken->mType != Token::Type::IDENTIFIER) {
		identifier = nullptr;
	} else
		advance();
	if (currentToken->mType != Token::Type::L_PAREN) {
		mError = new String("Expected '('");
		return nullptr;
	}
	advance();
	List<String*>* ids = new List<String*>();
	SymbolsParser* newSymbols = new SymbolsParser(symbols);
	if (currentToken->mType == Token::Type::IDENTIFIER) {
		
		ids->add(new String(currentToken->mValue->ptr));
		advance();
		while (currentToken->mType == Token::Type::COMMA) {
			advance();
			if (currentToken->mType == Token::Type::IDENTIFIER) {
			
				ids->add(new String(currentToken->mValue->ptr));
				advance();
			}
		}
	}

	if (currentToken->mType != Token::Type::R_PAREN) {
		mError = new String("Expected ')'");
		return nullptr;
	}
	advance();
	
	if (currentToken->mType == Token::Type::COLON) {
		advance();
		skipNewLines();
		//int id = symbols->setSymbolIndex(identifier->mValue);
		Node* body = expr(newSymbols);
		if (mError != nullptr)
			return nullptr;
		return new Method(identifier == nullptr ? nullptr : new String(identifier->mValue->ptr), body, ids);
	}
	else {
		skipNewLines();
		if (currentToken->mType == Token::Type::L_BRACE) {
			advance();
			skipNewLines();
			//int id = symbols->setSymbolIndex(identifier->mValue);
			Node* node = block(newSymbols, Token::Type::R_BRACE);
			advance(); //closing brace
			if (mError != nullptr)
				return nullptr;
			return new Method(identifier == nullptr ? nullptr : new String(identifier->mValue->ptr), node, ids);
		}
		mError = new String("Expected ':' or '{'");
		return nullptr;
	}
	return nullptr;
}

Node* Parser::for_expr(SymbolsParser* symbols) {
	Node* start, * to, * step = nullptr;
	advance(); // for keyword
	Token* identifier = currentToken;
	if (currentToken->mType != Token::Type::IDENTIFIER)
	{
		mError = new String("Expected an identifier (for loop)");
		printf("%d\n", currentToken->mType);
		return nullptr;
	}
	advance();

	if (currentToken->mType != Token::Type::EQUALS)
	{
		mError = new String("Expected '='");
		return nullptr;
	}
	advance();

	start = bitwise_or(symbols);
	if (mError != nullptr)
		return nullptr;
	if (currentToken->mType != Token::Type::KEYWORD_TO)
	{
		mError = new String("Expected 'to'");
		delete start;
		return nullptr;
	}
	advance();

	to = bitwise_or(symbols);
	if (mError != nullptr) {
		delete start;
		return nullptr;
	}

	if (currentToken->mType == Token::Type::KEYWORD_STEP) {
		advance();
		step = bitwise_or(symbols);
		if (mError != nullptr) {
			delete start;
			delete to;
			return nullptr;
		}
	}
	
	if (currentToken->mType == Token::Type::COLON) {
		advance();
		skipNewLines();
		//int id = symbols->setSymbolIndex(identifier->mValue);
		Node* body = expr(symbols);
		if (mError != nullptr)
		{
			delete start;
			delete to;
			if (step != nullptr)
				delete step;
			return nullptr;
		}
		return new ForLoop(new String(identifier->mValue->ptr), start, to, step, body);
	}
	else {
		skipNewLines();
		if (currentToken->mType == Token::Type::L_BRACE) {
			advance();
			skipNewLines();
			//int id = symbols->setSymbolIndex(identifier->mValue);
			Node* node = block(symbols, Token::Type::R_BRACE);
			advance(); //closing brace
			if (mError != nullptr)
			{
				delete start;
				delete to;
				if (step != nullptr)
					delete step;
				return nullptr;
			}
			return new ForLoop(new String(identifier->mValue->ptr), start, to, step, node);
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

Node* Parser::return_expr(SymbolsParser* symbols) {
	advance();
	Node* body = expr(symbols);
	if (mError != nullptr)
		return nullptr;
	return new Return(body);
}

Node* Parser::if_expr(SymbolsParser* symbols) {
	advance();
	List<IfCase*>* cases = new List<IfCase*>();
	Node* condition = expr(symbols);
	if (mError != nullptr)
		return nullptr;

	skipNewLines();
	if (currentToken->mType == Token::Type::COLON) {
		advance();
		skipNewLines();
		Node* body = expr(symbols);
		if (mError != nullptr) {
			delete condition;
			return nullptr;
		}
		cases->add(new IfCase(condition, body));
		skipNewLines();
	}
	else if (currentToken->mType == Token::Type::L_BRACE) {
		advance();
		skipNewLines();
		Node* body = block(symbols, Token::Type::R_BRACE);
		advance(); //closing brace
		if (mError != nullptr) {
			delete condition;
			return nullptr;
		}
		cases->add(new IfCase(condition, body));
		skipNewLines();
	}

	while (currentToken->mType == Token::Type::KEYWORD_ELIF) {
		advance();
		Node* elifCondition = expr(symbols);
		if (mError != nullptr) {
			delete cases;
			return nullptr;
		}

		skipNewLines();
		if (currentToken->mType == Token::Type::COLON) {
			advance();
			skipNewLines();
			Node* elifBody = expr(symbols);
			if (mError != nullptr) {
				delete elifCondition;
				delete cases;
				return nullptr;
			}
			cases->add(new IfCase(elifCondition, elifBody));
			skipNewLines();
		}
		else if (currentToken->mType == Token::Type::L_BRACE) {
			advance();
			skipNewLines();
			Node* elifBody = block(symbols, Token::Type::R_BRACE);
			advance(); //closing brace
			if (mError != nullptr) {
				delete elifCondition;
				delete cases;
				return nullptr;
			}
			cases->add(new IfCase(elifCondition, elifBody));
			skipNewLines();
		}
	}

	if (currentToken->mType == Token::Type::KEYWORD_ELSE) {
		advance();
		skipNewLines();
		if (currentToken->mType == Token::Type::COLON) {
			advance();
			skipNewLines();
			Node* elseBody = expr(symbols);
			if (mError != nullptr) {
				delete cases;
				return nullptr;
			}
			skipNewLines();
			return new If(cases, elseBody);
		}
		else if (currentToken->mType == Token::Type::L_BRACE) {
			advance();
			skipNewLines();
			Node* elseBody = block(symbols, Token::Type::R_BRACE);
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

Node* Parser::list_expr(SymbolsParser* symbols) {
	advance();
	if (currentToken->mType == Token::Type::R_SQ) {
		advance();
		return new ListNode(nullptr);
	}
	Node* expression = expr(symbols);
	if (mError != nullptr)
		return nullptr;
	List<Node*>* items = new List<Node*>();
	items->add(expression);

	while (currentToken->mType == Token::Type::COMMA) {
		advance();
		if (currentToken->mType == Token::Type::R_SQ)
			break;
		Node* expression = expr(symbols);
		if (mError != nullptr) {
			delete items;
			return nullptr;
		}
		items->add(expression);
	}

	if (currentToken->mType == Token::Type::R_SQ) {
		advance();
		return new ListNode(items);
	}
	if (currentToken->mType == Token::Type::L_SQ)
		return subscript(new ListNode(items), symbols);
	mError = new String("Expected ']'");
	delete items;
	return nullptr;
}

Node* Parser::subscript(Node* base, SymbolsParser* symbols) {
	advance();
	Node* expression = expr(symbols);
	if (mError != nullptr)
		return nullptr;

	if (currentToken->mType != Token::Type::R_SQ) {
		advance();
		mError = new String("Expected ']'");
		delete expression;
		return nullptr;
	}
	advance();

	if (currentToken->mType == Token::Type::L_SQ) 
		return subscript(new SubscriptAccessNode(base, expression), symbols);
		
	if (currentToken->mType == Token::Type::EQUALS) {
		advance();
		Node* node = expr(symbols);
		if (mError != nullptr) {
			delete expression;
			return nullptr;
		}
		return new SubscriptAssignNode(new SubscriptAccessNode(base, expression), node);
	}
	return new SubscriptAccessNode(base, expression);
}

Node* Parser::class_expr(SymbolsParser* symbols) {
	advance();
	Token* identifier = currentToken;
	if (identifier->mType != Token::Type::IDENTIFIER) {
		mError = new String("Expected an identifier");
		return nullptr;
	}
	advance();
	skipNewLines();
	if (currentToken->mType == Token::Type::L_BRACE) {
		advance();
		skipNewLines();
		//int id = symbols->setSymbolIndex(identifier->mValue);
		Node* node = block(symbols, Token::Type::R_BRACE);
		advance(); //closing brace
		if (mError != nullptr)
			return nullptr;
		return new ClassNode(new String(identifier->mValue->ptr), node);
	}
	mError = new String("Expected '{'");
	return nullptr;
}

Node* Parser::attribute(Node* base, SymbolsParser* symbols) {
	advance();
	
	Node* node = call(symbols, true);
	if (mError != nullptr)
		return nullptr;
	if (currentToken->mType == Token::Type::DOT)
		return attribute(new AttributeNode(base, node), symbols);
	return new AttributeNode(base, node);
}