#include <stdio.h>
#include <stdlib.h>

void printListeTable (int n, int** array);
void printArray(int n, int* array);
void bfs (int n, int** array, int i, int* alreadyVisited, int* visited, int* parent, int* returnArete);

int main(int argc, char const *argv[]) {
	// read input
	FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("File not found. \n");
        exit(12);
    }
    int n;
    fscanf(file,"%d",&n);
    int* array[n];
    for (int i = 0; i < n; ++i) {
    	int nb;
    	fscanf(file,"%d",&nb);
    	int* line = (int*) malloc(sizeof(int)*(nb+1));
    	line[0]=nb;
	    for (int j = 1; j < nb+1; ++j) {
	    	fscanf(file,"%d",&line[j]);
	    }
	    array[i]=line;
    }
    fclose(file);
    // end read input
    int* alreadyVisited = (int*) malloc(sizeof(int));
    alreadyVisited=0;
    int* visited = (int*) malloc(sizeof(int)*n); // if visited then 0 else order of visit 
    for (int i = 0; i < n; ++i) {
    	visited[i]=0;
    }
    int* parent = (int*) malloc(sizeof(int)*n);
    parent[0]=0; // root
    for (int i = 0; i < n; ++i) {
    	visited[i]=-1;
    }
    int* returnArete = (int*) malloc(sizeof(int)*n); 
    for (int i = 0; i < n; ++i) {
    	returnArete[i]=-1;
    }
    printListeTable(n, array);
    bfs(n, array, 0, alreadyVisited, visited, parent, returnArete);
    printArray(n, visited);
    printArray(n, parent);
    printArray(n, returnArete);

	return 0;
}

void bfs (int n, int** array, int i, int* alreadyVisited, int* visited, int* parent, int* returnArete) {
	visited[i]=*alreadyVisited+1;
	alreadyVisited++;
	for (int j = 0; j < n; ++j) {
		for (int k = 1; k < array[i][0]+1; ++k) {
			if (visited[array[i][k]]>0) {
				// voisin visité ==> arête de retour
				returnArete[array[i][k]]=i;
			}
			else {
				// voisin non visité
				parent[array[i][k]]=i;
				bfs(n, array, array[i][k], alreadyVisited, visited, parent, returnArete);
			}
		}
	}
}

void printListeTable (int n, int** array) {
	printf("n = %d\n", n);
	for (int i = 0; i < n; ++i) {
		printf("noeud[%d]", i);
		for (int j = 1; j < array[i][0]+1; ++j) {
			printf("\t%d", array[i][j]);
		}
		printf("\n");
	}
}

void printArray (int n, int* array) {
	for (int i = 0; i < n; ++i) {
		printf("\t%d\n", array[i]);
	}
}