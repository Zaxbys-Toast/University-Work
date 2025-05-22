#include <iostream>
using namespace std;
class Base
{
	public :
	virtual void iam();
};

void Base::iam()
{
	cout << "base" << endl;
}


class D1 : public Base {
public:
	void iam() override {
		cout << "D1" << endl;
	}

	void iam2() {
		Base::iam();
	}
};

class D2 : public Base {
public:
	void iam() override {
		cout << "D2" << endl;
	}

	void iam2() {
		Base::iam();
	}
};


int main() {
	D1 d1;
	D2 d2;

	d1.iam();
	d1.iam2();

	d2.iam();
	d2.iam2();

	Base* ptr1 = &d1;
	Base* ptr2 = &d2;

	ptr1->iam();
	ptr2->iam();

	return 0;
}
