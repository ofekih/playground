#include <iostream>
#include <fstream>
using namespace std;
#include "det.h"

int main()
{
	ofstream myfile;
	myfile.open("3x3.txt");
	DetBoard d;
	DetBoard::solveBoard(d, 1, myfile);
	myfile.close();
	return 0;
}

