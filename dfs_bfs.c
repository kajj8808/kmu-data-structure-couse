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

void dfsSeach(struct Graph *graph, int startVertex, int targetVertex)
{
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

int main()
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
    dfsSeach(graph, 1, 9);
    bfsSearch(graph, 1, 9);
}
