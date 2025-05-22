public class Employee extends Person
{
	private double salary = 0;
	private Date employmentDate = new Date();
	
	public Employee(String firstName, String lastName, double pay, Date hireDate, Date birthDate)
	{
		super(lastName, firstName, birthDate);
		salary = pay;
		employmentDate = hireDate;		
	}

	public double getSalary()
	{
		return salary;
	}

	public Date getHireDate()
	{
		return employmentDate;
	}
	
	public String toString()
	{
		String employee = "";
		employee += "name = " + getLastName() + ", " + getFirstName();
		employee += "\nsalary = " + getSalary();
		employee += "\nbirth = " + getBirthDate();
		employee += "\nhired = " + getHireDate();
		return employee;	
	}

	public void setHireDate(Date newDate)
	{
		employmentDate = newDate;	
	}

	public void setSalary(double newSalary)
        {
                salary = newSalary;
        }

}
