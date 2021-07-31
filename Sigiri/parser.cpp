#include "include/parser.h"
#include "include/string.h"
#include <cstdio>

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
	Node* left = compare(symbols);
	if (mError != nullptr)
		return nullptr;
	while (currentToken->mType == Token::Type::BOOLEAN_AND || currentToken->mType == Token::Type::BOOLEAN_OR)
	{
		Token::Type type = currentToken->mType;
		advance();
		Node* right = compare(symbols);
		if (mError != nullptr) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, type, right);
	}
	return left;
}

Node* Parser::compare(SymbolsParser* symbols) {
	if (currentToken->mType == Token::Type::BOOLEAN_NOT) {
		advance();
		return new UnaryNode(Token::Type::BOOLEAN_NOT, compare(symbols));
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
	Node* left = arithmetic(symbols);
	if (mError != nullptr)
		return nullptr;
	while (currentToken->mType == Token::Type::LEFT_SHIFT || currentToken->mType == Token::Type::RIGHT_SHIFT)
	{
		Token::Type type = currentToken->mType;
		advance();
		Node* right = arithmetic(symbols);
		if (mError != nullptr) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, type, right);
	}
	return left;
}

Node* Parser::arithmetic(SymbolsParser* symbols) {
	Node* left = term(symbols);
	if (mError != nullptr)
		return nullptr;
	while (currentToken->mType == Token::Type::PLUS || currentToken->mType == Token::Type::MINUS)
	{
		Token::Type type = currentToken->mType;
		advance();
		Node* right = term(symbols);
		if (mError != nullptr) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, type, right);
	}
	return left;
}

Node* Parser::term(SymbolsParser* symbols) {
	Node* left = factor(symbols);
	if (mError != nullptr) 
		return nullptr;
	while (currentToken->mType == Token::Type::ASTERIX || currentToken->mType == Token::Type::FW_SLASH || currentToken->mType == Token::Type::MODULUS)
	{
		Token::Type type = currentToken->mType;
		advance();
		Node* right = factor(symbols);
		if (mError != nullptr) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, type, right);
	}
	return left;
}

Node* Parser::factor(SymbolsParser* symbols) {
	Token* token = currentToken;
	if (token->mType == Token::Type::PLUS || token->mType == Token::Type::MINUS) {
		advance();
		Node* node = factor(symbols);
		if (mError != nullptr) 
			return nullptr;
		return new UnaryNode(token->mType, node);
	}
	return power(symbols);
}

Node* Parser::power(SymbolsParser* symbols) {
	Node* left = complement(symbols);
	if (mError != nullptr) 
		return nullptr;
	
	while (currentToken->mType == Token::Type::POWER)
	{
		advance();
		Node* right = factor(symbols);
		if (mError != nullptr) {
			delete left;
			return nullptr;
		}
		left = new BinaryNode(left, Token::Type::POWER, right);
	}
	return left;
}

Node* Parser::complement(SymbolsParser* symbols) {
	if (currentToken->mType == Token::Type::BITWISE_COMPLEMENT) {
		advance();
		Node* node = factor(symbols);
		if (mError != nullptr)
			return nullptr;
		return new UnaryNode(Token::Type::BITWISE_COMPLEMENT, node);
	}
	return call(symbols);
}

Node* Parser::call(SymbolsParser* symbols) {
	Node* node = atom(symbols);
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
			Node* expression = expr(symbols);
			if (mError != nullptr) {
				delete node;
				return nullptr;
			}
			arguments->add(expression);
			while (currentToken->mType == Token::Type::COMMA) {
				advance();
				Node* expression = expr(symbols);
				if (mError != nullptr) {
					delete node;
					delete arguments;
					return nullptr;
				}
				arguments->add(expression);
			}
			if (currentToken->mType != Token::Type::R_PAREN) {
				delete node;
				delete arguments;
				mError = new String("Expected ')'");
				return nullptr;
			}
			advance();
		}
		return new Call(node, arguments);
	}
	return node;
}
 
Node* Parser::atom(SymbolsParser* symbols) {
	Token* token = currentToken;
	if (token->mType == Token::Type::INT_NUMBER) {
		advance();
		return new IntegerNode(strToInt(token->mValue));
	}
	else if (token->mType == Token::Type::FLOAT_NUMBER) {
		advance();
		return new FloatNode(strToFloat(token->mValue));
	}
	else if (token->mType == Token::Type::STRING) {
		advance();
		if (currentToken->mType == Token::Type::L_SQ)
			return subscript(new StringNode(new String(token->mValue->mPtr)), symbols);
		return new StringNode(new String(token->mValue->mPtr));
	}
	else if (token->mType == Token::Type::IDENTIFIER) {
		advance();
		if (currentToken->mType == Token::Type::EQUALS) {
			advance();
			Node* expression = expr(symbols);
			if (mError != nullptr)
				return nullptr;
			return new VarAssign(new String(token->mValue->mPtr), expression);
		}
		if (currentToken->mType == Token::Type::L_SQ)
			return subscript(new VarAccess(new String(token->mValue->mPtr)), symbols);
		return new VarAccess(new String(token->mValue->mPtr));
	}
	else if (token->mType == Token::Type::L_PAREN) {
		advance();
		Node* expression = expr(symbols);
		if (mError != nullptr)
			return nullptr;

		if (currentToken->mType != Token::Type::R_PAREN) {
			mError = new String("Expected ')'");
			delete expression;
			return nullptr;
		}
		advance();
		return expression;
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

			return new VarAssign(new String(token->mValue->mPtr), expression);
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
		
		ids->add(new String(currentToken->mValue->mPtr));
		advance();
		while (currentToken->mType == Token::Type::COMMA) {
			advance();
			if (currentToken->mType == Token::Type::IDENTIFIER) {
			
				ids->add(new String(currentToken->mValue->mPtr));
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
		return new Method(identifier == nullptr ? nullptr : new String(identifier->mValue->mPtr), body, ids);
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
			return new Method(identifier == nullptr ? nullptr : new String(identifier->mValue->mPtr), node, ids);
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
		return new ForLoop(new String(identifier->mValue->mPtr), start, to, step, body);
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
			return new ForLoop(new String(identifier->mValue->mPtr), start, to, step, node);
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

	if (currentToken->mType == Token::Type::L_SQ) {
		return subscript(new SubscriptAccessNode(base, expression), symbols);
	}
		
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