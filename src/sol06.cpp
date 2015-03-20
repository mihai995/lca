/* Binary search
*       Analogue to sol02 and sol04, but bynary searches the destination
*       TIME:   O(NlogN) pre-processing, O(logN) per query
*       MEMORY: O(NlogN)
*/

#include "lib/tree.h"
#include "lib/matrix.h"

int *start, *stop;
int *depth, *dad;
Matrix T;

void before(int x){
	start[x] = ++start[0];
	depth[x] = 1 + depth[ dad[x] ];
}

void after(int x){
	stop[x] = ++stop[0];
}

void prepare(int* buf, int N){
	alloc(depth, N);
	alloc(start, N);
	alloc(stop,  N);
	dad = buf;

	dfs(dad, N, before, after);
	start[0] = 0;

	int H = msb( getMaxDepth(depth, N) );
	T.build(H + 1, N + 1, buf);

	for (int t = 1; t <= H; t++)
		for (int i = 1; i <= N; i++)
			T[t][i] = T[t - 1][ T[t - 1][i] ];
}

inline bool isAncestor(int A, int x){
	return start[A] <= start[x] && stop[x] <= stop[A];
}

int lca(int x, int y){
	if ( isAncestor(x, y) )
		return x;

	for (int t = msb(depth[x]); t >= 0; t--)
		if ( !isAncestor( T[t][x], y ) )
			x = T[t][x];
	return T[0][x];
}

int main(int argc, char** argv){
	lca_online(argv[1], argv[2], prepare, lca);
	return 0;
}
