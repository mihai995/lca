#include <fstream>
#include <cassert>
#include <cstdlib>
using namespace std;

class RandomPick{
	int *v, size;

public:
	RandomPick(int N){
		v = new int[N + 1]();
		size = 0;
	}

	void push(int x){
		v[size++] = x;
	}

	int get(){
		return v[ rand() % size ];
	}

	int pop(){
		int pos = rand() % size, ans = v[pos];
		v[pos] = v[--size];
		return ans;
	}

	bool isEmpty(){
		return size == 0;
	}

	~RandomPick(){
		delete[] v;
	}
};

void generate(const char* fout, int N, int H, int Q){
	int* depth  = new int[N + 1]();
	int* father = new int[N + 1]();
	RandomPick nodes(N), dads(N);

	for (int i = 1; i <= N; i++)
		nodes.push(i);

	int root = nodes.pop(), node;
	depth[root] = 1;
	dads.push(root);

	for (int q = 1; q <= 2; q++)
		for (int i = 2, dad = root; i <= H; i++){
			node = nodes.pop();
			father[node] = dad;
			depth[node] = i;
			dad = node;
			if ( H != i )
				dads.push(node);
		}

	if (Q == 0) Q = N;
	while ( !nodes.isEmpty() ){
		node = nodes.pop();
		father[node] = dads.get();
		depth[node] = 1 + depth[ father[node] ];

		if ( depth[node] != H )
			dads.push(node);
	}

	ofstream out(fout);

	out << N << '\n';
	for (int i = 1; i <= N; i++)
		out << father[i] << ' ';
	out << '\n';

	out << Q << '\n';
	while (Q--)
		out << 1 + rand() % N << ' ' << 1 + rand() % N << '\n';
	out.close();

	delete[] father;
	delete[] depth;
}

int main(int argc, char** argv){
	assert( argc == 5 );
	generate( argv[1], atof(argv[2]), atof(argv[3]), atof(argv[4]) );
	return 0;
}
