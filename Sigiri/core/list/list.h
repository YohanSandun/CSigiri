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

#ifndef LIST_H
#define LIST_H

#include "core/declarations.h"

template <typename T>
class List {
private:
	const U_BYTE kDefaultSize = 10;
	int current_index_;
	U_INT32 size_;
	T* ptr_;

	void EnsureMemory();

public:
	bool keep_items_alive_ = false;
	List();
	List(U_INT32 size);
	~List();
	void Add(T item);
	void Add(U_INT32 index, T item);
	T Get(U_INT32 index);
	inline U_INT32 count() { return current_index_ + 1; }
};

#endif 

