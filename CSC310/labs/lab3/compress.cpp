#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

string compress(const string &input) {
    istringstream iss(input);
    ostringstream oss;
    vector<string> tokens;
    string num;
    
    while (iss >> num) {
        tokens.push_back(num);
    }
    
    int n = tokens.size();
    for (int i = 0; i < n; ) {
        int count = 1;
        while (i + count < n && tokens[i] == tokens[i + count]) {
            count++;
        }
        if (count > 2) {
            oss << "ff " << tokens[i] << " " << hex << setw(2) << setfill('0') << count << " ";
        } else {
            for (int j = 0; j < count; j++) {
                oss << tokens[i] << " ";
            }
        }
        i += count;
    }
    
    string result = oss.str();
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    return result;
}

string uncompress(const string &input) {
    istringstream iss(input);
    ostringstream oss;
    string token;
    
    while (iss >> token) {
        if (token == "ff") {
            string value;
            string countStr;
            iss >> value >> countStr;
            int count = stoi(countStr, nullptr, 16);
            for (int i = 0; i < count; i++) {
                oss << value << " ";
            }
        } else {
            oss << token << " ";
        }
    }
    
    string result = oss.str();
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    return result;
}

int main() {
    string myInput = "93 93 93 93 92 91 91 94 94 94 94 94 95 95 95 73 73 73 73 73 73 73";
    string compressed = compress(myInput);
    cout << "Compressed: " << compressed << endl;
    
    string decompressed = uncompress(compressed);
    cout << "Decompressed: " << decompressed << endl;
    
    return 0;
}

