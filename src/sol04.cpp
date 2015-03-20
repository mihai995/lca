/* SQRT Jumps
*	Analogue to sol02, but jumps chunks of sqrt(N)
*	TIME: 	O(N) pre-processing
*		O( sqrt(H) ) per query
*	MEMORY: O(N)
*/

#include "lib/tree.h"

int *T, *depth, *head;
int *start, *stop;
int *stack, top;

inline int getStep(int n){
	return 1 << ( msb( depth[n] ) >> 1 );
}

void before(int x){
	start[x] = ++start[0];

	stack[ ++top ] = x;
	depth[x] = 1 + depth[ T[x] ];
	head[x] = stack[ top - getStep(x) ];
}

void after(int x){
	stop[x] = ++stop[0];
	top--;
}

void prepare(int* T, int N){
	alloc(depth, N);
	alloc(start, N);
	alloc(stop,  N);
	alloc(head,  N);
	::T = T;

	alloc(stack, N);
	top = 0;

	dfs(T, N, before, after);
	start[0] = 0;

	freeSafe(stack);
}

inline bool isAncestor(int A, int x){
	return start[A] <= start[x] && stop[x] <= stop[A];
}

inline int goUp(int* T, int x, int y){
	while ( !isAncestor(T[x], y) )
		x = T[x];
	return x;
}

int lca(int x, int y){
	x = goUp(head, x, y);
	x = goUp(T,    x, y);

	if ( isAncestor(x, y) )
		return x;
	return T[x];
}

int main(int argc, char** argv){
	lca_online(argv[1], argv[2], prepare, lca);
	return 0;
}
