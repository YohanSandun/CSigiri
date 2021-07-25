#pragma once

#include "../libs/list.cpp"
#include "value.h"

class SymbolsRuntime {
public:
	int mSymbolCount = 0;
	SymbolsRuntime();
	SymbolsRuntime(SymbolsRuntime* parent);
	~SymbolsRuntime();
	SymbolsRuntime* mParent = nullptr;
	Value* getSymbol(String* id);
	void setSymbol(String* id, Value* value);
	List<Value*>* mSymbols;
	List<String*>* mSymbolNames;
};