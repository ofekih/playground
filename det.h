const int SIZE = 3; // max size 3 o_O
const int SIZE2 = SIZE * SIZE;
const int MAPSIZE = 1000000000;

// remember to update result calculation

class DetBoard
{
public:
	explicit DetBoard(int h = 0);
	DetBoard(const DetBoard &d);
	void playMove(int n, int m);
	void undoMove(int n, int m);
	bool over();
	int result();
	~DetBoard();
	static int solveBoard(DetBoard &d, int target_sign, ofstream & ofile);
	static void save(int hash, int result, ofstream & ofile);

// private:
	bool moves[SIZE2];
	int board[SIZE2];
	int movesleft;
	int hash;
	static char hashmap[MAPSIZE];
	static bool visitedmap[MAPSIZE];
};