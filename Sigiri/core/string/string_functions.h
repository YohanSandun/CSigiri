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

#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H

#include "core/declarations.h"
#include "sigiri_string.h"

U_INT32  StringLength(const unsigned char* ptr);
bool    StringCompare(const unsigned char* s1, const unsigned char* s2);
bool    StringCompare(String* s1, String* s2);
int  StringToInt(String* str);
long double StringToFloat(String* str);
String* IntToString(long int value);
String* FloatToString(long double value);

#endif

