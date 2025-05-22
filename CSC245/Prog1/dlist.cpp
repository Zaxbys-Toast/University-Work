#include <cstddef> 
#include <iostream>

using namespace std;

template<class ItemType>
struct NodeType
{
	ItemType info;
	NodeType<ItemType>*	next;
	NodeType<ItemType>*	back;
};

template <class ItemType>		
DList<ItemType>::DList()		// Class constructor
{
    length = 0;
    head = NULL;
}

template <class ItemType>
DList<ItemType>::~DList   ()		
{
	// Post: List is empty; All items have been deallocated.
	makeEmpty();
}

template <class ItemType>
void DList<ItemType>::makeEmpty()
{
    // Post: List is empty; all items have been deallocated.
	while (length < 0) //while the length isnt 0 delete the last item
	{
		deleteLocation(last());	
	}
}

template <class ItemType>
void DList<ItemType>::deleteItem (ItemType item)	
{
	//  Pre :  item to be deleted is passed in via parameter 
        // Post :  item is deleted if it exists in list 
	if(inList(item))
	{
		deleteLocation(location(item));	
	}
}

template <class ItemType>
bool DList<ItemType>::inList (ItemType item) const
{
	//  Pre :  item to be located is passed in via parameter 
        // Post :  function returns bool value if item is found 
	NodeType<ItemType>* temp = new NodeType<ItemType>;
	temp = head;
	while(temp != NULL)
	{
		if(temp->info == item)
			return true;
		temp=temp->next;
	}	
	return false;

}

template <class ItemType>
bool DList<ItemType>::isEmpty() const		
{
	// Post : function returns true if list is empty, false otherwise
	return (head == NULL);
	
}

template <class ItemType>
void DList<ItemType>::print() const	
{
	int pos = 1; //used to print the location in the list
	NodeType<ItemType>* node = new NodeType<ItemType>;
	node = head;

	while (node != NULL)
	{
		cout << pos << ":	 " <<  node->info << endl;
		pos++;
		node = node -> next; //traverse the list
	}
	node = NULL;
	delete node;
}
	
template <class ItemType>
void DList<ItemType>::insertHead(ItemType item)	
{
	//  Pre : item to be inserted is passed in via parameter
        // Post : item is inserted at head of list;  Former first node is 
        //        linked back to this new one via double link;
        //        Length incremented;  Special case handled if list is empty 
	NodeType<ItemType>* newNode = new NodeType<ItemType>;
	newNode->info = item;
	newNode->back = NULL;

        if(head == NULL)
	{
		newNode -> next = NULL;
	}
	else
	{
 		head -> back = newNode; //link the 1st item to the 2nd
		newNode -> next = head; //link the 2nd item to the 1st
	}
	head = newNode; //make newNode the new head
	length++;
}

template <class ItemType>
void DList<ItemType>::appendTail(ItemType item)
{
	//  Pre :  item to be inserted is passed in via parameter
        // Post :  item is added to tail of list; Former last node
        //         is linked to this new one via double link 
	NodeType <int>* newNode = new NodeType<int>;
	newNode -> info = item;
	newNode -> next = NULL;
	if (head == NULL)
	{
		newNode -> back = NULL; //make the newNode the new head
		head = newNode;
	}
	else
	{
		newNode -> back = last(); //link the new last item to the old last item
		newNode -> back -> next = newNode; //link the old last item to the new last item
	}
	length++;
}

template <class ItemType>
int DList<ItemType>::lengthIs() const	
{
	// Post : Function returns current length of list  
	return length;
}

template <class ItemType>
NodeType<ItemType>* DList<ItemType>::location(ItemType item) const	
{
	//  Pre : item to be located is passed in via parameter 
        // Post : function returns address of item being searched for --
        //        if not found, NULL is returned  
	if(inList(item))
	{
		NodeType<ItemType>* temp = new NodeType<ItemType>; //create a temp to traverse through the list 
		temp = head;
		while(temp -> info != item) //while the temp value is not the value being searched for traverse the list
		{
			temp = temp -> next;
		}	
		return temp; //return the temp location
	}	
	else
		return NULL;
}

template <class ItemType>
NodeType<ItemType>* DList<ItemType>::last() const	
{
	// Post : Function returns location of current last item in list
	NodeType<ItemType>* temp = head;
	if(isEmpty()) //if there is nothing in the list there is no last
	{
		return NULL;
	}
	else
	{
		while (temp -> next != NULL) // while the temp node next is not null it is not the last item in the list
		{
			temp = temp -> next; // set temp to the next node
		}	
		return temp; //return the last node
	}
}

template <class ItemType>
void DList<ItemType>::deleteLocation (NodeType<ItemType>* delPtr)	
{

	//  Pre : Item to be deleted exits in list and its location
        //        is passed in via parameter
                   
	// Post : Location passed in is removed from list;  Length
        //        is decremented, and location is deallocated 

        // Special Cases Handled for Deleting Only One Item in List,
        // The Head Item of List, and the Tail Item of List
	if(length == 1)
	{
		delete delPtr; //get rid of delPtr
		delPtr = NULL;
		head = NULL;	//Set the head to null
	}
	else if(head == delPtr) 
	{
		head = head -> next; //Make the new head the second item in the list
		head -> back = NULL; //Delete the old head
	}
	else if(last()==delPtr)
	{
		delPtr -> back -> next = NULL; //Set the second to last items next to null 
	}
	else
	{
		delPtr -> next -> back = delPtr -> back; //link the next item to the last item
		delPtr -> back -> next = delPtr -> next; //link the last item to the next item
	}
	length--;
	delPtr=NULL;
	delete delPtr;
}
