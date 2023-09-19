#include <stdio.h>
#include <stdlib.h>

// 트리 노드 구조체
struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

// 스택 노드 구조체
struct StackNode
{
    struct TreeNode *data;
    struct StackNode *next;
};

// 스택 구조체
struct Stack
{
    struct StackNode *top;
};

// 스택을 만드는 함수입니다. 초기화도 같이 진행합니다.
struct Stack *createStack()
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}

// 스택 push 함수입니다. 스택에 값을 넣을때 사용합니다.
void push(struct Stack *stack, struct TreeNode *data)
{
    struct StackNode *newNode = (struct StackNode *)malloc(sizeof(struct StackNode));
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

// 스택 pop 함수입니다. 스택에서 값을 뺄때 사용합니다.
struct TreeNode *pop(struct Stack *stack)
{
    if (stack->top == NULL)
    {
        return NULL; // 빈 스택 일 경우 NULL 을 리턴해 없다는것을 알려줍니다.
    }
    struct StackNode *temp = stack->top;
    stack->top = stack->top->next;
    struct TreeNode *popped = temp->data;
    free(temp); 
    return popped;
}

// 전위 순회 방식입니다.
void preorderTraversal(struct TreeNode *root)
{
    if (root == NULL)
    {
        return; // 빈 트리 노드의 경우 종료합니다.
    }
    // 스택생성
    struct Stack *stack = createStack();
    // 루트 노드를 스택에 추가
    push(stack, root);
    // 스택이 비어있지 않은 동안 반복합니다.
    while (stack->top != NULL)
    {
        // 스택에서 노드를 가져옵니다.
        struct TreeNode *current = pop(stack);
        // 노드의 데이터를 출력합니다. ( 전위 )
        printf("%d ", current->data);
        if (current->right != NULL)
        {
            push(stack, current->right); // 오른쪽 노드를 스택에 추가
        }
        if (current->left != NULL)
        {
            push(stack, current->left); // 왼쪽 노드를 스택에 추가
        }
    }
    free(stack); // 스택 메모리 해제
}

// 중위 순회
void inorderTraversal(struct TreeNode *root)
{
    if (root == NULL)
    {
        return; // 빈트리의 경우에 종료
    }
    // 스택 생성
    struct Stack *stack = createStack(); 
    struct TreeNode *current = root;
    // 스택이 비어있지 않는 동안 돕니다.
    while (current != NULL || stack->top != NULL) 
    {
        while (current != NULL)
        {
            // 현재 노드를 스택에 추가합니다.
            push(stack, current); 
            // 왼쪽 노드로 이동합니다.
            current = current->left;
        }
        // 스택에서 노드를 가져옵니다.
        current = pop(stack);
        // 노드의 데이터를 출력합니다. (중위)
        printf("%d ", current->data);
        // 오른쪽 노드로 이동합니다.
        current = current->right;
    }
    // 스택메모리를 해제합니다.
    free(stack);
}

// 후위 순회
void postorderTraversal(struct TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    // 후위의 경우 스택을 두개를 사용해 구현합니다.
    struct Stack *stack1 = createStack();
    struct Stack *stack2 = createStack();
    // 루트 노드를 첫번째 스택에 추가합니다.
    push(stack1, root);
    while (stack1->top != NULL)
    {
        // 스택 에서 노드를 가져옵니다.
        struct TreeNode *current = pop(stack1);
        // 두번쨰 스택에 노드를 추가합니다 ( 역순 저장 )
        push(stack2, current);
        if (current->left != NULL)
        {
            // 왼쪽 노드를 첫 번쨰 스택에 추가합니다.
            push(stack1, current->left);
        }
        if (current->right != NULL)
        {
            // 오른쪽 노드를 첫 번째 스택에 추가합니다.
            push(stack1, current->right);
        }
    }
    while (stack2->top != NULL)
    {
        struct TreeNode *current = pop(stack2); // 두 번째 스택에서 노드를 꺼내옵니다.
        printf("%d ", current->data); // 노드의 데이터를 출력합니다. ( 후위 순회 )
    }
    // 스택 메모리 해제
    free(stack1);
    free(stack2);
}

int main()
{
    /// Linked Tree
    struct TreeNode *n1 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    n1->data = 4;
    n1->left = NULL;
    n1->right = NULL;

    struct TreeNode *n2 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    n2->data = 5;
    n2->left = NULL;
    n2->right = NULL;

    struct TreeNode *n3 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    n3->data = 10;
    n3->left = NULL;
    n3->right = NULL;

    struct TreeNode *n4 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    n4->data = 11;
    n4->left = NULL;
    n4->right = NULL;

    struct TreeNode *n5 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    n5->data = 3;
    n5->left = n1;
    n5->right = n2;

    struct TreeNode *n6 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    n6->data = 6;
    n6->left = NULL;
    n6->right = NULL;

    struct TreeNode *n7 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    n7->data = 8;
    n7->left = NULL;
    n7->right = NULL;

    struct TreeNode *n8 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    n8->data = 9;
    n8->left = n3;
    n8->right = n4;

    struct TreeNode *n9 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    n9->data = 2;
    n9->left = n5;
    n9->right = n6;

    struct TreeNode *n10 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    n10->data = 7;
    n10->left = n7;
    n10->right = n8;

    struct TreeNode *n11 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    n11->data = 1;
    n11->left = n9;
    n11->right = n10;

    struct TreeNode *root = n11;

    printf("<Traversal with Stack>\n");
    printf("1. 전위 순회\n");
    preorderTraversal(root);
    printf("\n");
    printf("2. 중위 순회\n");
    inorderTraversal(root);
    printf("\n");
    printf("3. 후위 순회\n");
    postorderTraversal(root);
    printf("\n");

    return 0;
}
