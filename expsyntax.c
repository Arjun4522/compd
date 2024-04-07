//Write a program in C to output the syntax trees for b) Expressions
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
char data;
struct Node *left;
struct Node *right;
} Node;
Node *createNode(char data) {
Node *newNode = (Node *)malloc(sizeof(Node));
newNode->data = data;
newNode->left = NULL;
newNode->right = NULL;
return newNode;
}
void printSyntaxTree(Node *root, int level) {
if (root == NULL)
return;
printSyntaxTree(root->right, level + 1);
for (int i = 0; i < level; i++)
printf(" ");
printf("%c\n", root->data);
printSyntaxTree(root->left, level + 1);
}
int main() {
// Creating a syntax tree for expression: (a + b) * (c - d)
Node *root = createNode('*');
root->left = createNode('+');
root->right = createNode('-');
root->left->left = createNode('a');
root->left->right = createNode('b');
root->right->left = createNode('c');
root->right->right = createNode('d');
printf("Syntax Tree for Expression: (a + b) * (c - d)\n");
printSyntaxTree(root, 0);
return 0;
}