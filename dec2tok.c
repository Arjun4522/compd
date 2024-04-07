//Write a program in C to convert a declaration statement into a sequence of tokens
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LENGTH 50

enum TokenType { DATATYPE, IDENTIFIER, ASSIGN, VALUE, SEMICOLON };

typedef struct {
    enum TokenType type;
    char value[MAX_TOKEN_LENGTH];
} Token;

int getTokens(char *declaration, Token *tokens, int *numTokens) {
    char *ptr = declaration;
    int tokenIndex = 0;

    // Get data type
    while (isalnum(*ptr) || *ptr == '_') {
        tokens[tokenIndex].type = DATATYPE;
        int i = 0;
        while (isalnum(*ptr) || *ptr == '_') {
            tokens[tokenIndex].value[i++] = *ptr++;
        }
        tokens[tokenIndex].value[i] = '\0';
        tokenIndex++;
    }

    // Get identifier
    while (isspace(*ptr)) {
        ptr++;
    }
    tokens[tokenIndex].type = IDENTIFIER;
    int i = 0;
    while (isalnum(*ptr) || *ptr == '_') {
        tokens[tokenIndex].value[i++] = *ptr++;
    }
    tokens[tokenIndex].value[i] = '\0';
    tokenIndex++;

    // Get assignment operator
    while (isspace(*ptr)) {
        ptr++;
    }
    if (*ptr == '=') {
        tokens[tokenIndex].type = ASSIGN;
        tokens[tokenIndex].value[0] = '=';
        tokens[tokenIndex].value[1] = '\0';
        tokenIndex++;
        ptr++;
    }

    // Get value
    while (isspace(*ptr)) {
        ptr++;
    }
    tokens[tokenIndex].type = VALUE;
    i = 0;
    while (*ptr != ';') {
        tokens[tokenIndex].value[i++] = *ptr++;
    }
    tokens[tokenIndex].value[i] = '\0';
    tokenIndex++;

    // Get semicolon
    tokens[tokenIndex].type = SEMICOLON;
    tokens[tokenIndex].value[0] = ';';
    tokens[tokenIndex].value[1] = '\0';
    tokenIndex++;

    *numTokens = tokenIndex;
    return 0;
}

int main() {
    char declaration[] = "int x = 42;";
    Token tokens[10];
    int numTokens;

    getTokens(declaration, tokens, &numTokens);

    for (int i = 0; i < numTokens; i++) {
        printf("%d: %s\n", tokens[i].type, tokens[i].value);
    }

    return 0;
}
