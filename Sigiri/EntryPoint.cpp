#include <cstdio>
#include "include/string.h"
#include "include/token.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/sigiri.h"

int main() {

    while (true)
    {
        printf(">>> ");
        char line[200];
        scanf("%s", line);

        String* code = new String(line);
        Lexer lexer(code);
        Parser parser(lexer.generateTokens());
        Interpreter interpreter;
        Value* value = interpreter.visit(parser.parse());
        
        value->print();
      
        delete value;

        printf("\n");
    }

    return 0;
}