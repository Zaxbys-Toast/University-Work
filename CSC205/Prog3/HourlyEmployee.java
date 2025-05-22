import java.util.*;
import java.io.*;
public class HourlyEmployee extends Employee implements Serializable
{
  public HourlyEmployee(String name, double pay)
  {
	super(name, pay);
  }

  public double computePay(double hours)
  {
	if(hours <= 40)
	{
		return hours * getWage();
	}
	else
	{
		return ((40 * getWage()) + ((hours - 40) * 1.5 * getWage()));
	}
  }

  public String toString()
  {
	return pad(getName(), 20)  + String.format("%15s","$" +  getWage() + "/hour");
  }

}
