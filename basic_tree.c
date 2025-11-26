#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void printTree(struct TreeNode *node) {
    if(node == NULL) return;

    printf("%d-> ", node->val);
    printTree(node->left);
    printTree(node->right);
}

void inorder(struct TreeNode *node) {
    if(node == NULL) return;
    inorder(node->left);
    printf("%d ->", node->val);
    inorder(node->right);
}

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

struct TreeNode *findMin(struct TreeNode *node) {
    while(node->left != NULL) {
        node = node->left;
    }
    return node;
}

struct TreeNode *delete(struct TreeNode *node, int data) {
    if(node == NULL) return NULL;
    if(node->val == data) {
        printf("\ndeleting %d\n", node->val);
        if(node->left == NULL && node->right == NULL) {
            free(node);
            return NULL;
        } else if(node->left == NULL) { 
            struct TreeNode *temp = node->right;
            free(node);
            return temp;
        } else if(node->right == NULL) {
            struct TreeNode *temp = node->left;
            free(node);
            return temp;
        } else {
            struct TreeNode *minNode = findMin(node->right);
            node->val = minNode->val;
            node->right = delete(node->right, minNode->val);
            return node;
        }                  
    }                     
    if(node->val > data) {                     
        node->left = delete(node->left, data);
        return node;                          
    } else {                                  
        node->right = delete(node->right, data);
        return node;
    }
    return node;
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
    insert(node, 9);
    insert(node, 3);
    insert(node, 7);


    inorder(node);
    delete(node, 5);

    inorder(node);


    return 0;
}
