/*
* Disjoint data set implementation.
* Functionality:
	* Every set is indexed by the best element (i.e the one that is listed the first in update operations)
	* Link: merge the set containing x and the set containing y
	* operator []: return the handle for the set containing x
* Complexity: O(log* N) per operation, O(N) memory
*/

#include <cstdlib>
#include "ddset.h"

Ddset :: Ddset(){
	P = NULL;
}

void Ddset :: resize(int N){
	P = (int*) realloc( P, (N + 1) * sizeof(int) );
	for (int i = 1; i <= N; i++)
		P[i] = i;
}

int Ddset :: getRoot(int x){
	if ( P[x] == x )
		return x;
	return P[x] = getRoot( P[x] );
}

void Ddset :: link(int x, int y){
	P[ getRoot(y) ] = getRoot(x);
}

int Ddset :: operator[](const int N){
	return getRoot(N);
}

Ddset :: ~Ddset(){
	free(P);
}
