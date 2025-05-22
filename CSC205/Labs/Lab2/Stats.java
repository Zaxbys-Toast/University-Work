import java.util.Scanner;
public class Stats
{
	private static final int MAX_SIZE = 100;
	public static void main(String[] args)
	{
        	int[] List = new int[MAX_SIZE];		
		int numItems;

        	numItems = fillUp (List);

        	System.out.println("\n\10\7" + " The range of your " +
                                   numItems + " items is :  " + 
				   range (List, numItems));

        	System.out.println("\n\10\7" + " The mean of your " + 
                                   numItems + " items is  :  " +
				   mean (List, numItems));
	}
	public static int fillUp(int[] List)
	{
		System.out.println("Please Input Your Values (Enter a 0 to Stop): ");				
		Scanner input = new Scanner(System.in);
		int num = 1;
		int numItems = 0;
		int i = 0;
		while(i < MAX_SIZE && num != 0){
				List[i] = input.nextInt();
				num = List[i];
				i++;
				numItems++;	
			}				
		return numItems - 1;

	}
	public static int range(int[] List, int numItems){
		int min = List[0];
		int max = List[0];
		for(int i = 0; i<numItems; i++){
			if(List[i] < min)
			{
				min = List[i];
			}
			if(List[i] > max)
			{
				max = List[i];
			}
		}
		return max - min;
	}
	public static double mean(int[] List, int numItems){
		double sum = 0;
		for(int i =0; i < numItems; i++){
			sum += List[i];
		}
		return sum/numItems;
	}








}
