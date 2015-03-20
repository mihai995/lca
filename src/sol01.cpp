/* Brute force implementation
* 	query(x, y):
*		get x and y on the same level
*		move un with them in parallel until they meet
*	TIME:   O(N), O(H) per query
*	MEMORY: O(N)
*/

#include "lib/tree.h"

int *T, *depth;

void before(int x){
	depth[x] = 1 + depth[ T[x] ];
}

void after(int x){
}

void prepare(int* T, int N){
	alloc(depth, N);
	::T = T;
	dfs(T, N, before, after);
}

int lca(int x, int y){
	while (depth[x] < depth[y])
		y = T[y];
	while (depth[y] < depth[x])
		x = T[x];

	while (x != y){
		x = T[x];
		y = T[y];
	}
	return x;
}

int main(int argc, char** argv){
	lca_online(argv[1], argv[2], prepare, lca);
	return 0;
}
