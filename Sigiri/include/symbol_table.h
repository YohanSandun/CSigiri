#pragma once

#include "string.h"
#include "value.h"
#include "../libs/list.cpp"

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
