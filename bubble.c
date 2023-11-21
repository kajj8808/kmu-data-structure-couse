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

void bubbleSort(int list[], int n)
{

    int i, j, temp;
    for (i = n - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        { // 앞뒤의 레코드를 비교한 후 교체
            if (list[j] > list[j + 1])
            {
                swap(&list[j], &list[j + 1]);
                moveCount++;
            }
            compareCount++;
        }
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

        printf("Original List\n");
        printNums(ranNums);
        printf("\n");
        printf("Bubble Sort\n");
        bubbleSort(ranNums, 20);
    }

    printf("\nMove Count: %d\n", moveCount / 20);
    printf("CompareCount Count: %d\n", compareCount / 20);
}