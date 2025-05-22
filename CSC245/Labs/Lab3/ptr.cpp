using namespace std;
#include <iostream>
#include <string.h>
struct RecType
{
	int age;
	float weight;
	char gender;
};

int main()
{
	int num = 5;
	int *intPtr = NULL;
//	intPtr = &num;
	*intPtr *= 10;
	cout << *intPtr << endl;
	RecType *recPtr = new RecType;
	recPtr -> age = 25;
	recPtr -> weight = 190;
	recPtr -> gender = 'M';
	recPtr -> age += 5;
	cout << recPtr -> age << " " << recPtr -> weight << " " << recPtr -> gender << endl;
	delete recPtr;
	recPtr = NULL;
//***********************************************************************************************//
	char *strPtr = new char[50];
	strcpy(strPtr, "Operating Systems");
	cout << strPtr << endl;
	int lowerCount = 0;
	for (int i = 0; i < strlen(strPtr); i++)
	{
		if(islower(*(strPtr + i)))
		{
			lowerCount++;
		}
	}
	cout << lowerCount << endl;
	strPtr += 10;
	cout << strPtr << endl;
	strPtr -= 10;
	delete strPtr;
	return 0;
}
