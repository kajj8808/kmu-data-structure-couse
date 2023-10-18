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
        if (heap->arr[i] == NULL)
            continue;
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
    // 노드가 이동한 횟수를 저장하기 위한 변수
    int moves = 0;

    // 힙의 마지막에 값을 추가
    heap->arr[heap->size] = val;
    // 현재 노드의 위치를 마지막 위치로 설정
    int curr = heap->size;
    // 힙의 현재 상태 출력
    printHeapArray(heap);
    // insert할시 우선순위 heap의 경우 큰값을 가진 노드가 위에 위치함으로 부모노드를 찾아 그 값과 비교하며 올라가서 insert할 위치찾음
    while (curr > 0 && heap->arr[curr] > heap->arr[(curr - 1) / 2])
    {
        // 현재 노드와 부모 노드의 값을 교환
        swap(&heap->arr[curr], &heap->arr[(curr - 1) / 2]);
        // 현재 힙출력
        printHeapArray(heap);
        moves++;
        // 현재 위치를 부모 노드의 위치로 업데이트
        curr = (curr - 1) / 2;
    }
    heap->size++;
    printf("노드가 이동한 횟수: %d\n", moves);
}

// 삭제 메뉴 함수
int pop(HeapType *heap)
{
    int parent, child;
    int item, temp;
    int moves = 0;

    item = heap->arr[0];              // 루트의 값을 저장
    temp = heap->arr[heap->size - 1]; // 마지막 값을 임시로 저장
    heap->arr[heap->size - 1] = NULL; // 마지막 값을 초기화 (또는 0으로 설정)
    heap->size--;                     // 힙의 크기를 감소

    parent = 0;
    child = 1; // 0-based index에서의 첫 번째 자식의 위치

    while (child < heap->size)
    {
        moves++;
        // 두 자식 중에서 큰 자식을 선택
        if (child + 1 < heap->size && heap->arr[child] < heap->arr[child + 1])
        {
            child++;
        }

        if (temp >= heap->arr[child])
        {
            break; // 올바른 위치를 찾았을 경우
        }

        // 한 단계 아래로 이동
        heap->arr[parent] = heap->arr[child];
        parent = child;
        child = 2 * parent + 1; // 0-based index에서의 다음 자식의 위치

        // 중간 과정 출력
        printHeapArray(heap);
    }

    heap->arr[parent] = temp;
    printHeapArray(heap); // 마지막 상태 출력

    printf("노드가 이동된 횟수: %d\n", moves);
    return item;
}

// 트리 레벨별 출력
void printHeap(HeapType *heap)
{
    // 현재에 레벨을 저장 하기위한 변수, 초기 레벨 0
    int level = 0;
    // 다음 레벨로 넘아갈때 사용하는 변수 초기값은 0
    int nextLevel = 1;
    // 첫 번째 라벨을 출력해줍니다.
    printf("[%d] ", level + 1);
    // 힙을 모두돕니다.
    for (int i = 0; i < heap->size; i++)
    {
        // 현재 원소 출력
        printf("%d ", heap->arr[i]);
        // 현재 인덱스가 다음레벨의 인덱스와 같다면 레벨을 증가시켜줍니다.
        if (i == nextLevel - 1)
        {
            level++;
            // 줄바꿈을 하고 레벨을 출력
            printf("\n[%d] ", level + 1);
            // 다음레벨으로 넘어갑니다. 인덱스를 증가
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
