const int NUM_LETTERS = 26;
const int MAX_ROW_LEN = 26;

class Boggle {
public:
	explicit Boggle();
	Boggle(const Boggle &b);
	void addRow(const char * row);
	bool canSplout(const char * w); // splout == spell out
	~Boggle();

private:
	vector<Letter *> letters[NUM_LETTERS];
	vector<Letter *> pRow; // previous row
};
