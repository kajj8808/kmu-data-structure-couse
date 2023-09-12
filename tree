#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode *left, *right;
} TreeNode;

// Linked 후위
void linkedPostorder(TreeNode *root)
{

    if (root)
    {
        linkedPostorder(root->left);
        linkedPostorder(root->right);
        printf("%d ", root->data);
    }
}

// Linked 전위
void linkedPreorder(TreeNode *root)
{
    if (root)
    {
        printf("%d ", root->data);
        linkedPreorder(root->left);
        linkedPreorder(root->right);
    }
}

// Linked 중위
void linkedInorder(TreeNode *root)
{
    if (root)
    {
        linkedInorder(root->left);
        printf("%d ", root->data);
        linkedInorder(root->right);
    }
}
//// Array Part
// array
int tree[] = {NULL, 1, 2, 7, 3, 6, 8, 9, 4, 5, NULL, NULL, NULL, NULL, 10, 11};
int complete_node = 15;

int getRightChild(int index)
{
    if (tree[index] != NULL && ((2 * index) + 1) <= complete_node)
        return (2 * index) + 1;
    return -1;
}

int getLeftChild(int index)
{
    if (tree[index] != NULL && (2 * index) <= complete_node)
        return 2 * index;
    return -1;
}

void arrayPreorder(int index)
{
    if (index > 0 && tree[index] != NULL)
    {
        printf("%d ", tree[index]);
        arrayPreorder(getLeftChild(index));
        arrayPreorder(getRightChild(index));
    }
}

void arrayPostorder(int index)
{
    if (index > 0 && tree[index] != NULL)
    {
        arrayPostorder(getLeftChild(index));
        arrayPostorder(getRightChild(index));
        printf("%d ", tree[index]);
    }
}

void arrayInorder(int index)
{
    if (index > 0 && tree[index] != NULL)
    {
        arrayInorder(getLeftChild(index));
        printf("%d ", tree[index]);
        arrayInorder(getRightChild(index));
    }
}

int main()
{
    /// Linked Tree

    TreeNode *n1 = (TreeNode *)malloc(sizeof(TreeNode));
    n1->data = 4;
    n1->left = NULL;
    n1->right = NULL;

    TreeNode *n2 = (TreeNode *)malloc(sizeof(TreeNode));
    n2->data = 5;
    n2->left = NULL;
    n2->right = NULL;

    TreeNode *n3 = (TreeNode *)malloc(sizeof(TreeNode));
    n3->data = 10;
    n3->left = NULL;
    n3->right = NULL;

    TreeNode *n4 = (TreeNode *)malloc(sizeof(TreeNode));
    n4->data = 11;
    n4->left = NULL;
    n4->right = NULL;

    TreeNode *n5 = (TreeNode *)malloc(sizeof(TreeNode));
    n5->data = 3;
    n5->left = n1;
    n5->right = n2;

    TreeNode *n6 = (TreeNode *)malloc(sizeof(TreeNode));
    n6->data = 6;
    n6->left = NULL;
    n6->right = NULL;

    TreeNode *n7 = (TreeNode *)malloc(sizeof(TreeNode));
    n7->data = 8;
    n7->left = NULL;
    n7->right = NULL;

    TreeNode *n8 = (TreeNode *)malloc(sizeof(TreeNode));
    n8->data = 9;
    n8->left = n3;
    n8->right = n4;

    TreeNode *n9 = (TreeNode *)malloc(sizeof(TreeNode));
    n9->data = 2;
    n9->left = n5;
    n9->right = n6;

    TreeNode *n10 = (TreeNode *)malloc(sizeof(TreeNode));
    n10->data = 7;
    n10->left = n7;
    n10->right = n8;

    TreeNode *n11 = (TreeNode *)malloc(sizeof(TreeNode));
    n11->data = 1;
    n11->left = n9;
    n11->right = n10;

    TreeNode *root = n11;
    printf("<Linked Tree>\n");
    printf("1. 전위 순회\n");
    linkedPreorder(root);
    printf("\n");
    printf("2. 중위 순회\n");
    linkedInorder(root);
    printf("\n");
    printf("3. 후위 순회\n");
    linkedPostorder(root);
    printf("\n");
    /// Array Tree
    printf("<Array Tree>\n");
    printf("1. 전위 순회\n");
    arrayPreorder(1);
    printf("\n");
    printf("2. 중위 순회\n");
    arrayInorder(1);
    printf("\n");
    printf("3. 후위 순회\n");
    arrayPostorder(1);
    printf("\n");

    return 0;
}
