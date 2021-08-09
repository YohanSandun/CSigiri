#pragma once

#include "list/list.cpp"
#include "../values/value.h"

class SymbolsRuntime {
public:
	int mSymbolCount = 0;
	bool mReturn = false;
	bool mBreak = false;
	bool mContinue = false;
	bool keepReturnValue = false;
	SymbolsRuntime();
	SymbolsRuntime(SymbolsRuntime* parent);
	~SymbolsRuntime();
	SymbolsRuntime* mParent = nullptr;
	Value* getSymbol(String* id);
	Value* getDirectSymbol(String* id);
	Value* returnValue = nullptr;
	void setSymbol(String* id, Value* value);
	void unlinkValue(String* id);
	List<Value*>* mSymbols;
	List<String*>* mSymbolNames;
};