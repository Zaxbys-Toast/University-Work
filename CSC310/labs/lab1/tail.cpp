#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
	string filename = argv[2];
	string count = argv[1];
	count.erase(remove(count.begin(), count.end(), '-'), count.end());
	int n = stoi(count);
	// For testing
	string result;

	ifstream file;
	file.open(filename);

	// Navigate to the end of the file excluding the final new line
	file.seekg(-1, ios::end);

	// Dummy variable
	int lineCount = 0;
	int filePos = 0;
 	while(lineCount <= n) {
		char c = file.get();

		if ( c == '\n' ) {
			lineCount++;
		}
		file.seekg(-2, ios::cur);
		filePos = file.tellg();
	}
	
	file.seekg(filePos + 2, ios::beg);
	string line;
	while(getline(file, line)) {
		cout << line << endl;
	}
	
	
	return 0;
}
