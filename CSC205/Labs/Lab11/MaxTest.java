
import java.io.*;
@SuppressWarnings("unchecked")

public class MaxTest 
{
   public static void main(String[] args) throws IOException, CloneNotSupportedException
   {
        	Stack stack1 = new Stack();
		stack1.push("Andy");
		stack1.push("Allison");
		stack1.push("Aaron");
		stack1.push("Austin");
		stack1.push("Abbey");
		stack1.push("Alex");
        	System.out.println("findMax(stack1)="+findMax(stack1)); 
        	System.out.println("stack1.findMax()="+stack1.findMax()); 
  }

  public static String findMax(Stack st1) throws CloneNotSupportedException
  {
		Stack temp = (Stack) st1.clone();
		String currMax = "AAAAAAA";
		while(! temp.isEmpty())
		{
			if(((String)temp.top()).compareTo(currMax) > 0)
			{
				currMax =(String) temp.top();
			}
			temp.pop();	
		}
		return currMax;

	
  }

}
