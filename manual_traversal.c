#include<stdio.h>
#include<stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *insert(struct TreeNode *node, int data) {
    if(node == NULL) {
        struct TreeNode *newnode = malloc(sizeof(struct TreeNode));
        newnode->val = data;
        newnode->left = newnode->right = NULL;
        return newnode;
    }
    if(node->val > data) {
        node->left = insert(node->left, data);
    } else {
        node->right = insert(node->right, data);
    }
    return node;
}

void preOrderManual(struct TreeNode *node) {
    struct TreeNode *stack[100];
    int top = -1;
    int current = 0;
    stack[++top] = node;  
    while(top!=-1) {
        struct TreeNode *currentNode = stack[top];
        printf("%d ->", currentNode->val);
        currentNode = stack[top--];
        if(currentNode->right != NULL) stack[++top] = currentNode->right;
        if(currentNode->left != NULL) stack[++top] = currentNode->left;
    }
}

void freeTree(struct TreeNode *node) {
    if(!node) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main() {
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    if (node == NULL) {
        return 0; 
    }
    node->val = 5;
    node->left = NULL;
    node->right = NULL;

    insert(node, 1);
    insert(node, 0);
    insert(node, 9);
    insert(node, 3);
    insert(node, 7);

    printf("\n");

    preOrderManual(node);

    freeTree(node);
    return 0;
}