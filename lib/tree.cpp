/*
* Utility library with various functionalities
*/

#include "tree.h"

#include <cstdio>
void echo(const char* message)	{ fputs(message, stderr); }		//For debugging purposes
void echo(int n) 		{ fprintf(stderr, "%d ", n); }

int *__T, *__depth, *__euler;

int msb(int n){								// Most significant bit
	return 31 - __builtin_clz(n);
}

int lsb(int n){								// Least significant bit
	return __builtin_ctz(n);
}

int getRoot(int* T){							// Determines the root of a given tree
	int root = 1;
	while ( T[root] )
		root = T[root];
	return root;
}

int getMaxDepth(int* depth, int N){					// effectively computes the max value in a vector
	int maxH = 0;
	for (int i = 1; i <= N; i++)
		if (maxH < depth[i])
			maxH = depth[i];
	return maxH;
}


void dfs(int* T, int N, void (*before)(int), void (*after)(int)){	// depth first search without recursion
	int *bro, *son;								// uses a bro-son representation of the tree (basically, each node stores one son and one brother)
	alloc(bro, N); alloc(son ,N);					// before is called each time we enter a new node
	for (int i = 1; i <= N; i++){					// after is called eahc time we leave a node
		bro[i] = son[ T[i] ];
		son[ T[i] ] = i;
	}

	int x = getRoot(T);

	before(x);
	while (x)
		if ( son[x] ){
			x = son[x];
			son[ T[x] ] = bro[x];
			before(x);
		}
		else {
			after(x);
			x = T[x];
		}
	freeSafe(bro);
	freeSafe(son);
}


void eulerStart(int x){
	__depth[x] = 1 + __depth[ __T[x] ];
	__euler[ ++__euler[0] ] = x;
}

void eulerStop(int x) {
	__euler[ ++__euler[0] ] = __T[x];
}

void buildEuler(int* T, int N, int* &depth,  int* &euler){		// wrapper over dfs to determine the euler traverse of the tree
	__euler = alloc(euler, 2 * N);
	__depth = alloc(depth, N);
	__T = T;
	dfs(T, N, eulerStart, eulerStop);
	depth[0] = N + 1;
	euler[0]--;
}

int* getTree(FILE* in, int& N){						// reads a tree from file as a list of dads
	fscanf(in, "%d", &N);

	int* T; alloc(T, N);
	for (int i = 1; i <= N; i++)
		fscanf(in, "%d", T + i);

	return T;
}

void lca_online(char* fin, char* fout, void (*prepare)(int*, int), int (*lca)(int, int)){	//function that runs the online version of the lca algorithm
	int N, Q, x, y;											// takes a pre-processing function and a query function

	FILE* in = fopen(fin, "r");

	int* T = getTree(in, N);
	prepare(T, N);

	FILE* out = fopen(fout, "w");
	fscanf(in, "%d", &Q);

	while (Q--){
		fscanf(in, "%d%d", &x, &y);
		fprintf(out, "%d\n", lca(x, y));
	}

	fclose(out);
	fclose(in);
}

void lca_offline(char* fin, char* fout, int* (*process)(int*, int, Pair*, int)){		// function that runs the offine version of the lca algorithm
	int N, Q;											// takes a process function that takes a tree and an array of queries
													// and produces an array of answers
	FILE* in = fopen(fin, "r");
	int* T = getTree(in, N);

	fscanf(in, "%d", &Q);
	Pair* query; alloc(query, Q);
	for (int i = 1; i <= Q; i++)
		fscanf(in, "%d%d", &query[i].x, &query[i].y);
	fclose(in);

	int* ans = process(T, N, query, Q);

	FILE* out = fopen(fout, "w");
	for (int i = 1; i <= Q; i++)
		fprintf(out, "%d\n", ans[i]);
	fclose(out);
}

