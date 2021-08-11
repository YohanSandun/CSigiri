#pragma once

#include "../string/string.h"
#include "map_node.h"

// TODO: deconstructors

class HashMap {
private:
    const float kLoadFactor = 0.75f;
    int threshold_;
    int size_;
    int length_;
    MapNode** nodes_;
    void ExpandArray();
    void PutNode(MapNode** nodes, MapNode* node);

public:
    HashMap(int size = 16);
    void Put(String* key, Value* value);
    Value* Get(String* key);
};