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

#include "string_functions.h"

uint32 StringLength(const char* ptr) {
	uint32 i = 0;
	while (ptr[i++] != '\0');
	return i - 1;
}

bool StringCompare(const char* s1, const char* s2) {
	if (StringLength(s1) != StringLength(s2))
		return false;
	int i = 0;
	while (s1[i] != '\0' && s2[i] != '\0') {
		if (s1[i] != s2[i])
			return false;
		i++;
	}
	return true;
}

bool StringCompare(String* s1, String* s2) {
	if (s1->length_ != s2->length_)
		return false;
	int i = 0;
	while (s1->ptr_[i] != '\0' && s2->ptr_[i] != '\0') {
		if (s1->ptr_[i] != s2->ptr_[i])
			return false;
		i++;
	}
	return true;
}

uint32 StringToInt(String* str) {
	int value = 0;
	int i = 0;
	while (i < str->length_) {
		int digit = str->ptr_[i++] - '0';
		value *= 10;
		value += digit;
	}
	return value;
}

double StringToFloat(String* str) {
	double value = 0;
	int dotIndex = str->IndexOf('.');
	dotIndex = dotIndex >= 0 ? dotIndex : str->length_;

	for (size_t i = 0; i < dotIndex; i++)
	{
		int digit = str->ptr_[i] - '0';
		for (size_t j = 0; j < dotIndex - i - 1; j++)
			digit *= 10;
		value += digit;
	}

	double decimal = 0;
	for (size_t i = dotIndex + 1; i < str->length_; i++)
	{
		int digit = str->ptr_[i] - '0';
		uint32 divide = 1;
		for (size_t j = 0; j < i - dotIndex; j++)
			divide *= 10;
		decimal += (digit / (double)divide);
	}
	return value + decimal;
}