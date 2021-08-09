#include "context.h"

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

void SymbolsRuntime::unlinkValue(String* id) {
	for (size_t i = 0; i < mSymbolCount; i++)
	{
		if (mSymbolNames->Get(i)->Compare(id->ptr))
			mSymbols->UnlinkItem(i);
	}
}

Value* SymbolsRuntime::getSymbol(String* id) {
	for (size_t i = 0; i < mSymbolCount; i++)
	{
		//printf("%s(%s), ", mSymbolNames->Get(i)->ptr, id->ptr);
		if (mSymbolNames->Get(i)->Compare(id))
			return mSymbols->Get(i);
		
	}
	if (mParent != nullptr)
		return mParent->getSymbol(id);
	return nullptr;
}

Value* SymbolsRuntime::getDirectSymbol(String* id) {
	for (size_t i = 0; i < mSymbolCount; i++)
	{
		if (mSymbolNames->Get(i)->Compare(id))
			return mSymbols->Get(i);
	}
	return nullptr;
}

void SymbolsRuntime::setSymbol(String* id, Value* value) {
	for (size_t i = 0; i < mSymbolCount; i++)
	{
		if (mSymbolNames->Get(i)->Compare(id->ptr))
		{
			delete mSymbols->Get(i);
			mSymbols->Add(i, value);
			//printf("var update %s\n", id->ptr);
			return;
		}
	}
	mSymbols->Add(value);
	mSymbolNames->Add(id);
	//printf("var set %s\n", id->ptr);
	mSymbolCount++;
}

SymbolsRuntime::~SymbolsRuntime() {
	mSymbolNames->keep_items_alive_ = true;
	delete mSymbolNames;
	delete mSymbols;
	if (returnValue != nullptr && !keepReturnValue)
		delete returnValue;
}