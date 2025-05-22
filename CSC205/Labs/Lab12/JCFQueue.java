
import java.util.*;

@SuppressWarnings("unchecked")
public class JCFQueue
{
	public static void main(String[] args) throws CloneNotSupportedException
	{
		LinkedList queue1 = new LinkedList();
		LinkedList queue2 = new LinkedList();
		Object key = new Character('$');

        	queue1.addLast(new Character('b'));
        	queue1.addLast(new Character('$'));
        	queue1.addLast(new Character('E'));
        	queue1.addLast(new Character('$'));
        	queue2.addLast(new Character('b'));
        	queue2.addLast(new Character('$'));
        	queue2.addLast(new Character('E'));
        	queue2.addLast(new Character('b'));
		System.out.println("dup check = " +
                    identicalCheck(queue1, queue2));
		findAndReplace(queue1, key, new Character('*'));
		System.out.println("** After findAndReplace **");
		printQueue(queue1);
	}

	private static boolean identicalCheck(LinkedList queue1,
                                              LinkedList queue2)
                throws CloneNotSupportedException
	{
		LinkedList temp1 = (LinkedList) queue1.clone();
		LinkedList temp2 = (LinkedList) queue2.clone();
		if(temp1.isEmpty() && temp2.isEmpty())
		{
			return true;
		}
		if(temp1.isEmpty() && ! temp2.isEmpty())
		{
			return false;
		}
		if(temp1.getFirst() != temp2.getFirst())
		{
			return false;
		}
		temp1.removeFirst();
		temp2.removeFirst();
		return identicalCheck(temp1, temp2);
		
	}


	private static void findAndReplace(LinkedList queue1, 
		Object key, Object newVal)
	{
		for(int i = 0; i < queue1.size(); i++)
		{
			if(queue1.get(i).equals(key))
			{
				queue1.set(i, newVal);
			}
		}


	}


	private static void printQueue (LinkedList q)
		 throws CloneNotSupportedException
	{
		for(int i = 0; i < q.size(); i ++)
		{
			System.out.print(q.get(i));
		}


	}


}
