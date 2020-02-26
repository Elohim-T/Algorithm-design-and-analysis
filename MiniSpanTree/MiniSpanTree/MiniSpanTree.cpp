
#include <stdio.h>
#include "graph.h"
int main()
{
	int vn, en;
	graphPointer* graph;
	graph = createGraph(&vn, &en);

	//prim(graph,vn);
	kruskal(graph, vn);
}
