#include "lib/tree.h"

int *head, *weight, *son;
int *start, *stop, *T;

void before(int x){
	start[x] = ++start[0];
	weight[x] = 1;
}

void after(int x){
	stop[x] = ++stop[0];
	weight[ T[x] ] += weight[x];
	if ( weight[ son[ T[x] ] ] < weight[x] )
		son[ T[x] ] = x;
}

void getHead(int x){
	int H = x;
	while ( !head[H] && son[ T[H] ] == H )
		H = T[H];

	if ( !head[H] )
		head[H] = T[H];

	while ( H != x ){
		head[x] = head[H];
		x = T[x];
	}
}

void prepare(int* T, int N){
	alloc(weight,  N);
	alloc(start, N);
	alloc(stop,  N);
	alloc(son,   N);
	:: T = T;

	dfs(T, N, before, after);
	freeSafe(weight);
	start[0] = 0;

	int root = getRoot(T);
	alloc(head, N);
	head[root] = root;

	for (int i = 1; i <= N; i++)
		getHead(i);
	freeSafe(son);
	freeSafe(T);
}

inline int isAncestor(int A, int x){
	return start[A] <= start[x] && stop[x] <= stop[A];
}

int lca(int a, int b){
	int x = a, y = b;
	while ( !isAncestor(x, b) )
		x = head[x];
	while ( !isAncestor(y, a) )
		y = head[y];
	return stop[x] < stop[y] ? x : y;
}

int main(int argc, char** argv){
	lca_online(argv[1], argv[2], prepare, lca);
	return 0;
}
