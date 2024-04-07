//Write a program in C to convert a I/O statements (printf, scanf) into a sequence of tokens.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LENGTH 50

enum TokenType { PRINTF, SCANF, LPAREN, RPAREN, QUOTE, PERCENT, IDENTIFIER, VALUE, COMMA, SEMICOLON };

typedef struct {
    enum TokenType type;
    char value[MAX_TOKEN_LENGTH];
} Token;

int getTokens(char *statement, Token *tokens, int *numTokens) {
    char *ptr = statement;
    int tokenIndex = 0;

    // Get printf or scanf
    if (strncmp(ptr, "printf", 6) == 0) {
        tokens[tokenIndex].type = PRINTF;
        strcpy(tokens[tokenIndex].value, "printf");
        tokenIndex++;
        ptr += 6;
    } else if (strncmp(ptr, "scanf", 5) == 0) {
        tokens[tokenIndex].type = SCANF;
        strcpy(tokens[tokenIndex].value, "scanf");
        tokenIndex++;
        ptr += 5;
    }

    // Get left parenthesis
    while (isspace(*ptr)) {
        ptr++;
    }
    if (*ptr == '(') {
        tokens[tokenIndex].type = LPAREN;
        tokens[tokenIndex].value[0] = '(';
        tokens[tokenIndex].value[1] = '\0';
        tokenIndex++;
        ptr++;
    }

    // Get format string or identifier
    while (*ptr != ')') {
        if (*ptr == '"') {
            tokens[tokenIndex].type = QUOTE;
            int i = 0;
            ptr++;
            while (*ptr != '"') {
                tokens[tokenIndex].value[i++] = *ptr++;
            }
            tokens[tokenIndex].value[i] = '\0';
            tokenIndex++;
            ptr++;
        } else if (*ptr == '%') {
            tokens[tokenIndex].type = PERCENT;
            tokens[tokenIndex].value[0] = '%';
            tokens[tokenIndex].value[1] = '\0';
            tokenIndex++;
            ptr++;
        } else if (isalnum(*ptr) || *ptr == '_') {
            tokens[tokenIndex].type = IDENTIFIER;
            int i = 0;
            while (isalnum(*ptr) || *ptr == '_') {
                tokens[tokenIndex].value[i++] = *ptr++;
            }
            tokens[tokenIndex].value[i] = '\0';
            tokenIndex++;
        } else if (isdigit(*ptr)) {
            tokens[tokenIndex].type = VALUE;
            int i = 0;
            while (isdigit(*ptr)) {
                tokens[tokenIndex].value[i++] = *ptr++;
            }
            tokens[tokenIndex].value[i] = '\0';
            tokenIndex++;
        } else if (*ptr == ',') {
            tokens[tokenIndex].type = COMMA;
            tokens[tokenIndex].value[0] = ',';
            tokens[tokenIndex].value[1] = '\0';
            tokenIndex++;
            ptr++;
        } else {
            ptr++;
        }
    }

    // Get right parenthesis
    tokens[tokenIndex].type = RPAREN;
    tokens[tokenIndex].value[0] = ')';
    tokens[tokenIndex].value[1] = '\0';
    tokenIndex++;
    ptr++;

    // Get semicolon
    while (isspace(*ptr)) {
        ptr++;
    }
    if (*ptr == ';') {
        tokens[tokenIndex].type = SEMICOLON;
        tokens[tokenIndex].value[0] = ';';
        tokens[tokenIndex].value[1] = '\0';
        tokenIndex++;
        ptr++;
    }

    *numTokens = tokenIndex;
    return 0;
}

int main() {
    char statement[] = "printf(\"Hello, %s!\\n\", name);";
    Token tokens[20];
    int numTokens;

    getTokens(statement, tokens, &numTokens);

    for (int i = 0; i < numTokens; i++) {
        printf("%d: %s\n", tokens[i].type, tokens[i].value);
    }

    return 0;
}
