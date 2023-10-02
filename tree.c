#include <stdio.h>
#include <stdlib.h>

// Linked 구조체 를 선언합니다. 
typedef struct TreeNode
{
    int data;
    struct TreeNode *left, *right;
} TreeNode;

// Linked 후위
void linkedPostorder(TreeNode *root)
{
    // root node 가 존재할 때 + ( node 가 null 이 아닐때 즉 node 가 존재할 경우)
    if (root)
    {
        // 후위 이기에 L R V 순서로 실행( 출력 )합니다.
        linkedPostorder(root->left);
        linkedPostorder(root->right);
        printf("%d ", root->data);
    }
}

// Linked 전위
void linkedPreorder(TreeNode *root)
{
    // root node 가 존재할 때 + ( node 가 null 이 아닐때 즉 node 가 존재할 경우)
    if (root)
    {
        // 중위 이기에 V L R 순서로 실행( 출력 )합니다.
        printf("%d ", root->data);
        linkedPreorder(root->left);
        linkedPreorder(root->right);
    }
}

// Linked 중위
void linkedInorder(TreeNode *root)
{
    // root node 가 존재할 때 + ( node 가 null 이 아닐때 즉 node 가 존재할 경우)
    if (root)
    {
        // 중위 이기에 L V R 순서로 실행( 출력 )합니다.
        linkedInorder(root->left); 
        printf("%d ", root->data);
        linkedInorder(root->right);
    }
}
//// 배열 표현법
// 배열 표현법으로 표현한 Tree
int tree[] = {NULL, 1, 2, 7, 3, 6, 8, 9, 4, 5, NULL, NULL, NULL, NULL, 10, 11};
int complete_node = 15; // 트리의 node의 갯수

// 배열 표현법에서 오른쪽 노드를 얻기 위한 함수
int getRightChild(int index)
{
    // 배열 index 의 위치에 있는 값이 null 이 아니고, tree의 node의 갯수보다 적을 때
    if (tree[index] != NULL && ((2 * index) + 1) <= complete_node)
    // node가 존재할 경우 오른쪽 노드를 return 합니다.
    // 이 떄 오른쪽 노드는 * 2 를 하여 찾습니다. 오른쪽 노드기에 +1을 해줍니다.
        return (2 * index) + 1;  
    return -1; // node 가 존재하지 않기에 -1 을 return 합니다.
}

int getLeftChild(int index)
{
    // 오른쪽 노드를 얻기위한 방법과 동일하게 처리합니다. 이때 오른쪽 노드가 아니기에 +1은 안합니다.
    if (tree[index] != NULL && (2 * index) <= complete_node)
        return 2 * index;
    return -1;
}

void arrayPreorder(int index)
{
    // index가 0 을 넘고 ( 정상적 index ) null 이 아닐경우 실행합니다.
    if (index > 0 && tree[index] != NULL)
    {
        // 전위 순위기에 V L R 순서로 실행( 출력 ) 합니다.
        printf("%d ", tree[index]);
        arrayPreorder(getLeftChild(index));
        arrayPreorder(getRightChild(index));
    }
}

void arrayPostorder(int index)
{
    if (index > 0 && tree[index] != NULL)
    {
        // 후위 순서기에 L R V 순서로 실행( 출력 ) 합니다.
        arrayPostorder(getLeftChild(index));
        arrayPostorder(getRightChild(index));
        printf("%d ", tree[index]);
    }
}

void arrayInorder(int index)
{
    if (index > 0 && tree[index] != NULL)
    {
        // 중위 순서기에 L V R 순서로 실행( 출력 ) 합니다.
        arrayInorder(getLeftChild(index));
        printf("%d ", tree[index]);
        arrayInorder(getRightChild(index));
    }
}

int main()
{
    /// Linked Tree 부분입니다.
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
