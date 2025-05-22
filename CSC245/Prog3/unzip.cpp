#include <iostream>
#include <map>
#include "huffman.h"
#include <fstream>
#include <cstdlib>
#include <cctype>

using namespace std;

void openFile(ifstream& input, int argc, char* argv[]);
void fillMap(map<string, char>& M, char* argv[], ifstream& input);

int main(int argc, char* argv[])
{
	ifstream input;
	map<string, char> M;
	openFile(input, argc, argv);
	fillMap(M, argv, input);
	cout << "File Inflated" << endl;	
}

void openFile(ifstream& input, int argc, char* argv[])
{
	if (argc == 1)
	{
		cout << "No File Entered" << endl;
		exit(0);
	}
	string filename = argv[1];
	input.open(filename.c_str());
	string zipped = filename.substr(filename.find("."), 3);
	if(zipped.compare("zip") == 0)
	{
		cout << "Not a .zip file. Cannot unzip" << endl;
		exit(0);
	}
}


void fillMap(map<string, char>& M, char* argv[], ifstream& input)
{
	string code;
	string message;
	int numch;
	input >> numch;
	int ascii;
	for(int i = 0; i < numch; i++)
	{
		input >> ascii >> code;
		M[code] = (char)ascii;
	}
	input >> message;
	ofstream output;
	string filename	= argv[1];
	filename = filename.substr(0, filename.find("."));
	output.open(filename.c_str());	
	string check;
	int pos = 0;
	int a = 1;
	for(int i = 0; i < message.length(); i ++)
	{
		check = message.substr(pos, a);
		if(M.find(check) != M.end())
		{
			output << M.at(check);
			pos = i + 1;
			a = 1;
		} 	
		else
			a++;
		
	}
	output.close();
}	

