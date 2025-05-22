#include "dlist.h"
#include <iostream>

using namespace std;
//Set up all of the methods that are going to be used
void PrintMenu();
 
void FindandMove(DList<int>& list);

void AccessItem(DList<int>& list);

void TailInsert(DList<int>& list);

void HeadInsert(DList<int>& list);

void PrintList(const DList<int>& list);

void PrintLength(const DList<int>& list);

void Delete(DList<int>& list);
//Main----------------------------------------------------------------------------------------------------------
int main()
{
	DList<int> list;
	char sel;
	while(toupper(sel) != 'Q')
	{
		PrintMenu();
		cin >> sel;
		switch(toupper(sel))
		{
			case 'H' : HeadInsert(list); break;
			case 'T' : TailInsert(list); break;
			case 'A' : AccessItem(list); break;
			case 'D' : Delete(list); break;
			case 'P' : PrintList(list); break;
			case 'L' : PrintLength(list); break;
			case 'Q' : cout << "\tExiting Program...\n"; break;
			default : cout << "\tError. Try Again." << endl;
		}
	}
}
//Methods--------------------------------------------------------------------------------------------------------
void PrintMenu()
{
	cout << "\n|-----------------------------|" << endl;
	cout << "|------------Menu-------------|" << endl;
	cout << "|-----------------------------|" << endl;
	cout << "|                             |" << endl;
	cout << "| H: Insert item at front     |" << endl;
	cout << "| T: Insert item at back      |" << endl;
	cout << "| A: Access an item in list   |" << endl;
	cout << "| D: Delete an item in list   |" << endl;
	cout << "| P: Print the list           |" << endl;
	cout << "| L: Print the list's length  |" << endl;
	cout << "| Q: Quit the program         |" << endl;
	cout << "|                             |" << endl;
	cout << "|-----------------------------|" << endl;
	cout << "|                             |" << endl;
	cout << "|  Please enter your choice:  |\n" << endl;
	
}

void HeadInsert (DList<int>& list)
{
	int num;
	cout << "What number would you like to insert?" << endl;
	cin >> num;
	if(! list.inList(num)) //if the num isn't in the list use insertHead
	{
		list.insertHead(num);	
		cout << "Done" << endl;
	}
	else //if it is let the user know
		cout<< "Duplicate number" << endl;
}

void TailInsert (DList<int>& list)
{
	int num;
	cout<<"What number would you like to insert?" << endl;
	cin >> num;
	if(! list.inList(num)) //if the num isn't in the list already use appendTail
	{
		list.appendTail(num);
		cout<<"Done"<<endl;	
	}
	else	//if it is in the list let the user know and don't add it
	{
		cout<<"Duplicate number"<<endl;
	}
}

void AccessItem (DList<int>& list)
{
	FindandMove(list);
}

void FindandMove (DList<int>& list)
{
	int num;
	cout << "What number would you like to access?" << endl;
	cin >> num;
	if (list.inList(num))
	{
		NodeType<int>* temp = new NodeType<int>; //make a new temp node to hold the value that is getting moved
		temp -> info = num;
		list.deleteItem(num); //delete the node that is being moved 
		list.insertHead(temp -> info);	//create a new head using the temp value
		cout << "Item found and succesfully moved!" << endl; 
		delete temp;
		temp = NULL;
	}
	else
	{
		cout << "Item not found" << endl;
	}
}

void Delete (DList<int>& list)
{
	int num;
	cout << "What number would you like to delete?" << endl;
	cin >> num;
	if (list.inList(num)) //if the number is in the list delete it using the deleteItem method
	{
		list.deleteItem(num);
	}
	else //if the number isn't in the list let the user know 
	{
		cout << "This number is not in the list" << endl;
	}
}

void PrintList (const DList<int>& list)
{
	if (list.isEmpty()) //if the list is empty let the user know
	{
		cout << "The list is empty" << endl;
	}
	else //run the print method
	{
		cout << "Printing list ..." << endl;
		list.print();
	}
}

void PrintLength(const DList<int>& list) //Print out the private length variable using the lengthIs method
{
	cout << "The length of the list is " << list.lengthIs() << endl;
}



