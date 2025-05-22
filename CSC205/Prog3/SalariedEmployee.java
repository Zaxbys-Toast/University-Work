import java.io.*;
import java.util.*;
public class SalariedEmployee extends Employee implements Serializable
{
  private int salary;
  
  public SalariedEmployee(String name, double pay)
  {	
        super(name, pay);
  }

  public double computePay(double hours)
  {
	return (getWage()/52);
  }
	
  public String toString()
  {
	return pad(getName(), 20) +  String.format("%15s","$" + getWage() + "/year"); 		
  }
}

