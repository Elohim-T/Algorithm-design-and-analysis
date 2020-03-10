#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10000 
int SequentialSearch(int array[], int q, int n) {
	int i;
	for (i = 1; i <= n; i++) {
		if (array[i] == q) {
			return i;
		}
	}
	return 0;
}

int binarySearch(int list[], int target, int len) {
	int low = 1;
	int hight = len;
	int middle;
	while (low <= hight) {
		middle = (low + hight) / 2;
		if (list[middle] == target)
		{
			return middle;
		}
		else if (list[middle] > target)
		{
			hight = middle - 1;
		}
		else if (list[middle] < target)
		{
			low = middle + 1;
		}
	}
	return 0;
}
int main()
{
	int n, q, subscript;
	int i;
	int array[MAX_SIZE];

	FILE *fin;
	fin = fopen("input.txt", "r+");
	if (fin == NULL) {
		printf("file open error");
	}
	fscanf(fin, "%d", &n);
	for (i = 1; i <= n; i++) {
		fscanf(fin, "%d", &array[i]);
	}
	
	printf("数组中共有数字%d个,如下：\n", n);
	for (i = 1; i <= n; i++) {
		printf("%6d", array[i]);
		if (i % 20 == 0) {
			printf("\n");
		}
	}

	printf("\n请输入待检索的数：");
	scanf("%d", &q);
	subscript = binarySearch(array, q, n);
	//subscript = SequentialSearch(array, q, n);

	printf("%d\n", subscript);
	if (subscript != 0) {
		printf("%d在数组中的下标为%d\n",q, subscript-1);
	}
	else {
		printf("%d不在数组中\n");
	}
	return 0;
}
