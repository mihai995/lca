#include "lib/tree.h"

int *T, *depth, *euler;
int *bucket, step;

int best(int x, int y){
	return depth[x] < depth[y] ? x : y;
}

void prepare(int* T, int N){
	buildEuler(T, N, depth, euler);
	for (int i = euler[0]; i; i--)
		T[ euler[i] ] = i;
	::T = T;

	step = 1 << ( msb(euler[0]) >> 1 );
	alloc(bucket, euler[0] / step);

	for (int i = 1; i <= euler[0]; i++)
		bucket[i / step] = best( bucket[i / step], euler[i] );
}

int query(int v[], int x, int y){
	int ans = 0;
	for (int i = x; i <= y; i++)
		ans = best(ans, v[i]);
	return ans;
}

int lca(int x, int y){
	if (T[y] < T[x])
		return lca(y, x);

	x = T[x]; y = T[y];
	int X = (x - 1) / step + 1;
	int Y = (y + 1) / step - 1;

	if (Y < X) return query(euler, x, y);

	return best( 	query( bucket, X, Y), best(
			query( euler, x, X * step - 1),
			query( euler, (Y + 1) * step, y) ) );
}

int main(int argc, char** argv){
	lca_online(argv[1], argv[2], prepare, lca);
	return 0;
}
