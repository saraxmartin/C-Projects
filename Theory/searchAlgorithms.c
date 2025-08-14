#include <stdio.h>

// Create a tree
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node * createNode(int value)
{

}

void Create_tree()
{
    // We create 5 nodes
    struct Node *p = createNode(5);
    struct Node *p1 = createNode(3);
    struct Node *p2 = createNode(6);
    struct Node *p3 = createNode(1);
    struct Node *p4 = createNode(4);
    //p->left = p1;
    //p->right = p2;
    //p1->left = p3;
    //p1->right = p4;
}
struct node * Search_Iteration(struct Node * root, int key)
{
    while (root!=NULL)
    {
        if (key == root->data)
            return root;
        else if (key < root->data)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}

