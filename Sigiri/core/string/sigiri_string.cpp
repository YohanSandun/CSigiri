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

#include "sigiri_string.h"
#include "string_functions.h"

String::String(uint32 size) {
	size_ = size > 0 ? size : 1;
	length_ = 0;
	ptr_ = new unsigned char[size_];
	*ptr_ = '\0';
	hash_code_ = 0;
}

String::String(const unsigned char* ptr) {
	size_ = StringLength(ptr) + 1;
	length_ = size_ - 1;
	ptr_ = new unsigned char[size_];
	for (size_t i = 0; i < size_; i++)
		ptr_[i] = ptr[i];
	hash_code_ = 0;
	CalculateHash();
}

String::~String() {
	if (ptr_ != nullptr)
		delete[] ptr_;
}

bool String::Compare(String* other) {
	return StringCompare(this, other);
}

bool String::Compare(const unsigned char* other) {
	return StringCompare(ptr_, other);
}

uint32 String::IndexOf(unsigned char c) {
	for (size_t i = 0; i < length_; i++)
		if (ptr_[i] == c)
			return i;
	return -1;
}

void String::CalculateHash() {
	hash_code_ = 0;
	for (size_t i = 0; i < length_; i++)
		hash_code_ = 31 * hash_code_ + ptr_[i];
}

void String::Append(const unsigned char* ptr) {
	uint32 length = StringLength(ptr);
	if (length_ + length < size_) {
		for (size_t i = 0; i <= length; i++)
			ptr_[length_ + i] = ptr[i];
	}
	else {
		// re-alloc memory
		size_ += length + 10; // 10 extra bytes
		unsigned char* new_ptr = new unsigned char[size_];
		for (size_t i = 0; i < length_; i++)
			new_ptr[i] = ptr_[i];
		for (size_t i = 0; i <= length; i++)
			new_ptr[length_ + i] = ptr[i];
		delete[] ptr_;
		ptr_ = new_ptr;
	}
	length_ += length;
	CalculateHash();
}

void String::Append(unsigned char c) {
	if (c == '\0')
		return;
	if (length_ + 1 < size_) {
		ptr_[length_] = c;
	}
	else {
		// re-alloc memory
		size_ += 10; // 10 extra bytes
		unsigned char* new_ptr = new unsigned char[size_];
		for (size_t i = 0; i < length_; i++)
			new_ptr[i] = ptr_[i];
		new_ptr[length_] = c;
		delete[] ptr_;
		ptr_ = new_ptr;
	}
	ptr_[length_ + 1] = '\0';
	length_ += 1;
	CalculateHash();
}

String* String::Clone() {
	return new String(ptr_);
}
