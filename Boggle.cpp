#include <iostream>
#include <vector>
using namespace std;

#include "Letter.h"
#include "Boggle.h"

Boggle :: Boggle() {}

Boggle :: Boggle(const Boggle &b)
{
	for (int i = 0; i < NUM_LETTERS; ++i)
		letters[i] = b.letters[i];
}

Boggle :: ~Boggle() {}

void Boggle :: addRow(const char * row)
{
	vector<Letter *> r;
	Letter * pL;
	for (; row[0] != '\0'; row = &row[1])
	{
		Letter * l = new Letter(row[0]);
		if (r.size() != 0)
			pL->connect(l);
		r.push_back(l);
		letters[l->getIndex()].push_back(l);
		pL = l;
		// cout << pL->getIndex() << endl;
		// cout << r[0]->getIndex() << endl;
	}

	// connections with above row
	if (pRow.size() != 0)
	{
		for (int i = 0; i < pRow.size(); ++i)
		{
			r[i]->connect(pRow[i]);
			if (i == 0)
				r[i]->connect(pRow[i+1]);
			else if (i != pRow.size() - 1)
			{
				r[i]->connect(pRow[i - 1]);
				r[i]->connect(pRow[i + 1]);
			}
			else
				r[i]->connect(pRow[i - 1]);
		}
	}

	pRow = r;
}

bool Boggle :: canSplout(const char * w) // splout == spell out
{
	for (Letter * l : letters[w[0] - 'a'])
		if (l->canSplout(&w[1]))
			return true;
	return false;
}
