
#include <stdio.h>
#define MAX_SIZE 10
#define MAX_WEIGHT 128

//Floyd算法
void floyd() {
	FILE *fin;
	int graph[MAX_SIZE][MAX_SIZE] = { 0 };//邻接矩阵
	int vn, en;//点数、边数
	int startV, endV, w;//起始点、终点、权值
	int i, j, k;
	fin = fopen("input.txt", "r");
	fscanf(fin, "%d %d", &vn, &en);
	//初始化图
	for (i = 0; i < vn; i++) {
		for (j = 0; j < vn; j++) {
			if (i != j) {
				graph[i][j] = MAX_WEIGHT;
			}
			else {
				graph[i][j] = 0;
			}
		}
	}
	//读图
	for (i = 0; i < en; i++) {
		fscanf(fin, "%d %d %d", &startV, &endV, &w);
		graph[startV - 1][endV - 1] = w;
	}
	//Floyd算法
	for (k = 0; k < vn; k++) {
		//k为过度点
		for (i = 0; i < vn; i++) {
			for (j = 0; j < vn; j++) {
				//当通过过渡点的路径小于当前最短路径时，更新最短路径
				if (graph[i][k] + graph[k][j] < graph[i][j]) {
					graph[i][j] = graph[i][k] + graph[k][j];
				}
			}
		}
		//第k次更新结束

		printf("并入点%d后\n", k + 1);

		for (i = 0; i < vn; i++) {
			for (j = 0; j < vn; j++) {
				printf("%5d", graph[i][j]);
			}
			printf("\n");
		}

	}
	printf("注：%d表示不可达\n",MAX_WEIGHT);
}

//Dijkstra算法
void dijkstra() {
	FILE *fin;
	int graph[MAX_SIZE][MAX_SIZE] = { 0 };//邻接矩阵
	int vn, en;//点数、边数
	int startV, endV, w;//起始点、终点、权值
	int i, j, k;
	int d[10];//保存最短路径长度
	int final[10];//若final[i] = 1则说明 顶点vi已在集合S中
	int origin;//起始点
	fin = fopen("input2.txt", "r");
	fscanf(fin, "%d %d", &vn, &en);
	//初始化图
	for (i = 0; i < vn; i++) {
		for (j = 0; j < vn; j++) {
			if (i != j) {
				graph[i][j] = MAX_WEIGHT;
			}
			else {
				graph[i][j] = 0;
			}
		}
	}
	//读图
	for (i = 0; i < en; i++) {
		fscanf(fin, "%d %d %d", &startV, &endV, &w);
		graph[startV - 1][endV - 1] = w;
	}
	printf("请输入起始点:");
	scanf("%d",&origin);
	origin = origin - 1;
	//Dijkstra算法
	//初始化建立可达关系表
	for (i = 0; i < vn; i++) {
		final[i] = 0;
		d[i] = graph[origin][i];
	}
	//初始化 起始点属于集合S
	d[origin] = 0;
	final[origin] = 1;
	//开始主循环 每次求得起始点到某个顶点v的最短路径 并加v到集合S中
	for (i = 1; i < vn; i++) {
		int min = MAX_WEIGHT;
		//选择当前出离起始点最近且不在集合S中的顶点v
		for (j = 0; j < vn; j++) {
			if (!final[j]) {
				if (d[j]<min) {
					k = j;
					min = d[j];
				}
			}
		}
		final[k] = 1;//选出该点后加入到合集S中
		//更新当前最短路径和距离
		for (j = 0; j < vn; j++) {
			if (!final[j] && (min + graph[k][j] < d[j])&&graph[k][j]!=0) {
				d[j] = min + graph[k][j];
			}
		}
	}
	for (i = 0; i < vn; i++) {
		printf("从点%d 到点%d 的最短路径为 %d\n", origin+1,i+1, d[i]);
	}
	printf("注：%d表示不可达\n", MAX_WEIGHT);
}
int main()
{
	//Floyd算法
	//floyd();
	//Dijkstra算法
	dijkstra();
}

