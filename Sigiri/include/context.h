#pragma once

#include "../libs/list.cpp"
#include "value.h"

class SymbolsRuntime {
public:
	int mSymbolCount = 0;
	bool mReturn = false;
	SymbolsRuntime();
	SymbolsRuntime(SymbolsRuntime* parent);
	~SymbolsRuntime();
	SymbolsRuntime* mParent = nullptr;
	Value* getSymbol(String* id);
	Value* getDirectSymbol(String* id);
	Value* returnValue = nullptr;
	void setSymbol(String* id, Value* value);
	List<Value*>* mSymbols;
	List<String*>* mSymbolNames;
};