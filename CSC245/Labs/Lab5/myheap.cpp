#include "BinaryHeap.h"
#include <iostream>
using namespace std;

int main()
{
	BinaryHeap<char> PQ (50);

	for(char letter = 'A'; letter <= 'J'; letter++)
	{

		PQ.insert(letter);
	}
	PQ.deleteMin();
	cout << "Left Subtree of the root: " << endl;
	PQ.printLtSubtree();
	cout << endl;
	cout << "Height: " << PQ.Height() << endl;
	cout << "Max: " << PQ.findMax() << endl;
	
	
	return 0;
}
