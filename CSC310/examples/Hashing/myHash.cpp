// hash.cpp

#include <iomanip>
#include <cstring>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

typedef char String[20];
const int NumCities = 435;

struct Bucket
{
	int currSize;
	String key[3];
};

int hashMe (string key, int maxAddresses);
void numCollisions(int array[]);
void buildHashFile(Bucket mybucks[]);
void flushBuckets(Bucket mybucks[]);
void buildHashArray(fstream& infile, int array[], Bucket mybucks[]);
void printBuckets(Bucket mybucks[]);

int main()
{
	fstream infile("cities.dat", ios::in);
	int array[300] = {0};
        Bucket mybucks[300];

	flushBuckets(mybucks);
	buildHashArray(infile, array, mybucks);
	numCollisions(array);
	printBuckets(mybucks);
	buildHashFile(mybucks);

        return 0;
}

void flushBuckets(Bucket mybucks[])
{
	for (int i = 0;  i < 300;  i++)
	{
		mybucks[i].currSize = 0;
		for (int j = 0;  j < 3;  j++)
			strcpy (mybucks[i].key[j], "///");
	}
}

void buildHashArray(fstream& infile, int array[], Bucket mybucks[])
{
	string s;  int i;

	getline (infile, s);
        while (infile)
        {
                int slot = hashMe(s, 300);
		cout << "Key = " << s << " with a hash val of " << slot << endl;
                array[slot] += 1;
                mybucks[slot].currSize += 1;
		i = 0;
                while(strcmp(mybucks[slot].key[i],"///") != 0)
                {
			i++;
			if (i == 3)
			{
			i = 0;
			cout<<"Overflow at "<<slot<<" on hash of "<<s<< endl;
			slot++;
			if (slot > 299)
				slot = 0;
			}
		}
                strcpy(mybucks[slot].key[i], s.c_str());
                getline (infile, s);
        }
}

void buildHashFile(Bucket mybucks[])
{
	fstream outfile("hash.ind", ios::out | ios::binary);
	for (int i = 0;  i < 300;  i++)
		outfile.write((char *) &mybucks[i], sizeof(Bucket));
}

void numCollisions(int array[])
{
	int synonymns = 0;
	for (int j = 0;  j < 300;  j++)
	{
		if (array[j] > 1)
			synonymns += array[j] - 1;
		// cout << "j = " << j << " collisions = " << array[j] << endl;

	}
	cout << "Total Synonyms = " << synonymns << endl;

	cout.setf(ios::fixed, ios::floatfield);  cout.setf(ios::showpoint);
	for (int i=0;  i <= 7;  i++)
	{
		int count = 0;
		cout << "d(" << i << ") = ";
		for (int j = 0;  j < 300;  j++)
			if (array[j] == i)
				count++;
		cout << setprecision(2) << count << " " << float(count) / 300.0 << endl;
	}
}

int hashMe (string key, int maxAddresses)
{

	// Post:  Folds string key into an integer and returns it at a hashed address
	
	string s;  int sum = 0;
	for (int i = 0; i < key.length();  i++)
		if (isalpha(key[i]))
			s += toupper(key[i]);

	if (s.length() % 2 == 1)
		s += 'Z';
	for (int i = 0;  i < s.length();  i += 2)
	{
	    int temp = 0;
	    temp += int(s[i]) * 100;
	    temp += int(s[i+1]);
            sum += temp;
        }

	sum %= 36373;
	return sum % maxAddresses;
}

void printBuckets(Bucket mybucks[])
{
	// Pre:  Our array of 300 buckets size 3 has been initialized
	// Post:  Our array is printed out on 300 lines, with the 3 keys inside each bucket per line
	
	for (int i = 0;  i < 300;  i++)
	{
		cout << "i = " << i;
		cout << " size = " << mybucks[i].currSize << " "; 
		for (int j = 0;  j < 3;  j++)
			cout << mybucks[i].key[j] << " ";
		cout << endl;
	}
}
