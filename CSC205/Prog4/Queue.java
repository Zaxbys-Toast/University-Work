
@SuppressWarnings("unchecked")
public class Queue implements QueueInterface { // A Queue class built under the hood as a circular linked list.
  private Node lastNode;  // Points to item in rear.  The next field of lastNode always points to front of the queue.
  
  public Queue() {
    lastNode = null;   
  }  // end default constructor
  
  // queue operations:
  public boolean isEmpty() {
        return (lastNode == null);
  }  // end isEmpty

  public void dequeueAll() {
    lastNode = null;
  }  // end dequeueAll

  public void enqueue(Object newItem) {
	if(isEmpty())
	{
		Node item = new Node(newItem);
		lastNode = item;
		lastNode.setNext(item);
	}
	else
	{
		Node item = new Node(newItem, lastNode.getNext());
		lastNode.setNext(item);
		lastNode = item;
	}

  } 

  public Object dequeue() throws QueueException {

   	  // INSERT YOUR CODE HERE to handle 3 cases: when queue is empty, has one item, and has more than one item
	if (!isEmpty())
	{ 
	
		Object temp = lastNode.getNext().getItem();
	 	lastNode.getNext().setItem(null);
		if(lastNode.getNext() == lastNode )	
	 	{
			dequeueAll();
		 
	 	}
	 	else
	 	{
			 lastNode.setNext(lastNode.getNext().getNext());
	 	}
	 	return temp;
	}		 
	else
	{
		throw new QueueException("QueueException on dequeue:" + " queue empty");
	}
  }
  
  public Object peek() {
    return lastNode.getNext().getItem();
  }

  public Object front() throws QueueException {
    if (!isEmpty()) {
      Node firstNode = lastNode.getNext();
      return firstNode.getItem();
    }
    else {
      throw new QueueException("QueueException on front:"
                             + "queue empty");
    }
  }

  public Object clone() throws CloneNotSupportedException
  {
	boolean copied = false;
        Queue copy = new Queue();
        Node curr = lastNode, prev = null;
        while ( (! copied) && (lastNode != null) )
        {
                Node temp = new Node(curr.getItem());
                if (prev == null)
                        copy.lastNode = temp;
                else
                prev = temp;
                curr = curr.getNext();
		copied = (lastNode == curr);
        }
	prev.setNext(copy.lastNode);
        return copy;
  }
} // end Queue
