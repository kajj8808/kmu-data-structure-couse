#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NUM_VECTOR 10 // vector 의 갯수입니다.
// 방문한 위치들을 출력합니다.
void printVisited(int *visited, int numVisited)
{
    printf("Found: ");
    for (int i = 0; i < numVisited; i++)
    {
        printf("%d ", visited[i]);
    }
    printf("\n");
}
// distance 를 출력합니다.
void printDistance(int *dist, int numVertex)
{
    printf("Distance: ");
    for (int i = 0; i < numVertex; i++)
    {
        if (dist[i] == 999)
        {
            printf("* ");
            continue;
        }
        printf("%d ", dist[i]);
    }
    printf("\n");
}

int *dijstra(int graph[NUM_VECTOR][NUM_VECTOR], int start)
{
    int *dist = malloc(sizeof(int) * NUM_VECTOR); // D
    int visited[NUM_VECTOR];                      // 이미 방문한 위치를 저장하는데 사용합니다.
    int visitOrder[NUM_VECTOR];                   // 방문한 순서를 저장하는데 사용합니다.

    // 리턴배열과 이미 방문한위치 에 대한 배열을 초기화합니다.
    for (int i = 0; i < NUM_VECTOR; i++)
    {
        dist[i] = 999;
        visited[i] = 0;
    }

    // 시작 정점의 거리를 0으로 둡니다. // 거리로 하기에
    // 입력받은 시작위치를..
    dist[start] = 0;

    // 모든 정점을 방문할때 까지 반복합니다. // 가중치 갱신
    for (int i = 0; i < NUM_VECTOR; i++)
    {
        // 현재까지의 최소 거리를 가지는 vertex를 찾습니다.
        // 값들을 초기화해줍니다.
        int minDist = 999; // 할당 안된값에대해서 999 로둡니다
        int minIndex;
        for (int vertex = 0; vertex < NUM_VECTOR; vertex++)
        {
            //  방문한 적이 없고 , 초기화 된 값보다 minDist 초기(999) 가 클때. 초기화를 해줍니다.
            if (!visited[vertex] && dist[vertex] <= minDist)
            {
                minDist = dist[vertex];
                minIndex = vertex;
            }
        }
        printDistance(dist, NUM_VECTOR);
        printVisited(visited, NUM_VECTOR);
        printf("\n");

        // 방문한 정점으로 표시합니다.
        visited[minIndex] = 1;
        visitOrder[i] = minIndex;
        // 현재 정점과 연결된 정점들의 거리를 갱신합니다.
        for (int vertex = 0; vertex < NUM_VECTOR; vertex++)
        {
            if (graph[minIndex][vertex]
                // 거리가 999 즉 초기값이 아니고
                && dist[minIndex] != 999
                //  현재 길이와 이전길이를 더한것이 이 점의 최소보다 작다면.
                && dist[minIndex] + graph[minIndex][vertex] < dist[vertex])
            {
                // 현재길이를 최소길이에 더해줘 최소의 길이를 달성합니다.
                dist[vertex] = dist[minIndex] + graph[minIndex][vertex];
            }
        }
    }
    // 방문한 순서를 출력합니다.
    for (int i = 0; i < NUM_VECTOR; i++)
    {
        printf("%d ", visitOrder[i] + 1);
    }
    printf("\n");

    return dist;
};

int main()
{
    // 그래프 초기화
    int graph[NUM_VECTOR][NUM_VECTOR] = {
        {0, 3, 999, 999, 999, 11, 12, 999, 999, 999},
        {999, 0, 5, 4, 1, 7, 8, 999, 999, 999},
        {999, 5, 0, 2, 999, 999, 6, 5, 999, 999},
        {999, 4, 2, 0, 13, 999, 999, 999, 999, 16},
        {999, 1, 999, 13, 0, 9, 999, 999, 18, 17},
        {11, 7, 999, 999, 9, 0, 999, 999, 999, 999},
        {12, 8, 6, 999, 999, 999, 0, 13, 999, 999},
        {999, 999, 5, 14, 999, 999, 13, 0, 999, 15},
        {999, 999, 999, 999, 18, 999, 999, 999, 0, 10},
        {999, 999, 999, 16, 17, 999, 999, 15, 10, 0},
    };

    printf("Dijkstra Algorithm \n");
    // 시작위치를 초기화
    int start = 0;

    dijstra(graph, start);

    return 0;
}
