#include <cstdio>
#include "include/string.h"
#include "include/token.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/sigiri.h"
#include "include/symbol_table.h"
#include "include/context.h"

char* readFile() {
    /* declare a file pointer */
    FILE* infile;
    long numbytes;

    /* open an existing file for reading */
    infile = fopen("e:\\test.si", "r");

    /* quit if the file does not exist */
    if (infile == NULL)
        return nullptr;

    /* Get the number of bytes */
    fseek(infile, 0L, SEEK_END);
    numbytes = ftell(infile);

    /* reset the file position indicator to
    the beginning of the file */
    fseek(infile, 0L, SEEK_SET);

    /* grab sufficient memory for the
    buffer to hold the text */
    char* buffer = new char[numbytes + 1];

    for (size_t i = 0; i < numbytes+1; i++)
        buffer[i] = '\0';

    /* memory error */
    if (buffer == NULL)
        return nullptr;

    /* copy all the text into the buffer */
    fread(buffer, sizeof(char), numbytes, infile);

    fclose(infile);
    buffer[numbytes] = '\0';

    return buffer;
}

int main() {
    Interpreter interpreter;
    Parser parser;
    SymbolsParser* symbols = new SymbolsParser();
    SymbolsRuntime* symbolsRt = new SymbolsRuntime();

    while (true)
    {
        printf(">>> ");
        char line[200];
        scanf("%s", line);
        // "sum=0\nfor i = 0 to 100000: sum = sum + i\n\nsum"

        char* fdata = readFile();

        Lexer lexer(new String(fdata));
        delete[] fdata;

        parser.setTokens(lexer.generateTokens());

       /*
        List<Token*>* tokens = lexer.generateTokens();
        int len = tokens->getCount();
        for (size_t i = 0; i < len; i++)
        {
            printf("%d, ", tokens->get(i)->mType);
        }

        return 0;*/

        Node* ast = parser.parse(symbols);
        if (ast != nullptr) {
            printf(">>> program parsed. Please enter 'y' to start executing... \n");

            while (true) {
                printf(">>> ");
                char input[2];
                scanf("%s", input);

                Value* value = interpreter.visit(ast, symbolsRt);
                if (value != NULL) {
                    delete value;
                }

                printf("\n");
            }

            delete ast;

        }
        else if (parser.mError != nullptr) {
            printf("%s", parser.mError->mPtr);
            delete symbols;
            symbols = new SymbolsParser();
            //delete parser.mSymbols;
            delete parser.mError;
            //parser.mSymbols = new List<String*>();
            parser.mError = nullptr;
        }
        printf("\n");
    }

    return 0;
}