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

U_INT32 StringLength(const unsigned char* ptr) {
	U_INT32 i = 0;
	while (ptr[i++] != '\0');
	return i - 1;
}

bool StringCompare(const unsigned char* s1, const unsigned char* s2) {
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

int StringToInt(String* str) {
	int value = 0;
	int i = 0;
	while (i < str->length_) {
		int digit = str->ptr_[i++] - '0';
		value *= 10;
		value += digit;
	}
	return value;
}

long double StringToFloat(String* str) {
	long double value = 0;
	int dotIndex = str->IndexOf('.');
	dotIndex = dotIndex >= 0 ? dotIndex : str->length_;

	for (size_t i = 0; i < dotIndex; i++)
	{
		int digit = str->ptr_[i] - '0';
		for (size_t j = 0; j < dotIndex - i - 1; j++)
			digit *= 10;
		value += digit;
	}

	long double decimal = 0;
	for (size_t i = dotIndex + 1; i < str->length_; i++)
	{
		int digit = str->ptr_[i] - '0';
		U_INT32 divide = 1;
		for (size_t j = 0; j < i - dotIndex; j++)
			divide *= 10;
		decimal += (digit / (long double)divide);
	}
	return value + decimal;
}

String* IntToString(long int value) {
	String* string = new String(13);
	if (value == 0)
	{
		string->Append('0');
		return string;
	}

	if (value < 0) {
		string->Append('-');
		value *= -1;
	}

	char digits[10] = {};
	int i = 0;
	while (value > 0)
	{
		int digit = value - ((value / 10) * 10);
		digits[i++] = (char)(digit + '0');
		value /= 10;
	}

	for (i = 9; i >= 0; i--)
	{
		if (digits[i] != '\0')
			string->Append(digits[i]);
	}

	return string;
}

String* FloatToString(long double value) {
	String* string = new String(UTF_8 "need to implement");
	return string;
}