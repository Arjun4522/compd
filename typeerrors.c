//Write a program in C to check type expressions and produce type errors
#include <stdio.h>

// Function to check the type of expressions
void checkType(int a, float b) {
    // Check if both operands are integers
    if (a == (int)a && b == (int)b) {
        printf("Both operands are integers.\n");
    } 
    // Check if both operands are floats
    else if (a != (int)a && b != (int)b) {
        printf("Both operands are floats.\n");
    } 
    // Otherwise, operands have different types
    else {
        printf("Type error: Operands have different types.\n");
    }
}

int main() {
    int integerOperand = 5;
    float floatOperand = 3.5;
    
    // Test cases
    checkType(integerOperand, floatOperand); // Type error: Operands have different types.
    checkType(integerOperand, 2); // Both operands are integers.
    checkType(2.5, floatOperand); // Both operands are floats.

    return 0;
}
