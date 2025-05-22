using namespace std;
#include <iostream>

bool equalValue(double *p1, double *p2)
{
	if (*p1 == *p2)
		return true;
	else 
		return false;	
}

bool equalAddress(double *p1, double *p2)
{
	if (ptr1 == ptr2)
		return true;
	else
		return false;
}

int main()
{
	double *ptr1, *ptr2;
	double dbl1 = 1;
	double dbl2 = 1;
	cout << equalValue(*ptr1, *ptr2) << endl;
	cout << eqaulAddress(*ptr1, *ptr2) << endl;
}
