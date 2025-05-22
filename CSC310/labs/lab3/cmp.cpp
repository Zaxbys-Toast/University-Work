#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <sys/stat.h>

using namespace std;

bool isDirectory(const char *path);

int main(int argc, char *argv[]) {
    bool showChars = false;
    int ignoreBytes = 0;
    int fileIndex = 1;

    if (argc < 3 || argc > 5) {
        cerr << "Usage: cmp [-c] [-i N] file1 file2" << endl;
        return 1;
    }

    // Check flags
    while (fileIndex < argc && argv[fileIndex][0] == '-') {
        if (strcmp(argv[fileIndex], "-c") == 0) {
            showChars = true;
        } else if (strcmp(argv[fileIndex], "-i") == 0) {
            if (++fileIndex >= argc) {
                cerr << "Usage: cmp [-c] [-i N] file1 file2" << endl;
                return 1;
            }
            ignoreBytes = atoi(argv[fileIndex]);
            if (ignoreBytes < 0) {
                cerr << "Invalid byte count for -i option." << endl;
                return 1;
            }
        } else {
            cerr << "Invalid option: " << argv[fileIndex] << endl;
            return 1;
        }
        fileIndex++;
    }

    if (fileIndex + 1 >= argc) {
        cerr << "Usage: cmp [-c] [-i N] file1 file2" << endl;
        return 1;
    }

    const char *file1 = argv[fileIndex];
    const char *file2 = argv[fileIndex + 1];

    ifstream f1(file1, ios::binary);
    ifstream f2(file2, ios::binary);

    if (!f1) {
        cerr << "cmp: cannot open " << file1 << endl;
        return 1;
    }
    if (!f2) {
        cerr << "cmp: cannot open " << file2 << endl;
        return 1;
    }

    char ch1, ch2;
    int byteNum = 1, lineNum = 1;

    while (ignoreBytes-- > 0 && f1.get(ch1) && f2.get(ch2)) {
        byteNum++;
        if (ch1 == '\n') lineNum++;
    }

    while (f1.get(ch1) && f2.get(ch2)) {
        if (ch1 != ch2) {
            if (showChars) {
                cout << file1 << " " << file2 << " differ: char " << byteNum
                     << ", line " << lineNum << " is " << oct << (unsigned int)(unsigned char)ch1
                     << " " << (isprint(ch1) ? ch1 : '?') << " " << (unsigned int)(unsigned char)ch2
                     << " " << (isprint(ch2) ? ch2 : '?') << endl;
            } else {
                cout << file1 << " " << file2 << " differ: byte "
                     << byteNum << ", line " << lineNum << endl;
            }
            return 0;
        }
        byteNum++;
        if (ch1 == '\n') lineNum++;
    }

    if (f1.eof() && !f2.eof()) {
        cout << "cmp: EOF on " << file1 << endl;
    } else if (!f1.eof() && f2.eof()) {
        cout << "cmp: EOF on " << file2 << endl;
    }

    return 0;
}

bool isDirectory(const char *path) {
    struct stat s;
    if (stat(path, &s) == 0) {
        return S_ISDIR(s.st_mode);
    }
    return false;
}

