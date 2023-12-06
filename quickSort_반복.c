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
	// 간단한 스택구조로 반복방식을 구현합니다.
	int stack[20]; // stack 의 사이즈를 정합니다.
	int top = -1;  // top 을 설정합니다.

	// left right를 stack에 넣어둡니다.
	stack[++top] = left;
	stack[++top] = right;
	// 값이 없을떄 즉 stack 에 넣을 값이 없었던 경우 모든 값을 돈것이기 떄문에 반복을 종료합니다.
	while (top >= 0)
	{
		// stack 에서 위에서 부터 꺼냅니다.
		right = stack[top--];
		left = stack[top--];

		int q = partition(list, left, right);

		// 피벗이 왼쪽에 있는경우 left 는 가만히 두고 right 피벗 - 1 위치로 옮깁니다.
		if (q - 1 > left)
		{
			stack[++top] = left;
			stack[++top] = q - 1;
		}

		// 피벗이 오른쪽에 있는경우 right 는 가만히 두고 left를 피벗 + 1 위치로 옮깁니다.
		if (q + 1 < right)
		{
			stack[++top] = q + 1;
			stack[++top] = right;
		}
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
