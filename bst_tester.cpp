#include <stdio.h>
#include <iostream>
using namespace std;

#include "BST.h"



int main() {
	BST<int> tree(5);
	tree.insert(2);
	tree.insert(1);
	tree.insert(5);
	tree.insert(7);
	tree.insert(4);
	// for (int i = 0; i < 100; i++)
	// 	tree.insert(i);

	cout << tree.contains(7) << endl;
	cout << tree.minDepth() << endl;
	cout << tree.maxDepth() << endl;

	// tree.print(cout);

	// cout << endl;
	cout << tree << endl;

	BST<double> treef(12.7);

	cout << treef << endl;
}
