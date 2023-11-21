#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int moveCount = 0;
int compareCount = 0;

/* 두개의 요소의 위치를 swap 합니다. */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printNums(int nums[20])
{
    for (int i = 0; i < 20; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

// 삽입정렬
void selectionSort(int list[], int n)
{

    int i, j, least, temp;
    for (i = 0; i < n - 1; i++)
    {
        least = i;
        for (j = i + 1; j < n; j++) // 최솟값 탐색
            if (list[j] < list[least])
            {
                least = j;
                compareCount++;
            }
        swap(&list[i], &list[least]);
        moveCount++;
    }
    printNums(list);
}

int main()
{
    for (int i = 0; i < 20; i++)
    {
        srand(time(NULL));
        int ranNums[20];
        for (int i = 0; i < 20; i++)
        {
            int ranNum = rand() % 100;
            ranNums[i] = ranNum;
        }

        printf("\nOriginal List\n");
        printNums(ranNums);
        printf("\n");
        printf("Selection Sort\n");
        selectionSort(ranNums, 20);
        printf("\nMove Count: %d\n", moveCount / 20);
        printf("CompareCount Count: %d\n", compareCount / 20);
    }
}
