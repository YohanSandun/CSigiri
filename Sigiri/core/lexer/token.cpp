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

#include "token.h"

Token::Token(Type type) {
	type_ = type;
}

Token::Token(String* value, Type type) {
	value_ = value;
	type_ = type;
}

Token::~Token() {
	if (value_ != nullptr)
		delete value_;
}

const char* Token::GetName() {
	return token_names_[(int)type_];
}