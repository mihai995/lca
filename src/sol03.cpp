/* SQRT Jumps
*	Analogue to sol01, but instead of moving up linearly,
*	it jumps chuks of sqrt(H) nodes
*	TIME:   O(N) pre-processing
		O( sqrt(H) ) per query
*	MEMORY: O(N)
*/

#include "lib/tree.h"

int *T, *depth, *head;
int *stack, top;

inline int getStep(int n){
	return 1 << ( msb( depth[n] ) >> 1 );
}

void before(int x){
	stack[ ++top ] = x;
	depth[x] = 1 + depth[ T[x] ];
	head[x] = stack[ top - getStep(x) ];
}

void after(int x){
	top--;
}

void prepare(int* T, int N){
	alloc(depth, N);
	alloc(stack, N);
	alloc(head,  N);
	top = 0;

	::T = T;
	dfs(T, N, before, after);
	freeSafe(stack);
}

inline int getAncestor(int x, int L){
	while ( getStep(x) <= L ){
		L -= getStep(x);
		x = head[x];
	}
	while (L--)
		x = T[x];
	return x;
}

inline void goUp(int* T, int& x, int& y){
	while (T[x] != T[y]){
		x = T[x];
		y = T[y];
	}
}

int lca(int x, int y){
	if ( depth[y] < depth[x] )
		x = getAncestor(x, depth[x] - depth[y]);
	if ( depth[x] < depth[y] )
		y = getAncestor(y, depth[y] - depth[x]);

	goUp(head, x, y);
	goUp(T, x, y);

	if (x == y)
		return x;
	return T[x];
}

int main(int argc, char** argv){
	lca_online(argv[1], argv[2], prepare, lca);
	return 0;
}
