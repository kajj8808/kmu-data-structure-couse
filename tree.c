#include <stdio.h>
#include <stdlib.h>

// 트리 노드 구조체 정의
typedef struct TreeNode
{
    double data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

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

// 스택을 만드는 함수
struct Stack *createStack()
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}

// 스택 push 함수
void push(struct Stack *stack, struct TreeNode *data)
{
    struct StackNode *newNode = (struct StackNode *)malloc(sizeof(struct StackNode));
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

// 스택 pop 함수
struct TreeNode *pop(struct Stack *stack)
{
    if (stack->top == NULL)
    {
        return NULL; // 빈 스택일 경우 NULL 을 리턴해 없다는 것을 알려줍니다.
    }
    struct StackNode *temp = stack->top;
    stack->top = stack->top->next;
    struct TreeNode *popped = temp->data;
    free(temp); // 임시로 만들어놓은 temp을 메모리에서 할당을 풀어줍니다.
    return popped;
}

// 숫자인지 확인하는 함수입니다. 수식인지 확인하기 위해서 사용합니다.
int isDigit(char c)
{
    return (c >= 0 && c <= 9);
}

// 수식을 계산하는 함수
double evaluateExpression(TreeNode *root)
{
    if (root)
    {
        // 수식이 아닌 숫자라면 계산하지 않아도 되니 넘어가줍니다.
        if (isDigit(root->data))
        {
            return root->data;
        }
        else
        {
            // 왼쪽과 오른쪽 트리를 계산합니다.
            double left = evaluateExpression(root->left);
            double right = evaluateExpression(root->right);

            // 수식의 왼쪽 오른쪽 값을 참고해 값을 계산합니다.
            // 출력은 num1 + num2 = result 식으로 출력됩니다.
            // 그리고 계산값은 return 을 하여 다음 계산으로 넘어갑니다.
            double result;
            switch ((int)root->data)
            {
            case '+':
                result = left + right;
                printf("%0.2f + %0.2f = %0.2f\n", left, right, result);
                break;
            case '-':
                result = left - right;
                printf("%0.2f - %0.2f = %0.2f\n", left, right, result);
                break;
            case '*':
                result = left * right;
                printf("%0.2f * %0.2f = %0.2f\n", left, right, result);
                break;
            case '/':
                if (right != 0)
                    result = left / right;
                printf("%0.2f / %0.2f = %0.2f\n", left, right, result);
                break;
            }

            return result;
        }
    }
    return 0;
}
// 수식 트리함수
void expressionTree(TreeNode *root)
{
    // 수식 트리를 계산하고 결과를 출력합니다.
    double result = evaluateExpression(root);
    // 수식 트리 의 계산 결과를 출력합니다.
    printf("수식의 값은 %0.2f입니다.\n", result);
}
// 총 노드의 갯수를 알기위해 사용합니다.
int countNode = 0;
// 후위 순회 함수
void postorderTraversal(struct TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    struct Stack *stack1 = createStack();
    struct Stack *stack2 = createStack();
    push(stack1, root);
    while (stack1->top != NULL)
    {
        struct TreeNode *current = pop(stack1);
        push(stack2, current);
        if (current->left != NULL)
        {
            push(stack1, current->left);
        }
        if (current->right != NULL)
        {
            push(stack1, current->right);
        }
    }
    // 후위 방식으로 추가된 item을 pop으로 빼내고 이때 총 노도의 갯수를 확인하기 위해 countNode 을 증감시켜줍니다.
    while (stack2->top != NULL)
    {
        pop(stack2);
        countNode++;
    }
    // stack을 메모리에서 해체시켜 줍니다.
    free(stack1);
    free(stack2);
}

int main()
{
    TreeNode *m13 = (TreeNode *)malloc(sizeof(TreeNode));
    m13->data = 5;
    m13->left = NULL;
    m13->right = NULL;

    TreeNode *m12 = (TreeNode *)malloc(sizeof(TreeNode));
    m12->data = 4;
    m12->left = NULL;
    m12->right = NULL;

    TreeNode *m11 = (TreeNode *)malloc(sizeof(TreeNode));
    m11->data = (int)'*';
    m11->left = m12;
    m11->right = m13;

    TreeNode *m10 = (TreeNode *)malloc(sizeof(TreeNode));
    m10->data = 3;
    m10->left = NULL;
    m10->right = NULL;

    TreeNode *m7 = (TreeNode *)malloc(sizeof(TreeNode));
    m7->data = (int)'+';
    m7->left = m10;
    m7->right = m11;

    TreeNode *m6 = (TreeNode *)malloc(sizeof(TreeNode));
    m6->data = 2;
    m6->left = NULL;
    m6->right = NULL;

    TreeNode *m4 = (TreeNode *)malloc(sizeof(TreeNode));
    m4->data = (int)'+';
    m4->left = m6;
    m4->right = m7;

    TreeNode *m8 = (TreeNode *)malloc(sizeof(TreeNode));
    m8->data = 6;
    m8->left = NULL;
    m8->right = NULL;

    TreeNode *m9 = (TreeNode *)malloc(sizeof(TreeNode));
    m9->data = 7;
    m9->left = NULL;
    m9->right = NULL;

    TreeNode *m5 = (TreeNode *)malloc(sizeof(TreeNode));
    m5->data = (int)'/';
    m5->left = m8;
    m5->right = m9;

    TreeNode *m2 = (TreeNode *)malloc(sizeof(TreeNode));
    m2->data = (int)'-';
    m2->left = m4;
    m2->right = m5;

    TreeNode *m3 = (TreeNode *)malloc(sizeof(TreeNode));
    m3->data = 9;
    m3->left = NULL;
    m3->right = NULL;

    TreeNode *m1 = (TreeNode *)malloc(sizeof(TreeNode)); // root node
    m1->data = (int)'+';
    m1->left = m2;
    m1->right = m3;
    // 1. 다음 수식을 수식트리로 만든 뒤 결과를 계산하고 출력하기
    expressionTree(m1);
    // 2. 이진 트리의 노드 수를 반복적 방법으로 계산하고 출력하기
    postorderTraversal(m1);
    printf("\n총 노드의 수는 %d개 입니다.", countNode);
}
