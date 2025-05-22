#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "stack.h"
using namespace std;

void run(Stack<int>& s, string in);
bool check(string s);
void print(Stack<int> s);
void nPrint(Stack<int>& s);
void fPrint(Stack<int>& s);
void duplicate(Stack<int>& s);
void reverse(Stack<int>& s);
void clearStack(Stack<int>& s);
void addition(Stack<int>& s);
void subtraction(Stack<int>& s);
void multiplication(Stack<int>& s);
void division(Stack<int>& s);
void mod(Stack<int>& s);

int main()
{
	Stack<int> s(10);
	string input;
	cin >> input;
	while(cin)
	{
		try{
			if(check(input))
			{
				s.push(atoi(input.c_str()));	
			}
			else
			{
				run(s, input);
			}	
			
		}
		catch (DataError exc)
		{
			cout << "Exception -- You have entered an invalid expression. Please re-enter." << endl;
		}
		cin >> input;
	}
} 

void run (Stack<int>& s, string in)
{
	for(int i = 0; i < in.size(); i++)
	{
		if(isdigit(in[i]))
		{
			string input;
			while(isdigit(in[i]))
			{
				input += in[i];
				i++;	
			}	
			s.push(atoi(input.c_str()));
				
		}
		else if(in[i] == '_')
		{
			string input;
			input = '-';
			i++;
			while(isdigit(in[i]))
			{
				input += in[i];	
				i++;
			}		
			i--;
			s.push(atoi(input.c_str()));	
		}	
		else if (in[i] == '+')
		{
			addition(s);	
		}
		else if(in[i] == '-')
		{	
			subtraction(s);
		}
		else if(in[i] == '*')
                {
			multiplication(s);
                }
		else if(in[i] == '/')
                {
			division(s);
                }
		else if(in[i] == '%')
                {
			mod(s);
                }
		else if(in[i] == 'p')
                {
			print(s);
                }
		else if(in[i] == 'n')
                {
			nPrint(s);
                }
		else if(in[i] == 'f')
                {
			fPrint(s);
                }
		else if(in[i] == 'd')
                {
			duplicate(s);
                }
		else if(in[i] == 'c')
                {
			clearStack(s);
                }
		else if(in[i] == 'r')
		{
			reverse(s);
		}
		else	
		{			
			throw DataError();
		}	
	}
}

bool check(string s)
{
	for(int i = 0; i < s.size(); i++)
	{
		if(!isdigit(s[i]))
			return false;
	}
	return true;
}


void print(Stack<int> s)
{
	try{
		cout << s.top() << endl;
	}
	catch(Underflow exc){
		cout << "Underflow Error" << endl;
	}
}


void nPrint(Stack<int>& s)
{
	//Pop top of stack and print it
	//Need to catch underflow
	try{
		cout << s.top() << endl;
		s.pop();
	} catch(Underflow exc) {
		cout << "Underflow Error" << endl;
	}
	
}

void fPrint(Stack<int>& s)
{
	//Print the whole stack but don't change it at all
	Stack<int> x = s;
	while(!x.isEmpty())
	{
		cout << x.top() << " ";
		x.pop();
	}
	cout << endl;
}

void clearStack(Stack<int>& s)
{
	//Clear the whole stack
	//Use makeEmpty?
	//Catch underflow(stack was already empty)
	try{
		s.makeEmpty();
	}catch(Underflow exc){
		cout << "Underflow Error" << endl;
	}
}

void duplicate(Stack<int>& s)
{
	//Duplicate the top of the stack and push it on
	//Catch underflow (Empty stack)
	//Catch overflow (Full stack)
	int x;
	x = s.top();
	s.push(x);
}

void reverse(Stack<int>& s)
{
	//Reverse the order of the stack
	//catch undeflow
	try{

		Stack<int> x(10);
		while(!s.isEmpty())
		{
			x.push(s.top());
			s.pop();		
		}
		s = x;

	} catch (Underflow exc) {
		cout << "Underflow Error" << endl;
	}
	
}

void addition(Stack<int>& s)
{
	try{
		int x = s.top();
		s.pop();
		int y = s.top();
		s.pop();
		s.push(x + y);
	}
	catch(Underflow exc)
	{
		cout << "Undeflow Error" << endl;
	}
	catch(Overflow exc)
	{
		cout << "Overflow Error" << endl;
	}
}

void subtraction(Stack<int>& s)
{
	try{
                int x = s.top();
		s.pop();
                int y = s.top();
		s.pop();
                s.push(y - x);
        }
        catch(Underflow exc)
        {
                cout << "Undeflow Error" << endl;
        }
        catch(Overflow exc)
        {
                cout << "Overflow Error" << endl;
        }

}

void multiplication(Stack<int>& s)
{
	try{
                int x = s.top();
		s.pop();
                int y = s.top();
		s.pop();
                s.push(x * y);
        }
        catch(Underflow exc)
        {
                cout << "Undeflow Error" << endl;
        }
        catch(Overflow exc)
        {
                cout << "Overflow Error" << endl;
        }

}

void division(Stack<int>& s)
{
	try{
                int x = s.top();
		s.pop();
                int y = s.top();
		s.pop();
                s.push(y / x);
        }
        catch(Underflow exc)
        {
                cout << "Undeflow Error" << endl;
        }
        catch(Overflow exc)
        {
                cout << "Overflow Error" << endl;
        }

}	

void mod(Stack<int>& s)
{
	try{
                int x = s.top();
		s.pop();
                int y = s.top();
		s.pop();
                s.push(y % x);
        }
        catch(Underflow exc)
        {
                cout << "Undeflow Error" << endl;
        }
        catch(Overflow exc)
        {
                cout << "Overflow Error" << endl;
        }

}













