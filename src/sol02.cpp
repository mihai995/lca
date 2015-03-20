#include "lib/tree.h"

int *start, *stop;
int *T, *depth;

void before(int x){
	depth[x] = 1 + depth[ T[x] ];
	start[x] = ++start[0];
}

void after(int x){
	stop[x] = ++stop[0];
}

void prepare(int* T, int N){
	alloc(depth, N);
	alloc(start, N);
	alloc(stop,  N);
	::T = T;

	dfs(T, N, before, after);
	start[0] = 0;
}

inline int isAncestor(int A, int x){
	return start[A] <= start[x] && stop[x] <= stop[A];
}

int lca(int x, int y){
	if ( depth[y] < depth[x] )
		return lca(y, x);
	while ( !isAncestor(x, y) )
		x = T[x];
	return x;
}

int main(int argc, char** argv){
	lca_online(argv[1], argv[2], prepare, lca);
	return 0;
}
