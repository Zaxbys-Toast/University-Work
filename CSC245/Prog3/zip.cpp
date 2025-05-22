#include <iostream>
#include <fstream>
#include <cstdlib>
#include "huffman.h"
#include <stdio.h>
using namespace std;
void Insert(const int Letters[], HuffmanTree& h, int header);
void Frequency(ifstream& input, int Letters[], int argc, char *argv[], int source, string& s);
void Compress(ifstream& input, int argc, char *argv[], int Letters[256], HuffmanTree& h, int source, string& s, int header);

int main(int argc, char* argv[])
{
	string s;
	int header = 0;
	int source = 0;
	int Letters[256];
	string input;
	if(argc > 1)
		input = argv[1];
	HuffmanTree h;
	ifstream infile;
	if(argc <= 1)
	{
		cout << "No file entered!" << endl;
		exit(1);
	}
	
	else if(input.compare("--help") == 0)
	{
		infile.open("help");
		string in;
		while(!infile.eof())
		{
			getline(infile, in);
			cout << in << endl;
		}
		exit(1);
	}
	else
	{
		if(input.compare("--t") == 0)
			infile.open(argv[2]);
		else
			infile.open(argv[1]);
		if(infile.fail())
		{
			cout << "Failed to open file" << endl;
			exit(1);
		}
		Frequency(infile, Letters, argc, argv, source, s);
                Insert(Letters, h, header);
                h.build();
                Compress(infile, argc, argv, Letters, h, source, s, header);
		infile.close();
	}

	return 0;
}

void Frequency(ifstream& input, int Letters[], int argc, char *argv[], int source, string& s)
{
	string filename;
	char ch;
	if (argc > 2)
		filename = argv[2];
	else
		filename = argv[1];
	for (int i = 0; i < 256; i++)
	{
                Letters[i] = 0;
	}
	input.get(ch);
	while (input)
	{
		Letters[ch] += 1;
		s += ch;
		input.get(ch);
	}
}


void Insert(const int Letters[], HuffmanTree& h, int header)
{
    // Use unique ASCII values for special characters
   	const char newlineChar = '\n';
       	const char spaceChar = ' ';
   
           // Insert characters into the Huffman tree
       	for (char ch = char(0); ch <= char(126); ch++)
        {
                if (Letters[ch] != 0)
                {
                       char insertChar = ch;
                       if (ch == newlineChar)
                       {
                               insertChar = '^'; // Use a unique ASCII value for newline
                       }
                       else if (ch == spaceChar)
                       {
	                       insertChar = '$'; // Use a unique ASCII value for space
                       }
                       h.insert(insertChar, Letters[ch]);
	               header++;
	       }
	}
}

void Compress(ifstream& input, int argc, char *argv[], int Letters[256], HuffmanTree& h, int source, string& s, int header)
{
	int compressed = 0;
	float ratio;
	string in = argv[1];
	string filename;
	if(argc > 2)
		filename = argv[2];
	else
		filename = argv[1];
	if (!input.is_open())
	{
		cout << "The file is not open!" << endl;
		exit(1);
	}
	else
	{
		header = h.numNodes() - (h.numNodes() / 2);
		filename += ".zip";
		ofstream output;
		output.open(filename.c_str());
		output << header << endl;
		for(char ch = ' '; ch <= '~'; ch++)
		{
			if(Letters[ch] != 0)
			{
				if(ch != '\n' && ch != ' ')
				{
					output << (int)ch << " " << h.GetCode(ch) << endl;
					source++;
				}
				else if(ch == '\n')
				{
					output << (int)ch << " " << h.GetCode('^') << endl;
					source++;
				}
				else if(ch == ' ')
				{
					output << (int)ch << " " << h.GetCode('$') << endl;
					source++;
				}
			}
		}	
		if ( in.compare("--t") == 0 && argc > 2)
		{
			h.PrintTable();
		}	
		char code;
		for(int i = 0; i < s.length(); i++)
		{
			code = s[i];
			output << h.GetCode(code);
			compressed++; 
		}
		output << endl;
		output.close();
		ratio = (1 -(float)(compressed/((float)source*8))) * 100;
		cout << "File successfully compressed to " << compressed << " bits. " << ratio << "% less" << endl;
	}
		
}
