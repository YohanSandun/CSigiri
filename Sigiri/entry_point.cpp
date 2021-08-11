#include <cstdio>
#include "core/string/string.h"
#include "core/token.h"
#include "core/lexer.h"
#include "core/parser.h"
#include "core/sigiri.h"
#include "core/symbol_table.h"
#include "core/context.h"

#include "core/map/hash_map.h"


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

//char* tokenNames[] = {
//        "NEWLINE",
//        "INT_NUMBER",
//        "FLOAT_NUMBER",
//        "STRING",
//        "IDENTIFIER",
//        "KEYWORD_VAR",
//        "KEYWORD_INT",
//        "KEYWORD_FOR",
//        "KEYWORD_TO",
//        "KEYWORD_STEP",
//        "KEYWORD_METHOD",
//        "KEYWORD_RETURN",
//        "KEYWORD_BREAK",
//        "KEYWORD_CONTINUE",
//        "KEYWORD_IF",
//        "KEYWORD_ELIF",
//        "KEYWORD_ELSE",
//        "KEYWORD_CLASS",
//        "PLUS",
//        "MINUS",
//        "ASTERIX",
//        "FW_SLASH",
//        "MODULUS",
//        "POWER",
//        "L_PAREN",
//        "R_PAREN",
//        "COMMA",
//        "DOT",
//        "L_BRACE",
//        "R_BRACE",
//        "L_SQ",
//        "R_SQ",
//        "COLON",
//        "SEMI_COLON",
//        "EQUALS",
//        "EQUALS_EQUALS",
//        "NOT_EQUALS",
//        "GREATER_THAN",
//        "LESS_THAN",
//        "GREATER_EQ",
//        "LESS_EQ",
//        "BOOLEAN_NOT",
//        "BOOLEAN_AND",
//        "BOOLEAN_OR",
//        "BITWISE_OR",
//        "BITWISE_AND",
//        "BITWISE_XOR",
//        "BITWISE_COMPLEMENT",
//        "LEFT_SHIFT",
//        "RIGHT_SHIFT",
//        "EOF_TOKEN"
//};

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

       
        /*List<Token*>* tokens = lexer.generateTokens();
        int len = tokens->count();
        for (size_t i = 0; i < len; i++)
        {
            printf("%s\n", tokenNames[(int)tokens->Get(i)->mType]);
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
            printf("%s", parser.mError->ptr);
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