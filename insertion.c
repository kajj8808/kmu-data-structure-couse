#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int moveCount = 0;
int compareCount = 0;

void printNums(int nums[20])
{
    for (int i = 0; i < 20; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

// 삽입정렬
void insertionSort(int list[], int n)
{
    int i, j, key;
    for (i = 1; i < n; i++)
    {
        key = list[i];
        for (j = i - 1; j >= 0 && list[j] > key; j--)
        {
            list[j + 1] = list[j]; // 레코드의 오른쪽 이동
            moveCount++;
            compareCount++;
        }

        list[j + 1] = key;
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
        printf("Insertion Sort\n");
        insertionSort(ranNums, 20);
    }

    printf("\nMove Count: %d\n", moveCount / 20);
    printf("CompareCount Count: %d\n", compareCount / 20);
}