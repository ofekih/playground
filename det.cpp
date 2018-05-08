#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;
#include "det.h"

int board_to_hash(int * board)
{
	int h = 0;
	for (int i = 0; i < SIZE2; ++i)
		h += board[i] * pow(10, SIZE2 - i - 1);
	return h;
}

void hash_to_board(int board[], int h)
{
	for (int i = SIZE2 - 1; i >= 0; --i, h /= 10)
		board[i] = h % 10;
}

DetBoard::DetBoard(int h) : movesleft(SIZE2), hash(h)
{
	for (int i = 0; i < SIZE2; ++i)
		moves[i] = true;

	for (int i = SIZE2 - 1; i >= 0; --i, h /= 10)
	{
		board[i] = h % 10;
		if (board[i] != 0)
		{
			moves[board[i] - 1] = false;
			--movesleft;
		}
	}
}

DetBoard::DetBoard(const DetBoard &d)
{
	movesleft = d.movesleft;
	hash = d.hash;
	for (int i = 0; i < SIZE2; ++i)
	{
		moves[i] = d.moves[i];
		board[i] = d.board[i];
	}
}

DetBoard::~DetBoard() {}

void DetBoard::playMove(int n, int m) // m: (0, SIZE2 - 1), eg.: {0, 1, 2, 3}
{
	board[n] = m + 1;
	moves[m] = false;
	--movesleft;
	hash += (m + 1) * pow(10, SIZE2 - n - 1);
}

void DetBoard::undoMove(int n, int m)
{
	board[n] = 0;
	moves[m] = true;
	++movesleft;
	hash -= (m + 1) * pow(10, SIZE2 - n - 1);
}

bool DetBoard::over()
{
	return movesleft == 0;
}

int DetBoard::result()
{
	// 2x2 and 3x3 equations
	// return board[0] * board[3] - board[1] * board[2];
	return board[0] * (board[4] * board[8] - board[5] * board[7]) - board[1] * (board[3] * board[8] - board[5] * board[6]) + board[2] * (board[3] * board[7] - board[4] * board[6]);
}

char DetBoard::hashmap[] = { 0 };
bool DetBoard::visitedmap[] = { false };


int DetBoard::solveBoard(DetBoard &d, int target_sign, ofstream & ofile)
{
	if (d.over())
	{
		int result = d.result();
		visitedmap[d.hash] = true;
		hashmap[d.hash] = result > 127 ? 127 : result < -127 ? -127 : result;
		save(d.hash, result, ofile);
		return result;
	}

	// cout << "Moves Left: " << d.movesleft << endl;

	int best_result = -9999;

	for (int n = 0; n < SIZE2; ++n)
		if (d.board[n] == 0)
			for (int m = 0; m < SIZE2; ++m)
				if (d.moves[m])
				{
					d.playMove(n, m);
					int result;
					if (visitedmap[d.hash])
						result = hashmap[d.hash];
					else
						result = solveBoard(d, -target_sign, ofile);

					if (result * target_sign > best_result * target_sign || best_result == -9999)
						best_result = result;
					// cout << result << "HEYA" << endl;

					d.undoMove(n, m);
					if (d.hash == 817392046)
					{
						for (int i : d.board)
							cout << i << " ";
						cout << endl;
						for (bool i : d.moves)
							cout << i << " ";
						cout << endl;
						cout << n << " " << m << endl;
						cout << result << " " << target_sign << " " << best_result << endl;

						d.playMove(n, m);
						cout << hashmap[d.hash] << " " << d.hash << endl;
						d.undoMove(n, m);
					}
				}

	visitedmap[d.hash] = true;
	hashmap[d.hash] = best_result > 127 ? 127 : best_result < -127 ? -127 : best_result;
	save(d.hash, best_result, ofile);
	return best_result;
}

void DetBoard::save(int hash, int result, ofstream & ofile)
{
	ofile << hash << " " << result << "\n";
}

