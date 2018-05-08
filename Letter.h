class Letter {
public:
	explicit Letter();
	explicit Letter(char l);
	Letter(const Letter &l);
	Letter operator = (const Letter &l);
	int getIndex();
	void connect(Letter * l);
	bool canSplout(const char * w); // splout = spell out
	operator bool() const;
	~Letter();
private:
	char letter;
	int index;
	bool visited; // used in algorithms
	vector<Letter *> connections;
};