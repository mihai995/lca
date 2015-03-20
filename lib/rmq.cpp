/*
* Range minimum query implementation
* Functionality: Takes a sequence of integers and a comparison function and can answer questions of the form
	query(x, y) = what is the best element in the interval [x; y]
* Complexity: pre-preocessing: O(NlogN) time and memory, O(1) per query
*/

#include "matrix.h"
#include "rmq.h"

void Rmq :: build(int* v, int (*best)(int, int), int N){
	this -> best = best;
	int lg = 31 - __builtin_clz(N);

	rmq.build( lg + 1, N + 1, v );
	for (int i = 1, step = 1; i <= lg; i++, step <<= 1)
		for (int j = 0; j <= N - step; j++)
			rmq[i][j] = best( rmq[i - 1][j], rmq[i - 1][j + step] );
}

int Rmq :: query(int x, int y){
	if (x < y) {
		int lg = 31 -__builtin_clz(y - x);
		return best( rmq[lg][x], rmq[lg][ y - (1 << lg) + 1 ] );
	}
	return x == y ? rmq[0][x] : 0;
}
