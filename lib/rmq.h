#ifndef __LIB_RMQ
#define __LIB_RMQ

#include "matrix.h"

class Rmq{
	Matrix rmq;
	int (*best)(int, int);
	int N;

public:
	void build( int*, int (*)(int, int), int);
	int query(int, int);
};

#endif
