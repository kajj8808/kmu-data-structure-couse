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
    int i = ++(heap->heapSize);
    while (i != 1 && item.key > heap->heap[i / 2].key)
    {
        heap->heap[i] = heap->heap[i / 2];
        i /= 2;
    }
    heap->heap[i] = item;
}

element deleteMaxHeap(HeapType *heap)
{
    element deletedNode = heap->heap[1];
    heap->heap[1] = heap->heap[heap->heapSize];
    heap->heapSize--;

    int parent = 1;
    int child = 2;
    element temp = heap->heap[1];

    while (child <= heap->heapSize)
    {
        if (child < heap->heapSize && heap->heap[child].key < heap->heap[child + 1].key)
        {
            child++;
        }

        if (temp.key >= heap->heap[child].key)
        {
            break;
        }

        heap->heap[parent] = heap->heap[child];
        parent = child;
        child *= 2;
    }
    heap->heap[parent] = temp;

    return deletedNode;
}

int *heapSort(HeapType *heap)
{
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
    HeapType *heap = create();
    init(heap);
    // 88  86  85  79  59  76  78  56  16  32  34  34  29  55  41  12
    element items[] = {34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 34, 85, 29, 78, 41, 56, 86};
    for (int i = 0; i < 17; i++)
    {
        insertMaxHeap(heap, items[i]);
        printHeap(heap);
    }

    int *sortedHeap = heapSort(heap);

    for (int i = 0; i < 17; i++)
    {
        printf("%d ", sortedHeap[i]);
    }
    printf("\n");

    free(sortedHeap);
    free(heap);
    return 0;
}
