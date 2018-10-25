#include <stdio.h>
#include <stdlib.h>

void bfs(int n, int u, int** adjacencyList, int* count, int* order, int* parent, int* children, int* low, int* ap);
void printAdjacencyList (int n, int** adjacencyList);
void printArray(int n, int* array);

int main(int argc, char const *argv[]) {
	// read input
	FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("File not found. \n");
        exit(12);
    }
    int n;
    fscanf(file,"%d",&n);
    int* adjacencyList[n];
    for (int i = 0; i < n; ++i) {
    	int nb;
    	fscanf(file,"%d",&nb);
    	int* list = (int*) malloc(sizeof(int)*(nb+1));
    	list[0]=nb;
	    for (int j = 1; j < nb+1; ++j) {
	    	fscanf(file,"%d",&list[j]);
	    }
	    adjacencyList[i]=list;
    }
    fclose(file);
    // end read input
    // init structures
    int count=0; // number of vertices already visited
    int order[n]; // if visited then 0 else order of visit
    int parent[n]; // if root then -1 else parent number 
    int children[n]; // number of children 
    int low[n]; // lowest return order in the subtree
    int ap[n]; // if articulation point then 1 else 0
    for (int i = 0; i < n; ++i) {
    	order[i]=0;
    	parent[i]=-1;
    	children[i]=0;
    	low[i]=-1;
    	ap[i]=0;
    }
    // end init structures

    // bfs to detect cut vertices
    for (int i = 0; i < n; ++i) {
    	if (order[i]==0) { // not visited
    		bfs(n, i, adjacencyList, &count, order, parent, children, low, ap);
    		if (children[i]>1) {
    			ap[i]=1;
    		}
    	}
    }
    // end bfs

    // print
    printf("Adjacency list :\n");
    printAdjacencyList(n, adjacencyList);
    printf("Orders : \n");
    printArray(n, order);
    printf("Parents : \n");
    printArray(n, parent);
    printf("Articulation points :\n");
    for (int i = 0; i < n; ++i) {
    	if (ap[i]!=0) {
    		printf("%d\t", i);
    	}
    }
    printf("\n");
    // end print

	return 0;
}

void bfs(int n, int u, int** adjacencyList, int* count, int* order, int* parent, int* children, int* low, int* ap) {
	order[u]=++(*count);
	low[u]=order[u];
	for (int i = 1; i <= adjacencyList[u][0]; ++i) {
		int v = adjacencyList[u][i];
		if (order[v]==0) { // not visited
			children[u]++;
			if (u==0) {
				printf("vertice 0 parent of %d\n", v);
			}
			parent[v]=u;
			bfs(n, v, adjacencyList, count, order, parent, children, low, ap);
			low[u]=(low[u]>low[v])?low[v]:low[u];
			if ((parent[u]!=-1)&&(low[v]>=order[u])) {
				ap[u]=1;
			}
		}
		else {
			low[u]=(low[u]>order[v])?order[v]:low[u];
		}
	}
}

void printAdjacencyList (int n, int** adjacencyList) {
	for (int i = 0; i < n; ++i) {
		printf("%d:\t", i);
		for (int j = 1; j < adjacencyList[i][0]+1; ++j) {
			printf("%d\t", adjacencyList[i][j]);
		}
		printf("\n");
	}
}

void printArray (int n, int* array) {
	for (int i = 0; i < n; ++i) {
		printf("%d\t", i);
	}
	printf("\n");
	for (int i = 0; i < n; ++i) {
		printf("%d\t", array[i]);
	}
	printf("\n");
}