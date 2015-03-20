/*
* Segment tree implementation (lacks implementation for update function)
* Functionality: takes a sequence of numbers and a comparison function and answers questions of the form:
	query(x, y) = what is the best element in the interval [x; y]
* Complexity: O(N) pre-processing time and memory, O(logN) per query
* NOTE: it is not the classical implementation of segment trees, because I wanted to avoid recursion
*/

#include <cstdlib>
#include <cstring>
#include "segment_tree.h"

int __aint_default_best(int a, int b){
	return a < b ? a : b;
}

Aint :: Aint() : aint(NULL) {}

void Aint :: flush(int* v, int (*best)(int, int) = __aint_default_best){
	N = 1 << ( 32 - __builtin_clz(v[0]) );

	aint = (int*) realloc(aint, 2 * N * sizeof(int));
	memcpy( aint + N, v + 1, v[0] * sizeof(int) );
	free(v);

	this -> best = best;
	for (int i = N - 1; i; i--)
		aint[i] = best( aint[i << 1], aint[1 + (i << 1)] );
}

int Aint :: query(int x, int y){
	int ansX = aint[x += N - 1], ansY = aint[y += N - 1];

	int stopX = x >> (31 - __builtin_clz(x ^ y) );
	int stopY = y >> (31 - __builtin_clz(x ^ y) );

	while ( stopX < ( x >>= __builtin_ctz(~x) ) )
		ansX = best( ansX, aint[x ^= 1] );
	while ( stopY < ( y >>= __builtin_ctz(y) ) )
		ansY = best( aint[y ^= 1], ansY );

	return best(ansX, ansY);
}

Aint :: ~Aint(){
	free(aint);
}
