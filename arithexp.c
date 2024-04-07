//Write a C program to solve an arithmetic expression using +, -, *,/ operators.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPRESSION_LENGTH 100

int main() {
    char expression[MAX_EXPRESSION_LENGTH];
    int operands[MAX_EXPRESSION_LENGTH / 2 + 1];
    char operators[MAX_EXPRESSION_LENGTH / 2];
    int operandIndex = 0;
    int operatorIndex = 0;
    int result;

    printf("Enter an arithmetic expression (e.g., 5+3*2-1/4): ");
    fgets(expression, MAX_EXPRESSION_LENGTH, stdin);
    expression[strcspn(expression, "\n")] = '\0'; // Remove the newline character

    for (int i = 0; i < strlen(expression); i++) {
        if (isdigit(expression[i])) {
            int num = 0;
            while (i < strlen(expression) && isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            i--;
            operands[operandIndex++] = num;
        } else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            while (operatorIndex > 0 && (expression[i] == '*' || expression[i] == '/') && (operators[operatorIndex - 1] == '*' || operators[operatorIndex - 1] == '/')) {
                char op = operators[--operatorIndex];
                int b = operands[--operandIndex];
                int a = operands[--operandIndex];
                switch (op) {
                    case '*':
                        operands[operandIndex++] = a * b;
                        break;
                    case '/':
                        operands[operandIndex++] = a / b;
                        break;
                }
            }
            operators[operatorIndex++] = expression[i];
        }
    }

    while (operatorIndex > 0) {
        char op = operators[--operatorIndex];
        int b = operands[--operandIndex];
        int a = operands[--operandIndex];
        switch (op) {
            case '+':
                operands[operandIndex++] = a + b;
                break;
            case '-':
                operands[operandIndex++] = a - b;
                break;
            case '*':
                operands[operandIndex++] = a * b;
                break;
            case '/':
                operands[operandIndex++] = a / b;
                break;
        }
    }

    result = operands[0];
    printf("Result: %d\n", result);

    return 0;
}
