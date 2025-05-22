#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <sstream>
#include <map>

using namespace std;

enum TransactionType { Add, Delete, ChangeOnHand, ChangePrice };

typedef char String[25];

struct BookRec {
	unsigned int isbn;
	String name;
	String author;
	int onhand;
	float price;
	String type;
};

struct TransactionRec {
	TransactionType ToDo;
	BookRec B;
};

void processTransaction(const string &master, const string &tFile, const string &newMaster, const string &errorFile) {
	ifstream masterIn(master, ios::binary);
	ifstream transactionIn(tFile, ios::binary);
	ofstream masterOut(newMaster, ios::binary);
	ofstream errorOut(errorFile);

	if (!masterIn || !transactionIn || !masterOut || !errorOut) {
		cerr << "Error opening one or more files" << endl;
		return;
	}

	map<unsigned int, BookRec> masterData;
	BookRec book;

	// Read the master file into the map
	while (masterIn.read(reinterpret_cast<char *>(&book), sizeof(BookRec))) {
		masterData[book.isbn] = book;
	}

	TransactionRec transaction;
	int transactionNumber = 0;

	while (transactionIn.read(reinterpret_cast<char *>(&transaction), sizeof(TransactionRec))) {
		transactionNumber++;
		unsigned int isbn = transaction.B.isbn;

		switch(transaction.ToDo) {
			case Add:
				if (masterData.find(isbn) == masterData.end()) {
					masterData[isbn] = transaction.B;
				} else {
					errorOut << "Error in transaction number " << transactionNumber << ": cannot add---duplicate key " << isbn << endl;
					cout << "Error in transaction number " << transactionNumber << ": cannot add---duplicate key " << isbn << endl;
				}
				break;

			case Delete:
				if (masterData.find(isbn) != masterData.end()) {
					masterData.erase(isbn);
				} else {
					errorOut << "Error in transaction number " << transactionNumber << ": cannot delete---no such key " << isbn << endl;
					cout << "Error in transaction number " << transactionNumber << ": cannot delete---no such key " << isbn << endl;
				}
				break;

			case ChangeOnHand:
				if (masterData.find(isbn) != masterData.end()) {
					masterData[isbn].onhand += transaction.B.onhand;
					if (masterData[isbn].onhand < 0) {
						errorOut << "Error in transaction number " << transactionNumber << ": count = " << masterData[isbn].onhand << " for key " << isbn << endl;
						cout << "Error in transaction number " << transactionNumber << ": count = " << masterData[isbn].onhand << " for key " << isbn << endl;
						masterData[isbn].onhand = 0;
					}
				} else {
					errorOut << "Error in transaction number " << transactionNumber << ": cannot change count---no such key " << isbn << endl;
					cout << "Error in transaction number " << transactionNumber << ": cannot change count---no such key " << isbn << endl;
				}
				break;

			case ChangePrice:
				if (masterData.find(isbn) != masterData.end()) {
					masterData[isbn].price = transaction.B.price;
				} else {
					errorOut << "Error in transaction number " << transactionNumber << ": cannot change price---no such key " << isbn << endl;
					cout << "Error in transaction number " << transactionNumber << ": cannot change price---no such key " << isbn << endl;
				}
				break;
		}
	}

	for (const auto &entry : masterData) {
		masterOut.write(reinterpret_cast<const char *>(&entry.second), sizeof(BookRec));
	}

	masterIn.close();
	transactionIn.close();
	masterOut.close();
	errorOut.close();

	ifstream displayMaster(newMaster, ios::binary);
	while (displayMaster.read(reinterpret_cast<char *>(&book), sizeof(BookRec))) {
		cout << book.isbn << " "
			 << book.name << " "
			 << book.author << " "
			 << book.onhand << " "
			 << fixed << setprecision(2) << book.price << " "
			 << book.type << endl;
	}
	displayMaster.close();
}

int main(int argc, char *argv[]) {
	if (argc != 4) {
		cerr << "Usage: " << argv[0] << " <master file> <transaction file> <new master file>" << endl;
		return 1;
	}

	string masterFile = argv[1];
	string transactionFile = argv[2];
	string newMasterFile = argv[3];
	string errorFile = "ERRORS";

	processTransaction(masterFile, transactionFile, newMasterFile, errorFile);
	return 0;
}

