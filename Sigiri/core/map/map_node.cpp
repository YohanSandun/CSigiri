#include "map_node.h"

MapNode::MapNode(int hashCode, String *key, Value* value) {
	hash_code_ = hashCode;
	key_ = key;
	value_ = value;
	next_ = nullptr;
}

MapNode::MapNode() {
	next_ = nullptr;
}

MapNode::~MapNode() {
	delete value_;
}