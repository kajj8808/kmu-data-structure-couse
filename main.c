#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 256

/// num ////////////////////////

typedef struct NodeNumType
{
    int num;
    struct NodeNumType *left;
    struct NodeNumType *right;
} NodeNumType;

typedef struct PriorityQueueNumType
{
    int size;
    NodeNumType **nodes;
} PriorityQueueNumType;
// heap 정수 정렬
void enqueueNum(PriorityQueueNumType *queue, NodeNumType *node)
{
    int i = queue->size;
    while (i > 0)
    {
        int parent = (i - 1) / 2; // size / 2 -> 부모노드
        if (queue->nodes[parent]->num > node->num)
        {
            queue->nodes[i] = queue->nodes[parent];
            i = parent;
        }
        else
        {
            break;
        }
    }
    queue->nodes[i] = node;
}

NodeNumType *dequeueNum(PriorityQueueNumType *queue)
{
    NodeNumType *node = queue->nodes[0]; // 가장큰 값.
    int last = --queue->size;            // 마지막 노드
    int i = 0;
    while (i * 2 + 1 <= last)
    {
        int child = i * 2 + 1;
        if (child < last && queue->nodes[child]->num > queue->nodes[child + 1]->num)
        {
            child++;
        }
        if (queue->nodes[child]->num < queue->nodes[last]->num)
        {
            queue->nodes[i] = queue->nodes[child];
            i = child;
        }
        else
        {
            break;
        }
        queue->nodes[i] = queue->nodes[last];
        return node;
    }
}

PriorityQueueNumType *createProitorityNumQueue(int len)
{
    PriorityQueueNumType *queue = (PriorityQueueNumType *)malloc(sizeof(PriorityQueueNumType));
    queue->size = 0;
    queue->nodes = (NodeNumType **)malloc(sizeof(NodeNumType *) * len);
    return queue;
}

NodeNumType *createNumNode(int data)
{
    NodeNumType *node = (NodeNumType *)malloc(sizeof(NodeNumType));
    node->num = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

////////////////////////////////////
// 허프만 코드
typedef struct Node
{
    char data;
    int freq;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct PriorityQueue
{
    int size;
    Node **nodes;
} PriorityQueue;

// 큐에 사용할 node를 초기화 해주는 함수입니다.
Node *createNode(char data, int freq)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->freq = freq;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 큐를 초기화 하는함수입니다.
PriorityQueue *createPriorityQueue(int capacity)
{
    PriorityQueue *queue = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    queue->size = 0;
    queue->nodes = (Node **)malloc(sizeof(Node *) * capacity);
    return queue;
}

// 우선순위 큐에 값을 넣는 함수입니다.
void enqueue(PriorityQueue *queue, Node *node)
{
    int i = queue->size++;
    while (i > 0)
    {
        int parent = (i - 1) / 2;
        if (queue->nodes[parent]->freq > node->freq)
        {

            queue->nodes[i] = queue->nodes[parent];
            i = parent;
        }
        else
        {
            break;
        }
    }
    queue->nodes[i] = node;
}

// 우선순위 큐에서 값을 빼는 함수입니다.
Node *dequeue(PriorityQueue *queue)
{
    Node *node = queue->nodes[0];
    int last = --queue->size;
    int i = 0;
    while (i * 2 + 1 <= last)
    {
        int child = i * 2 + 1;
        if (child < last && queue->nodes[child]->freq > queue->nodes[child + 1]->freq)
        {
            child++;
        }
        if (queue->nodes[child]->freq < queue->nodes[last]->freq)
        {
            queue->nodes[i] = queue->nodes[child];
            i = child;
        }
        else
        {
            break;
        }
    }
    queue->nodes[i] = queue->nodes[last];
    return node;
}

// 허프만 코드를 생성하는 함수입니다.
Node *buildHuffmanTree(int *freqs, char *chars, int len)
{
    PriorityQueue *queue = createPriorityQueue(len);

    // 각 노드를 생성하고 우선순위 큐에 저장합니다.
    for (int i = 0; i < len; i++)
    {
        Node *node = createNode(chars[i], freqs[i]);
        enqueue(queue, node);
    }

    // 우선순위 큐에서 노드를 꺼내어 허프만 트리를 생성합니다
    while (queue->size > 1)
    {
        Node *left = dequeue(queue);
        Node *right = dequeue(queue);
        Node *parent = createNode(chars[0], left->freq + right->freq); // 첫 번째 노드의 data 값 복사합니다.
        parent->left = left;
        parent->right = right;
        enqueue(queue, parent);
    }

    // 마지막으로 남은 노드를 반환합니다.
    return dequeue(queue);
}

void printHuffmanCode(Node *node, char *code, int depth)
{
    // 둘다 NULL 이라면 더이상 갈곳이 없기떄문에 결과값을 출력한후 return을 합니다.
    if (node->left == NULL && node->right == NULL)
    {
        printf("%c: %s\n", node->data, code);
        return;
    }
    // 노드의 왼쪽 오른쪽을 보면서 0 인지 1 인지 확인을 합니다. 이후 재귀를 돌려 위에서 값을 출력합니다.
    if (node->left != NULL)
    {
        code[depth] = '0';
        printHuffmanCode(node->left, code, depth + 1);
    }
    if (node->right != NULL)
    {
        code[depth] = '1';
        printHuffmanCode(node->right, code, depth + 1);
    }
    // 코드끝에 마지막에 null문자열을 넣어 이상한 값이 나오는것을 방지합니다.
    code[depth] = '\0'; // 코드 끝에 null 문자 추가
}

int main()
{
    /* int numList[] = {34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 34, 85, 29, 78, 41, 56, 86};
    int numListLen = sizeof(numList) / sizeof(int);
    // num list 코드를 생성합니다.
    PriorityQueueNumType *numQueue = createProitorityNumQueue(numListLen);
    // num node 를 생성하고 우선순위 큐에 저장합니다.
    for (int i = 0; i < numListLen; i++)
    {
        NodeNumType *node = createNumNode(numList[i]);
        enqueueNum(numQueue, node);
    }

    while (numQueue->size > 1)
    {
        NodeNumType *left = dequeueNum(numQueue);
        NodeNumType *right = dequeueNum(numQueue);
        NodeNumType *parent = createNumNode(numList[0]); // 첫 번째 노드의 data 값 복사합니다.
        parent->left = left;
        parent->right = right;
        enqueueNum(numQueue, parent);
    }

    NodeNumType *numRoot = dequeueNum(numQueue);
    printf("%d\n", numRoot->left->num); */

    /* a ➔ 10
    e ➔ 15
    i ➔ 12
    o ➔ 3
    u ➔ 4
    s ➔ 13
    t ➔ 1 */
    /// 허프만
    int freqs[] = {10, 15, 12, 3, 4, 13, 1};
    char chars[] = {'a', 'e', 'i', 'o', 'u', 's', 't'};
    int len = sizeof(freqs) / sizeof(int);
    // 허프만 코드를 생성합니다.
    Node *root = buildHuffmanTree(freqs, chars, len);
    char code[MAX_SIZE];
    memset(code, 0, sizeof(code));
    printHuffmanCode(root, code, 0);
}
