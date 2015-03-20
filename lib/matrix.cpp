#include "matrix.h"
#include <cstring>

Matrix :: Matrix() : buf(NULL)
{}

void Matrix :: build(int N, int M, int* buf){
	this -> buf = new int[N * M]();
	if (buf) {
		memcpy( this -> buf, buf, M * sizeof(int) );
//		delete[] buf;
	}
	lineSize = M;
}

int* Matrix :: operator[](const int n){
	return buf + lineSize * n;
}

Matrix :: ~Matrix(){
	delete[] buf;
}
