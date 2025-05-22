import java.util.*;
public class TestClock{
	public static void main(String[] args){
		int hours;
		int minutes;
		int seconds;
		Scanner stdin = new Scanner(System.in);
		System.out.println("What time would you like to set your DVR to?");
		System.out.print("\nHours: ");
		hours = stdin.nextInt();
		System.out.print("Minutes: ");
		minutes = stdin.nextInt();
		System.out.print("Seconds: ");
		seconds = stdin.nextInt();
		Clock DVR = new Clock();
		DVR.reset(hours,minutes,seconds);
		System.out.println("\nThe time is now " + DVR.toString());
		DVR.advance();
		System.out.println("\nAdvancing the time!");
		System.out.println("\nThe time is now " + DVR.toString());
	}
}
