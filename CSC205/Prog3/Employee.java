import java.io.*;

public abstract class Employee implements Serializable
{
  private String name;
  private double wage;
   
  public abstract double computePay(double hours);

  public double getWage()
  {
	return wage; 
  }

  public String getName()
  {
	return name;
  }

  public void setWage(double wage)
  {
	this.wage = wage;
  }

  public void setName(String name)
  {
	this.name = name;
  }

  public Employee(String name, double wage)
  {
	this.name = name;
	this.wage = wage;
  }

  public void increasePay(double percentage)
  {
	this.wage += (wage * (percentage / 100));
  }

  public static String pad(String str, int n) {
    if (str.length() > n)
      return str.substring(0, n);
    while (str.length() < n)
      str += " ";
    return str;
  }

}
