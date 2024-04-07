//Write a program in C to output the syntax trees for I/O Statements (printf and scanf)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ASTNode {
    char* type;
    char* value;
    struct ASTNode* left;
    struct ASTNode* right;
} ASTNode;

ASTNode* createNode(char* type, char* value, ASTNode* left,
                    ASTNode* right) {
    ASTNode* newNode = (ASTNode*)malloc(sizeof(ASTNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->type = type;
    newNode->value = value;
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

    ASTNode* printfTree = createNode("Statement", "printf",
                                     createNode("Format", "\"Hello, world!\\n\"", NULL, NULL),
                                     NULL
                                    );

    ASTNode* scanfTree = createNode("Statement", "scanf",
                                    createNode("Format", "\"%%d\"", NULL, NULL), // Note: Added an extra '%' to escape '%'
                                    createNode("Variable", "&x", NULL, NULL)
                                   );

    printf("\nSyntax tree for printf statement:\n");
    printAST(printfTree, 0, coderName);

    printf("\nSyntax tree for scanf statement:\n");
    printAST(scanfTree, 0, coderName);

    return 0;
}
