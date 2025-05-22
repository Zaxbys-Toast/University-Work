import java.util.*;
@SuppressWarnings("unchecked")

public class JCFStack
{
   public static void main(String[] args) throws CloneNotSupportedException
   {
		Scanner in = new Scanner(System.in);
		System.out.print("Enter a Key Value: ");
		Object key = new Object();
		int keyValue = in.nextInt();
		key = (Integer) keyValue;
        	Stack stack1 = new Stack();
		stack1.push(new Integer(27));
		stack1.push(new Integer(0));
		stack1.push(new Integer(-3));
		stack1.push(new Integer(-18));
		stack1.push(new Integer(99));
        	printStack (stack1);
		System.out.println("\nkey value: " + keyValue); 
		if(stack1.search(key) != -1)
		{
			System.out.println("key found at " + stack1.search(key));
		}
		else
			System.out.println("Key not found");
		
		
  }

  private static void printStack (Stack s) throws CloneNotSupportedException
  {
        Stack tempStack = (Stack) (s.clone());
        if (! tempStack.isEmpty())
                System.out.println("*** Printing Out Stack:  ");

        while (! tempStack.isEmpty())
        {
               System.out.print(tempStack.peek() + "  ");
               tempStack.pop();
        }
  }
}
