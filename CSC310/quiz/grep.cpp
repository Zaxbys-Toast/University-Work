#include <fstream>
#include <iostream>
#include <cstring>
#include <sys/stat.h>
#include <ios>
using namespace std;

bool isDirectory(const char *path);

int main(int argc, char * argv[]) {
	if (argc > 4 || argc < 3) {
		cout << "Wrong number of arguments" << endl;
		return 1;
	}
	string tempFlag = argv[1];
	if (argc > 3 && tempFlag != "-c") {
		cout << "Unknown flag" << endl;
		return 1;
	}
	
	string x;
	ifstream file;
	if (argc > 3) {
		file.open(argv[3], ios::in);
		x = argv[2];
	} else {
		file.open(argv[2], ios::in);
		x = argv[1];
	}

	if (!file) {
		cout << "Could not open file" << endl;
		return 1;
	}

	if(isDirectory(argv[3]) || isDirectory(argv[2])) {
		cout << "File is a directory" << endl;
		return 1;
	}

	
	string temp = "";
	string line = "";
	int location;
	
	location = file.tellg();
	getline(file, line);
	file.seekg(location, ios::beg);

	if (argc < 4) {
		while (file) {
			if (file.peek() == '\n') {
				file.seekg(1, ios::cur);
				location = file.tellg();
				getline(file, line);
				file.seekg(location, ios::beg);
			}
			file >> temp;	
			if (temp == x){
				getline(file, temp);
				cout << line << endl;
			}		
		}	
	} else {
		int count = 0;
		while (file) {
			file >> temp;
			if(temp == x) {
				getline(file, temp);
				count++;
			}
			
		}
		cout << count << endl;
	}
	
}

bool isDirectory(const char *path) {
    struct stat s;
    if (stat(path, &s) == 0) {
        return S_ISDIR(s.st_mode);
    }
    return false;
}

