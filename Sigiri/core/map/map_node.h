#pragma once

#include "../string/string.h"
#include "../../values/value.h"

class MapNode {
public:
	int hash_code_;
	String* key_;
	Value* value_;
	MapNode() { next_ = nullptr; }
	MapNode(int hashCode, String *key, Value* value);
	MapNode* next_;
};
