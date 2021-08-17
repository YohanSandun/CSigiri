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

#include "list.h"
#include "core/string/string.h"
#include "core/lexer/token.h"

template <typename T>
List<T>::List() {
	size_ = kDefaultSize;
	current_index_ = -1;
	ptr_ = new T[size_];
}

template <typename T>
List<T>::List(uint32 size) {
	size_ = size;
	current_index_ = -1;
	ptr_ = new T[size_];
}

template <typename T>
List<T>::~List() {
	if (!keep_items_alive_) {
		for (size_t i = 0; i <= current_index_; i++) {
			if (ptr_[i] != nullptr)
				delete ptr_[i];
		}
	}
	delete[] ptr_;
}

template <typename T>
void List<T>::Add(T item) {
	EnsureMemory();
	ptr_[current_index_] = item;
}

template <typename T>
void List<T>::Add(uint32 index, T item) {
	ptr_[index] = item;
}

template <typename T>
T List<T>::Get(uint32 index) {
	return ptr_[index];
}

template <typename T>
void List<T>::EnsureMemory() {
	if (++current_index_ == size_) {
		size_ += kDefaultSize;
		T* new_ptr = new T[size_];
		for (size_t i = 0; i < current_index_; i++)
			new_ptr[i] = ptr_[i];
		delete[] ptr_;
		ptr_ = new_ptr;
	}
}

// Never call or never delete this function
// This is need by the linker to resolve template types
void SatisfyLinker() {
	List<String*>* list1 = new List<String*>();
	List<String*>* list2 = new List<String*>(0);
	list1->Add(new String(""));
	list1->Add(0, new String(""));
	list1->Get(0);
	delete list1;
	delete list2;

	List<Token*>* list3 = new List<Token*>();
	list3->Add(new Token(Token::Type::kInteger));
	list3->Add(0, new Token(Token::Type::kInteger));
	list3->Get(0);
	delete list3;
}