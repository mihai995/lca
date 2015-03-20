#ifndef __LIB_MATRIX
#define __LIB_MATRIX

class Matrix{
	int* buf;
	int lineSize;

public:
	Matrix();
	void build(int N = 0, int M = 0, int* buf = 0);
	int* operator[](const int);
	~Matrix();
};

#endif
