#ifndef __LIB_SEGMENT_TREE
#define __LIB_SEGMENT_TREE

class Aint{
        int* aint,  N;
	int (*best)(int, int);

public:
	Aint();
        void flush(int* buf, int (*cmp)(int, int));
        int query(int, int);
        ~Aint();
};

#endif
