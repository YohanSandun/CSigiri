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

#ifndef SIGIRI_STRING_H
#define SIGIRI_STRING_H

#include "core/declarations.h"

class String {
private:
	uint32 size_;

public:
	char* ptr_;
	uint32 length_;
	int hash_code_;
	
	String(const char* ptr);
	String(uint32 size);
	~String();

	bool Compare(String* other);
	bool Compare(const char* other);

	inline char operator [] (int i) {
		return ptr_[i];
	}

	void CalculateHash();
	void Append(const char* ptr);
	void Append(char c);
	uint32 IndexOf(char c);
	String* Clone();
};

#endif