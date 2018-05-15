#ifndef BACKGAMMONMOVE_H
#define BACKGAMMONMOVE_H

const int MAXSHIFTS = 4;

class BackgammonMove
{
public:
	BackgammonMove();
	BackgammonMove(BackgammonMove & bm);
	BackgammonMove operator = (const BackgammonMove & bm);
	bool operator == (const BackgammonMove & bm) const;
	void addShift(int from, int to);

private:
	int shifts[MAXSHIFTS][2];
	int numShifts;
};

BackgammonMove::BackgammonMove() : numShifts(0)
{
	for (int i = 0; i < MAXSHIFTS; ++i)
		shifts[i][0] = -1;
}

BackgammonMove::BackgammonMove(BackgammonMove & bm) : numShifts(bm.numShifts)
{
	for (int i = 0; i < MAXSHIFTS; ++i)
	{
		shifts[i][0] = bm.shifts[i][0];
		shifts[i][1] = bm.shifts[i][1];
	}
}

BackgammonMove BackgammonMove::operator = (const BackgammonMove & bm)
{
	for (int i = 0; i < MAXSHIFTS; ++i)
	{
		shifts[i][0] = bm.shifts[i][0];
		shifts[i][1] = bm.shifts[i][1];
	}
	numShifts = bm.numShifts;
	return *this;
}

bool BackgammonMove::operator == (const BackgammonMove & bm) const
{
	if (numShifts != bm.numShifts) return false;
	for (int i = 0; i < MAXSHIFTS; ++i)
		if (shifts[i][0] != bm.shifts[i][0] || shifts[i][1] != bm.shifts[i][1])
			return false;
	return true;
}

void BackgammonMove::addShift(int from, int to)
{
	shifts[numShifts][0] = from;
	shifts[numShifts][1] = to;
	numShifts++;
}

#endif
