#include "symbol_table.h"

SymbolsParser::SymbolsParser() {
	mSymbols = new List<String*>();
}

SymbolsParser::SymbolsParser(SymbolsParser* parent) {
	mSymbols = new List<String*>();
	mParent = parent;
}

int SymbolsParser::getSymbolIndex(String* name) {
	int count = mSymbols->count();
	for (size_t i = 0; i < count; i++)
	{
		if (mSymbols->Get(i)->Compare(name) == 1)
			return i;
	}
	if (mParent != nullptr)
		return mParent->getSymbolIndex(name);
	return -1;
}

int SymbolsParser::setSymbolIndex(String* name) {
	int count = mSymbols->count();
	for (size_t i = 0; i < count; i++)
	{
		if (mSymbols->Get(i)->Compare(name) == 1)
			return i;
	}
	mSymbols->Add(name->Clone());
	return count;
}

SymbolsParser::~SymbolsParser() {

}

//----------------------------------------------------------------------------------------------
