class Ddset{
	int *P;

	int getRoot(int);
public:
	Ddset();
	void resize(int);
	void link(int, int);
	int operator[](const int);
	~Ddset();
};
