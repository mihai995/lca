#include "lib/rmq.h"
#include "lib/tree.h"

int *T, *depth, *euler;
Rmq A;

int best(int x, int y){
	return depth[x] < depth[y] ? x : y;
}

void prepare(int* T, int N){
	buildEuler(T, N, depth, euler);
	for (int i = euler[0]; i; i--)
		T[ euler[i] ] = i;
	::T = T;

	depth[0] = N + 1;
	A.build(euler, best, euler[0]);
}

int lca(int x, int y){
	if (T[x] < T[y])
		return A.query(T[x], T[y]);
	return A.query(T[y], T[x]);
}

int main(int argc, char** argv){
	lca_online(argv[1], argv[2], prepare, lca);
	return 0;
}
