#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

#include "BackgammonBoard.h"

int main()
{
	BackgammonBoard bb, bb2;
	cout << bb << endl;
	cout << (bb == bb2) << endl;
	return 0;
}
