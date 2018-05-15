#ifndef BACKGAMMONBOARD_H
#define BACKGAMMONBOARD_H

#include "BackgammonMove.h"

const int BOARDSIZE = 24;

class BackgammonBoard
{
public:
	BackgammonBoard();
	explicit BackgammonBoard(int board[], bool turn, int captured[], BackgammonMove lastMove);
	BackgammonBoard(BackgammonBoard & bb);
	int * getBoard();
	vector<BackgammonMove> getPossibleMoves(int die1, int die2) const; // where die1 >= die2
	bool operator == (const BackgammonBoard & bb) const;
	void print(ostream & out);
	~BackgammonBoard();
private:
	int board[BOARDSIZE];
	int captured[2];
	bool turn; // true = positive player's turn, false otherwise
	BackgammonMove lastMove;
};

BackgammonBoard::BackgammonBoard()
{
	turn = true;
	board[0] = -2;
	board[1] = 0;
	board[2] = 0;
	board[3] = 0;
	board[4] = 0;
	board[5] = 5;
	board[6] = 0;
	board[7] = 3;
	board[8] = 0;
	board[9] = 0;
	board[10] = 0;
	board[11] = -5;
	board[12] = 5;
	board[13] = 0;
	board[14] = 0;
	board[15] = 0;
	board[16] = -3;
	board[17] = 0;
	board[18] = -5;
	board[19] = 0;
	board[20] = 0;
	board[21] = 0;
	board[22] = 0;
	board[23] = 2;

	captured[0] = captured[1] = 0;
}

BackgammonBoard::BackgammonBoard(int board[], bool turn, int captured[], BackgammonMove lastMove)
{
	for (int i = 0; i < BOARDSIZE; ++i)
		this->board[i] = board[i];
	this->turn = turn;
	this->captured[0] = captured[0];
	this->captured[1] = captured[1];
	this->lastMove = lastMove;
}

BackgammonBoard::BackgammonBoard(BackgammonBoard & bb)
{
	for (int i = 0; i < BOARDSIZE; ++i)
		board[i] = bb.board[i];
	turn = bb.turn;
	captured[0] = bb.captured[0];
	captured[1] = bb.captured[1];
	lastMove = bb.lastMove;
}

int * BackgammonBoard::getBoard()
{
	return board;
}


bool BackgammonBoard::operator == (const BackgammonBoard & bb) const
{
	if (turn != bb.turn) return false;
	if (captured[0] != bb.captured[0] || captured[1] != bb.captured[1]) return false;
	for (int i = 0; i < BOARDSIZE; ++i)
		if (board[i] != bb.board[i])
			return false;
	return true;
}

BackgammonBoard::~BackgammonBoard()
{
}

void BackgammonBoard::print(ostream & out)
{
	char buffer[30];

	// Top row

	for (int i = 0; i < BOARDSIZE / 2; ++i)
	{
		int padding = 2;
		if (board[11 - i] < 0) padding--;
		if (abs(board[11 - i]) > 9) padding--;
		if (padding == 2) out << " ";
		out << board[11 - i];
		if (padding != 0) out << " ";
		if (i == 5) out << " | ";
	}
	out << endl;

	for (int i = 0; i < BOARDSIZE / 2 + 1; ++i)
		out << "---";

	out << " Captured Stones: " << captured[0] << " " << captured[1] << endl;

	for (int i = 0; i < BOARDSIZE / 2; ++i)
	{
		int padding = 2;
		if (board[12 + i] < 0) padding--;
		if (abs(board[12 + i]) > 9) padding--;
		if (padding == 2) out << " ";
		out << board[12 + i];
		if (padding != 0) out << " ";
		if (i == 5) out << " | ";
	}

	out << endl;

	out.flush();
}

ostream & operator << (ostream & out, BackgammonBoard bb)
{
	bb.print(out);
	return out;
}


#endif
