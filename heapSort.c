#include <stdio.h>
#include <stdlib.h>

typedef struct element
{
    int key;
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

void printHeap(HeapType *heap)
{
    // root 노드 생략
    for (int i = 1; i <= heap->heapSize; i++)
    {
        printf("%d ", heap->heap[i].key);
    }
    printf("\n");
}

void init(HeapType *heap)
{
    heap->heapSize = 0;
}

void insertMaxHeap(HeapType *heap, element item)
{
    // 힙의 사이즈를 늘려줍니다. 루트 노드를 넘깁니다.
    int i = ++(heap->heapSize);
    // i != 1 => 힙의 사이즈가 0 일때 즉 루트만 있을때 가 아닌경우 와
    // 노드 의 key값이 부모 노드의 key값 보다 클때 위의 heap 과 교환하면서 올라갑니다.
    while (i != 1 && item.key > heap->heap[i / 2].key)
    {
        heap->heap[i] = heap->heap[i / 2];
        i /= 2;
    }
    // 적절한 위치를 찾았으므로 값을 넣어줍니다.
    heap->heap[i] = item;
}

element deleteMaxHeap(HeapType *heap)
{
    // 루트 바로밑에 있는 노드를 삭제할 노드로 보고 삭제하는 노드로 지정합니다.
    element deletedNode = heap->heap[1];
    // 가장 밑에 있는 노드 를 위로 올립니다.
    heap->heap[1] = heap->heap[heap->heapSize];
    // 노드를 하나 삭제했기때문에 힙의 사이즈를 줄여줍니다.
    heap->heapSize--;

    int parent = 1;
    int child = 2;
    element temp = heap->heap[1];
    // child 가 힙의 안에 있을때만 돕니다.
    while (child <= heap->heapSize)
    {
        // 오른쪽 자식이 있고 (child < heap->heapSize)
        // 왼쪽 값보다 크다면 오른쪽 노드로 변경합니다.
        if (child < heap->heapSize && heap->heap[child].key < heap->heap[child + 1].key)
        {
            child++;
        }
        // 현재 노드가 자식노드 보다 크거나 작으면 조정을 그만 둡니다.
        if (temp.key >= heap->heap[child].key)
        {
            break;
        }
        // 자식 노드보다 현재의 노드가 작다면 자식 노드의 값을 부모 노드에 넣습니다.
        heap->heap[parent] = heap->heap[child];
        // 아래로 이동합니다.
        parent = child;
        child *= 2;
    }
    // 삭제되었거나 아래로 이동했던 노드의 올바른 위치에 temp를 삽입합니다.
    heap->heap[parent] = temp;

    return deletedNode;
}

int *heapSort(HeapType *heap)
{
    // heap 노드는 값을 넣고 삭제하면 sort가 됨으로 값을 삭제하면서 값을 넣어갑니다.
    int n = heap->heapSize;
    int *sorted = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++)
    {
        element item = deleteMaxHeap(heap);
        printHeap(heap);
        sorted[n - 1 - i] = item.key;
    }

    return sorted;
}

int main()
{
    // 힙을 생성합니다.
    HeapType *heap = create();
    // 힙을 초기화합니다.
    init(heap);
    // 넣을 item들을 작성합니다.
    element items[] = {34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 34, 85, 29, 78, 41, 56, 86};
    // max 힙 에 item들을 넣어줍니다. 이때 넣은 현재 상황들을 출력합니다.
    for (int i = 0; i < 17; i++)
    {
        insertMaxHeap(heap, items[i]);
        printHeap(heap);
    }
    // 힙을 정렬합니다.
    int *sortedHeap = heapSort(heap);
    // 정렬된 힙값들을 출력합니다.
    for (int i = 0; i < 17; i++)
    {
        printf("%d ", sortedHeap[i]);
    }
    printf("\n");
    // 썻던 메모리를 놓아줍니다.
    free(sortedHeap);
    free(heap);
    return 0;
}
