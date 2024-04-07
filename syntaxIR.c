//Write a program in C to check type expressions and produce type errors
#include <stdio.h>
#include <stdlib.h>
typedef enum {
NODE_CONSTANT,
NODE_VARIABLE,
NODE_BINARY_OPERATION,
NODE_ASSIGNMENT
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
void generateIntermediateCode(Node* root, char* coderName) {
if (root == NULL) {
return;
}
switch (root->type) {
case NODE_CONSTANT:
printf("%s: LOAD %s\n", coderName, root->value);
break;
case NODE_VARIABLE:
printf("%s: READ %s\n", coderName, root->value);
break;
case NODE_BINARY_OPERATION:
generateIntermediateCode(root->left, coderName);
generateIntermediateCode(root->right, coderName);
printf("%s: OP %s\n", coderName, root->value);
break;
case NODE_ASSIGNMENT:
generateIntermediateCode(root->right, coderName);
printf("%s: STORE %s\n", coderName, root->left->value);
break;
default:
fprintf(stderr, "Unknown node type\n");
exit(EXIT_FAILURE);
}
}
int main() {
Node* syntaxTree = createNode(NODE_ASSIGNMENT, "x",
createNode(NODE_VARIABLE, "y", NULL, NULL),
createNode(NODE_BINARY_OPERATION, "+",
createNode(NODE_CONSTANT, "5", NULL, NULL),
createNode(NODE_CONSTANT, "3", NULL, NULL)
)
);
generateIntermediateCode(syntaxTree, "orzoo"); // Example
return 0;
}
