// Imports
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	string flag;
	string filename;
	if(argc == 3) {
		flag = argv[1];
		filename = argv[2];
	}
	else {
		filename = argv[1];
	}
	int byteCount = 0;
	int wordCount = 0;
	int lineCount = 0;

	ifstream file;
	file.open(filename);
	
	// Navigate to the end of the file and get the byte at that point then go back to the beginning
	file.seekg(0, ios::end);
	byteCount = file.tellg();
	file.seekg(0, ios::beg);
	
	// Count the number of words in the file
	string word;
	
	while(file >> word) {
		++wordCount;
	}
	file.clear();
	file.seekg(0, ios::beg);

	// Count the number of lines in the file
	string line;
	while(getline(file, line)) {
		++lineCount;
	}
	file.close();
	if (flag == "-c" || flag == "-C") {
		cout << byteCount << "   " << filename << endl;
	}
	else if (flag == "-l" || flag == "-L") {
		cout << lineCount << "   " << filename << endl;
	}
	else if (flag == "-w" || flag == "-W") {
		cout << wordCount << "   " << filename << endl;
	}

	else {
		cout << lineCount << "\t" << wordCount << "\t" << byteCount << "    " << filename << endl;
	}
}
