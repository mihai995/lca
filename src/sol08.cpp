/* Heavy path
* 	Binary search over the previous solution (sol07)
*       TIME:   O(N loglogN) pre-processing, O(loglogN) per query
*       MEMORY: O(N loglogN)
*/

#include "lib/matrix.h"
#include "lib/tree.h"

int *weight, *son;
int *start, *stop, *T;
Matrix head;
int lglg;

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
	while ( !head[0][H] && son[ T[H] ] == H )
		H = T[H];

	if ( !head[0][H] )
		head[0][H] = T[H];

	while ( H != x ){
		head[0][x] = head[0][H];
		x = T[x];
	}
}

void buildHead(int N){
	lglg = msb( msb(N) );
	head.build( lglg + 1, N + 1 );

	int root = getRoot(T);
	head[0][root] = root;
	for (int i = 1; i <= N; i++)
		getHead(i);
	for (int i = 1; i <= lglg; i++)
		for (int j = 1; j <= N; j++)
			head[i][j] = head[i - 1][ head[i - 1][j] ];
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

	buildHead(N);
	freeSafe(son);
	freeSafe(T);
}

inline int isAncestor(int A, int x){
	return start[A] <= start[x] && stop[x] <= stop[A];
}

int getCandidate(int x, int y){
	if ( isAncestor(x, y) )
		return x;
	for ( int i = lglg; i >= 0; i--)
		if ( !isAncestor( head[i][x], y ) )
			x = head[i][x];
	return head[0][x];
}

int lca(int x, int y){
	int a = getCandidate(x, y), b = getCandidate(y, x);
	return isAncestor(b, a) ? a : b;
}

int main(int argc, char** argv){
	lca_online(argv[1], argv[2], prepare, lca);
	return 0;
}
