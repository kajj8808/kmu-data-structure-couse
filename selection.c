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
        for (j = i + 1; j < n; j++) // 가장 작은 값을 찾습니다.
            if (list[j] < list[least]) 
            {
                least = j;
                compareCount++;
            }
        swap(&list[i], &list[least]); // 가장 작은 값과 위치를 swap합니다. 
        moveCount++;
    }
    printNums(list);
}

int main()
{
    // 20번 반복합니다.
    for (int i = 0; i < 20; i++)
    {
        // random값 20개를 생성합니다.
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
        // sort를 할때 움직인 횟수를 출력합니다.
        printf("\nMove Count: %d\n", moveCount / 20); 
        // 20번 반복한 평균 이동 횟수를 출력합니다.
        printf("CompareCount Count: %d\n", compareCount / 20);
    }
}
