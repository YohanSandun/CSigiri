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
        Node* ast = parser.parse();
        //ast->toString();
        Value* value = interpreter.visit(ast);
        
        value->print();
      
        delete value;
        delete ast;

        printf("\n");
    }

    return 0;
}