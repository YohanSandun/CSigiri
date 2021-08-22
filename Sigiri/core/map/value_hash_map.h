//--------------------------------------------------------------------------
// Copyright 2021 Yohan Sandun
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//--------------------------------------------------------------------------

#ifndef VALUE_HASH_MAP_H
#define VALUE_HASH_MAP_H

#include "value_map_node.h"

class ValueHashMap {
private:
    const float kLoadFactor = 0.75f;
    int threshold_;
    int size_;
    int length_;
    ValueMapNode** nodes_;
    void ExpandArray();
    void PutNode(ValueMapNode** nodes, ValueMapNode* node);

public:
    ValueHashMap(int size = 16);
    ~ValueHashMap();
    void Put(String* key, Value* value);
    Value* Get(String* key);
};

#endif