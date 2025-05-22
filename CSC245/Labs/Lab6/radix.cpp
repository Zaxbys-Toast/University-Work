#include <vector>
#include <queue>
#include <cstdlib>
#include <sstream>
#include <iostream>

using namespace std;

int maxElemLength(const vector<int>& k);
int GetDigit(int number, int k);
vector<queue<int> > ItemsToQueues(const vector<int>& L, int numVals);
vector<int> QueuesToArray(vector<queue<int> >& QA, int numVals);
void RadixSort(vector<int>& L, int numDigits);
void PrintVector(const vector<int>& L);


int main()
{
	vector<int> L;
	L.push_back(380);
	L.push_back(95);
	L.push_back(345);
	L.push_back(382);
	L.push_back(260);
	L.push_back(100);
	L.push_back(492);
	RadixSort(L, maxElemLength(L));
	PrintVector(L);
}

int maxElemLength(const vector<int>& k)
{
	int vLen = k.size();
	int max = 0;
	for(int i = 0; i < vLen; i++)
	{
		if(k[i] > max)
			max = k[i];
	}
	int len = 1;
	while(max >= 10)
	{
		max /= 10;
		len++;
	}
	return len;
}

int GetDigit(int number, int k)
{
	stringstream ss;
	ss << number;
	string num = ss.str();
	
	if (k >= 0 && k < num.length()) 
	{
        	return num[k] - '0';
    	} 
	else 	
	{
        	return 0;
    	}
}


vector<queue<int> > ItemsToQueues(const vector<int>& L, int k)
{
	vector<queue<int> > queueArray(10);
	for(int i = 0; i < L.size(); i++)
	{
		int temp = L[i];
		queueArray[(GetDigit(L[i], k))].push(temp);
	}
	return queueArray;
}


vector<int> QueuesToArray(vector<queue<int> >& QA, int numVals)
{
	int index = 0;
	vector<int> array;
	for(int i = 0; i < 10; i++)
	{
		while(!QA[i].empty())
		{
			array.push_back(QA[i].front());
			QA[i].pop();
		}
	}
	return array;

}


void RadixSort(vector<int>& L, int numDigits)
{
	vector<queue<int> > tempQueue(10);

	for(int i = 0; i < numDigits; i++)
	{
		tempQueue = ItemsToQueues(L, i);		
		L = QueuesToArray(tempQueue, maxElemLength(L));		
	}

}


void PrintVector(const vector<int>& L)
{
	for(int i = 0; i < L.size(); i++)
	{
		cout << L[i] << " ";
	}
	cout << endl;
}
