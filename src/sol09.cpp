/* Stack search
*	Offline algorithm:
*		Mark query(x, y) in both x and y
*		Do a DFS search, remember the entering time for each node
*		When encountering a query the second time, binary search the entrance
*		time of y on the ancestor stack of x.
*	TIME:	O(N + QLogH)
*	MEMORY: O(N + Q)
*/

#include "lib/stack.h"
#include "lib/tree.h"

class StackTrace{
	int *label, time;
	int *stack;

public:
	void resize(int N){
		alloc(label, N);
		alloc(stack, N);
		time = 0;
	}

	void goDown(int x){
		stack[ ++stack[0] ] = x;
		label[x] = ++time;
	}

	void goUp(int x){
		while ( stack[ stack[0]-- ] != x );
		return goDown(x);
	}

	int query(int x){
		int ans = 0;
		for (int step = 1 << msb( stack[0] ); step; step >>= 1)
			if ( ans + step < stack[0] && label[ stack[ans + step] ] < label[x] )
				ans += step;
		return stack[ans + 1];
	}

	~StackTrace(){
		freeSafe(stack);
		freeSafe(label);
	}
};

StackTrace S;
Stack* query;
int *ans, *T;

void before(int x){
	S.goDown(x);
	while ( !query[x].isEmpty() ){
		int y = query[x].pop();
		if ( ans[y] )
			ans[y] = S.query( ans[y] );
		else
			ans[y] = x;
	}
}

void after(int x){
	S.goUp( T[x] );
}

int* process(int* T, int N, Pair* Q, int nrQ){
	alloc(query, N);
	alloc(ans, nrQ);
	for (int i = 1; i <= nrQ; i++){
		query[ Q[i].x ].push(i);
		query[ Q[i].y ].push(i);

	}
	freeSafe(Q);

	::T = T;
	S.resize(N);
	dfs(T, N, before, after);

	return ans;
}

int main(int argc, char** argv){
	lca_offline(argv[1], argv[2], process);
	return 0;
}
