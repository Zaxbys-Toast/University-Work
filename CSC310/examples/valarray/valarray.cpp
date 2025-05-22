
using namespace std;
#include <fstream>
#include <iostream>
#include <valarray>
#include <algorithm>

template<class T>
void printvalarray (const valarray<T>& va);

int main()
{
	valarray<int> va1(10);	      // valarray of ten ints with value 0
	valarray<int> va2(5, 10);     // valarray of ten ints with value 5

	int array[10] = {3, 6, 18, 3, 22, 1, 0};
	valarray<int> va3(array, sizeof(array)/sizeof(array[0]));
	valarray<int> va4(array+1, 3);

	va1[0] = 3 * va2[1] + va1[2];
	printvalarray(va1);

	va1 = va2 * va3;  // num elements in each operand should match
	va1 = 4 * va2;    // constants can be used

	va1 = va2;
	printvalarray(va1);
	valarray<bool> vab(10);
        vab = (va1 == va2);
	printvalarray(vab);

	va1 = -1;
	cout << va2.min() << " " << va2.max() << " " << va2.sum() << endl;

	printvalarray(va1);

	va1[slice(2, 4, 1)] = 2;
	printvalarray(va1);
        va1 = -1;
	va1[slice(2, 4, 2)] = 2;

	printvalarray(va1);
        return 0;
}

template<class T>
void printvalarray (const valarray<T>& va)
{
	for (int i = 0;  i < va.size();  i++)
		cout << va[i] << ' ';
	cout << endl;
}
