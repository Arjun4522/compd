//Write a program in C to convert a control flow statements (conditions and loops into a sequence of tokens.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LENGTH 50

enum TokenType { IF, WHILE, FOR, LPAREN, RPAREN, LBRACE, RBRACE, IDENTIFIER, OPERATOR, VALUE, SEMICOLON };

typedef struct {
    enum TokenType type;
    char value[MAX_TOKEN_LENGTH];
} Token;

int getTokens(char *statement, Token *tokens, int *numTokens) {
    char *ptr = statement;
    int tokenIndex = 0;

    // Get keyword (if, while, for)
    if (strncmp(ptr, "if", 2) == 0) {
        tokens[tokenIndex].type = IF;
        strcpy(tokens[tokenIndex].value, "if");
        tokenIndex++;
        ptr += 2;
    } else if (strncmp(ptr, "while", 5) == 0) {
        tokens[tokenIndex].type = WHILE;
        strcpy(tokens[tokenIndex].value, "while");
        tokenIndex++;
        ptr += 5;
    } else if (strncmp(ptr, "for", 3) == 0) {
        tokens[tokenIndex].type = FOR;
        strcpy(tokens[tokenIndex].value, "for");
        tokenIndex++;
        ptr += 3;
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

    // Get identifier, operator, or value
    while (*ptr != ')') {
        if (isalnum(*ptr) || *ptr == '_') {
            tokens[tokenIndex].type = IDENTIFIER;
            int i = 0;
            while (isalnum(*ptr) || *ptr == '_') {
                tokens[tokenIndex].value[i++] = *ptr++;
            }
            tokens[tokenIndex].value[i] = '\0';
            tokenIndex++;
        } else if (strchr("=<>!&|", *ptr)) {
            tokens[tokenIndex].type = OPERATOR;
            int i = 0;
            while (strchr("=<>!&|", *ptr)) {
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

    // Get left brace
    while (isspace(*ptr)) {
        ptr++;
    }
    if (*ptr == '{') {
        tokens[tokenIndex].type = LBRACE;
        tokens[tokenIndex].value[0] = '{';
        tokens[tokenIndex].value[1] = '\0';
        tokenIndex++;
        ptr++;
    }

    // Get right brace
    while (isspace(*ptr)) {
        ptr++;
    }
    if (*ptr == '}') {
        tokens[tokenIndex].type = RBRACE;
        tokens[tokenIndex].value[0] = '}';
        tokens[tokenIndex].value[1] = '\0';
        tokenIndex++;
        ptr++;
    }

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
    char statement[] = "if (x > 0) { y = 42; }";
    Token tokens[20];
    int numTokens;

    getTokens(statement, tokens, &numTokens);

    for (int i = 0; i < numTokens; i++) {
        printf("%d: %s\n", tokens[i].type, tokens[i].value);
    }

    return 0;
}
