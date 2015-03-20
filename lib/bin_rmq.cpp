#include "bin_rmq.h"
#include "tree.h" ///REMOVE AFTER DEBUG

inline int __msb(int n){
	return 31 - __builtin_clz(n);
}

inline int __getValue(int pattern){
	return 2 * __builtin_popcount(pattern) - __msb(pattern);
}

void BinRmq :: build(int N){
	int lim = 1 << N;
	best = new int[lim]();

	best[1] = 1;
	for ( int i = 2; i < lim; i++ )
		if ( __getValue(i) <= __getValue( best[i >> 1] ) )
			best[i] = best[i >> 1];
		else
			best[i] = i;

	for ( int i = 0; i < lim; i++)
		best[i] = __msb( best[i] );
}

int BinRmq :: operator[](const int pattern) {
	return best[ pattern ];
}

BinRmq :: ~BinRmq(){
	delete[] best;
}
