#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct
{
    int arr[MAX_SIZE];
    int size;
} HeapType;

// heap의 현재 상태를 출력합니다.
void printHeapArray(HeapType *heap)
{
    for (int i = 0; i <= heap->size; i++)
    {
        printf("%d ", heap->arr[i]);
    }
    printf("\n");
}
// swap함수입니다.
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 노드 추가 함수입니다
void push(HeapType *heap, int val)
{
    int moves = 0;
    if (heap->size >= MAX_SIZE)
    {
        printf("heap이 가득 찼습니다.\n");
        return;
    }

    heap->arr[heap->size] = val;
    int curr = heap->size;
    printHeapArray(heap);
    // insert할시 우선순위 heap의 경우 큰값을 가진 노드가 위에 위치함으로 부모노드를 찾아 그 값과 비교하며 올라가서 insert할 위치를 찾습니다.
    while (curr > 0 && heap->arr[curr] > heap->arr[(curr - 1) / 2])
    {
        swap(&heap->arr[curr], &heap->arr[(curr - 1) / 2]);
        printHeapArray(heap);
        moves++;
        curr = (curr - 1) / 2; // 부모노드를 찾아줍니다.
    }
    heap->size++;
    printf("노드가 이동한 횟수: %d\n", moves);
}

// 삭제 메뉴 함수
int pop(HeapType *heap)
{
    // 노드가 이동한 횟수 출력을 위해 사용
    int moves = 0;

    // 마지막 노드를 루트 노드로 이동합니다. + 루트 노드를 삭제합니다.
    heap->arr[0] = heap->arr[--heap->size];
    // 루트 노드를 삭제했기 때문에 사이즈도 같이 줄여줍니다.
    heap->size--;
    // 루트의 위치를 현재 위치로 초기화합니다.
    int curr = 0;
    // 루트에서부터 단말 노드까지의 경로에 있는 노드들을 교환하여 히프 성질을 만족시킵니다.
    while (1)
    {
        // 노드의 L R 을 가져옵니다.
        // 2 * 0 + 1 => 1
        int left = 2 * curr + 1;
        // 2 * 0 + 2 => 2
        int right = 2 * curr + 2;
        // left가 heap.size 보다 커지면 종료합니다. -> 움직일 노드 없음
        if (left >= heap->size)
        {
            break;
        }
        // 스왑할 노드의 인덱스를 찾습니다.
        int j = left;

        // 오른쪽 자식이 히프 크기 안에 있고, 오른쪽 값이 왼쪽 값보다 크다면 오른쪽 자식을 스왑 대상으로 변경합니다.
        if (right < heap->size && heap->arr[right] > heap->arr[left])
        {
            j = right;
        }

        // 현재 노드의 값이 자식 노드값 보다 크다면 교환하지 않아도 됩니다.
        if (heap->arr[curr] > heap->arr[j])
        {
            break;
        }
        // 히프의 현재 상태를 출력합니다.
        printHeapArray(heap);
        // 값을 스왑시켜 줍니다.
        swap(&heap->arr[curr], &heap->arr[j]);

        // 노드의 이동횟수를 증가시킵니다.
        moves++;
        // 현재의 위치를 j으로 업데이트 시켜줍니다.
        curr = j;
    }
    // 노드의 이동 횟수 출력.
    printf("노드가 이동된 횟수: %d\n", moves);
}

// 트리 레벨별 출력
void printHeap(HeapType *heap)
{
    int level = 0;
    int nextLevel = 1;
    printf("[%d] ", level + 1);
    for (int i = 0; i < heap->size; i++)
    {
        printf("%d ", heap->arr[i]);
        if (i == nextLevel - 1)
        {
            level++;
            printf("\n[%d] ", level + 1);
            nextLevel += (1 << level);
        }
    }
    printf("\n");
}

int main()
{
    HeapType heap;
    heap.size = 0;

    push(&heap, 90);
    push(&heap, 89);
    push(&heap, 70);
    push(&heap, 36);
    push(&heap, 75);
    push(&heap, 63);
    push(&heap, 65);
    push(&heap, 21);
    push(&heap, 18);
    push(&heap, 15);
    printf("---------------------------------\n");
    printf("| i\t: 노드 추가\t\t|\n");
    printf("| d\t: 노드 삭제\t\t|\n");
    printf("| p\t: 레벨별 출력\t\t|\n");
    printf("| c\t: 종료\t\t\t|\n");
    printf("---------------------------------\n\n\n");

    while (1)
    {
        char cmd;
        int value;
        printf("메뉴 입력: ");
        scanf(" %c", &cmd);
        switch (cmd)
        {
        case 'i':
            printf("추가할 값 입력: ");
            scanf("%d", &value);
            push(&heap, value);
            printf("\n");
            break;
        case 'd':
            pop(&heap);
            printf("\n");
            break;
        case 'p':
            printHeap(&heap);
            printf("\n");
            break;
        default:
            printf("잘못된 메뉴입니다. 메뉴를 다시 입력해주세요.\n");
        }
    }

    return 0;
}
