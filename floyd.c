#include <stdio.h>

#define INF 1000L

typedef struct GraphType
{
    int n;
    int weight[100][100];
} GraphType;

int A[100][100];
int P[100][100]; // path

// 가중치를 출력하는 함수입니다.
void printA(GraphType *g)
{
    printf("============================================================================\n");
    // 각각의 가중치 들을 출력합니다.
    for (int i = 0; i < g->n; i++)
    {
        for (int j = 0; j < g->n; j++)
        {
            printf("%d\t", A[i][j]);
        }
        printf("\n");
    }
}

void floyd(GraphType *g)
{
    // 사용할 배열들을 초기화 시켜줍니다.
    // A -> 가중치 배열 P -> 경로 배열
    for (int i = 0; i < g->n; i++)
    {
        for (int j = 0; j < g->n; j++)
        {
            A[i][j] = g->weight[i][j];
            P[i][j] = 0;
        }
    }
    // 초기 상태를 출력합니다.
    // printA(g);
    // 각 점마다 최단거리를 찾습니다.
    for (int k = 0; k < g->n; k++)
    {
        for (int i = 0; i < g->n; i++)
        {
            for (int j = 0; j < g->n; j++)
            {
                if (A[i][k] + A[k][j] < A[i][j])
                {
                    A[i][j] = A[i][k] + A[k][j]; // A의 경우 가장 빠른 Distance를 기억합니다.
                    P[i][j] = k + 1;             // P의 경우 가장 빠른곳 으로 가는 점을 기억해 둡니다.
                }
            }
        }
        // printA(g);
    }
}

// 경로를 출력하는 함수입니다.
void printPath(int startNode, int endNode)
{
    // 경로를 저장합니다.
    int path[100];
    int pathIndex = 0;
    int start = startNode;
    int end = endNode;

    // 경로들을 저장해둔 배열에서 현재 가야할 경로를 가져옵니다.
    // P 의 경우 가장 짦은 경로를 의 점을 저장하고 있습니다.
    // 그렇기에 end point를 변경하고 갱신하며 경로를 가져옵니다.
    while (P[start][end] != 0)
    {
        path[pathIndex++] = P[start][end];
        end = P[start][end] - 1;
    }
    // 경로를 출력합니다.
    printf("Shortest Distance: ");
    printf("(%d,", start + 1);
    // 도착지점에서 출력지점으로 값을 넣었으므로,
    // 역순으로 출력합니다  5 , 2 , 1 -> 1 , 2 , 5
    for (int i = pathIndex - 1; i >= 0; i--)
    {
        printf("%d,", path[i]);
    }
    printf("%d) ", endNode + 1);
}

int main()
{
    GraphType graph = {10, {
                               {0, 3, INF, INF, INF, 11, 12, INF, INF, INF},
                               {INF, 0, 5, 4, 1, 7, 8, INF, INF, INF},
                               {INF, 5, 0, 2, INF, INF, 6, 5, INF, INF},
                               {INF, 4, 2, 0, 13, INF, INF, INF, INF, 16},
                               {INF, 1, INF, 13, 0, 9, INF, INF, 18, 17},
                               {11, 7, INF, INF, 9, 0, INF, INF, INF, INF},
                               {12, 8, 6, INF, INF, INF, 0, 13, INF, INF},
                               {INF, INF, 5, 14, INF, INF, 13, 0, INF, 15},
                               {INF, INF, INF, INF, 18, INF, INF, INF, 0, 10},
                               {INF, INF, INF, 16, 17, INF, INF, 15, 10, 0},
                           }};
    floyd(&graph);
    // 값을 입력받아 줍니다.
    int startNode, endNode;
    while (1)
    {
        printf("Start Node : ");
        scanf("%d", &startNode);
        printf("End Node : ");
        scanf("%d", &endNode);
        printf("Shortest Distance: %d\n", A[startNode - 1][endNode - 1]);
        printPath(startNode - 1, endNode - 1);
        printf("\n\n");
    }
}
