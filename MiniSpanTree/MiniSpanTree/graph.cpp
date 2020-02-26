
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

graphPointer* createGraph(int* vn,int* en) 
{
	
	int i, start, end, weight;
	FILE * fin;
	fopen_s(&fin,"input.txt", "r+");
	if (fin == NULL) {
		printf("Flie open error!");
		return 0;
	}
	fscanf_s(fin,"%d %d",vn,en);
	graphPointer* graph = (graphPointer*)malloc(sizeof(graphPointer*)*(*vn + 1));
	//因为0号不用，所以多申请一个
	for (i = 0; i < *vn +1;i++) {
		graph[i] = NULL;
	}
	//因为是无向图，所以一条边会被输入两次
	for (i = 0; i < *en * 2; i++) {
		fscanf_s(fin, "%d %d %d", &start, &end, &weight);
		insertEdge(&graph[start], end, weight);
	}

	fclose(fin);

	return graph;
}
void insertEdge(graphPointer* graph, int e, int w) {
	//插入一条新边
	graphPointer temp = (graphPointer)malloc(sizeof(node));
	temp->id = e;
	temp->weight = w;
	temp->link = NULL;
	if ((*graph) == NULL) {
		(*graph) = temp;
	} else {
		temp->link = *graph;
		(*graph) = temp;
	}
}
graphPointer* insertVertex(graphPointer* graph, int *vn) {
	//插入一个新节点
	int i;
	graphPointer* newGraph = (graphPointer*)malloc(sizeof(graphPointer)*(*vn+1));
	for (i = 0; i < *vn; i++) {
		newGraph[i] = graph[i];
	}
	newGraph[*vn] = NULL;
	*vn = *vn + 1;
	return newGraph;
}

bool isEmpty(graphPointer* graph) {
	if ((*graph) == NULL) {
		return true;
	}
	else {
		return false;
	}
}
//最小生成树——Prim算法
void prim(graphPointer* graph, int vn) {
	int pointSet[MAX_SIZE+1] = {0};//现有点集
	int i, j;
	int w;//代价
	int targetV;//目标点
	int startV; //起始点
	graphPointer temp;

	printf("Prim:\n");
	//从1号点开始
	pointSet[1] = 1;

	for (i = 1; i < vn; i++) {

		w = 10000;//假设每条边的权重均小于10000；
		//找到从现有点集出发的能够以最小代价达到的点
		for (j = 1; j < vn + 1; j++) {
			if (pointSet[j] == 1) {
				temp = graph[j];
				//找到从j出发的能够以最小代价达到的点
				while (temp != NULL) {
					if (temp->weight < w && pointSet[temp->id]!=1) {
						w = temp->weight;
						targetV = temp->id;
						startV = j;
					}
					temp = temp->link;
				}
			}
		}
		pointSet[targetV] = 1;
		printf("%d --- %d\n",startV,targetV);
	}
}
//最小生成树——Kruskal算法
void kruskal(graphPointer* graph, int vn) {

	int i, j, k;
	int w;//代价
	int targetV;//目标点
	int startV; //起始点
	graphPointer temp,ptr1,ptr2,ptr;
	int flag1, flag2;
	
	//初始化树群
	graphPointer* tree = (graphPointer*)malloc(sizeof(graphPointer*)*(vn + 1));
	//因为0号不用，所以多申请一个
	for (i = 1; i < vn + 1; i++) {
		ptr = (graphPointer)malloc(sizeof(node));
		ptr->id = i;
		ptr->link = NULL;
		tree[i] = ptr;
	}
	int trees[MAX_SIZE][MAX_SIZE] = {0};

	for (i = 1; i < vn + 1; i++) {
		trees[i][i] = 1;
	}

	printf("Kruskal:\n");
	for (i = 1; i < vn; i++) {
		w = 10000;//假设每条边的权重均小于10000；
		//找到一条不在现有集合中的最小边
		for (j = 1; j < vn + 1; j++) {
			temp = graph[j];
			while (temp != NULL) {
				if (temp->weight <= w) {
					//树群校验
					
					if (trees[j][temp->id] == 1) {
						//存在回路
					}
					else {
						w = temp->weight;
						targetV = temp->id;
						startV = j;
					}
				}
				temp = temp->link;
			}
		}
		//更新树群
		for (k = 1; k < MAX_SIZE; k++) {
			if (trees[startV][k]) {
				trees[targetV][k] = 1;
			}
			else if (trees[targetV][k]) {
				trees[startV][k] = 1;
			}
		}
		for (j = 1; j < MAX_SIZE; j++) {
			if (trees[startV][j]) {
				for (k = 1; k < MAX_SIZE; k++) {
					if (trees[targetV][k]) {
						trees[j][k] = 1;
					}
				}
			}
		}
		for (j = 1; j < MAX_SIZE; j++) {
			if (trees[targetV][j]) {
				for (k = 1; k < MAX_SIZE; k++) {
					if (trees[startV][k]) {
						trees[j][k] = 1;
					}
				}
			}
		}
		trees[0][0] = 0;
		printf("%d --- %d  %d\n", startV, targetV,w);
	}

}
