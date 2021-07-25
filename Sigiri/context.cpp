#include "include/context.h"

SymbolsRuntime::SymbolsRuntime() {
	mParent = nullptr;
	mSymbols = new List<Value*>();
	mSymbolNames = new List<String*>();
	mSymbolCount = 0;
}

SymbolsRuntime::SymbolsRuntime(SymbolsRuntime* parent) {
	mParent = parent;
	mSymbols = new List<Value*>();
	mSymbolNames = new List<String*>();
	mSymbolCount = 0;
}

Value* SymbolsRuntime::getSymbol(String* id) {
	for (size_t i = 0; i < mSymbolCount; i++)
	{
		if (mSymbolNames->get(i)->compare(id->mPtr))
			return mSymbols->get(i);
	}
	if (mParent != nullptr)
		return mParent->getSymbol(id);
	return nullptr;
}

void SymbolsRuntime::setSymbol(String* id, Value* value) {
	for (size_t i = 0; i < mSymbolCount; i++)
	{
		if (mSymbolNames->get(i)->compare(id->mPtr))
		{
			delete mSymbols->get(i);
			mSymbols->add(i, value);
			return;
		}
	}
	mSymbols->add(value);
	mSymbolNames->add(id);
	mSymbolCount++;
}

SymbolsRuntime::~SymbolsRuntime() {
	delete mSymbolNames;
	delete mSymbols;
}