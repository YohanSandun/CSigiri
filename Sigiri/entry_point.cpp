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

#include <cstdio>

#include "core/string/string.h"
#include "core/list/list.cpp"
#include "core/lexer/lexer.h"
#include "core/parser/parser.h"
#include "core/parser/nodes/node.h"

int main() {
    String code = u8 "23+";
    Lexer lexer(&code);
    Parser parser(lexer.GenerateTokens());
    Node* node = parser.Parse();
    if (parser.HasError()) {
        parser.PrintError();
        return 0;
    }
    printf("OK!\n");

    return 0;
}
