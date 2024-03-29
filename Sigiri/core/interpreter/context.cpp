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

#include "context.h"

Context::Context() {
	parent_ = nullptr;
	return_value_ = nullptr;
	symbols_ = new ValueHashMap();
}

Context::Context(Context* parent) {
	return_value_ = nullptr;
	parent_ = parent;
	symbols_ = new ValueHashMap();
}

Context::~Context() {
	delete symbols_;
}

Value* Context::GetSymbol(String* key) {
	Value* value = symbols_->Get(key);
	if (value != nullptr)
		return value;
	if (parent_ != nullptr)
		return parent_->GetSymbol(key);
	return nullptr;
}