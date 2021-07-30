#pragma once

#include "../libs/list.cpp"
#include "token.h"

class Node {
public:
	enum class Type
	{
		INTEGER,
		FLOAT,
		UNARY,
		BINARY,
		VAR_ASSIGN,
		VAR_ACCESS,
		BLOCK,
		FOR_LOOP,
		METHOD,
		CALL,
		RETURN,
		IF
	} mType;
	Node(Type type);
	virtual ~Node();
	virtual void toString();
};

class IntegerNode : public Node {
public:
	IntegerNode(int value);
	~IntegerNode();
	void toString();
	int mValue;
};

class FloatNode : public Node {
public:
	FloatNode(double value);
	~FloatNode();
	void toString();
	double mValue;
};

class UnaryNode : public Node {
public:
	~UnaryNode();
	UnaryNode(Token::Type type, Node* node);
	Node* mNode;
	Token::Type mOpType;
	void toString();
};

class BinaryNode : public Node {
public:
	~BinaryNode();
	BinaryNode(Node* left, Token::Type type, Node* right);
	Node* mLeft, * mRight;
	Token::Type mOpType;
	void toString();
};

class VarAssign : public Node {
public:
	~VarAssign();
	VarAssign(String* id, Node* node);
	Node* mNode;
	String* mId;
	void toString();
};

class VarAccess : public Node {
public:
	~VarAccess();
	VarAccess(String* id);
	String* mId;
	void toString();
};

class Block : public Node {
public:
	~Block();
	Block(List<Node*>* statements);
	List<Node*>* mStatements;
	void toString();
};

class ForLoop : public Node {
public:
	~ForLoop();
	ForLoop(String* id, Node* start, Node* to, Node* step, Node* body);
	Node* mStart, * mTo, * mStep, * mBody; 
	String* mId;
};

class Method : public Node {
public:
	~Method();
	Method(String* id, Node* body, List<String*>* params);
	List<String*>* mParams;
	String* mId;
	Node* mBody;
};

class Call : public Node {
public:
	Call(Node* base, List<Node*>* args);
	~Call();
	Node* mBase;
	List<Node*>* mArgs;
};

class Return : public Node {
public:
	Return(Node* node);
	~Return();
	Node* mNode;
};

class IfCase {
public:
	IfCase(Node* condition, Node* body);
	~IfCase();
	Node* mCondition, * mBody;
};

class If : public Node {
public:
	If(List<IfCase*>* cases, Node* elseCase);
	~If();
	List<IfCase*>* mCases;
	Node* mElseCase;
};
