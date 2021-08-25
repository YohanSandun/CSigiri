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

char* read_file(const char* file_name);

int main() {

    bool read_from_file = true;

    if (read_from_file) {
        
        bool memory_check = false;
        while (true) {

            Interpreter interpreter;
            Context context;

            char* file_data = read_file("e:\\test.si");
            String code(UTF_8 file_data);
            delete[] file_data;

            Lexer lexer(&code);
            List<Token*>* tokens = lexer.GenerateTokens();

            //for (size_t i = 0; i < tokens->count(); i++)
            //{
            //    printf("%s\n", tokens->Get(i)->name());
            //}
            //return 0;

            Parser parser(tokens);
            Node* node = parser.Parse();

            if (parser.HasError()) {
                parser.PrintError();
                delete tokens;
                if (!memory_check) {
                    printf("\nPress any key to continue...");
                    getchar();
                    return 0;
                }
                continue;
            }

            Value* value = interpreter.Visit(node, &context);
            if (interpreter.HasError()) {
                interpreter.PrintError();
                interpreter.ClearError();
            }

            delete tokens;
            delete node;

            if (!memory_check) {
                printf("\nPress any key to continue...");
                getchar();
                return 0;
            }

        }
    }
    else {
        printf("CSigiri v1.0.0\nThis is not a released version. CSigiri is still under development at https://github.com/YohanSandun/CSigiri \nBut my twin brother is way ahead of me. you can find him at https://github.com/YohanSandun/Sigiri \n");

        Interpreter interpreter;
        Context context;

        while (true)
        {
            printf("--> ");

            char buffer[1024];
            fgets(buffer, sizeof(buffer), stdin);
            String code(UTF_8 buffer);
            //delete[] buffer;

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
    }
    return 0;
}

char* read_file(const char* file_name) {
    FILE* infile;
    long numbytes;

    infile = fopen(file_name, "r");

    if (infile == NULL)
        return nullptr;

    fseek(infile, 0L, SEEK_END);
    numbytes = ftell(infile);

    fseek(infile, 0L, SEEK_SET);

    char* buffer = new char[numbytes + 1];

    for (size_t i = 0; i < numbytes + 1; i++)
        buffer[i] = '\0';

    if (buffer == NULL)
        return nullptr;

    fread(buffer, sizeof(char), numbytes, infile);

    fclose(infile);
    buffer[numbytes] = '\0';

    return buffer;
}