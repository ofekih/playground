#include <iostream>
#include <vector>
using namespace std;

#include "Letter.h"

Letter :: Letter() : letter('\0'), index(-1), visited(false) {}

Letter :: Letter(char l) : letter(l), index(l - 'a'), visited(false) {}

Letter :: Letter(const Letter &l) : letter(l.letter), index(l.index),
	visited(false), connections(l.connections) {}

Letter Letter :: operator = (const Letter &l)
{
	letter = l.letter;
	index = l.index;
	visited = l.visited;
	connections = l.connections;
	return *this;
}

int Letter :: getIndex()
{
	return index;
}

bool Letter :: canSplout(const char * w) // splout == spell out
{
	if (w[0] == '\0') return true;
	visited = true;
	bool works = false;
	for (Letter * l : connections)
	{
		if (l->visited || l->letter != w[0]) continue;
		else if (l->canSplout(&w[1]))
		{
			works = true;
			break;
		}
	}
	visited = false;
	return works;
}

Letter :: operator bool() const
{
	return letter != '\0';
}

void Letter :: connect(Letter * l) {
	// cout << "Connecting: (" << letter << ") to (" << l->letter << ")\n";
	connections.push_back(l);
	l->connections.push_back(this);
}

Letter :: ~Letter() {}
