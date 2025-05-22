#include "huffman.h"
#include <iostream>
using namespace std;

HuffmanTree:: HuffmanTree()
	: numChars(0), built(false) {}

void HuffmanTree:: insert(char ch, int weight) {
    HNode newNode = {ch, weight, -1, -1}; 
    built = false;
    nodes.push_back(newNode);
    numChars++;

}

bool HuffmanTree:: inTree(char ch) {
	return lookUp(ch) != -1;
}

int HuffmanTree:: GetFrequency(char ch) {
	return GetFrequency(ch);
}

int HuffmanTree:: GetFrequency(int i) {
	char ch;
	int Letters[256];
	for (ch = char(0); ch <= char(126); ch++)
	{
		Letters[ch] = 0;
	}	
	cin.get(ch);
	while(cin)
	{
		Letters[ch] += 1;
		cin.get(ch);
	}				
	return Letters[ch];
}

int HuffmanTree:: lookUp(char ch) {
	
	for(int i = 0; i < numChars; i++)
	{
		if (nodes[i].ch == ch)
			return i;
	}
	return -1;
}

string HuffmanTree:: GetCode(char ch) {

	return GetCode(lookUp(ch));
}


string HuffmanTree::GetCode(int i) {
    	if (nodes[i].parent == -1)
        	return "";
	else
		return (GetCode(nodes[i].parent) + (char)(nodes[i].childType + '0'));
    
}

void HuffmanTree:: PrintTable() {

	int num = 1;
	cout << "\t++++Encoding Table++++\n" << endl;
	cout << "INDEX\tCHAR\tWEIGHT\tPARENT\tCHILD TYPE" << endl;
	for(int i = 0; i < numChars; i++)
	{
		if(nodes[i].ch != ' ' && nodes[i].ch != '\0')
		{
			cout << i << "\t" << nodes[i].ch << "\t" << nodes[i].parent << "\t" << nodes[i].childType << endl;
		} 
		else if (nodes[i].ch == '\0' && nodes[i].childType != -1)
		{
			cout << i << "\t" << 'T' << num << "\t" << nodes[i].weight << "\t" << nodes[i].parent << "\t" << nodes[i].childType << endl;
			num++;
		}
		else
		{
			cout << i <<"\t" << 'T' <<num<< "\t" << nodes[i].weight << "\t" << "0" << "\t" << "-1" << endl;	
			num++;
		}
	}
}

int HuffmanTree:: numNodes() {
	return numChars;
}


void HuffmanTree::build()
{
	int max = (numChars * 2) - 1;
	while(max > numChars)
	{
		int min1 = -1;
		int min2 = -1;
		for(int i = 0; i < numChars; i++)
		{
			if(nodes[i].parent == -1)
			{
				if(min1 == -1 || nodes[i].weight < nodes[min1].weight)
				{	
					min2 = min1;
					min1 = i;
				}
				else if(min2 == -1|| nodes[i].weight < nodes[min2].weight)
				{
					min2 = i;
				}
			}
		}

	
		HNode temp = {'\0', nodes[min1].weight + nodes[min2].weight, -1, -1};
		nodes.push_back(temp);

		nodes[min1].parent = nodes.size() - 1;
		nodes[min1].childType = 0;
		nodes[min2].parent = nodes.size() - 1;
		nodes[min2].childType = 1;

		numChars++;
	}
	
	nodes[nodes.size() - 1].parent = -1;
	built = true;
}
