//Write a program in C to output the syntax trees for a) Declarations
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum {
NODE_DECLARATION,
NODE_TYPE,
NODE_IDENTIFIER
} NodeType;
typedef struct Node {
NodeType type;
char* value;
struct Node* left;
struct Node* right;
} Node;
Node* createNode(NodeType type, char* value, Node* left, Node*
right)
{
Node* newNode = (Node*)malloc(sizeof(Node));
if (newNode == NULL) {
perror("Memory allocation failed");
exit(EXIT_FAILURE);
}
newNode->type = type;
newNode->value = value;
newNode->left = left;
newNode->right = right;
return newNode;
}
void printSyntaxTree(Node* root) {
if (root == NULL) {
return;
}
switch (root->type) {
case NODE_DECLARATION:
printf("Declaration\n");
break;
case NODE_TYPE:
printf("Type: %s\n", root->value);
break;
case NODE_IDENTIFIER:
printf("Identifier: %s\n", root->value);
break;
default:
fprintf(stderr, "Unknown node type\n");
exit(EXIT_FAILURE);
}
printSyntaxTree(root->left);
printSyntaxTree(root->right);
}
Node* parseDeclaration(char* declaration) {
Node* declarationNode = createNode(NODE_DECLARATION,
NULL, NULL, NULL);
char* token = strtok(declaration, " ");
Node* currentNode = declarationNode;
while (token != NULL) {
if (strcmp(token, "int") == 0 || strcmp(token, "char") == 0
||
strcmp(token, "float") == 0) {
currentNode->left = createNode(NODE_TYPE, token, NULL,
NULL);
} else {
currentNode->right = createNode(NODE_IDENTIFIER, token,
NULL, NULL);
}
token = strtok(NULL, " ");
if (token != NULL) {
currentNode->left = createNode(NODE_DECLARATION, NULL,
NULL, currentNode->left);
currentNode = currentNode->left;
}
}
return declarationNode;
}
int main() {
char coderName[100];
printf("Enter your name: ");
fgets(coderName, sizeof(coderName), stdin);
coderName[strcspn(coderName, "\n")] = '\0';
char declaration[100];
printf("Enter a declaration: ");
fgets(declaration, sizeof(declaration), stdin);
declaration[strcspn(declaration, "\n")] = '\0';
Node* syntaxTree = parseDeclaration(declaration);
printf("\nSyntax Tree (Coder: %s):\n", coderName);
printSyntaxTree(syntaxTree);
return 0;
}