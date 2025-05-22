#include "time.h"
using namespace std;

int main()
{
	Time myTime(9,30,0);
	myTime.Write();
	myTime.WriteAmPm();
	myTime.set(8,0,0);
	
	Time Schedule[10];
	for(int i = 0; i < 10; i ++)
	{
		Schedule[i].set(11,0,0);
		Schedule[i].WriteAmPm();
	}
	return 0;
}

