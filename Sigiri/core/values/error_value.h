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

#ifndef ERROR_VALUE_H
#define ERROR_VALUE_H

#include "value.h"
#include "core/string/string.h"

struct ErrorValue : public Value
{
	String* error;
	ErrorValue(const char* error, U_INT32 line, U_INT32 column_start, U_INT32 column_end);
	~ErrorValue();
	void Print();
};

#endif