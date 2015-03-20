class BinRmq{
	int* best;

	inline int getBestVal(int);
public:
	void build(int);
	int operator[](const int);
	~BinRmq();
};
