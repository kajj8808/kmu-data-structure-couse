#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode *left, *right;
    int is_thread; // 만약 오른쪽 링크가 스레드이면 1 아니면 0
} TreeNode;

// 다음을 찾는 함수이빈다.
TreeNode *findSuccessor(TreeNode *p)
{

    TreeNode *q = p->right;
    // 만약 오른쪽 포인터가 NULL이거나 스레드이면 오른쪽 포인터를 반환합니다.
    // NULL 일 경우는 마지막 노드일 경우입니다. 이진이 불가능 한 상태입니다.
    if (q == NULL || p->is_thread == 1)
        return q;

    // 만약 오른쪽 자식이면 다시 가장 왼쪽 노드로 이동합니다.
    while (q->left != NULL)
    {
        q = q->left;
    }

    return q;
}

// 중위순회 함수입니다.
void threadInorder(TreeNode *t)
{
    TreeNode *q;
    q = t;
    // 중위 를 하기위해 가장 왼쪽 노드를 갑니다.
    while (q->left)
        q = q->left;
    do
    {
        // 현재 위치 의 값을 출력합니다.
        printf("%d ", q->data);
        // 노드의 위치를 옮깁니다.
        q = findSuccessor(q);
    } while (q); // 마지막 노드까지 돕니다.
}

TreeNode *parent(TreeNode *child)
{

    TreeNode *parentNode;
    // 오른쪽 노드가 없는경우 child를 return 합니다.
    if (!child->right)
        return child;

    // thread 으로 연결되어 있는 상태일 때
    if (child->is_thread == 1)
    {
        // 스레드로 연결되어 있기 때문에 오른쪽 노드로 가면 부모 노드기에 parentNode에 오른쪽 노드를 넣어줍니다.
        parentNode = child->right;
        // 만약 부모노드에서 왼쪽의 노드가 목표 노드 가 아니라면 한칸 위의 노드를 가르키고 있는거기 때문에 부모노드를 한번더 왼쪽으로 옮겨줍니다.
        if (parentNode->left != child)
        {
            parentNode = parentNode->left;
        }
    }

    return parentNode;
}

int main()
{
    /// Linked Tree
    struct TreeNode *n4 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    n4->data = 4;
    n4->left = NULL;
    n4->right = NULL;
    n4->is_thread = 0;

    struct TreeNode *n5 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    n5->data = 5;
    n5->left = NULL;
    n5->right = NULL;
    n5->is_thread = 0;

    struct TreeNode *n10 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    n10->data = 10;
    n10->left = NULL;
    n10->right = NULL;
    n10->is_thread = 0;

    struct TreeNode *n11 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    n11->data = 11;
    n11->left = NULL;
    n11->right = NULL;
    n11->is_thread = 0;

    struct TreeNode *n3 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    n3->data = 3;
    n3->left = n4;
    n3->right = n5;
    n3->is_thread = 0;

    struct TreeNode *n6 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    n6->data = 6;
    n6->left = NULL;
    n6->right = NULL;
    n6->is_thread = 0;

    struct TreeNode *n8 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    n8->data = 8;
    n8->left = NULL;
    n8->right = NULL;
    n8->is_thread = 0;

    struct TreeNode *n9 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    n9->data = 9;
    n9->left = n10;
    n9->right = n11;
    n9->is_thread = 0;

    struct TreeNode *n2 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    n2->data = 2;
    n2->left = n3;
    n2->right = n6;
    n2->is_thread = 0;

    struct TreeNode *n7 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    n7->data = 7;
    n7->left = n8;
    n7->right = n9;
    n7->is_thread = 0;

    struct TreeNode *n1 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    n1->data = 1;
    n1->left = n2;
    n1->right = n7;
    n1->is_thread = 0;

    n4->is_thread = 1;
    n4->right = n3;

    n5->is_thread = 1;
    n5->right = n2;

    n10->is_thread = 1;
    n10->right = n9;

    n6->is_thread = 1;
    n6->right = n1;

    n8->is_thread = 1;
    n8->right = n7;

    struct TreeNode *root = n1;
    // 중위 순회 결과.
    printf("1. 중위 순회 결과\n");
    threadInorder(root);
    printf("\n\n");
    // 특정 노드의 부모노드를 찾아서 반환하는 parent 함수 구현
    TreeNode *parentNode_n4 = parent(n4);
    printf("2. Node 4의 부모: %d\n", parentNode_n4->data);
    TreeNode *parentNode_n5 = parent(n5);
    printf("3. Node 5의 부모: %d\n", parentNode_n5->data);
    TreeNode *parentNode_n6 = parent(n6);
    printf("4. Node 5의 부모: %d\n", parentNode_n6->data);
    return 0;
}
