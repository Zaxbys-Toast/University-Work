#include "dlist.h"
#include <iostream>
using namespace std;

int main()
{
	DList<int> list;
	list.insertHead(1);
	list.insertHead(2);
	list.appendTail(3);
	list.deleteItem(2);
	list.print();
}
