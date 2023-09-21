#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode *left, *right;
    int is_thread; // 만약 오른쪽 링크가 스레드이면 TRUE
} TreeNode;

TreeNode *find_successor(TreeNode *p) // 다음을 찾는 루틴
{
    // q는 p의 오른쪽 포인터
    TreeNode *q = p->right;
    // 만약 오른쪽 포인터가 NULL이거나 스레드이면 오른쪽 포인터를 반환
    if (q == NULL || p->is_thread == 1)
        // q == NULL // 오른쪽 마지막 노드일떄 스레드 이진이 불가능하기에..
        return q;

    // 만약 오른쪽 자식이면 다시 가장 왼쪽 노드로 이동
    while (q->left != NULL)
    {
        q = q->left;
    }

    return q;
}

void thread_inorder(TreeNode *t) // 찾아가는 함수
{
    TreeNode *q;
    q = t;
    while (q->left)
        q = q->left; // 가장 왼쪽 노드로 간다.
    do
    {
        printf("%d ", q->data); // 데이터 출력 여긴 방문, 이후 다음을 찾는 것.
        q = find_successor(q);  // 후속자 함수 호출
    } while (q);                // NULL이 아니면 NULL일떄는 E인 경우 뿐임.
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
    n5->right = n6;

    n10->is_thread = 1;
    n10->right = n9;

    n6->is_thread = 1;
    n6->right = n1;

    n8->is_thread = 1;
    n8->right = n7;

    struct TreeNode *root = n1;
    thread_inorder(root);
    return 0;
}
