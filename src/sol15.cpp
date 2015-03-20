#include "lib/bin_rmq.h"
#include "lib/rmq.h"
#include "lib/tree.h"

int *T, *depth, *euler;
int *bucket, bSize;
int *bucketAspect;

Rmq A;
BinRmq B;

inline int __swap(int& x, int& y){
	int aux = x;
	x = y;
	y = aux;
}

int best(int x, int y){
	return depth[x] < depth[y] ? x : y;
}

inline int best(int x, int y, int z){
	return best( x, best(y, z) );
}

void prepare(int* T, int N){
	buildEuler(T, N, depth, euler);
	depth[0] = N + 1; ::T = T;
	for (int i = euler[0]; i; i--)
		T[ euler[i] ] = i;

	bSize = (int)(msb( euler[0] ) * 0.7);
	int nrBuckets = euler[0] / bSize;

	alloc(bucket, euler[0] / bSize);
	alloc(bucketAspect, nrBuckets);

	for ( int i = 0, st = 1, dr = bSize; i <= nrBuckets; i++, st += bSize, dr += bSize ){
		if ( euler[0] < dr ) dr = euler[0] + 1;
		bucket[i] = euler[st - 1];
		for (int j = st; j < dr; j++){
			bucketAspect[i] = (bucketAspect[i] << 1) ^ ( depth[ euler[j] ] < depth[ euler[j - 1] ] );
			bucket[i] = best(bucket[i], euler[j]);
		}
	}
	A.build(bucket, best, nrBuckets);
	B.build( bSize );
}

inline int query(int bucket, int x, int y){
	int size = 1 << (y - x);
	bucket = bucketAspect[bucket] >> (bSize - y % bSize - 1) & (size - 1);
	return euler[x + B[ bucket ^ size ] ];
}

int lca(int x, int y){
	x = T[x]; y = T[y];
	if (y < x) __swap(x, y);
	int X = x / bSize, Y = y / bSize;

	if ( X == Y )
		return query(X, x, y);

	return best(	query(X, x, (X + 1) * bSize - 1),
		     	A.query( X + 1, Y - 1),
		     	query(Y, Y * bSize, y)
		   );
}

int main(int argc, char** argv){
	lca_online(argv[1], argv[2], prepare, lca);
	return 0;
}
