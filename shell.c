#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 평균 움직인 횟수, 비교 횟수를 카운트 하기위해 사용합니다.
int moveCount = 0;
int compareCount = 0;

// 20개의 숫자를 출력합니다.
void printNums(int nums[20])
{
    for (int i = 0; i < 20; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

void insertionSort(int list[], int first, int last, int gap)
{
    // insertionSort 를 진행합니다.
    int i, j, key;
    // insertionSort 의 특성상 값 두개를 체크하고 변경합니다.
    for (i = first + gap; i <= last; i = i + gap)
    {
        key = list[i];
        for (j = i - gap; j >= first && key < list[j]; j = j - gap)
        {
            list[j + gap] = list[j];
            compareCount++;
        }
        list[j + gap] = key;
        moveCount++;
    }
}

void shellSort(int list[20], int n)
{
    int i, gap;
    // n의 경우 10으로 설정하였습니다 -> 초기 gap 10 / 2.
    // gap을 변경시키며 값을 찾습니다. 10 -> 5 -> 2 -> 1
    for (gap = n / 2; gap > 0; gap = gap / 2)
    {
        if ((gap % 2) == 0)
            gap++;
        for (i = 0; i < gap; i++) // 부분 리스트의 개수는 gap
        {
            insertionSort(list, i, n - 1, gap);
        }
        // gap이 변경된 후 insertionSort를 진행한 후의 값을 출력합니다.
        printNums(list);
    }
}

int main()
{

    for (int i = 0; i < 20; i++)
    {
        //  random 값을 초기화 합니다.
        srand(time(NULL));
        // random 값을 생성합니다.
        int ranNums[20];
        for (int i = 0; i < 20; i++)
        {
            int ranNum = rand() % 100; // 랜덤 값을 생성합니다. 99
            ranNums[i] = ranNum;
        }
        // 랜덤으로 생성된 리스트를 출력합니다.
        printf("\nOriginal List\n");
        printNums(ranNums);
        printf("\n");
        // 정렬이 완료된 리스트를 출력합니다.
        printf("Shell Sort\n");
        shellSort(ranNums, 10);
        printNums(ranNums);
    }
    // 20번 돌린 결과의 평균을 출력합니다.
    printf("\nAverage Move Count: %d\n", moveCount / 20);
    printf("Average CompareCount Count: %d\n", compareCount / 20);
}
