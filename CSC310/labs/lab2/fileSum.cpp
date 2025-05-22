#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

int sumIntegers(istream &input) {
    int sum = 0, num;
    char ch;

    while (input >> num) {
        sum += num;
        input >> ws; // Consume any whitespace
        if (input.peek() == ',') {
            input.get(); // Consume the comma
            input >> ws; // Consume any whitespace after the comma
        } else if (input.peek() != EOF && !isdigit(input.peek()) && !isspace(input.peek())) {
            return -1; // Invalid format (e.g., unexpected character)
        }
    }
    
    if (input.fail() && !input.eof()) {
        return -1; // Ensure the failure wasn't due to bad format
    }

    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file) {
        cerr << "Error: Cannot open file." << endl;
        return 1;
    }

    int result = sumIntegers(file);
    cout << "Sum: " << result << endl;

    return 0;
}

