#pragma once

#include "string/string.h"
#include "../values/value.h"
#include "list/list.cpp"

class SymbolsParser {
public:
	SymbolsParser();
	SymbolsParser(SymbolsParser* parent);
	~SymbolsParser();
	SymbolsParser* mParent = nullptr;
	int getSymbolIndex(String* name);
	int setSymbolIndex(String* name);
	List<String*>* mSymbols;
};
