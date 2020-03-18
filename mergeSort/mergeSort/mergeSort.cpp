#include<stdio.h>
#define MAX_SIZE 20
void merge(int initList[], int mergedList[], int i, int m, int n) {
	int j, k, t;
	j = m + 1;
	k = i;
	while (i <= m && j <= n) {
		if (initList[i] <= initList[j])
			mergedList[k++] = initList[i++];
		else
			mergedList[k++] = initList[j++];
	}
	if (i > m) {
		for (t = j; t <= n; t++)
			mergedList[t] = initList[t];
	}
	else {
		for (t = i; t <= m; t++)
			mergedList[k + t - i] = initList[t];
	}
}

void mergePass(int initList[], int mergedList[], int n, int s) {
	int i, j;
	for (i = 1; i <= n - 2 * s + 1; i += 2 * s)
		merge(initList, mergedList, i, i + s - 1, i + 2 * s - 1);
	if (i + s - 1 < n)
		merge(initList, mergedList, i, i + s - 1, n);
	else
		for (j = i; j <= n; j++)
			mergedList[j] = initList[j];
}

void mergeSort(int a[], int n) {
	int s = 1;
	int extra[MAX_SIZE];
	while (s < n) {
		mergePass(a, extra, n, s);
		s *= 2;
		mergePass(extra, a, n, s);
		s *= 2;
	}
}
int main()
{
	int data[MAX_SIZE + 1];
	int i;
	FILE * fin;
	fopen_s(&fin, "input.txt", "r+");
	if (fin == NULL) {
		printf("Flie open error!");
		return 0;
	}
	int n = 0;
	while (fscanf_s(fin, "%d", &data[n + 1]) != EOF) {
		n++;
	}
	fclose(fin);
	mergeSort(data, n);
	for (i = 1; i <= n; i++) {
		printf(" %d", data[i]);
	}
}

