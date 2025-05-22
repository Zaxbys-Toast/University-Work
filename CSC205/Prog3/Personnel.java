import java.util.*;
import java.io.*;
public class Personnel implements Serializable
{
  private static final long serialVersionUID = 1234567L;
  private static int eCount = 0;
  private static ArrayList<Employee> employees = new ArrayList<Employee>(5);
	
  public static void main(String[] args)
  {
	run(employees);
  }

  public static void run(ArrayList<Employee> list)
  {
	Scanner in = new Scanner(System.in);
	int key = 1;
	String choice = "x";
	while(key != 0)
	{
		menu();
		System.out.print("\nEnter Command: ");
		choice = in.nextLine();
		while(choice.compareTo("n") != 0 && choice.compareTo("c") != 0 && choice.compareTo("p") != 0 && choice.compareTo("r") != 0
			 && choice.compareTo("d") != 0 && choice.compareTo("u") != 0 && choice.compareTo("q") != 0)
		{
			System.out.println("Command was not recognized: Please try again");
			System.out.print("Enter Command: ");
			choice = in.nextLine();
		}			
		switch(choice)
		{
			case "n":
				newEmployee();
				break;
			case "c":
				computeChecks(list);
				break;
			case "p":
				printAll(list);
				break;
			case "r":
				increasePay(list);
				break;
			case "d":
				download(list);
				break;
			case "u":
				upload(list);
				break;
			case "q":
				key = 0;
				break;
		}				
	}
  }

  public static void menu()
  {
	System.out.println("-----------------------------------");
	System.out.println("|Commands: n - New Employee       |");
	System.out.println("|          c - Compute Paychecks  |");
	System.out.println("|          r - Raise Wages        |");
	System.out.println("|          p - Print Records      |");
	System.out.println("|          d - Download Data      |");
	System.out.println("|          u - Upload Data        |");
	System.out.println("|          q - Quit               |");
	System.out.println("-----------------------------------");
  }

  public static void newEmployee()
  {
	String name;
	double wage;
	char type;
	Scanner in = new Scanner(System.in);
	
	System.out.print("\nEnter name of new employee: ");
	name = in.nextLine();
	System.out.print("\nHourly (h) or salaried (s): ");
	type = in.next().charAt(0);
	while (type != 'h' && type != 's')
	{
		System.out.println("Input was not h or s; please try again");
		type = in.next().charAt(0);
	}
	if(type == 's')
	{
		System.out.print("\nEnter annual salary: ");
		wage = in.nextDouble();
		employees.add(new SalariedEmployee(name, wage));
	}	
	if(type == 'h')
	{
		System.out.print("\nEnter hourly pay: ");
                wage = in.nextDouble();
		employees.add(new HourlyEmployee(name, wage));
	}
	eCount++;
  }

  public static void computeChecks(ArrayList<Employee> list)
  {
	Scanner in = new Scanner(System.in);
  	for(int i = 0; i < list.size(); i++)
	{
		double hours = 0;
		double pay = 0;
		System.out.print("\nEnter the number of hours " + (list.get(i)).getName() + " worked: ");
		hours = in.nextDouble();
		pay = (list.get(i)).computePay(hours);
		System.out.println("\nPay: $" + toDollars(pay));
	}	
  }

  public static String toDollars(double amount) 
  {
    	long roundedAmount = Math.round(amount * 100);
    	long dollars = roundedAmount / 100;
    	long cents = roundedAmount % 100;

    	if (cents <= 9)
      		return dollars + ".0" + cents;
    	else
      		return dollars + "." + cents;
  }

  public static void increasePay(ArrayList<Employee> list)
  {
	Scanner in = new Scanner(System.in);
	System.out.print("\nEnter percentage increase: ");
	double increase = in.nextDouble();
	for(int i = 0; i < list.size(); i++)
	{
		(list.get(i)).increasePay(increase);
	}
	System.out.println("New Wages");
	System.out.println("---------");
	for(int i = 0; i < list.size(); i++)
	{
		System.out.println((list.get(i)).toString());
	}
  }

  public static void printAll(ArrayList<Employee> list)
  {
	System.out.println("Employees");
	System.out.println("---------");
	for(int i = 0; i < list.size(); i++)
	{
		System.out.println(list.get(i).toString());
	}
  }

  public static void download(ArrayList<Employee> list) 
  {
	String fileName = "employee.dat";
	try
	{
		FileOutputStream fileOut = new FileOutputStream(fileName);
		ObjectOutputStream objOut = new ObjectOutputStream(fileOut);
		objOut.writeObject(list);
		objOut.close();
	}
	catch(IOException e)
	{
		System.out.println(e.getMessage());
	}
  }

  public static void upload(ArrayList<Employee> list)
  {
	String fileName = "employee.dat";
	try 
	{
		FileInputStream fileIn = new FileInputStream(fileName);
		ObjectInputStream in = new ObjectInputStream(fileIn);
		ArrayList<Employee> temp = (ArrayList<Employee>) in.readObject(); 
		in.close();
		for(int i = 0; i < temp.size(); i++)
		{	
			list.add(temp.get(i));
		}
      	}
	catch(IOException e)
	{
		System.out.println(e.getMessage());
	}
	catch(ClassNotFoundException e) 
	{
		System.out.println(e.getMessage());	
	}

  }

}	
