#include <cstdio>
#include "include/string.h"
#include "include/token.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/sigiri.h"

int main() {
    Interpreter interpreter;
    Parser parser;

    while (true)
    {
        printf(">>> ");
        char line[200];
        scanf("%s", line);

        Lexer lexer(new String(line));

        parser.setTokens(lexer.generateTokens());
       
        Node* ast = parser.parse();
        
        Value* value = interpreter.visit(ast);
        if (value != NULL) 
            value->print();
        
        delete ast;

        printf("\n");
    }

    return 0;
}