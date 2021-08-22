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

#include "value_hash_map.h"

//TODO: implement delete and contains method.

ValueHashMap::ValueHashMap(int size) {
	size_ = size;
	threshold_ = (int)(size_ * kLoadFactor);
	length_ = 0;
	nodes_ = new ValueMapNode * [size_]();
}

ValueHashMap::~ValueHashMap() {
	for (size_t i = 0; i < size_; i++)
	{
		if (nodes_[i] != nullptr) {
			ValueMapNode* node = nodes_[i];
			while (node != nullptr)
			{
				ValueMapNode* temp = node;
				node = node->next;
				delete temp;
			}
		}
	}
	delete nodes_;
}

void ValueHashMap::Put(String* key, Value* value) {
	int index = 0;
	int hash = 0;
	if (key != nullptr) {
		hash = key->hash_code_;
		index = hash & (size_ - 1);
	}
	if (nodes_[index] == nullptr) {
		nodes_[index] = new ValueMapNode(hash, key, value);
		length_++;
		if (length_ >= threshold_)
			ExpandArray();
	}
	else {
		ValueMapNode* node = nodes_[index];
		if (node->key->Compare(key)) {
			ValueMapNode* next = node->next;
			delete node;
			node = new ValueMapNode(hash, key, value);
			node->next = next;
			nodes_[index] = node;
			return;
		}
		ValueMapNode* previous_node = node;
		node = node->next;
		while (node != nullptr) {
			if (node->key->Compare(key)) {
				ValueMapNode* next = node->next;
				delete node;
				node = new ValueMapNode(hash, key, value);
				node->next = next;
				previous_node->next = node;
				return;
			}
			if (node->next == nullptr) {
				node->next = new ValueMapNode(hash, key, value);
				return;
			}
			previous_node = node;
			node = node->next;
		}
		previous_node->next = new ValueMapNode(hash, key, value);
	}
}

Value* ValueHashMap::Get(String* key) {
	int index = 0;
	if (key != nullptr) {
		int hash = key->hash_code_;
		index = hash & (size_ - 1);
	}
	if (nodes_[index] != nullptr) {
		ValueMapNode* node = nodes_[index];
		while (node != nullptr) {
			if (node->key->Compare(key))
				return node->value;
			node = node->next;
		}
	}
	return nullptr;
}

void ValueHashMap::ExpandArray() {
	length_ = 0;
	int oldSize = size_;
	size_ *= 2;
	threshold_ = (int)(size_ * kLoadFactor);
	ValueMapNode** new_nodes = new ValueMapNode * [size_]();

	for (size_t i = 0; i < oldSize; i++)
	{
		if (nodes_[i] != nullptr) {
			ValueMapNode* node = nodes_[i];
			while (node != nullptr)
			{
				ValueMapNode* temp = node;
				node = node->next;
				PutNode(new_nodes, temp);
			}
		}
	}
	delete[] nodes_;
	nodes_ = new_nodes;
}

void ValueHashMap::PutNode(ValueMapNode** nodes, ValueMapNode* node) {
	node->next = nullptr;
	int index = node->hash_code & (size_ - 1);
	if (nodes[index] == nullptr) {
		nodes[index] = node;
		length_++;
		if (length_ >= threshold_)
			ExpandArray();
	}
	else
	{
		ValueMapNode* n = nodes[index];
		while (n != nullptr) {
			if (n->next == nullptr) {
				n->next = new ValueMapNode(node->hash_code, node->key, node->value);
				return;
			}
			n = n->next;
		}
	}
}