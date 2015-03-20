/* Binary search
* 	Analogue to sol01 and sol03, but bynary searches the destination
*	TIME:	O(NlogN) pre-processing, O(logN) per query
*	MEMORY: O(NlogN)
*/

#include "lib/tree.h"
#include "lib/matrix.h"

int *dad, *depth;
Matrix T;

void before(int x){
	depth[x] = 1 + depth[ dad[x] ];
}

void after(int x){
}

void prepare(int* buf, int N){
	alloc(depth, N);
	dad = buf;

	dfs(dad, N, before, after);

	int H = msb( getMaxDepth(depth, N) );
	T.build(H + 1, N + 1, buf);

	for (int t = 1; t <= H; t++)
		for (int i = 1; i <= N; i++)
			T[t][i] = T[t - 1][ T[t - 1][i] ];
}

int ancestor(int nr, int x){
	for (int p; nr; nr ^= 1 << p)
		x = T[ p = lsb(nr) ][x];
	return x;
}

int lca(int x, int y){
	if ( depth[x] < depth[y])
		y = ancestor(depth[y] - depth[x], y);
	else
		x = ancestor(depth[x] - depth[y], x);

	if (x == y)
		return x;

	for (int t = msb(depth[x]); t >= 0; t--)
		if (T[t][x] && T[t][x] != T[t][y]){
			x = T[t][x];
			y = T[t][y];
		}
	return T[0][x];
}

int main(int argc, char** argv){
	lca_online(argv[1], argv[2], prepare, lca);
	return 0;
}
