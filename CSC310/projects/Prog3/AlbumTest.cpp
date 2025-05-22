#include "album.h"
#include <iostream>

using namespace std;

void testConstructors() {
    cout << "\n[Test] Constructors and Assignment:" << endl;

    Album a1("12345", "Taylor Swift", "1989");
    cout << "Created a1: " << a1 << endl;

    if (a1.getUPC() == "12345") {
        cout << "PASS: Constructor with parameters works." << endl;
    } else {
        cout << "FAIL: Constructor with parameters failed." << endl;
    }

    Album a2(a1);
    cout << "Copied a1 to a2: " << a2 << endl;

    if (a2.getUPC() == a1.getUPC()) {
        cout << "PASS: Copy constructor works." << endl;
    } else {
        cout << "FAIL: Copy constructor failed." << endl;
    }

    Album a3;
    a3 = a1;
    cout << "Assigned a1 to a3: " << a3 << endl;

    if (a3.getUPC() == a1.getUPC()) {
        cout << "PASS: Assignment operator works." << endl;
    } else {
        cout << "FAIL: Assignment operator failed." << endl;
    }
}

void testComparison() {
    cout << "\n[Test] Comparison Operator (<):" << endl;

    Album a1("12345", "Taylor Swift", "1989");
    Album a2("54321", "Adele", "25");

    if (a1 < a2) {
        cout << "PASS: a1 is less than a2 as expected." << endl;
    } else {
        cout << "FAIL: a1 is NOT less than a2." << endl;
    }
}

void testRecordSize() {
    cout << "\n[Test] Record Size Calculation:" << endl;

    Album a1("12345", "Taylor Swift", "1989");
    int size = a1.recordSize();
    cout << "Record size: " << size << endl;

    if (size > 0) {
        cout << "PASS: Record size seems reasonable." << endl;
    } else {
        cout << "FAIL: Record size is zero or negative." << endl;
    }
}

void testStreamOperators() {
    cout << "\n[Test] Stream Operators (>> and <<):" << endl;

    Album a;
    cout << "Please enter an album (UPC, Title, Artist), each on a new line:" << endl;
    cin >> a;

    cout << "You entered: " << a << endl;
    if (!a.getUPC().empty()) {
        cout << "PASS: Stream extraction seems to work." << endl;
    } else {
        cout << "FAIL: UPC is empty after input." << endl;
    }
}

int main() {
    cout << "===== Running Album Class Tests =====" << endl;

    testConstructors();
    testComparison();
    testRecordSize();

    cout << "\n===== All Basic Album Tests Completed =====" << endl;
    return 0;
}

