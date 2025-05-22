import java.io.*;

public class Pez 
{

  public static void main(String[] args)
  {
	Stack Pez = new Stack();
	addPez(Pez);
	removeGreen(Pez);
	printStack(Pez);
  }

  public static void addPez(Stack s)
  {
	s.push("yellow");
	s.push("red");
	s.push("green");
	s.push("green");
	s.push("yellow");
	s.push("yellow");
	s.push("red");
	s.push("green");
  }

  public static void removeGreen(Stack s) 
  {
	Stack temp = new Stack();
	String key = "green";
	while(! s.isEmpty())
	{
		if(((String)s.top()).compareTo(key) == 0)
		{
			s.pop();
		}
		else
		{
			temp.push(s.top());
			s.pop();
		}
	}
	
	while(! temp.isEmpty())
	{
		s.push(temp.top());
		temp.pop();
	}
	
  }

  public static void printStack(Stack s)
  {
	Stack temp = new Stack();
	
	while(! s.isEmpty())
	{
		temp.push(s.top());
		s.pop();
	}
	
	while(! temp.isEmpty())
	{
		s.push(temp.top());
		System.out.println(temp.top());
		temp.pop();
	}
  }
}
