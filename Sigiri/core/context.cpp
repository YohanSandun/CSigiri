#include "context.h"

Context::Context() {
	mParent = nullptr;
	//mSymbols = new List<Value*>();
	//mSymbolNames = new List<String*>();
	map_ = new HashMap();
	mSymbolCount = 0;
}

Context::Context(Context* parent) {
	mParent = parent;
	//mSymbols = new List<Value*>();
	//mSymbolNames = new List<String*>();
	map_ = new HashMap();
	mSymbolCount = 0;
}

void Context::unlinkValue(String* id) {
	/*
	for (size_t i = 0; i < mSymbolCount; i++)
	{
		if (mSymbolNames->Get(i)->Compare(id->ptr))
			mSymbols->UnlinkItem(i);
	}
	*/
}

Value* Context::getSymbol(String* id) {
	Value* value = map_->Get(id);
	if (value != nullptr)
		return value;
	/*for (size_t i = 0; i < mSymbolCount; i++)
	{
		if (mSymbolNames->Get(i)->Compare(id))
			return mSymbols->Get(i);
		
	}*/
	if (mParent != nullptr)
		return mParent->getSymbol(id);
	return nullptr;
}

Value* Context::getDirectSymbol(String* id) {
	return map_->Get(id);
	/*for (size_t i = 0; i < mSymbolCount; i++)
	{
		if (mSymbolNames->Get(i)->Compare(id))
			return mSymbols->Get(i);
	}
	return nullptr;*/
}

void Context::setSymbol(String* id, Value* value) {
	map_->Put(id, value);
	//for (size_t i = 0; i < mSymbolCount; i++)
	//{
	//	if (mSymbolNames->Get(i)->Compare(id->ptr))
	//	{
	//		delete mSymbols->Get(i);
	//		mSymbols->Add(i, value);
	//		//printf("var update %s\n", id->ptr);
	//		return;
	//	}
	//}
	//mSymbols->Add(value);
	//mSymbolNames->Add(id);
	////printf("var set %s\n", id->ptr);
	//mSymbolCount++;
}

Context::~Context() {
	//mSymbolNames->keep_items_alive_ = true;
	//delete mSymbolNames;
	//delete mSymbols;
	if (returnValue != nullptr && !keepReturnValue)
		delete returnValue;
}