#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

int dateToCanonical(const string& dateStr) {
	
	map<string, string> monthMap = {
		{"January", "01"},
		{"February", "02"},
		{"March", "03"},
		{"April", "04"},
		{"May", "05"},
		{"June", "06"},
		{"July", "07"},
		{"August", "08"},
		{"September", "09"},
		{"October", "10"},
		{"November", "11"},
		{"December", "12"}

	};

	string month, day, year;
	stringstream ss(dateStr);
	ss >> month >> day;
	day = day.substr(0, day.size() - 1);
	ss >> year;

	string monthNumeric = monthMap[month];
	stringstream monthStream;
	int numMonth = stoi(monthNumeric);
	monthStream << setw(2) << setfill('0') << numMonth;
	monthNumeric = monthStream.str();
	int numDay = stoi(day);
	stringstream dayStream;
	dayStream << setw(2) << setfill('0') << numDay;
	string dayNumeric = dayStream.str();
	string fullString = monthNumeric + dayNumeric + year;
	int result = stoi(fullString);
	return result;
}	

int main(int argc, char *argv[]) {
	string dateStr = argv[1];
	cout << dateToCanonical(dateStr) << endl;
}
