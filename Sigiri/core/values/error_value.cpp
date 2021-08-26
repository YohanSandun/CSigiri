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

#include "error_value.h"

ErrorValue::ErrorValue(const char* error, U_INT32 line, U_INT32 column_start, U_INT32 column_end) : Value(Value::Type::kError, line, column_start, column_end) {
	this->error = new String(UTF_8 error);
}

ErrorValue::~ErrorValue() {
	delete error;
}

void ErrorValue::Print() {
	printf("Runtime Error : ");
	printf("%s\n", error->ptr_);
	printf("\tnear line %d, column %d to %d", line, column_start, column_end);
}