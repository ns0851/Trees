#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *insert(struct TreeNode *node, int data)
{
    if (node == NULL)
    {
        struct TreeNode *newnode = malloc(sizeof(struct TreeNode));
        newnode->val = data;
        newnode->left = newnode->right = NULL;
        return newnode;
    }
    if (node->val > data)
    {
        node->left = insert(node->left, data);
    }
    else
    {
        node->right = insert(node->right, data);
    }
    return node;
}

int getCount(struct TreeNode *node)
{
    if (node == NULL)
        return 0;
    return 1 + getCount(node->left) + getCount(node->right);
}

// -----------------------------------------Pre Order Traversal------------------------------------------ //
void preOrderManual(struct TreeNode *node)
{
    int count = getCount(node);
    struct TreeNode **stack = malloc(count * sizeof(struct TreeNode *));
    int top = -1;
    int current = 0;
    stack[++top] = node;
    while (top != -1)
    {
        struct TreeNode *currentNode = stack[top];
        printf("%d -> ", currentNode->val);
        top--;
        if (currentNode->right != NULL)
            stack[++top] = currentNode->right;
        if (currentNode->left != NULL)
            stack[++top] = currentNode->left;
    }
    free(stack);
}

// --------------------------------------End of Pre Order Traversal-------------------------------------- //

bool isElementPresent(int count, struct TreeNode *arr[], struct TreeNode *data) {
    for (int i = 0; i < count; i++) {
        if (arr[i] != NULL && (arr[i]->val == data->val)) {
            return true;
        }
    }
    return false;
}

// --------------------------In Order Manual Recursion Simulation (Custom Approach)---------------------- //
void inOrderManual(struct TreeNode *node) {
    int count = getCount(node);
    struct TreeNode **stack = calloc(count, sizeof(struct TreeNode *));
    struct TreeNode **visited = calloc(count, sizeof(struct TreeNode *));
    int top = -1;
    int visitedIndex = -1;
    stack[++top] = node;
    while (top != -1) {
        struct TreeNode *currentNode = stack[top];
        if (isElementPresent(count, visited, currentNode)) {
            // pop current node
            printf("%d -> ", currentNode->val);
            stack[top] = NULL;
            top--;
            // push right node
            if (currentNode->right != NULL)
                stack[++top] = currentNode->right;
        }
        else {
            if (currentNode != NULL) {
                // push current node to visited
                visited[++visitedIndex] = currentNode;
                // push left node
                if (currentNode->left != NULL)
                    stack[++top] = currentNode->left;
            }
        }
    }
    free(stack);
    free(visited);
}

// ----------------------End of In Order Manual Recursion Simulation (Custom Approach)------------------- //

void freeTree(struct TreeNode *node)
{
    if (!node)
        return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main()
{
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    if (node == NULL)
    {
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

    printf("\nPre Order Traversal: ");
    preOrderManual(node);
    printf("\nIn Order Traversal: ");
    inOrderManual(node);

    freeTree(node);
    return 0;
}