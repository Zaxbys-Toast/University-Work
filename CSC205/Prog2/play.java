import java.util.*;
import java.io.*;

public class play
{
	public static void main(String[] args) {
		String fileName = start();
		ArrayList<LibraryBook> books = new ArrayList<LibraryBook>(50); 
		int numBooks = inputBooks(fileName, books);
		sortBooks(books, numBooks);
		stall();
		run(books);
	}
	//Takes all of the book data from a .dat file and adds it into an ArrayList of the LibraryBook type
	public static int inputBooks(String inputFile, ArrayList<LibraryBook> books) {
		int numBooks = 0;
		try
		{
			Scanner in = new Scanner(new File(inputFile));
			while(in.hasNext())
			{
				Scanner lsc = new Scanner(in.nextLine()).useDelimiter(";");

				String title = lsc.next();
				String name = lsc.next();
				int copyright = lsc.nextInt();
				double price = lsc.nextDouble();
				String genre = lsc.next();

				books.add(new LibraryBook(title,name,copyright,price,genre));
				
				numBooks++;
			}
		}
		catch (IOException e) 
		{
			System.out.println(e.getMessage());
		}
		return numBooks;
	}

	//Runs the opening screen where the user selects a file. Only happens on start-up. Returns the file name
	public static String start()
	{
		String fileName;
		Scanner input = new Scanner(System.in);
		clearScreen();
		System.out.println("                    The Book Search Program             ");
		System.out.println("	----------------------------------------------------");
		System.out.println("		What file is your book data stored in?");
		System.out.println("\n\n		Here are the files in the current directory :\n");
		fileStuff();
		System.out.print("\n\n		Filename: ");
		fileName = input.nextLine();
		return fileName;			
	}

	//Prints all of the data contained in a LibraryBook object in the proper format
	public static void printRecord(ArrayList<LibraryBook> books, int location) {
		System.out.println("	Record #" + (location + 1) + " :");
		System.out.println("	^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
		System.out.print("   	             Title:");
		System.out.printf("%25s" , books.get(location).getTitle() + "\n");
		System.out.print("    	     Author's Name:");
		System.out.printf("%25s" , books.get(location).getAuthor() + "\n");
		System.out.print("     	         Copyright:");
		System.out.printf("%25s" , books.get(location).getCopyright() + "\n");
		System.out.print("                     Price:");
		System.out.printf("%25s" ,books.get(location).getPrice() + "\n");
		System.out.print("                     Genre:");
		System.out.printf("%25s" , books.get(location).getGenre() + "\n");
		System.out.println("	^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
	}
	//Sorts the books using a set of for and if loops
	public static void sortBooks(ArrayList<LibraryBook> list, int numBooks)
	{
		int minIndex;
		LibraryBook temp;
		for (int i = 0; i < numBooks - 1; i++)
		{
			minIndex = i;
			LibraryBook curr = list.get(i);
			for(int j = i; j < numBooks; j++)
			{
				LibraryBook test = list.get(j);
				if ((curr.getTitle()).compareTo(test.getTitle()) >= 0)
				{
					curr = list.get(j);
					minIndex = j;
				}
			} 
			if (minIndex != i)
			{
				temp = list.get(i);
				list.set(i, list.get(minIndex));
				list.set(minIndex, temp);
			}
		}
		System.out.println("	A total of " + numBooks + " books have been input and sorted by title.");
	}

	//Prints out all of the options and the title
	public static void menu()
	{
		clearScreen();
		System.out.println("	^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
		System.out.println("	      THE GREAT BOOKS SEARCH PROGRAM      ");
		System.out.println("	^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
		System.out.println("	1) Display All Book Records");
		System.out.println("	2) Search for a Book Title");
		System.out.println("	3) Exit Search Program");
		System.out.println("	^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");		
	}
	//Prints all  of the books using printRecord
	public static void displayAll(ArrayList<LibraryBook> book)
	{
		clearScreen();
		for(int i = 0; i < book.size(); i ++)
		{
			printRecord(book, i);
			stall();
			clearScreen();			
		}		
	}
	//Uses a binarySearch to check if the  user input title is a book in the library
	public static void bookSearch(ArrayList<LibraryBook> book)
	{
		Scanner stdin = new Scanner(System.in);
		int found = 0;
		int first = 0;
		int last = book.size() - 1;
		int middle;
		System.out.print("	Please Enter the Title of a Book: ");
		String bookTitle = stdin.nextLine();
		clearScreen();
		while(found == 0 && first <= last)
		{
			middle = (int) ((first + last) / 2);
			String midTitle = (book.get(middle)).getTitle();
			if (bookTitle.compareTo(midTitle) == 0)
			{
				printRecord(book, middle);
				found ++;
			}
			else if (bookTitle.compareTo(midTitle) < 0)
			{
				last = middle - 1;
			}
			else
			{
				first = middle + 1;
			}
			
		}	
		if(found == 0)
		{
			System.out.println("	The Book " + bookTitle + " Was Not Found");
		}
		stall();	
	}
	//Runs the displayAll, bookSearch, and menu on a loop. What is running the program
	public static void run(ArrayList<LibraryBook> book)
	{
		menu();
		int choice;
		Scanner input = new Scanner(System.in);
		System.out.print("	Select an Option: ");
		choice = input.nextInt();
		while (choice > 3 || choice < 1)
		{
			System.out.print("\n	Invalid Choice Please Choose Another Option: )");
			menu();
			choice = input.nextInt();	
		}
		while (choice <= 3 && choice > 0)
		{
			switch(choice)
			{
				case 1 : 
					displayAll(book);
					break;
				case 2 : 
					bookSearch(book);
					break;
				case 3 :
					System.out.println("	Goodbye. Have a Nice Day. :-)");
					break;			
			}
			if(choice != 3)
			{
				menu();
				System.out.print("	Select an Option: ");
				choice = input.nextInt();		
			}
			else
			{
				break;
			}
			while(choice > 3 || choice < 1)
			{
				System.out.print("\n    Invalid Choice Please Choose Another Option: ");
                        	choice = input.nextInt();
			}			
		}
			
	} 
       //Method to clear the screen
        public static void clearScreen()
	{
		System.out.println("\033[H\033[2J");
		System.out.flush();

	}
       //Method to make people hit return to continue
	public static void stall()
	{
		Scanner input = new Scanner(System.in);
		System.out.print("	Please Hit Return to Continue...");
		String dummy = input.nextLine();		
	}
	//Method that finds all the files in the directory
	public static void fileStuff()
	{
		//Get all files from directory
		File curDir = new File(".");                                
		String[] fileNames = curDir.list();
	        ArrayList<String> data = new ArrayList<String>();
		//Find files which may have data. (aka, are in the .dat format)
		for(String s:fileNames) 
		{  
			if(s.endsWith(".dat"))
			{ 
				data.add(s);
			}
		}
		for(int i = 0; i < data.size(); i ++)
		{
			System.out.print(data.get(i) + "	");
		}                                                                                                                                                                                                                
	}
}	 
