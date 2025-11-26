#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct Node {
    int data;
    struct Node *next;
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

// ----------------------------------------START INSERTION-------------------------------------------------//

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

// ----------------------------------------END DELETION-------------------------------------------------//

// ----------------------------------------START DELETION-------------------------------------------------//
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

// ----------------------------------------END DELETION-------------------------------------------------//


// --------------------------------START BFS(STUPID WAY)-----------------------------------------------//
int getCount(struct TreeNode *node) {
    if(node == NULL) return 0;
    return 1 + getCount(node->left) + getCount(node->right);
}

int getEmptyIndex(struct TreeNode *arr[], int count) {
    for(int i = 0; i < count; i++) {
        if(arr[i] == NULL) {
            return i;
        }
    }
    return -1;
}

void bfs(struct TreeNode *node) {
    if(node == NULL) return;

    int count = getCount(node);
    struct TreeNode **arr = calloc(count, sizeof(struct TreeNode *));

    arr[0] = node;
    int i = 0;
    
    while(i < count && arr[i] != NULL) {

        struct TreeNode *current = arr[i];
        printf("%d->", current->val);

        int index = getEmptyIndex(arr, count);
        if(index != -1 && current->left != NULL)
            arr[index] = current->left;
            
        index = getEmptyIndex(arr, count);
        if(index != -1 && current->right != NULL)
            arr[index] = current->right;
            
        i++;
    }
    
    free(arr);
}

// --------------------------------END BFS(STUPID WAY)-----------------------------------------------//


// --------------------------------START BFS(NOT SO STUPID WAY)---------------------------------------//


void bfs2(struct TreeNode *node) {
    if(node == NULL) return;

    int count = getCount(node);
    struct TreeNode **arr = calloc(count, sizeof(struct TreeNode *));

    int front = 0;
    int rear = 0;
    arr[rear++] = node;
    
    while(front<rear) {

        struct TreeNode *current = arr[front];
        printf("%d ->", current->val);

        if(current->left != NULL)
            arr[rear++] = current->left;
            
        if(current->right != NULL)
            arr[rear++] = current->right;
            
        front++;
    }
    
    free(arr);
}

// --------------------------------END BFS(NOT SO STUPID WAY)-----------------------------------------------//

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
    printf("\n");

    bfs2(node);
    return 0;
}
