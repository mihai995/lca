/*
* Binary RMQ Data Structure: Computes the Range Minimum Query for short sequences that have the property that the value of consecutive term differs
* by exactly 1. Complexity: O(2^N) pre-processing time and memory, O(1) per query.
* Interface: in order to communicate the query, one must compute a bit mask the following way: For any position between 1 and N - 1, store 1 if the
* element is better than it predecessor and 0 if it is not. Pad the bit mask with one 1 at the end to mark its precise length.
* EXAMPLE: the sequence {1, 2, 1, 0, 1, 2, 3, 4} becomes 11001111
*/

#include "bin_rmq.h"

inline int __msb(int n){					// Most significant bit function
	return 31 - __builtin_clz(n);
}

inline int __getValue(int pattern){				// Computes the new worth of a bit mask at the end. For instance, 1001001 maps to -2
	return 2 * __builtin_popcount(pattern) - __msb(pattern);
}

void BinRmq :: build(int N){
	int lim = 1 << N;
	best = new int[lim]();

	best[1] = 1;
	for ( int i = 2; i < lim; i++ )				// Initially, best[x] = a mask whose best is attained at the same position as x's
		if ( __getValue(i) <= __getValue( best[i >> 1] ) )
			best[i] = best[i >> 1];
		else
			best[i] = i;

	for ( int i = 0; i < lim; i++)				// Then it is set to the actual value
		best[i] = __msb( best[i] );
}

int BinRmq :: operator[](const int pattern) {			// Overloading the [] operator as a way to query the data structure
	return best[ pattern ];
}

BinRmq :: ~BinRmq(){
	delete[] best;
}
