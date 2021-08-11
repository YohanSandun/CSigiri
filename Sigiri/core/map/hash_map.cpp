#include "hash_map.h"

//TODO: implement delete and contains method.

HashMap::HashMap(int size) {
	size_ = size;
	threshold_ = (int)(size_ * kLoadFactor);
	length_ = 0;
	nodes_ = new MapNode*[size_]();
}

HashMap::~HashMap() {
	for (size_t i = 0; i < size_; i++)
	{
		if (nodes_[i] != nullptr) {
			MapNode* node = nodes_[i];
			while (node != nullptr)
			{
				MapNode* temp = node;
				node = node->next_;
				delete temp;
			}
		}
	}
	delete nodes_;
}

void HashMap::Put(String* key, Value* value) {
	int index = 0;
	int hash = 0;
	if (key != nullptr) {
		hash = key->hash_code_;
		index = hash & (size_ - 1);
	}
	if (nodes_[index] == nullptr) {
		nodes_[index] = new MapNode(hash, key, value);
		length_++;
		if (length_ >= threshold_)
			ExpandArray();
	}
	else {
		MapNode* node = nodes_[index];
		while (node != nullptr) {
			if (node->key_->Compare(key)) {
				MapNode* next = node->next_;
				delete node;
				node = new MapNode(hash, key, value);
				node->next_ = next;
				return;
			}
			if (node->next_ == nullptr) {
				node->next_ = new MapNode(hash, key, value);
				return;
			}
			node = node->next_;
		}
	}
}

Value* HashMap::Get(String* key) {
	int index = 0;
	if (key != nullptr) {
		int hash = key->hash_code_;
		index = hash & (size_ - 1);
	}
	if (nodes_[index] != nullptr) {
		MapNode* node = nodes_[index];
		while (node != nullptr) {
			if (node->key_->Compare(key)) 
				return node->value_;
			node = node->next_;
		}
	}
	return nullptr;
}

void HashMap::ExpandArray() {
	length_ = 0;
	int oldSize = size_;
	size_ *= 2;
	threshold_ = (int)(size_ * kLoadFactor);
	MapNode** newNodes = new MapNode*[size_]();

	for (size_t i = 0; i < oldSize; i++)
	{
		if (nodes_[i] != nullptr) {
			MapNode* node = nodes_[i];
			while (node != nullptr)
			{
				MapNode* temp = node;
				node = node->next_;
				PutNode(newNodes, temp);
			}
		}
	}
	delete[] nodes_;
	nodes_ = newNodes;
}

void HashMap::PutNode(MapNode** nodes, MapNode* node) {
	node->next_ = nullptr;
	int index = node->hash_code_ & (size_ - 1);
	if (nodes[index] == nullptr) {
		nodes[index] = node;
		length_++;
		if (length_ >= threshold_)
			ExpandArray();
	}
	else
	{
		MapNode* n = nodes[index];
		while (n != nullptr) {
			if (n->next_ == nullptr) {
				n->next_ = new MapNode(node->hash_code_, node->key_, node->value_);
				return;
			}
			n = n->next_;
		}
	}
}