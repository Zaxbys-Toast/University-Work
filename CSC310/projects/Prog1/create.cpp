#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <sstream>
using namespace std;

typedef char String[25];

struct BookRec {
	unsigned int isbn;
	String name;
	String author;
	int onhand;
	float price;
	String type;
};

void printBook(const BookRec& book) {
	cout << setfill('0') << setw(10) << book.isbn << " "
		 << setfill(' ') <<  setw(25) << right << string(book.name)
		 << setw(25) << string(book.author)
		 << setw(4) << right << book.onhand
		 << fixed << setprecision(2) << setw(10) << book.price
		 << setw(10) << string(book.type) << endl;
}

void trimAndCopy(char* dest, const string& src, size_t size) {
	strncpy(dest, src.c_str(), size - 1);
	dest[size - 1] = '\0'; // Ensure null-termination
}

int main() {
	ifstream infile("library.dat");
	ofstream outfile("library.out", ios::binary);

	if (!infile.is_open()) {
		cerr << "Error opening input text file." << endl;
		return 1;
	}

	if (!outfile.is_open()) {
		cerr << "Error opening output binary file." << endl;
		return 1;
	}

	BookRec book;
	unsigned int previousIsbn = 0;
	string line;

	while (getline(infile, line)) {
		stringstream ss(line);
		string isbnStr, name, author, onhandStr, priceStr, type;

		getline(ss, isbnStr, '|');
		getline(ss, name, '|');
		getline(ss, author, '|');
		getline(ss, onhandStr, '|');
		getline(ss, priceStr, '|');
		getline(ss, type, '|');

		book.isbn = stoul(isbnStr);
		trimAndCopy(book.name, name, sizeof(book.name));
		trimAndCopy(book.author, author, sizeof(book.author));
		book.onhand = stoi(onhandStr);
		book.price = stof(priceStr);
		trimAndCopy(book.type, type, sizeof(book.type));

		bool isValid = true;

		if (book.isbn < 1) {
			cerr << "Illegal Number: ISBN " << book.isbn << endl;
			isValid = false;
		}

		if (book.isbn <= previousIsbn) {
			cerr << "Number Out of Sequence: ISBN " << book.isbn << endl;
			printBook(book);
		}

		if (book.onhand < 0 || book.price < 0) {
			cerr << "Illegal OnHand or Price: ISBN " << book.isbn << endl;
			printBook(book);
			isValid = false;
		}

		if (isValid) {
			outfile.write(reinterpret_cast<const char*>(&book), sizeof(BookRec));
			previousIsbn = book.isbn;
		}
	}

	infile.close();
	outfile.close();

	// Read back from binary file and display records
	ifstream binaryInput("library.out", ios::binary);
	if (!binaryInput.is_open()) {
		cerr << "Error opening binary file for reading." << endl;
		return 1;
	}

	cout << "\nContents of library.out:\n";
	cout << "ISBN            Name                     Author                OnHand  Price  Type" << endl;
	cout << string(80, '-') << endl;

	while (binaryInput.read(reinterpret_cast<char*>(&book), sizeof(BookRec))) {
		printBook(book);
	}

	binaryInput.close();

	return 0;
}
