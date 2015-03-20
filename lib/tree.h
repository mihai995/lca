#ifndef __LIB_TREE
#define __LIB_TREE

struct Pair{
	int x, y;
};

int msb(int), lsb(int);
void echo(const char*);
void echo(int);

template<class Type>
Type* alloc(Type* &p, int N){
	return p = new Type[N + 1]();
}

template<class Type>
void freeSafe(Type* &p){
	delete[] p;
	p = 0;
}

int getRoot(int*);
int getMaxDepth(int*, int);
void buildEuler(int*, int, int*&, int*&);
void dfs(int*, int, void (*)(int), void (*)(int));

void lca_online ( char*, char*, void (*)(int*, int), int (*)(int, int) );
void lca_offline( char*, char*, int* (*)(int*, int, Pair*, int) );

#endif
