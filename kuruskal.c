#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int node[2]; // 이어줄 노드 2개
    int weight;  // 간선의 가중치
} Edge;
// 간선을 만듭니다.
Edge *createEdge(int a, int b, int weight)
{
    Edge *newEdge = (Edge *)malloc(sizeof(Edge));
    newEdge->node[0] = a;
    newEdge->node[1] = b;
    newEdge->weight = weight;
    return newEdge;
}
// target이 속한 집합의 가장 위의 값을 반환합니다.
int getParent(int parent[], int target)
{
    // 재귀함수 종료 부분
    if (parent[target] == target)
    {
        return target;
    }
    // parent 즉 집합의 대표(가장 위의 값)을 찾습니다. 재귀로 합니다.
    return parent[target] = getParent(parent, parent[target]);
}

// 정렬을하는데 qsort를 사용하는데 사용합니다. A 의 가중치가 b 보다 작으면 -1  아니면 1 같다면 0을리턴합니다.
int compare(const void *a, const void *b)
{
    Edge *edgeA = *(Edge **)a;
    Edge *edgeB = *(Edge **)b;
    if (edgeA->weight < edgeB->weight)
    {
        return -1;
    }
    else if (edgeA->weight > edgeB->weight)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
// 두 부모 노드를 합치는 함수입니다.
void unionParent(int parent[], int a, int b)
{
    a = getParent(parent, a);
    b = getParent(parent, b);
    if (a < b)
        parent[b] = a; // 더 작은쪽으로 부모를 합쳐주는 과정
    else
        parent[a] = b; // 이렇게 함으로써 가장 작은 부모를 찾을수가 있습니다.
}
// 같은 부모를 가지는지 확인 하는 함수 동일한 그래프에 속해있는지 확인.
int findParent(int parent[], int a, int b)
{
    a = getParent(parent, a);
    b = getParent(parent, b);
    if (a == b)
        return 1; // 같다면 같은 부모를 가지는구나 확인.
    else
        return 0; // 아니라면 0을 return
}
//////////(minHeap 정렬 이전코드 사용)/////////////////////////////////////////
typedef struct element
{
    int key;
    Edge *edge;
} element;

typedef struct HeapType
{
    element heap[100];
    int heapSize;
} HeapType;

HeapType *create()
{
    return (HeapType *)malloc(sizeof(HeapType));
}

void init(HeapType *heap)
{
    heap->heapSize = 0;
}

void insertMinHeap(HeapType *heap, element item)
{
    int i = ++(heap->heapSize);
    while (i != 1 && item.key < heap->heap[i / 2].key)
    {
        heap->heap[i] = heap->heap[i / 2];
        i /= 2;
    }
    heap->heap[i] = item;
}

element deleteMinHeap(HeapType *heap)
{
    element minItem = heap->heap[1];
    element temp = heap->heap[(heap->heapSize)--];
    int parent = 1;
    int child = 2;
    while (child <= heap->heapSize)
    {
        if (child < heap->heapSize && heap->heap[child].key > heap->heap[child + 1].key)
            child++;
        if (temp.key <= heap->heap[child].key)
            break;
        heap->heap[parent] = heap->heap[child];
        parent = child;
        child *= 2;
    }
    heap->heap[parent] = temp;
    return minItem;
}
/////////////////////////////////////////////////////////////
int main()
{
    int vertexs = 10;  // 정점의 개수
    int edgesNum = 20; // 간선의 개수

    // edge의 개수만큼 메모리를 초기화 해줍니다.
    Edge **edges = (Edge **)malloc(edgesNum * sizeof(Edge));
    edges[0] = createEdge(1, 2, 3);
    edges[1] = createEdge(1, 6, 11);
    edges[2] = createEdge(1, 7, 12);
    edges[3] = createEdge(6, 5, 9);
    edges[4] = createEdge(6, 2, 7);
    edges[5] = createEdge(7, 2, 8);
    edges[6] = createEdge(2, 5, 1);
    edges[7] = createEdge(7, 3, 6);
    edges[8] = createEdge(3, 2, 5);
    edges[9] = createEdge(2, 4, 4);
    edges[10] = createEdge(3, 4, 2);
    edges[11] = createEdge(7, 8, 13);
    edges[12] = createEdge(3, 8, 5);
    edges[13] = createEdge(8, 4, 14);
    edges[14] = createEdge(8, 10, 15);
    edges[15] = createEdge(4, 10, 16);
    edges[16] = createEdge(5, 4, 13);
    edges[17] = createEdge(5, 10, 17);
    edges[18] = createEdge(5, 9, 18);
    edges[19] = createEdge(9, 10, 10);
    // qsort(edges, edgesNum, sizeof(Edge *), compare);
    // 정렬 확인 for문입니다.
    /* for (int i = 0; i < edgesNum; i++)
    {
        printf("(%d , %d) -> %d \n", edges[i]->node[0], edges[i]->node[1], edges[i]->weight);
    } */
    // init 을 합니다.
    // heap min 정렬을 진행합니다.
    HeapType *heap = create();
    init(heap);

    for (int i = 0; i < edgesNum; i++)
    {
        element temp;
        temp.key = edges[i]->weight;
        temp.edge = edges[i];
        insertMinHeap(heap, temp);
    }

    int parent[vertexs]; // 정점의 갯수.
    for (int i = 0; i <= vertexs; i++)
    {
        parent[i] = i; // 기본적으로 모든 vertex 는 자기 자신을 가르키게 합니다.
    }

    printf("Kruskal MST Algorithm (Min Heap 사용)\n");
    while (heap->heapSize > 0)
    {
        element minElement = deleteMinHeap(heap);
        Edge *minEdge = minElement.edge;
        // 사이클이 발생하지 않는경우 그래프에 포함
        // 간선에서 서로 연결이 되지 않은경우.
        if (!findParent(parent, minEdge->node[0], minEdge->node[1]))
        {
            // 연결되지 않았을때 연결해줍니다
            unionParent(parent, minEdge->node[0], minEdge->node[1]);
            printf("Edge (%d, %d) ", minEdge->node[0], minEdge->node[1]);
            printf("Select %d\n", minEdge->weight);
        }
        // 않은경우는 무시해줍니다.
    }
}
