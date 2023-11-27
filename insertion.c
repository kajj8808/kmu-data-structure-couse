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
        // 올바른 위치를 찾습니다.
        for (j = i - 1; j >= 0 && list[j] > key; j--)
        {
            list[j + 1] = list[j]; // 올바른 위치를 한칸씩 옮기며 찾습니다.
            moveCount++;
            compareCount++;
        }
        // 올바른 위치에 값을 넣어줍니다. 
        list[j + 1] = key;
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
        printf("Insertion Sort\n");
        insertionSort(ranNums, 20);
    }
    // sort를 할때 움직인 횟수를 출력합니다.
    printf("\nMove Count: %d\n", moveCount / 20);
    // 20번 반복한 평균 이동 횟수를 출력합니다.
    printf("CompareCount Count: %d\n", compareCount / 20);
}
