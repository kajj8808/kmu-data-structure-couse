#include <stdio.h>
#include <stdlib.h>
struct queue
{
    int items[50];
    int front;
    int rear;
};

struct node
{
    int vertex;
    struct node *link;
};

struct Graph
{
    int vertexs;
    struct node **adjLists;
    int *visited;
};

// 노드 생성
struct node *createNode(int v)
{
    struct node *newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->link = NULL;
    return newNode;
}

// 그래프 생성
struct Graph *createGraph(int vertexs)
{
    struct Graph *graph = malloc(sizeof(struct Graph));
    graph->vertexs = vertexs;

    graph->adjLists = malloc(vertexs * sizeof(struct node *));
    graph->visited = malloc(vertexs * sizeof(int));

    for (int i = 0; i < vertexs; i++)
    {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

// 간선 연결
void addEdge(struct Graph *graph, int src, int dest)
{
    // 출발지 부터 목적지 까지 간선을 연결합니다.
    struct node *newNode = createNode(dest);
    newNode->link = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    // 목적지부터 출발지 까지 간선을 연결합니다.
    newNode = createNode(src);
    newNode->link = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// 큐 생성
struct queue *createQueue()
{
    struct queue *q = malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;
    return q;
}
// 큐가 비어있는지 확인하는 함수
int isEmpty(struct queue *q)
{
    if (q->rear == -1)
        return 1;
    else
        return 0;
}
// 큐에 값을 넣는 함수
void enqueue(struct queue *q, int value)
{
    if (q->rear == 50 - 1)
        printf("\nQueue is Full!!");
    else
    {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

// 큐에서 값을 빼는 함수
int dequeue(struct queue *q)
{
    int item;
    if (isEmpty(q))
    {
        printf("Queue is empty");
        item = -1;
    }
    else
    {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear)
        {
            q->front = q->rear = -1;
        }
    }
    return item;
}

void bfsSearch(struct Graph *graph, int startVertex, int targetVertex)
{
    int nodeCount = 0;
    struct queue *q = createQueue();
    // visited 시작된 vertex를 넣어줍니다. -> 방문한 정점이라 표시합니다.
    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);

    while (!isEmpty(q))
    {
        int currentVertex = dequeue(q);
        printf("%d ", currentVertex);
        // target노드를 찾았을 경우 결과를 출력하고, 방문한 노드의 수를 출력합니다.
        if (currentVertex == targetVertex)
        {
            printf("\n탐색 성공: %d \n", targetVertex);
            printf("방문한 노드의 수: %d\n", nodeCount);
            break;
        }
        struct node *temp = graph->adjLists[currentVertex];
        while (temp)
        {
            int adjVertex = temp->vertex;
            // 방문하지 않은 vertex를 큐에 넣어줍니다.
            if (graph->visited[adjVertex] == 0)
            {
                nodeCount++;
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }
            temp = temp->link;
        }
    }
}

// 스택의 새로운 노드 생성
struct node *createStackNode(int v)
{
    struct node *stackNode = (struct node *)malloc(sizeof(struct node));
    stackNode->vertex = v;
    stackNode->link = NULL;
    return stackNode;
}

// 스택에 값을 추가하는 함수
void push(struct node **stackTop, int vertex)
{
    struct node *stackNode = createStackNode(vertex);
    stackNode->link = *stackTop;
    *stackTop = stackNode;
}

// 스택이 비어있는지 확인하는 함수
int isStackEmpty(struct node *stackTop)
{
    return stackTop == NULL;
}

// 스택에서 값을 제거하고 반환하는 함수
int pop(struct node **stackTop)
{
    if (isStackEmpty(*stackTop))
    {
        return -1;
    }
    struct node *tempNode = *stackTop;
    *stackTop = (*stackTop)->link;
    int popped = tempNode->vertex;
    free(tempNode);
    return popped;
}

// DFS 탐색 구현(스택)
void dfsSeach(struct Graph *graph, int startVertex, int targetVertex)
{
    // 스택 초기화
    struct node *stack = NULL;

    // 방문 배열을 초기화 (모든 노드를 방문하지 않음으로 설정)
    for (int i = 0; i < graph->vertexs; i++)
    {
        graph->visited[i] = 0;
    }

    // 시작 정점을 스택에 푸시
    push(&stack, startVertex);
    graph->visited[startVertex] = 1; // 시작 정점을 방문함으로 표시
    printf("%d ", startVertex);
    // 방문한 노드 수
    int visitedCount = 1;

    while (!isStackEmpty(stack))
    {
        // 스택에서 데이터 를 꺼냅니다.
        int currentVertex = pop(&stack);

        // 목표 정점을 찾으면 종료
        if (currentVertex == targetVertex)
        {
            printf("\n탐색 성공: %d\n", targetVertex);
            printf("방문한 노드 수: %d\n", visitedCount);
            return;
        }

        // 인접 정점을 확인하고 방문
        struct node *temp = graph->adjLists[currentVertex];
        while (temp)
        {
            int adjVertex = temp->vertex;

            if (graph->visited[adjVertex] == 0)
            {
                printf("%d ", adjVertex);
                push(&stack, adjVertex);
                graph->visited[adjVertex] = 1;
                visitedCount++; // 방문한 노드 수 증가
            }
            temp = temp->link;
        }
    }

    printf("방문한 노드 수: %d\n", visitedCount);
}

int main()
{

    int menu = 0;
    printf("--------------------------------\n");
    printf("1\t: 깊이 우선 탐색\t|\n");
    printf("2\t: 너비 우선 탐색\t|\n");
    printf("3\t: 종료\t\t\t|\n");
    printf("--------------------------------\n\n\n");
    while (1)
    {
        struct Graph *graph = createGraph(10);
        addEdge(graph, 0, 2);
        addEdge(graph, 0, 4);
        addEdge(graph, 0, 5);
        addEdge(graph, 0, 6);
        addEdge(graph, 0, 9);
        addEdge(graph, 2, 3);
        addEdge(graph, 2, 4);
        addEdge(graph, 3, 4);
        addEdge(graph, 3, 5);
        addEdge(graph, 4, 1);
        addEdge(graph, 4, 5);
        addEdge(graph, 4, 6);
        addEdge(graph, 4, 7);
        addEdge(graph, 5, 1);
        addEdge(graph, 1, 7);
        addEdge(graph, 1, 10);
        addEdge(graph, 10, 7);
        addEdge(graph, 10, 8);
        addEdge(graph, 8, 9);
        addEdge(graph, 8, 6);
        addEdge(graph, 6, 7);

        printf("메뉴 입력: ");
        scanf("%d", &menu);
        switch (menu)
        {
        case 1:
            dfsSeach(graph, 1, 9);
            printf("\n\n");
            break;
        case 2:
            bfsSearch(graph, 1, 9);
            printf("\n\n");
            break;
        case 3:
            exit(0);
        default:
            break;
        }
    }
}
