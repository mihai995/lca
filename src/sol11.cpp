#include "lib/tree.h"

int *T, *depth, *euler;

int best(int x, int y){
	return depth[x] < depth[y] ? x : y;
}

void prepare(int* T, int N){
	buildEuler(T, N, depth, euler);
	for (int i = euler[0]; i; i--)
		T[ euler[i] ] = i;
	::T = T;
}

int lca(int x, int y){
	if (T[y] < T[x])
		return lca(y, x);

	int ans = 0;
	for (int i = T[x]; i <= T[y]; i++)
		ans = best(ans, euler[i]);
	return ans;
}

int main(int argc, char** argv){
	lca_online(argv[1], argv[2], prepare, lca);
	return 0;
}
