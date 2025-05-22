#include "queue.h"
#include <vector>
#include "graph.h"
#include "HashTable.h"
#include "LinkedList.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "limits.h"
#include <algorithm>

using namespace std;

// Struct for data holding
struct Vert
{
	string name;
	string prev;
	bool marked;
	int distance;
};


// Function Declaration
void construct(const string& filename, Graph<string>& g, vector<string>& vertices);
void buildArray(vector<string> vertices, vector<Vert>& vArray);
void printVertices(vector<Vert> vArray);
int findIndex(string& start, vector<Vert>& vArray);
void djikstra(string& startVertice, const Graph<string>& g, vector<Vert>& vArray);
bool compareByDistance(const Vert& a, const Vert& b);
void printTable(vector<Vert> vArray);
// Main
int main(int argc, char* argv[])
{
	printf("\033c");
	Graph <string> myGraph(50);
	vector<string> myVertices;
	vector<Vert> vArray;
	construct(argv[1], myGraph, myVertices);
	buildArray(myVertices, vArray);
	printVertices(vArray);
	string startVertice;
	int startIndex = -1;
	cout << "What vertex would you like to start from?" << endl;
	cin >> startVertice;
	djikstra(startVertice, myGraph, vArray);
	printTable(vArray);
}
// Functions
void construct(const string& filename, Graph<string>& g, vector<string>& vertices)
{
	ifstream input(filename.c_str());
	string line;	
	
	while(getline(input, line))
	{
		istringstream iss(line);
		string source, destination;
		int weight;
		
		if(getline(iss, source, ';') && getline(iss, destination, ';') && (iss >> weight))
		{
			g.AddVertex(source);
			g.AddVertex(destination);	
			g.AddEdge(source, destination, weight);
			
			if (find(vertices.begin(), vertices.end(), source) == vertices.end()) 
			{
                		vertices.push_back(source);
            		}
			if (find(vertices.begin(), vertices.end(), destination) == vertices.end())
            		{
                		vertices.push_back(destination);
            		}	
		}
	}
	
}

void buildArray(vector<string> vertices, vector<Vert>& vArray)
{
	vArray.resize(vertices.size());
	for(int i = 0; i < vertices.size(); i++)
	{
		vArray[i].name = vertices[i];
		vArray[i].prev = "N/A";
		vArray[i].distance = INT_MAX;
		vArray[i].marked = false;		
	}	

}

void printVertices(vector<Vert> vArray)
{
	cout << "Built a Directed Graph for:";
	for (int i = 0; i < vArray.size(); i++)
	{
		if(i % 3 == 0)
			cout << endl;
		cout << vArray[i].name << "\t";
	}	
	cout << endl;
}

int findIndex(string& start, vector<Vert>& vArray)
{
	int index = -1;
	for(int i = 0; i < vArray.size(); i++)
	{
		if(vArray[i].name == start)
		{
			index = i;
			return index;
		}
	}
	return index;
}

void djikstra(string& startVertice, const Graph<string>& g, vector<Vert>& vArray)
{
	int startIndex = findIndex(startVertice, vArray);
	if(startIndex == -1)
	{
		cout << "No such vertice was found";
		return;
	}
	vArray[startIndex].distance = 0;
	int minIndex = startIndex;
	while(minIndex != -1)
	{
		Queue<string> adjvertQ;
		g.GetToVertices(vArray[minIndex].name, adjvertQ);
	 
		while (!adjvertQ.isEmpty())
    		{
			string adjVertex = adjvertQ.getFront();
        		adjvertQ.dequeue();

        		int adjIndex = findIndex(adjVertex, vArray);
	
        		if (adjIndex != -1 && !vArray[adjIndex].marked)
        		{
        	    		int weight = g.WeightIs(vArray[minIndex].name, adjVertex);
            			int distThroughMin = vArray[minIndex].distance + weight;

            			if (distThroughMin < vArray[adjIndex].distance)
            			{
                			vArray[adjIndex].distance = distThroughMin;
                			vArray[adjIndex].prev = vArray[minIndex].name;
            			}		
        		}
			
    		}
		vArray[minIndex].marked = true;
		g.GetToVertices(vArray[minIndex].name, adjvertQ);
		
		int temp = -1;
        	int distThroughMin = INT_MAX;

        	for (size_t i = 0; i < vArray.size(); ++i)
        	{
            		if (!vArray[i].marked && vArray[i].distance < distThroughMin)
            		{
                		distThroughMin = vArray[i].distance;
                		temp = i;
            		}
        	}

        	minIndex = temp;
	}
}	

bool compareByDistance(const Vert& a, const Vert& b) 
{
    return a.distance < b.distance;
}

void printTable(vector<Vert> vArray)
{
    	vector<Vert> sortedArray = vArray;
    	sort(sortedArray.begin(), sortedArray.end(), compareByDistance);
	cout << "-----------------------------------------" << endl;
    	cout << "Vertex\t\tDistance\tPrevious" << endl;
    	for (size_t i = 0; i < sortedArray.size(); ++i)
    	{
        	cout << sortedArray[i].name << "\t\t";
        	if (sortedArray[i].distance == INT_MAX)
        	{
            		cout << "INF\t\t";
        	}
        	else
        	{
            		cout << sortedArray[i].distance << "\t\t";
        	}
        	cout << sortedArray[i].prev << endl;
	}
	cout << "-----------------------------------------" << endl;
		
}

