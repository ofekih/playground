#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <algorithm>
using namespace std;
#include "Letter.h"
#include "Boggle.h"
#include <unistd.h>


void find_and_replace(string& source, string const& find, string const& replace)
{
    for(string::size_type i = 0; (i = source.find(find, i)) != string::npos;)
	{
		source.replace(i, find.length(), replace);
		i += replace.length();
	}
}

// string * getWords(const char * fileName)
// {
	//
	// string line;
	// cout << numLines << endl;
// 	return words;
// }

int main()
{
	ifstream infile("enable2k.txt");
	int numLines;
	infile >> numLines;
	string words[numLines];
	for (int i = 0; i < numLines; ++i)
		getline(infile, words[i]);

	Boggle boggle;
	string row;
	for (int i = 0; i < 6; ++i) {
		cin >> row;
		boggle.addRow(row.c_str());
	}
	// boggle.addRow("abcda");
	// boggle.addRow("efgha");
	// boggle.addRow("ijkla");
	// boggle.addRow("mnopa");
	// boggle.addRow("mnopa");

	string q("q"), qu("qu");
	usleep(5000000);
	for (int i = 1; i < numLines; ++i)
	{
		if (boggle.canSplout(words[i].c_str()))
		{
			// cout << "found " << words[i].c_str() << endl;
			find_and_replace(words[i], q, qu);
			system(("xdotool type " + words[i]).c_str());
			system("xdotool key KP_Enter");
			usleep(10000);
		}
		// cout << words[i] << endl;
	}


	// cout << boggle.canSplout("deaf") << endl;
	// cout << boggle.canSplout("nokf") << endl;
	// cout << boggle.canSplout("nokfd") << endl;
	// cout << boggle.canSplout("nokfa") << endl;
	return 0;
}