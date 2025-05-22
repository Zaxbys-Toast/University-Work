public class CheckingAccount extends Account
{
	private int checksWritten = 0;	
	
	public CheckingAccount(double initialBalance)
	{
		super(initialBalance);
		checksWritten = 0;		
	}
	
	public int getChecksWritten()
	{
		return checksWritten;
	}

	public void writeCheck(double amount)
	{
		withdraw(amount);	
		checksWritten++;			
	}

	








}
