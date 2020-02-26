#pragma once
#define MAX_SIZE 10
typedef struct node * graphPointer;

typedef struct node {
	int weight;
	int id;
	graphPointer link;
};

graphPointer* createGraph(int* vn, int* en);
void insertEdge(graphPointer* graph, int e, int w);
graphPointer* insertVertex(graphPointer* graph,int *vn);
bool isEmpty(graphPointer* graph);
void prim(graphPointer* graph,int vn);
void kruskal(graphPointer* graph,int vn);