#include <iostream>
#include <queue>

using namespace std;
void printQueue (priority_queue <string> pq);

int main()
{
	priority_queue<string> pq;
    	pq.push("a");
    	pq.push("c");
    	pq.push("b");
    	pq.push("e");
    	pq.push("d");
    	pq.push("g");
    	pq.push("f");
    	pq.push("i");
    	pq.push("h");
    	pq.push("j");
    	printQueue(pq);
 

   return 0;
}

void printQueue (priority_queue <string> pq)
{
    	priority_queue<string> temp = pq;
    	while(temp.size() != 0)
	{	
        	cout << temp.top() << " ";
        	temp.pop();
    	}
   	cout << endl;
}
