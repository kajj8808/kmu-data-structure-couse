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
    int isPrint = 0;
    i = left;
    j = mid + 1;
    k = left;
    // 분할 정렬된 list의 합병
    while (i <= mid && j <= right)
    {
        moveCount++;
        if (list[i] <= list[j])
        {
            sorted[k++] = list[i++];
        }
        else
        {
            compareCount++;
            isPrint = 1; // 변화가 있을때만 출력하기 위해 사용합니다.
            sorted[k++] = list[j++];
        }
    }
    if (i > mid) // 남아 있는 레코드의 일괄 복사
        for (l = j; l <= right; l++)
            sorted[k++] = list[l];

    else // 남아 있는 레코드의 일괄 복사
        for (l = i; l <= mid; l++)
            sorted[k++] = list[l];
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
