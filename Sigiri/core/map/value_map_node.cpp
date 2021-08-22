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

#include "value_map_node.h"

ValueMapNode::ValueMapNode(int hash_code, String* key, Value* value) {
	this->hash_code = hash_code;
	this->key = key;
	this->value = value;
	next = nullptr;
}

ValueMapNode::ValueMapNode() {
	hash_code = 0;
	key = nullptr;
	value = nullptr;
	next = nullptr;
}

ValueMapNode::~ValueMapNode() {
	delete value;
}