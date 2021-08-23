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
#include "core/values/value.h"
#include "core/interpreter/interpreter.h"
#include "core/interpreter/context.h"

int main() {
    printf("CSigiri v1.0.0\nThis is not a released version. CSigiri is still under development at https://github.com/YohanSandun/CSigiri \nBut my twin brother is way ahead of me. you can find him at https://github.com/YohanSandun/Sigiri \n");

    Interpreter interpreter;
    Context context;

    while (true)
    {
        printf("--> ");

        char buffer[1024];
        fgets(buffer, sizeof(buffer), stdin);
        String code(UTF_8 buffer);

        Lexer lexer(&code);
        List<Token*>* tokens = lexer.GenerateTokens();
        Parser parser(tokens);
        Node* node = parser.Parse();
        if (parser.HasError()) {
            parser.PrintError();
            delete tokens;
            continue;
        }

        Value* value = interpreter.Visit(node, &context);
        if (!interpreter.HasError()) {
            if (value != nullptr) {
                value->Print();
                printf("\n");
            }
        }
        else {
            interpreter.PrintError();
            interpreter.ClearError();
            printf("\n");
        }

        delete tokens;
        delete node;
        delete value;
    }
    return 0;
}
