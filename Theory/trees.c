//TREES
#include <stdio.h>
#include <stdlib.h>

struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
    struct TreeNode *parent;
};

struct TreeNode * newNode(int data)
{
    struct TreeNode *node=(struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

// Print nodes in preorder
void PrintPreorder(struct TreeNode *node)
{
    if (node == NULL)
        return;
    printf("%d ", node->data);
    PrintPreorder(node->left);
    PrintPreorder(node->right);
}
// Print nodes in inorder
void PrintInorder(struct TreeNode *node)
{
    if (node == NULL)
        return;
    PrintInorder(node->left);
    printf("%d ", node->data);
    PrintInorder(node->right);
}
// Print nodes in postorder
void PrintPostorder(struct TreeNode *node)
{
    if (node == NULL)
        return;
    PrintPostorder(node->left);
    PrintPostorder(node->right);
    printf("%d ", node->data);
}

int main()
{
    // Create tree
    struct TreeNode *root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);

    // Print Tree in different orders
    PrintPreorder(root);
    printf("\n");
    PrintInorder(root);
    printf("\n");
    PrintPostorder(root);

    return 0;
}