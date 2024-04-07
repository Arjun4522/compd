//Write a program in C to output the syntax trees for d) Control Flow Statements (Conditions and Loops)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ASTNode {
    char* type;
    char* value;
    struct ASTNode* left;
    struct ASTNode* right;
} ASTNode;

ASTNode* createNode(const char* type, const char* value,
                    ASTNode* left, ASTNode* right) {
    ASTNode* newNode = (ASTNode*)malloc(sizeof(ASTNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    // Allocate memory for type and value strings
    newNode->type = strdup(type);
    newNode->value = strdup(value);
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

void printAST(ASTNode* root, int level, const char* coderName) {
    if (root == NULL) return;
    for (int i = 0; i < level; i++) {
        printf("\t");
    }
    printf("%s (%s): %s\n", root->type, coderName, root->value);
    printAST(root->left, level + 1, coderName);
    printAST(root->right, level + 1, coderName);
}

int main() {
    char coderName[100];
    printf("Enter your name: ");
    fgets(coderName, sizeof(coderName), stdin);
    coderName[strcspn(coderName, "\n")] = 0; // Remove newline

    ASTNode* ifElseTree = createNode("Statement", "if",
                                      createNode("Condition", "x > 5", NULL, NULL),
                                      createNode("Block", "{\n\t// Code block\n}", NULL, NULL)
                                    );
    ifElseTree->right->left = createNode("Block", "{\n\t// Code block\n\t// else block\n}", NULL, NULL);

    ASTNode* forLoopTree = createNode("Statement", "for",
                                      createNode("Initialization", "int i = 0", NULL, NULL),
                                      createNode("Condition", "i < 10", NULL, NULL)
                                     );
    forLoopTree->right->left = createNode("Increment", "i++", NULL, NULL);
    forLoopTree->right->right = createNode("Block", "{\n\t// Loop body\n}", NULL, NULL);

    printf("\nSyntax tree for if-else statement:\n");
    printAST(ifElseTree, 0, coderName);
    printf("\nSyntax tree for for loop:\n");
    printAST(forLoopTree, 0, coderName);

    return 0;
}
