//Write a program to convert an annotated syntax tree to intermediate code.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILDREN 5
#define MAX_TOKEN_LENGTH 50

typedef struct Node {
    char token[MAX_TOKEN_LENGTH];
    int type; // 0 - Identifier, 1 - Constant, 2 - Operator
    int value; // Used for constants
    struct Node *children[MAX_CHILDREN];
    int numChildren;
} Node;

Node *createNode(char *token, int type, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->token, token);
    newNode->type = type;
    newNode->value = value;
    newNode->numChildren = 0;
    return newNode;
}

void addChild(Node *parent, Node *child) {
    parent->children[parent->numChildren++] = child;
}

void generateIntermediateCode(Node *root) {
    if (root->type == 0) { // Identifier
        printf("%s\n", root->token);
    } else if (root->type == 1) { // Constant
        printf("%d\n", root->value);
    } else if (root->type == 2) { // Operator
        generateIntermediateCode(root->children[0]);
        generateIntermediateCode(root->children[1]);
        printf("%s\n", root->token);
    }
}

int main() {
    // Construct the annotated syntax tree
    Node *root = createNode("+", 2, 0);
    Node *left = createNode("x", 0, 0);
    Node *right = createNode("5", 1, 5);
    addChild(root, left);
    addChild(root, right);

    // Generate intermediate code
    generateIntermediateCode(root);

    return 0;
}
