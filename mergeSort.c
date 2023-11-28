#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int moveCount = 0;
int compareCount = 0;
int isLastStep = 0;

int sorted[20]; // 추가 공간이 필요
// i는 정렬된 왼쪽리스트에 대한 인덱스
// j는 정렬된 오른쪽리스트에 대한 인덱스
// k는 정렬될 리스트에 대한 인덱스
void printNums(int nums[20])
{
    for (int i = 0; i < 20; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

void merge(int list[], int left, int mid, int right)
{
    int i, j, k, l;

    i = left;
    j = mid + 1;
    k = left;
    // 분할 정렬된 list의 합병
    while (i <= mid && j <= right)
    {
        moveCount++;    // 움직인 횟수를 카운트 해줍니다.
        compareCount++; // 두 집합이 값을 비교할때의 횟수를 카운트 해줍니다.
        if (list[i] <= list[j])
        {
            sorted[k++] = list[i++];
        }
        else
        {
            sorted[k++] = list[j++];
        }
    }
    if (i > mid) // 남아 있는 레코드의 일괄 복사
        for (l = j; l <= right; l++)
        {
            sorted[k++] = list[l];
            moveCount++; // 남아 있는 값을 복사할때도 카운트해줍니다.
        }

    else // 남아 있는 레코드의 일괄 복사
        for (l = i; l <= mid; l++)
        {
            sorted[k++] = list[l];
            moveCount++; // 남아 있는 값을 복사할때도 카운트해줍니다.
        }

    // 배열 sorted[]의 리스트를 배열 list[]로 복사
    for (l = left; l <= right; l++)
        list[l] = sorted[l];
    if (isLastStep)
    {
        printNums(list);
    }
}

void merge_sort(int list[], int left, int right)
{
    int mid;
    if (left < right) // left 가 작을 경우만
    {
        mid = (left + right) / 2;         // 리스트의 균등분할 (중간 계산)
        merge_sort(list, left, mid);      // 부분리스트 정렬
        merge_sort(list, mid + 1, right); // 부분리스트 정렬
        merge(list, left, mid, right);    // 합병
    }
}

int main()
{
    for (int i = 0; i < 20; i++)
    {
        // random 값을 초기화 합니다.
        srand(time(NULL));
        // random 값을 생성합니다.
        int ranNums[20];
        for (int i = 0; i < 20; i++)
        {
            int ranNum = rand() % 100; // 랜덤 값을 생성합니다. 99
            ranNums[i] = ranNum;
        }

        if (i == 19)
        {
            // 랜덤으로 생성된 리스트를 출력합니다.
            printf("\nOriginal List\n");
            printNums(ranNums);
            isLastStep = 1;
            printf("\n");
            printf("Merge Sort\n");
        }
        merge_sort(ranNums, 0, 19);
    }
    // 정렬이 완료된 리스트를 출력합니다.

    printf("\nAverage Move Count: %d\n", moveCount / 20);
    printf("Average Compare Count: %d\n", compareCount / 20);
}
