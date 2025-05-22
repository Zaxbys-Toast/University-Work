#include <string>
#include <vector>
#include <stack>

using namespace std;

void Initialize(vector<int> v)
{
	cout<<"Enter 5 integers: ";
	for (int i = 0; i < 5; i++)
	{
		int temp;
		cin >> temp;
		v.push_back(temp);
	}
	cout << endl;
}

void Print(vector<int> v)
{
	for (int i = 0; i < 5; i ++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}

void Reverse (vector<int> v)
{
	reverse(v.begin(), v.end());
}


int main()
{
	stack<string> s1, s2;
	
	s1.push("Hi there");
	s1.push("Hello");
	s2.push("a");
	s2.push("b");
	if(s1 == s2)
		cout << "They are the same" << endl;
	else if ( s1 < s2)
		cout << "s1 is less than s2" << endl;
	else if (s1 > s2)
		cout << s1 is greater than s2 << endl;

	vector<int> v;
	Initialize(v);
	Reverse(v);
	Print(v);	
	sort(v.begin(), v.end());
	Print(v);
}
