#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double moveCount = 0;
double compareCount = 0;

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
int partition(int list[], int left, int right)
{
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left];
	// 피봇을 중심으로 값을 교환 합니다.
	do
	{
		do
		{
			low++;
			compareCount++; // 비교 회수 증감
		} while (low <= right && list[low] < pivot);
		do
		{
			high--;
			compareCount++; // 비교 회수 증감
		} while (high >= left && list[high] > pivot);
		if (low < high)
		{
			swap(&list[low], &list[high]);
			moveCount++; // 이동 회수 증감
		}

	} while (low < high);

	swap(&list[left], &list[high]);
	printNums(list);

	moveCount++; // 이동 회수 증감
	return high;
}

void quick_sort(int list[], int left, int right)
{
	if (left < right)
	{
		int q = partition(list, left, right);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
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
		printf("Quick Sort\n");
		quick_sort(ranNums, 0, 19);
	}
	// 값이 이동한 평균 횟수를 출력합니다.
	printf("\nAverage Move Count: %f\n", moveCount / 20);
	// 값을 비교한 평균횟수를 출력합니다.
	printf("Average Comp Count: %f\n", compareCount / 20);
}
