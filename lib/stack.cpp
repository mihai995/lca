// Simple stack

#include <cstdlib>
#include "stack.h"

Stack :: Stack(){
	stk = (int*) calloc(2, sizeof(int));
}

void Stack :: push(int x){
	if ( stk[0] && !(stk[0] & stk[0]-1) )
		stk = (int*) realloc( stk, 2 * stk[0] * sizeof(int) );
	stk[ ++stk[0] ] = x;
}

bool Stack :: isEmpty(){
	return stk[0] == 0;
}

int Stack :: pop(){
	return stk[ stk[0]-- ];
}

Stack :: ~Stack(){
	free(stk);
}
