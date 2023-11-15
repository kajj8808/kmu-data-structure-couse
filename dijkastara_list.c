#include <stdio.h>
#include <stdlib.h>

#define NUM_VECTOR 10 // Vertex 개수를 define으로 정해둡니다.

// Edge구조체 입니다.
typedef struct
{
    int node[2]; // 두개의 연결되는 노드를 입력받습니다.
    int weight;  // Edge의 가중치를 입력받습니다.
} Edge;

// Edge를 만드는 함수입니다.
Edge *createEdge(int a, int b, int weight)
{
    Edge *newEdge = (Edge *)malloc(sizeof(Edge));
    newEdge->node[0] = a;
    newEdge->node[1] = b;
    newEdge->weight = weight;
    return newEdge;
}

void dijkstra(Edge **edges, int edgesNum)
{
    // dijkstra에서 사용할 변수를 선언합니다.
    int distance[NUM_VECTOR];   // distance 를 저장하는데 사용합니다.
    int prevDistanceIndex;      // 이전의 distance를 저장하여 다음 선에서 distance 값을 더하기 위해 사용합니다.
    int visited[NUM_VECTOR];    // 방문한 곳을 저장합니다.
    int visitOrder[NUM_VECTOR]; // 방문한 순서를 저장합니다.
    int visitOrderCount = 0;    // 방문한 순서를 저장하는데 사용합니다.

    // 초기값을 지정해줍니다. distance는 max값으로 999, visited는 방문하지 않은값을 0으로 초기화합니다.
    for (int i = 0; i < NUM_VECTOR; i++)
    {
        distance[i] = 999;
        visited[i] = 0;
    }
    // 초기에 1을 방문합니다.
    distance[0] = 0;
    prevDistanceIndex = 0;
    visitOrder[visitOrderCount] = 1;
    visited[visitOrderCount++] = 1;
    int vertex = 1;
    // 이후 반복합니다.
    while (1)
    {
        // 모든 선을 돕니다.
        for (int i = 0; i < edgesNum; i++)
        {
            // 그래프를 선언할떄 edge의 0은 시작점 1은 도착점을 지정하였습니다.
            // 0이므로 시작점이고, 시작점이 vertex와 같으면 다음 내용들을 진행합니다.
            if (edges[i]->node[0] == vertex)
            {
                // 연결 되어있는 vertex 도착점의 index를 변수로 저장합니다.
                int vertexIndex = edges[i]->node[1] - 1;
                // 저장되어 있는 distance가 현재 weight와 출발지 부터의 distance를 합쳐 적다면 distance 에 저장합니다.
                if (distance[vertexIndex] >= edges[i]->weight + distance[vertex - 1])
                {
                    distance[vertexIndex] = edges[i]->weight + distance[vertex - 1];
                }
            }
        }
        // 이후 Distance를 출력하고, 이후 진행할 vertex(가장 적은 distance를 가진 점)를 정합니다.
        int minDistanceIndex = 999;
        int minDistance = 999;
        printf("Distance: ");
        for (int i = 0; i < NUM_VECTOR; i++)
        {
            // 999 라면 distance를 찾지 못한것 이기떄문에 *을 출력합니다.
            if (distance[i] == 999)
            {
                printf("* ");
                continue;
            }
            // 방문한 적이 없고, distance 보다 작은 distance 라면 minDistance 를 옮깁니다.
            if (visited[i] == 0 && distance[i] < minDistance)
            {
                minDistance = distance[i];
                minDistanceIndex = i;
            }
            printf("%d ", distance[i]);
        }
        printf("\n");
        // 이때까지 찾은 vertex를 출력합니다.
        printf("Found: ");
        for (int i = 0; i < NUM_VECTOR; i++)
        {
            printf("%d ", visited[i]);
        }
        printf("\n\n");
        vertex = minDistanceIndex + 1;
        // minDistanceIndex 가 999 초기값 이라면 더이상 바꿀값이 없다는 뜻이기 떄문에 반복을 종료합니다.
        if (minDistanceIndex == 999)
        {
            break;
        }
        else
        {
            // 방문한 위치를 저장합니다.
            visited[minDistanceIndex] = 1;
            visitOrder[visitOrderCount++] = vertex;
        }
    }
    // 방문한 순서를 출력합니다.
    for (int i = 0; i < visitOrderCount; i++)
    {
        printf("%d ", visitOrder[i]);
    }
    printf("\n");
}

int main()
{
    // list로 그래프를 생성합니다. 이때 첫번째 칸에 출발 노드 두번째 칸에 도착 노드를 넣어둡니다.
    Edge **edges = (Edge **)malloc(20 * sizeof(Edge));

    edges[0] = createEdge(1, 2, 3);
    edges[1] = createEdge(1, 6, 11);
    edges[2] = createEdge(1, 7, 12);
    edges[3] = createEdge(5, 6, 9);
    edges[4] = createEdge(2, 6, 7);
    edges[5] = createEdge(2, 7, 8);
    edges[6] = createEdge(2, 5, 1);
    edges[7] = createEdge(3, 7, 6);
    edges[8] = createEdge(2, 3, 5);
    edges[9] = createEdge(2, 4, 4);
    edges[10] = createEdge(3, 4, 2);
    edges[11] = createEdge(7, 8, 13);
    edges[12] = createEdge(3, 8, 5);
    edges[13] = createEdge(4, 8, 14);
    edges[14] = createEdge(8, 10, 15);
    edges[15] = createEdge(4, 10, 16);
    edges[16] = createEdge(4, 5, 13);
    edges[17] = createEdge(5, 10, 17);
    edges[18] = createEdge(5, 9, 18);
    edges[19] = createEdge(9, 10, 10);
    // dijkstra 실행합니다.
    printf("Dijkstra Algorithm \n");
    dijkstra(edges, 20);

    return 0;
}
