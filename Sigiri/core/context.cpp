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
		if (mSymbolNames->get(i)->Compare(id->ptr))
			mSymbols->unlinkItem(i);
	}
}

Value* SymbolsRuntime::getSymbol(String* id) {
	for (size_t i = 0; i < mSymbolCount; i++)
	{
		//printf("%s(%s), ", mSymbolNames->get(i)->mPtr, id->mPtr);
		if (mSymbolNames->get(i)->Compare(id))
			return mSymbols->get(i);
		
	}
	if (mParent != nullptr)
		return mParent->getSymbol(id);
	return nullptr;
}

Value* SymbolsRuntime::getDirectSymbol(String* id) {
	for (size_t i = 0; i < mSymbolCount; i++)
	{
		if (mSymbolNames->get(i)->Compare(id))
			return mSymbols->get(i);
	}
	return nullptr;
}

void SymbolsRuntime::setSymbol(String* id, Value* value) {
	for (size_t i = 0; i < mSymbolCount; i++)
	{
		if (mSymbolNames->get(i)->Compare(id->ptr))
		{
			delete mSymbols->get(i);
			mSymbols->add(i, value);
			//printf("var update %s\n", id->mPtr);
			return;
		}
	}
	mSymbols->add(value);
	mSymbolNames->add(id);
	//printf("var set %s\n", id->mPtr);
	mSymbolCount++;
}

SymbolsRuntime::~SymbolsRuntime() {
	mSymbolNames->keepItemsAlive = true;
	delete mSymbolNames;
	delete mSymbols;
	if (returnValue != nullptr && !keepReturnValue)
		delete returnValue;
}