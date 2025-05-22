#include <vector>
#include <queue>
#include <cstdlib>
#include <sstream>
#include <iostream>

using namespace std;

int maxElemLength(const vector<string>& k);
int GetDigit(const string& s, int k);
vector<queue<string> > ItemsToQueues(const vector<string>& s, int numVals);
vector<string> QueuesToArray(vector<queue<string> >& QA, int numVals);
void RadixSort(vector<string>& L, int numDigits);
void PrintVector(const vector<string>& L);


int main()
{
	vector<string> a(10);
	a.push_back("zebra");
	a.push_back("apple");
	a.push_back("orange");
	a.push_back("can");
	a.push_back("candy");
	a.push_back("a");
	a.push_back("top");
	a.push_back("pumpkin");
	a.push_back("today");
	a.push_back("parade");
	int l = maxElemLength(a);	
	RadixSort(a, l);
}

int maxElemLength(const vector<string>& k)
{
    	int maxLen = 0;
    	for (int i = 0; i < k.size(); i++)
    	{	
		const string& s = k[i];
        	if (s.length() > maxLen)
        	{
        		maxLen = s.length();
        	}
    	}	
	return maxLen;
}

int GetDigit(const string& s, int k)
{
	if (k >= 0 && k < s.length()) 
	{
        	return s[k];
    	} 
	else 	
	{
        	return ' ';
    	}
}


vector<queue<string> > ItemsToQueues(const vector<string>& s, int k)
{
	vector<queue<string> > queueArray(128);
	for(int i = 0; i < s.size(); i++)
	{
		const string& temp = s[i];
		queueArray[(GetDigit(s[i], k))].push(temp);
	}
	return queueArray;
}


vector<string> QueuesToArray(vector<queue<string> >& QA, int numVals)
{
	vector<string> array;
	for(int i = 0; i < QA.size(); i++)
	{
		queue<string>& q = QA[i];
		while(!q.empty())
		{
			array.push_back(q.front());
			q.pop();
		}
	}
	return array;

}


void RadixSort(vector<string>& L, int numDigits)
{
	vector<queue<string> > tempQueue(128);

	for(int i = 0; i < numDigits; i++)
	{
		tempQueue = ItemsToQueues(L, i);		
		L = QueuesToArray(tempQueue, maxElemLength(L));		
	}

}


void PrintVector(const vector<string>& L)
{
	for(int i = 0; i < L.size(); i++)
	{
		cout << L[i] << " ";
	}
	cout << endl;
}
