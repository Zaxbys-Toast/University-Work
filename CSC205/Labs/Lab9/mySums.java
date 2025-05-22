public class mySums
{
	public static int interativeSum(int n)
	{
		int sum = 0;
		while(n != 0)
		{
			sum += Math.pow(2,n) + 1;
			n--;	
		}
		return sum;
	}

	public static int recurSum(int n)
	{
		if( n == 1)
		{
			return 3;
		}
		else
		{
			return (int)(Math.pow(2,n) + 1) + recurSum(n - 1);
		}
	}

	public static void main(String[] args)
	{
		System.out.println(interativeSum(5));
		System.out.println(recurSum(5));
	}
}
