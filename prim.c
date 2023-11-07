#include <stdio.h>

// 무한 값 선택할수 없는 곳을 표현하기 위해 사용
#define INF 1000L

// 그래프 구조체
typedef struct GraphType
{
    int n;
    int weight[100][100];
} GraphType;

int selected[100]; // 선택된 vertex를 저장해두는 배열
int distance[100]; // 업데이트 되는 vertex가중치 배열

int getMinVertex(int num)
{
    int currentVertex; // 결과 vertex(가장 작은)를 저장해 두는 변수입니다.
    for (int i = 0; i < num; i++)
    {
        if (!selected[i])
        {
            currentVertex = i; // 선택하지 않은 vertex를 선택합니다.
            break;
        }
    }
    // 이후 distance -> 업데이트 되고있는 가중치 에서 가장 작은 가중치를 찾아 가장 작은 vertex를 찾습니다.
    for (int i = 0; i < num; i++)
    {
        if (!selected[i] && (distance[i] < distance[currentVertex]))
        {
            currentVertex = i;
        }
    }
    // 가장 작은 vertex를 리턴합니다.
    return currentVertex;
}

void MSTPrim(GraphType *graph, int startNode)
{

    int currentVertex;
    for (int i = 0; i < graph->n; i++)
    {
        distance[i] = INF; // distance를 초기화 합니다. 이때 못가는 곳이라는 뜻으로 INF를 지정합니다.
    }
    // start node 를 방문합니다.
    distance[startNode] = 0;
    for (int i = 0; i < graph->n; i++)
    {
        // 가장 작은 vertex를 찾아 방문합니다.
        currentVertex = getMinVertex(graph->n);
        selected[currentVertex] = 1;
        // 이때 가중치가 INF 라면 갈곳이 없으므로 return 을 합니다.
        if (distance[currentVertex] == INF)
        {
            return;
        }
        // 추가된 정점을 출력합니다. 이떄 index로 돌아가고 있기 때문에 +1 을 해줍니다.
        printf("정점 %d 추가\n", currentVertex + 1);
        // 가중치 들을 업데이트 해줍니다.
        for (int j = 0; j < graph->n; j++)
        {
            // 갈수 있는 곳을 업데이트 해줍니다.
            if (graph->weight[currentVertex][j] != INF)
            {
                // 더 작은 가중치가 나온다면 그 가중치로 distance의값을 업데이트 시켜줍니다.
                if (!selected[j] && graph->weight[currentVertex][j] < distance[j])
                {
                    distance[j] = graph->weight[currentVertex][j];
                }
            }
        }
    }
}

int main()
{
    // 그래프 를 작성합니다.
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
    printf("Prim MST Algorithm\n");
    MSTPrim(&graph, 0);
    return 0;
}
