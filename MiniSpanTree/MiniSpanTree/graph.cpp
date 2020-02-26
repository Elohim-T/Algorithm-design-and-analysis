
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
	//��Ϊ0�Ų��ã����Զ�����һ��
	for (i = 0; i < *vn +1;i++) {
		graph[i] = NULL;
	}
	//��Ϊ������ͼ������һ���߻ᱻ��������
	for (i = 0; i < *en * 2; i++) {
		fscanf_s(fin, "%d %d %d", &start, &end, &weight);
		insertEdge(&graph[start], end, weight);
	}

	fclose(fin);

	return graph;
}
void insertEdge(graphPointer* graph, int e, int w) {
	//����һ���±�
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
	//����һ���½ڵ�
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
//��С����������Prim�㷨
void prim(graphPointer* graph, int vn) {
	int pointSet[MAX_SIZE+1] = {0};//���е㼯
	int i, j;
	int w;//����
	int targetV;//Ŀ���
	int startV; //��ʼ��
	graphPointer temp;

	printf("Prim:\n");
	//��1�ŵ㿪ʼ
	pointSet[1] = 1;

	for (i = 1; i < vn; i++) {

		w = 10000;//����ÿ���ߵ�Ȩ�ؾ�С��10000��
		//�ҵ������е㼯�������ܹ�����С���۴ﵽ�ĵ�
		for (j = 1; j < vn + 1; j++) {
			if (pointSet[j] == 1) {
				temp = graph[j];
				//�ҵ���j�������ܹ�����С���۴ﵽ�ĵ�
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
//��С����������Kruskal�㷨
void kruskal(graphPointer* graph, int vn) {

	int i, j, k;
	int w;//����
	int targetV;//Ŀ���
	int startV; //��ʼ��
	graphPointer temp,ptr1,ptr2,ptr;
	int flag1, flag2;
	
	//��ʼ����Ⱥ
	graphPointer* tree = (graphPointer*)malloc(sizeof(graphPointer*)*(vn + 1));
	//��Ϊ0�Ų��ã����Զ�����һ��
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
		w = 10000;//����ÿ���ߵ�Ȩ�ؾ�С��10000��
		//�ҵ�һ���������м����е���С��
		for (j = 1; j < vn + 1; j++) {
			temp = graph[j];
			while (temp != NULL) {
				if (temp->weight <= w) {
					//��ȺУ��
					
					if (trees[j][temp->id] == 1) {
						//���ڻ�·
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
		//������Ⱥ
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
