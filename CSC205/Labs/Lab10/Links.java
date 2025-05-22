
@SuppressWarnings("unchecked")

public class Links
{
	public static void main(String[] args)
	{
          	Node pos1 = null;
    		Node pos2 = null;
    		pos1 = new Node(new Integer(13));
   		pos1.setNext(new Node(new Integer(15), null));
    		pos2 = new Node(new Integer(11), null);
		pos2.setNext(pos1);
		printList(pos2);
		System.out.println(count(pos2));
		System.out.println(findMax(pos2));
	}

	private static void printList(Node head)
	{
		if (head != null)
		{
			System.out.println(head.getItem());
			printList(head.getNext());
		}
	}
	
	private static int count(Node head)
	{
		if(head.getNext() == null)
		{
			return 1;	
		}
		else
		{
			return 1 + count(head.getNext());
		}
	}
	
	private static int findMax(Node head)
	{
		int max = -999;
		Node curr = head;
		
		while(curr != null)
		{
			int currElement = (int)  ((Integer) curr.getItem()).intValue();
			if(currElement > max)
			{
				max = currElement;
			}
			curr = curr.getNext();				
		}
		
		return max;
	}

}
