public class MyTree
{
	public static void main(String[] args) throws CloneNotSupportedException
	{
		BinarySearchTree t = new BinarySearchTree();
		t.insert(new KeyedItem("M"));
		t.insert(new KeyedItem("W"));
		t.insert(new KeyedItem("Z"));
		t.insert(new KeyedItem("S"));
		t.insert(new KeyedItem("T"));
		t.insert(new KeyedItem("J"));
		t.insert(new KeyedItem("D"));
		t.insert(new KeyedItem("F"));
		t.insert(new KeyedItem("L"));
	//	t.inorder();
		t.preorder();
		BinarySearchTree myCopy = new BinarySearchTree();
		t.insert(new KeyedItem("M"));
                t.insert(new KeyedItem("W"));
                t.insert(new KeyedItem("Z"));
                t.insert(new KeyedItem("S"));
                t.insert(new KeyedItem("T"));
                t.insert(new KeyedItem("J"));
                t.insert(new KeyedItem("D"));
                t.insert(new KeyedItem("F"));
                t.insert(new KeyedItem("L"));
		if (t.duplicateCheck(myCopy))
			System.out.println("They're Duplicates");
		else
			System.out.println("They're Not Duplicates");
	}















}
