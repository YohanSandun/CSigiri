#pragma once

#include "map/hash_map.h"
#include "../values/value.h"

class Context {
public:
	int mSymbolCount = 0;
	bool mReturn = false;
	bool mBreak = false;
	bool mContinue = false;
	bool keepReturnValue = false;
	Context();
	Context(Context* parent);
	~Context();
	Context* mParent = nullptr;
	Value* getSymbol(String* id);
	Value* getDirectSymbol(String* id);
	Value* returnValue = nullptr;
	void setSymbol(String* id, Value* value);
	void unlinkValue(String* id);
	//List<Value*>* mSymbols;
	//List<String*>* mSymbolNames;
	HashMap* map_;
};