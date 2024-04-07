//Write a program in C to implement a Symbol Table to work with Declaration Statements and Arithmetic Expressions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SYMBOL_TABLE_SIZE 100
#define MAX_IDENTIFIER_LENGTH 50

enum SymbolType { VARIABLE, FUNCTION };

typedef struct {
    char name[MAX_IDENTIFIER_LENGTH];
    enum SymbolType type;
    int value;
} SymbolTableEntry;

SymbolTableEntry symbolTable[MAX_SYMBOL_TABLE_SIZE];
int symbolTableSize = 0;

int findSymbol(char *name) {
    for (int i = 0; i < symbolTableSize; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int addSymbol(char *name, enum SymbolType type, int value) {
    if (symbolTableSize == MAX_SYMBOL_TABLE_SIZE) {
        fprintf(stderr, "Symbol table is full.\n");
        return -1;
    }

    int index = findSymbol(name);
    if (index != -1) {
        fprintf(stderr, "Symbol '%s' already exists in the table.\n", name);
        return -1;
    }

    strcpy(symbolTable[symbolTableSize].name, name);
    symbolTable[symbolTableSize].type = type;
    symbolTable[symbolTableSize].value = value;
    symbolTableSize++;
    return 0;
}

int updateSymbol(char *name, int value) {
    int index = findSymbol(name);
    if (index == -1) {
        fprintf(stderr, "Symbol '%s' not found in the table.\n", name);
        return -1;
    }

    symbolTable[index].value = value;
    return 0;
}

int evaluateExpression(char *expression) {
    int result = 0;
    char *ptr = expression;
    int operand1, operand2;
    char op;

    while (*ptr != '\0') {
        // Find the first operand
        while (isspace(*ptr)) {
            ptr++;
        }
        if (isdigit(*ptr)) {
            operand1 = 0;
            while (isdigit(*ptr)) {
                operand1 = operand1 * 10 + (*ptr - '0');
                ptr++;
            }
        } else {
            char name[MAX_IDENTIFIER_LENGTH];
            int i = 0;
            while (isalnum(*ptr) || *ptr == '_') {
                name[i++] = *ptr++;
            }
            name[i] = '\0';
            int index = findSymbol(name);
            if (index == -1) {
                fprintf(stderr, "Symbol '%s' not found in the table.\n", name);
                return -1;
            }
            operand1 = symbolTable[index].value;
        }

        // Find the operator
        while (isspace(*ptr)) {
            ptr++;
        }
        op = *ptr++;

        // Find the second operand
        while (isspace(*ptr)) {
            ptr++;
        }
        if (isdigit(*ptr)) {
            operand2 = 0;
            while (isdigit(*ptr)) {
                operand2 = operand2 * 10 + (*ptr - '0');
                ptr++;
            }
        } else {
            char name[MAX_IDENTIFIER_LENGTH];
            int i = 0;
            while (isalnum(*ptr) || *ptr == '_') {
                name[i++] = *ptr++;
            }
            name[i] = '\0';
            int index = findSymbol(name);
            if (index == -1) {
                fprintf(stderr, "Symbol '%s' not found in the table.\n", name);
                return -1;
            }
            operand2 = symbolTable[index].value;
        }

        // Perform the operation
        switch (op) {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                result = operand1 / operand2;
                break;
            default:
                fprintf(stderr, "Invalid operator: %c\n", op);
                return -1;
        }
    }

    return result;
}

int main() {
    addSymbol("x", VARIABLE, 10);
    addSymbol("y", VARIABLE, 20);
    addSymbol("add", FUNCTION, 0);

    printf("Symbol table:\n");
    for (int i = 0; i < symbolTableSize; i++) {
        printf("%s (%s): %d\n", symbolTable[i].name, symbolTable[i].type == VARIABLE ? "variable" : "function", symbolTable[i].value);
    }

    printf("\nEvaluating expression: x + y\n");
    int result = evaluateExpression("x + y");
    printf("Result: %d\n", result);

    printf("\nUpdating symbol table...\n");
    updateSymbol("x", 15);

    printf("\nSymbol table after update:\n");
    for (int i = 0; i < symbolTableSize; i++) {
        printf("%s (%s): %d\n", symbolTable[i].name, symbolTable[i].type == VARIABLE ? "variable" : "function", symbolTable[i].value);
    }

    printf("\nEvaluating expression: x + y\n");
    result = evaluateExpression("x + y");
    printf("Result: %d\n", result);

    return 0;
}
